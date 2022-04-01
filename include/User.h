#pragma once
#include <iostream>
#include <boost/array.hpp>

class User
{
public:
    User();
private:
    int uid_;   //唯一uid
    //char* token;  //未使用
    int roomid_;    //所属房间
    char* recvbuf_; //接收区
    char* sendbuf_; //发送区
    size_t bufsize;

};