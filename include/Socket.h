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
#include "universal.h"
#include "kcp.h"
#include "Address.h"


class Socket
{
public:
    /*  ikcp output */
    typedef int(OUTPUTFUNC)(const char *buf, int len, struct IKCPCB *kcp, void *user);



    /**
     * @brief 构造一个打开的套接字，并绑定本地端点
     * @param ioc_ IO上下文
     * @param addr_ 本地地址
     */
    Socket(boost::asio::io_context& ioc_,const Address& addr_);

    /**
     * @brief 构造一个打开的套接字，未绑定端口
     * @param ioc IO上下文
     */
    Socket(boost::asio::io_context& ioc_);
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
    int recvfrom(char *buf,int len,Address& peer);
    
    
    
    /**
     * @brief 给一个尚未绑定地址的socket,绑定本地地址
     * @param local 本地地址 
     */
    void bind(Address local);

    /**
     * @brief 设置对端地址
     * @param peer 
     */
    void peer(Address peer);



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
    /**
     * @brief 从网络中接收低级数据（如，原始udp包）并传入ikcp
     */



    void ikcpRecv(Address& peer);
    /* ikcpcb*初始化，并设置 output */
    
    
    
    void ikcpinit();
    /* 封装ikcp_input */



    int ikcpRecvRelay(char* buf, int len);



private:
    boost::mutex lock_;
    ikcpcb* kcp_;                   /* 对应的kcpcb */
    boost::asio::ip::udp::socket socket_;   /* 套接字 */
    Address peer_;                  /* 对端地址*/
    char ikcprecvbuf_[IKCPRECVBUF];  /* kcp接收缓存*/

    ErrorCallback errorcb_;     /* error 回调*/
    SendtoCallback sendcb_;     /* senddata 回调*/
    RecvfromCallback recvcb_;   /* recvfrom 回调*/
};


