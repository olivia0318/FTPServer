#ifndef __COMMAND_H__
#define __COMMAND_H__
#include "head.h"
#include "tranFile.h"

int TypeNum(char *cmd);
int classifyWork(char *buf,int);
void classifyType(char *cmd1,char *cmd2,int *typeNum,int);

void enterDir(char*,int);
void DirList(char*,int);
void Upload(char*);
void Download(char*);
void RemoveF(char*);
void printWDir(char*);


#endif
