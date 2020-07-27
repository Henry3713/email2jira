#include <iostream> 
#include <string>

// include log4cxx header files.
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/xml/domconfigurator.h>
#include <log4cxx/helpers/exception.h>

#include <boost/program_options.hpp>

using namespace log4cxx;
using namespace log4cxx::helpers;

LoggerPtr loggerMyMain(Logger::getLogger( "main"));

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
    std::cout << "Hallo Ralf!" << std::endl;
    LOG4CXX_INFO(loggerMyMain, "Hallo Ralf!");
    LOG4CXX_INFO(loggerMyMain, "Application has stopped;");
    return 0;
}
