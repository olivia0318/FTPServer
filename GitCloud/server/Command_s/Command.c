#include "Command.h"

//命令反馈，反馈结果装车，由子线程调用tranFile发送给客户端
void enterDir(char *path,int fd)
{
    int total=0,ret;
    char buf[1000];
    memset(buf,0,sizeof(buf));
    
    sprintf(buf,"Jump to %s ",path);
    ret=write(fd,buf,strlen(buf));
    total+=ret;
    //t->dataLen=total;
    //memcpy(t->buf,buf,total);
    
    //printf("%s size=%d\n",buf,total);
    chdir(path);
    DirList(path,fd);
    lseek(fd,-total,SEEK_CUR);
}

void DirList(char *path,int fd)
{
    int total=0,ret;
    char buf[1000];
    memset(buf,0,sizeof(buf));
    
    DIR *dir;
    
    sprintf(buf,"print dir:%s \n",path);
    ret=write(fd,buf,strlen(buf));
    total+=ret;
    
    dir=opendir(path);

    if(NULL==dir)
    {
        perror("opendir");
        sprintf(buf,"opendir %s: No such file or directory",path);
        ret=write(fd,buf,sizeof(buf));
        total+=ret;
        lseek(fd,-total,SEEK_CUR);
        return;
    }
    
    struct dirent *p;
    int flag=0;
    while(NULL!=(p=readdir(dir)))
    {
        if(0==strcmp(p->d_name,".")||0==strcmp(p->d_name,".."))
        {
            continue;
        }
        sprintf(buf,"%s  ",p->d_name);
        ret=write(fd,buf,strlen(buf));
        total+=ret;
        flag++;
        if(0==flag%5 && 5<=flag)
        {
            sprintf(buf,"\n");
            ret=write(fd,buf,strlen(buf));
            total+=ret;
        }
    }
    sprintf(buf,"\n");
    ret=write(fd,buf,strlen(buf));
    total+=ret;

    time_t cur;
    cur=time(NULL);
    ctime_r(&cur,buf);
    ret=write(fd,buf,strlen(buf));
    total+=ret;
    lseek(fd,-total,SEEK_CUR);
    //ret=sprintf(buf,"\n");
    //total+=ret;
    //memcpy(t->buf+t->dataLen,buf,total);
    //t->dataLen+=total;
    //printf("%ssize=%d\n",buf,total);
}

void Upload(char* filename)
{
    printf("upload file:%s\n",filename);
}

void Download(char* filename)
{
    printf("Download file:%s\n",filename);
}
void RemoveF(char* filename)
{
    printf("Remove file：%s\n",filename);
}

void printWDir(char *path)
{
    printf("current working directory:\n%s\n",getcwd(NULL,0));
}
