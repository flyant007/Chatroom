#include "Common.h"
#include "Server.h"

//设置套接字域的地址
void Server::SetAddr()
{
    //设置套接字域：套接字通信中使用的网络介质
    addr.sin_family = AF_INET;

    //设置套接字的ip地址
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    //设置套接字的端口地址
    addr.sin_port = SERVER_PORT

}

void Server::Init()
{
    //创建套接字
    //套接字域：套接字通信中使用的网络介质
    //AF_INET：internet网络，底层是网际协议，地址是ip
    //AF_UNIX：UNIX文件系统域，底层是文件I/O协议，地址是文件名
    //套接字类型：通信方式
    //SOCK_STREAM：流套接字，有序、可靠、双向， TCP/IP
    //SOCK_DGRAM：数据报套接字，不建立和维持一个连接，无序、不可靠，速度快、占资源小，UDP/IP
    //套接字协议
    //一般默认0
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
}
