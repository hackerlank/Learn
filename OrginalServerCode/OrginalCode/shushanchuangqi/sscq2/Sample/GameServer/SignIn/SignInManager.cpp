#include "SignInManager.h"
#include "Tokenizer.h"
#include "Player.h"
#include "Tokenizer.h" 
CSignInManager g_CSignInManager;
SSignInCFGEx::SSignInCFGEx(const SSignInCFG& other):SSignInCFG(other)
{
}
bool CSignInManager::Init()
{

    CSignInLoader oSignInLoader;
    string strPath = Config._strConfigDir + "Conf/Table/SignIn.xml";
    if(!oSignInLoader.LoadData(strPath))
    {
        LOG_CRI << "Load " << strPath << "ERR";
        return false;
    }
    _mapCfg.clear();
    for(auto iter = oSignInLoader._vecData.begin(); iter != oSignInLoader._vecData.end();iter++)
    {
        SSignInCFGEx cFg(*(*iter));
        if(cFg._ID ==0 || cFg._ID > 24)
        {
            LOG_CRI <<"SignIn.xml ERR ID";
            return false;
        }
        buf::Tokenizer tkAward(cFg._Award, '|');
        if(tkAward.size() == 0)
        {
            LOG_CRI <<"SignIn.xml empty award";
            return false;
        }
        for (size_t i = 0 ; i< tkAward.size();++i)
        {
            buf::Tokenizer tksubAward(tkAward[i],',');
            if(tksubAward.size() != 2)
            {
                LOG_CRI <<"SignIn.xml err award";    
                return false;   
            }
            UINT16 wItem = atoi(tksubAward[0].c_str());
            UINT32 dwNum = atoi(tksubAward[1].c_str());
            if(wItem == 0 || dwNum == 0)
            {
                LOG_CRI <<"SignIn.xml err award"; 
                return false;
            }
            cFg.mapAward[wItem] = dwNum;
        }

        if(!_mapCfg.insert(make_pair(cFg._ID,cFg)).second)
        {
            LOG_CRI << "RepeatId"; 
            return false;
        }
    }
    return true;
}

const SSignInCFGEx * CSignInManager::GetCFGbyId(UINT16 wId)
{
    auto it = _mapCfg.find(wId);
    if(it == _mapCfg.end())
    {
        return NULL;
    }
    return &(it->second);
}

