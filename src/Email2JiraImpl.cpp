#include "Email2JiraImpl.h"

#include "ImapAdapterImpl.h"

namespace tyntec { namespace email2jira {

Email2JiraImpl::Email2JiraImpl(boost::asio::io_service& refIoService, log4cxx::LoggerPtr spLogger):
    refIoService_(refIoService),
    spLogger_(spLogger)
{
    LOG4CXX_TRACE(spLogger_, "Email2JiraImpl constructed");
}

Email2JiraImpl::~Email2JiraImpl(void)
{
    LOG4CXX_TRACE(spLogger_, "Email2JiraImpl will be destructed.");
}

void Email2JiraImpl::init(void)
{
    LOG4CXX_TRACE(spLogger_, "Email2JiraImpl start init");


    ImapAdapterImpl adapter;
    try  {
        adapter.createSession();
        adapter.openStore();
        adapter.openConnection();
    }
    catch(std::runtime_error& ex)
    {
        LOG4CXX_ERROR(spLogger_, "RuntimeError: " << ex.what());
    }
    catch(...)
    {
        LOG4CXX_ERROR(spLogger_, "unhandled exception.");
    }
}

void Email2JiraImpl::fini(void)
{
    LOG4CXX_TRACE(spLogger_, "Email2JiraImpl will be fini :)");
}

}}
