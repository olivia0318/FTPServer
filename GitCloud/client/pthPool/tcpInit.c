#include "func.h"

int tcpInit(int *sFd,char *ip,char *port)
{
    int socketFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	
    struct sockaddr_in serAddr;
	memset(&serAddr,0,sizeof(serAddr));
	serAddr.sin_family=AF_INET;
	serAddr.sin_port=htons(atoi(port));//把端口转换为网络字节序
	serAddr.sin_addr.s_addr=inet_addr(ip);//把IP地址转换为网络字节序
	
    int ret;
	ret=connect(socketFd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"connect");

    *sFd=socketFd;
    printf("Connected Server\n");
    return 0;
}

