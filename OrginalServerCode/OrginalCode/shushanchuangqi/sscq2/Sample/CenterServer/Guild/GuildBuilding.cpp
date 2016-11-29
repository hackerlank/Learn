#include "GuildBuilding.h"

#include "GuildMgr.h"
#include "Center2DBGuildC.h"
#include "GuildLog.h"
#include "User.h"

static const UINT8 BUILDINGS_COUNT = 4;

CGuildBuilding::CGuildBuilding() : 
    _eType(eBuildingNone)
{
    _eLevelType = eLevelUpByLevelResetExp;
}

CGuildBuilding::~CGuildBuilding()
{
}

bool CGuildBuilding::InitFromDB(EBuildingType eType, UINT16 wLevel)
{
    _eType = eType;
    CLevelObject::InitFromDB(GetTableLevelExp(wLevel), wLevel, 0);
    return true;
}

UINT32 CGuildBuilding::GetTableLevelExp(UINT16 wLevel) const
{
    TVecPGuildBuildingCFG vecPGuildBuildingCFG;
    if (!CGuildMgr::Instance().GetBuildingConfig(static_cast<UINT8>(_eType), vecPGuildBuildingCFG))
        return 0;
    if (vecPGuildBuildingCFG.size() < static_cast<size_t>(wLevel + 1))
        return 0;
    return vecPGuildBuildingCFG[wLevel]->_Cost;
}

EBuildingType CGuildBuilding::GetType() const
{
    return _eType;
}

void CGuildBuilding::SetType(EBuildingType eType)
{
    _eType = eType;
}

UINT32 CGuildBuilding::GetAttrValue() const
{
    TVecPGuildBuildingCFG vecPGuildBuildingCFG;
    if (!CGuildMgr::Instance().GetBuildingConfig(static_cast<UINT8>(_eType), vecPGuildBuildingCFG))
        return 0;
    if (vecPGuildBuildingCFG.size() < static_cast<size_t>(GetLevel() + 1))
        return 0;
    return vecPGuildBuildingCFG[GetLevel()]->_Val;
}

// 返回等级
UINT16 CGuildBuilding::GetTableLevel(UINT32 exp) const
{
    TVecPGuildBuildingCFG vecPGuildBuildingCFG;
    if (!CGuildMgr::Instance().GetBuildingConfig(static_cast<UINT8>(_eType), vecPGuildBuildingCFG))
        return 0;
    if (vecPGuildBuildingCFG.size() < 2)
        return 0;
    UINT16 wLevel = 1;
    for (auto it = vecPGuildBuildingCFG.begin() + 1; it != vecPGuildBuildingCFG.end(); ++it)
    {
        if (!((*it)->_Cost))
            break;
        if (((*it)->_Cost) <= exp)
            ++wLevel;
    }
    return wLevel;
}

//  返回最高等级
UINT16 CGuildBuilding::GetMaxLevel() const
{
    TVecPGuildBuildingCFG vecPGuildBuildingCFG;
    if (!CGuildMgr::Instance().GetBuildingConfig(static_cast<UINT8>(_eType), vecPGuildBuildingCFG))
        return 0;
    if (vecPGuildBuildingCFG.empty())
        return 0;
    return vecPGuildBuildingCFG.size() - 1;
}

void CGuildBuilding::GetAllInfo(SGuildBuildingInfo& rInfo) const
{
    rInfo.eBuildingType = _eType;
    rInfo.wLevel        = GetLevel();
}

////////////////////////////////////////////////////////////////////////////////////////////////

CGuildBuildingOwner::CGuildBuildingOwner(CGuildPtr pGuild) : 
    _pGuild(pGuild)
{
    for (UINT8 byIndex = static_cast<UINT8>(eBuildingNone) + 1; byIndex < static_cast<UINT8>(eBuildingMax); ++byIndex)
    {
        CGuildBuildingPtr pBuilding (new CGuildBuilding);
        pBuilding->SetType(static_cast<EBuildingType>(byIndex));
        _mapGuildBuildingPtr.insert(make_pair(static_cast<EBuildingType>(byIndex), pBuilding));
    }
}

CGuildBuildingOwner::~CGuildBuildingOwner()
{
}

// 从数据库加载
bool CGuildBuildingOwner::InitFromDB(const TVecGuildBuildingInfo& rvecBuildings)
{
    _mapGuildBuildingPtr.clear();
    for (auto it = rvecBuildings.begin(); it != rvecBuildings.end(); ++it)
    {
        CGuildBuildingPtr pBuilding(new CGuildBuilding);
        pBuilding->InitFromDB((*it)->eBuildingType, (*it)->wLevel);
        _mapGuildBuildingPtr.insert(make_pair((*it)->eBuildingType, pBuilding));
    }
    return true;
}

UINT64 CGuildBuildingOwner::GetGuildID() const
{
    if (!_pGuild)
        return 0;
    return _pGuild->GetID();
}

UINT16 CGuildBuildingOwner::GetLevel(EBuildingType eType) const
{
    auto it = _mapGuildBuildingPtr.find(eType);
    if (it == _mapGuildBuildingPtr.end())
        return 0;
    return (it->second)->GetLevel();
}


UINT16 CGuildBuildingOwner::GetMaxLevel(EBuildingType eType) const
{
    auto it = _mapGuildBuildingPtr.find(eType);
    if (it == _mapGuildBuildingPtr.end())
        return 0;
    return it->second->GetMaxLevel();
}

UINT32 CGuildBuildingOwner::GetAttrValue(EBuildingType eType) const
{
    auto it = _mapGuildBuildingPtr.find(eType);
    if (it == _mapGuildBuildingPtr.end())
        return 0;
    return (it->second)->GetAttrValue();
}

// 帮派建筑升级
bool CGuildBuildingOwner::UpgradeBuilding(EBuildingType eType, EBuildingResult& eResult)
{
    if (!_pGuild)
    {
        eResult = eGBuildingResultFailed;
        return false;
    }
    
    auto it = _mapGuildBuildingPtr.find(eType);
    if (it == _mapGuildBuildingPtr.end())
    {
        eResult = eGBuildingResultFailed;
        return false;
    }
    CGuildBuildingPtr pBuilding = it->second;

    if (pBuilding->GetLevel() >= GetMaxLevel(eType)) // 已经最高等级
    {
        eResult = eGBuildingResultLevelMax;
        return false;
    }

    if (pBuilding->GetLevel() >= _pGuild->GetBuildingMaxLevel()) // 帮派等级过低
    {
        eResult = eGBuildingResultGuildLevelTooLow;
        return false;
    }

    UINT32 dwMoney = _pGuild->GetMoney();
    ELevelObjectErr eErr = pBuilding->TryLevelUp(dwMoney);
    if (eErr == eErrNoEnoughExp)
    {
        eResult = eGBuildingResultLackofSilver;
        return false;
    }
    else if (eErr != eErrSuccess)
    {
        eResult = eGBuildingResultFailed;
        return false;
    }
    _pGuild->SetMoney(dwMoney);
    _pGuild->SetDirty(eGDTBuilding);
    _pGuild->SaveData();
    _pGuild->NotifyBuildingInfo();
    eResult = eGBuildingResultSuccess;

    //LogServer日志
    SLogOp sLog;
    if(eType == eBuildingOracle)
        sLog.eType = eOpType_Tower;
    else if(eType == eBuildingStore)
        sLog.eType = eOpType_Store;
    else if(eType == eBuildingSword)
        sLog.eType = eOpType_Hourse;
    sLog.qwGuildID = _pGuild->GetID();
    sLog.byParam = 0;
    CGuildMgr::Instance().WriteGuildLog(sLog);

    CGuildBuildingLogPtr pLog (new CGuildBuildingLog);
    if (pLog->FormatParam(eType, pBuilding->GetLevel()))
    {
        _pGuild->AddLog(pLog);
        CGuildLog::Update2DB(pLog, eOpAdd, _pGuild->GetID());
    }
    CGuildListInfoPtr pGuildListInfo = CGuildMgr::Instance().GetListInfo(_pGuild->GetID());
    if (pGuildListInfo)
        pGuildListInfo->SetMaxMemberCount(_pGuild->GetMaxMemberCount());
    return true;
}

void CGuildBuildingOwner::GetAllInfo(TVecSGuildInfoBase& rvecInfo) const
{
    for (auto it = _mapGuildBuildingPtr.begin(); it != _mapGuildBuildingPtr.end(); ++it)
    {
        if (it->second)
        {
            SGuildBuildingInfoPtr pBuildingInfo(new SGuildBuildingInfo);
            pBuildingInfo->qwGuildID = GetGuildID();
            it->second->GetAllInfo(*pBuildingInfo);
            rvecInfo.push_back(pBuildingInfo);
        }
    }
}

void CGuildBuildingOwner::GetAllInfo(TVecGuildBuildingInfo& rvecInfo) const
{
    for (auto it = _mapGuildBuildingPtr.begin(); it != _mapGuildBuildingPtr.end(); ++it)
    {
        if (it->second)
        {
            SGuildBuildingInfoPtr pBuildingInfo(new SGuildBuildingInfo);
            pBuildingInfo->qwGuildID = GetGuildID();
            it->second->GetAllInfo(*pBuildingInfo);
            rvecInfo.push_back(pBuildingInfo);
        }
    }
}

void CGuildBuildingOwner::Update2DB(CGuildBuildingOwnerPtr pBuildingOwner, EDataChange eChangeType, UINT64 qwOwnerID /* = 0 */)
{
    if (pBuildingOwner && !qwOwnerID)
        return;

    if (!qwOwnerID)
        qwOwnerID = pBuildingOwner->GetGuildID();

    TVecGuildBuildingInfo vecBuildingInfo;
    if (pBuildingOwner)
        pBuildingOwner->GetAllInfo(vecBuildingInfo);
    string strData;
    COutArchive iar(strData);
    iar << vecBuildingInfo;
    g_Center2DBGuildC.Send_GuildDataUpdate(qwOwnerID, eGDTBuilding, eChangeType, strData);
}
