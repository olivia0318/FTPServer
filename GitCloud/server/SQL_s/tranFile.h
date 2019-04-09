#ifndef __TRANFILE_H__
#define __TRANFILE_H__
#include "head.h"

int sendCycle(int fd,char *p,int sendLen);
int recvCycle(int fd,char *p,int recvLen);
int tranFile(int newFd,char *FILENAME);

//#define FILENAME "file"

typedef struct{
    int dataLen;
    int atflag;
    char buf[1024];
}train;


#endif
