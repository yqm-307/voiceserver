cmake_minimum_required(VERSION 2.6) 
project(server CXX)

include_directories(../include)



add_executable(udpserver 
    ../src/kcp.c
    UdpSocketTest.cpp 
    ../src/Logger.cpp
    ../src/Socket.cpp
)
target_link_libraries(udpserver -lboost_regex -lboost_thread -lpthread)