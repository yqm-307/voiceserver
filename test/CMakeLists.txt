cmake_minimum_required(VERSION 2.6)
project(sockettest CXX C)

include_directories(../include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
#aux_source_directory(../src SRC)

set(My_SRC
    ../src/kcp.c
    ../src/Logger.cpp
    ../src/Socket.cpp
)
set(My_LIB
    -lboost_regex
    -lboost_thread
    -lpthread
)

add_executable(server 
    echoServer.cpp
    ../src/kcp.c
    ../src/Logger.cpp
    ../src/Socket.cpp
)
target_link_libraries(server ${My_LIB})


add_executable(client
    echoClient.cpp
    ../src/kcp.c
    ../src/Logger.cpp
    ../src/Socket.cpp
)
target_link_libraries(client ${My_LIB})
