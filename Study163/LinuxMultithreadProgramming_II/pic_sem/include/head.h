#ifndef HEAD_H
#define HEAD_H
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/stat.h>

//创建且初始化信号集
int I(const semnum,const int val);

//进行P操作
void P(const int semid,const int semnum,const int val);

//进行V操作
void V(const int semid,const int semnum,const int val);

//把信号集进行销毁
void D(const int semid);

#endif
