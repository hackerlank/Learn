#include "messageQueue.h"

MessageQueue::MessageQueue()
{
    pthread_mutex_init(&m_mutex,NULL);
}

MessageQueue::~MessageQueue()
{
    m_messageList.clear();
}

void MessageQueue::putMessage(boost::shared_ptr<MessageData> messageData)
{
    pthread_mutex_lock(&m_mutex);
    m_messageList.push_back(messageData);
    pthread_mutex_unlock(&m_mutex);
}

boost::shared_ptr<MessageData> MessageQueue::getMessage()
{
    pthread_mutex_lock(&m_mutex);
    boost::shared_ptr<MessageData> ret = m_messageList.front();
    m_messageList.pop_front();
    pthread_mutex_unlock(&m_mutex);
    return ret;
}

bool MessageQueue::empty() const
{
    return m_messageList.empty();
}

MessageBuffer::MessageBuffer() : m_readPos(0),m_writePos(0),m_buffer(s_MessageBufferMax)
{
    pthread_mutex_init(&m_mutex,NULL);
}

MessageBuffer::~MessageBuffer()
{
    m_buffer.clear();
}

bool MessageBuffer::beginRead(MessageData *messageData)
{
    bool ret = false;
    pthread_mutex_lock(&m_mutex);
    do
    {
        if(!messageData)
        {
            break;
        }
        unsigned int len = *(unsigned int*)(&m_buffer[m_readPos]);
        if(!len || len > m_writePos - m_readPos)
        {
            break;
        }
        unsigned int offset = sizeof(unsigned int);
        unsigned int key = *(unsigned int*)(&m_buffer[m_readPos+offset]);
        offset += sizeof(unsigned int);
        messageData->key = key;
        messageData->size = len - offset; 
        if(messageData->size)
        {
            bcopy((void*)(&m_buffer[m_readPos+offset]),(void*)(&messageData->data[0]),messageData->size);
        }
        m_readPos += len;
        ret = true;
    }while(false);
    pthread_mutex_unlock(&m_mutex);
    return ret;
}

unsigned char* MessageBuffer::beginWrite()
{
    pthread_mutex_lock(&m_mutex);
    unsigned char *ptr = &m_buffer[m_writePos];
    pthread_mutex_unlock(&m_mutex);
    return ptr;
}

void MessageBuffer::moveWritePos(unsigned int size)
{
    pthread_mutex_lock(&m_mutex);
    m_writePos += size;
    pthread_mutex_unlock(&m_mutex);
}

bool MessageBuffer::adjustPos(unsigned int size)
{
    bool adjust = s_MessageBufferMax - m_writePos < m_readPos ? true : false;
    adjust = adjust ? true : (s_MessageBufferMax - m_writePos < size ?  true : false);
    if(adjust && m_readPos)
    {
        pthread_mutex_lock(&m_mutex);
        memmove(&m_buffer[0],&m_buffer[m_readPos],m_writePos - m_readPos);
        m_writePos -= m_readPos; 
        m_readPos = 0;
        pthread_mutex_unlock(&m_mutex);
    }
    return s_MessageBufferMax - m_writePos > size;
}
        
unsigned int MessageBuffer::ableWriteSize()
{
    pthread_mutex_lock(&m_mutex);
    unsigned int size = s_MessageBufferMax - m_writePos;
    pthread_mutex_unlock(&m_mutex);
    return size;
}



