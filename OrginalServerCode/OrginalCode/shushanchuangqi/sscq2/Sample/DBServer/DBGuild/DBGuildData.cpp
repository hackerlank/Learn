#include "DBGuildData.h"

#include "GuildProt.h"

using namespace NGuildProt;

CDBGuildData::CDBGuildData(UINT64 qwGuildID) :
    _qwGuildID(qwGuildID),
    _eGuildState(eGuildNone), 
    _dwNowUpdate(0),
    _eUpdateDataStatus(DATAUPDATE_NONE)
{
    for (UINT8 byIndex = 0; byIndex < eGDTMax; ++byIndex)
    {
        EGuildDataType eType = static_cast<EGuildDataType>(byIndex);
        _mapDataManager[eType] = CTableManagerBaseForGuild::CreateManager(eType, _qwGuildID);
    }
#ifdef _DEBUG
    LOG_CRI << "Create CDBGuildData(" << qwGuildID << ")";
#endif
}

CDBGuildData::~CDBGuildData()
{
    for (auto iter = _mapDataManager.begin();iter != _mapDataManager.end();iter++)
        CTableManagerBaseForGuild::DestroyManager(iter->second);
    _mapDataManager.clear();
}

EGuildUpdateStatus CDBGuildData::GetUpdateStatus() const
{
    return _eUpdateDataStatus;
}

void CDBGuildData::SetUpdateStatus(EGuildUpdateStatus eStatus)
{
    _eUpdateDataStatus = eStatus;
}

bool CDBGuildData::HasUpdateNum()
{
    for (auto iter = _mapDataManager.begin(); iter != _mapDataManager.end();iter++)
    {
        if (iter->second->GetUpdataNum())
            return true;
    }
    return false;
}

UINT32 CDBGuildData::UpdateNum()
{
    UINT32 dwNum = 0;
    for (auto iter = _mapDataManager.begin(); iter != _mapDataManager.end();iter++)
    {
        dwNum += iter->second->GetUpdataNum();
    }
    return dwNum;
}

CTableManagerBaseForGuild* CDBGuildData::GetDataManagerByType(EGuildDataType etype)
{
    auto iter = _mapDataManager.find(etype);
    if (iter != _mapDataManager.end())
        return iter->second;
    return NULL;
}

EGuildState CDBGuildData::GetGuildState()
{
    return _eGuildState;
}

void CDBGuildData::SetGuildState(EGuildState eGuildState)
{
    if (_eGuildState == eGuildState)
        return;

    LOG_INF << "CDBGuildData::SetGuildState:" << eGuildState;

    _eGuildState = eGuildState;
}

UINT64 CDBGuildData::GetGuildID() const
{
    return _qwGuildID;
}

UINT32 CDBGuildData::GetNowUpdate() const
{
    return _dwNowUpdate;
}

void    CDBGuildData::SetNowUpdate(UINT32 dwNowUpdate)
{
    _dwNowUpdate = dwNowUpdate;
}

void    CDBGuildData::AddNowUpdate(UINT32 dwNowUpdate /* = 1 */)
{
    _dwNowUpdate += dwNowUpdate;
}

CDBPubGuildData::CDBPubGuildData(UINT64 qwGuildID) : 
    _eGuildState(eGuildNone), 
    _dwNowUpdate(0),
    _eUpdateDataStatus(DATAUPDATE_NONE), 
    _qwGuildID(qwGuildID)
{
    for (UINT8 byIndex = eGPDTListInfo; byIndex < eGPDTMax; ++byIndex)
    {
        EGuildPubDataType eType = static_cast<EGuildPubDataType>(byIndex);
        _mapDataManager[eType] = CTableManagerBaseForGuildPub::CreateManager(eType, _qwGuildID);
    }
}

CDBPubGuildData::~CDBPubGuildData()
{
}

bool CDBPubGuildData::HasUpdateNum()
{
    for (auto iter = _mapDataManager.begin(); iter != _mapDataManager.end();iter++)
    {
        if (iter->second->GetUpdataNum())
            return true;
    }
    return false;
}

UINT32 CDBPubGuildData::UpdateNum()
{
    UINT32 dwNum = 0;
    for (auto iter = _mapDataManager.begin(); iter != _mapDataManager.end();iter++)
    {
        dwNum += iter->second->GetUpdataNum();
    }
    return dwNum;
}

UINT64 CDBPubGuildData::GetGuildID() const
{
    return _qwGuildID;
}

UINT32 CDBPubGuildData::GetNowUpdate() const
{
    return _dwNowUpdate;
}

void    CDBPubGuildData::SetNowUpdate(UINT32 dwNowUpdate)
{
    _dwNowUpdate = dwNowUpdate;
}

void    CDBPubGuildData::AddNowUpdate(UINT32 dwNowUpdate /* = 1 */)
{
    _dwNowUpdate += dwNowUpdate;
}

EGuildUpdateStatus CDBPubGuildData::GetUpdateStatus() const
{
    return _eUpdateDataStatus;
}

void CDBPubGuildData::SetUpdateStatus(EGuildUpdateStatus eStatus)
{
    _eUpdateDataStatus = eStatus;
}

CTableManagerBaseForGuildPub* CDBPubGuildData::GetDataManagerByType(EGuildPubDataType etype)
{
    auto iter = _mapDataManager.find(etype);
    if (iter != _mapDataManager.end())
        return iter->second;
    return NULL;
}
