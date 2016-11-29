#include "TrumpMgr.h"

#include "ServerDefine.h" // XXX: for LOG_INF……
#include "GameConfig.h"
#include "ItemMgr.h"
#include "ItemAttrCFG.h"

#include "Fighter.h"
#include "Player.h"
#include "Random.h"

template<typename T, typename V>
V* GetValFromMap2(std::map<T, V>& rMap, const T& t)
{
    auto it = rMap.find(t);
    if(it != rMap.end())
        return it->second;
    return NULL;
}

bool CTrumpMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/TrumpIntensify.xml";
    LOG_INF << "Loading " << strPath << " ...";
    if (!LoadIntensifyConfig(strPath))
        return false;
    LOG_INF << "Loading " << strPath << " succeed.";

    return true;
}

bool CTrumpMgr::LoadConfig(const string &strFile)
{
    string strPath;
    if("TrumpIntensify.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/TrumpIntensify.xml";
        LOG_INF << "Loading " << strPath << " ...";
        if (!LoadIntensifyConfig(strPath))
            return false;
        LOG_INF << "Loading " << strPath << " succeed.";
    }
    return true;
}

bool CTrumpMgr::Reload()
{
    string strPath = Config._strConfigDir + "Conf/Table/TrumpIntensify.xml";
    LOG_INF << "Loading " << strPath << " ...";
    if (!LoadIntensifyConfig(strPath))
        return false;
    LOG_INF << "Loading " << strPath << " succeed.";

    return true;
}

bool CTrumpMgr::LoadIntensifyConfig(const string& strPath)
{
    if(_cIntensifyLoader.LoadData(strPath))
    {
        _mapIDLevelRank2AttrInfo.clear();
        _mapID2Intensify.clear();
        for (auto & pCFG : _cIntensifyLoader._vecData)
        {
            if (!pCFG->_ItemAttrID)
            {
                LOG_INF << "Loading " << strPath << " failed, ID = " << pCFG->_ItemAttrID;
                return false;
            }

            UINT32 dwIDLevelRank = (static_cast<UINT32>(pCFG->_ItemAttrID) << 16) | 
                static_cast<UINT16>(pCFG->_Level << 8) | 
                pCFG->_Rank;
            _mapIDLevelRank2AttrInfo[dwIDLevelRank] = pCFG;
            SIntensifyInfo& rIntensifyInfo = _mapID2Intensify[pCFG->_ItemAttrID];
            UINT16 wLevelRank =  pCFG->_Rank | static_cast<UINT16>(pCFG->_Level << 8);
            if (rIntensifyInfo.mapOneLevelInfo.find(wLevelRank) != rIntensifyInfo.mapOneLevelInfo.end())
            {
                LOG_WRN << "Rank(" << (wLevelRank & 0xFF) << ") and Level(" << (wLevelRank >> 8) << ") conflict.";
                return false;
            }
            SOneLevelInfo sOneLevelInfo;
            sOneLevelInfo.wAttrID       = pCFG->_ItemAttrID;
            sOneLevelInfo.wLevel        = pCFG->_Level;
            sOneLevelInfo.wRank         = pCFG->_Rank;
            sOneLevelInfo.dwExp         = pCFG->_ExpNeed;
            sOneLevelInfo.wItemID       = pCFG->_EvolveItemID;
            sOneLevelInfo.wItemCount    = pCFG->_EvolveItemCount;
            sOneLevelInfo.bySkillLevel  = pCFG->_SkillLevel;
            rIntensifyInfo.mapOneLevelInfo[wLevelRank] = sOneLevelInfo;
            ++(rIntensifyInfo.wMaxTotalLevel);
        }
    }
    else
    {
        LOG_INF << "Loading " << strPath << " failed.";
        return false;
    }
    return true;
}

void CTrumpMgr::GetAllAttr(TVecFloat& rvecAttr, UINT16 wItemID, UINT16 wLevel, UINT16 wRank, bool bIsMainFighter) const
{
    SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
    if (!pItemInfo)
        return;

    CItemMgr::AppendAttr2(pItemInfo->oItemCfg._AttrIdx_1, rvecAttr);
    AddAttr2FighterAttr(pItemInfo->oItemCfg._AttrIdx_1, wLevel, wRank, rvecAttr);

    if (bIsMainFighter)
    {
        CItemMgr::AppendAttr2(pItemInfo->oItemCfg._AttrIdx_2, rvecAttr);
        AddAttr2FighterAttr(pItemInfo->oItemCfg._AttrIdx_2, wLevel, wRank, rvecAttr);
    }

    CItemMgr::AppendAttr2(pItemInfo->oItemCfg._AttrIdx_3, rvecAttr);
    AddAttr2FighterAttr(pItemInfo->oItemCfg._AttrIdx_3, wLevel, wRank, rvecAttr);
}

UINT32 CTrumpMgr::GetNextLevelExp(UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const
{
    if (IsMaxLevel(wItemID, wLevel, wRank))
        return 0;
    UINT16 wAttrID = GetAttrID(wItemID);
    auto it = _mapID2Intensify.find(wAttrID);
    if (it == _mapID2Intensify.end())
        return 0;
    const SIntensifyInfo& rIntensifyInfo = it->second;
    UINT16 wLevelRank = wRank|(wLevel << 8);
    if (rIntensifyInfo.mapOneLevelInfo.find(wLevelRank) == rIntensifyInfo.mapOneLevelInfo.end())
        return 0;
    auto it2 = rIntensifyInfo.mapOneLevelInfo.find(wLevelRank);
    return (it2->second).dwExp;
}

// 判断是否是当前阶数的最大等级
bool CTrumpMgr::IsMaxRank(UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const
{
    UINT16 wAttrID = GetAttrID(wItemID);
    auto it = _mapID2Intensify.find(wAttrID);
    if (it == _mapID2Intensify.end())
        return true;
    const SIntensifyInfo& rIntensifyInfo = it->second;
    UINT16 wLevelRank = (wRank + 1)|(1 << 8);
    if (rIntensifyInfo.mapOneLevelInfo.find(wLevelRank) == rIntensifyInfo.mapOneLevelInfo.end())
        return true;
    else
        return false;
}

// 判断是否是当前最大阶数
bool CTrumpMgr::IsMaxLevel(UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const
{
    UINT16 wAttrID = GetAttrID(wItemID);
    auto it = _mapID2Intensify.find(wAttrID);
    if (it == _mapID2Intensify.end())
        return true;
    const SIntensifyInfo& rIntensifyInfo = it->second;
    UINT16 wLevelRank = wRank|((wLevel + 1) << 8);
    if (rIntensifyInfo.mapOneLevelInfo.find(wLevelRank) == rIntensifyInfo.mapOneLevelInfo.end())
        return true;
    else
        return false;
}

// TODO: 判断是否可以升阶
bool CTrumpMgr::CanEvolve      (UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const
{
    return false;
}

// TODO: 判断是否可以升级
bool CTrumpMgr::CanUpgrade     (UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const
{
    return false;
}

UINT16 CTrumpMgr::GetAttrID(UINT16 wItemID) const
{
    SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
    if (!pItemInfo)
        return 0;
    return pItemInfo->oItemCfg._AttrIdx_1;
}

bool CTrumpMgr::GetHaloAttr(TVecFloat& rvecAttr, UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const
{
    SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
    if (!pItemInfo)
        return false;
    if (!pItemInfo->oItemCfg._AttrIdx_1)
        return false;
    AddAttr2FighterAttr(pItemInfo->oItemCfg._AttrIdx_1, wLevel, wRank, rvecAttr);
    return true;
}

bool CTrumpMgr::GetExtraAttr(TVecFloat& rvecAttr, UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const
{
    SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
    if (!pItemInfo)
        return false;
    if (!pItemInfo->oItemCfg._AttrIdx_3)
        return false;
    AddAttr2FighterAttr(pItemInfo->oItemCfg._AttrIdx_3, wLevel, wRank, rvecAttr);
    return true;
}

bool CTrumpMgr::GetActiveAttr(TVecFloat& rvecAttr, UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const
{
    SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
    if (!pItemInfo)
        return false;
    if (!pItemInfo->oItemCfg._AttrIdx_2)
        return false;
    AddAttr2FighterAttr(pItemInfo->oItemCfg._AttrIdx_2, wLevel, wRank, rvecAttr);
    return true;
}

// 返回带等级的技能ID
UINT32 CTrumpMgr::GetSkill(UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const
{
    SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
    if (!pItemInfo || !pItemInfo->pItemAttr)
        return 0;
    UINT32 dwSkill = SKILL_ID(pItemInfo->pItemAttr->dwPeerless);
    if (!dwSkill)
    {
        for (auto it = pItemInfo->pItemAttr->vecPassSkills.begin(); it != pItemInfo->pItemAttr->vecPassSkills.end(); ++it)
        {
            if (*it)
            {
                dwSkill = SKILL_ID(*it);
                break;
            }
        }
    }
    if (!dwSkill)
        return dwSkill;
    UINT16 wAttrID = GetAttrID(wItemID);
    auto it = _mapID2Intensify.find(wAttrID);
    if (it == _mapID2Intensify.end())
        return 0;
    const SIntensifyInfo& rIntensifyInfo = it->second;
    UINT16 wLevelRank = wRank|(wLevel << 8);
    if (rIntensifyInfo.mapOneLevelInfo.find(wLevelRank) == rIntensifyInfo.mapOneLevelInfo.end())
        return 0;
    auto it2 = rIntensifyInfo.mapOneLevelInfo.find(wLevelRank);
    if (it2 == rIntensifyInfo.mapOneLevelInfo.end())
        return 0;
    UINT8 bySkillLevel = (it2->second).bySkillLevel;
    //return SKILLANDLEVEL(dwSkill, bySkillLevel);
    return SkillMgr.GetSkillIDQualityLevel(dwSkill, bySkillLevel);
}

bool    CTrumpMgr::GetUpgradeMaterial(UINT16 wItemID, UINT16 wLevel, UINT16 wRank, STrumpUpgradeMaterial& rMaterial) const
{
    UINT16 wAttrID = GetAttrID(wItemID);
    auto it = _mapID2Intensify.find(wAttrID);
    if (it == _mapID2Intensify.end())
        return false;
    const SIntensifyInfo& rIntensifyInfo = it->second;
    UINT16 wLevelRank = wRank|(wLevel << 8);
    if (rIntensifyInfo.mapOneLevelInfo.find(wLevelRank) == rIntensifyInfo.mapOneLevelInfo.end())
        return false;
    auto it2 = rIntensifyInfo.mapOneLevelInfo.find(wLevelRank);
    rMaterial.wItemID       = (it2->second).wItemID;
    rMaterial.dwItemCount    = (it2->second).wItemCount;
    return true;
}

bool    CTrumpMgr::GetEvolveMaterial(UINT16 wItemID, UINT16 wLevel, UINT16 wRank, STrumpEvolveMaterial& rMaterial) const
{
    UINT16 wAttrID = GetAttrID(wItemID);
    auto it = _mapID2Intensify.find(wAttrID);
    if (it == _mapID2Intensify.end())
        return 0;
    const SIntensifyInfo& rIntensifyInfo = it->second;
    UINT16 wLevelRank = wRank|(wLevel << 8);
    if (rIntensifyInfo.mapOneLevelInfo.find(wLevelRank) == rIntensifyInfo.mapOneLevelInfo.end())
        return 0;
    auto it2 = rIntensifyInfo.mapOneLevelInfo.find(wLevelRank);
    rMaterial.wItemID       = (it2->second).wItemID;
    rMaterial.dwItemCount    = (it2->second).wItemCount;
    return true;
}

UINT32  CTrumpMgr::Upgrade (CUserPtr pUser, UINT16 wItemID, UINT16& wLevel, UINT16& wRank, UINT32& dwExp, STrumpUpgradeMaterial& rMaterial, bool bOneKey, UINT32& dwAddExp) const
{
    UINT32 dwUsedCount = 0;

    if (!pUser)
        return dwUsedCount;

    if (IsMaxLevel(wItemID, wLevel, wRank))
        return dwUsedCount;

    UINT32 dwMaxExp = GetNextLevelExp(wItemID, wLevel, wRank);
    if (!dwMaxExp)
        return dwUsedCount;

    STrumpUpgradeMaterial sNeedMaterial;
    if (!GetUpgradeMaterial(wItemID, wLevel, wRank, sNeedMaterial))
        return dwUsedCount;

    if (dwMaxExp < dwExp)
        dwExp = dwMaxExp - 1;   // 要是这里执行到，应该是配置改了吧。

    dwAddExp = 0;
    while (dwExp < dwMaxExp)
    {
        if (rMaterial.dwItemCount < sNeedMaterial.dwItemCount) // 材料不足
            break;

        dwUsedCount += sNeedMaterial.dwItemCount;
        rMaterial.dwItemCount -= sNeedMaterial.dwItemCount;
        
        dwAddExp = 10;
        UINT8 byNum = 1;
#if ON_OFF
        UINT16 wRand = CRandom::RandInt(0, MAX_RANDNUM);
        if (wRand < RANDVALUE_A)
            byNum = 10;
        else if (wRand < RANDVALUE_B)
            byNum = 5;
        else if (wRand < RANDVALUE_C)
            byNum = 2;

        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (pPlayer)
        {
            if (TWO_NOTIFY==byNum)
                pPlayer->SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eTrumpCrit, eTwoMultipleCrit));
            else if (FIVE_NOTIFY==byNum)
                pPlayer->SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eTrumpCrit, eFiveMultipleCrit));
            else if(TEN_NOTIFY==byNum)
            {
                TVecString vecstring;
                vecstring.push_back(NumberToString(pPlayer->GetColor()));
                vecstring.push_back(pPlayer->GetName());
                vecstring.push_back(NumberToString(byNum));
                g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgTrumpIntensify, vecstring);
                
                pPlayer->SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eTrumpCrit, eTenMultipleCrit));
            }
        }
#endif
        //dwAddExp = CRandom::RandInt(1, 19);
        dwExp += (dwAddExp * byNum);
        if (dwExp >= dwMaxExp) // 升级了
        {
            ++wLevel;
            dwExp = 0;
            break;
            /*
            dwMaxExp = GetNextLevelExp(wItemID, wLevel, wRank);
            if (!GetUpgradeMaterial(wItemID, wLevel, wRank, sNeedMaterial))
                break;
            */
        }
        if (!bOneKey)
            break;
    }
    return dwUsedCount;
}

// 法宝升阶
UINT32    CTrumpMgr::Evolve  (UINT16 wItemID, UINT16& wLevel, UINT16& wRank, UINT32& dwExp, STrumpEvolveMaterial& rMaterial) const
{
    UINT32 dwUsedCount = 0;
    if (!IsMaxLevel(wItemID, wLevel, wRank))
        return dwUsedCount;
    if (IsMaxRank(wItemID, wLevel, wRank))
        return dwUsedCount;

    STrumpEvolveMaterial sNeedMaterial;
    if (!GetEvolveMaterial(wItemID, wLevel, wRank, sNeedMaterial))
        return dwUsedCount;

    if (rMaterial.dwItemCount < sNeedMaterial.dwItemCount) // 材料不足
        return dwUsedCount;

    dwUsedCount += sNeedMaterial.dwItemCount;
    rMaterial.dwItemCount -= sNeedMaterial.dwItemCount;

    wLevel = 1;
    ++ wRank;
    return dwUsedCount;
}

bool  CTrumpMgr::Super (UINT16 wItemID, UINT16& wLevel, UINT16& wRank, UINT32& dwExp) const
{
    if (IsMaxLevel(wItemID, wLevel, wRank))
        return false;
    UINT32 dwMaxExp = GetNextLevelExp(wItemID, wLevel, wRank);
    if (!dwMaxExp)
        return false;

    if (dwMaxExp < dwExp)
        dwExp = dwMaxExp - 1;   // 要是这里执行到，应该是配置改了吧。

    while (dwExp < dwMaxExp)
    {
        //dwExp += CRandom::RandInt(1, 19);
        dwExp += 10;
        if (dwExp >= dwMaxExp) // 升级了
        {
            ++wLevel;
            dwExp = 0;
            dwMaxExp = GetNextLevelExp(wItemID, wLevel, wRank);
        }
    }
    return true;
}

// 将属性表转为将领属性vector
bool CTrumpMgr::AddAttr2FighterAttr(UINT16 wAttrID, UINT16 wLevel, UINT16 wRank, TVecFloat& rvecAttr) const
{
    UINT32 dwIDLevelRank = (static_cast<UINT32>(wAttrID) << 16) | (wLevel << 8) | wRank;
    auto it = _mapIDLevelRank2AttrInfo.find(dwIDLevelRank);
    if (it == _mapIDLevelRank2AttrInfo.end())
        return false;
    STrumpIntensifyCFG* pCFG = it->second;
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

