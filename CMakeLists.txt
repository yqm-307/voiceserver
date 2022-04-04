cmake_minimum_required(VERSION 2.6) 
project(voiceserver CXX C)

set(CMAKE_CXX_FLAGS
    "-g
    -std=c++11
    -Wall"
)

#头文件目录
include_directories(include)

#源文件集合 SOURCES
file(GLOB SOURCES ./src/*.cpp)

add_subdirectory(test)
