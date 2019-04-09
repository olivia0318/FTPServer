#include "func.h"

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    tcpInit(&socketFd,argv[1],argv[2]);

    int ret;
    int epfd=epoll_create(1);
    struct epoll_event event,evs[2];
    event.events=EPOLLIN;
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");

    event.data.fd=socketFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int readyNum,i;
    //int fd=open(argv[3],O_CREAT|O_RDWR|0666);
    char buf[1024];
    train t;

    while(1)
    {
        memset(evs,0,sizeof(evs));
        readyNum=epoll_wait(epfd,evs,2,-1);

        for(i=0;i<readyNum;++i)
        {
            if(STDIN_FILENO==evs[i].data.fd)
            {
                memset(&t,0,sizeof(train));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                send(socketFd,buf,ret-1,0);
            }

            if(EPOLLIN==evs[i].events && socketFd==evs[i].data.fd)
            {
                memset(buf,0,sizeof(buf));
                ret=recv(socketFd,buf,sizeof(buf),0);
                ERROR_CHECK(ret,-1,"recv");
                //read(socketFd,buf,sizeof(buf));
                printf("%s\n",buf);
            }
        }
    }

    close(socketFd);

    return 0;
}	
