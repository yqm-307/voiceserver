#pragma once
/**
 * @file Socket.h
 * @author yqm-307 (979336542@qq.com)
 * @brief 封装boost的udpsocket、ikcp；预计服务器压力不打，先采用但ikcpcb对应一个socket
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 */
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <universal.h>
#include <kcp.h>
#include <Address.h>
#include <include/universal.h>


class Socket
{
public:
    /*  ikcp output */
    typedef int(OUTPUTFUNC)(const char *buf, int len, struct IKCPCB *kcp, void *user);

    /**
     * @brief 构造一个以打开套接字，并绑定本地端点
     * @param ioc_ IO上下文
     * @param addr_ 本地地址
     */
    Socket(boost::asio::io_context& ioc_,const Address& addr_);

    /**
     * @brief 构造一个未打开套接字，需要open打开
     * @param ioc IO上下文
     */
    Socket(boost::asio::io_context& ioc_);

    /* 拷贝构造 */
    Socket(const Socket& );
    
    /* 析构 */
    ~Socket();

    /**
     * @brief 向对端发送len字节
     * 
     * @param buf 待发送数据
     * @param len 待发送数据长度
     * @param peer_ 对端地址
     * @return int 发送成功字节数量
     */
    int sendto(const char *buf,int len,Address peer_);
    
    /**
     * @brief 接收来自peer的数据
     * 
     * @param buf 接受缓冲区
     * @param len 缓冲区长度
     * @param peer_ 对端地址
     */
    void recvfrom(char *buf,int len,Address& peer);

    void bind(Address local);
    /**
     * @brief 从网络中接收低级数据（如，原始udp包）并传入ikcp
     */
    void ikcpRecv(Address& peer);
    /**
     * @brief 更新ikcpcb状态
     */
    void update(int current=INT32_MAX);
    /* set errorcallback */
    void setErrorCallback(ErrorCallback& cb)
    { errorcb_ = cb; }

    /* set sendcallback */
    void setSendtoCallback(SendtoCallback& cb)
    { sendcb_ = cb; }
protected:
    /* ikcpcb*初始化，并设置 output */
    void ikcpinit();
    /* 封装ikcp_input */
    int ikcpRecvRelay(char* buf, int len);
private:
    
    ikcpcb* kcp_;                   /* 对应的kcpcb */
    boost::asio::ip::udp::socket socket_;   /* 套接字 */
    boost::mutex lock_;
    static OUTPUTFUNC* output_;     /* kcpcb的数据发送调用，kcp本身0系统调用，需要用户传递系统调用 */
    char ikcprecvbuf_[IKCPRECVBUF];  /* kcp接收缓存*/

    ErrorCallback errorcb_;     /* error 回调*/
    SendtoCallback sendcb_;     /* senddata 回调*/
    RecvfromCallback recvcb_;   /* recvfrom 回调*/
};


/**
 * @brief ikcp_send调用output_发送数据
 */
Socket::OUTPUTFUNC* Socket::output_ = [](const char*buf,int len,
            ikcpcb* ikcp,void*user)->int
{
    Socket* socket = reinterpret_cast<Socket*>(user);
    socket->socket_.async_send(boost::asio::buffer(buf,len),socket->sendcb_);
};


