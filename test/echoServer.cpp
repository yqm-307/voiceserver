#include "../include/Socket.h"
#include "../include/Address.h"
#include "../include/Logger.h"

class server
{    
public:
    server(boost::asio::io_context&ioc,int port)
        :endpoint(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),13000)),
        socket(ioc,endpoint)
    {
        start();
    }   

    void start()
    {
        Address client;
        while(1)
        {
            socket.update();
            char buf[1024];
            memset(buf,'\0',1024);
            socket.recvfrom(buf,1024,client);
            printf("接收：%s\n",buf);
            socket.sendto(buf,strlen(buf),client);
            printf("回送\n");
        }
    }
private:
    Address endpoint;
    Socket socket;
};

int main()
{
    udp::Logger::GetInstance("./Server.log");
    boost::asio::io_context ioc;
    server server(ioc,13000);
}