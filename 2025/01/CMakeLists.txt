cmake_minimum_required(VERSION 3.13)
project(aoc_01)
set(CMAKE_CXX_STANDARD 20)

configure_file(input.txt input.txt COPYONLY)

add_executable(aoc_01
    main.cpp
)