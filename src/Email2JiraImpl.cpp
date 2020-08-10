#include "Email2JiraImpl.h"

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
}

void Email2JiraImpl::fini(void)
{
    LOG4CXX_TRACE(spLogger_, "Email2JiraImpl will be fini :)");
}

}}
