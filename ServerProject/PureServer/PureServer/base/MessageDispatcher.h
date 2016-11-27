#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H

template <typename T>
class MessageDispatcher
{
    private:
        typedef boost::function<bool,<T,boost::shared_ptr<google::protobuf::Message> > > CallBack;
        std::map<const google::protobuf::Descriptor*,CallBack> m_callMap;
        std::string m_name;
    public:
        MessageDispatcher(const std::string name) : m_name(name)
        {
        }

        ~MessageDispatcher()
        {
        }

        bool messageReg(boost::shared_ptr<google::protobuf::Message> mesaage,CallBack callBack)
        {
            if(m_callMap.find(mesaage->GetDescriptor()) == m_callMap.end())
            {
                return false;
            }
            m_callMap.insert(std::pair<const google::protobuf::Descriptor*,CallBack> >(mesaage->GetDescriptor(),callBack));
            return true;
        }

        bool dispatch(T,boost::shared_ptr<google::protobuf::Message> message)
        {
            auto iter = m_callMap.find(mesaage->GetDescriptor());
            if(iter == m_callMap.end())
            {
                return false;
            }
            return iter->second(T,message);
        }
};

#endif



