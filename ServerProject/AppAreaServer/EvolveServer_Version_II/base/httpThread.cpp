#include "httpThread.h"
#include "flyer.h"

bool HttpThread::add(const HttpReq &req)
{
    std::pair<std::map<unsigned long,HttpReq>::iterator,bool> ret = m_httpReqMap.insert(std::pair<unsigned long,HttpReq>(req.m_id,req));
    return ret.second;
}

void HttpThread::checkSet()
{
    pthread_mutex_lock(&m_mutex);
    for(auto iter = m_httpReqMap.begin();iter != m_httpReqMap.end();++iter)
    {
        m_idSet.insert(iter->first);
    }
    pthread_mutex_unlock(&m_mutex);
}

void HttpThread::run()
{
    while(!isFinal())
    {
        checkSet();
        for(auto iter = m_idSet.begin();iter != m_idSet.end();++iter)
        {
            auto itr = m_httpReqMap.find(*iter);
            if(itr == m_httpReqMap.end())
            {
                continue;
            }
            const HttpReq &req = itr->second;
            m_client.initUrl(req.m_url);
            if(req.getType() == HRT_Post)
            {
                if(m_client.post(m_retData,req.m_data))
                {
                }
            }
            else
            {
                if(m_client.get(m_retData,req.m_data))
                {
                }
            }
        }
        for(auto iter = m_idSet.begin();iter != m_idSet.end();++iter)
        {
            m_httpReqMap.erase(*iter);
        }
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));       
    }
}
