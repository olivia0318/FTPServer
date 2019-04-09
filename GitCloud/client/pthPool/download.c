#include "func.h"

int Download(int socketFd)
{
    char buf[1000]={0};
    int dataLen;

    recvCycle(socketFd,(char*)&dataLen,sizeof(int));//文件名称
    recvCycle(socketFd,buf,dataLen);

    off_t downloadsize=0,filesize;
    recvCycle(socketFd,(char*)&dataLen,sizeof(int));//文件大小
    recvCycle(socketFd,(char*)&filesize,dataLen);

    int fd;
    fd=open(buf,O_CREAT|O_RDWR,0666);
    ERROR_CHECK(fd,-1,"open");

    time_t t1,t2;
    t1=t2=time(NULL);
    
    while(1)
    {
        //printf("dataLen=%d\n",dataLen);
        recvCycle(socketFd,(char*)&dataLen,sizeof(int));
        if(dataLen>0)
        {
            recvCycle(socketFd,buf,dataLen);
            downloadsize+=dataLen;
            write(fd,buf,dataLen);
            t2=time(NULL);
            if(t2-t1>=1)
            {
                printf("\r%5.2f%s",(double)downloadsize/filesize*100,"%");
                fflush(stdout);
                t1=t2;
            }
        }
        else
        {
            printf("\r100.00%s\n","%");
            close(fd);
            break;
        }
    }
    return 0;
}
