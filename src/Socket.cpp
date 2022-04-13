#include "../include/Socket.h"
#include "../include/Logger.h"


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
    assert(Soutput_!=nullptr);
    ikcp_setoutput(kcp_,Soutput_);
    Soutput_ = [](const char*buf,int len,ikcpcb* ikcp,void*user)->int
    {
        printf("b1\n");
        Socket* socket = reinterpret_cast<Socket*>(user);
        return socket->socket_.send_to(boost::asio::buffer(buf,len),socket->peer_());
    };
    kcp_->writelog = [](const char* log,ikcpcb*kcp,void* user)
    {
        INFO("log");
    };
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
    INFO("Receives %d bytes from the network",n);
    int nbytes = ikcp_input(kcp_,ikcprecvbuf_,n);
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
    socket_.open(boost::asio::ip::udp::v4());
    ikcpinit();
}

Socket::~Socket()
{
    ikcp_release(kcp_);
    socket_.close();
}

int Socket::sendto(const char* buf,int len,Address peer)
{
    update();
    this->peer(peer);
    int n = ikcp_send(kcp_,buf,len);
    if(n < 0) 
        WARN("ikcp_send: error , errcode %d",n);
    //发送完当即flush
    //todo input、output
    ikcp_flush(kcp_);
    return n;

}

void Socket::recvfrom(char* recvbuf,int len,Address& peer)
{
    update();
    ikcpRecv(peer); //传入kcp当前数据
    int n = ikcp_recv(kcp_,recvbuf,len);
    if(n == -1)//接收区缓存无数据
        INFO("ikcp_recv: the receiving buffer has no data");
    
    else if(n>=0)
        INFO("recv %dbytes",n);
    else
        ERROR("ikcp_recv: error , errcode: %d",n);
}

void Socket::bind(Address local)
{
    socket_.bind(local());
}

void Socket::peer(Address peer)
{
    boost::unique_lock<boost::mutex> lock(lock_);
    peer_ = peer;
}
