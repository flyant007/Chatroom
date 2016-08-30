#ifndef SERVER_H
#define SERVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //AF_INET
class Server
{
public:
    //构造函数
    Server();

    //设置套接字域的地址
    void SetAddr();

    //初始化一个Server
    void Init();

private:
    //套接字
    int socket_fd;

    //套接字域的地址
    struct sockaddr_in addr;

};
#endif // SERVER_H
