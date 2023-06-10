cmake_minimum_required(VERSION 3.22)
project(untitled2)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-O3)

add_executable(untitled2 main.cpp GA.cpp individual.cpp random.cpp graph.cpp)
