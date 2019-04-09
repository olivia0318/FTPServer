#include "factory.h"

int epollInit(int socketFd)//如果用户在输出途中退出,多个用户同时登录
{
    int ret;

    int epfd=epoll_create(1);

    struct epoll_event event;
    event.events=EPOLLIN;
    //event.data.fd=STDIN_FILENO;
    //ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    //ERROR_CHECK(ret,-1,"epoll_ctl");

    event.data.fd=socketFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);                      
    ERROR_CHECK(ret,-1,"epoll_ctl");

    return epfd;
}

int UsrLogInCheck(pNode p)
{
    int epfd=epollInit(p->newFd);
    struct epoll_event evt;

    int t,ret;
    char query[1024];
    char usrName[20];
    char pswd[64];
    train pt;

Label1:
    memset(usrName,0,sizeof(usrName));
    memset(pswd,0,sizeof(pswd));
    printf("User LogIn\n");

    epoll_wait(epfd,&evt,1,-1);
    if(EPOLLIN==evt.events && evt.data.fd==p->newFd)
    {
        recv(p->newFd,usrName,sizeof(usrName),0);
    }

    memset(query,0,sizeof(query));
    sprintf(query,"select Salt from usrInfor where Usrname='%s';",usrName);
    t=querySql(p->conn,query);
    puts(query);
    //printf("t=%d\n",t);

    if(1!=t || 0==strcmp("",query))
    {
        ret=sprintf(pt.buf,"User is not exist");
        pt.atflag=-1;//用户名错误标志
        send(p->newFd,&pt,sizeof(pt),0);
        printf("User %s is not exist!Are you sure,try again\n",usrName);
        goto Label1;
        //return -1;//返回用户名不存在标志
    }
    else
    {
Label2:
        sprintf(pt.buf,"%s",query);
        send(p->newFd,&pt,sizeof(pt),0);//send salt
        memset(query,0,sizeof(query));
        epoll_wait(epfd,&evt,1,-1);
        if(EPOLLIN==evt.events && evt.data.fd==p->newFd)
        {
            recv(p->newFd,pswd,sizeof(pswd),0);
        }
        //sprintf(query,"select Ciphertext from usrInfor where Usrname='%s';",usrName);
        sprintf(query,"select Usrname from usrInfor where Ciphertext='%s';",pswd);
        t=querySql(p->conn,query);
        puts(query);
        //printf("t=%d\n",t);

        if(1!=t || 0!=strcmp(usrName,query))
        {
            sprintf(pt.buf,"Password is error,please try again");
            pt.atflag=-2;//密文错误标志
            send(p->newFd,&pt,sizeof(pt),0);
            printf("Password is error,please try again\n");
            //return -2;//返回密码错误标志i
            goto Label2;
        }
        else
        {
            sprintf(pt.buf,"Log In Success!\nWelcome to use Cloud Storage!\n");
            pt.atflag=1;//登录成功标志
            send(p->newFd,&pt,sizeof(pt),0);
            //printf("Log In Success!\nWelcome to use Cloud Storage!\n");
            //querySql(conn,query);
            memset(query,0,sizeof(query));
            //记录登录时间
            sprintf(query,"update usrInfor set loginTime=CURRENT_TIMESTAMP() where Usrname='%s'",usrName);
            querySql(p->conn,query);
            //puts(query);

            p->LoginFlag=1;
            //mysql_close(p->conn);
            return 1;//返回登录成功标志
        }
    }
}


