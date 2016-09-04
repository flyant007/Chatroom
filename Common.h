#ifndef COMMON_H
#define COMMON_H
#include <errno.h>//错误处理变量errno
#include <stdio.h> //包含perror()
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <string.h>

#include <iostream>

//默认服务器端口号
#define SERVER_PORT 8000

//默认服务器端ip地址
#define SERVER_IP   "127.0.0.1"

//epoll支持的最大句柄数
#define EPOLL_SIZE 5000

//缓冲区大小65535
#define BUF_SIZE 0xFFFF

// 新用户登录后的欢迎信息
#define SERVER_WELCOME "Welcome you join to the chat room! Your chat ID is: Client #%d"

// 其他用户收到消息的前缀
#define SERVER_MESSAGE "ClientID %d say >> %s"

// 退出系统
#define EXIT "EXIT"

// 提醒你是聊天室中唯一的客户
#define CAUTION "There is only one int the char room!"

//将文件描述符fd添加到epollfd标示的内盒事件表中，并注册EPOLLIN和EPOLLET事件，
//EPOLLIN是数据可读事件；EPOOLET表明是ET工作方式，最后将文件描述符设置位非阻塞方式
/**
  * 功能：注册新的fd到epollfd中
  * @param epollfd: epoll句柄
  * @param fd: 文件描述符
  * @param enable_et : enable_et = true,
     采用epoll的ET工 作方式；否则采用LT工作方式
**/
static void addfd(int epollfd, int fd, bool enable_et)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(enable_et)
    {
        ev.events = EPOLLIN | EPOLLET;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    //设置socket为nonblocking模式，执行完就转向吓一跳指令，不管函数有没有返回
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)|O_NONBLOCK);
    printf("fd added to epoll!\n\n");
}

#endif // COMMON_H
