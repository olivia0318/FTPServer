#include "factory.h"

int TypeNum(char *cmd)
{
    //printf("3 cmd1=%s",cmd);
    int typeNum=0;
    if(0==strcmp(cmd,"cd "))
    {
        typeNum=1;
    }
    else if(0==strcmp(cmd,"ls "))
    {
        typeNum=2;
    }
    else if(0==strcmp(cmd,"puts "))
    {
        typeNum=3;
    }
    else if(0==strcmp(cmd,"gets "))
    {
        typeNum=4;
    }
    else if(0==strcmp(cmd,"remove "))
    {
        typeNum=5;
    }
    else if(0==strcmp(cmd,"pwd "))
    {
        typeNum=6;
    }
    else
    {
        typeNum=7;
    }
    return typeNum;
}

void classifyType(char *cmd1,char *cmd2,int *typeNum,int fd)
{
    switch(TypeNum(cmd1))
    {
    case 1:
        *typeNum=1;
        enterDir(cmd2,fd);
        break;
    case 2:
        *typeNum=2;
        DirList(cmd2,fd);
        break;
    case 7:
        *typeNum=7;
        printf("Invaild cmd\n");
        break;
    }

    printf("cmd1=%s,cmd2=%s,typeNum=%d\n",cmd1,cmd2,*typeNum);
}

int classifyWork(char *cmd,int fd)
{
    //int ret;
    char cmd1[20]={0};
    char cmd2[100]={0};
    size_t i,j;

    //ret=read(pcur->newFd,cmd,sizeof(cmd));
    for(i=0;i<strlen(cmd);++i)//分离命令
    {
        cmd1[i]=cmd[i];
        if(' '==cmd[i]&&' '!=cmd[i+1])
        {
            for(j=i+1;j<strlen(cmd);++j)
            {
                cmd2[j-i-1]=cmd[j];
            }
            break;
        }
    }
    int typeNum=0;
    classifyType(cmd1,cmd2,&typeNum,fd);
    return typeNum;
}

