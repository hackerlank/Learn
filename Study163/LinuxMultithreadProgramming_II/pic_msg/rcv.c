#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Msg
{
    long m_type;
    int m_begin;
    int m_end;
}Msg;

int main(int argc,char *argv[])
{
    int ret = 0;
    do
    {
        if(argc < 3)
        {
            printf("argc error\n");
            break;
        }
        key_t key = atol(argv[1]);
        long type = atol(argv[2]);
        int msgID = msgget(key,0777);
        if(msgID < 0)
        {
            break;
        }
        //根据type来获得消息(type为0,则获取队列的头,type为正整数,则获取type为次正整数的的第一个消息,如果为负数,则获取type小于或者等于次负数的绝对值的第一个,且取类型最小的
        Msg msg;
        if(msgrcv(msgID,&msg,sizeof(msg) - sizeof(msg.m_type),type,IPC_NOWAIT) < 0)
        {
            perror("no msg get\n");
            break;
        }
        printf("get msg:%ld,%d,%d\n",msg.m_type,msg.m_begin,msg.m_end);
        ret = 1;
    }while(0);
    return ret;
}


