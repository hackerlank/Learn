#include "stdafx.h"
#include "Protocols.h"
#include "User.h"
#include "LoginPkgMgr.h"
#include "Parameter.h"
#include "Loot.h"
#include "Player.h"
#include "LoginPkgProtS.h"

extern CLoginPkgMgr g_LoginPkgMgr;
const static UINT8 byMaxDay = 14;
CLoginPkgMgr::CLoginPkgMgr(CPlayer &rPlayer) : 
    CRegiserterEvent(eActClass_LoginPkg,rPlayer),
    _rPlayer(rPlayer)
{
     _dwEventID = 10010;
     _dwDays = 1;
}

void CLoginPkgMgr::RegisterLoginEvent()
{
     RegisterEventInit(); 
     
     SEventInfoPtr pEventInfoPtr = GetEventInfo(_dwEventID,byMaxDay);
     if(pEventInfoPtr)
        _dwDays = pEventInfoPtr->dwParam1;
     
     AddEvent(_dwEventID,byMaxDay,0);

}

void CLoginPkgMgr::OnEvent(SEventInfoPtr pEventInfoPtr)
{
    if(pEventInfoPtr->dwApplyID == byMaxDay
       && pEventInfoPtr->dwEventInstID == _dwEventID)
    {
        _dwDays = pEventInfoPtr->dwParam1;
        _rPlayer.GetUser().GetVars().SetVar(ePlayerVarLoginDays,_dwDays);
        LOG_CRI  << _rPlayer.GetRoleID() << "Login Days = " << _dwDays ; 
    }
}

EResultInLoginProt CLoginPkgMgr::GetLoginPkg(CUser &rUser,UINT8 byIndex, UINT16 &wResult)
{
    EResultInLoginProt eResult = ePkgGain;
    
    if(byIndex > _dwDays)
    {
        LOG_CRI << " 登入天数不够";
        return ePkgError;
    }
    if(byIndex > 14 || byIndex < 1)
        return ePkgError;
    UINT64 qwVar = rUser.GetVars().GetVar(ePlayerLoginPkg);
    UINT8 byFlag = (qwVar >> (byIndex - 1)) & 1;
    if(byFlag == 1)
    {
        return eResult;
    }
    UINT32 dwIndex;
    switch(byIndex)
    {
#define CASE(dwIndex,id) case id: dwIndex=SParamConfig::wLoginPkg##id; break;
      CASE(dwIndex,1);
      CASE(dwIndex,2);
      CASE(dwIndex,3);
      CASE(dwIndex,4);
      CASE(dwIndex,5);
      CASE(dwIndex,6);
      CASE(dwIndex,7);
      CASE(dwIndex,9);
      CASE(dwIndex,11);
      CASE(dwIndex,13);
      CASE(dwIndex,14);
        default:
      dwIndex = SParamConfig::wLoginPkg14;
      break;
    }
    TVecItemGenInfo vecItems;
    TVecResource vecRes;
    LOOT.Roll(dwIndex, vecItems,vecRes);
    for(auto it=vecRes.begin(); it!=vecRes.end(); ++it)
    {
        SItemGenInfo tepInfo;
        SResource &rRes = *it;
        tepInfo.wItemID = rRes._eRes;
        tepInfo.dwCount = rRes._dwValue;
        vecItems.push_back(tepInfo);

    }
    if(!vecItems.empty())
    {
        CPack& oPack = rUser.GetPack();
        if(!oPack.CanAddItem(vecItems))
        {
            return ePkgFull;
        }
        else
        {
            oPack.AddItem(vecItems,NLogDataDefine::ItemFrom_LoginPkg);
            qwVar = qwVar | (1 << (byIndex - 1));
            wResult = static_cast<UINT16>(qwVar);
        }
    }
    rUser.GetVars().SetVar(ePlayerLoginPkg, qwVar);

    if(rUser.GetPlayer())
    {
        TVecINT32 vecParam;
        vecParam.push_back(dwIndex);
        rUser.GetPlayer()->OnEvent(eEventType_14DaysGift,vecParam);
    }
   return ePkgSuccess; 
}

bool CLoginPkgMgr::GetPkgInfo(CUser &rUser,UINT16& wDays,UINT16& wResult)
{
    wDays = static_cast<UINT16>(_dwDays);
    UINT64 qwVar = rUser.GetVars().GetVar(ePlayerLoginPkg);
    wResult = static_cast<UINT16>(qwVar);
    LOG_INF << "GetPkgInfo wDays("<<wDays<<"),wResult("<<wResult<<").";
    return true;
}

void CLoginPkgMgr::SendPkgInfoFor0()
{
    UINT16 wDays = 0;
    UINT16 wResult = 0;
    UINT64 qwVar = 0;
    CUser& rUser = _rPlayer.GetUser();
    if(rUser.GetUserState() == eUserInGame)
    {
        wDays = static_cast<UINT16>(_dwDays);
        qwVar = rUser.GetVars().GetVar(ePlayerLoginPkg);
        wResult = static_cast<UINT16>(qwVar);
        if(!(wResult & (1 << 13)))
           _rPlayer.SendPkg(g_LoginPkgProtS.BuildPkg_SendPkgInfo(wDays,wResult));
    }
}

UINT32 CLoginPkgMgr::GetLoginDays()
{
    UINT32 dwDays = 0;
    CUser& rUser = _rPlayer.GetUser();
    dwDays = rUser.GetVars().GetVar(ePlayerVarLoginDays);
    
    return dwDays;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

