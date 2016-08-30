#include "Common.h"
#include "Server.h"



//设置套接字域的地址
void Server::SetAddr()
{
    //设置套接字域：套接字通信中使用的网络介质
    server_addr.sin_family = AF_INET;

    //设置套接字的ip地址
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    //设置套接字的端口地址
    server_addr.sin_port = SERVER_PORT;

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
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //设置套接字地址
    SetAddr();

    //命名套接字，将创建的AF_INET型套接字server_sockfd关联到一个ip端口号
    if (bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        perror("Bind error");

    //创建套接字队列：服务器创建该队列用来接收进入的连接
    if(listen(server_sockfd, 5) == -1)
        perror("Listen error");

    while(1)
    {
        std::cout << "server waiting..." << endl;
        //等待客户端建立对该套接字的连接
        //只有当有排在套接字队列里的第一个未处理的连接程序试图连接到server_sockfd时才返回一个新的套接字client_sockfd
        //没有的话accpet()将阻塞。可以对套接字文件描述符server_sockfd设置O_NONBLOCK来改为非阻塞
        //client_sockfd用于与客户端通信，
        //client_addr：存放连接客户的地址，可以为空指针
        //sizeof(client_addr)：指定客户端结构的长度，如果超过该长度被截断，调用返回时，被设置为连接客户地址结构的实际长度
        //
        client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_addr, (size_t *) &(sizeof(client_addr)));
        if(client_sockfd == -1)
            perror("Accpet error");
    }



}
