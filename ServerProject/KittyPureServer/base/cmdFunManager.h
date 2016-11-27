#ifndef CMD_FUN_MANAGER_H
#define CMD_FUN_MANAGER_H

#include "xmlparser.h"
#include <map>

class CmdFunManager : public Singleton<CmdFunManager>
{
    private:
        std::map<DWORD,std::string> m_cmdProtoNameMap;
        std::map<std::string,DWORD> m_protoNameCmdMap;
    private:
        friend class Singleton<CmdFunManager>;
        CmdFunManager();
        ~CmdFunManager();
    public:
        bool loadCmd(const Fir::XMLParser &cmdXml);
        DWORD getCmd(const std::string &protoName);
        std::string getProtoName(const DWORD cmd);
        void logCmdMap() const;

};
#endif

