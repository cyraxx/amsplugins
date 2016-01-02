#if !defined(Adaptor_h)
#define Adaptor_h

#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

#include "IFCAccessAdaptor.h"

class FCExport KeyAdaptor : public IFCAccessAdaptor
{
	IFCAccessContext* m_pCtx;

	public:
		KeyAdaptor(IFCAccessContext* pCtx);

		virtual ~KeyAdaptor();

		virtual const char* getDescription() const;

		virtual void getVersion(int& iMajor, int& iMinor, int& iMicro) const;

		virtual void onAccess(IFCAccess* pAccess);

	private:
		virtual const std::string getKeyFromURI(const char* url);

		virtual const char* checkKey(const std::string suppliedKey);
};

#endif	// !defined(Adaptor_h)
