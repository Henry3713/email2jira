#include "ImapAdapterImpl.h"
#include <stdexcept>
#include <fstream>

namespace tyntec { namespace email2jira {

ImapAdapterImpl::ImapAdapterImpl(log4cxx::LoggerPtr spLogger):
    spLogger_(spLogger),
    serviceUri_("imaps://jira-test:EL0BEkpal@maildo.tyntec.com"),
    certPath_("/home/henry/data/mycert.pem"),
    rootCAs_(),
    verifier_(vmime::make_shared<vmime::security::cert::defaultCertificateVerifier>()),
    session_()
{
    vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();
}

ImapAdapterImpl::~ImapAdapterImpl(void)
{
    int i = 0;
}

void ImapAdapterImpl::createSession(void)
{
    session_ = vmime::net::session::create();
}

void ImapAdapterImpl::openStore(void)
{
    vmime::utility::url  url(serviceUri_.c_str());
    store_  =  session_->getStore(url);
    if(store_)
    {
        store_->setProperty("connection.tls", true);
        store_->setCertificateVerifier(verifier_);
    }

}

void ImapAdapterImpl::loadCertificate()
{
    std::ifstream certFile;
    certFile.open(certPath_.c_str(), std::ios::in | std::ios::binary);

    if (!certFile)
    {
        // handle error
        throw std::runtime_error("could not load certificate.");
    }

    vmime::utility::inputStreamAdapter is (certFile);
    vmime::shared_ptr<vmime::security::cert::X509Certificate> spCert;

    spCert = vmime::security::cert::X509Certificate::import(is);

    rootCAs_.push_back(spCert);

    if(verifier_)
    {
        verifier_->setX509RootCAs(rootCAs_);
    }
}

void ImapAdapterImpl::openConnection(void)
{
    store_->connect();
    bool isConnected = store_->isConnected();
    if(isConnected)
    {
        LOG4CXX_TRACE(spLogger_, "Hurra");
    }
    else
    {
        LOG4CXX_TRACE(spLogger_, "shit...");
    }
}

}}
