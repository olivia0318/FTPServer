#include "FuncSql.h"

int querySql(MYSQL *conn,char *query)
{
    MYSQL_RES *res;
    //MYSQL_ROW row;
    int t;
    t=mysql_query(conn,query);
    res=mysql_use_result(conn);
    mysql_free_result(res);

    return t;
    
}

int UsrLogInCheck(MYSQL *conn,char *usrName,char *pswd)
{
    int t;
    char query[128];
    
    memset(query,0,sizeof(query));
    sprintf(query,"select * from usrInfor where Usrname='%s';",usrName);
    t=querySql(conn,query);
    
    if(0!=t)
    {
        printf("User %s is not exist!Are you sure,try again\n",usrName);
        return -1;//返回用户名不存在标志
    }
    else
    {
        memset(query,0,sizeof(query));
        sprintf(query,"select * from usrInfor where Usrname='%s' and Ciphertext='%s';",usrName,pswd);
        t=querySql(conn,query);
    
        if(0!=t)
        {
            printf("Password is error,please try again\n");
            return -2;//返回密码错误标志
        }
        else
        {
            printf("Log In Success!\nWelcome to use Cloud Storage!\n");
            //querySql(conn,query);
            
            memset(query,0,sizeof(query));
            //记录登录时间
            sprintf(query,"update usrInfor set loginTime=CURRENT_TIMESTAMP() where Usrname='%s'",usrName);
            querySql(conn,query);
            
            return 1;//返回登录成功标志
        }
    }
    mysql_close(conn);
}

int mysqlInit(MYSQL **conn)
{
    *conn=mysql_init(NULL);
    if(!mysql_real_connect(*conn,"localhost","root","qwer","usrCloud",0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(*conn));
        return -1;
    }
    else
    {
        printf("Database Connected\n");
        return 0;
    }
}

