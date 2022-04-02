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
     * @brief 服务端使用Socket
     * @param ioc_ IO上下文
     * @param addr_ 服务器地址
     */
    Socket(boost::asio::io_context& ioc_,const Address& addr_);

    /**
     * @brief 客户端使用Socket，使用时无需绑定本地地址
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
     * @return int 接收数据长度
     */
    int recvfrom(const char *buf,int len,Address peer_);

    /* 设置错误时回调 */
    void setErrorCallback(ErrorCallback& cb)
    { errorcb_ = cb; }

    /* 设置发送数据时回调 */
    void setSendtoCallback(SendtoCallback& cb)
    { sendcb_ = cb; }
    
private:
    boost::asio::ip::udp::socket socket_;   /* 套接字 */
    static ikcpcb* kcp_;   /* 对应的kcpcb */
    OUTPUTFUNC* output_;    /* kcpcb的数据发送调用，kcp本身0系统调用，需要用户传递系统调用 */
    ErrorCallback errorcb_; /* error 回调*/
    SendtoCallback sendcb_; /* senddata 回调*/
};
