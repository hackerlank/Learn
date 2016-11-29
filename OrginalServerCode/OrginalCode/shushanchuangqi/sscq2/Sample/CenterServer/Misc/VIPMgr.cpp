#include "stdafx.h"
#include "Protocols.h"
#include "VIPMgr.h"
#include "VIPProt.h"
#include "Version.h"

UINT64 CVIPMgr::_qwVersion = VERSION_INIT;
map<UINT8, SVIPLevelCFGEx> CVIPMgr::_mapID2VIPLevelCFG;

bool CVIPMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/VIPLevel.xml";
    CVIPLevelLoader oVIPLevelLoader;
    if(!oVIPLevelLoader.LoadData(strPath))
    {
        LOG_CRI << "oVIPLevelLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oVIPLevelLoader._vecData.size(); ++i)
    {
        SVIPLevelCFG* pVIPLevelCFG = oVIPLevelLoader._vecData[i];
        SVIPLevelCFGEx& rVIPLevelCFGEx = _mapID2VIPLevelCFG[pVIPLevelCFG->_Level];
        rVIPLevelCFGEx.SetConfig(*pVIPLevelCFG);

    }

    return true;
}

bool CVIPMgr::ReLoadConfig(const string &strFile)
{
    string strPath;
    if("VIPLevel.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/VIPLevel.xml";
        CVIPLevelLoader oVIPLevelLoader;
        if(!oVIPLevelLoader.LoadData(strPath))
        {
            LOG_CRI << "oVIPLevelLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oVIPLevelLoader._vecData.size(); ++i)
        {
            SVIPLevelCFG* pVIPLevelCFG = oVIPLevelLoader._vecData[i];
            SVIPLevelCFGEx& rVIPLevelCFGEx = _mapID2VIPLevelCFG[pVIPLevelCFG->_Level];
            rVIPLevelCFGEx.SetConfig(*pVIPLevelCFG);

        }
    }
    return true;
}

SVIPLevelCFGEx* CVIPMgr::GetVIPLevelCfg(UINT8 byLvl)
{
    auto it = _mapID2VIPLevelCFG.find(byLvl);
    if(it != _mapID2VIPLevelCFG.end())
        return &it->second;
    return NULL;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

