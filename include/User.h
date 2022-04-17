#pragma once
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
//class Address;


class User
{
public:
    User();
    ~User();

    size_t send(const char* date,size_t len);
    size_t recv(char* buf,size_t buflen);

    int uid()
    {return uid_;}
    int room()
    {return roomid_;}
private:
    int uid_;   //唯一uid
    //char* token;  //未使用
    int roomid_;    //所属房间
    char* recvbuf_; //接收区
    char* sendbuf_; //发送区
    size_t bufsize;
    Address clientaddr;    //地址
};