#include <sys/time.h>
#include <sys/mman.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <syslog.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <signal.h>
#include <pthread.h>
#include <malloc.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/uio.h>
#include <stdbool.h>

#define ARGS_CHECK(argc,num){if(argc!=num){perror("error args\n");return -1;}}
#define ERROR_CHECK(ret,retval,funcname) {if(retval==ret){perror(funcname);return -1;}}
#define THREAD_ERROR_CHECK(ret,funcname) {if(-1==ret){printf("%s is error\n",funcname);return -1;}}

