#include "Common.h"
#include "Client.h"
#include <arpa/inet.h> //包含inet_addr(SERVER_IP)

//设置套接字地址
void Client::SetAddr()
{
    //服务器端套接字域
    server_addr.sin_family = AF_INET;

    //服务器端端口号
    server_addr.sin_port = SERVER_PORT;

    //服务器端IP
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

}

void Client::Init()
{
    //socket系统调用创建一个套接字，并返回一个文件描述符
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //设置服务器端地址
    SetAddr();

    //请求连接
    //套接字sockfd将连接到server_addr指定的服务器套接字上
    //如果不能建立连接，connect()会阻塞一段不确定的超时时间
    //如果连接被信号中断，信号被处理后，connect会返回失败，但是连接不会被放弃，移异步的方式继续建立
    if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
        perror("Connect error");
}
