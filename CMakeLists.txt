cmake_minimum_required(VERSION 3.23)
project(MPS_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(MPS_Project
        src/Parser.cpp
        src/Parser.h
        src/Pixel.cpp
        src/Pixel.h
        src/LocalPixel.cpp
        src/LocalPixel.h
        src/GlobalPixel.cpp
        src/GlobalPixel.h src/Node.cpp src/Node.h src/Functions.cpp src/Functions.h src/test.cpp)
