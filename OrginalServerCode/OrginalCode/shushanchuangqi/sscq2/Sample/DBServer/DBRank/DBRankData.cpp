// =====================================================================================
//
//       Filename:  DBRankData.cpp
//
//    Description:  排行榜数据
//
//        Version:  1.0
//        Created:  09/05/2014 02:03:47 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "DBRankData.h"

#include "RankProt.h"

using namespace NRankProt;

/////////////////////////////////////////////////////////////////////////////////
// CDBRankData
CDBRankData::CDBRankData(UINT64 qwInstID) : 
    _eUpdateDataStatus(DATAUPDATE_NONE), _qwInstID(qwInstID)
{
}

CDBRankData::~CDBRankData()
{
}

ERankUpdateStatus CDBRankData::GetUpdateStatus() const
{
    return _eUpdateDataStatus;
}

void CDBRankData::SetUpdateStatus(ERankUpdateStatus eStatus)
{
    _eUpdateDataStatus = eStatus;
}

UINT64 CDBRankData::GetInstID() const
{
    return _qwInstID;
}


/////////////////////////////////////////////////////////////////////////////////
// CDBRoleRankData
CDBRoleRankData::CDBRoleRankData(UINT64 qwInstID) : 
    CDBRankData(qwInstID)
{
    for (UINT8 byIndex = eRTRoleRankBegin; byIndex < eRTRoleRankEnd; ++byIndex)
    {
        ERankType eType = static_cast<ERankType>(byIndex);
        _mapDataManager[eType] = CTableManagerBaseForRoleRank::CreateManager(eType, _qwInstID);
    }
}

CDBRoleRankData::~CDBRoleRankData()
{
    for (auto iter = _mapDataManager.begin(); iter != _mapDataManager.end(); iter++)
        CTableManagerBaseForRoleRank::DestroyManager(iter->second);
    _mapDataManager.clear();
}

bool CDBRoleRankData::HasUpdateNum(ERankType eType)
{
    auto it = _mapDataManager.find(eType);
    if (it == _mapDataManager.end())
        return false;
    return it->second->GetUpdataNum()?true:false;
}

bool CDBRoleRankData::HasUpdateNum()
{
    for (auto iter = _mapDataManager.begin(); iter != _mapDataManager.end(); iter++)
    {
        if (iter->second->GetUpdataNum())
            return true;
    }
    return false;
}

UINT32 CDBRoleRankData::UpdateNum()
{
    UINT32 dwNum = 0;
    for (auto iter = _mapDataManager.begin(); iter != _mapDataManager.end(); iter++)
    {
        dwNum += iter->second->GetUpdataNum();
    }
    return dwNum;
}

UINT64 CDBRoleRankData::GetRoleID() const
{
    return GetInstID();
}

CTableManagerBaseForRoleRank* CDBRoleRankData::GetDataManagerByType(ERankType etype)
{
    auto iter = _mapDataManager.find(etype);
    if (iter != _mapDataManager.end())
        return iter->second;
    return NULL;
}

// CDBRoleRankData
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// CDBGuildRankData
CDBGuildRankData::CDBGuildRankData(UINT64 qwInstID) : 
    CDBRankData(qwInstID)
{
    for (UINT8 byIndex = eRTGuildRankBegin; byIndex < eRTGuildRankEnd; ++byIndex)
    {
        ERankType eType = static_cast<ERankType>(byIndex);
        _mapDataManager[eType] = CTableManagerBaseForGuildRank::CreateManager(eType, _qwInstID);
    }
}

CDBGuildRankData::~CDBGuildRankData()
{
}

bool CDBGuildRankData::HasUpdateNum(ERankType eType)
{
    auto it = _mapDataManager.find(eType);
    if (it == _mapDataManager.end())
        return false;
    return it->second->GetUpdataNum()?true:false;
}

bool CDBGuildRankData::HasUpdateNum()
{
    for (auto iter = _mapDataManager.begin(); iter != _mapDataManager.end(); iter++)
    {
        if (iter->second->GetUpdataNum())
            return true;
    }
    return false;
}

UINT32 CDBGuildRankData::UpdateNum()
{
    UINT32 dwNum = 0;
    for (auto iter = _mapDataManager.begin(); iter != _mapDataManager.end(); iter++)
    {
        dwNum += iter->second->GetUpdataNum();
    }
    return dwNum;
}

CTableManagerBaseForGuildRank* CDBGuildRankData::GetDataManagerByType(ERankType etype)
{
    auto iter = _mapDataManager.find(etype);
    if (iter != _mapDataManager.end())
        return iter->second;
    return NULL;
}
// CDBGuildRankData
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// CDBRoleAdoreData
CDBRoleAdoreData::CDBRoleAdoreData(UINT64 qwRoleID):
    _eUpdateDataStatus(DATAUPDATE_NONE), _qwRoleID(qwRoleID)
{
    _pDataManager = new CDBRoleAdoreTableManager(qwRoleID);
}

CDBRoleAdoreData::~CDBRoleAdoreData()
{
    if (_pDataManager)
    {
        delete _pDataManager;
        _pDataManager = NULL;
    }
}

ERankUpdateStatus CDBRoleAdoreData::GetUpdateStatus() const
{
    return _eUpdateDataStatus;
}

void CDBRoleAdoreData::SetUpdateStatus(ERankUpdateStatus eStatus)
{
    _eUpdateDataStatus = eStatus;
}

bool CDBRoleAdoreData::HasUpdateNum()
{
    if (_pDataManager && _pDataManager->GetUpdataNum())
        return true;
    return false;
}

UINT32 CDBRoleAdoreData::UpdateNum()
{
    UINT32 dwNum = 0;
    if (_pDataManager)
        dwNum += _pDataManager->GetUpdataNum();
    return dwNum;
}

UINT64 CDBRoleAdoreData::GetRoleID() const
{
    return _qwRoleID;
}
// CDBRoleAdoreData
/////////////////////////////////////////////////////////////////////////////////
