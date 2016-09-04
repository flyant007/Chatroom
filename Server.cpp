#include "Common.h"
#include "Server.h"
#include <arpa/inet.h> ////包含inet_addr(SERVER_IP)

using namespace std;

//服务器端类构造函数
Server::Server()
{
    //初始化套接字域的地址
    //设置套接字域：套接字通信中使用的网络介质
    server_addr.sin_family = AF_INET;

    //设置套接字的ip地址
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    //设置套接字的端口地址
    server_addr.sin_port = htons(SERVER_PORT);

    //初始化监听socket
    server_sockfd = 0;

    epfd = 0;
}


void Server::Init()
{
    char output;
    int result;
    fd_set readfds, testfds;
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
    std::cout << "server fd: " << server_sockfd << std::endl;


    //设置套接字地址
    SetAddr();

    //命名套接字，将创建的AF_INET型套接字server_sockfd关联到一个ip端口号
    if (bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        perror("Bind error");

    //创建套接字队列：服务器创建该队列用来接收进入的连接
    if(listen(server_sockfd, 5) == -1)
        perror("Listen error");

//    signal(SIGCHLD, SIG_IGN);
    //将readfds初始化为空集合
    FD_ZERO(&readfds);

    //在readfds种设置文件描述符server_sockfd
    FD_SET(server_sockfd, &readfds);

    while(1)
    {
        testfds = readfds;
        int fd;
        int nread;
        std::cout << "server waiting..." << std::endl;

        //当读写和错误文件描述符就绪，返回状态发生变化的描述符总数，失败时-1
        //select返回时，描述符集合将被修改以指示哪些描述符正处于可读，可写或有错误的状态。
        //或者超时返回0，此处0，不会发生超时
        result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0);
        std::cout << "result = " << result << std::endl;
        if(result < 1)
        {
            perror("server select:");
            exit(1);
        }

        //检查每个描述符，以发现活动发生在哪个描述符上
        for(fd = 0; fd < FD_SETSIZE; fd++)
        {
            if(FD_ISSET(fd, &testfds))//fd是testfds中，则返回非零
            {
                if(fd == server_sockfd) //如果活动发生在坚挺套接字上，则时新的连接请求
                {
                    //等待客户端建立对该套接字的连接
                    //只有当有排在套接字队列里的第一个未处理的连接程序试图连接到server_sockfd时才返回一个新的套接字client_sockfd
                    //没有的话accpet()将阻塞。可以对套接字文件描述符server_sockfd设置O_NONBLOCK来改为非阻塞
                    //client_sockfd用于与客户端通信，
                    //client_addr：存放连接客户的地址，可以为空指针
                    //sizeof(client_addr)：指定客户端结构的长度，如果超过该长度被截断，调用返回时，被设置为连接客户地址结构的实际长度
                    int client_len;
                    client_len = sizeof(client_addr);
                    client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_addr, (socklen_t *) &client_len);
                    if(client_sockfd == -1)
                        perror("Accpet error");

                    //将新的client_sockfd添加到readfds描述符中
                    FD_SET(client_len, &readfds);
                    std::cout << "adding client on fd " << client_sockfd << std::endl;
                }
                else
                {
                    ioctl(fd, FIONREAD, &nread);
                    if(nread == 0)
                    {
                        close(fd);
                        FD_CLR(fd, &readfds);
                        std::cout << "removing client on fd " << fd << std::endl;
                    }
                    else
                    {
                        std::cout << "serving client on fd " << fd << std::endl;
                        read(fd, &output, 1);
                        std::cout << output << std::endl;
                        output++;
                        write(fd, &output, 1);
                    }
                }
            }
        }


    }



}
