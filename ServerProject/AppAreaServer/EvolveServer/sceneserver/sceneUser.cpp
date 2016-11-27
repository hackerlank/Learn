#include "sceneUser.h"
#include "clientManager.h"
#include "parseMessage.h"
#include "excelManager.h"
#include "login.pb.h"
#include "sceneTimeTick.h"
#include "excel.h"
#include "flyerMD5.h"
#include "redisMemManager.h"
#include "taskManager.h"

SceneUser::SceneUser(const unsigned long charID,const unsigned short gatewayID) : m_charID(charID),m_phone(),m_gatewayID(gatewayID),m_onTime(0),m_offTime(0)
{
    bzero(m_lastMD5,sizeof(m_lastMD5));
}

SceneUser::~SceneUser()
{
}

bool SceneUser::parseFromBinary(const ProtoMsgData::UserBinary &binary)
{
    bool ret = false;
    do
    {
        if(binary.charid() != m_charID)
        {
            Debug(Flyer::logger,"[登陆场景] 错误(" << binary.charid() << "," << m_charID << ")");
            break;
        }
        m_phone = binary.phone();
        m_onTime = binary.ontime();
        m_offTime = binary.offtime();
        ret = true;
    }while(false);
    return ret;
}

bool SceneUser::serializeToBinary(ProtoMsgData::UserBinary &binary)
{
    bool ret = false;
    do
    {
        binary.set_charid(m_charID);
        binary.set_phone(m_phone);
        binary.set_ontime(m_onTime);
        binary.set_offtime(m_offTime);
        ret = true;
    }while(false);
    return ret;
}

bool SceneUser::sendUserMsg(const google::protobuf::Message &message)
{
    bool ret = false;
    do
    {
        std::string msg;
        encodeMessage(&message,msg);
        ProtoMsgData::AckUserMsg ackMsg;
        ackMsg.set_charid(m_charID);
        ackMsg.set_data(msg);
        ret = sendGatewayMsg(ackMsg);
    }while(false);
    return ret;
}

bool SceneUser::sendGatewayMsg(const google::protobuf::Message &message)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<Connect> connect = TaskManager::getInstance().getServerTask(m_gatewayID);
        if(!connect)
        {
            break;
        }
        ret = connect->sendMsg(message);
    }while(false);
    return ret;
}

bool SceneUser::onLine()
{
    bool ret = false;
    do
    {
        if(!m_onTime)
        {
            if(!initAttr())
            {
                break;
            }
            m_onTime = SceneTimeTick::getInstance().s_time.sec();
        }
        ProtoMsgData::AckOnLine ackMsg;
        ret = sendUserMsg(ackMsg);     
    }while(false);
    return ret;
}

bool SceneUser::initAttr()
{
    bool ret = false;
    do
    {
        const ExcelConf::Conf_t_Init *init = ExcelTbx::Init().getBase(1);
        if(!init)
        {
            break;
        }
        const std::map<ProtoMsgData::AttrType,unsigned int> &attrMap = init->getAttrMap();
        for(auto iter = attrMap.begin();iter != attrMap.end();++iter)
        {
            m_attrMap.insert(std::pair<ProtoMsgData::AttrType,unsigned int>(iter->first,iter->second));
        }
        ret = true;
    }while(false);
    return ret;
}

unsigned int SceneUser::serializeToArray(char *array)
{
    ProtoMsgData::UserBinary binary;
    serializeToBinary(binary);
    binary.SerializeToArray(array,Flyer::msglen);
    return binary.ByteSize();
}

bool SceneUser::saveData(const bool force)
{
    MsgRet ret = MR_No_Register;
    do
    {
        bool saveFlg = true;
        char buffer[Flyer::msglen];
        bzero(buffer,sizeof(buffer));
        unsigned int size = serializeToArray(buffer);
        unsigned char md5[16];
        bzero(md5,sizeof(md5));
        Flyer::MD5Data(buffer,size,md5);
        if(!force)
        {
            if(!strncmp((const char*)md5,(const char*)m_lastMD5,sizeof(md5)))
            {
                saveFlg = false;
            }
            else
            {
                bcopy(md5,m_lastMD5,sizeof(md5));
            }
        }
       if(!saveFlg)
       {
           break;
       }
       ret = MR_False;
       boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis(m_charID);
       if(!redisMem)
       {
           break;
       }
       if(!redisMem->setBin("serialize",m_charID,"user",buffer,size))
       {
           break;
       }
       redisMem = RedisMemManager::getInstance().getRedis();
       if(!redisMem)
       {
           break;
       }
       if(!redisMem->setSet("serialize","userset",m_charID))
       {
           break;
       }
       ret = MR_True;
    }while(false);
    bool flag = ret == MR_False ? false : true;
    Info(Flyer::logger,"[角色信息存档] (" << (flag ? "成功" : "失败") << "," << m_charID << ")");
    return flag;
}
