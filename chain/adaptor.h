#if !defined(Adaptor_h)
#define Adaptor_h

#include "IFCAccessAdaptor.h"

typedef int (FCExport *AccessAdaptorFactory)(IFCAccessContext* pCtx, IFCAccessAdaptor*& pAdaptor);

class FCExport ChainLoadingAdaptor : public IFCAccessAdaptor 
{
	IFCAccessContext* m_pCtx;
	IFCAccessAdaptor* m_pChainAdaptor;
	void* m_libHandle;

	public:
		ChainLoadingAdaptor(IFCAccessContext* pCtx);

		virtual ~ChainLoadingAdaptor();

		virtual const char* getDescription() const;

		virtual void getVersion(int& iMajor, int& iMinor, int& iMicro) const;

		virtual void onAccess(IFCAccess* pAccess);
};

#endif	// !defined(Adaptor_h)
