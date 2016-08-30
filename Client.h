#ifndef CLIENT_H
#define CLIENT_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //AF_INET
class Client
{
public:
    //构造函数
    Client();

    //设置套接字域的地址
    void SetAddr();

    //初始化一个Server
    void Init();

private:

    //套接字
    int sockfd;

    //服务器端套接字域的地址
    struct sockaddr_in server_addr;

};

#endif // CLIENT_H
