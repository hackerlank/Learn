#include "cmdFunManager.h"
#include "key.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/typeof/typeof.hpp>

CmdFunManager::CmdFunManager()
{
}
CmdFunManager::~CmdFunManager()
{
}

bool CmdFunManager::loadCmd(const char *fileName)
{
    bool ret = false;
    do
    {
        using namespace boost::property_tree;
        ptree tree;
        read_xml(fileName,tree);
        ptree child = tree.get_child("protocol.RegisterProto");
        for(auto iter = child.begin();iter != child.end();++iter)
        {
            if(iter->first == "<xmlattr>" || iter->first == "<xmlcomment>")
            {
                continue;
            }
            std::string temp = iter->second.get<std::string>("<xmlattr>.value");
            unsigned short logicID = atol(temp.c_str());
            for(auto itr = iter->second.begin();itr != iter->second.end();++itr)
            {
                if(itr->first == "<xmlattr>" || itr->first == "<xmlcomment>")
                {
                    continue;
                }
                std::string protoName = Flyer::globalConfMap["namespace"];
                protoName += ".";
                protoName += itr->second.get<std::string>("<xmlattr>.proto");
                string temp = itr->second.get<std::string>("<xmlattr>.value");
                unsigned short cmdID = atol(temp.c_str());
                unsigned int cmdKey = hashKey(logicID,cmdID);
                m_cmdProtoNameMap.insert(std::pair<unsigned int,std::string>(cmdKey,protoName));
                m_protoNameCmdMap.insert(std::pair<std::string,unsigned int>(protoName,cmdKey));

            }

        }
        ret = true;
    }while(false);
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"[加载指令] %s:%s",ret ? "成功" : "失败",fileName);
    Info(Flyer::logger,temp);
    return ret;
}

unsigned int CmdFunManager::getCmd(const std::string &protoName)
{
    return m_protoNameCmdMap.find(protoName) == m_protoNameCmdMap.end() ? 0 : m_protoNameCmdMap[protoName];
}

std::string CmdFunManager::getProtoName(const unsigned int cmdKey)
{
    return m_cmdProtoNameMap.find(cmdKey) == m_cmdProtoNameMap.end() ? "" : m_cmdProtoNameMap[cmdKey];
}

void CmdFunManager::logCmdMap() const
{
    Debug(Flyer::logger,"[指令] 测试开始");
    Debug(Flyer::logger,"[指令] 测试cmdProtoNameMap开始(" << m_cmdProtoNameMap.size() << ")");
    size_t cnt = 0;
    for(auto iter = m_cmdProtoNameMap.begin();iter != m_cmdProtoNameMap.end();++iter)
    {
        unsigned int cmdKey = iter->first;
        const std::string &protoName = iter->second;
        Debug(Flyer::logger,"[指令] 测试cmdKey,protoName(" << cmdKey << "," << protoName << ")");
        ++cnt;
    }
    Debug(Flyer::logger,"[指令] 测试cmdProtoNameMap结束(" << cnt << ")");
    Debug(Flyer::logger,"[指令] 测试protoNameCmdMap开始(" << m_protoNameCmdMap.size() << ")");
    cnt = 0;
    for(auto iter = m_protoNameCmdMap.begin();iter != m_protoNameCmdMap.end();++iter)
    {
        const std::string &protoName = iter->first;
        unsigned int cmdKey = iter->second;
        Debug(Flyer::logger,"[指令] 测试protoName,cmdKey(" << cmdKey << "," << protoName << ")");
        ++cnt;
    }
    Debug(Flyer::logger,"[指令] 测试protoNameCmdMap结束(" << cnt << ")");
    Debug(Flyer::logger,"[指令] 测试开始");
}
