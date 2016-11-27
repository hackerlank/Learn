#ifndef MESSAGE_QUEUQ_H
#define MESSAGE_QUEUE_H
#include "thread.h"
#include "head.h"

struct MessageData
{
    unsigned int key;
    unsigned int size;
    unsigned char data[0]; 
    MessageData()
    {
        key = 0;
        size = 0;
    }
};

class MessageQueue
{
    private:
        std::list<boost::shared_ptr<MessageData> > m_messageList;
        pthread_mutex_t m_mutex;
    public:
        MessageQueue();
        virtual ~MessageQueue();
        void putMessage(boost::shared_ptr<MessageData> messageData);
        boost::shared_ptr<MessageData> getMessage();
        bool empty() const;
};

class MessageBuffer
{
    private:
        static const unsigned int s_MessageBufferMax = 10240;
        unsigned int m_readPos;
        unsigned int m_writePos;
        std::vector<unsigned char> m_buffer;
        pthread_mutex_t m_mutex;
    public:
        MessageBuffer();
        virtual ~MessageBuffer();
        unsigned char* beginWrite();
        void moveWritePos(unsigned int size);
        bool adjustPos(unsigned int size = 1000);
        unsigned int ableWriteSize();
        bool beginRead(MessageData *messageData);

};

#endif
