cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 14)

project(BoilerPlate)

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK=1)
SET(Boost_USE_STATIC_LIBS ON)
set(BoilerPlate_VERSION_MAJOR 0)
set(BoilerPlate_VERSION_MINOR 1)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

set(CMAKE_BUILD_TYPE Debug)

set(Boost_USE_STATIC_LIBRARIES ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED)

include_directories(${PROJECT_BINARY_DIR})
include_directories(${LIBRARY_OUTPUT_PATH})
include_directories("${PROJECT_BINARY_DIR}/Logger")
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

set(BOOST_LIBS "-lpthread -lboost_chrono -lboost_thread -lboost_system -lboost_program_options -lboost_date_time -lboost_locale -lboost_regex -lboost_log_setup -lboost_log")

add_subdirectory("Logger")
set(EXTRA_LIBS ${EXTRA_LIBS} Logger)

add_executable(BoilerPlate main.cpp)
target_link_libraries(BoilerPlate ${EXTRA_LIBS} ${BOOST_LIBS})