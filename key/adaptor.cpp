/*
 * AMS key auth adaptor
 * https://github.com/cyraxx/amsplugins
 *
 * This AMS access plugin requires that all clients with certain user agent strings (see below) include
 * a key parameter as part of the URL (for example: rtmp://yourserver/live?key=secretkey). All other
 * clients also get their write access revoked so they can't publish.
 *
 * Valid keys are to be specified in a file called keys inside the AMS conf directory, one key per line.
 */

#include "adaptor.h"

int FCExport IFCCreateAccessAdaptor(IFCAccessContext* pCtx, IFCAccessAdaptor*& pAdaptor)
{
	pAdaptor = new KeyAdaptor(pCtx);
	return pAdaptor ? 1 : 0;
}

KeyAdaptor::KeyAdaptor(IFCAccessContext* pCtx)  
{
	m_pCtx = pCtx;

	openlog("AmsKeyAdaptor", LOG_CONS, LOG_USER);
	syslog(LOG_INFO, "Initializing key access adaptor");
	closelog();

	// These user agents will be considered publishers and need to provide a key
	// (and will be the only ones with write access)
	m_publishingUserAgents.push_back("FMLE/");
	m_publishingUserAgents.push_back("FME/");
	m_publishingUserAgents.push_back("Wirecast/FM");
}

KeyAdaptor::~KeyAdaptor()  
{
}

const char* KeyAdaptor::getDescription() const
{
	return "Key access adaptor";
}

void KeyAdaptor::getVersion(int& iMajor, int& iMinor, int& iMicro) const
{
	iMajor = 1;
	iMinor = 0;
	iMicro = 0;
}

void KeyAdaptor::onAccess(IFCAccess* pAccess)
{
	switch(pAccess->getType())
	{
		case IFCAccess::CONNECT:
		{
			bool isPublisher = false;

			const char* userAgent = pAccess->getValue(fms_access::FLD_USER_AGENT);
			if(userAgent) {
				std::string uaString(userAgent);
				for(unsigned i = 0; i < m_publishingUserAgents.size(); i++) {
					if(uaString.find(m_publishingUserAgents[i]) != std::string::npos) {
						isPublisher = true;
						break;
					}
				}
			}

			if(!isPublisher) {
				// For regular clients (i.e. non-publishers), accept the connection but remove their write access so they can't publish
				pAccess->setValue(fms_access::FLD_WRITE_ACCESS, "");
				pAccess->setValue(fms_access::FLD_WRITE_LOCK, "true");
				pAccess->accept();
			} else {
				// If a publisher connects, check their key and accept or reject the connection
				const char* clientIP = pAccess->getValue(fms_access::FLD_CLIENT_IP);
				if(!clientIP) clientIP = "unknown address";

				openlog("AmsKeyAdaptor", LOG_CONS, LOG_USER);

				const char* error = checkKey(pAccess->getValue(fms_access::FLD_SERVER_URI));
				if(error) {
					syslog(LOG_INFO, "Rejecting publisher connection from %s", clientIP);
					pAccess->reject(error);
				} else {
					syslog(LOG_INFO, "Accepting publisher connection from %s", clientIP);
					pAccess->accept();
				}

				closelog();
			}

			break;
		}

		default:
			break;
	}
}

// Checks for a valid key based on the supplied URL. Returns an error message, or NULL if the key is valid.
const char* KeyAdaptor::checkKey(const char* url)
{
	if(!url) return "Need key";
	std::string urlString(url);

	size_t keyIndex = urlString.find("?key=");
	if(keyIndex == std::string::npos) return "Need key";

	std::string suppliedKey = urlString.substr(keyIndex + 5);

	std::ifstream keyfile("./conf/keys");
	if(!keyfile.is_open()) return "Error reading key file";

	std::string key;

	while(std::getline(keyfile, key)) {
		if(key.empty() || key[0] == '#') continue;
		if(key == suppliedKey) return NULL;
	}

	return "Invalid key";
}