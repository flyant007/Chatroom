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
    //无参构造函数
    Server();

    //初始化一个Server端设置
    void Init();

    //关闭服务
    void Close();

    //启动服务端
    void Start();

private:

    //广播消息给所有客户端
    int SendBroadcastMessage(int clientfd);

    //服务器端套接字,用来监听
    int server_sockfd;

    //接收的客户端套接字列表
    list<int> client_sockfds_list;

    //服务器端套接字域的地址
    struct sockaddr_in server_addr;

    //epoll_create创建后的返回值
    int epfd;

};
#endif // SERVER_H
