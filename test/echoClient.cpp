#include "../include/Socket.h"
#include <boost/asio.hpp>
#include <iostream>
#include "../include/Logger.h"

class KcpClient
{
public:
    KcpClient(boost::asio::io_context& ioc,Address&& peer)
        :socket_(ioc),
        peer_(peer)
    {
        socket_.peer(peer);
        start();
    }   
    KcpClient(boost::asio::io_context& ioc,Address& peer)
        :socket_(ioc),
        peer_(peer)
    {
        socket_.peer(peer);
        start();
    }  

    void start()
    {
        while (1)
        {
            socket_.update();
            Address client;
            char buf[1024];
            memset(buf,'\0',1024);
            printf("输入:");
            std::cin>>buf;
            socket_.sendto(buf,strlen(buf),peer_);
            memset(buf,'\0',1024);
            socket_.recvfrom(buf,1024,peer_);
            printf("接收:%s\n",buf);
        }
        
    }
private:
    Socket socket_; //套接字
    Address peer_; //本地地址    
};

int main()
{
    udp::Logger::GetInstance("./Client.log");
    boost::asio::io_context ioc;
    KcpClient(ioc,Address("127.0.0.1",13000));
}