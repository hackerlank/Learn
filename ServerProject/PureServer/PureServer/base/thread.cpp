#include "thread.h"

Thread::Thread(const std::string &name,const bool join) : m_id(0),m_name(name),m_complete(false),m_alive(false),m_join(join)
{
    pthread_mutex_init(&m_mutex,NULL);
    pthread_cond_init(&m_cond,NULL);
}

void* Thread::process(void *arg)
{
    Thread *thread = (Thread*)arg;
    pthread_mutex_lock(&thread->m_mutex);
    thread->m_alive = true;
    pthread_cond_broadcast(&thread->m_cond);
    pthread_mutex_unlock(&thread->m_mutex);

    pthread_mutex_lock(&thread->m_mutex);
    thread->run();
    pthread_mutex_unlock(&thread->m_mutex);

    pthread_mutex_lock(&thread->m_mutex);
    thread->m_alive = false;
    pthread_cond_broadcast(&thread->m_cond);
    pthread_mutex_unlock(&thread->m_mutex);

    if(!thread->join())
    {
        pthread_mutex_lock(&thread->m_mutex);
        while(thread->m_alive)
        {
            pthread_cond_wait(&thread->m_cond,&thread->m_mutex);
        }
        pthread_mutex_unlock(&thread->m_mutex);
    }

    pthread_exit(NULL);
}


bool Thread::start()
{
    if(m_alive)
    {
        return false;
    }
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    if(!m_join)
    {
        pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    }
    bool ret = pthread_create(&m_id,&attr,Thread::process,this) == 0 ? true : false;
    pthread_attr_destroy(&attr);
    if(ret)
    {
        pthread_mutex_lock(&m_mutex);
        while(!m_alive)
        {
            pthread_cond_wait(&m_cond,&m_mutex);
        }
        pthread_mutex_unlock(&m_mutex);
    }
    return ret;
}

void Thread::sleep(const unsigned int sec)
{
    ::sleep(sec);
}

void Thread::msleep(const unsigned int msec)
{
    ::usleep(msec * 1000);
}

void Thread::usleep(const unsigned int msec)
{
    ::usleep(msec);
}
