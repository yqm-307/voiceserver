#pragma once
/*
    房间属性、基本操作
*/
#include <vector>
#include "Socket.h"
#include "User.h"
#include "universal.h"  

class Room
{
public:
    typedef std::vector<User> UserList;

    
private:
    int roomid_;
    static const int MAXSIZE = ROOM_MAX_SIZE; 
    UserList users_;    //用户


};