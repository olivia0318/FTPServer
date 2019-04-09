#include "func.h"

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
