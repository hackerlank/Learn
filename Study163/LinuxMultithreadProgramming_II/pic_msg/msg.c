#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <string.h>

typedef struct Msg
{
    long m_type; //type不计入发送消息的长度
    int m_begin;
    int m_end;
}Msg;

int main(int argc,char *argv[])
{
    int ret = 0;
    do
    {
        if(argc < 2)
        {
            printf("input error:%s\n",argv[0]);
            break;
        }
        key_t key = atol(argv[1]);
        //创建消息队列
        int msgID = msgget(key,IPC_CREAT | IPC_EXCL | 0777);
        if(msgID < 0)
        {
            perror("msgget error");
            break;
        }
        int flg = 1;
        Msg msg;
        int cnt = 1;
        while(cnt < 5)
        {
            msg.m_type = cnt;
            msg.m_begin = msg.m_type;
            msg.m_end = msg.m_begin;
            //放入消息队列,IPC_NOWAIT参数为非阻塞,长度为总长度减去type
            if(msgsnd(msgID,&msg,sizeof(Msg) - sizeof(long),IPC_NOWAIT) < 0)
            {
                perror("msgsnd msg error");
                flg = 0;
                break;
            }
            ++cnt;
        }
        if(!flg)
        {
            break;
        }
        //控制消息队列函数,获取队列的属性
        struct msqid_ds ds;
        if(msgctl(msgID,IPC_STAT,&ds) < 0)
        {
            perror("msgctl error");
            break;
        }
        printf("msg cnt:%d\n",ds.msg_qnum);
        ret = 1;
    }while(0);
    return ret ? 1 : 0;
}

