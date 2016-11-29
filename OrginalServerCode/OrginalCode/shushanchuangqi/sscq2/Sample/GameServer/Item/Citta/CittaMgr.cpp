#include "CittaMgr.h"
#include "GameConfig.h"
#include "Tokenizer.h"
#include "ItemMgr.h"
#include "Random.h"

bool CCittaMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/Citta.xml";

    LOG_INF << "Loading " << strPath << " ...";
    if(!_cLoader.LoadData(strPath))
    {
        LOG_CRI << "Loading " << strPath << " failed.";
        return false;
    }
    LOG_INF << "Loading " << strPath << " succeed.";

    strPath = Config._strConfigDir + "Conf/Table/CittaMerge.xml";

    LOG_INF << "Loading " << strPath << " ...";
    if(!_cMergeLoader.LoadData(strPath))
    {
        LOG_CRI << "Loading " << strPath << " failed.";
        return false;
    }
    LOG_INF << "Loading " << strPath << " succeed.";

    strPath = Config._strConfigDir + "Conf/Table/CittaSignet.xml";

    LOG_INF << "Loading " << strPath << " ...";
    if(!_cSignetLoader.LoadData(strPath))
    {
        LOG_CRI << "Loading " << strPath << " failed.";
        return false;
    }
    LOG_INF << "Loading " << strPath << " succeed.";

    strPath = Config._strConfigDir + "Conf/Table/CittaSignetSuit.xml";

    LOG_INF << "Loading " << strPath << " ...";
    if(!_cSignetSuitLoader.LoadData(strPath))
    {
        LOG_CRI << "Loading " << strPath << " failed.";
        return false;
    }
    LOG_INF << "Loading " << strPath << " succeed.";

    LOG_INF << "Init ProbData ...";
    if (!InitProbData())
    {
        LOG_INF << "Init ProbData failed.";
        return false;
    }
    LOG_INF << "Init ProbData succees.";

    LOG_INF << "Init SuitData ...";
    if (!InitSuitData())
    {
        LOG_INF << "Init SuitData failed.";
        return false;
    }
    LOG_INF << "Init SuitData succees.";
    return true;
}

bool CCittaMgr::LoadConfig(const string &strFile)
{
    string strPath;
    if("Citta.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/Citta.xml";

        LOG_INF << "Loading " << strPath << " ...";
        if(!_cLoader.LoadData(strPath))
        {
            LOG_CRI << "Loading " << strPath << " failed.";
            return false;
        }
        LOG_INF << "Loading " << strPath << " succeed.";

        LOG_INF << "Start init SkillProbData.";
        for (auto it = _cLoader._vecData.begin(); it != _cLoader._vecData.end(); ++it)
        {
            const SCittaCFG* pCittaCFG = *it;
            if (!pCittaCFG)
                return false;
            if (!AnalysisString2ProbData(pCittaCFG->_Signet, _mapSignetID[pCittaCFG->_ID]))
                return false;
            if (!AnalysisString2ProbData(pCittaCFG->_Skill, _mapCittaSkillID[pCittaCFG->_ID]))
                return false;
                
        }
        LOG_INF << "Init SkillProbData succeed.";

    }else if("CittaMerge.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/CittaMerge.xml";

        LOG_INF << "Loading " << strPath << " ...";
        if(!_cMergeLoader.LoadData(strPath))
        {
            LOG_CRI << "Loading " << strPath << " failed.";
            return false;
        }
        LOG_INF << "Loading " << strPath << " succeed.";

        LOG_INF << "Start init MergeProbData.";
        for (auto it = _cMergeLoader._vecData.begin(); it != _cMergeLoader._vecData.end(); ++it)
        {
            const  SCittaMergeCFG* pCittaMergeCFG = *it;
            if (!pCittaMergeCFG)
                return false;
            if (!AnalysisString2ProbData(pCittaMergeCFG->_CittaID, _mapMergeCittaID[pCittaMergeCFG->_FormulaID]))
                return false;
            if (!AnalysisString2VectorUINT32(pCittaMergeCFG->_SignetID, _mapMergeSignetID[pCittaMergeCFG->_FormulaID]))
                return false;
        }
        LOG_INF << "Init MergeProbData succeed.";

    }else if("CittaSignet.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/CittaSignet.xml";

        LOG_INF << "Loading " << strPath << " ...";
        if(!_cSignetLoader.LoadData(strPath))
        {
            LOG_CRI << "Loading " << strPath << " failed.";
            return false;
        }
        LOG_INF << "Loading " << strPath << " succeed.";
    }else if("CittaSignetSuit.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/CittaSignetSuit.xml";

        LOG_INF << "Loading " << strPath << " ...";
        if(!_cSignetSuitLoader.LoadData(strPath))
        {
            LOG_CRI << "Loading " << strPath << " failed.";
            return false;
        }
        LOG_INF << "Loading " << strPath << " succeed.";

        LOG_INF << "Init SuitData ...";
        if (!InitSuitData())
        {
            LOG_INF << "Init SuitData failed.";
            return false;
        }
        LOG_INF << "Init SuitData succees.";
    }
   return true;
}

// 初始化概率相关参数
bool CCittaMgr::InitProbData()
{
    LOG_INF << "Start init MergeProbData.";
    for (auto it = _cMergeLoader._vecData.begin(); it != _cMergeLoader._vecData.end(); ++it)
    {
        const  SCittaMergeCFG* pCittaMergeCFG = *it;
        if (!pCittaMergeCFG)
            return false;
        if (!AnalysisString2ProbData(pCittaMergeCFG->_CittaID, _mapMergeCittaID[pCittaMergeCFG->_FormulaID]))
            return false;
        if (!AnalysisString2VectorUINT32(pCittaMergeCFG->_SignetID, _mapMergeSignetID[pCittaMergeCFG->_FormulaID]))
            return false;
    }
    LOG_INF << "Init MergeProbData succeed.";

    LOG_INF << "Start init SkillProbData.";
    for (auto it = _cLoader._vecData.begin(); it != _cLoader._vecData.end(); ++it)
    {
        const SCittaCFG* pCittaCFG = *it;
        if (!pCittaCFG)
            return false;
        if (!AnalysisString2ProbData(pCittaCFG->_Signet, _mapSignetID[pCittaCFG->_ID]))
            return false;
        if (!AnalysisString2ProbData(pCittaCFG->_Skill, _mapCittaSkillID[pCittaCFG->_ID]))
            return false;
            
    }
    LOG_INF << "Init SkillProbData succeed.";
    return true;
}

bool CCittaMgr::InitSuitData()
{
    for (auto it = _cSignetSuitLoader._vecData.begin(); it != _cSignetSuitLoader._vecData.end(); ++it)
    {
        const SCittaSignetSuitCFG* pCittaSignegSuitCFG = *it;
        if (!pCittaSignegSuitCFG)
            continue;
        TSetUINT32 setData;
        AnalysisString2SetUINT32(pCittaSignegSuitCFG->_SignetID, setData);
        for (auto it2 = setData.begin(); it2 != setData.end(); ++it2)
        {
            _mapSignetIndex[*it2] = pCittaSignegSuitCFG->_ID;
        }
        _mapSignetSuitID[pCittaSignegSuitCFG->_ID] = setData;
        if (pCittaSignegSuitCFG->_Number1 && pCittaSignegSuitCFG->_AttrID1)
        {
            SSuitData sSuitData;
            sSuitData._byCount = pCittaSignegSuitCFG->_Number1;
            sSuitData._dwAttrID = pCittaSignegSuitCFG->_AttrID1;
            _mapSignetSuitAttr[pCittaSignegSuitCFG->_ID].push_back(sSuitData);
        }
        if (pCittaSignegSuitCFG->_Number2 && pCittaSignegSuitCFG->_AttrID2)
        {
            SSuitData sSuitData;
            sSuitData._byCount = pCittaSignegSuitCFG->_Number2;
            sSuitData._dwAttrID = pCittaSignegSuitCFG->_AttrID2;
            _mapSignetSuitAttr[pCittaSignegSuitCFG->_ID].push_back(sSuitData);
        }
        if (pCittaSignegSuitCFG->_Number3 && pCittaSignegSuitCFG->_AttrID3)
        {
            SSuitData sSuitData;
            sSuitData._byCount = pCittaSignegSuitCFG->_Number3;
            sSuitData._dwAttrID = pCittaSignegSuitCFG->_AttrID3;
            _mapSignetSuitAttr[pCittaSignegSuitCFG->_ID].push_back(sSuitData);
        }
        if (pCittaSignegSuitCFG->_Number4 && pCittaSignegSuitCFG->_AttrID4)
        {
            SSuitData sSuitData;
            sSuitData._byCount = pCittaSignegSuitCFG->_Number4;
            sSuitData._dwAttrID = pCittaSignegSuitCFG->_AttrID4;
            _mapSignetSuitAttr[pCittaSignegSuitCFG->_ID].push_back(sSuitData);
        }

    }
    return true;
}

ECittaResult CCittaMgr::GetMaterial(UINT32 dwFormulaID, map<UINT16, UINT32>& mapMaterial)
{
    ECittaResult eResult = eCittaFailed;
    if (!dwFormulaID)
        return eResult;
    for (auto it = _cMergeLoader._vecData.begin(); it != _cMergeLoader._vecData.end(); ++it)
    {
        if (*it && (*it)->_FormulaID == dwFormulaID)
        {
            if ((*it)->_Material1ID && (*it)->_Material1Count)
                mapMaterial.insert(make_pair((*it)->_Material1ID, (*it)->_Material1Count));
            if ((*it)->_Material2ID && (*it)->_Material2Count)
                mapMaterial.insert(make_pair((*it)->_Material2ID, (*it)->_Material2Count));
            if ((*it)->_Material3ID && (*it)->_Material3Count)
                mapMaterial.insert(make_pair((*it)->_Material3ID, (*it)->_Material3Count));
            if ((*it)->_Material4ID && (*it)->_Material4Count)
                mapMaterial.insert(make_pair((*it)->_Material4ID, (*it)->_Material4Count));
            eResult = eCittaSuccess;
            break;
        }
    }
    if (eResult != eCittaSuccess)
        LOG_WRN << "Invalid citta FormulaID " << dwFormulaID << ".";
    return eResult;
}

ECittaResult CCittaMgr::GetBreakMaterial(UINT16 wItemID, UINT16& wMaterialID, UINT16& wCount)
{
    for (auto it = _cLoader._vecData.begin(); it != _cLoader._vecData.end(); ++it)
    {
        if (*it && (*it)->_ID == wItemID)
        {
            wMaterialID = (*it)->_ResolveMaterial;
            wCount = CRandom::RandInt((*it)->_ResolveMin, (*it)->_ResolveMax);
            return eCittaSuccess;
        }
    }
    return eCittaFailed;
}

UINT32       CCittaMgr::GetMergeSilver(UINT32 dwFormulaID) const
{
    UINT32 dwCost = 0;
    if (!dwFormulaID)
        return dwCost;
    for (auto it = _cMergeLoader._vecData.begin(); it != _cMergeLoader._vecData.end(); ++it)
    {
        if (*it && (*it)->_FormulaID == dwFormulaID)
        {
            dwCost = (*it)->_SilverCost;
            break;
        }
    }
    return dwCost;
}

UINT32      CCittaMgr::GetBreakSilver(UINT16 wItemID) const
{
    UINT32 dwCost = 0;
    if (!wItemID)
        return dwCost;
    for (auto it = _cLoader._vecData.begin(); it != _cLoader._vecData.end(); ++it)
    {
        if (*it && (*it)->_ID == wItemID)
        {
            dwCost = (*it)->_SilverCost;
            break;
        }
    }
    return dwCost;
}

UINT32      CCittaMgr::GetBreakLootID(UINT16 wItemID) const
{
    UINT32 dwCost = 0;
    if (!wItemID)
        return dwCost;
    for (auto it = _cLoader._vecData.begin(); it != _cLoader._vecData.end(); ++it)
    {
        if (*it && (*it)->_ID == wItemID)
        {
            dwCost = (*it)->_ResolveLoots;
            break;
        }
    }
    return dwCost;
}

// 根据材料获取心法ID 
ECittaResult CCittaMgr::GetCittaID(UINT32 dwFormulaID, UINT32 wCount, TVecUINT32& vecCittaID, TVecUINT32& vecSignet)
{
    if (!dwFormulaID)
        return eCittaFailed;
    if (_mapMergeCittaID.find(dwFormulaID) == _mapMergeCittaID.end())
        return eCittaFailed;

    while (wCount-- > 0)
    {
        UINT32 dwCittaID = 0;
        UINT32 dwSignet = 0;
        UINT32 dwRandVal = CRandom::RandInt(0, 9999);
        for (auto it = _mapMergeCittaID[dwFormulaID].begin(); it != _mapMergeCittaID[dwFormulaID].end(); ++it)
        {
            const SProbData& rProbData = *it;
            if (rProbData._dwProb >= dwRandVal)
            {
                dwCittaID = rProbData._dwID;
                UINT32 dwSignetCount = _mapMergeSignetID[dwFormulaID].size();
                if (dwSignetCount)
                {
                    UINT32 dwSignetIndex = CRandom::RandInt(0, dwSignetCount - 1);
                    dwSignet = _mapMergeSignetID[dwFormulaID][dwSignetIndex];
                }
                break;
            }
        }
        if (!dwCittaID)
            return eCittaFailed;
        else
        {
            vecCittaID.push_back(dwCittaID);
            vecSignet.push_back(dwSignet);
        }
    }

    return eCittaSuccess;
}

ECittaResult CCittaMgr::SetCittaAttr(CCitta& rCitta)
{
    SItemInfo* pItemInfo = rCitta.GetItemInfo();
    if (!pItemInfo)
        return eCittaFailed;
    SItemAttrCFGEx* pItemAttrCfg = pItemInfo->pItemAttr;
    if (rCitta.IsInited()) // 已经生成初始化过的心法
        return eCittaSuccess;
    TVecUINT8 vecAttrType;
    TVecUINT32 vecAttrValue;
    for (UINT8 byIndex = eCittaAttrNone + 1; byIndex < eCittaAttrMax; ++byIndex)
    {
        bool bNeedAdd = false;
        UINT32 dwVal = 0;
        switch (byIndex)
        {
            case eCittaAttrAttack   :
                dwVal = static_cast<UINT32>(pItemAttrCfg->_EFIGHTATTR_PHYATK);
                bNeedAdd = true;
                break;
            case eCittaAttrPhyDef   :
                dwVal = static_cast<UINT32>(pItemAttrCfg->_EFIGHTATTR_PHYDEF);
                bNeedAdd = true;
                break;
            case eCittaAttrMgcDef   :
                dwVal = static_cast<UINT32>(pItemAttrCfg->_EFIGHTATTR_MGCDEF);
                bNeedAdd = true;
                break;
            case eCittaAttrHP       :
                dwVal = static_cast<UINT32>(pItemAttrCfg->_EFIGHTATTR_MAXHP);
                bNeedAdd = true;
                break;
            case eCittaAttrHit      :
                dwVal = static_cast<UINT32>(pItemAttrCfg->_EFIGHTATTR_HIT);
                bNeedAdd = true;
                break;
            case eCittaAttrDodge    :
                dwVal = static_cast<UINT32>(pItemAttrCfg->_EFIGHTATTR_DODGE);
                bNeedAdd = true;
                break;
            case eCittaAttrCri      :
                dwVal = static_cast<UINT32>(pItemAttrCfg->_EFIGHTATTR_CRITICAL);
                bNeedAdd = true;
                break;
            case eCittaAttrAntiCri  :
                dwVal = static_cast<UINT32>(pItemAttrCfg->_EFIGHTATTR_ANTICRITCAL);
                bNeedAdd = true;
                break;
            case eCittaAttrPiece    :
                dwVal = static_cast<UINT32>(pItemAttrCfg->_EFIGHTATTR_PIERCE);
                bNeedAdd = true;
                break;
            case eCittaAttrCounter  :
                dwVal = static_cast<UINT32>(pItemAttrCfg->_EFIGHTATTR_COUNTER);
                bNeedAdd = true;
                break;
            case eCittaAttrResist   :
                dwVal = static_cast<UINT32>(pItemAttrCfg->_EFIGHTATTR_RESIST);
                bNeedAdd = true;
                break;
        }
        if (bNeedAdd && dwVal > 0)
        {
            vecAttrType.push_back(byIndex);
            vecAttrValue.push_back(dwVal);
        }
    }
    UINT8 byAttrNum = 0;
    UINT32 dwRangeMax = 0;
    UINT32 dwRangeMin = 0;
    for (auto it = _cLoader._vecData.begin(); it != _cLoader._vecData.end(); ++it)
    {
        if (*it && ((*it)->_ID == rCitta.GetItemID()))
        {
            byAttrNum = (*it)->_AttrCount;
            dwRangeMax = (*it)->_RangeMax;
            dwRangeMin = (*it)->_RangeMin;
            break;
        }
    }

    for (UINT8 byIndex = 0; byIndex < byAttrNum; ++byIndex)
    {
        ECittaResult eResult = AddOneCittaRandAttr(rCitta, vecAttrType, vecAttrValue, dwRangeMax, dwRangeMin);
        if (eResult != eCittaSuccess)
            return eResult;
    }
    return eCittaSuccess;
}

ECittaResult CCittaMgr::SetCittaSignet(CCitta& rCitta, UINT32 dwSignetID /* = 0 */)
{
    if (dwSignetID)
    {
        rCitta._dwSignetID = dwSignetID;
        return eCittaSuccess;
    }
    UINT32 dwRandVal = CRandom::RandInt(0, 9999);
    for (auto it = _mapSignetID[rCitta.GetItemID()].begin(); it != _mapSignetID[rCitta.GetItemID()].end(); ++it)
    {
        const SProbData& rProbData = *it;
        if (rProbData._dwProb >= dwRandVal)
        {
            rCitta._dwSignetID = rProbData._dwID;
            break;
        }
    }
    return eCittaSuccess;
}

ECittaResult CCittaMgr::SetCittaSkill(CCitta& rCitta)
{
    UINT32 dwRandVal = CRandom::RandInt(0, 9999);
    for (auto it = _mapCittaSkillID[rCitta.GetItemID()].begin(); it != _mapCittaSkillID[rCitta.GetItemID()].end(); ++it)
    {
        const SProbData& rProbData = *it;
        if (rProbData._dwProb >= dwRandVal)
        {
            rCitta._dwSkillID = rProbData._dwID;
            break;
        }
    }
    return eCittaSuccess;
}

ECittaResult CCittaMgr::AddOneCittaRandAttr(CCitta& rCitta, TVecUINT8& vecAttrType, TVecUINT32& vecAttrValue,
        UINT32 dwRangeMax, UINT32 dwRangeMin)
{
    UINT32 dwRandVal = CRandom::RandInt(dwRangeMin, dwRangeMax);
    if (vecAttrType.empty())
        return eCittaFailed;
    UINT8 byRandIndex = CRandom::RandInt(0, vecAttrType.size() - 1);
    switch (vecAttrType[byRandIndex])
    {
        case eCittaAttrAttack   :
            rCitta._mapAttr[EFIGHTATTR_PHYATK] = vecAttrValue[byRandIndex] * dwRandVal / 10000;
            //rCitta._mapAttr[EFIGHTATTR_MGCATK] = vecAttrValue[byRandIndex];
            break;
        case eCittaAttrPhyDef   :
            rCitta._mapAttr[EFIGHTATTR_PHYDEF] = vecAttrValue[byRandIndex] * dwRandVal / 10000;
            break;
        case eCittaAttrMgcDef   :
            rCitta._mapAttr[EFIGHTATTR_MGCDEF] = vecAttrValue[byRandIndex] * dwRandVal / 10000;
            break;
        case eCittaAttrHP       :
            rCitta._mapAttr[EFIGHTATTR_MAXHP] = vecAttrValue[byRandIndex] * dwRandVal / 10000;
            break;
        case eCittaAttrHit      :
            rCitta._mapAttr[EFIGHTATTR_HIT] = vecAttrValue[byRandIndex] * dwRandVal / 10000;
            break;
        case eCittaAttrDodge    :
            rCitta._mapAttr[EFIGHTATTR_DODGE] = vecAttrValue[byRandIndex] * dwRandVal / 10000;
            break;
        case eCittaAttrCri      :
            rCitta._mapAttr[EFIGHTATTR_CRITICAL] = vecAttrValue[byRandIndex] * dwRandVal / 10000;
            break;
        case eCittaAttrAntiCri  :
            rCitta._mapAttr[EFIGHTATTR_ANTICRITCAL] = vecAttrValue[byRandIndex] * dwRandVal / 10000;
            break;
        case eCittaAttrPiece    :
            rCitta._mapAttr[EFIGHTATTR_PIERCE] = vecAttrValue[byRandIndex] * dwRandVal / 10000;
            break;
        case eCittaAttrCounter  :
            rCitta._mapAttr[EFIGHTATTR_COUNTER] = vecAttrValue[byRandIndex] * dwRandVal / 10000;
            break;
        case eCittaAttrResist   :
            rCitta._mapAttr[EFIGHTATTR_RESIST] = vecAttrValue[byRandIndex] * dwRandVal / 10000;
            break;
    }
    vecAttrType.erase(vecAttrType.begin() + byRandIndex);
    vecAttrValue.erase(vecAttrValue.begin() + byRandIndex);
    return eCittaSuccess;
}

bool CCittaMgr::AddOneSuitAttr(UINT32 dwAttrID, TVecFloat& rvecAttr)
{
    SItemAttrCFGEx* pCFG = CItemMgr::GetItemAttrConfig(dwAttrID);
    if (!pCFG)
        return false;
    else
    {
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
    }
    return eCittaSuccess;
}

// 加载概率数据
bool CCittaMgr::AnalysisString2ProbData(const string& strValue, TVecProbData& vecProbData, const string& strSep /* = "|" */, const string& strSep2 /* = ";" */)
{
    vecProbData.clear();
    Tokenizer tk(strValue, strSep);
    UINT32 dwTotalProb = 0;
    for (size_t i = 0; i < tk.size(); ++i)
    {               
        Tokenizer tk2(tk[i], strSep2);
        if (tk2.size() < 2)
            return false;
        SProbData sProbData;
        sProbData._dwID = ::atoi(tk2[0].c_str());
        dwTotalProb += ::atoi(tk2[1].c_str());
        sProbData._dwProb = dwTotalProb;
        vecProbData.push_back(sProbData);
    }               
    return true;
}

// 加载并列数据
bool CCittaMgr::AnalysisString2VectorUINT32(const string& strValue, TVecUINT32& vecData, const string& strSep /* = ";" */)
{
    vecData.clear();
    Tokenizer tk(strValue, strSep);
    for (size_t i = 0; i < tk.size(); ++i)
        vecData.push_back(::atoi(tk[i].c_str()));
    return true;
}

// 加载并列数据
bool CCittaMgr::AnalysisString2SetUINT32(const string& strValue, TSetUINT32& setData, const string& strSep /* = "," */)
{
    setData.clear();
    Tokenizer tk(strValue, strSep);
    for (size_t i = 0; i < tk.size(); ++i)
        setData.insert(::atoi(tk[i].c_str()));
    return true;
}

// 套装数据
bool CCittaMgr::SignetToAttr(const TSetUINT32& setSignetID, TVecFloat& rvecAddAttr)
{
    map<UINT32, UINT32> mapSignetCount;
    for (auto it = setSignetID.begin(); it != setSignetID.end(); ++it)
    {
        if (_mapSignetIndex.find(*it) == _mapSignetIndex.end())
            continue;
        ++mapSignetCount[_mapSignetIndex[*it]];
    }
    for (auto it = mapSignetCount.begin(); it != mapSignetCount.end(); ++it)
    {
        if (_mapSignetSuitAttr.find(it->first) == _mapSignetSuitAttr.end())
            continue;
        for (auto it2 = _mapSignetSuitAttr[it->first].begin(); it2 != _mapSignetSuitAttr[it->first].end(); ++it2)
        {
            if ((*it2)._byCount <= it->second)
            {
                AddOneSuitAttr((*it2)._dwAttrID, rvecAddAttr);
            }
        }
    }
    return true;
}

ECittaNameType CCittaMgr::GetNameType(UINT16 wItemID, const TMapCittaAttr& rmapCittaAttr)
{
    SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
    if (!pItemInfo)
        return eNameNone;
    SItemAttrCFGEx* pItemAttrCfg = CItemMgr::GetItemAttrConfig(pItemInfo->oItemCfg._AttrIdx_1);
    if (!pItemAttrCfg) // 已经生成初始化过的心法
        return eNameNone;
    TVecUINT8 vecAttrType;
    TVecUINT32 vecAttrValue;
    ECittaNameType eNameType = eNameNone;
    float fMaxRate = 0.0f;
    for (auto it = rmapCittaAttr.begin(); it != rmapCittaAttr.end(); ++it)
    {
        float fTmpRate = 0.0f;
        switch (it->first)
        {
            case EFIGHTATTR_PHYATK   :
                fTmpRate = static_cast<float>(it->second) / pItemAttrCfg->_EFIGHTATTR_PHYATK;
                if (fTmpRate > fMaxRate)
                {
                    fMaxRate = fTmpRate;
                    eNameType = eNameAttack;
                }
                break;
            case EFIGHTATTR_PHYDEF   :
                fTmpRate = static_cast<float>(it->second) / pItemAttrCfg->_EFIGHTATTR_PHYDEF;
                if (fTmpRate > fMaxRate)
                {
                    fMaxRate = fTmpRate;
                    eNameType = eNameDefence;
                }
                break;
            case EFIGHTATTR_MGCDEF   :
                fTmpRate = static_cast<float>(it->second) / pItemAttrCfg->_EFIGHTATTR_MGCDEF;
                if (fTmpRate > fMaxRate)
                {
                    fMaxRate = fTmpRate;
                    eNameType = eNameMgcDefence;
                }
                break;
            case EFIGHTATTR_MAXHP       :
                fTmpRate = static_cast<float>(it->second) / pItemAttrCfg->_EFIGHTATTR_MAXHP;
                if (fTmpRate > fMaxRate)
                {
                    fMaxRate = fTmpRate;
                    eNameType = eNameHP;
                }
                break;
            case EFIGHTATTR_HIT      :
                fTmpRate = static_cast<float>(it->second) / pItemAttrCfg->_EFIGHTATTR_HIT;
                if (fTmpRate > fMaxRate)
                {
                    fMaxRate = fTmpRate;
                    eNameType = eNameHit;
                }
                break;
            case EFIGHTATTR_DODGE    :
                fTmpRate = static_cast<float>(it->second) / pItemAttrCfg->_EFIGHTATTR_DODGE;
                if (fTmpRate > fMaxRate)
                {
                    fMaxRate = fTmpRate;
                    eNameType = eNameDodge;
                }
                break;
            case EFIGHTATTR_CRITICAL      :
                fTmpRate = static_cast<float>(it->second) / pItemAttrCfg->_EFIGHTATTR_CRITICAL;
                if (fTmpRate > fMaxRate)
                {
                    fMaxRate = fTmpRate;
                    eNameType = eNameCritical;
                }
                break;
            case EFIGHTATTR_ANTICRITCAL  :
                fTmpRate = static_cast<float>(it->second) / pItemAttrCfg->_EFIGHTATTR_ANTICRITCAL;
                if (fTmpRate > fMaxRate)
                {
                    fMaxRate = fTmpRate;
                    eNameType = eNameAntiCri;
                }
                break;
            case EFIGHTATTR_PIERCE    :
                fTmpRate = static_cast<float>(it->second) / pItemAttrCfg->_EFIGHTATTR_PIERCE;
                if (fTmpRate > fMaxRate)
                {
                    fMaxRate = fTmpRate;
                    eNameType = eNamePiece;
                }
                break;
            case EFIGHTATTR_COUNTER  :
                fTmpRate = static_cast<float>(it->second) / pItemAttrCfg->_EFIGHTATTR_COUNTER;
                if (fTmpRate > fMaxRate)
                {
                    fMaxRate = fTmpRate;
                    eNameType = eNameCounter;
                }
                break;
            case EFIGHTATTR_RESIST   :
                fTmpRate = static_cast<float>(it->second) / pItemAttrCfg->_EFIGHTATTR_RESIST;
                if (fTmpRate > fMaxRate)
                {
                    fMaxRate = fTmpRate;
                    eNameType = eNameResist;
                }
                break;
            default:
                break;
        }
    }
    return eNameType;
}
