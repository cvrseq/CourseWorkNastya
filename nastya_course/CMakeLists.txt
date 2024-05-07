cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 26)

add_executable(untitled library.cpp
        library.h
        main.cpp)
