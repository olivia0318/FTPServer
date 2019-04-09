#include "head.h"
#ifndef __WORK_QUE__
#define __WORK_QUE__
#endif

typedef struct tagNode
{
    int newFd;
    struct tagNode *pNext;
}Node,*pNode;

typedef struct tagQueue
{
    pNode front,rear;
    int queCapacity;//队列所能存的最大值
    int queSize;//队列实时大小
    pthread_mutex_t queMutex;
}que,*pQue;

void QueueInit(pQue q,int capacity);
void QueueInsert(pQue q,pNode pNew);
int QueueGet(pQue q,pNode *p);

void QueDestroy(pQue q);
bool IsFull(pQue q);
bool IsEmpty(pQue q);


