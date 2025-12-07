cmake_minimum_required(VERSION 3.20)
project(SparseLA)

set (CMAKE_CXX_STANDARD 20)

include_directories(src nanoblas/src)

add_executable(main src/main.cpp)