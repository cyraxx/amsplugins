/*
 * Chain loading AMS auth adaptor
 * https://github.com/cyraxx/amsplugins
 *
 * This AMS access plugin chain loads another access plugin (which needs to be named libconnect_chain.so)
 * and passes any connections by a publisher with an FMLE user-agent string to that plugin. Any other
 * connections get their write access revoked so they can't publish.
 */

#include "adaptor.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <memory.h>
#include <syslog.h>

int FCExport IFCCreateAccessAdaptor(IFCAccessContext* pCtx, IFCAccessAdaptor*& pAdaptor)
{
	pAdaptor = new ChainLoadingAdaptor(pCtx);
	return pAdaptor ? 1 : 0;
}

IFCAccessAdaptor *chainLoadAdaptor(IFCAccessContext* pCtx, void*& libHandle) {
	const char* path = "./modules/access/libconnect_chain.so";

	// Open the chain loaded original plugin
	libHandle = dlopen(path, RTLD_LAZY);
	if(!libHandle) {
		syslog(LOG_ERR, "Unable to open chain auth adaptor: %s", dlerror());
		return NULL;
	}

	syslog(LOG_INFO, "Auth adaptor chain loaded from %s", path);

	// Get the adaptor factory function (IFCCreateAccessAdaptor) from the chain loaded plugin
	dlerror();
	AccessAdaptorFactory chainCreate = (AccessAdaptorFactory)dlsym(libHandle, IFC_ACCESS_ENTRY_PROC);

	char *error;
	if((error = dlerror()) != NULL) {
		syslog(LOG_ERR, "Unable to get chain auth adaptor factory function: %s", error);
		dlclose(libHandle);
		return NULL;
	}

	// Create the chain loaded adaptor instance
	IFCAccessAdaptor *adaptor = NULL;
	if(!chainCreate(pCtx, adaptor)) {
		adaptor = NULL;
		syslog(LOG_ERR, "Chain auth adaptor factory function returned an error");
	}

	return adaptor;
}

ChainLoadingAdaptor::ChainLoadingAdaptor(IFCAccessContext* pCtx)  
{
	m_pCtx = pCtx;
	m_libHandle = NULL;

	openlog("AmsChainAdaptor", LOG_CONS, LOG_USER);
	syslog(LOG_INFO, "Creating chain loading access adaptor");

	m_pChainAdaptor = chainLoadAdaptor(pCtx, m_libHandle);

	closelog();
}

ChainLoadingAdaptor::~ChainLoadingAdaptor()  
{
	if(m_pChainAdaptor) delete m_pChainAdaptor;
	if(m_libHandle) dlclose(m_libHandle);
}

const char* ChainLoadingAdaptor::getDescription() const
{
	return "Chain loading access adaptor";
}

void ChainLoadingAdaptor::getVersion(int& iMajor, int& iMinor, int& iMicro) const
{
	iMajor = 1;
	iMinor = 0;
	iMicro = 0;
}

void ChainLoadingAdaptor::onAccess(IFCAccess* pAccess)
{
	switch(pAccess->getType())
	{
		case IFCAccess::CONNECT:
		{
			const char *userAgent = pAccess->getValue(fms_access::FLD_USER_AGENT);
			
			// For normal clients (i.e. non-FMLE), accept the connection but remove their write access so they can't publish
			if(!userAgent || (!strstr(userAgent, "FMLE/") && !strstr(userAgent, "FME/"))) {
				pAccess->setValue(fms_access::FLD_WRITE_ACCESS, "");
				pAccess->setValue(fms_access::FLD_WRITE_LOCK, "true");
				pAccess->accept();

			// If a publisher connects but the original plugin couldn't be loaded, reject the connection for security reasons
			} else if(!m_pChainAdaptor) {
				openlog("AmsChainAdaptor", LOG_CONS, LOG_USER);
				syslog(LOG_WARNING, "Rejecting source connection due to missing chain adaptor");
				closelog();
				pAccess->reject("Internal error");

			// Hand off the connection to the chain loaded plugin for authentication
			} else {
				m_pChainAdaptor->onAccess(pAccess);

			}

			break;
		}

		default:
			break;
	}
}
