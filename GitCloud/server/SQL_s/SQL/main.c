#include "FuncSql.h"

int main(int argc,char *argv[])
{
    //ARGS_CHECK(argc,3);
    MYSQL *conn;
    mysqlInit(&conn);
    
    char usrname[12]="Oli";
    char pwd[12]="qwer";
    UsrLogInCheck(conn,usrname,pwd);

    return 0;
}

