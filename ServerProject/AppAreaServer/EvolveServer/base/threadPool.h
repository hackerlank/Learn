#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include "singleton.h"
#include "verifyThread.h"
#include "mainThread.h"
#include "recycleThread.h"

class ThreadPool : public Singleton<ThreadPool>
{
    private:
        friend class Singleton<ThreadPool>;
        ThreadPool();
        ~ThreadPool();
    private:
        std::map<unsigned int,boost::shared_ptr<VerifyThread> >m_verifyThreadMap;
        std::map<unsigned int,boost::shared_ptr<MainThread> >m_mainThreadMap;
        std::map<unsigned int,boost::shared_ptr<RecycleThread> >m_recycleThreadMap;
        std::map<unsigned long,unsigned int> m_verifyMap;
        std::map<unsigned long,unsigned int> m_mainMap;
        std::map<unsigned long,unsigned int> m_recycleMap;
        static unsigned int s_id;
    public:
        bool init();
        bool addVerify(const unsigned long id);
        bool addMain(const unsigned long id);
        bool addRecycle(const unsigned long id);
        bool addMainFromVerify(const unsigned long id);
        bool addRecycleFromMain(const unsigned long id);
        void delFromVefiry(const unsigned long id);
        void delFromMain(const unsigned long id);
        void delFromRecycle(const unsigned long id);
        bool addRecycleFromVerify(const unsigned long id);
        void final();
        void start();
        void print();

};


#endif
