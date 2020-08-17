cmake_minimum_required (VERSION 3.10.2)
project(email2jira)

find_package(Boost 1.65.1 COMPONENTS program_options system)

find_library(LOG4CXX_LIBRARY log4cxx)

set(${CMAKE_PROJECT_NAME}_SOURCE ./src/main.cpp
                                   ./src/Email2JiraImpl.cpp)

add_executable (${CMAKE_PROJECT_NAME} ${${CMAKE_PROJECT_NAME}_SOURCE})

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${LOG4CXX_LIBRARY} ${Boost_LIBRARIES} pthread)
