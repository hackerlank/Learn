#include "DBRoleData.h"
#include "DBRoleMgr.h"

bool SDBRoleData::HasUpdateNum()
{
    for (auto iter = _mapDataManager.begin(); iter != _mapDataManager.end();iter++)
    {
        if (iter->second->GetUpdataNum())
        {
            return true;
        }

    }
    return false;
}

UINT32 SDBRoleData::UpDateNum()
{
    UINT32 DwNum = 0;
    for (auto iter = _mapDataManager.begin(); iter != _mapDataManager.end();iter++)
    {
        DwNum += iter->second->GetUpdataNum();
    }
    return DwNum;
}

TableManagerBaseForRole* SDBRoleData::GetDataManagerByType(EDataType etype)
{
    auto iter = _mapDataManager.find(etype);
    if (iter != _mapDataManager.end())
    {
        return iter->second;
    }
    return NULL;
}

UINT16 SDBRoleData::GetMapID()
{
    TableManagerBaseForRole* pMgr = GetDataManagerByType(eTypeRoleBaseInfo);
    if (pMgr)
        return static_cast<DBRoleBaseTableManager*>(pMgr)->GetMapID();
    return 0;
}

EUserState SDBRoleData::GetUserState()
{
    return _eUserState;
}

void SDBRoleData::SetUserState(EUserState eUserState)
{
    if (_eUserState == eUserState)
    {
        return ;
    }
    LOG_INF << "SDBRoleData::SetUserState:" << eUserState;
    TableManagerBaseForRole* pBaseMgr = GetDataManagerByType(eTypeRoleBaseInfo);
    if (pBaseMgr)
    {
        DBRoleBaseTableManager* pMgr = static_cast<DBRoleBaseTableManager*>(pBaseMgr);
        switch(eUserState)
        {
            case eUserInGame:
                {
                    if(_eUserState != eUserReplace)
                    {
                        pMgr->Login();
                        CDBRoleMgr::Instance().CheckRoleState(this,true);
                    }

                }
                break;
            case eUserLeaveAway:
            case eUserLeaveOff:
                {
                    if(_eUserState == eUserReplace || _eUserState == eUserInGame)
                    {
                        pMgr->LoginOff();
                        CDBRoleMgr::Instance().CheckRoleState(this,true);
                    }

                }
                break;
            default:
                break;

        }
    }
    _eUserState = eUserState;
}

UINT32 SDBRoleData::GetFreezeTimer()
{
    TableManagerBaseForRole* pBaseMgr = GetDataManagerByType(eTypeRoleBaseInfo);
    if (pBaseMgr)
    {
        DBRoleBaseTableManager* pMgr = static_cast<DBRoleBaseTableManager*>(pBaseMgr);
        if(pMgr)
        {
            return pMgr->GetFreezeTimer();
        }
    }
    return 0;
}
