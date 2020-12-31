cmake_minimum_required(VERSION 3.0.0)
project(ttt VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ttt main.cpp src/ttt.cpp)
include_directories(src)

set(CXX_STANDARD 17)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
