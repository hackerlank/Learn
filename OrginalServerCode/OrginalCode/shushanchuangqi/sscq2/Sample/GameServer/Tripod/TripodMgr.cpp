#include "TripodMgr.h"
#include "Version.h"
#include "CommonDef.h"
#include "User.h"
#include "Store.h"
#include "ProtoCommon.h"
#include "Parameter.h"
#include "Random.h"

using namespace NProtoCommon;

UINT64 CTripodMgr::_qwVersion = VERSION_INIT;
map<UINT32, SStoveAttrCFGEx> CTripodMgr::_mapID2StoveAttrCFG;

bool CTripodMgr::Init()
{
    return LoadConfig();
}

bool CTripodMgr::LoadConfig(bool bReload /*= false*/)
{
    string strPath = Config._strConfigDir + "Conf/Table/StoveAttr.xml";
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
    if("StoveAttr.xml" == strFile)
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

SStoveAttrCFGEx* CTripodMgr::GetStoveAttrCfg(UINT8 byStoveID, UINT8 byLvl, UINT8 byRank/* = 1*/)
{
    auto it = _mapID2StoveAttrCFG.find(MAKE_STOVEIDKEY(byStoveID, byLvl, byRank));
    if(it != _mapID2StoveAttrCFG.end())
        return &it->second;
    return NULL;
}

// 将属性表转为将领属性vector
bool CTripodMgr::AddTripodAttr(UINT8 byStoveID, UINT8 byLvl, UINT8 byRank, TVecFloat& rvecAttr)
{
    SStoveAttrCFGEx* pCFG = GetStoveAttrCfg(byStoveID, byLvl, byRank);
    if (!pCFG)
        return false;
    PHYATK_ADD(rvecAttr, pCFG);
    MGCATK_ADD(rvecAttr, pCFG);
    PHYDEF_ADD(rvecAttr, pCFG);
    MGCDEF_ADD(rvecAttr, pCFG);
    PHYRDC_ADD(rvecAttr, pCFG);
    MGCRDC_ADD(rvecAttr, pCFG);
    MAXHP_ADD(rvecAttr, pCFG);
    SPEED_ADD(rvecAttr, pCFG);
    HIT_ADD(rvecAttr, pCFG);
    HITRATE_ADD(rvecAttr, pCFG);
    DODGE_ADD(rvecAttr, pCFG);
    DODGERATE_ADD(rvecAttr, pCFG);
    CRITICAL_ADD(rvecAttr, pCFG);
    CRTRATE_ADD(rvecAttr, pCFG);
    ANTICRITCAL_ADD(rvecAttr, pCFG);
    ANTICRTRATE_ADD(rvecAttr, pCFG);
    BLOCK_ADD(rvecAttr, pCFG);
    BLOCKRATE_ADD(rvecAttr, pCFG);
    PIERCE_ADD(rvecAttr, pCFG);
    PIERCERATE_ADD(rvecAttr, pCFG);
    COUNTER_ADD(rvecAttr, pCFG);
    COUNTERRATE_ADD(rvecAttr, pCFG);
    RESIST_ADD(rvecAttr, pCFG);
    RESISTRATE_ADD(rvecAttr, pCFG);
    INITAURA_ADD(rvecAttr, pCFG);
    MAXAURA_ADD(rvecAttr, pCFG);
    CRIEXTRAADD_ADD(rvecAttr, pCFG);
    CRIEXTRARDC_ADD(rvecAttr, pCFG);
    METALATK_ADD(rvecAttr, pCFG);
    WOODATK_ADD(rvecAttr, pCFG);
    WATERATK_ADD(rvecAttr, pCFG);
    FIREATK_ADD(rvecAttr, pCFG);
    EARTHATK_ADD(rvecAttr, pCFG);
    METALDEF_ADD(rvecAttr, pCFG);
    WOODDEF_ADD(rvecAttr, pCFG);
    WATERDEF_ADD(rvecAttr, pCFG);
    FIREDEF_ADD(rvecAttr, pCFG);
    EARTHDEF_ADD(rvecAttr, pCFG);
    PHYATK_PER_ADD(rvecAttr, pCFG);
    MGCATK_PER_ADD(rvecAttr, pCFG);
    PHYDEF_PER_ADD(rvecAttr, pCFG);
    MGCDEF_PER_ADD(rvecAttr, pCFG);
    MAXHP_PER_ADD(rvecAttr, pCFG);
    SPEED_PER_ADD(rvecAttr, pCFG);
    HIT_PER_ADD(rvecAttr, pCFG);
    DODGE_PER_ADD(rvecAttr, pCFG);
    CRITICAL_PER_ADD(rvecAttr, pCFG);
    ANTICRITCAL_PER_ADD(rvecAttr, pCFG);
    BLOCK_PER_ADD(rvecAttr, pCFG);
    PIERCE_PER_ADD(rvecAttr, pCFG);
    COUNTER_PER_ADD(rvecAttr, pCFG);
    RESIST_PER_ADD(rvecAttr, pCFG);
    ANTIEFFECT_ADD(rvecAttr, pCFG);
    //COUTEREXTRAADD_ADD(rvecAttr, pCFG);
    //COUTEREXTRARDC_ADD(rvecAttr, pCFG);
    return true;
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

bool CTripodMgr::UpgradeTripod(UINT8 byStoveID, UINT8& byLevel, UINT8 byRank, UINT32& dwExp, bool bOneKey, CUserPtr pUser)
{
    SStoveAttrCFGEx* pCFG = GetStoveAttrCfg(byStoveID, byLevel, byRank);
    if (!pUser || !pCFG)
        return false;
    if (IsMaxLevel(byStoveID, byLevel, byRank))
        return false;
    CPack& rPack = pUser->GetPack();
    UINT16 wMaxCount = rPack.GetItemCount(pCFG->_EvolveItemID);
    if (wMaxCount < pCFG->_EvolveItemCount)
        return false;

    UINT16 wNeedCount = 0;
    UINT32 dwMaxExp = pCFG->_ExpNeed;
    while (dwExp < dwMaxExp)
    {
        if (wNeedCount >= wMaxCount)
            break;
        wNeedCount += pCFG->_EvolveItemCount;
        dwExp += CRandom::RandInt(SParamConfig::byStoveUpgradeLow, SParamConfig::byStoveUpgradeMax);
        if (dwExp >= dwMaxExp) // 升级了
        {
            ++ byLevel;
            dwExp = 0;
            break;
        }
        if (!bOneKey)
            break;
    }
    rPack.DelItemByItemID(pCFG->_EvolveItemID, wNeedCount, true, NLogDataDefine::ItemTo_TripodUpgrade);
    return true;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

