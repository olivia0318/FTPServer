#define _XOPEN_SOURCE
#include "func.h"
#include "pthpool.h"

int epollInit(int epfd,int socketFd)
{
    int ret;

    struct epoll_event event;
    event.events=EPOLLIN;
    //event.data.fd=STDIN_FILENO;
    //ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    //ERROR_CHECK(ret,-1,"epoll_ctl");

    event.data.fd=socketFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");

    return 0;
}

int LogInFunc(int epfd,pFac pf)
{
    epollInit(epfd,pf->sFd);
    struct epoll_event evt;

    char buf[128];
    char salt[12];
    char cipher[128];
    int ret;

    train pt;

    printf("Welcome to use CloudPan\n");
    memset(buf,0,sizeof(buf));
    memset(salt,0,sizeof(salt));
    
    printf("Username Input:\n");
    //ret=scanf("%s",buf);
    ret=read(STDIN_FILENO,buf,sizeof(buf));
    send(pf->sFd,buf,ret-1,0);
    
    while(1)
    {
        epoll_wait(epfd,&evt,1,-1);
        if(EPOLLIN==evt.events && pf->sFd==evt.data.fd)
        {
            memset(&pt,0,sizeof(train));
            ret=recv(pf->sFd,&pt,sizeof(pt),0);
            
            if(1==pt.atflag)//有安全问题，要用token改进
            {
                printf("%s\n",pt.buf);
                pf->LogInFlag=1;
                return 0;
            }
            else if(-1==pt.atflag)
            {
                memset(buf,0,sizeof(buf));
                printf("Username reInput:\n");
                //ret=scanf("%s",buf);
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                send(pf->sFd,buf,ret-1,0);
            }
            else if(0==pf->LogInFlag || -2==pt.atflag)
            {
                sprintf(salt,"%s",pt.buf);
                memset(buf,0,sizeof(buf));
                sprintf(buf,"%s",getpass("Password Input:\n"));
                
                printf("pw=%s salt=%s\n",buf,salt);
                ret=sprintf(cipher,"%s",crypt(buf,salt));
                memset(salt,0,sizeof(salt));
                printf("pw=%s\n",cipher);
                send(pf->sFd,cipher,ret,0);
            }
        }
    }
    return -1;
}

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,4);
    int socketFd;
    tcpInit(&socketFd,argv[1],argv[2]);

    fac pf;
    memset(&pf,0,sizeof(fac));
    factoryInit(&pf,atoi(argv[3]));
    pf.sFd=socketFd;
    //facStart(&pf);
    //int ret;
    
    int epfd=epoll_create(1);
    //struct epoll_event evt;
    //epollInit(epfd,socketFd);
    
    //int fd=open(argv[3],O_CREAT|O_RDWR|0666);
    //char buf[1024];

    while(1)
    {
        LogInFunc(epfd,&pf);
        printf("Command Input:\n");//客户端命令反馈接收处理机制
        //pthread_cond_signal(&pf.cond);
    }

    close(socketFd);

    return 0;
}	
