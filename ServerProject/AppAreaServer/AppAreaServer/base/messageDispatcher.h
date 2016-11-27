#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H
#include "head.h"
#include "singleton.h"

enum MsgRet
{
    MR_No_Register = -1, //没找到处理函数
    MR_False = 0, //处理结果为false
    MR_True = 1, //处理结果为true
};

template<typename T>
class CallBack/* : public DisCopy*/
{
    public:
        virtual ~CallBack()
        {
        }
        virtual bool exec(T owner,boost::shared_ptr<google::protobuf::Message> msg) = 0;
};

template<typename T,typename ProtoMsg>
class MsgCallBack : public CallBack<T> 
{
    private:
        boost::function<bool (T,boost::shared_ptr<ProtoMsg>)> m_func;
    public:
        MsgCallBack(boost::function<bool (T,boost::shared_ptr<ProtoMsg>)> func) : m_func(func)
        {
        }
        virtual bool exec(T owner,boost::shared_ptr<google::protobuf::Message> msg)
        {
            if(msg)
            {
                boost::shared_ptr<ProtoMsg> message = boost::dynamic_pointer_cast<ProtoMsg>(msg);
                return m_func(owner,message);
            }
            return false;
        }
};


template <typename T>
class MessageDispatcher
{
    private:
        std::map<const google::protobuf::Descriptor*,boost::shared_ptr<CallBack<T> > >m_callMap;
        std::string m_name;
    public:
        MessageDispatcher(const std::string name) : m_name(name)
        {
        }

        ~MessageDispatcher()
        {
        }
        
        template <typename ProtoMsg>
        bool messageReg(boost::shared_ptr<MsgCallBack<T,ProtoMsg> >callBack)
        {
            if(m_callMap.find(ProtoMsg::descriptor()) != m_callMap.end())
            {
                return false;
            }
            m_callMap.insert(std::pair<const google::protobuf::Descriptor*,boost::shared_ptr<CallBack<T> > >(ProtoMsg::descriptor(),callBack));
            return true;
        }

        MsgRet dispatch(T owner,boost::shared_ptr<google::protobuf::Message> message)
        {
            MsgRet ret = MR_No_Register;
            do
            {
                auto iter = m_callMap.find(message->GetDescriptor());
                if(iter == m_callMap.end())
                {
                    break;
                }
                bool flag = iter->second->exec(owner,message);
                ret = flag ? MR_True : MR_False;
            }while(false);
            return ret;
        }
};

#endif



