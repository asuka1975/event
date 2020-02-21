cmake_minimum_required(VERSION 3.15)
project(event)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fconcepts")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(event include/event.h include/property.h Google_tests/event_test.cpp)

add_subdirectory(Google_tests)