#include "work_que.h"

bool IsEmpty(pQue q)
{
    if(0<q->queSize)
    {
        printf("\nQueue is not empty\n");
        return false;
    }
    else
    {
        printf("\nQueue is empty\n");
        return true;
    }
}

void QueueInit(pQue q,int capacity)
{
    memset(q,0,sizeof(que));
    q->queCapacity=capacity;
    pthread_mutex_init(&q->queMutex,NULL);
    printf("\nQueueInit is over\n");
}

void QueueInsert(pQue q,pNode pNew)
{
    printf("\nMission is IN\n");
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
    printf("\nTry get mission\n");
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
        else
        {
            q->queSize--;
        }
        printf("Quesize=%d\n",q->queSize);
        printf("Mission is Out\n");
        return 0;
    }
}

