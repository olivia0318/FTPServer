#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <shadow.h>
#include <errno.h>

void help(void)
{
    printf("用户密码验证程序\n第一个参数为用户名！\n");
    exit(-1);
}

void error_quit(char *msg)
{
    perror(msg);
    exit(-2);
}

void get_salt(char *salt,char *passwd)
{
    int i,j;

    for(i=0,j=0;passwd[i]&&j!=3;++i)
    {
        if(passwd[i]=='$')
        {
            ++j;
        }
        strncpy(salt,passwd,i-1);
    }
}

int main(int argc,char **argv)
{
    struct spwd *sp;
    char *passwd;
    char salt[512]={0};

    if(argc!=2)
    {
        help();
    }

    //char *buf;
    passwd=getpass("Input pw:\n");
    if(NULL==(sp=getspnam(argv[1])))
    {
        //strcpy(buf,"get usrname and pw");
        error_quit("get usrname and pw");
        
    }
    get_salt(salt,sp->sp_pwdp);

    if(0==strcmp(sp->sp_pwdp,crypt(passwd,salt)))
    {
        printf("check success!\n");
    }
    else
    {
        printf("check fail\n");
    }

    return 0;
}

