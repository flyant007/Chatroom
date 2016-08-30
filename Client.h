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

    //设置套接字地址
    void SetAddr();

    //初始化一个client
    void Init();

private:
    //套接字
    int socket_fd;

    //套接字名字
    struct sockaddr_in addr;

};

#endif // CLIENT_H
