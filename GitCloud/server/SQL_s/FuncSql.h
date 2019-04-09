#ifndef __FUNCSQL_H__
#define __FUNCSQL_H__
#include "head.h"
#include "mysql/mysql.h"

int mysqlInit(MYSQL **);
int querySql(MYSQL *,char *query);


#endif
