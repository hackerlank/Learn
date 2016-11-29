#include "TitleManager.h"
#include "Tokenizer.h"
#include "Player.h"
CTitleManager g_CTitleManager;
bool CTitleManager::Init()
{

    _mapCfg.clear();
    CTitleLoader oTitleLoader;
    string strPath = Config._strConfigDir + "Conf/Table/Title.xml";
    if(!oTitleLoader.LoadData(strPath))
    {
        LOG_CRI << "Load " << strPath << "ERR";
        return false;
    }

    for(auto iter = oTitleLoader._vecData.begin(); iter != oTitleLoader._vecData.end();iter++)
    {
        STitleCFG cFg(*(*iter));
        if(cFg._Type ==0 || cFg._Type >= Etitle_Max)
        {
            LOG_CRI <<"ERR Type";
        }
        if(!_mapCfg.insert(make_pair(cFg._ID,cFg)).second)
        {
            LOG_CRI << "RepeatId"; 
            return false;
        }
    }
    return true;
}

const STitleCFG * CTitleManager::GetCFGbyId(UINT16 wId)
{
    auto it = _mapCfg.find(wId);
    if(it == _mapCfg.end())
    {
        return NULL;
    }
    return &(it->second);
}

void CTitleManager::FinishAchievement(CPlayer & rPlayer,UINT16 wId){
    UINT16 wTitle =0 ;
    for(auto it = _mapCfg.begin();it != _mapCfg.end();it++)
    {
        STitleCFG& rCfg = it->second;
        if(rCfg._RequireID == wId)
        {
            wTitle = it->first;
            break;
        }
    }
    if(wTitle != 0)
    {
        rPlayer.GetTitlePkg().AddTitle(wTitle);
    }
}
