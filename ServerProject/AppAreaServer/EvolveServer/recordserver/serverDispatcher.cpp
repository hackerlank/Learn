#include "recordServer.h"
#include "recordDataManager.h"

ServerMessageDispatcher RecordServer::s_serverMsgDispatcher("档案服务器消息处理器");
MsgRet RecordServer::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_No_Register;
    do
    {
        ret = s_serverMsgDispatcher.dispatch(getInstance(),message);
    }while(false);
    return ret;
}

bool RecordServer::reqCreateUser(boost::shared_ptr<ProtoMsgData::ReqCreateUser> message)
{
    bool ret = false;
    unsigned long charID = 0;
    do
    {
        if(!RecordDataManager::getInstance().createUser(message->phone(),charID))
        {
            break;
        }
        ret = true;
    }while(false);
    ProtoMsgData::AckCreateUser ackMsg;
    ackMsg.set_code(ret ? ProtoMsgData::EC_Default : ProtoMsgData::EC_Create_Role);
    ackMsg.set_phone(message->phone());
    ackMsg.set_charid(charID);
    ackMsg.set_id(message->id());
    ret = m_superClient->sendMsg(ackMsg);
    return ret;
}
