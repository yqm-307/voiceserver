#include "../include/Acceptor.h"

using boost::asio::ip::udp;

Acceptor::Acceptor(boost::asio::io_context& ioc,int port)
    :ioc_(ioc),
    localaddress_(udp::endpoint(boost::asio::ip::udp::v4(),port)),
    listen_(ioc_,localaddress_),
    listenthread_(Acceptor::listen)
{
    
}


void Acceptor::listen()
{
    while(true)
    {
    }
}