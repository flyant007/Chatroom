#ifndef SERVER_H
#define SERVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //AF_INET
#include <stdio.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

//服务端类，用来处理客户请求
class Server
{
public:
    //构造函数
    Server() = default;

    //设置套接字域的地址
    void SetAddr();

    //初始化一个Server
    void Init();

private:
    //服务器端套接字
    int server_sockfd;

    //接收的客户端套接字
    int client_sockfd;

    //服务器端套接字域的地址
    struct sockaddr_in server_addr;

    //客户端套接字域的地址
    struct sockaddr_in client_addr;

};
#endif // SERVER_H
