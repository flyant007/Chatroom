#ifndef CLIENT_H
#define CLIENT_H
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //AF_INET
class Client
{
public:
    //构造函数
    Client() = default;

    //设置套接字域的地址
    void SetAddr();

    //初始化一个Server
    void Init();

    //获得套接字
    int GetSockfd() {return sockfd;}

    //关闭socket连接
    int Close() {close(sockfd);}

private:

    //套接字
    int sockfd;

    //服务器端套接字域的地址
    struct sockaddr_in server_addr;

};

#endif // CLIENT_H
