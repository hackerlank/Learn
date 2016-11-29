
#include "stdafx.h"
#include "ItemMgr.h"
#include "Protocols.h"
#include "GameScript.h"
#include "CittaMgr.h"
#include "Trump.h"
#include "EquipTrump.h"
#include "Fighter.h"
#include "Tokenizer.h"
#include "UpgradeCFG.h"
#include "GUIDMgr.h"

#include "Gemstone.h"

static TSetUINT16 s_setNoneID;

UINT64 CItemMgr::_qwVersion = VERSION_INIT;
map<UINT16, SItemInfo> CItemMgr::_mapID2ItemInfo;
map<UINT16, SItemTimeInfo> CItemMgr::_mapID2TimeInfo;
map<UINT16, SItemAttrCFGEx> CItemMgr::_mapID2ItemAttrInfo;
map<UINT16, SBagCostCFG> CItemMgr::_mapID2BagCostCfg;
map<UINT16, SDepotCostCFG> CItemMgr::_mapID2DepotCostCfg;
map<UINT32, SIntensifyCFG> CItemMgr::_mapJobLevel2IntensifyCfg;
vector<SFashionCFG> CItemMgr::_vecLevel2FashionExp;
map<UINT16, std::vector<SFashionAttrCFG>> CItemMgr::_mapIDLevel2FashionAttr;
map<UINT8, std::vector<SMallCFG>> CItemMgr::_mapMallType2MallCfg;
map<UINT8, SChongZhiCFGEx> CItemMgr::_mapID2ChongZhiCfg;
map<UINT16,map<UINT16,UINT32> > CItemMgr::_mapUpgrade;

    template<typename T, typename V>
V* GetValFromMap(std::map<T, V>& rMap, const T& t)
{
    auto it = rMap.find(t);
    if(it != rMap.end())
        return &it->second;
    return NULL;
}

bool CItemMgr::Init()
{
    return LoadConfig();
}

bool CItemMgr::LoadConfig(bool bReload /* = false */)
{
    string strPath = Config._strConfigDir + "Conf/Table/ItemAttr.xml";
    {
        CItemAttrLoader oItemAttrLoader;
        if(!oItemAttrLoader.LoadData(strPath))
        {
            LOG_CRI << "oItemLoader.LoadData fails! Path: " << strPath;
            return false;
        }

        for(size_t i = 0; i < oItemAttrLoader._vecData.size(); ++i)
        {
            SItemAttrCFG* pItemAttrCfg = oItemAttrLoader._vecData[i];
            SItemAttrCFGEx& rItemAttrCfg = _mapID2ItemAttrInfo[pItemAttrCfg->_ID];
            rItemAttrCfg.SetConfig(*pItemAttrCfg);
            rItemAttrCfg.dwPeerless = SkillMgr.GetSkillIDQualityLevel(pItemAttrCfg->_Skill, 1);
            Tokenizer tk(rItemAttrCfg._PassSkills, "|"); // XXX: SKillID[[,SkillLevel]|SKillID[,SkillLevel]...]
            for (size_t i = 0; i < tk.size(); ++i)
            {
                Tokenizer yatk(tk[i], ",");
                UINT32 dwSkillID = atoi(yatk[0].c_str());
                if (dwSkillID)
                {
                    UINT32 dwLevel = 1;
                    if (yatk.size() > 1)
                        dwLevel = atoi(yatk[1].c_str());
                    rItemAttrCfg.vecPassSkills.push_back(SkillMgr.GetSkillIDQualityLevel(dwSkillID, dwLevel));
                }
            }
            {
                Tokenizer tk(rItemAttrCfg._LockOne, "|"); // XXX: ID;Count|ID;Count...
                for (size_t i = 0; i < tk.size(); ++i)
                {
                    Tokenizer yatk(tk[i], ";");
                    if (yatk.size())
                    {
                        UINT16 wItemID = atoi(yatk[0].c_str());
                        UINT16 wCount = 1;
                        if (yatk.size() > 1)
                            wCount = atoi(yatk[1].c_str());

                        rItemAttrCfg.vecLockOne.push_back(SItemCount(wItemID, wCount));
                    }
                }
            }

            {
                Tokenizer tk(rItemAttrCfg._LockTwo, "|"); // XXX: ID;Count|ID;Count...
                for (size_t i = 0; i < tk.size(); ++i)
                {
                    Tokenizer yatk(tk[i], ";");
                    if (yatk.size())
                    {
                        UINT16 wItemID = atoi(yatk[0].c_str());
                        UINT16 wCount = 1;
                        if (yatk.size() > 1)
                            wCount = atoi(yatk[1].c_str());

                        rItemAttrCfg.vecLockTwo.push_back(SItemCount(wItemID, wCount));
                    }
                }
            }
        }
    }

    strPath = Config._strConfigDir + "Conf/Table/Item.xml";
    {
        CItemLoader oItemLoader;
        if(!oItemLoader.LoadData(strPath))
        {
            LOG_CRI << "oItemLoader.LoadData fails! Path: " << strPath;
            return false;
        }

        for(size_t i = 0; i < oItemLoader._vecData.size(); ++i)
        {
            SItemCFG* pItemCfg = oItemLoader._vecData[i];
            if(pItemCfg->_ID != 0)
            {
                if(!LoadItemConfig(*pItemCfg, bReload))
                {
                    LOG_CRI << "LoadItemConfig fails!";
                    return false;
                }
            }
        }
    }

    strPath = Config._strConfigDir + "Conf/Table/ItemTime.xml";
    {
        CItemTimeLoader oItemTimeLoader;
        if(!oItemTimeLoader.LoadData(strPath))
        {
            LOG_CRI << "oItemTimeLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        stringstream ss;
        using boost::posix_time::ptime;
        using boost::local_time::local_time_input_facet;
        local_time_input_facet* input_facet = new local_time_input_facet;
        if(input_facet == NULL)
        {
            LOG_CRI << "input_facet is NULL!";
            return false;
        }
        input_facet->format("%Y-%m-%d %H:%M:%S");
        ss.imbue(locale(ss.getloc(), input_facet));
        ptime pt;
        for(size_t i = 0; i < oItemTimeLoader._vecData.size(); ++i)
        {
            SItemTimeCFG* pItemTimeCFG = oItemTimeLoader._vecData[i];
            if(pItemTimeCFG->_ID != 0)
            {
                SItemTimeInfo& rItemTimeInfo = _mapID2TimeInfo[pItemTimeCFG->_ID];
                rItemTimeInfo.oTimeCfg = *pItemTimeCFG;
                if(pItemTimeCFG->_ExpireTime.size() > 10)
                {
                    ss << pItemTimeCFG->_ExpireTime;
                    ss >> pt;
                    tm t = boost::posix_time::to_tm(pt);
                    rItemTimeInfo.tExpireTime = mktime(&t);
                }
            }
        }
    }

    strPath = Config._strConfigDir + "Conf/Table/BagCost.xml";
    {
        CBagCostLoader oBagCostLoader;
        if(!oBagCostLoader.LoadData(strPath))
        {
            LOG_CRI << "oBagCostLoader.LoadData fails! Path: " << strPath;
            return false;
        }

        for(size_t i = 0; i < oBagCostLoader._vecData.size(); ++i)
        {
            SBagCostCFG* pBagCostCfg = oBagCostLoader._vecData[i];
            if(pBagCostCfg->_Idx != 0)
            {
                SBagCostCFG& rBagCostCfg = _mapID2BagCostCfg[pBagCostCfg->_Idx];
                rBagCostCfg = *pBagCostCfg;
            }
        }
    }

    strPath = Config._strConfigDir + "Conf/Table/DepotCost.xml";
    {
        CDepotCostLoader oDepotCostLoader;
        if(!oDepotCostLoader.LoadData(strPath))
        {
            LOG_CRI << "oDepotCostLoader.LoadData fails! Path: " << strPath;
            return false;
        }

        for(size_t i = 0; i < oDepotCostLoader._vecData.size(); ++i)
        {
            SDepotCostCFG* pDepotCostCfg = oDepotCostLoader._vecData[i];
            if(pDepotCostCfg->_Idx != 0)
            {
                SDepotCostCFG& rDepotCostCfg = _mapID2DepotCostCfg[pDepotCostCfg->_Idx];
                rDepotCostCfg._Idx = pDepotCostCfg->_Idx;
                rDepotCostCfg._Cost = pDepotCostCfg->_Cost;
            }
        }
    }

    strPath = Config._strConfigDir + "Conf/Table/Intensify.xml";
    {
        CIntensifyLoader oIntensifyLoader;
        if(!oIntensifyLoader.LoadData(strPath))
        {
            LOG_CRI << "oIntensifyLoader.LoadData fails! Path: " << strPath;
            return false;
        }

        for(size_t i = 0; i < oIntensifyLoader._vecData.size(); ++i)
        {
            SIntensifyCFG* pIntensifyCfg = oIntensifyLoader._vecData[i];
            SIntensifyCFG& rIntensifyCfg = _mapJobLevel2IntensifyCfg[MAKE_JOBLEVELEQUIPKEY(pIntensifyCfg->_Job, pIntensifyCfg->_ArmorType, pIntensifyCfg->_IntensifyLevel)];
            rIntensifyCfg = *pIntensifyCfg;
        }
    }

    strPath = Config._strConfigDir + "Conf/Table/Fashion.xml";
    {
        CFashionLoader oFashionLoader;
        if(!oFashionLoader.LoadData(strPath))
        {
            LOG_CRI << "oFashionLoader.LoadData fails! Path: " << strPath;
            return false;
        }

        if (bReload)
            _vecLevel2FashionExp.clear();
        for(size_t i = 0; i < oFashionLoader._vecData.size(); ++i)
        {
            SFashionCFG* pFashionCfg = oFashionLoader._vecData[i];
            _vecLevel2FashionExp.push_back(*pFashionCfg);
        }
    }

    strPath = Config._strConfigDir + "Conf/Table/FashionAttr.xml";
    {
        CFashionAttrLoader oFashionAttrLoader;
        if(!oFashionAttrLoader.LoadData(strPath))
        {
            LOG_CRI << "oFashionAttrLoader.LoadData fails! Path: " << strPath;
            return false;
        }

        UINT16 wLastID = 0;
        for(size_t i = 0; i < oFashionAttrLoader._vecData.size(); ++i)
        {
            SFashionAttrCFG* pFashionAttrCfg = oFashionAttrLoader._vecData[i];
            std::vector<SFashionAttrCFG>& rVec = _mapIDLevel2FashionAttr[pFashionAttrCfg->_ID];
            if (bReload && wLastID != pFashionAttrCfg->_ID)
                rVec.clear();
            rVec.push_back(*pFashionAttrCfg);
            wLastID = pFashionAttrCfg->_ID;
        }
    }

    strPath = Config._strConfigDir + "Conf/Table/Mall.xml";
    if (!LoadMallCfg(strPath))
        return false;
    strPath = Config._strConfigDir + "Conf/Table/ChongZhi.xml";
    if (!LoadChongZhiCfg(strPath))
        return false;

    if (bReload)
        _mapUpgrade.clear();
    strPath = Config._strConfigDir + "Conf/Table/Upgrade.xml";
    {
        CUpgradeLoader oUpgradeLoader;
        if(!oUpgradeLoader.LoadData(strPath))
        {
            LOG_CRI  << "LOAD " << strPath << "ERR";
        }
        for(size_t i = 0; i < oUpgradeLoader._vecData.size(); ++i)
        {
            SUpgradeCFG* pCfg = oUpgradeLoader._vecData[i];
            Tokenizer tk(pCfg->_MaterialItemId, "|"); // XXX: ID;Count|ID;Count...
            UINT16 wItemID = pCfg->_TargetItemId;
            if(wItemID == 0)
                continue;
            for (size_t i = 0; i < tk.size(); ++i)
            {
                Tokenizer subtk(tk[i], ";");
                if (subtk.size() != 2)
                {
                    LOG_CRI  << "LOAD " << strPath << "ERR";
                }
                UINT16 wID = atoi(subtk[0].c_str());
                UINT32 dwNum = atoi(subtk[1].c_str());
                if(wID == 0 || dwNum ==0 )
                {
                    LOG_CRI  << "LOAD " << strPath << "ERR";
                }
                _mapUpgrade[wItemID][wID] = dwNum;
            }


        }
    }

    if (bReload)
        ++_qwVersion;
    return true;
}

bool CItemMgr::ReLoadConfig(const string &strFile)
{
    bool bReload = true;
    string strPath;
    if("ItemAttr.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/ItemAttr.xml";
        {
            CItemAttrLoader oItemAttrLoader;
            if(!oItemAttrLoader.LoadData(strPath))
            {
                LOG_CRI << "oItemLoader.LoadData fails! Path: " << strPath;
                return false;
            }

            for(size_t i = 0; i < oItemAttrLoader._vecData.size(); ++i)
            {
                SItemAttrCFG* pItemAttrCfg = oItemAttrLoader._vecData[i];
                SItemAttrCFGEx& rItemAttrCfg = _mapID2ItemAttrInfo[pItemAttrCfg->_ID];
                rItemAttrCfg.SetConfig(*pItemAttrCfg);
                rItemAttrCfg.dwPeerless = SkillMgr.GetSkillIDQualityLevel(pItemAttrCfg->_Skill, 1);
                Tokenizer tk(rItemAttrCfg._PassSkills, "|"); // XXX: SKillID[[,SkillLevel]|SKillID[,SkillLevel]...]
                for (size_t i = 0; i < tk.size(); ++i)
                {
                    Tokenizer yatk(tk[i], ",");
                    UINT32 dwSkillID = atoi(yatk[0].c_str());
                    if (dwSkillID)
                    {
                        UINT32 dwLevel = 1;
                        if (yatk.size() > 1)
                            dwLevel = atoi(yatk[1].c_str());
                        rItemAttrCfg.vecPassSkills.push_back(SkillMgr.GetSkillIDQualityLevel(dwSkillID, dwLevel));
                    }
                }
                {
                    Tokenizer tk(rItemAttrCfg._LockOne, "|"); // XXX: ID;Count|ID;Count...
                    for (size_t i = 0; i < tk.size(); ++i)
                    {
                        Tokenizer yatk(tk[i], ";");
                        if (yatk.size())
                        {
                            UINT16 wItemID = atoi(yatk[0].c_str());
                            UINT16 wCount = 1;
                            if (yatk.size() > 1)
                                wCount = atoi(yatk[1].c_str());

                            rItemAttrCfg.vecLockOne.push_back(SItemCount(wItemID, wCount));
                        }
                    }
                }

                {
                    Tokenizer tk(rItemAttrCfg._LockTwo, "|"); // XXX: ID;Count|ID;Count...
                    for (size_t i = 0; i < tk.size(); ++i)
                    {
                        Tokenizer yatk(tk[i], ";");
                        if (yatk.size())
                        {
                            UINT16 wItemID = atoi(yatk[0].c_str());
                            UINT16 wCount = 1;
                            if (yatk.size() > 1)
                                wCount = atoi(yatk[1].c_str());

                            rItemAttrCfg.vecLockTwo.push_back(SItemCount(wItemID, wCount));
                        }
                    }
                }
            }
        }
    }else if("Item.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/Item.xml";
        {
            CItemLoader oItemLoader;
            if(!oItemLoader.LoadData(strPath))
            {
                LOG_CRI << "oItemLoader.LoadData fails! Path: " << strPath;
                return false;
            }

            for(size_t i = 0; i < oItemLoader._vecData.size(); ++i)
            {
                SItemCFG* pItemCfg = oItemLoader._vecData[i];
                if(pItemCfg->_ID != 0)
                {
                    if(!LoadItemConfig(*pItemCfg, bReload))
                    {
                        LOG_CRI << "LoadItemConfig fails!";
                        return false;
                    }
                }
            }
        }
    }else if("ItemTime.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/ItemTime.xml";
        {
            CItemTimeLoader oItemTimeLoader;
            if(!oItemTimeLoader.LoadData(strPath))
            {
                LOG_CRI << "oItemTimeLoader.LoadData fails! Path: " << strPath;
                return false;
            }
            stringstream ss;
            using boost::posix_time::ptime;
            using boost::local_time::local_time_input_facet;
            local_time_input_facet* input_facet = new local_time_input_facet;
            if(input_facet == NULL)
            {
                LOG_CRI << "input_facet is NULL!";
                return false;
            }
            input_facet->format("%Y-%m-%d %H:%M:%S");
            ss.imbue(locale(ss.getloc(), input_facet));
            ptime pt;
            for(size_t i = 0; i < oItemTimeLoader._vecData.size(); ++i)
            {
                SItemTimeCFG* pItemTimeCFG = oItemTimeLoader._vecData[i];
                if(pItemTimeCFG->_ID != 0)
                {
                    SItemTimeInfo& rItemTimeInfo = _mapID2TimeInfo[pItemTimeCFG->_ID];
                    rItemTimeInfo.oTimeCfg = *pItemTimeCFG;
                    if(pItemTimeCFG->_ExpireTime.size() > 10)
                    {
                        ss << pItemTimeCFG->_ExpireTime;
                        ss >> pt;
                        tm t = boost::posix_time::to_tm(pt);
                        rItemTimeInfo.tExpireTime = mktime(&t);
                    }
                }
            }
        }
    }else if("BagCost.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/BagCost.xml";
        {
            CBagCostLoader oBagCostLoader;
            if(!oBagCostLoader.LoadData(strPath))
            {
                LOG_CRI << "oBagCostLoader.LoadData fails! Path: " << strPath;
                return false;
            }

            for(size_t i = 0; i < oBagCostLoader._vecData.size(); ++i)
            {
                SBagCostCFG* pBagCostCfg = oBagCostLoader._vecData[i];
                if(pBagCostCfg->_Idx != 0)
                {
                    SBagCostCFG& rBagCostCfg = _mapID2BagCostCfg[pBagCostCfg->_Idx];
                    rBagCostCfg = *pBagCostCfg;
                }
            }
        }
    }else if("DepotCost.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/DepotCost.xml";
        {
            CDepotCostLoader oDepotCostLoader;
            if(!oDepotCostLoader.LoadData(strPath))
            {
                LOG_CRI << "oDepotCostLoader.LoadData fails! Path: " << strPath;
                return false;
            }

            for(size_t i = 0; i < oDepotCostLoader._vecData.size(); ++i)
            {
                SDepotCostCFG* pDepotCostCfg = oDepotCostLoader._vecData[i];
                if(pDepotCostCfg->_Idx != 0)
                {
                    SDepotCostCFG& rDepotCostCfg = _mapID2DepotCostCfg[pDepotCostCfg->_Idx];
                    rDepotCostCfg._Idx = pDepotCostCfg->_Idx;
                    rDepotCostCfg._Cost = pDepotCostCfg->_Cost;
                }
            }
        }
    }else if("Intensify.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/Intensify.xml";
        {
            CIntensifyLoader oIntensifyLoader;
            if(!oIntensifyLoader.LoadData(strPath))
            {
                LOG_CRI << "oIntensifyLoader.LoadData fails! Path: " << strPath;
                return false;
            }

            for(size_t i = 0; i < oIntensifyLoader._vecData.size(); ++i)
            {
                SIntensifyCFG* pIntensifyCfg = oIntensifyLoader._vecData[i];
                SIntensifyCFG& rIntensifyCfg = _mapJobLevel2IntensifyCfg[MAKE_JOBLEVELEQUIPKEY(pIntensifyCfg->_Job, pIntensifyCfg->_ArmorType, pIntensifyCfg->_IntensifyLevel)];
                rIntensifyCfg = *pIntensifyCfg;
            }
        }
    }else if("Fashion.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/Fashion.xml";
        {
            CFashionLoader oFashionLoader;
            if(!oFashionLoader.LoadData(strPath))
            {
                LOG_CRI << "oFashionLoader.LoadData fails! Path: " << strPath;
                return false;
            }

            if (bReload)
                _vecLevel2FashionExp.clear();
            for(size_t i = 0; i < oFashionLoader._vecData.size(); ++i)
            {
                SFashionCFG* pFashionCfg = oFashionLoader._vecData[i];
                _vecLevel2FashionExp.push_back(*pFashionCfg);
            }
        }
    }else if("FashionAttr.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/FashionAttr.xml";
        {
            CFashionAttrLoader oFashionAttrLoader;
            if(!oFashionAttrLoader.LoadData(strPath))
            {
                LOG_CRI << "oFashionAttrLoader.LoadData fails! Path: " << strPath;
                return false;
            }

            UINT16 wLastID = 0;
            for(size_t i = 0; i < oFashionAttrLoader._vecData.size(); ++i)
            {
                SFashionAttrCFG* pFashionAttrCfg = oFashionAttrLoader._vecData[i];
                std::vector<SFashionAttrCFG>& rVec = _mapIDLevel2FashionAttr[pFashionAttrCfg->_ID];
                if (bReload && wLastID != pFashionAttrCfg->_ID)
                    rVec.clear();
                rVec.push_back(*pFashionAttrCfg);
                wLastID = pFashionAttrCfg->_ID;
            }
        }
    }else if("Mall.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/Mall.xml";
        if (!LoadMallCfg(strPath))
            return false;
    }else if("ChongZhi.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/ChongZhi.xml";
        if (!LoadChongZhiCfg(strPath))
            return false;
    } else if("Upgrade.xml" == strFile) 
    {
        _mapUpgrade.clear();
        strPath = Config._strConfigDir + "Conf/Table/Upgrade.xml";
        CUpgradeLoader oUpgradeLoader;
        if(!oUpgradeLoader.LoadData(strPath))
        {
            LOG_CRI  << "LOAD " << strPath << "ERR";
        }
        for(size_t i = 0; i < oUpgradeLoader._vecData.size(); ++i)
        {
            SUpgradeCFG* pCfg = oUpgradeLoader._vecData[i];
            Tokenizer tk(pCfg->_MaterialItemId, "|"); // XXX: ID;Count|ID;Count...
            UINT16 wItemID = pCfg->_TargetItemId;
            if(wItemID == 0)
                continue;
            for (size_t i = 0; i < tk.size(); ++i)
            {
                Tokenizer subtk(tk[i], ";");
                if (subtk.size() != 2)
                {
                    LOG_CRI  << "LOAD " << strPath << "ERR";
                }
                UINT16 wID = atoi(subtk[0].c_str());
                UINT32 dwNum = atoi(subtk[1].c_str());
                if(wID == 0 || dwNum ==0 )
                {
                    LOG_CRI  << "LOAD " << strPath << "ERR";
                }
                _mapUpgrade[wItemID][wID] = dwNum;
            }


        }
    }

    if (bReload)
        ++_qwVersion;
    return true;
}

bool CItemMgr::LoadMallCfg(string& strPath)
{
    _mapMallType2MallCfg.clear();
    CMallLoader oMallLoader;
    if(!oMallLoader.LoadData(strPath))
    {
        LOG_CRI << "oMallLoader.LoadData fails! Path: " << strPath;
        return false;
    }

    for(size_t i = 0; i < oMallLoader._vecData.size(); ++i)
    {
        SMallCFG* pMallCfg = oMallLoader._vecData[i];
        std::vector<SMallCFG>& rVec = _mapMallType2MallCfg[pMallCfg->_Type];
        rVec.push_back(*pMallCfg);
    }
    return true;
}

bool CItemMgr::LoadChongZhiCfg(string& strPath)
{
    _mapID2ChongZhiCfg.clear();
    CChongZhiLoader oChongZhiLoader;
    if(!oChongZhiLoader.LoadData(strPath))
    {
        LOG_CRI << "oChongZhiLoader.LoadData fails! Path: " << strPath;
        return false;
    }

    for(size_t i = 0; i < oChongZhiLoader._vecData.size(); ++i)
    {
        SChongZhiCFG* pChongZhiCFG = oChongZhiLoader._vecData[i];
        if(pChongZhiCFG->_Id == 0)
            continue;
        SChongZhiCFGEx& rChongZhiCFGEx = _mapID2ChongZhiCfg[pChongZhiCFG->_Id];
        rChongZhiCFGEx.SetConfig(*pChongZhiCFG);

        Tokenizer tk(rChongZhiCFGEx._Gift, "|");
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
            rChongZhiCFGEx._vecItemAward.push_back(stItemGen);
        }
    }
    return true;
}

UINT8 CItemMgr::FashionExpToLevel(UINT32 dwExp)
{
    size_t size = _vecLevel2FashionExp.size();
    if (!size)
        return 1;
    for (size_t i = 0; i < size; ++ i)
    {
        if (dwExp < _vecLevel2FashionExp[i]._Exp)
            return _vecLevel2FashionExp[i]._Level;
    }
    return size;
}

UINT32 CItemMgr::LevelToFashionExp(UINT8 byLevel)
{
    size_t size = _vecLevel2FashionExp.size();
    if (!size || !byLevel)
        return 0;
    if (byLevel > size)
        return _vecLevel2FashionExp[size-1]._Exp;
    for (size_t i = 0; i < size; ++ i)
    {
        if (_vecLevel2FashionExp[i]._Level == byLevel)
            return _vecLevel2FashionExp[i]._Exp;
    }
    return 0;
}

bool CItemMgr::FashionTestLevelUp(UINT8& byLevel, UINT32& dwExp)
{
    if (!byLevel)
        byLevel = 1;
    size_t size = _vecLevel2FashionExp.size();
    if (byLevel >= size)
    {
        dwExp = _vecLevel2FashionExp[size-1]._Exp;
        return false;
    }

    bool r = false;
    while (byLevel <= size && _vecLevel2FashionExp[byLevel-1]._Exp > 0 && dwExp >= _vecLevel2FashionExp[byLevel-1]._Exp)
    {
        r = true;
        ++byLevel;
    }

    if (byLevel >= size)
    {
        byLevel = size;
        dwExp = _vecLevel2FashionExp[size-1]._Exp;
    }
    return r;
}

UINT8 CItemMgr::GetFashionLevelMax()
{
    return _vecLevel2FashionExp.size();
}

// 将属性表转为将领属性vector
bool CItemMgr::AppendAttr2(UINT16 wAttrID, TVecFloat& rvecAttr)
{
    SItemAttrCFGEx* pItemAttrCFG = GetValFromMap(_mapID2ItemAttrInfo, wAttrID);
    if (!pItemAttrCFG)
        return false;
    PHYATK_ADD(rvecAttr, pItemAttrCFG);
    MGCATK_ADD(rvecAttr, pItemAttrCFG);
    PHYDEF_ADD(rvecAttr, pItemAttrCFG);
    MGCDEF_ADD(rvecAttr, pItemAttrCFG);
    PHYRDC_ADD(rvecAttr, pItemAttrCFG);
    MGCRDC_ADD(rvecAttr, pItemAttrCFG);
    MAXHP_ADD(rvecAttr, pItemAttrCFG);
    SPEED_ADD(rvecAttr, pItemAttrCFG);
    HIT_ADD(rvecAttr, pItemAttrCFG);
    HITRATE_ADD(rvecAttr, pItemAttrCFG);
    DODGE_ADD(rvecAttr, pItemAttrCFG);
    DODGERATE_ADD(rvecAttr, pItemAttrCFG);
    CRITICAL_ADD(rvecAttr, pItemAttrCFG);
    CRTRATE_ADD(rvecAttr, pItemAttrCFG);
    ANTICRITCAL_ADD(rvecAttr, pItemAttrCFG);
    ANTICRTRATE_ADD(rvecAttr, pItemAttrCFG);
    BLOCK_ADD(rvecAttr, pItemAttrCFG);
    BLOCKRATE_ADD(rvecAttr, pItemAttrCFG);
    PIERCE_ADD(rvecAttr, pItemAttrCFG);
    PIERCERATE_ADD(rvecAttr, pItemAttrCFG);
    COUNTER_ADD(rvecAttr, pItemAttrCFG);
    COUNTERRATE_ADD(rvecAttr, pItemAttrCFG);
    RESIST_ADD(rvecAttr, pItemAttrCFG);
    RESISTRATE_ADD(rvecAttr, pItemAttrCFG);
    INITAURA_ADD(rvecAttr, pItemAttrCFG);
    MAXAURA_ADD(rvecAttr, pItemAttrCFG);
    CRIEXTRAADD_ADD(rvecAttr, pItemAttrCFG);
    CRIEXTRARDC_ADD(rvecAttr, pItemAttrCFG);
    METALATK_ADD(rvecAttr, pItemAttrCFG);
    WOODATK_ADD(rvecAttr, pItemAttrCFG);
    WATERATK_ADD(rvecAttr, pItemAttrCFG);
    FIREATK_ADD(rvecAttr, pItemAttrCFG);
    EARTHATK_ADD(rvecAttr, pItemAttrCFG);
    METALDEF_ADD(rvecAttr, pItemAttrCFG);
    WOODDEF_ADD(rvecAttr, pItemAttrCFG);
    WATERDEF_ADD(rvecAttr, pItemAttrCFG);
    FIREDEF_ADD(rvecAttr, pItemAttrCFG);
    EARTHDEF_ADD(rvecAttr, pItemAttrCFG);
    PHYATK_PER_ADD(rvecAttr, pItemAttrCFG);
    MGCATK_PER_ADD(rvecAttr, pItemAttrCFG);
    PHYDEF_PER_ADD(rvecAttr, pItemAttrCFG);
    MGCDEF_PER_ADD(rvecAttr, pItemAttrCFG);
    MAXHP_PER_ADD(rvecAttr, pItemAttrCFG);
    SPEED_PER_ADD(rvecAttr, pItemAttrCFG);
    HIT_PER_ADD(rvecAttr, pItemAttrCFG);
    DODGE_PER_ADD(rvecAttr, pItemAttrCFG);
    CRITICAL_PER_ADD(rvecAttr, pItemAttrCFG);
    ANTICRITCAL_PER_ADD(rvecAttr, pItemAttrCFG);
    BLOCK_PER_ADD(rvecAttr, pItemAttrCFG);
    PIERCE_PER_ADD(rvecAttr, pItemAttrCFG);
    COUNTER_PER_ADD(rvecAttr, pItemAttrCFG);
    RESIST_PER_ADD(rvecAttr, pItemAttrCFG);
    ANTIEFFECT_ADD(rvecAttr, pItemAttrCFG);
    //COUTEREXTRAADD_ADD(rvecAttr, pItemAttrCFG);
    //COUTEREXTRARDC_ADD(rvecAttr, pItemAttrCFG);
    return true;
}

bool CItemMgr::LoadItemConfig(const SItemCFG& rItemCfg, bool bReload /*= false*/)
{
    UINT16 wItemID = rItemCfg._ID;
    SItemInfo& rItemInfo = _mapID2ItemInfo[wItemID];
    rItemInfo.oItemCfg = rItemCfg;
    if (rItemCfg._AttrIdx_1 && !rItemInfo.pItemAttr)
    {
        auto i = _mapID2ItemAttrInfo.find(rItemCfg._AttrIdx_1);
        if (i != _mapID2ItemAttrInfo.end())
            rItemInfo.pItemAttr = &i->second;
    }
    if (rItemCfg._AttrIdx_2 && !rItemInfo.pItemAttrActive)
    {
        auto i = _mapID2ItemAttrInfo.find(rItemCfg._AttrIdx_2);
        if (i != _mapID2ItemAttrInfo.end())
            rItemInfo.pItemAttrActive = &i->second;
    }
    if (rItemCfg._AttrIdx_3 && !rItemInfo.pItemAttrExtra)
    {
        auto i = _mapID2ItemAttrInfo.find(rItemCfg._AttrIdx_3);
        if (i != _mapID2ItemAttrInfo.end())
            rItemInfo.pItemAttrExtra = &i->second;
    }
    if (rItemCfg._Useable)
    {
        rItemInfo.bHasOnUseItem = Config.GetScript().HasUseFunction(wItemID);
        if (!rItemInfo.bHasOnUseItem)
            LOG_WRN << "LoadLuaFile fails! Script: Item" << wItemID << ".lua";
    }
    Tokenizer tk(rItemInfo.oItemCfg._EquipConflict, "|");
    for (size_t i = 0; i < tk.size(); ++i)
    {
        UINT16 wItemID = atoi(tk[i].c_str());
        if (wItemID)
            rItemInfo.setEquipConflict.insert(wItemID);
    }
    Tokenizer tk2(rItemInfo.oItemCfg._EquipConflictTeam, "|");
    for (size_t i = 0; i < tk2.size(); ++i)
    {
        UINT16 wItemID = atoi(tk2[i].c_str());
        if (wItemID)
            rItemInfo.setEquipConflict.insert(wItemID);
    }

    return true;
}

CItemPtr CItemMgr::CreateAllTypeItem(UINT16 wItemID, UINT16 wNum /*= 1*/, UINT8 byQuality /*= 0*/)
{
    auto it = _mapID2ItemInfo.find(wItemID);
    if(it == _mapID2ItemInfo.end())
        return NULL;
    SItemCFG& rItemCfg = it->second.oItemCfg;
    switch(CItem::GetItemType(rItemCfg))
    {
        case eItemCitta:
            return CreateCitta(wItemID);
        case eItemTrump:
            return CreateTrump(wItemID);
        case eItemFashion:
            return CreateFashion(wItemID, byQuality);
        case eItemEquipTrump:
            return CreateEquipTrump(wItemID);
            break;
        //case eItemStone:
          //  return CreateGemstone(wItemID);
        default:
            break;
    }
    return CreateItem(wItemID, wNum, byQuality);
}

CItemPtr CItemMgr::CreateAllTypeEmptyItem(UINT16 wItemID)
{
    auto it = _mapID2ItemInfo.find(wItemID);
    if(it == _mapID2ItemInfo.end())
        return NULL;
    SItemCFG& rItemCfg = it->second.oItemCfg;
    switch(CItem::GetItemType(rItemCfg))
    {
        case eItemTrump:
            return CreateEmptyTrump(wItemID);
        case eItemCitta:
            return CreateEmptyCitta(wItemID);
        case eItemEquipTrump:
            return CreateEmptyEquipTrump(wItemID);
        default:
            break;
    }
    return CreateEmptyItem(wItemID);
}

CItemPtr CItemMgr::CreateItem(UINT16 wItemID, UINT16 wNum /*= 1*/, UINT8 byQuality /*= 0*/)
{
    CItemPtr pItem = CreateEmptyItem(wItemID, wNum);
    if(pItem == NULL)
        return NULL;
    if(!AssignItemProp(*pItem, byQuality))
        return NULL;

    pItem->_qwInstID = GET_GUID(GUID_ITEM);
    return pItem;
}

CItemPtr CItemMgr::CreateEmptyItem(UINT16 wItemID, UINT16 wNum /*= 1*/)
{
    if(0 == wNum)
        return NULL;
    auto it = _mapID2ItemInfo.find(wItemID);
    if(it == _mapID2ItemInfo.end())
        return NULL;
    SItemCFG& rItemCfg = it->second.oItemCfg;
    CItemPtr pItem = NULL;
    if(CItem::IsStackItem(rItemCfg))
    {
        if(wNum > CItem::GetMaxNum(rItemCfg))
            return NULL;
        pItem.reset(new CStackItem(wItemID, wNum));
    }
    else
    {
        pItem.reset(new CItem(wItemID));
    }
    return pItem;
}

CItemPtr CItemMgr::CreateItem(const SItem& rItemStream)
{
    switch(rItemStream.GetClassType())
    {
        case eType_SItem:
            {
                CItemPtr pItem = CItemMgr::CreateEmptyItem(rItemStream.sItemInfo.wItemID);
                if(pItem == NULL)
                {
                    LOG_CRI << "Can't create Item: " << rItemStream.sItemInfo.wItemID;
                    return NULL;
                }
                pItem->FromStream(rItemStream);
                return pItem;
            }
            break;

        case eType_SStack:
            {
                const SStack& rStackStream = (const SStack&)rItemStream; // XXX: SStack与SItem是一样的
                CStackItemPtr pStackItem = CItemMgr::CreateEmptyStackItem(rStackStream.sItemInfo.wItemID);
                if(pStackItem == NULL)
                {
                    LOG_CRI << "Can't create Item: " << rStackStream.sItemInfo.wItemID;
                    return NULL;
                }
                pStackItem->FromStream(rStackStream);
                return pStackItem;
            }
            break;

        case eType_SFashion:
            {
                const SFashion& rFashionStream = (const SFashion&)rItemStream;
                CFashionPtr pFashion = CItemMgr::CreateEmptyFashion(rFashionStream.sItemInfo.wItemID);
                if(pFashion == NULL)
                {
                    LOG_CRI << "Can't create Item: " << rFashionStream.sItemInfo.wItemID;
                    return NULL;
                }
                if(!pFashion->FromStream(rFashionStream))
                {
                    LOG_CRI << "FromStream fails! ItemID: " << rFashionStream.sItemInfo.wItemID;
                    return NULL;
                }
                pFashion->InitItemAttr();
                return pFashion;
            }
            break;

        case eType_SCitta:
            {
                const SCitta& rCittaStream = (const SCitta&)rItemStream;
                CCittaPtr pCitta = CItemMgr::CreateEmptyCitta(rCittaStream.sItemInfo.wItemID);
                if(pCitta == NULL)
                {
                    LOG_CRI << "Can't create Item: " << rCittaStream.sItemInfo.wItemID;
                    return NULL;
                }
                if(!pCitta->FromStream(rCittaStream))
                {
                    LOG_CRI << "FromStream fails! ItemID: " << rCittaStream.sItemInfo.wItemID;
                    return NULL;
                }
                pCitta->InitItemAttr();
                return pCitta;
            }

        case eType_STrump:
            {
                const STrump& rTrumpStream = (const STrump&)rItemStream;
                CTrumpPtr pTrump = CItemMgr::CreateEmptyTrump(rTrumpStream.sItemInfo.wItemID);
                if(pTrump == NULL)
                {
                    LOG_CRI << "Can't create Item: " << rTrumpStream.sItemInfo.wItemID;
                    return NULL;
                }
                if(!pTrump->FromStream(rTrumpStream))
                {
                    LOG_CRI << "FromStream fails! ItemID: " << rTrumpStream.sItemInfo.wItemID;
                    return NULL;
                }
                pTrump->InitItemAttr();
                return pTrump;
            }
            break;
        case eType_SGemstone:
            {
                const SGemstone& rGemstoneStream = (const SGemstone&)rItemStream;
                CGemstonePtr pGemstone = CItemMgr::CreateEmptyGemstone(rGemstoneStream.sItemInfo.wItemID);
                if(pGemstone == NULL)
                {
                    LOG_CRI << "Can't create Item: " << rGemstoneStream.sItemInfo.wItemID;
                    return NULL;
                }
                if(!pGemstone->FromStream(rGemstoneStream))
                {
                    LOG_CRI << "FromStream fails! ItemID: " << rGemstoneStream.sItemInfo.wItemID;
                    return NULL;
                }
                return pGemstone;
            }
            break;
        case eType_SEquipTrump:
            {
                const SEquipTrump& rEquipTrumpStream = (const SEquipTrump&)rItemStream;
                CEquipTrumpPtr pEquipTrump = CItemMgr::CreateEmptyEquipTrump(rEquipTrumpStream.sItemInfo.wItemID);
                if(pEquipTrump == NULL)
                {
                    LOG_CRI << "Can't create Item: " << rEquipTrumpStream.sItemInfo.wItemID;
                    return NULL;
                }
                if(!pEquipTrump->FromStream(rEquipTrumpStream))
                {
                    LOG_CRI << "FromStream fails! ItemID: " << rEquipTrumpStream.sItemInfo.wItemID;
                    return NULL;
                }
                return pEquipTrump;
            }
            break;

        default:
            break;

    }

    LOG_CRI << "Invalid type: " << rItemStream.GetClassType();
    return NULL;
}

CFashionPtr CItemMgr::CreateFashion(UINT16 wItemID, UINT8 byQuality/* = 0*/)
{
    CFashionPtr pFashion = CreateEmptyFashion(wItemID);
    if(pFashion == NULL)
        return NULL;
    if(!AssignItemProp(*pFashion, byQuality))
        return NULL;

    pFashion->_qwInstID = GET_GUID(GUID_EQUIP);
    return pFashion;
}

CCittaPtr CItemMgr::CreateCitta(UINT16 wItemID, UINT32 dwSignetID /* = 0 */)
{
    CCittaPtr pCitta = CreateEmptyCitta(wItemID);
    if(pCitta == NULL)
        return NULL;
    if(!AssignItemProp(*pCitta, 0))
        return NULL;

    if(!AssignCittaProp(*pCitta, dwSignetID))
        return NULL;

    pCitta->_qwInstID = GET_GUID(GUID_EQUIP);
    pCitta->SetInited(true);
    return pCitta;
}

CTrumpPtr CItemMgr::CreateTrump(UINT16 wItemID)
{
    CTrumpPtr pTrump = CreateEmptyTrump(wItemID);
    if(pTrump == NULL)
        return NULL;
    if(!AssignItemProp(*pTrump, 0))
        return NULL;

    if(!AssignTrumpProp(*pTrump))
        return NULL;   // Trump   法宝

    pTrump->_qwInstID = GET_GUID(GUID_ITEM);
    return pTrump;
}

CTrumpPtr CItemMgr::CreateEmptyTrump(UINT16 wItemID)
{
    auto itItem = _mapID2ItemInfo.find(wItemID);
    if(itItem == _mapID2ItemInfo.end())
        return NULL;
    return CTrumpPtr(new CTrump(wItemID));
}

CGemstonePtr CItemMgr::CreateGemstone(UINT16 wItemID)
{
    CGemstonePtr pGemstone = CreateEmptyGemstone(wItemID);
    if(pGemstone == NULL)
        return NULL;
    if(!AssignItemProp(*pGemstone, 0))
        return NULL;
    pGemstone->_qwInstID = GET_GUID(GUID_ITEM);
    return pGemstone;

}

CGemstonePtr CItemMgr::CreateEmptyGemstone(UINT16 wItemID)
{
    auto itItem = _mapID2ItemInfo.find(wItemID);
    if(itItem == _mapID2ItemInfo.end())
        return NULL;
    return CGemstonePtr(new CGemstone(wItemID));

}

CEquipTrumpPtr CItemMgr::CreateEquipTrump(UINT16 wItemID)
{
    CEquipTrumpPtr pEquipTrump = CreateEmptyEquipTrump(wItemID);
    if(pEquipTrump == NULL)
        return NULL;
    if(!AssignItemProp(*pEquipTrump, 0))
        return NULL;
    pEquipTrump->_qwInstID = GET_GUID(GUID_EQUIP);
    pEquipTrump->InitAttr();
    LOG_CRI<<"CreateEquipTrump qwInstID:"<<pEquipTrump->_qwInstID;
    return pEquipTrump;

}

CEquipTrumpPtr CItemMgr::CreateEmptyEquipTrump(UINT16 wItemID)
{
    auto itItem = _mapID2ItemInfo.find(wItemID);
    if(itItem == _mapID2ItemInfo.end())
        return NULL;
    return CEquipTrumpPtr(new CEquipTrump(wItemID));
}

CCittaPtr CItemMgr::CreateEmptyCitta(UINT16 wItemID)
{
    auto itItem = _mapID2ItemInfo.find(wItemID);
    if(itItem == _mapID2ItemInfo.end())
        return NULL;
    return CCittaPtr(new CCitta(wItemID));
}

bool CItemMgr::AssignItemProp(CItem& rItem, UINT8 byQuality /*= 0*/)
{
#if 0
    const SItemCFG& rItemCfg = rItem.GetItemConfig();
    if(byQuality != 0 && byQuality <= MAX_ITEM_QUALITY)
    {
        rItem._byQuality = byQuality;
    }
    else if(rItemCfg._Quality != 0)
    {
        if(rItemCfg._Quality > MAX_ITEM_QUALITY)
            rItem._byQuality = MAX_ITEM_QUALITY;
        else
            rItem._byQuality = rItemCfg._Quality;
    }
    else
    {
        rItem._byQuality = CRandom::RandInt(1, MAX_ITEM_QUALITY);
    }
#endif
    bool bBind = (rItem.GetItemConfig()._Binding == eBindGet);
    if (bBind)
        rItem.SetBind(true);

    rItem.InitItemAttr();
    rItem.SetVersion(GetVersion());
    return true;
}

bool CItemMgr::AssignFashionProp(CFashion& rEquip, UINT8 byQuality)
{
    SItemAttrCFGEx* pItemAttrCfg = CItemMgr::GetItemAttrConfig(rEquip.GetItemConfig()._AttrIdx_1);
    if (!pItemAttrCfg)
        return false;
    // TODO:
    return true;
}

bool CItemMgr::AssignCittaProp(CCitta& rCitta, UINT32 dwSignetID /* = 0 */)
{
    CCittaMgr::Instance().SetCittaAttr(rCitta);
    CCittaMgr::Instance().SetCittaSignet(rCitta, dwSignetID);
    CCittaMgr::Instance().SetCittaSkill(rCitta);

    return true;
}

bool CItemMgr::AssignTrumpProp(CTrump& rTrump)
{
    return true;
}

CStackItemPtr CItemMgr::CreateEmptyStackItem(UINT16 wItemID)
{
    auto it = _mapID2ItemInfo.find(wItemID);
    if(it == _mapID2ItemInfo.end())
        return NULL;
    SItemCFG& rItemCfg = it->second.oItemCfg;
    if(CItem::IsStackItem(rItemCfg))
        return CStackItemPtr(new CStackItem(wItemID, CItem::GetMaxNum(rItemCfg)));
    return NULL;
}

CFashionPtr CItemMgr::CreateEmptyFashion(UINT16 wItemID)
{
    auto itItem = _mapID2ItemInfo.find(wItemID);
    if(itItem == _mapID2ItemInfo.end())
        return NULL;
    return CFashionPtr(new CFashion(wItemID));
}

bool CItemMgr::TransferStoreItem(CStore& rFromStore, CStore& rToStore, CItem& rFromItem,
        INT16 wFromIndex, CItem& rToItem, INT16 wIndex)
{
    if(rFromStore.DelItem(rFromItem, true, false, NLogDataDefine::ItemTo_UserDeptORPack))
    {
        rFromStore.AddItem(rToItem, wFromIndex, true, false, true, NLogDataDefine::ItemFrom_UserDeptORPack);

        if(rToStore.DelItem(rToItem, true, false, NLogDataDefine::ItemTo_UserDeptORPack))
        {
            rToStore.AddItem(rFromItem, wIndex, true, false, true, NLogDataDefine::ItemFrom_UserDeptORPack);
            return true;
        }
    }

    return false;
}

bool CItemMgr::MergeStackItem(CStore& rFromStore, CStore& rToStore, CItem& rFromItem, CItem& rToItem)
{
    if(rFromItem.IsStackItem() && rToItem.IsStackItem())
    {
        CStackItemPtr pFromStackItem = ToPtr<CStackItem>(rFromItem);
        CStackItemPtr pToStackItem = ToPtr<CStackItem>(rToItem);
        if(pFromStackItem != NULL && pToStackItem != NULL)
        {
            if(pFromStackItem->CanMerge(*pToStackItem))
            {
                UINT16 wTotalCount = pFromStackItem->GetCount() + pToStackItem->GetCount();
                if(wTotalCount > pToStackItem->GetMaxNum())
                {
                    pToStackItem->SetCount(pToStackItem->GetMaxNum());
                    rToStore.Update2DB(pToStackItem->GetIndex(), *pToStackItem, eOpUpdate, NLogDataDefine::ItemFrom_UserDeptORPack); 

                    UINT16 wRemCount = wTotalCount - pToStackItem->GetMaxNum();
                    if(pFromStackItem->SetCount(wRemCount))
                    {
                        pFromStackItem->NotifyCount(rFromStore);
                        rFromStore.Update2DB(pFromStackItem->GetIndex(), *pFromStackItem, eOpUpdate, NLogDataDefine::ItemFrom_UserDeptORPack);
                    }
                }
                else
                {
                    pToStackItem->SetCount(wTotalCount);
                    rToStore.Update2DB(pToStackItem->GetIndex(), *pToStackItem, eOpUpdate, NLogDataDefine::ItemFrom_UserDeptORPack); 
                    rFromStore.DelItem(*pFromStackItem, true, true, NLogDataDefine::ItemTo_UserDeptORPack);
                }
                pToStackItem->NotifyCount(rToStore);
                return true;
            }
        }
    }

    return false;
}

SItemInfo* CItemMgr::GetItemConfig(UINT16 wItemID)
{
    return GetValFromMap(_mapID2ItemInfo, wItemID);
}

SItemTimeCFG* CItemMgr::GetItemTimeConfig(UINT16 wTimeID)
{
    return &GetValFromMap(_mapID2TimeInfo, wTimeID)->oTimeCfg;
}

SItemAttrCFGEx* CItemMgr::GetItemAttrConfig(UINT16 wAttrID)
{
    return GetValFromMap(_mapID2ItemAttrInfo, wAttrID);
}

SBagCostCFG* CItemMgr::GetBagCost(UINT16 wIdx)
{
    return GetValFromMap(_mapID2BagCostCfg, wIdx);
}

SDepotCostCFG* CItemMgr::GetDepotCost(UINT16 wIdx)
{
    return GetValFromMap(_mapID2DepotCostCfg, wIdx);
}

SIntensifyCFG* CItemMgr::GetIntensifyConfig(UINT8 byJob, UINT8 byType, UINT8 byLevel)
{
    UINT32 dwIdx = MAKE_JOBLEVELEQUIPKEY(byJob, byType, byLevel);
    return GetValFromMap(_mapJobLevel2IntensifyCfg, dwIdx);
}

// XXX: 配置从1等级开始
SFashionCFG* CItemMgr::GetFashionConfig(UINT8 byLevel)
{
    if (!byLevel)
        return NULL;
    if (byLevel > _vecLevel2FashionExp.size())
        return &_vecLevel2FashionExp[_vecLevel2FashionExp.size()-1];
    return &_vecLevel2FashionExp[byLevel-1];
}

SFashionAttrCFG* CItemMgr::GetFashionAttrConfig(UINT16 wItemID, UINT8 byLevel)
{
    auto iter = _mapIDLevel2FashionAttr.find(wItemID);
    if (iter == _mapIDLevel2FashionAttr.end())
        return NULL;
    if (byLevel > iter->second.size())
        return &iter->second[iter->second.size()-1];
    for (size_t i = 0; i < iter->second.size(); ++ i)
    {
        if (iter->second[i]._material == byLevel)
            return &iter->second[i];
    }
    return NULL;
}

const std::vector<SMallCFG>* CItemMgr::GetMallCfg(UINT8 byType)
{
    auto i = _mapMallType2MallCfg.find(byType);
    if (i == _mapMallType2MallCfg.end())
        return NULL;
    return &i->second;
}
const SMallCFG* CItemMgr::GetMallCFG(UINT8 byType,UINT32 dwInstID)
{
    const std::vector<SMallCFG>* pCfg=GetMallCfg(byType);
    if(NULL == pCfg)
    {
        return NULL;
    }

    const SMallCFG* pMallCfg = NULL;
    for (size_t i = 0; i < pCfg->size(); ++i)
    {
        if ((*pCfg)[i]._Id == dwInstID)
        {
            pMallCfg = &(*pCfg)[i];
            break;
        }
    }

    return pMallCfg;
}

float CItemMgr::GetGoldPrice(UINT16 wItemID)
{
    for (auto iter = _mapMallType2MallCfg.begin(); iter != _mapMallType2MallCfg.end(); ++ iter)
    {
        for (size_t i = 0; i < iter->second.size(); ++i)
        {
            if ((iter->second)[i]._ItemId == wItemID)
            {
                if ((iter->second)[i]._MoneyType == EMONEY_GOLD && (iter->second)[i]._ItemNum)
                    return float((iter->second)[i]._Price) / (iter->second)[i]._ItemNum;
                return 0.0f;
            }
        }
    }
    return 0.0f;
}

SChongZhiCFGEx* CItemMgr::GetChongZhiCfg(UINT16 wGoldID)
{
    if (!wGoldID)
        return NULL;
    auto it = _mapID2ChongZhiCfg.begin();
    while (it != _mapID2ChongZhiCfg.end())
    {
        if ((it->second)._ItemID == wGoldID)
            return &it->second;
        ++ it;
    }
    return NULL;
}

bool CItemMgr::GetUpdateMaterial(UINT16 wItemId,map<UINT16,UINT32>  &mapMaterial)
{
    if(_mapUpgrade.find(wItemId) == _mapUpgrade.end())
    {
        return false;
    }
    mapMaterial = _mapUpgrade[wItemId];
    return true;

}

TSetUINT16& CItemMgr::GetConflictID(UINT16 wItemID)
{
    auto it = _mapID2ItemInfo.find(wItemID);
    if (it == _mapID2ItemInfo.end())
        return s_setNoneID;
    return it->second.setEquipConflict;
}

TSetUINT16& CItemMgr::GetTeamConflictID(UINT16 wItemID)
{
    auto it = _mapID2ItemInfo.find(wItemID);
    if (it == _mapID2ItemInfo.end())
        return s_setNoneID;
    return it->second.setEquipConflictTeam;
}

