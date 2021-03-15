#pragma once

#include<vmime/vmime.hpp>
#include<vmime/platforms/posix/posixHandler.hpp>

#include <log4cxx/logger.h>

#include <string>

namespace tyntec { namespace email2jira {

class ImapAdapterImpl
{
    using VecCertificates = std::vector<vmime::shared_ptr<vmime::security::cert::X509Certificate>>;
    using Verifier = vmime::shared_ptr<vmime::security::cert::defaultCertificateVerifier>;

    log4cxx::LoggerPtr spLogger_;
    std::string serviceUri_;
    std::string certPath_;

    VecCertificates                         rootCAs_;
    Verifier                                verifier_;

    vmime::shared_ptr<vmime::net::session>  session_;
    vmime::shared_ptr<vmime::net::store>    store_;
    vmime::shared_ptr<vmime::net::folder>   inbox_;

public:
    ImapAdapterImpl(log4cxx::LoggerPtr spLogger);
    ~ImapAdapterImpl(void);

    void createSession(void);
    void openStore(void);
    void loadCertificate(void);
    void openConnection(void);
    void openFolder(void);
};

}}
