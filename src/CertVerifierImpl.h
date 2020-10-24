#pragma once

#include<vmime/vmime.hpp>
#include<vmime/security/cert/certificateVerifier.hpp>

#include <string>

namespace tyntec { namespace email2jira {

class CertVerifierImpl:public vmime::security::cert::certificateVerifier
{
public:
    CertVerifierImpl(void);
    ~CertVerifierImpl(void);

    void verify(vmime::shared_ptr<certificateChain> certs);

};

}}
