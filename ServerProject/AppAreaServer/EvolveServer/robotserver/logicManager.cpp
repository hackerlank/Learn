#include "logicManager.h"
#include "flyer.h"
#include "robotTimeTick.h"
#include "clientManager.h"
#include "robotClient.h"
#include "login.pb.h"
#include <sstream>
#include "redisMemManager.h"
#include "excelManager.h"
#include "clientThread.h"

void LogicManager::notice()
{
    std::cout << "请输入GM指令:" << endl;
    std::cout << "cmd=ReqRegister(注册),phone=(手机号),num=(数量)" << endl;
}

void LogicManager::waitCmd()
{
    //char buffer[100];
    while(true)
    {
        ::usleep(atol(Flyer::globalConfMap["threadsleep"].c_str()) * 1000 * 10000);
#if 0
        bzero(buffer,sizeof(buffer));
        std::cin.sync();
        std::cin.clear();
        notice();
        do
        {
            std::cin.getline(buffer,sizeof(buffer));
            add(buffer);
        }while(!strlen(buffer));
        Debug(Flyer::logger,"[接受消息](" << buffer << ")");
#endif
    }
}

void LogicManager::loop()
{
    if(!m_cmdMap.empty())
    {
        Debug(Flyer::logger,"[消息批处理]开始(" << m_cmdMap.size() << "," << RobotTimeTick::getInstance().s_time.msec() << ")");
        std::vector<std::string> delVec;
        for(auto iter = m_cmdMap.begin();iter != m_cmdMap.end();++iter)
        {
            Debug(Flyer::logger,"[消息处理]开始(" << iter->first << "," << iter->second << "," << RobotTimeTick::getInstance().s_time.msec() << ")");
            bool ret = parseMsg(iter->first,iter->second);  
            iter->second -= 1;
            if(iter->second == 0)
            {
                delVec.push_back(iter->first);
            }
            Debug(Flyer::logger,"[消息处理]结束(" << iter->first <<  "," << iter->second << "," << ret << "," << RobotTimeTick::getInstance().s_time.msec() << ")");
        }
        for(auto iter = delVec.begin();iter != delVec.end();++iter)
        {
            m_cmdMap.erase(*iter);
        }
        Debug(Flyer::logger,"[消息批处理]结束(" << m_cmdMap.size() << "," << RobotTimeTick::getInstance().s_time.msec() << ")");
        //m_cmdMap.clear();
    }
}

void LogicManager::add(const std::string &cmd)
{
    do
    {
        std::map<std::string,std::string> cmdMap;
        ExcelConf::parseStringToStringMap(cmd,cmdMap,"=",",");
        if(cmdMap.empty())
        {
            break;
        }
        auto iter = cmdMap.find("cmd");
        if(iter == cmdMap.end())
        {
            break;
        }
        iter = cmdMap.find("num");
        unsigned int num = iter != cmdMap.end() ? atol(iter->second.c_str()) : 1;
        m_cmdMap.insert(std::pair<std::string,unsigned int>(cmd,num));
    }while(false);
}

bool LogicManager::parseMsg(const std::string &cmd,const unsigned int num)
{ 
    bool ret = false;
    do
    {
        std::map<std::string,std::string> cmdMap;
        ExcelConf::parseStringToStringMap(cmd,cmdMap,"=",",");
        if(cmdMap.empty())
        {
            break;
        }
        auto iter = cmdMap.find("cmd");
        if(iter == cmdMap.end())
        {
            break;
        }
        const std::string &cmdKey = iter->second;
        if(cmdKey.compare("ReqRegister") == 0)
        {
            ret = reqRegister(cmdMap,num);
        }
    }while(false);
    return ret;
}

bool LogicManager::reqRegister(const std::map<std::string,std::string>& cmdMap,const unsigned num)
{
    bool ret = false;
    do
    {
        std::string loginIp = Flyer::globalConfMap["loginip"];
        unsigned short loginPort = atol(Flyer::globalConfMap["loginport"].c_str());
        if(loginIp.empty() || !loginPort)
        {
            break;
        }
        auto iter = cmdMap.find("phone");
        if(iter == cmdMap.end())
        {
            break;
        }
        std::string phone = iter->second;
#if 0
        iter = cmdMap.find("num");
        unsigned int num = iter != cmdMap.end() ? atol(iter->second.c_str()) : 1;
#endif
        for(unsigned int cnt = num;cnt <= num;++cnt)
        {
            bool flag = false;
            ProtoMsgData::ReqRegister cmd;
            std::ostringstream oss;
            oss << phone << "_" << cnt;
            cmd.set_phone(oss.str());
            cmd.set_passwd(cmd.phone());
            do
            {
                boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
                if(!redisMem)
                {
                    break;
                }
                std::string getPasswd = redisMem->getString("register",cmd.phone().c_str());
                int fd = -1;
                if(!Client::connectOwner(fd,loginIp,loginPort))
                {
                    break;
                }
                boost::shared_ptr<RobotClient> client(new RobotClient("客户端",loginIp,loginPort,fd));
                if(!ClientManager::getInstance().add(client))
                {
                    break;
                }
                if(!ClientThread::getInstance().add(client->getID()))
                {
                    break;
                }
                client->setPhone(cmd.phone());
                if(!getPasswd.empty())
                {
                    ProtoMsgData::ReqGateway reqMsg;
                    reqMsg.set_phone(cmd.phone());
                    reqMsg.set_passwd(cmd.phone());
                    flag = client->sendMsg(reqMsg);
                }
                else
                {
                    flag = client->sendMsg(cmd);
                }
            }while(false);
            Info(Flyer::logger,"[注册类](" << flag << "," << cmd.phone() << ")");
        }
        ret = true;
    }while(false);
    return ret; 
}

