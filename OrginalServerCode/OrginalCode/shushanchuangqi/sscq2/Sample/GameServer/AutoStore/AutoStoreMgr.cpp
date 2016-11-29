#include "stdafx.h"
#include "stdafx.h"
#include "AutoStoreMgr.h"
#include "Player.h"
#include "User.h"
#include "Game2DBCommC.h"
extern CGame2DBCommC g_Game2DBCommC;
bool CAutoStoreMgr::AutoStoreInit()
{
    return true;
}

CAutoStoreMgr::CAutoStoreMgr(CPlayer& rPlayer):
    _rPlayer(rPlayer)
{
    
}

bool CAutoStoreMgr::LoadFromDB(const RoleDataInfo& rRoleDataInfo)
{
    for(size_t i=0;i < rRoleDataInfo.vecAutoStoreDBInfo.size(); i++)
    {
        SAutoStoreKey oAutoStoreKey(rRoleDataInfo.vecAutoStoreDBInfo[i].wType,rRoleDataInfo.vecAutoStoreDBInfo[i].dwClassID); 
        _mapAutoStoreDBInfo.insert(make_pair(oAutoStoreKey,rRoleDataInfo.vecAutoStoreDBInfo[i]));
    }
    return true;
}

void CAutoStoreMgr::Update2DB(const SAutoStoreDBInfo& rInfo, EDataChange eDataChange/* = eOpUpdate*/)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeAutoStore, eDataChange, strData);
}

 //增加值(注意初始值默认为0)
void CAutoStoreMgr::AddValue(EAutoStore eType,UINT32  dwClassID,UINT32  dwAddvalue)
{
    SAutoStoreKey oAutoStoreKey(eType,dwClassID);
    auto itr = _mapAutoStoreDBInfo.find(oAutoStoreKey);
    if(itr != _mapAutoStoreDBInfo.end())
    {
        itr->second.dwValue += dwAddvalue;
        Update2DB(itr->second);
    }
    else
    {
        SetValue(eType,dwClassID,dwAddvalue);
    }

}

//设置值
void CAutoStoreMgr::SetValue(EAutoStore eType,UINT32  dwClassID,UINT32  dwvalue)
{
    SAutoStoreKey oAutoStoreKey(eType,dwClassID);
    auto itr = _mapAutoStoreDBInfo.find(oAutoStoreKey);
    if(itr != _mapAutoStoreDBInfo.end())
    {
        itr->second.dwValue = dwvalue;
        Update2DB(itr->second);
    }
    else
    {
        SAutoStoreDBInfo oAutoStoreDBInfo(_rPlayer.GetRoleID(),eType,dwClassID,dwvalue);
        _mapAutoStoreDBInfo.insert(make_pair(oAutoStoreKey,oAutoStoreDBInfo));
        Update2DB(oAutoStoreDBInfo);
    }
}

//如果未找到默认返回值0
UINT32 CAutoStoreMgr::GetValue(EAutoStore eType,UINT32  dwClassID)
{
    SAutoStoreKey oAutoStoreKey(eType,dwClassID);
    auto itr = _mapAutoStoreDBInfo.find(oAutoStoreKey);
    if(itr != _mapAutoStoreDBInfo.end())
    {
        return itr->second.dwValue;
    }
    return 0;
}

//删掉值
void CAutoStoreMgr::Remove(EAutoStore eType,UINT32  dwClassID)
{
    SAutoStoreKey oAutoStoreKey(eType,dwClassID);
    auto itr = _mapAutoStoreDBInfo.find(oAutoStoreKey);
    if(itr != _mapAutoStoreDBInfo.end())
    {
        Update2DB(itr->second,eOpDel);
        _mapAutoStoreDBInfo.erase(itr);
    }
}

//清理某类数据
void CAutoStoreMgr::ClearValue(EAutoStore eType)
{
    for(auto itr = _mapAutoStoreDBInfo.begin(); itr != _mapAutoStoreDBInfo.end();)
    {
        auto itrTmp = itr;
        itr++;
        if(itrTmp->second.wType == eType)
        {
            Update2DB(itrTmp->second,eOpDel);
            _mapAutoStoreDBInfo.erase(itrTmp);
        }
    }
}

//获取某个类型的全部值
void CAutoStoreMgr::GetListByType(EAutoStore eType,TVecAutoStoreDBInfo& vecAutoStoreDBInfo)
{
    
    for(auto itr = _mapAutoStoreDBInfo.begin(); itr != _mapAutoStoreDBInfo.end();)
    {
        auto itrTmp = itr;
        itr++;
        if(itrTmp->second.wType == eType)
        {
            vecAutoStoreDBInfo.push_back(itrTmp->second);
        }
    }

}


//零点事件
void CAutoStoreMgr::OnMidNight()
{
    ClearValue(eAutoStore_BattleArray);
    ClearValue(eAutoStore_Activity_ShareFriend);
}

//19点事件
void CAutoStoreMgr::On19Event()
{

}

