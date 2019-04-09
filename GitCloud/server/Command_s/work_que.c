#include "work_que.h"

bool IsEmpty(pQue q)
{
    if(0<q->queSize)
    {
        return false;
        printf("Queue is not empty\n");
    }
    else
    {
        return true;
        printf("Queue is empty\n");
    }
}

void QueueInit(pQue q,int capacity)
{
    memset(q,0,sizeof(que));
    q->queCapacity=capacity;
    pthread_mutex_init(&q->queMutex,NULL);
    printf("QueueInit is over\n");
}

void QueueInsert(pQue q,pNode pNew)
{
    printf("Mission is IN\n");
    if(NULL==q->rear)
    {
        q->front=pNew;
        q->rear=pNew;
    }
    else
    {
        q->rear->pNext=pNew;
        q->rear=pNew;
    }
    q->queSize++;
    printf("Quesize=%d\n",q->queSize);
}

int QueueGet(pQue q,pNode *pcur)
{
    printf("Try get mission\n");
    if(0==q->queSize)
    {
        return -1;
    }
    else
    {
        *pcur=q->front;
        q->front=q->front->pNext;
        if(q->rear==*pcur)
        {
            q->front=NULL;
            q->rear=NULL;
            q->queSize=0;
        }
        q->queSize--;
        printf("Mission is Out\n");
        return 0;
    }
}

