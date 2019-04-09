#include "factory.h"

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,5);
    int sFd;
    tcpInit(&sFd,argv[1],argv[2]);
    
    int threadNum=atoi(argv[3]);
    int cap=atoi(argv[4]);
    factory pf;
    factoryInit(&pf,threadNum,cap);
    factoryStart(&pf);

    int newFd;
    pQue q=&pf.queue;

    while(1)
    {
        newFd=accept(sFd,NULL,NULL);
        pNode pNew=(pNode)calloc(1,sizeof(que));
        pNew->newFd=newFd;
        pthread_mutex_lock(&q->queMutex);
        printf("Child pthread is working\n");
        QueueInsert(q,pNew);
        pthread_mutex_unlock(&q->queMutex);
        pthread_cond_signal(&pf.cond);
    }
    return 0;
}

