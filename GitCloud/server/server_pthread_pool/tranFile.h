#ifndef __TRANFILE_H__
#define __TRANFILE_H__
#include "head.h"
#endif

int sendCycle(int fd,char *p,int sendLen);
int recvCycle(int fd,char *p,int recvLen);
int tranFile(int newFd);

#define FILENAME "file"

typedef struct{
    int dataLen;
    char buf[1000];
}train;
