#pragma once
/**
 * @brief 为了搭配Socket的ip、port封装
 * 
 */

#include <boost/asio.hpp>

class Address
{
public:
    /**
     * @brief Address的构造，右值
     */
    Address(const std::string&& ip,int port)
        :endpoint_(boost::asio::ip::address::from_string(ip),port){}
    /**
     * @brief Address的构造函数，左值
     */
    Address(std::string& ip,int port)
        :endpoint_(boost::asio::ip::address::from_string(ip),port){}
    /**
     * @brief 拷贝构造函数
     * @param rhs 
     */
    Address(const Address& rhs)
    { this->endpoint_=rhs(); }
    /**
     * @brief 拷贝赋值运算符
     * @param rhs 
     * @return Address& 
     */
    Address& operator=(Address& rhs)
    {   
        endpoint_ = rhs(); 
        return *this;
    }

    /**
     * @brief 对endpoint的访问，常函数
     * @return endpoint的常引用 
     */
    const boost::asio::ip::udp::endpoint& operator()() const
    {
        return endpoint_;
    }
private:
    boost::asio::ip::udp::endpoint endpoint_;
};
