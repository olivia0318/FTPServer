#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>

int main(int argc,char* argv[])
{
    char buf[20]="helloworld";
    char *md;
    unsigned int i;
    md=MD5(buf,strlen(buf),NULL);
    printf("%s\n",buf);
    for(i=0;i<strlen(md);i++)
    {
        printf("%x",md[i]);
    }
    printf("\n");
    return 0;
}

