#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#include "singleton.h"
#include <string>
class Thread : /*public SharedPtr* ,*/ private DisCopy
{
    private:
        pthread_t m_id;
        std::string m_name;
        bool m_complete;
        bool m_alive;
        bool m_join;
        pthread_mutex_t m_mutex;
        pthread_cond_t m_cond;
    public:
        Thread(const std::string &name,const bool join = true);
        virtual ~Thread()
        {
        }
        bool start();
        virtual void run() = 0;
        static void* process(void *arg);
        inline bool join()
        {
            return m_join;
        }
        inline bool isFinal()
        {
            return m_complete;
        }
        inline void final()
        {
            m_complete = true;
        }
        void sleep(const unsigned int sec);
        void usleep(const unsigned int msec);
        void msleep(const unsigned int msec);
        void end();
};

#endif


