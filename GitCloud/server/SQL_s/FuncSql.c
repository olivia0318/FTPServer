#include "FuncSql.h"

int querySql(MYSQL *conn,char *query)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i;
    char buf[1024];
    memset(buf,0,sizeof(buf));

    if(mysql_query(conn,query))
    {
        printf("mysql_query error:%s\n",mysql_error(conn));
    }
    else
    {
        printf("%s\n",query);
        res=mysql_use_result(conn);
        if(res){
            while(NULL!=(row=mysql_fetch_row(res)))
            {
                for(i=0;i<mysql_num_fields(res);++i)
                {
                    sprintf(buf,"%s%s\t",buf,row[i]);
                }
            }
        }
        else
        {
            printf("Not Found Data\n");
            return -1;
        }
    }

    sprintf(query,"%s",buf);
    sprintf(&query[strlen(query)-1],"%c",'\0');
    mysql_free_result(res);

    return i;
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

