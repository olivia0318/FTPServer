#include <func.h>

int recvCycle(int,char*,int);

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int socketFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	
    struct sockaddr_in serAddr;
	memset(&serAddr,0,sizeof(serAddr));
	serAddr.sin_family=AF_INET;
	serAddr.sin_port=htons(atoi(argv[2]));//把端口转换为网络字节序
	serAddr.sin_addr.s_addr=inet_addr(argv[1]);//把IP地址转换为网络字节序
	
    int ret;
	ret=connect(socketFd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"connect");
	
    char buf[1000]={0};
    int dataLen;

    recvCycle(socketFd,(char*)&dataLen,sizeof(int));
    recvCycle(socketFd,buf,dataLen);
    
    off_t downloadsize=0,filesize;
    recvCycle(socketFd,(char*)&dataLen,sizeof(int));
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
        //sleep(1);
    }
    close(socketFd);

    return 0;
}	
