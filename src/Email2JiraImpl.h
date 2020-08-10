#pragma once

#include <boost/asio.hpp>

#include <log4cxx/logger.h>

namespace tyntec { namespace email2jira {

class Email2JiraImpl
{
    boost::asio::io_service&        refIoService_;
    log4cxx::LoggerPtr              spLogger_;

public:
    Email2JiraImpl(boost::asio::io_service& refIoService, log4cxx::LoggerPtr);
    ~Email2JiraImpl(void);

    void init(void);

    void fini(void);
};

}}
