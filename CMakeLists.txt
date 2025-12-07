cmake_minimum_required(VERSION 3.20)
project(SparseLA)

set (CMAKE_CXX_STANDARD 20)

include_directories(src nanoblas/src)

find_package(Eigen3 REQUIRED)
add_executable(jacobi src/jacobi.cpp)
target_link_libraries(jacobi PRIVATE Eigen3::Eigen)