#include "../include/Acceptor.h"

using boost::asio::ip::udp;
Acceptor::Acceptor(boost::asio::io_context& ioc,boost::asio::ip::address& localhost,int port)
    :ioc_(ioc),
    localaddress_(localhost,port),
    listenfd_(ioc_,localaddress_),
    listenthread_(Acceptor::listen)
{
    
}

void Acceptor::listen()
{
    while(true)
    {
    }
}