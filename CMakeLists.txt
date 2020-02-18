cmake_minimum_required(VERSION 3.15)
project(event)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(event include/event.h)