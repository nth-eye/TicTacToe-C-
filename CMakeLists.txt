cmake_minimum_required(VERSION 3.0.0)
project(ttt VERSION 0.1.0)

include_directories(inc)

add_executable(ttt main.cpp src/ttt.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wno-parentheses -O3")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
