#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "work_que.h"
#include "head.h"//假定不知道work_que.h包含了head.h
#include "tranFile.h"
#endif

typedef struct{
    pthread_t *pthid;
    int pthNum;
    pthread_cond_t cond;
    que queue;
    short startFlag;
}factory,*pFac;

void factoryInit(pFac,int,int);
int factoryStart(pFac);
void tcpInit(int*,char*,char*);



