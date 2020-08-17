#include "Email2JiraImpl.h"

#include <iostream> 
#include <string>
#include <functional>

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/xml/domconfigurator.h>
#include <log4cxx/helpers/exception.h>

#include <boost/program_options.hpp>
#include <boost/asio.hpp>

using namespace log4cxx;
using namespace log4cxx::helpers;

LoggerPtr loggerMyMain(Logger::getLogger( "main"));

using Email2JiraPtr = std::shared_ptr<tyntec::email2jira::Email2JiraImpl>;

Email2JiraPtr g_spEmail2Jira;

boost::asio::io_service myIoService;
// Construct a signal set registered for process termination.
boost::asio::signal_set signals(myIoService);

void handler(
    const boost::system::error_code& error,
    int signal_number)
{
  if (!error)
  {
      switch (signal_number) {
      case SIGTERM:
          LOG4CXX_INFO(loggerMyMain, "SIGTERM reached");
          g_spEmail2Jira->fini();
          return;
          break;
      case SIGINT:
          LOG4CXX_INFO(loggerMyMain, "SIGINT entered");
          g_spEmail2Jira->fini();
          return;
          break;
      case SIGUSR1:
          LOG4CXX_INFO(loggerMyMain, "SIGUSR1 entered");
          break;
      case SIGPIPE:
          LOG4CXX_TRACE(loggerMyMain, "SIGPIPE entered, do nothing. :)");
          break;
      default:
          LOG4CXX_ERROR(loggerMyMain, "unexpected SIGNAL: " << signal_number);
          break;
      }
      signals.async_wait(handler);
  }
}


int main(int argc, char* argv[])
{
    namespace po = boost::program_options;
    po::options_description desc("Allowed options:");
    desc.add_options()
        ("help,h", "produce help message")
        ("logconf,l", po::value<std::string>(), "set the path for the log4cxx config");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    signals.add(SIGINT);
    signals.add(SIGTERM);
    signals.add(SIGUSR1);
    signals.add(SIGPIPE);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }

    if (vm.count("logconf"))
    {
        std::string logconf = vm["logconf"].as<std::string>();
        log4cxx::xml::DOMConfigurator::configure(logconf);
    }
    else
    {
        BasicConfigurator::configure();
    }

    LOG4CXX_INFO(loggerMyMain, "Application has started;");

    signals.async_wait(handler);

    LOG4CXX_INFO(loggerMyMain, "Hallo Henry!");
    g_spEmail2Jira = std::make_shared<tyntec::email2jira::Email2JiraImpl>(myIoService, loggerMyMain->getLogger("Email2JiraImpl"));

    myIoService.post(std::bind(&tyntec::email2jira::Email2JiraImpl::init,g_spEmail2Jira));
    myIoService.run();

    g_spEmail2Jira.reset();

    LOG4CXX_INFO(loggerMyMain, "Application has stopped;");
    return 0;
}
