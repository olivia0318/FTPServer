#include "factory.h"

void *downloadFile(void* p)
{
    //printf("Child pthread is working\n");
    pFac pf=(pFac) p;
    pNode pcur;
    int getSuccess;
    while(1)
    {
        pthread_mutex_lock(&pf->queue.queMutex);
        if(IsEmpty(&pf->queue))
        {
            printf("None of Mission Queue\n");
            pthread_cond_wait(&pf->cond,&pf->queue.queMutex);
        }
        
        printf("Child pthread is working\n");
        getSuccess=QueueGet(&pf->queue,&pcur);
        pthread_mutex_unlock(&pf->queue.queMutex);
       
        if(!getSuccess)
        {
            tranFile(pcur->newFd);
            free(pcur);
        }
    }
    return NULL;
}

void factoryInit(pFac pf,int pthNum,int capacity)
{
    printf("FactortInit\n");
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
            ret=pthread_create(pf->pthid+i,NULL,downloadFile,pf);
            ERROR_CHECK(ret,-1,"pthread_create");
        }
        pf->startFlag=1;
    }
    return 0;
}
