#include "EquipTrumpMgr.h"

#include "EquipTrumpSlotCFG.h"

#include "ServerDefine.h" // XXX: for LOG_INF……
#include "GameConfig.h"
#include "ItemMgr.h"
#include "ItemAttrCFG.h"
#include "EquipTrumpRecycleCFG.h"
#include "Tokenizer.h"
#include "ItemUpgradeCFG.h"
#include "Tokenizer.h"
#include "Player.h"

bool GetXiLianProbString(TVecXiLianProb& vecXiLianProb, const string strItem)
{
    UINT32 dwTotalRateValue = 0;
    Tokenizer tk(strItem, "|"); // XXX: 20,5000|40,3000|60,1500|80,500
    for (size_t i = 0; i < tk.size(); ++i)
    {
            Tokenizer yatk(tk[i], ",");
            UINT32 dwMinRate = atoi(yatk[0].c_str());
            if (dwMinRate)
            {
                UINT32 dwRateValue = 0;
                if (yatk.size() > 1)
                {
                    dwRateValue = atoi(yatk[1].c_str());

                    dwTotalRateValue += dwRateValue;

                    SXiLianProb oXiLianProb;
                    oXiLianProb.dwMinRate = dwMinRate;
                    if(i == tk.size()-1)
                    {
                        oXiLianProb.dwMaxRate = 100;
                    }
                    else if(i==0)
                    {
                        //不处理
                    }
                    else
                    {
                        if(i-1 < vecXiLianProb.size())
                        {
                            vecXiLianProb[i-1].dwMaxRate = dwMinRate;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    oXiLianProb.dwRateValue = dwTotalRateValue;
                    vecXiLianProb.push_back(oXiLianProb);
                }
            }
     }

    return true;
}

bool CEquipTrumpMgr::Init()
{
     return Reload();
}

bool CEquipTrumpMgr::LoadConfig(const string &strFile)
{
    string strPath;
    if("StrengthProbability.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/" + strFile;
        bool bRet = LoadStrenghProbability(strPath);
        if (bRet)
            LOG_INF << "Loading " << strPath << " succeed.";
        else
            LOG_CRI << "Loading " << strPath << " failed.";
    }
    if("TrumpIntensify.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/" + strFile;
        bool bRet = LoadTrumpIntensify(strPath);
        if (bRet)
            LOG_INF << "Loading " << strPath << " succeed.";
        else
            LOG_CRI << "Loading " << strPath << " failed.";
    }

    else if("XiLian.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/" + strFile;
        bool bRet = LoadXiLianConfig(strPath);
        if (bRet)
            LOG_INF << "Loading " << strPath << " succeed.";
        else
            LOG_CRI << "Loading " << strPath << " failed.";
 
    }
    else if ("EquipTrumpSlot.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/" + strFile;
        bool bRet = LoadEquipTrumpSlotConfig(strPath);
        if (bRet)
            LOG_INF << "Loading " << strPath << " succeed.";
        else
            LOG_CRI << "Loading " << strPath << " failed.";
    }
    else if ("ItemUpgrade.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/" + strFile;
        bool bRet = LoadMergeConfig(strPath);
        if (bRet)
            LOG_INF << "Loading " << strPath << " succeed.";
        else
            LOG_CRI << "Loading " << strPath << " failed.";
    }
    else if ("EquipTrumpRecycle.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/" + strFile;
        bool bRet = LoadBreakConfig(strPath);
        if (bRet)
            LOG_INF << "Loading " << strPath << " succeed.";
        else
            LOG_CRI << "Loading " << strPath << " failed.";
    }
    return true;
}

bool CEquipTrumpMgr::Reload()
{
    if(!LoadConfig("StrengthProbability.xml"))
        return false;

    if(!LoadConfig("TrumpIntensify.xml"))
        return false;

    if(!LoadConfig("XiLian.xml"))
        return false;

    if(!LoadConfig("EquipTrumpSlot.xml"))
        return false;

    if(!LoadConfig("ItemUpgrade.xml"))
        return false;

    if(!LoadConfig("EquipTrumpRecycle.xml"))
        return false;
    return true;
}

bool CEquipTrumpMgr::LoadStrenghProbability(const string& strPath)
{
    CStrengthProbabilityLoader oStrengthProbabilityLoader;
    if(!oStrengthProbabilityLoader.LoadData(strPath))
    {
        LOG_CRI << "CStrengthProbabilityLoaderLoader fails! Path: " << strPath;
        return false;
    }

    _mapStrengthProbabilityCFGExPtr.clear();

    for(size_t i  = 0; i < oStrengthProbabilityLoader._vecData.size(); ++i)
    {
        SStrengthProbabilityCFGExPtr pStrengthProbabilityCFG(new SStrengthProbabilityCFGEx);
        pStrengthProbabilityCFG->CopyFrom(*oStrengthProbabilityLoader._vecData[i]);
        _mapStrengthProbabilityCFGExPtr[pStrengthProbabilityCFG->_ID] = pStrengthProbabilityCFG;
    }
    return true;
}

bool CEquipTrumpMgr::LoadXiLianConfig(const string& strPath)
{
    CXiLianLoader oXiLianLoader;
    if(!oXiLianLoader.LoadData(strPath))
    {
        LOG_CRI << "CXiLianLoaderLoader fails! Path: " << strPath;
        return false;
    }

    _mapXiLianCFGExPtr.clear();

    for(size_t i  = 0; i < oXiLianLoader._vecData.size(); ++i)
    {
        SXiLianCFGExPtr pXiLianCFG(new SXiLianCFGEx);
        pXiLianCFG->CopyFrom(*oXiLianLoader._vecData[i]);
        _mapXiLianCFGExPtr[pXiLianCFG->_ID] = pXiLianCFG;

        GetXiLianProbString(pXiLianCFG->_vecXiLianProb,pXiLianCFG->_Shuffer1);
        GetXiLianProbString(pXiLianCFG->_vecXiLianProb2,pXiLianCFG->_Shuffer2);
        GetXiLianProbString(pXiLianCFG->_vecXiLianProb3,pXiLianCFG->_Shuffer3);

        TVecFloat vecAttr;
        VECATTR_RESET(vecAttr);
        PHYATK_ADD(vecAttr, pXiLianCFG);
        MGCATK_ADD(vecAttr, pXiLianCFG);
        PHYDEF_ADD(vecAttr, pXiLianCFG);
        MGCDEF_ADD(vecAttr, pXiLianCFG);
        PHYRDC_ADD(vecAttr, pXiLianCFG);
        MGCRDC_ADD(vecAttr, pXiLianCFG);
        MAXHP_ADD(vecAttr, pXiLianCFG);
        SPEED_ADD(vecAttr, pXiLianCFG);
        HIT_ADD(vecAttr, pXiLianCFG);
        HITRATE_ADD(vecAttr, pXiLianCFG);
        DODGE_ADD(vecAttr, pXiLianCFG);
        DODGERATE_ADD(vecAttr, pXiLianCFG);
        CRITICAL_ADD(vecAttr, pXiLianCFG);
        CRTRATE_ADD(vecAttr, pXiLianCFG);
        ANTICRITCAL_ADD(vecAttr, pXiLianCFG);
        ANTICRTRATE_ADD(vecAttr, pXiLianCFG);
        BLOCK_ADD(vecAttr, pXiLianCFG);
        BLOCKRATE_ADD(vecAttr, pXiLianCFG);
        PIERCE_ADD(vecAttr, pXiLianCFG);
        PIERCERATE_ADD(vecAttr, pXiLianCFG);
        COUNTER_ADD(vecAttr, pXiLianCFG);
        COUNTERRATE_ADD(vecAttr, pXiLianCFG);
        RESIST_ADD(vecAttr, pXiLianCFG);
        RESISTRATE_ADD(vecAttr, pXiLianCFG);
        INITAURA_ADD(vecAttr, pXiLianCFG);
        MAXAURA_ADD(vecAttr, pXiLianCFG);
        CRIEXTRAADD_ADD(vecAttr, pXiLianCFG);
        CRIEXTRARDC_ADD(vecAttr, pXiLianCFG);
        METALATK_ADD(vecAttr, pXiLianCFG);
        WOODATK_ADD(vecAttr, pXiLianCFG);
        WATERATK_ADD(vecAttr, pXiLianCFG);
        FIREATK_ADD(vecAttr, pXiLianCFG);
        EARTHATK_ADD(vecAttr, pXiLianCFG);
        METALDEF_ADD(vecAttr, pXiLianCFG);
        WOODDEF_ADD(vecAttr, pXiLianCFG);
        WATERDEF_ADD(vecAttr, pXiLianCFG);
        FIREDEF_ADD(vecAttr, pXiLianCFG);
        EARTHDEF_ADD(vecAttr, pXiLianCFG);
        PHYATK_PER_ADD(vecAttr, pXiLianCFG);
        MGCATK_PER_ADD(vecAttr, pXiLianCFG);
        PHYDEF_PER_ADD(vecAttr, pXiLianCFG);
        MGCDEF_PER_ADD(vecAttr, pXiLianCFG);
        MAXHP_PER_ADD(vecAttr, pXiLianCFG);
        SPEED_PER_ADD(vecAttr, pXiLianCFG);
        HIT_PER_ADD(vecAttr, pXiLianCFG);
        DODGE_PER_ADD(vecAttr, pXiLianCFG);
        CRITICAL_PER_ADD(vecAttr, pXiLianCFG);
        ANTICRITCAL_PER_ADD(vecAttr, pXiLianCFG);
        BLOCK_PER_ADD(vecAttr, pXiLianCFG);
        PIERCE_PER_ADD(vecAttr, pXiLianCFG);
        COUNTER_PER_ADD(vecAttr, pXiLianCFG);
        RESIST_PER_ADD(vecAttr, pXiLianCFG);
        ANTIEFFECT_ADD(vecAttr, pXiLianCFG);

        for(size_t i = 0; i < vecAttr.size(); i++)
        {
            if(vecAttr[i] > 0 )
            {
                SShuffleInfo oMaxShuffleInfo;
                oMaxShuffleInfo.dwType = i;
                oMaxShuffleInfo.dwValue = vecAttr[i];
                pXiLianCFG->_vecMaxShuffleInfo.push_back(oMaxShuffleInfo);
            }
        }
    }
    return true;
}

bool CEquipTrumpMgr::LoadEquipTrumpSlotConfig(const string& strPath)
{
    CEquipTrumpSlotLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "CEquipTrumpSlotLoader fails! Path: " << strPath;
        return false;
    }
  
    if(!LoadConfig("TrumpIntensify.xml"))
    {
        return false;
    }

    _mapSlotConfig.clear();
    for(auto & pCFG :oLoader._vecData)
    {
        if (!pCFG)
        {
            LOG_CRI << "pCFG = NULL.";
            return false;
        }

        if(pCFG->_SlotId >= 10)
        {
            //修改这个数据需要修改下面的定义
            //const UINT8 EQUIP_TRUMP_SLOTS = 10; 
            LOG_CRI<<" SlotId >= 10";

            return false;
        }

        SEquipTrumpSlotConfig sConfig;
        sConfig.byIndex         = pCFG->_SlotId;
        switch (pCFG->_EquipTrumpType)
        {
            case 205: // 先天  
            case 206: // 被动  
            case 207: // 光环  
            case 208: // 变身
                sConfig.eSlotType = static_cast<EEquipTrumpSlotType>(pCFG->_EquipTrumpType - 204);
                break;
            default:
                LOG_CRI << "SEquipTrumpSlotConfig error: " << static_cast<UINT32>(pCFG->_SlotId) << ".";
                return false;
                break;

        }
        sConfig.wMinDujieLevel  = pCFG->_UnlockDujieLevel;
        auto it = _mapSlotConfig.find(pCFG->_SlotId);
        if (it == _mapSlotConfig.end())
            _mapSlotConfig[pCFG->_SlotId] = sConfig;
        else
        {
            LOG_CRI << "SEquipTrumpSlotConfig conflict: " << static_cast<UINT32>(pCFG->_SlotId) << ".";
            return false;
        }
    }
    return true;
}

bool CEquipTrumpMgr::LoadMergeConfig(const string& strPath)
{
    CItemUpgradeLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "CItemUpgradeLoader fails! Path: " << strPath;
        return false;
    }

    for(auto & rPair : _mapMergeConfig)
    {
        if (rPair.second)
            delete rPair.second;
    }
    _mapMergeConfig.clear();
    for(auto & pCFG :oLoader._vecData)
    {
        if (!pCFG)
        {
            LOG_CRI << "pCFG = NULL.";
            return false;
        }

        auto it = _mapMergeConfig.find(pCFG->_ItemID);
        if (it == _mapMergeConfig.end())
        {
            SEquipTrumpMergeConfig* pNewCFG = new SEquipTrumpMergeConfig;
            pNewCFG->wItemID = pCFG->_ItemID;
            pNewCFG->dwSilver = pCFG->_RequiredSilver;

            Tokenizer tk(pCFG->_RequiredItem, "|");
            for (size_t i = 0; i < tk.size(); ++i)
            {               
                Tokenizer tk2(tk[i], ",");
                if (tk2.size() != 2)
                {
                    LOG_CRI << pCFG->_ItemID << " Wrong RequiredItem: " << pCFG->_RequiredItem << ".";
                    return false;
                }
                UINT16 wItemID = atoi(tk2[0].c_str());
                UINT16 wItemCount = atoi(tk2[1].c_str());
                // TODO: 这里物品最好检查一下
                pNewCFG->vecMaterial.push_back(SItemCount(wItemID, wItemCount));
            }               
            _mapMergeConfig[pCFG->_ItemID] = pNewCFG;
        }
        else
        {
            LOG_CRI << "SItemUpgradeCFG conflict: " << static_cast<UINT32>(pCFG->_ItemID) << ".";
            return false;
        }
    }
    return true;
}

bool CEquipTrumpMgr::LoadBreakConfig(const string& strPath)
{
    CEquipTrumpRecycleLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "CEquipTrumpRecycleLoader fails! Path: " << strPath;
        return false;
    }

    for(auto & rPair : _mapBreakConfig)
    {
        if (rPair.second)
            delete rPair.second;
    }
    _mapBreakConfig.clear();
    for(auto & pCFG :oLoader._vecData)
    {
        if (!pCFG)
        {
            LOG_CRI << "pCFG = NULL.";
            return false;
        }
        UINT32 dwID = static_cast<UINT32>(pCFG->_EquipTrumpId) << 16 | pCFG->_Level;

        auto it = _mapBreakConfig.find(dwID);
        if (it == _mapBreakConfig.end())
        {
            SEquipTrumpRecycleCFG* pNewCFG = new SEquipTrumpRecycleCFG;
            memcpy(pNewCFG, pCFG, sizeof(SEquipTrumpRecycleCFG));
            _mapBreakConfig[dwID] = pNewCFG;
        }
        else
        {
            LOG_CRI << "SEquipTrumpRecycleCFG conflict: " << static_cast<UINT32>(pCFG->_EquipTrumpId) << ".";
            return false;
        }
    }
    return true;
}

bool CEquipTrumpMgr::LoadTrumpIntensify(string& strFile)
{
        string strTrumpIntensifyPath = Config._strConfigDir + "Conf/Table/TrumpIntensify.xml";
        CTrumpIntensifyLoader oTrumpIntensifyLoader;
        if(!oTrumpIntensifyLoader.LoadData(strTrumpIntensifyPath))
        {
            LOG_CRI << "CTrumpIntensifyLoaderLoader fails! Path: " << strTrumpIntensifyPath;
            return false;
        }

        _mapTrumpIntensifyCFGExPtr.clear();

        for(size_t i  = 0; i < oTrumpIntensifyLoader._vecData.size(); ++i)
        {
            if(NULL == oTrumpIntensifyLoader._vecData[i])
            {
                LOG_CRI << "CTrumpIntensifyLoaderLoader Error! Path: " << strTrumpIntensifyPath;
                return false;
            }

            if(oTrumpIntensifyLoader._vecData[i]->_Type != 2)
            {
                continue;
            }

            STrumpIntensifyCFGExPtr pTrumpIntensifyCFG(new STrumpIntensifyCFGEx);
            pTrumpIntensifyCFG->CopyFrom(*oTrumpIntensifyLoader._vecData[i]);

            UINT32 dwStrongID = GetStrengthID(pTrumpIntensifyCFG->_ItemAttrID,pTrumpIntensifyCFG->_Level);
            _mapTrumpIntensifyCFGExPtr[dwStrongID] = pTrumpIntensifyCFG;
            
            VECATTR_RESET(pTrumpIntensifyCFG->_vecAttr);
            PHYATK_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            MGCATK_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            PHYDEF_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            MGCDEF_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            PHYRDC_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            MGCRDC_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            MAXHP_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            SPEED_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            HIT_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            HITRATE_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            DODGE_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            DODGERATE_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            CRITICAL_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            CRTRATE_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            ANTICRITCAL_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            ANTICRTRATE_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            BLOCK_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            BLOCKRATE_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            PIERCE_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            PIERCERATE_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            COUNTER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            COUNTERRATE_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            RESIST_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            RESISTRATE_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            INITAURA_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            MAXAURA_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            CRIEXTRAADD_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            CRIEXTRARDC_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            METALATK_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            WOODATK_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            WATERATK_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            FIREATK_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            EARTHATK_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            METALDEF_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            WOODDEF_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            WATERDEF_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            FIREDEF_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            EARTHDEF_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            PHYATK_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            MGCATK_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            PHYDEF_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            MGCDEF_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            MAXHP_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            SPEED_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            HIT_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            DODGE_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            CRITICAL_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            ANTICRITCAL_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            BLOCK_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            PIERCE_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            COUNTER_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            RESIST_PER_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
            ANTIEFFECT_ADD(pTrumpIntensifyCFG->_vecAttr, pTrumpIntensifyCFG);
        }

        return true;
}

SStrengthProbabilityCFGExPtr CEquipTrumpMgr::GetStrengthProbabilityCFGEx(UINT32 dwStrongID)
{
    auto itr = _mapStrengthProbabilityCFGExPtr.find(dwStrongID);
    if(itr != _mapStrengthProbabilityCFGExPtr.end())
    {
        return itr->second;
    }
    return NULL;
}

SXiLianCFGExPtr CEquipTrumpMgr::GetXiLianCFGEx(UINT32 dwXiLianID)
{

    auto itr = _mapXiLianCFGExPtr.find(dwXiLianID);
    if(itr != _mapXiLianCFGExPtr.end())
    {
        return itr->second;
    }

    return NULL;
}

const CEquipTrumpMgr::MapSlotConfig& CEquipTrumpMgr::GetSlotConfig() const
{
    return _mapSlotConfig;
}

STrumpIntensifyCFGExPtr CEquipTrumpMgr::GetTrumpIntensify(UINT32 dwItemAttrID,UINT16 wLevel)
{
    UINT32 dwStrongID = GetStrengthID(dwItemAttrID,wLevel);

    auto itr = _mapTrumpIntensifyCFGExPtr.find(dwStrongID);
    if(itr != _mapTrumpIntensifyCFGExPtr.end())
    {
        return itr->second;
    }

    return NULL;
}

UINT32 CEquipTrumpMgr::GetBreakLootID(UINT16 wItemID, UINT8 byLevel) const
{
    UINT32 dwID = static_cast<UINT32>(wItemID) << 16 | byLevel;
    auto it = _mapBreakConfig.find(dwID);
    if (it == _mapBreakConfig.end() || !(it->second))
        return 0;
    return it->second->_LootId;
}

void CEquipTrumpMgr::GetMaterial(UINT16 wItemID, map<UINT16, UINT32>& rmapMaterial) const
{
    auto it = _mapMergeConfig.find(wItemID);
    if (it == _mapMergeConfig.end() && !it->second)
        return;
    for (auto& rInfo : it->second->vecMaterial)
    {
        rmapMaterial[rInfo.wItemID] += rInfo.wCount;
    }
}

UINT32 CEquipTrumpMgr::GetMergeCost(UINT16 wItemID) const
{
    auto it = _mapMergeConfig.find(wItemID);
    if (it == _mapMergeConfig.end() && !it->second)
        return 0;
    return it->second->dwSilver;
}

