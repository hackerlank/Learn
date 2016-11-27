#include "cmdFunManager.h"
#include "dataManager.h"
#include "key.h"

CmdFunManager::CmdFunManager()
{
}
CmdFunManager::~CmdFunManager()
{
}

bool CmdFunManager::loadCmd(const Fir::XMLParser &cmdXml)
{
    const Fir::XMLParser::Node *root = cmdXml.root();
    if(!root)
    {
        Fir::logger->error("[加载指令配置]:错误,没有根节点");
        return false;
    }
    
    const Fir::XMLParser::Node *registNode = cmdXml.child(root, "RegisterProto");
    if(!registNode)
    {
        Fir::logger->error("[加载指令配置]:错误,没有RegisterProto节点");
        return false;
    }
    const Fir::XMLParser::Node *tempNode = cmdXml.child(registNode); 
    while(tempNode)
    {
        if(!tempNode || !cmdXml.has_attribute(tempNode,"value"))
        {
            Fir::logger->error("[加载指令配置]:错误,%s 没有属性value",tempNode->name);
        }
        WORD logicID = (WORD)cmdXml.node_attribute(tempNode,"value");
        const Fir::XMLParser::Node *node = cmdXml.child(tempNode);
        while(node)
        {
            if(!node || !cmdXml.has_attribute(node,"value") || !cmdXml.has_attribute(node,"proto"))
            {
                Fir::logger->debug("[加载指令配置]:错误,%s逻辑节点%s节点没有value或者proto属性",tempNode->name,node->name);
                continue;
            }
            WORD cmdID = (WORD)cmdXml.node_attribute(node,"value");
            std::string protoName = (const char*)cmdXml.node_attribute(node,"proto");
            DWORD cmdKey = hashKey(logicID,cmdID);
            m_cmdProtoNameMap.insert(std::pair<DWORD,std::string>(cmdKey,protoName));
            m_protoNameCmdMap.insert(std::pair<std::string,DWORD>(protoName,cmdKey));
            node = cmdXml.next(node);
        }
        tempNode = cmdXml.next(tempNode);
    }
    return true;
}

DWORD CmdFunManager::getCmd(const std::string &protoName)
{
    return m_protoNameCmdMap.find(protoName) == m_protoNameCmdMap.end() ? 0 : m_protoNameCmdMap[protoName];
}

std::string CmdFunManager::getProtoName(const DWORD cmdKey)
{
    return m_cmdProtoNameMap.find(cmdKey) == m_cmdProtoNameMap.end() ? "" : m_cmdProtoNameMap[cmdKey];
}

void CmdFunManager::logCmdMap() const
{
    Fir::logger->debug("Test the CmdFunMap begin");
    Fir::logger->debug("Test the cmdProtoNameMap begin (%lu)",m_cmdProtoNameMap.size());
    size_t cnt = 0;
    for(auto iter = m_cmdProtoNameMap.begin();iter != m_cmdProtoNameMap.end();++iter)
    {
        DWORD cmdKey = iter->first;
        const std::string &protoName = iter->second;
        Fir::logger->debug("%u,%s",cmdKey,protoName.c_str());
        ++cnt;
    }
    Fir::logger->debug("Test the cmdProtoNameMap end (%lu)",cnt);
    Fir::logger->debug("Test the protoNameCmdMap begin (%lu)",m_protoNameCmdMap.size());
    cnt = 0;
    for(auto iter = m_protoNameCmdMap.begin();iter != m_protoNameCmdMap.end();++iter)
    {
        const std::string &protoName = iter->first;
        DWORD cmdKey = iter->second;
        Fir::logger->debug("%s,%u",protoName.c_str(),cmdKey);
        ++cnt;
    }
    Fir::logger->debug("Test the protoNameCmdMap end (%lu)",cnt);
    Fir::logger->debug("Test the CmdFunMap end");
}
