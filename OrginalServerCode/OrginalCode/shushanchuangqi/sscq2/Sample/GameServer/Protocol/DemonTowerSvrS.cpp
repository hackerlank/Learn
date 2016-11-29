#include "stdafx.h"
#include "Protocols.h"
#include "Creature.h"
#include "UserMgr.h"
#include "Player.h"
#include "DemonTowerSvrS.h"
#include "DemonTowerMgr.h"
#include "DungeonMgr.h"
#include "DemonTowerDgn.h"
#include "SoulSpaceMgr.h"
#include "Game2CenterDemonTowerC.h"
#include "AttackedMgr.h"
#include "SysMsgDefine.h"
#include "GameNetMgr.h"

CDemonTowerSvrS g_DemonTowerSvrS;
//接收：进入锁妖塔(假的仅返回当前层的信息)
bool CDemonTowerSvrS::OnRecv_EnterDemonTower(
        UINT32 dwFloorID, //层数
        shared_func<SEnterDemonTowerAck>& fnAck //返回回调函数
        ) 
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         fnAck->dwRet = eDemonTower_Error;     
         return false;                       
    }
    
    EDungeonResult eResult;
    CDemonTowerDgnPtr pDemonTowerDgn = CDungeonMgr::CreateDemonTowerDgn(1001,*pPlayer,eResult);
    if(pDemonTowerDgn)
    {
        bool bRet = pDemonTowerDgn->PlayerEnterFloor(*pPlayer,dwFloorID);
        if(bRet)
        {
            fnAck->dwRet = 0;
            return true;
        }

    }
    fnAck->dwRet = -1;
    return true;
}

 //接收：离开锁妖塔
 bool CDemonTowerSvrS::OnRecv_LeaveDemonTower(
		shared_func<SLeaveDemonTowerAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         fnAck->dwRet = eDemonTower_Error;     
         return false;                       
    }


    //fnAck->dwRet = g_DemonTowerMgr.PlayerLeave(*pPlayer);
    return true;
}

//接收：封印怪物(挑战?)
bool CDemonTowerSvrS::OnRecv_SealMonster(
		UINT32 dwFloorID, //层数
		shared_func<SSealMonsterAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         fnAck->dwRet = eDemonTower_Error;     
         return false;                       
    }


    fnAck->dwRet = g_DemonTowerMgr.AttackMonster(*pPlayer,dwFloorID);
    return true;
}



//接收：升级魄空间                                   
bool CDemonTowerSvrS::OnRecv_UpgradeSoulSpace(
        UINT32 dwSoulSpaceID, //魄空间ID
        shared_func<SUpgradeSoulSpaceAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         fnAck->dwRet = eDemonTower_Error; 
         return false;                       
    }                                       

    CSoulSpaceMgrPtr pSoulSpaceMgr = pPlayer->GetSoulSpaceMgr();

    if(pSoulSpaceMgr)
        pSoulSpaceMgr->Upgrade(dwSoulSpaceID);
    return true;
}

//接收：获取魄空间列表
void CDemonTowerSvrS::OnRecv_GetSoulSpace(
	)
{
    
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return;                       
    }                                       

    CSoulSpaceMgrPtr pSoulSpaceMgr = pPlayer->GetSoulSpaceMgr();

    if(pSoulSpaceMgr)
    {
        pSoulSpaceMgr->NotifyList();
    }

    
}

//接收：获取被攻击列表
void CDemonTowerSvrS::OnRecv_GetAttackedList(
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return;                       
    }                                       

    CAttackedMgrPtr pAttacked = pPlayer->GetAttackedMgr();

    if(pAttacked)
    {
        TVecRoleAttaked vecRoleAttaked;
        pAttacked->GetAttakedList(vecRoleAttaked,eAttackedType_DemonTower);

        TVecDemonToweAttackedInfo VecDemonToweAttackedInfo;
        for(SRoleAttaked& rRoleAttacked:vecRoleAttaked)
        {
            SDemonToweAttackedInfo oDemonToweAttackedInfo;
            oDemonToweAttackedInfo.qwAtkRoleID =rRoleAttacked.qwAtkRoleID;
            oDemonToweAttackedInfo.strRoleName = rRoleAttacked.strRoleName;
            oDemonToweAttackedInfo.dwLayerID = 0;
            oDemonToweAttackedInfo.byLevel = rRoleAttacked.byLevel;
            oDemonToweAttackedInfo.dwAttackedTime = rRoleAttacked.dwAttackedTime;
            VecDemonToweAttackedInfo.push_back(oDemonToweAttackedInfo);
        }
        UINT32 dwServerID = pUser->GetCenterSvrID();
        UINT64 qwUserID = pUser->GetUserID();
        g_Game2CenterDemonTowerC.SendSvr_GetAttackedLayerInfo(&dwServerID,1, //发送给多个服务器
		qwUserID, //玩家账号
		VecDemonToweAttackedInfo, //被攻击列表
		[] (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUserID, //(返回值)玩家账号
			const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList //(返回值)被攻击列表
		)
        {
            if(0 != byRet_)
            {
                LOG_CRI<<"query Error!!!";
                return;
            }

            CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
            if (!pUser)                                         
                return;
             pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_AttackListNotify(oAttackedList));

        });


    }


}

	//接收：获取每日奖励
bool CDemonTowerSvrS::OnRecv_TakeDayPrize(
	shared_func<STakeDayPrizeAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         fnAck->dwRet = eDemonTower_Error;     
         return false;                       
    }


    fnAck->dwRet = g_DemonTowerMgr.TakeSealPrize(*pPlayer);

    return true;
}

//接收：领取每层奖励
bool CDemonTowerSvrS::OnRecv_TakeLayerPrize(
	UINT32 dwFloorID, //层数
	shared_func<STakeLayerPrizeAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         fnAck->dwRet = eDemonTower_Error;     
         return false;                       
    }


    fnAck->dwRet = g_DemonTowerMgr.TakeLayerPrize(*pPlayer,dwFloorID,fnAck->dwFloorID);

    return true;
}

//接收：获取最高已领奖层
bool CDemonTowerSvrS::OnRecv_GetTopPrizeLayer(
	shared_func<SGetTopPrizeLayerAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    fnAck->dwFloorID = pPlayer->GetLayerPrizeDemonFloorID();
    return true;
}

const UINT32 DEMONTOWER_DEATH = 19;

//接收：清除pve战斗cd
bool CDemonTowerSvrS::OnRecv_ClearFightMonsterCd(
	shared_func<SClearFightMonsterCdAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         fnAck->bRet = eDemonTower_Error;     
         return false;                       
    }

    if(!pPlayer->HasBuff(DEMONTOWER_DEATH))
    {
        fnAck->bRet = 0;
        return true;
    }

    if(!pUser->SubGoldOrCoupon(SParamConfig::wDemonTowerCleanCD1,eCouponCoin,NLogDataDefine::ItemTo_DemonTower))
    {
        fnAck->bRet = 1;
        pUser->SendSysMsg(eMsgGoldErr);
        return true;
    }

    pPlayer->RemoveBuff(DEMONTOWER_DEATH);

    fnAck->bRet = 0;
    pUser->SendSysMsg(eMsgDemonTowerClean); 

    TVecINT32 vecParam;
    vecParam.push_back(1);
    pPlayer->OnEvent(eEventType_DemonTowerClearPVECD,vecParam);

    return true;
}
//接收：获取已领奖励层数
bool CDemonTowerSvrS::OnRecv_GetLayerPrized(
	shared_func<SGetLayerPrizedAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    g_DemonTowerMgr.OnGetLayerPrized(*pPlayer,fnAck->vecFloorID);

    return true;
}

