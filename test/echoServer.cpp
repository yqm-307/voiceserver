#include "../include/Socket.h"
#include "../include/Address.h"
#include "../include/Logger.h"

class server
{    
public:
    server(boost::asio::io_context&ioc)
        :socket(ioc),
        endpoint(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),13000))
    {
        start();
    }   

    void start()
    {
        socket.bind(endpoint);
        while(1)
        {
            Address client;
            char buf[1024];
            socket.recvfrom(buf,1024,client);
            printf("接收：%s\n",buf);
            //socket.sendto(buf,strlen(buf),client);
        }
    }
private:
    Socket socket;
    Address endpoint;
};

int main()
{
    udp::Logger::GetInstance("./Server.log");
    boost::asio::io_context ioc;
    server server(ioc);
}