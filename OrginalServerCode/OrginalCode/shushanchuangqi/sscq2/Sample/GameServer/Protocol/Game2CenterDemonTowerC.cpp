#include "stdafx.h"
#include "UserMgr.h"
#include "Game2CenterDemonTowerC.h"
#include "DemonTowerMgr.h"
#include "DemonTowerDgn.h"
#include "DungeonMgr.h"
#include "Map.h"
#include "DemonTowerMgr.h"
#include "SysMsgDefine.h"
#include "Protocols.h" 
#include "AttackedMgr.h"
#include "DemonTowerSvrS.h"
CGame2CenterDemonTowerC g_Game2CenterDemonTowerC;
//接收：玩家请求进入镇妖塔
void CGame2CenterDemonTowerC::OnRecv_EnterDemonTower(
	UINT64 qwUserID, //帐号ID
	UINT32 dwFloorID //层数
    )
{
     CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
     if (!pUser)                                         
        return;
     CPlayerPtr pPlayer = pUser->GetPlayer();
     if(!pPlayer)
     {
        return;
     }

     g_DemonTowerMgr.PlayerEnter(*pPlayer,dwFloorID);
    
}
//接收：玩家请求离开镇妖塔
void CGame2CenterDemonTowerC::OnRecv_LeaveDemonTower(
	UINT64 qwUsrID //帐号ID
)
{
     CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
       if (!pUser)                                         
            return;
     CPlayerPtr pPlayer = pUser->GetPlayer();
     if(!pPlayer)
     {
         return;
     }
    
     CGameMapPtr pMap = pPlayer->GetMap();
     if(NULL == pMap)
     {
        g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUsrID,1,eMsgDemonTowerErrorMap);

         return;
     }

     CDungeonPtr pDungeon = pMap->GetDungeon();
     if(NULL == pDungeon)
     {
         g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUsrID,1,eMsgDemonTowerNotInDgn);
         return;
     }
             
     if(pDungeon->GetDgnType() != eDemonTowerDgn)
     {
         g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUsrID,1,eMsgDemonTowerNotInDgn);
         return;
     }

     CDemonTowerDgnPtr pDemonTowerDgn = dynamic_pointer_cast<CDemonTowerDgn>(pDungeon);
     if(pDemonTowerDgn)
     {
        if(!pDemonTowerDgn->PlayerLeave(*pPlayer))
        {
            g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUsrID,1,eMsgDemonTowerLeaveFail);
        }
     }

}

//接收：获取每日魂值奖励
bool CGame2CenterDemonTowerC::OnRecv_TakeDailyPrize(
	UINT64 qwUsrID, //帐号ID
	shared_func<STakeDailyPrizeAck>& fnAck //返回回调函数
)
{


    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)                                       
       return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();            
    if(!pPlayer)
    {
       return false; 
    }

    g_DemonTowerMgr.TakeSealPrize(*pPlayer);
    return true;
}


void OnAttacked(const NDemonTower::SDemonToweAttackedInfo& oAttacker,CPlayerPtr pPlayer)
{
    
    if(NULL == pPlayer)
    {
        return;
    }
    
    CAttackedMgrPtr pAttackMgr = pPlayer->GetAttackedMgr();
     if(pAttackMgr)
     {
         SRoleAttaked rInfo;
         rInfo.qwRoleID = pPlayer->GetRoleID();
         rInfo.qwAtkRoleID = oAttacker.qwAtkRoleID;
         rInfo.strRoleName = oAttacker.strRoleName;
         rInfo.byLevel = oAttacker.byLevel;
         rInfo.dwAttackedTime = time(NULL);
         rInfo.dwFighterType = NDemonTower::eAttackedType_DemonTower;
         pAttackMgr->OnAttackedInfo(rInfo);
     }

}
//接收：被攻击信息
void CGame2CenterDemonTowerC::OnRecv_Attacked(
    UINT64 qwUsrID, //帐号ID
	const NDemonTower::SDemonToweAttackedInfo& oAttacker //被攻击信息
)
{
     CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
     if (!pUser) 
     {
         
         CUserMgr::LoadUser(qwUsrID,
                [oAttacker](CUserPtr pUser)
                {
                    if(NULL == pUser)
                    {
                        return;
                    }
                    CPlayerPtr pPlayer = pUser->GetPlayer();
                    if(NULL == pPlayer)
                    {
                        return;
                    }

                    OnAttacked(oAttacker,pPlayer);

                });
 

        return;
     }
     CPlayerPtr pPlayer = pUser->GetPlayer();
     OnAttacked(oAttacker,pPlayer);
     pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_AttackChangedNotify());
  
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

