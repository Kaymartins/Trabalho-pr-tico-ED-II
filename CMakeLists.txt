cmake_minimum_required(VERSION 3.20)
project(ED_II)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(headers)


add_executable(ED_II
        "projeto/src/Main.cpp")
