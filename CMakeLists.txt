cmake_minimum_required(VERSION 3.0.0)
project(ttt VERSION 0.1.0)

add_library(libttt INTERFACE)
target_include_directories(libttt INTERFACE inc)
target_compile_features(libttt INTERFACE cxx_std_20)

add_executable(ttt main.cpp)
target_compile_features(ttt PRIVATE cxx_std_20)
target_link_libraries(ttt PRIVATE libttt)
