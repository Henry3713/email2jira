#include "ImapAdapterImpl.h"

namespace tyntec { namespace email2jira {

ImapAdapterImpl::ImapAdapterImpl(void):
    serviceUri_("imaps://jira-test:EL0BEkpal@maildo.tyntec.com"),
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
        store_->setProperty("connection.tls", true);

}

void ImapAdapterImpl::openConnection(void)
{
    store_->connect();
}

}}
