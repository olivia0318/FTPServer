#ifndef __PTHPOOL_H__
#define __PTHPOOL_H__
#include "func.h"

typedef struct{
    int sFd;
    pthread_t *pthid;
    int pthNum;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    short startFlag;
    unsigned short LogInFlag;
}fac,*pFac;

void *GotoDo(void *p)
{
    pFac pf=(pFac)p;
    //一个子线程发送命令，接收命令反馈
    while(1)
    {
        pthread_mutex_lock(&pf->mutex);
        if(0==pf->LogInFlag)
        {
            printf("Cpthread is Wait\n");
            pthread_cond_wait(&pf->cond,&pf->mutex);
        }
        pthread_mutex_unlock(&pf->mutex);
        //如果有上传或者下载任务，让第二个子醒来
    }

}

void factoryInit(pFac pf,int pthNum)
{
    printf("pthPoolInit\n");
    memset(pf,0,sizeof(fac));
    pthread_mutex_init(&pf->mutex,NULL);
    pthread_cond_init(&pf->cond,NULL);
    pf->pthNum=pthNum;
    pf->pthid=(pthread_t*)calloc(pf->pthNum,sizeof(pthread_t));
}

void facStart(pFac pf)
{
    int i;
    if(0==pf->startFlag)
    {
        printf("\nStart to generate child pthread\n");
        for(i=0;i<pf->pthNum;++i)
        {
            pthread_create(pf->pthid+i,NULL,GotoDo,pf);
            printf("Child pthread %d is generated",i);
        }
        pf->startFlag=1;
    }
}

#endif
