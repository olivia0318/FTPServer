#include "tranFile.h"

int tranFile(int newFd)
{
    train t;//发送数据的结构体
    t.dataLen=strlen(FILENAME);
    strcpy(t.buf,FILENAME);
    sendCycle(newFd,(char*)&t,4+t.dataLen);//网络字节序，大小端
    int fd=open(FILENAME,O_RDONLY);
   
    struct stat buf;
    fstat(fd,&buf);
    t.dataLen=sizeof(buf.st_size);
    memcpy(t.buf,&buf.st_size,sizeof(buf.st_size));
    sendCycle(newFd,(char*)&t,4+t.dataLen);
    
    while((t.dataLen=read(fd,t.buf,sizeof(t.buf)))>0)
    {
        sendCycle(newFd,(char*)&t,4+t.dataLen);
    }
    send(newFd,&t,4,0);//文件结束标志
    return 0;
}
