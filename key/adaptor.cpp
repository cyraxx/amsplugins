/*
 * AMS key auth adaptor
 * https://github.com/cyraxx/amsplugins
 *
 * This AMS access plugin requires that all publishing clients include a key parameter as part of the
 * URL (for example: rtmp://yourserver/live?key=secretkey). All other clients get their write access
 * revoked so they can't publish.
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
	iMinor = 1;
	iMicro = 0;
}

void KeyAdaptor::onAccess(IFCAccess* pAccess)
{
	if(pAccess->getType() != IFCAccess::CONNECT) return;

	std::string key = getKeyFromURI(pAccess->getValue(fms_access::FLD_SERVER_URI));

	if(key.empty())
	{
		// If no key has been supplied, remove write access so the client can't publish
		pAccess->setValue(fms_access::FLD_WRITE_ACCESS, "");
		pAccess->setValue(fms_access::FLD_WRITE_LOCK, "true");
		pAccess->accept();
	}
	else
	{
		const char* clientIP = pAccess->getValue(fms_access::FLD_CLIENT_IP);
		if(!clientIP) clientIP = "unknown address";

		openlog("AmsKeyAdaptor", LOG_CONS, LOG_USER);

		const char* error = checkKey(key);
		if(error)
		{
			// Reject the connection if a key has been supplied but is invalid
			syslog(LOG_INFO, "Rejecting publisher connection from %s (%s)", clientIP, error);
			pAccess->reject(error);
		}
		else
		{
			syslog(LOG_INFO, "Accepting publisher connection from %s", clientIP);
			pAccess->accept();
		}

		closelog();
	}
}

// Extracts the key from the server URI and returns it, or an empty string is no key was supplied
const std::string KeyAdaptor::getKeyFromURI(const char* url)
{
	if(!url) return "";
	std::string urlString(url);

	size_t keyIndex = urlString.find("?key=");
	if(keyIndex == std::string::npos) return "";

	return urlString.substr(keyIndex + 5);
}

// Checks the supplied key against the key file and returns an error message, or NULL if the key is valid
const char* KeyAdaptor::checkKey(const std::string suppliedKey)
{
	std::ifstream keyfile("./conf/keys");
	if(!keyfile.is_open()) return "Error reading key file";

	std::string key;

	while(std::getline(keyfile, key)) {
		if(key.empty() || key[0] == '#') continue;
		if(key == suppliedKey) return NULL;
	}

	return "Invalid key";
}