#include "include/Socket.h"
#include "include/Logger.h"
/**
 * @brief 提供给ikcp数据发送的系统调用
 * 
 * @param ioc_ IO上下文
 * @param addr_ Socket本地地址
 */
Socket::Socket(boost::asio::io_context& ioc_,const Address& addr_)
    :socket_(ioc_)
{
    kcp_ = ikcp_create(1,this);
    socket_.async_connect(addr_(),errorcb_);

    output_ = [](const char*buf,int len,
                ikcpcb* ikcp,void*user)->int
    {
        Socket* socket = reinterpret_cast<Socket*>(user);
        socket->socket_.async_send(boost::asio::buffer(buf,len),socket->sendcb_);

    };
    ikcp_setoutput(kcp_,output_);
}


int Socket::sendto(const char* buf,int len,Address peer)
{
    int n = ikcp_send(kcp_,buf,len);
    if(n < len) 
        WARN("%d bytes have been sent, but %d bytes remain unsent",n,len-n);
    return n;
}

int Socket::recvfrom(char* recvbuf,int len,Address peer)
{
    assert(recvcb_);
    int n = socket_.async_receive_from(boost::asio::buffer(recvbuf,len),const_cast<Address&>(peer()),recvcb_);
    if(n<len)
        WARN("%d bytes have been recv, but %d bytes remain unrecv",n,len-n);
    return n;
}

