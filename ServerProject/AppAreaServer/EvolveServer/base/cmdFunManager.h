#ifndef CMD_FUN_MANAGER_H
#define CMD_FUN_MANAGER_H

#include "flyerXmlParse.h"
#include "singleton.h"
#include "flyer.h"
#include <map>

class CmdFunManager : public Singleton<CmdFunManager>
{
    private:
        std::map<unsigned int,std::string> m_cmdProtoNameMap;
        std::map<std::string,unsigned int> m_protoNameCmdMap;
    private:
        friend class Singleton<CmdFunManager>;
        CmdFunManager();
        ~CmdFunManager();
    public:
        bool loadCmd(const char *fileName);
        unsigned int getCmd(const std::string &protoName);
        std::string getProtoName(const unsigned int cmd);
        void logCmdMap() const;

};
#endif

