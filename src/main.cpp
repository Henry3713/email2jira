#include <iostream> 
#include <string>

// include log4cxx header files.
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/xml/domconfigurator.h>
#include <log4cxx/helpers/exception.h>

#include <boost/program_options.hpp>
#include <boost/asio.hpp>

using namespace log4cxx;
using namespace log4cxx::helpers;

LoggerPtr loggerMyMain(Logger::getLogger( "main"));

using WorkPtr = std::shared_ptr<boost::asio::io_service::work>;

WorkPtr g_spWork;

void handler(
    const boost::system::error_code& error,
    int signal_number)
{
  if (!error)
  {
      switch (signal_number) {
      case SIGTERM:
          LOG4CXX_INFO(loggerMyMain, "SIGTERM reached;");
          g_spWork.reset();
          break;
      case SIGINT:
          LOG4CXX_INFO(loggerMyMain, "SIGINT entered;");
          g_spWork.reset();
          break;
      default:
          LOG4CXX_INFO(loggerMyMain, "unexpected SIGNAL: " << signal_number);
          break;
      }
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

    boost::asio::io_service myIoService;
    // Construct a signal set registered for process termination.
    boost::asio::signal_set signals(myIoService);


    signals.add(SIGINT);
    signals.add(SIGTERM);

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
    g_spWork = std::make_shared<boost::asio::io_service::work>(myIoService);
    myIoService.run();
    LOG4CXX_INFO(loggerMyMain, "Application has stopped;");
    return 0;
}
