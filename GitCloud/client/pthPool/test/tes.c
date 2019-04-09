#define _XOPEN_SOURCE                                                  
#include "func.h"

int main()
{
    char buf[1024];                                                    
    //train t;
 
    //int flag=0;
 
    //char cipher[64];
    char *cipher;
    char salt[12]="thursd";

    memset(buf,0,sizeof(buf));
    printf("Input:\n");
    read(STDIN_FILENO,buf,sizeof(buf));
    printf("1\n");
    cipher=crypt(buf,salt);
    //sprintf(cipher,"%s",crypt(buf,salt));
    printf("2\n");
    printf("buf=%s salt=%s crypt=%s\n",buf,salt,crypt(buf,salt));
    printf("cipher=%s",cipher);
    return 0;
}

