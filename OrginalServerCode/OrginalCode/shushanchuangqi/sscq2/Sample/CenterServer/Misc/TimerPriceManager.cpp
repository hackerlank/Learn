#include "TimerPriceManager.h"
#include "CenterConfig.h"
#include "stdafx.h"
TimesPriceManager g_TimesPriceManager;
bool TimesPriceManager::Init()
{
    _mapTimesPriceCFG.clear();
    string strPath = Config._strConfigDir + "Conf/Table/TimesPrice.xml";
    CTimesPriceLoader oTimesPriceLoader;
    if(!oTimesPriceLoader.LoadData(strPath))
    {
        LOG_CRI << "ERR Load" << strPath;
        return false;
    }
    for(size_t it =0 ; it != oTimesPriceLoader._vecData.size();it++)
    {
        STimesPriceCFG &rCfg = *(oTimesPriceLoader._vecData[it]);
        if(!_mapTimesPriceCFG.insert(make_pair(rCfg._BoughtTimes,rCfg)).second)
        {
            LOG_CRI << "Repeat Load" << strPath; 
            return false;
        }

    }
    return true;
}

const STimesPriceCFG* TimesPriceManager::GetConfigByTimes(UINT32 dwTimes)
{
    if(_mapTimesPriceCFG.empty())
    {
        return NULL;
    }
    auto it = _mapTimesPriceCFG.find(dwTimes);
    if(it !=  _mapTimesPriceCFG.end())
    {
        return &(it->second);
    }
    return &(_mapTimesPriceCFG.rbegin()->second);
}
