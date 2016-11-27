#ifndef LOGIC_MANAGER_H
#define LOGIC_MANAGER_H 
#include "singleton.h"
#include "head.h"

class LogicManager : public Singleton<LogicManager>
{
    private:
        friend class Singleton<LogicManager>;
        LogicManager()
        {
        }
        ~LogicManager()
        {
        }
    public:
        void loop();
        void add(const std::string &cmd);
        void waitCmd();
    private:
        void notice();
        bool parseMsg(const std::string &cmd,const unsigned int cnt);
        bool reqRegister(const std::map<std::string,std::string>& cmdMap,const unsigned int cnt);
    private:
        std::map<std::string,unsigned int> m_cmdMap;
};

#endif


