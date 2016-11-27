#include "messageHandle.h"
#include "flyer.h"

MessageHandle::MessageHandle(const std::string &name) : m_name(name)
{
}

MessageHandle::~MessageHandle()
{
}

bool MessageHandle::init()
{
    return true;
}

const std::string MessageHandle::getName() const
{
    return m_name;
}

MessageHandleManager::MessageHandleManager()
{
}

MessageHandleManager::~MessageHandleManager()
{
}

void MessageHandleManager::addHandle(boost::shared_ptr<MessageHandle> handle)
{
    m_handleVec.push_back(handle);
}

bool MessageHandleManager::init()
{
    for(auto iter = m_handleVec.begin();iter != m_handleVec.end();++iter)
    {
        boost::shared_ptr<MessageHandle> handle = *iter;
        if(!handle->init())
        {
            Error(Flyer::logger,"[消息处理句柄] 错误(" << handle->getName() << ")");
            return false;
        }
    }
    return true;
}

