cmake_minimum_required(VERSION 3.23)
project(MPS_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(MPS_Project
        src/Main.cpp
        src/Main.h)
