#include "stdafx.h"
#include "stdafx.h"
#include "SoulSpaceMgr.h"
#include "Player.h"
#include "User.h"
#include "Protocols.h"
#include "DemonTowerMgr.h"
#include "DemonTowerSvrS.h"
#include "SysMsgDefine.h"
#include "Skill.h"
CSoulSpaceMgr::CSoulSpaceMgr(CPlayer* pPlayer):
    _pPlayer(pPlayer)
{
    
}

void CSoulSpaceMgr::LoadFromDB(const TVecSoulSpaceInfo& vecSoulSpaceInfo)
{
    for(auto itr = vecSoulSpaceInfo.begin(); itr != vecSoulSpaceInfo.end(); ++itr)
    {
        CSoulSpaceExPtr pSoulSpace(new CSoulSpaceEx());
        pSoulSpace->dwSoulSpaceID = itr->dwSoulSpaceID;
        pSoulSpace->dwSoulSpaceLevel = itr->dwSoulSpaceLevel;

    }

    LOG_INF<<"CSoulSpaceMgr::LoadFromDB!";
    NotifyList();
}

void CSoulSpaceMgr::Update2DB(CSoulSpaceExPtr pSoulSpaceEx, EDataChange eDataChanige /*= eOpUpdate*/)
{
    if(NULL == pSoulSpaceEx)
    {
        return;
    }
    SSoulSpaceInfo rInfo;
    rInfo.qwRoleID = _pPlayer->GetRoleID();
    rInfo.dwSoulSpaceID = pSoulSpaceEx->dwSoulSpaceID;
    rInfo.dwSoulSpaceLevel = pSoulSpaceEx->dwSoulSpaceLevel;
    Update2DB(rInfo,eDataChanige);
}

void CSoulSpaceMgr::Update2DB(SSoulSpaceInfo& rInfo, EDataChange eDataChange/* = eOpUpdate*/)
{
    if(NULL == _pPlayer)
    {
        return;
    }

    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    
    g_Game2DBCommC.Send_RoleDataUpdate(_pPlayer->GetUserID(), eTypeSoulSpaceInfo, eDataChange, strData);
}

//升级
void CSoulSpaceMgr::Upgrade(UINT32 dwSoulSpaceID)
{
    /*这功能不用了
    CUser& rUser = _pPlayer->GetUser();

    auto itr = _mapSoulSpaceExPtr.find(dwSoulSpaceID);
    if(itr == _mapSoulSpaceExPtr.end())
    {
        UINT32 dwSpaceID = SKILLANDLEVEL(dwSoulSpaceID,1);

        SSoulSpaceCFGExPtr pSoulSpaceCFGEx =  g_DemonTowerMgr.GetSoulSpaceCFG(dwSpaceID);
        if(NULL == pSoulSpaceCFGEx)
        {
            rUser.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgRoleLevelErr));
            return;
        }
        if(pSoulSpaceCFGEx->_NeedLevel > _pPlayer->GetLevel())
        {
            rUser.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgRoleLevelErr));
            return;
        }

        if(!rUser.CanSubMoney((EMoneyType)pSoulSpaceCFGEx->_NeedMoneyType,pSoulSpaceCFGEx->_NeedMoneyValue))
        {
            rUser.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDemonTowerSoulNoEnough));
            return;
        }
        CSoulSpaceExPtr pSoulSpaceEx(new CSoulSpaceEx);
        pSoulSpaceEx->dwSoulSpaceID = dwSoulSpaceID;
        pSoulSpaceEx->dwSoulSpaceLevel = 1;
        pSoulSpaceEx->_bChange = true;
        _mapSoulSpaceExPtr.insert(make_pair(dwSoulSpaceID,pSoulSpaceEx));
        Update2DB(pSoulSpaceEx,eOpAdd);
        rUser.SendPkg(g_DemonTowerSvrS.BuildPkg_UpgradeSoulSpaceNotify(pSoulSpaceEx->dwSoulSpaceID,pSoulSpaceEx->dwSoulSpaceLevel));
    }
    else
    {
        UINT32 dwSpaceID = SKILLANDLEVEL(dwSoulSpaceID,itr->second->dwSoulSpaceLevel+1);
        SSoulSpaceCFGExPtr pSoulSpaceCFGEx =  g_DemonTowerMgr.GetSoulSpaceCFG(dwSpaceID);
        if(NULL == pSoulSpaceCFGEx)                                                      
        {
            rUser.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgCfgErr));;
           return;        
        }
        if(pSoulSpaceCFGEx->_NeedLevel > _pPlayer->GetLevel())
        {
            rUser.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgRoleLevelErr));
            return;
        }

        if(!rUser.CanSubMoney((EMoneyType)pSoulSpaceCFGEx->_NeedMoneyType,pSoulSpaceCFGEx->_NeedMoneyValue))
        {
            rUser.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDemonTowerSoulNoEnough));
            return;
        }
        
        if(!rUser.SubMoney((EMoneyType)pSoulSpaceCFGEx->_NeedMoneyType,pSoulSpaceCFGEx->_NeedMoneyValue,))
        {
            return;
        }

        //升级
        itr->second->dwSoulSpaceLevel += 1;
        Update2DB(itr->second);

        rUser.SendPkg(g_DemonTowerSvrS.BuildPkg_UpgradeSoulSpaceNotify(itr->second->dwSoulSpaceID,itr->second->dwSoulSpaceLevel));
    }

    _bChange = true;
    */

}


void CSoulSpaceMgr::NotifyList()
{

    LOG_INF<<"CSoulSpaceMgr::NotifyList";
    TVecSpaceInfo vecSpaceInfo;

    for(auto itr =  _mapSoulSpaceExPtr.begin(); itr != _mapSoulSpaceExPtr.end(); itr++)
    {
        SSpaceInfo oSpaceInfo;
        oSpaceInfo.dwSoulSpaceID = itr->second->dwSoulSpaceID;
        oSpaceInfo.dwSoulSpaceLevel = itr->second->dwSoulSpaceLevel;
        vecSpaceInfo.push_back(oSpaceInfo);
    }

    CUser& rUser = _pPlayer->GetUser();
    bool bRet = rUser.SendPkg(g_DemonTowerSvrS.BuildPkg_SoulSpaceListNotify(vecSpaceInfo));
    if(!bRet)
    {
        LOG_CRI<<"NotifyList fail";
    }

}

const TVecFloat& CSoulSpaceMgr::GetAttrVec()  
{ 
    RebuildAttr();
    return _vecAttr; 
}

void CSoulSpaceMgr::RebuildAttr()
{
    if(!_bChange)
    {
        return;
    }

    _vecAttr.clear();

    for(auto itr = _mapSoulSpaceExPtr.begin(); itr != _mapSoulSpaceExPtr.end(); ++itr)
    {
        UINT32 dwSpaceID = SKILLANDLEVEL(itr->second->dwSoulSpaceID,itr->second->dwSoulSpaceLevel);
        SSoulSpaceCFGExPtr pSoulSpaceCFGEx =  g_DemonTowerMgr.GetSoulSpaceCFG(dwSpaceID);
        if(NULL != pSoulSpaceCFGEx)                                                      
        {
            _vecAttr += pSoulSpaceCFGEx->_vecAttr;
           return;        
        }

    }

    _bChange = false;

}
