#include "stdafx.h"
#include "Protocols.h"
#include "VIPMgr.h"
#include "VIPProt.h"
#include "Version.h"
#include "Tokenizer.h"

UINT64 CVIPMgr::_qwVersion = VERSION_INIT;
map<UINT8, SVIPLevelCFGEx> CVIPMgr::_mapID2VIPLevelCFG;
map<UINT8, SVIPBaseCFGEx> CVIPMgr::_mapID2VIPBaseCFG;

bool CVIPMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/VIPLevel.xml";
    CVIPLevelLoader oVIPLevelLoader;
    if(!oVIPLevelLoader.LoadData(strPath))
    {
        LOG_CRI << "oVIPLevelLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    _vecRecharge.clear();
    for(size_t i = 0; i < oVIPLevelLoader._vecData.size(); ++i)
    {
        SVIPLevelCFG* pVIPLevelCFG = oVIPLevelLoader._vecData[i];
        SVIPLevelCFGEx& rVIPLevelCFGEx = _mapID2VIPLevelCFG[pVIPLevelCFG->_Level];
        rVIPLevelCFGEx.SetConfig(*pVIPLevelCFG);

        if (pVIPLevelCFG->_Level > 0)
            _vecRecharge.push_back(pVIPLevelCFG->_Exp);

        Tokenizer tk(rVIPLevelCFGEx._DayPack, "|");
        for (size_t j = 0; j < tk.size(); ++ j)
        {
            Tokenizer yatk(tk[j], ",");
            UINT32 dwItemID = atoi(yatk[0].c_str());
            if (!dwItemID)
                continue;
            SItemGenInfo stItemGen;
            if (yatk.size() > 1)
                stItemGen.dwCount = atoi(yatk[1].c_str());
            else
                stItemGen.dwCount = 1;
            stItemGen.wItemID = dwItemID;
            stItemGen.eBindType = eBindGet;
            rVIPLevelCFGEx._vecItemDayPack.push_back(stItemGen);
        }
        Tokenizer tk1(rVIPLevelCFGEx._Award, "|");
        for (size_t j = 0; j < tk1.size(); ++ j)
        {
            Tokenizer yatk(tk1[j], ",");
            UINT32 dwItemID = atoi(yatk[0].c_str());
            if (!dwItemID)
                continue;
            SItemGenInfo stItemGen;
            if (yatk.size() > 1)
                stItemGen.dwCount = atoi(yatk[1].c_str());
            else
                stItemGen.dwCount = 1;
            stItemGen.wItemID = dwItemID;
            stItemGen.eBindType = eBindGet;
            rVIPLevelCFGEx._vecItemLevelAward.push_back(stItemGen);
        }
    }

    strPath = Config._strConfigDir + "Conf/Table/VIPBase.xml";
    CVIPBaseLoader oVIPBaseLoader;
    if(!oVIPBaseLoader.LoadData(strPath))
    {
        LOG_CRI << "oVIPBaseLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oVIPBaseLoader._vecData.size(); ++i)
    {
        SVIPBaseCFG* pVIPBaseCFG = oVIPBaseLoader._vecData[i];
        if(pVIPBaseCFG->_ID == 0)
            continue;
        SVIPBaseCFGEx& rVIPBaseCFGEx = _mapID2VIPBaseCFG[pVIPBaseCFG->_ID];
        rVIPBaseCFGEx.SetConfig(*pVIPBaseCFG);
    }

    return true;
}

bool CVIPMgr::LoadConfig(const string &strFile)
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
        _vecRecharge.clear();
        for(size_t i = 0; i < oVIPLevelLoader._vecData.size(); ++i)
        {
            SVIPLevelCFG* pVIPLevelCFG = oVIPLevelLoader._vecData[i];
            SVIPLevelCFGEx& rVIPLevelCFGEx = _mapID2VIPLevelCFG[pVIPLevelCFG->_Level];
            rVIPLevelCFGEx.SetConfig(*pVIPLevelCFG);

            if (pVIPLevelCFG->_Level > 0)
                _vecRecharge.push_back(pVIPLevelCFG->_Exp);

            Tokenizer tk(rVIPLevelCFGEx._DayPack, "|");
            for (size_t j = 0; j < tk.size(); ++ j)
            {
                Tokenizer yatk(tk[j], ",");
                UINT32 dwItemID = atoi(yatk[0].c_str());
                if (!dwItemID)
                    continue;
                SItemGenInfo stItemGen;
                if (yatk.size() > 1)
                    stItemGen.dwCount = atoi(yatk[1].c_str());
                else
                    stItemGen.dwCount = 1;
                stItemGen.wItemID = dwItemID;
                stItemGen.eBindType = eBindGet;
                rVIPLevelCFGEx._vecItemDayPack.push_back(stItemGen);
            }
            Tokenizer tk1(rVIPLevelCFGEx._Award, "|");
            for (size_t j = 0; j < tk1.size(); ++ j)
            {
                Tokenizer yatk(tk1[j], ",");
                UINT32 dwItemID = atoi(yatk[0].c_str());
                if (!dwItemID)
                    continue;
                SItemGenInfo stItemGen;
                if (yatk.size() > 1)
                    stItemGen.dwCount = atoi(yatk[1].c_str());
                else
                    stItemGen.dwCount = 1;
                stItemGen.wItemID = dwItemID;
                stItemGen.eBindType = eBindGet;
                rVIPLevelCFGEx._vecItemLevelAward.push_back(stItemGen);
            }
        }
    }else if("VIPBase.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/VIPBase.xml";
        CVIPBaseLoader oVIPBaseLoader;
        if(!oVIPBaseLoader.LoadData(strPath))
        {
            LOG_CRI << "oVIPBaseLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oVIPBaseLoader._vecData.size(); ++i)
        {
            SVIPBaseCFG* pVIPBaseCFG = oVIPBaseLoader._vecData[i];
            if(pVIPBaseCFG->_ID == 0)
                continue;
            SVIPBaseCFGEx& rVIPBaseCFGEx = _mapID2VIPBaseCFG[pVIPBaseCFG->_ID];
            rVIPBaseCFGEx.SetConfig(*pVIPBaseCFG);
        }
    }
    return true;
}

//XXX 配置表VIP等级从0开始
UINT8 CVIPMgr::CalcVIPLevel(UINT32 dwGrowthValue)
{
    for (size_t i = 0; i < _vecRecharge.size(); ++i)
    {
        if (dwGrowthValue < _vecRecharge[i])
            return i;
    }
    return _vecRecharge.size();
    /*
    UINT8 byMaxLvl = 0;
    if (!dwGrowthValue)
        return byMaxLvl;
    for (auto iter = _mapID2VIPLevelCFG.begin(); iter != _mapID2VIPLevelCFG.end(); ++ iter)
    {
        if (iter->second._Level > byMaxLvl)
            byMaxLvl = iter->second._Level;
        if (dwGrowthValue < iter->second._Exp)
            return iter->second._Level-1;
    }
    return byMaxLvl;
    */
}

SVIPLevelCFGEx* CVIPMgr::GetVIPLevelCfg(UINT8 byLvl)
{
    auto it = _mapID2VIPLevelCFG.find(byLvl);
    if(it != _mapID2VIPLevelCFG.end())
        return &it->second;
    return NULL;
}

SVIPBaseCFGEx* CVIPMgr::GetVIPBaseCfg(UINT8 byTypeID)
{
    auto it = _mapID2VIPBaseCFG.find(byTypeID);
    if(it != _mapID2VIPBaseCFG.end())
        return &it->second;
    return NULL;
}

UINT8 CVIPMgr::GetVIPMaxLevel()
{
    if(_mapID2VIPLevelCFG.empty())
        return 0;
    
    return (_mapID2VIPLevelCFG.rbegin())->second._Level; 
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

