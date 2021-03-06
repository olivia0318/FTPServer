#include "tranFile.h"
//循环发送
//防止发送端发包速度和接收端接包速度不匹配，使协议失效
//发送的更快时，缓冲区会先填满，使得下次发送时，send发送的数据不能被正常接收完
//接受的更快时，缓冲区有多少都直接会被recv读出来，接受的量和设计好的量不匹配
//
int sendCycle(int fd,char *p,int sendLen)
{
    int total=0;
    int ret;
    while(total<sendLen)
    {
        ret=send(fd,p+total,sendLen-total,0);
        total+=ret;

    }
    return 0;
}

int recvCycle(int fd,char *p,int recvLen)
{
    int total=0;
    int ret;
    while(total<recvLen)
    {
        ret=recv(fd,p+total,recvLen-total,0);
        total+=ret;

    }
    return 0;
}
