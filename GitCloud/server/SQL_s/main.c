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

    MYSQL *conn;
    mysqlInit(&conn);

    int newFd;
    pQue q=&pf.queue;
    char buf[64];
    
    while(1)
    {
        newFd=accept(sFd,NULL,NULL);
        pNode pNew=(pNode)calloc(1,sizeof(que));
        pNew->newFd=newFd;
        pNew->conn=conn;//开数据库的钥匙
        
        printf("LOGIN:%d\n",pNew->LoginFlag);
        if(0==pNew->LoginFlag)
        {
            UsrLogInCheck(pNew);
            memset(buf,0,sizeof(buf));
            sprintf(buf,"LogIn success");
            send(pNew->newFd,buf,strlen(buf),0);
        }
        
        if(1==pNew->LoginFlag)
        {
            CommandHandler(pNew);
        }
        
        if(2==pNew->LoginFlag)
        {
            pthread_mutex_lock(&q->queMutex);
            QueueInsert(q,pNew);
            pthread_mutex_unlock(&q->queMutex);
            pthread_cond_signal(&pf.cond);
        }
    }
    return 0;
}

