#pragma once

#include<vmime/vmime.hpp>
#include<vmime/platforms/posix/posixHandler.hpp>

#include <string>

namespace tyntec { namespace email2jira {

class ImapAdapterImpl
{
    std::string serviceUri_;

    vmime::shared_ptr<vmime::net::session>  session_;
    vmime::shared_ptr<vmime::net::store>    store_;

public:
    ImapAdapterImpl(void);
    ~ImapAdapterImpl(void);

    void createSession(void);
    void openStore(void);

    void openConnection(void);
};

}}
