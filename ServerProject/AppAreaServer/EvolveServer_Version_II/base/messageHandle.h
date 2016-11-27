#ifndef MESSAGE_HANDLE_H
#define MESSAGE_HANDLE_H
#include "head.h"
#include "singleton.h"
class MessageHandle
{
    private:
        std::string m_name;
    public:
        MessageHandle(const std::string &name);
        virtual ~MessageHandle();
        virtual bool init() = 0;
        const std::string getName() const;
};



class MessageHandleManager : public Singleton<MessageHandleManager>
{
    private:
        std::vector<boost::shared_ptr<MessageHandle> >m_handleVec;
    private:
        friend class Singleton<MessageHandleManager>;
        MessageHandleManager();
        ~MessageHandleManager();
    public:
        bool init();
        void addHandle(boost::shared_ptr<MessageHandle> handle);
};

#endif
