#include "head.h"


union semun
{
    int val;
    struct semid_ds *buffer;
    unsigned short *arry;
};

int I(const int semnum,const int val)
{
    //创建信号集
    int semid = semget(IPC_PRIVATE,semnum,IPC_CREAT | IPC_EXCL | 0777);
    if(semid < 0)
    {
        perror("semget error");
        return -1;
    }
    //设置信号集中每个信号灯的值
    unsigned short *arry = (unsigned short*)malloc(semnum * sizeof(unsigned short));
    int cnt;
    for(cnt = 0;cnt < semnum;++cnt)
    {
        arry[cnt] = val;
    }
    union semun un;
    //初始化信号集
    un.arry = arry;
    if(semctl(semid,0,SETALL,un) < 0)
    {
        perror("semctl error");
        return -1;
    }
    free(arry);
    return semid;
}

//P操作对信号量进行减操作
void P(const int semid,const int semnum,const int val)
{
    //如果进行多个信号灯进行操作,那么ops里面就有多个sembuf函数
    assert(val > 0);
    //struct sembuf ops[]  = { {semnum,-val,SEM_UNDO } };
    struct sembuf ops;
    ops.sem_num = semnum;
    ops.sem_op = -val;
    ops.sem_flg = SEM_UNDO;
    if(semop(semid,&ops,1) < 0)
    {
        perror("semop error");
    }
}

//v操作对信号量进行加操作
void V(const int semid,const int semnum,const int val)
{
    assert(val > 0);
    //用数组会报错
    //struct sembuf ops[]  = { {semnum,val,SEM_UNDO } };
    struct sembuf ops;
    ops.sem_num = semnum;
    ops.sem_op = val;
    ops.sem_flg = SEM_UNDO;
    if(semop(semid,&ops,1) < 0)
    {
        perror("semop error");
    }
}

//销毁信号量集操作
void D(const int semid)
{
    //这里是销毁,所以最后传NULL即可
    if(semctl(semid,0,IPC_RMID,NULL) < 0)
    {
        perror("semctl error");
    }
}
