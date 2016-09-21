#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

typedef struct Arg
{
    int produce;
    int max;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    Arg(const int pro = 0,const int max = 0) : produce(pro),max(max)
    {
        pthread_mutex_init(&mutex,NULL);
        pthread_cond_init(&cond,NULL);
    }
}Arg;

void* produce(void *arg)
{
    Arg *val = (Arg*)arg;
    while(true)
    {
        pthread_mutex_lock(&val->mutex);
        if(val->produce < val->max)
        {
            val->produce += 1;
            std::cout << "produce thread:" << val->produce << std::endl;
        }
        else
        {
            pthread_cond_wait(&val->cond,&val->mutex);
        }
        pthread_mutex_unlock(&val->mutex);
        usleep(100);
    }
    return NULL;
}

void* consume(void *arg)
{
    Arg *val = (Arg*)arg;
    while(true)
    {
        pthread_mutex_lock(&val->mutex);
        if(val->produce > 0)
        {
            val->produce -= 1;
            std::cout << "consume thread:" << val->produce << std::endl;
        }
        else
        {
            pthread_cond_broadcast(&val->cond);
        }
        pthread_mutex_unlock(&val->mutex);
        usleep(100);
    }
    return NULL;
}

int main(void)
{
    pthread_t pro,con;
    Arg arg(0,10);
    if(pthread_create(&pro,NULL,produce,(void*)(&arg)))
    {
        return 0;
    }
    if(pthread_create(&con,NULL,consume,(void*)(&arg)))
    {
        return 0;
    }

    pthread_join(pro,NULL);
    pthread_join(con,NULL);
    return 0;
}

