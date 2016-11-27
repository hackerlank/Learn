#ifndef HTTP_THREAD_H
#define HTTP_THREAD_H
#include "thread.h"
#include "httpClient.h"

class HttpThread : public Thread,public Singleton<HttpThread>
{
    private:
        friend class Singleton<HttpThread>;
        HttpThread() : Thread("http处理线程"),m_client()
        {
            m_client.initCurl();
            pthread_mutex_init(&m_mutex,NULL);
        }
        ~HttpThread()
        {
        }
        void checkSet();
    private:
        std::map<unsigned long,HttpReq> m_httpReqMap;
        std::set<unsigned long> m_idSet;
        HttpClient m_client;
        std::string m_retData;
        pthread_mutex_t m_mutex;
    public:
        bool add(const HttpReq &req);
        virtual void run();
};
#endif
