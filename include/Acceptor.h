#pragma once
/*
    连接
*/
#include "universal.h"
#include "Socket.h"

class Acceptor
{
public:

    typedef boost::array<char,BUFSIZE> BUFFER;
    typedef boost::function<void(ConnectionPtr&,BUFFER&)> OnConnectCallback;
    /*
    * @brief Acceptor构造函数
    * @param ioc io上下文
    * @param addr 服务器本地地址    udp::v4()
    * @return null
    */
    Acceptor(boost::asio::io_context& ioc,int port);
    ~Acceptor();
    
    /*  
    * @brief 启动监听套接字，如果有新的连接，就要为新连接创建一个User对象
    */
    void listen();
    

private:
    //io上下文，不由Acceptor管理
    boost::asio::io_context& ioc_;
    //本地地址
    Address localaddress_;
    //监听socket
    Socket listen_;
    //新连接时回调
    boost::thread listenthread_;
};