#include <iostream>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
using namespace std;

typedef struct Res
{
    int ret;
    bool wait;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    Res()
    {
        ret = 0;
        wait = false;
        pthread_mutex_init(&mutex,NULL);
        pthread_cond_init(&cond,NULL);
    }
}Res;


void* cntFun(void *arg)
{
    Res *res = (Res*)arg;
    pthread_mutex_lock(&res->mutex);
    res->ret = 10;
    pthread_mutex_unlock(&res->mutex);
    pthread_mutex_lock(&res->mutex);
    while(!res->wait)
    {
        pthread_mutex_unlock(&res->mutex);
        usleep(100);
        pthread_mutex_lock(&res->mutex);
    }
    pthread_cond_broadcast(&res->cond);
    pthread_mutex_unlock(&res->mutex);
    return NULL;
}

void* printFun(void *arg)
{
    Res *res = (Res*)arg;
    pthread_mutex_lock(&res->mutex);
    res->wait = true;
    pthread_cond_wait(&res->cond,&res->mutex);
    pthread_mutex_unlock(&res->mutex);
    std::cout << "ret:" << res->ret << std::endl;
    return NULL;
}

int main(void)
{
    Res res;
    pthread_t tid1,tid2;
    if(pthread_create(&tid1,NULL,cntFun,(void*)(&res)))
    {
        return 0;
    }
    if(pthread_create(&tid2,NULL,printFun,(void*)(&res)))
    {
        return 0;
    }

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return 0;
}


