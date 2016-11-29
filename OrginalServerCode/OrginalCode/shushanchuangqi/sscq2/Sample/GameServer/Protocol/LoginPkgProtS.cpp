
#include "LoginPkgProtS.h"
#include "User.h"
#include "Player.h"
#include "UserMgr.h"
#include "LoginPkgProt.h"
#include "LoginPkgMgr.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "GameNetMgr.h"

CLoginPkgProtS g_LoginPkgProtS;
//接收：获取礼
bool CLoginPkgProtS::OnRecv_GetLoginPkg(
		UINT8 byIndex, //累计天数
		shared_func<SGetLoginPkgAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser,&pPlayer))
    {
        fnAck->eResult = ePkgError;
        return false;
    }
    CLoginPkgMgrPtr pLoginPkg = pPlayer->GetLoginPkgMgr();
    if(pLoginPkg)
        fnAck->eResult = pLoginPkg->GetLoginPkg(*pUser,byIndex,fnAck->wResult);
    return true;
}
      //接收：登入礼包信息
bool CLoginPkgProtS::OnRecv_GetPkgInfo(
		shared_func<SGetPkgInfoAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser,&pPlayer))
    {
        return false;
    }
    CLoginPkgMgrPtr pLoginPkg = pPlayer->GetLoginPkgMgr();
    if(pLoginPkg)
    pLoginPkg->GetPkgInfo(*pUser,fnAck->wDays,fnAck->wResult);
    return true;
}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

