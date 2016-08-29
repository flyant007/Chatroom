#include "Common.h"
#include "Client.h"

//设置套接字地址
void Client::SetAddr()
{
    //
    addr.sin_family = AF_INET;

    //设置端口号
    addr.sin_port = SERVER_PORT;

    //设置IP
    addr.sin_addr.s_addr = htonl()

}

void Client::Init()
{
    //设置
    //socket系统调用创建一个套接字，并返回一个文件描述符
    fd = socket()
}
