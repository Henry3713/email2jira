#include "CertVerifierImpl.h"

namespace tyntec { namespace email2jira {


CertVerifierImpl::CertVerifierImpl()
{
    void verify(vmime::shared_ptr<certificateChain> certs);
    {
        vmime::shared_ptr<vmime::security::cert::certificate> cert=chain->getAt(0);

        std::cout << std::endl;
        std::cout << "Server sent a '" << cert->getType() << "'"
                  << " certificate." << std::endl;

    }
}

}}
