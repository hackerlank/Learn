#include "TripodProt.h"
#include "Version.h"
#include "Tokenizer.h"
#include "TripodMgr.h"
#include "ItemProt.h"

using namespace NItemProt;

UINT64 CTripodMgr::_qwVersion = VERSION_INIT;
map<UINT16, SStoveFireCFGEx> CTripodMgr::_mapID2StoveFireCFG;
map<UINT8, SStoveFireLevelCFGEx> CTripodMgr::_mapID2StoveFireLevelCFG;
map<UINT8, SStovePropCFGEx> CTripodMgr::_mapID2StovePropCFG;
map<UINT32, SStoveAttrCFGEx> CTripodMgr::_mapID2StoveAttrCFG;

bool CTripodMgr::Init()
{
    return LoadConfig();
}

bool CTripodMgr::LoadConfig(bool bReload /*= false*/)
{
    string strPath = Config._strConfigDir + "Conf/Table/StoveFire.xml";
    CStoveFireLoader oStoveFireLoader;
    if(!oStoveFireLoader.LoadData(strPath))
    {
        LOG_CRI << "oStoveFireLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oStoveFireLoader._vecData.size(); ++i)
    {
        SStoveFireCFG* pStoveFireCFG = oStoveFireLoader._vecData[i];
        if(pStoveFireCFG->_ID == 0)
            continue;
        SStoveFireCFGEx& rStoveFireCFGEx = _mapID2StoveFireCFG[pStoveFireCFG->_ID];
        rStoveFireCFGEx.SetConfig(*pStoveFireCFG);

        Tokenizer tk(rStoveFireCFGEx._RequiredItem, "|");
        for (size_t j = 0; j < tk.size(); ++ j)
        {
            Tokenizer yatk(tk[j], ",");
            UINT16 wItemID = atoi(yatk[0].c_str());
            if (wItemID)
            {
               UINT32 dwItemCount = 0;
                if (yatk.size() > 1)
                    dwItemCount = atoi(yatk[1].c_str());
                rStoveFireCFGEx._vecItemCost.push_back(SItemCount(wItemID, dwItemCount));
            }
        }

        Tokenizer awtk(rStoveFireCFGEx._RewardItem, ",");
        UINT16 wItemID = atoi(awtk[0].c_str());
        if (wItemID)
        {
            UINT32 dwItemCount = 1;
            if (awtk.size() > 1)
                dwItemCount = atoi(awtk[1].c_str());
            rStoveFireCFGEx._oItemGenInfo.wItemID = wItemID;
            rStoveFireCFGEx._oItemGenInfo.dwCount = dwItemCount;
            rStoveFireCFGEx._oItemGenInfo.eBindType = eBindGet;
        }
    }

    strPath = Config._strConfigDir + "Conf/Table/StoveFireLevel.xml";
    CStoveFireLevelLoader oStoveFireLevelLoader;
    if(!oStoveFireLevelLoader.LoadData(strPath))
    {
        LOG_CRI << "oStoveFireLevelLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oStoveFireLevelLoader._vecData.size(); ++i)
    {
        SStoveFireLevelCFG* pFireLevelCFG = oStoveFireLevelLoader._vecData[i];
        if(pFireLevelCFG->_Level == 0)
            continue;
        SStoveFireLevelCFGEx& rFireLevelCFGEx = _mapID2StoveFireLevelCFG[pFireLevelCFG->_Level];
        rFireLevelCFGEx.SetConfig(*pFireLevelCFG);
    }

    strPath = Config._strConfigDir + "Conf/Table/StoveProp.xml";
    CStovePropLoader oStovePropLoader;
    if(!oStovePropLoader.LoadData(strPath))
    {
        LOG_CRI << "oStovePropLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oStovePropLoader._vecData.size(); ++i)
    {
        SStovePropCFG* pStovePropCFG = oStovePropLoader._vecData[i];
        if(pStovePropCFG->_ID == 0)
            continue;
        SStovePropCFGEx& rStovePropCFGEx = _mapID2StovePropCFG[pStovePropCFG->_ID];
        rStovePropCFGEx.SetConfig(*pStovePropCFG);

        Tokenizer tk(rStovePropCFGEx._BornFires, "|");
        for (size_t j = 0; j < tk.size(); ++ j)
        {
            UINT16 wFireID = atoi(tk[j].c_str());
            if (wFireID > 0)
                rStovePropCFGEx._vecFireID.push_back(wFireID);
        }
    }

    strPath = Config._strConfigDir + "Conf/Table/StoveAttr.xml";
    CStoveAttrLoader oStoveAttrLoader;
    if(!oStoveAttrLoader.LoadData(strPath))
    {
        LOG_CRI << "oStoveAttrLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oStoveAttrLoader._vecData.size(); ++i)
    {
        SStoveAttrCFG* pStoveAttrCFG = oStoveAttrLoader._vecData[i];
        if(pStoveAttrCFG->_StoveID == 0)
            continue;
        UINT32 dwKey = MAKE_STOVEIDKEY(pStoveAttrCFG->_StoveID, pStoveAttrCFG->_Level, pStoveAttrCFG->_Rank);
        SStoveAttrCFGEx& rStoveAttrCFGEx = _mapID2StoveAttrCFG[dwKey];
        rStoveAttrCFGEx.SetConfig(*pStoveAttrCFG);
    }
    return true;
}

bool CTripodMgr::ReLoadConfig(const string& strFile)
{
    string strPath;
    if("StoveFire.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/StoveFire.xml";
        CStoveFireLoader oStoveFireLoader;
        if(!oStoveFireLoader.LoadData(strPath))
        {
            LOG_CRI << "oStoveFireLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oStoveFireLoader._vecData.size(); ++i)
        {
            SStoveFireCFG* pStoveFireCFG = oStoveFireLoader._vecData[i];
            if(pStoveFireCFG->_ID == 0)
                continue;
            SStoveFireCFGEx& rStoveFireCFGEx = _mapID2StoveFireCFG[pStoveFireCFG->_ID];
            rStoveFireCFGEx.SetConfig(*pStoveFireCFG);

            Tokenizer tk(rStoveFireCFGEx._RequiredItem, "|");
            for (size_t j = 0; j < tk.size(); ++ j)
            {
                Tokenizer yatk(tk[j], ",");
                UINT16 wItemID = atoi(yatk[0].c_str());
                if (wItemID)
                {
                   UINT32 dwItemCount = 0;
                    if (yatk.size() > 1)
                        dwItemCount = atoi(yatk[1].c_str());
                    rStoveFireCFGEx._vecItemCost.push_back(SItemCount(wItemID, dwItemCount));
                }
            }

            Tokenizer awtk(rStoveFireCFGEx._RewardItem, ",");
            UINT16 wItemID = atoi(awtk[0].c_str());
            if (wItemID)
            {
                UINT32 dwItemCount = 0;
                if (awtk.size() > 1)
                    dwItemCount = atoi(awtk[1].c_str());
                rStoveFireCFGEx._oItemGenInfo.wItemID = wItemID;
                rStoveFireCFGEx._oItemGenInfo.dwCount = dwItemCount;
                rStoveFireCFGEx._oItemGenInfo.eBindType = eBindGet;
            }
        }
    }
    else if("StoveFireLevel.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/StoveFireLevel.xml";
        CStoveFireLevelLoader oStoveFireLevelLoader;
        if(!oStoveFireLevelLoader.LoadData(strPath))
        {
            LOG_CRI << "oStoveFireLevelLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oStoveFireLevelLoader._vecData.size(); ++i)
        {
            SStoveFireLevelCFG* pFireLevelCFG = oStoveFireLevelLoader._vecData[i];
            if(pFireLevelCFG->_Level == 0)
                continue;
            SStoveFireLevelCFGEx& rFireLevelCFGEx = _mapID2StoveFireLevelCFG[pFireLevelCFG->_Level];
            rFireLevelCFGEx.SetConfig(*pFireLevelCFG);
        }
    }
    else if("StoveProp.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/StoveProp.xml";
        CStovePropLoader oStovePropLoader;
        if(!oStovePropLoader.LoadData(strPath))
        {
            LOG_CRI << "oStovePropLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oStovePropLoader._vecData.size(); ++i)
        {
            SStovePropCFG* pStovePropCFG = oStovePropLoader._vecData[i];
            if(pStovePropCFG->_ID == 0)
                continue;
            SStovePropCFGEx& rStovePropCFGEx = _mapID2StovePropCFG[pStovePropCFG->_ID];
            rStovePropCFGEx.SetConfig(*pStovePropCFG);

            Tokenizer tk(rStovePropCFGEx._BornFires, "|");
            for (size_t j = 0; j < tk.size(); ++ j)
            {
                UINT16 wFireID = atoi(tk[j].c_str());
                if (wFireID > 0)
                    rStovePropCFGEx._vecFireID.push_back(wFireID);
            }
        }
    }
    else if("StoveAttr.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/StoveAttr.xml";
        CStoveAttrLoader oStoveAttrLoader;
        if(!oStoveAttrLoader.LoadData(strPath))
        {
            LOG_CRI << "oStoveAttrLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oStoveAttrLoader._vecData.size(); ++i)
        {
            SStoveAttrCFG* pStoveAttrCFG = oStoveAttrLoader._vecData[i];
            if(pStoveAttrCFG->_StoveID == 0)
                continue;
            UINT32 dwKey = MAKE_STOVEIDKEY(pStoveAttrCFG->_StoveID, pStoveAttrCFG->_Level, pStoveAttrCFG->_Rank);
            SStoveAttrCFGEx& rStoveAttrCFGEx = _mapID2StoveAttrCFG[dwKey];
            rStoveAttrCFGEx.SetConfig(*pStoveAttrCFG);
        }
    }
    return true;
}

SStoveFireCFGEx* CTripodMgr::GetStoveFireCfg(UINT16 wFireID)
{
    auto it = _mapID2StoveFireCFG.find(wFireID);
    if(it != _mapID2StoveFireCFG.end())
        return &it->second;
    return NULL;
}

SStoveFireLevelCFGEx* CTripodMgr::GetStoveFireLevelCfg(UINT8 byLvl)
{
    auto it = _mapID2StoveFireLevelCFG.find(byLvl);
    if(it != _mapID2StoveFireLevelCFG.end())
        return &it->second;
    return NULL;
}

SStovePropCFGEx* CTripodMgr::GetStovePropCfg(UINT8 byStoveID)
{
    auto it = _mapID2StovePropCFG.find(byStoveID);
    if(it != _mapID2StovePropCFG.end())
        return &it->second;
    return NULL;
}

SStoveAttrCFGEx* CTripodMgr::GetStoveAttrCfg(UINT8 byStoveID, UINT8 byLvl, UINT8 byRank/* = 1*/)
{
    auto it = _mapID2StoveAttrCFG.find(MAKE_STOVEIDKEY(byStoveID, byLvl, byRank));
    if(it != _mapID2StoveAttrCFG.end())
        return &it->second;
    return NULL;
}

// 判断当前是否是最大等级
bool CTripodMgr::IsMaxLevel(UINT8 byStoveID, UINT8 byLevel, UINT8 byRank)
{
    SStoveAttrCFGEx* pCFG = GetStoveAttrCfg(byStoveID, byLevel+1, byRank);
    if (pCFG)
        return false;
    else
        return true;
}

bool CTripodMgr::TestTripodLevelUp(UINT8 byTripodID, UINT8& byLevel, UINT32& dwExp, UINT8 byRank)
{
    if (IsMaxLevel(byTripodID, byLevel, byRank))
        return false;
    SStoveAttrCFGEx* pCFG = GetStoveAttrCfg(byTripodID, byLevel, byRank);
    if (!pCFG)
        return false;
    while(true)
    {
        pCFG = GetStoveAttrCfg(byTripodID, byLevel, byRank);
        if (!pCFG)
            break;
        if (dwExp < pCFG->_ExpNeed)
            break;

        dwExp -= pCFG->_ExpNeed;
        ++ byLevel;
    }
    return true;
}

UINT32 CTripodMgr::GetFireLevelRandom()
{
    UINT8 byMaxLvl = 0;
    UINT32 dwRand = CRandom::RandInt(1, 10000);
    for (auto iter = _mapID2StoveFireLevelCFG.begin(); iter != _mapID2StoveFireLevelCFG.end(); ++ iter)
    {
        if (iter->second._Level > byMaxLvl)
            byMaxLvl = iter->second._Level;
        if (iter->second._Appear > dwRand)
            return iter->second._Level;
    }
    return byMaxLvl;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

