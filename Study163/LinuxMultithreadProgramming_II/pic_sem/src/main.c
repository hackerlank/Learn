#include "head.h"
#include <pthread.h>
int semid;

void* aFun(void *arg)
{
    P(semid,0,1);
    printf("runing a thread\n");
    V(semid,1,1);
    return NULL;
}

void* bFun(void *arg)
{
    P(semid,1,1);
    printf("runing b thread\n");
    V(semid,2,1);
    return NULL;
}

void* cFun(void *arg)
{
    P(semid,2,1);
    printf("runing c thread\n");
    return NULL;
}


int main()
{
    semid = I(3,1);
    //先把第二个和第三个信号进行P操作
    P(semid,1,1);
    P(semid,2,1);
    pthread_t a,b,c;
    if(pthread_create(&a,NULL,aFun,NULL))
    {
        return 0;
    }
    if(pthread_create(&b,NULL,bFun,NULL))
    {
        return 0;
    }
    if(pthread_create(&c,NULL,cFun,NULL))
    {
        return 0;
    }
    pthread_join(a,NULL);
    pthread_join(b,NULL);
    pthread_join(c,NULL);
    D(semid);
    return 0;
}
