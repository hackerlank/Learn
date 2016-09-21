#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <map>
using namespace std;

typedef struct Table 
{
    std::map<int,bool> m_forkmap;
    pthread_mutex_t m_mutex;
    Table(const int num = 5)
    {
        for(int cnt = 1;cnt <= num;++cnt)
        {
            m_forkmap[cnt] = true;
        }
        pthread_mutex_init(&m_mutex,NULL);
    }
    bool eat(const int personNo)
    {
        pthread_mutex_lock(&m_mutex);
        bool ret = false;
        do
        {
            int left = personNo == 1 ? 5 : personNo - 1;
            int right = personNo;
            if(!m_forkmap[left])
            {
                break;
            }
            if(!m_forkmap[right])
            {
                break;
            }
            m_forkmap[left] = false;
            m_forkmap[right] = false;
            ret = true;
        }while(false);
        pthread_mutex_unlock(&m_mutex);
        return ret;
    }
    bool eatFinish(const int personNo)
    {
        pthread_mutex_lock(&m_mutex);
        bool ret = false;
        do
        {
            int left = personNo == 1 ? 5 : personNo - 1;
            int right = personNo;
            if(m_forkmap[left])
            {
                break;
            }
            if(m_forkmap[right])
            {
                break;
            }
            m_forkmap[left] = true;
            m_forkmap[right] = true;
            ret = true;
        }while(false);
        pthread_mutex_unlock(&m_mutex);
        return ret;
    }
    ~Table()
    {
        pthread_mutex_destroy(&m_mutex);
    }
}Table;

Table table(5);

void* eat(void* arg)
{
    int personNo = *(int*)arg;
    while(true)
    {
        bool ret = table.eat(personNo);
        if(ret)
        {
            std::cout << "personNo eat begin (" << personNo << ") success !" << std::endl;
            usleep(1000);
            ret = table.eatFinish(personNo);
            std::cout << "personNo eat end (" << personNo << ") success !" << std::endl;

        }
    }
    return NULL;
}

int main(void)
{
    bool ret = false;
    pthread_t a,b,c,d,e;
    do
    {
        int no1 = 1;
        if(pthread_create(&a,NULL,eat,(void*)&no1))
        {
            break;
        }
        int no2 = 2;
        if(pthread_create(&b,NULL,eat,(void*)&no2))
        {
            break;
        }
        int no3 = 3;
        if(pthread_create(&c,NULL,eat,(void*)&no3))
        {
            break;
        }
        int no4 = 4;
        if(pthread_create(&d,NULL,eat,(void*)&no4))
        {
            break;
        }
        int no5 = 5;
        if(pthread_create(&e,NULL,eat,(void*)&no5))
        {
            break;
        }
        ret = true;
    }while(false);
    if(!ret)
    {
        return 0;
    }
    pthread_join(a,NULL);
    pthread_join(b,NULL);
    pthread_join(c,NULL);
    pthread_join(d,NULL);
    pthread_join(e,NULL);
    std::cout << "main thread finish ..." << std::endl;
    return 0;
}

