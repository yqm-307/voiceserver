#pragma once
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>




namespace def
{

template<class T>
using SharedPtr = boost::shared_ptr<T>; 

typedef boost::function<void(const boost::system::error_code&)> ErrorCallback;
typedef boost::function<void(const boost::system::error_code&,size_t)> BufferCallback;
typedef BufferCallback SendtoCallback;
typedef BufferCallback RecvfromCallback;

#define BUFSIZE 1024
#define ErrorCallback def::ErrorCallback
#define SendtoCallback def::SendtoCallback
#define ConnectionPtr def::SharedPtr<boost::asio::ip::udp::socket>
#define RecvfromCallback def::RecvfromCallback

}




