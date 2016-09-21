#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;

typedef struct Arg
{
    int ret;
    sem_t sem;
    Arg()
    {
        ret = 0;
        sem_init(&sem,0,0);
    }
}Arg;

void* produce(void *arg)
{
    Arg *val = (Arg*)arg;
    while(true)
    {
        val->ret += 1;
        std::cout << "produce therad :" << val->ret << std::endl;
        sem_post(&val->sem);
        usleep(100);
    }
    return NULL;
}

void* consume(void *arg)
{
    Arg *val = (Arg*)arg;
    while(true)
    {
        sem_wait(&val->sem);
        val->ret -= 1;
        std::cout << "consume therad :" << val->ret << std::endl;
        usleep(100);
    }
    return NULL;
}

int main()
{
    Arg arg;
    pthread_t pro,con;
    if(pthread_create(&pro,NULL,produce,(void*)&arg))
    {
        return 0;
    }
    if(pthread_create(&con,NULL,consume,(void*)&arg))
    {
        return 0;
    }

    pthread_join(pro,NULL);
    pthread_join(con,NULL);
    sem_destroy(&arg.sem);
    return 0;
}

