#include "factory.h"

void *Gotodo(void* p)
{
    pFac pf=(pFac) p;
    pNode pcur;
    int getSuccess,ret;
    //train t;
    //int fd;
    char buf[128]={0};
    while(1)
    {
        pthread_mutex_lock(&pf->queue.queMutex);
        if(IsEmpty(&pf->queue))
        {
            printf("\nNone of Mission Queue\n");
            pthread_cond_wait(&pf->cond,&pf->queue.queMutex);
        }

        printf("\nChild pthread %ld is working\n",*pf->pthid);
        //getSuccess=QueueGet(&pf->queue,&pcur);

        pthread_mutex_unlock(&pf->queue.queMutex);
        
        //while(1)
        //{
        //    if(!getSuccess)
        //    {
        //        //用户注册
        //        //用户登陆
        //        if(0==pcur->LoginFlag)
        //        {
        //            UsrLogInCheck(pcur);
        //        }
        //        else if(1==pcur->LoginFlag)
        //        {
        //            //break;
        //            sprintf(buf,"Login success");
        //            send(pcur->newFd,buf,strlen(buf),0);
        //            pcur->LoginFlag=2;//表示客户端已接受登录确认信息
        //        }
        //        else if(2==pcur->LoginFlag)
        //        {
        //            memset(buf,0,sizeof(buf));
        //            sprintf(buf,"\nCommand Input:\n");
        //            send(pcur->newFd,buf,strlen(buf),0);
        //            CommandHandler(pcur);//命令处理函数
        //        }
        //        
        //    }
        //}
    }

    return NULL;
}

void factoryInit(pFac pf,int pthNum,int capacity)
{
    printf("FactoryInit\n");
    memset(pf,0,sizeof(factory));
    pthread_cond_init(&pf->cond,NULL);
    pf->pthNum=pthNum;
    pf->queue.queCapacity=capacity;
    pf->pthid=(pthread_t*)calloc(pf->pthNum,sizeof(pthread_t));
    QueueInit(&pf->queue,capacity);
}

int factoryStart(pFac pf)
{
    int i,ret;
    if(0==pf->startFlag)
    {
        printf("Begin to generate child pthread\n");
        for(i=0;i<pf->pthNum;++i)
        {
            ret=pthread_create(pf->pthid+i,NULL,Gotodo,pf);
            ERROR_CHECK(ret,-1,"pthread_create");
        }
        pf->startFlag=1;
    }
    return 0;
}

int CommandHandler(pNode pcur)                                                           
{
    int ret;
    char buf[128];
    int fd=open("test0403",O_RDWR|O_CREAT,0666);
    char res[1024];
Label1:
    lseek(fd,0,SEEK_END);
    memset(res,0,sizeof(res));
    memset(buf,0,sizeof(buf));
    ret=recv(pcur->newFd,buf,sizeof(buf),0);
    if(0<ret)
    {
        ret=classifyWork(buf,fd);
        read(fd,res,sizeof(res));
        //printf("%s\n",res);
        send(pcur->newFd,res,sizeof(res),0);

        if(7==ret)
        {
            strcpy(buf,"Invaild Command,please try again");
            send(pcur->newFd,buf,strlen(buf),0);
            goto Label1;
        }
        else
        {
            close(fd);
            //send(pcur->newFd,buf,strlen(buf),0);
            return 0;
        }
    }
    else if(0>ret)
    {
        printf("Command recv error\n");
        strcpy(buf,"Recv error,please try again");
        send(pcur->newFd,buf,strlen(buf),0);
        goto Label1;
    }
    else
    {
        close(fd);
        return 0;
    }
}   

