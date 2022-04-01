#pragma once
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>


#define BUFSIZE 1024

namespace def
{

template<class T>
using SharedPtr = boost::shared_ptr<T>; 

}