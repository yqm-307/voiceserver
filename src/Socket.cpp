#include "include/Socket.h"
#include "include/Logger.h"


void InitSendtoCalback(const boost::system::error_code& err,size_t len)
{
    if(err)
    {
        ERROR("ikcpcb->output_ : An error :%s",err.message());
    }
    INFO("boost::asio::socket::async_send_to(const char* buf,int len) send %d byte",len);
}

void InitRecvfromCallback(const boost::system::error_code&err,size_t len)
{
        if(err)
    {
        ERROR("ikcpcb->output_ : An error :%s",err.message());
    }
    INFO("boost::asio::socket::async_recv_from(const char* buf,int len) recv %d byte",len);
}

void InitErrorCallback(const boost::system::error_code&err)
{
    if(err)
        ERROR("%s",err.message());
    else
        INFO("ErrorCallback called but with no exception");
}

void InitIkcpRecvCallback(const boost::system::error_code&& err,size_t len)
{

}

void Socket::ikcpinit()
{
    //ikcp 资源初始化
    kcp_ = ikcp_create(1,this);
    assert(output_!=nullptr);
    ikcp_setoutput(kcp_,output_);
}

int Socket::ikcpRecvRelay(char* buf, int len)
{
    int n = ikcp_input(kcp_,buf,len);
    if(n<0)
        ERROR("Socket::ikcpRecvRelay ikcp_input errcode:%d",n);
    return n;
}

void Socket::ikcpRecv(Address& peer)
{
    boost::asio::ip::udp::endpoint clientendpoint;
    size_t n = socket_.receive_from(boost::asio::buffer(ikcprecvbuf_,IKCPRECVBUF),peer());
    int nbytes = ikcp_input(kcp_,ikcprecvbuf_,n);
    assert(nbytes == n);
    INFO("Receives %d bytes from the network",nbytes);
}

void Socket::update(int current)
{
    ikcp_update(kcp_,current);
}


Socket::Socket(boost::asio::io_context& ioc_,const Address& addr_)
    :socket_(ioc_,addr_())
{
    ikcpinit();
} 

Socket::Socket(boost::asio::io_context& ioc)
    :socket_(ioc)
{
    ikcpinit();
}

int Socket::sendto(const char* buf,int len,Address peer)
{
    update();
    int n = ikcp_send(kcp_,buf,len);
    if(n < len) 
        WARN("%d bytes have been sent, but %d bytes remain unsent",n,len-n);
    return n;
}

void Socket::recvfrom(char* recvbuf,int len,Address& peer)
{
    update();
    ikcpRecv(peer); //传入kcp当前数据
    ikcp_recv(kcp_,recvbuf,len);
}

void Socket::bind(Address local)
{
    socket_.bind(local());
}
