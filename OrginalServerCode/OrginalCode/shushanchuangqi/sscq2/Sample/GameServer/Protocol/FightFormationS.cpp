#include "stdafx.h"
#include "FightFormationS.h"
#include "User.h"
#include "Player.h"
#include "FightFormationMgr.h"
#include "FightHeroInfoMgr.h"
#include "RoleInfoDefine.h"
#include "GameNetMgr.h"

using namespace NRoleInfoDefine;
CFightFormationS g_FightFormationS;

//extern CGame2CenterLogC g_Game2CenterLog;

	//接收：取得阵形信息
bool CFightFormationS::OnRecv_GetFightFormation(
	UINT16 wBattleType, //战斗类型
	shared_func<SGetFightFormationAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CFightFormationMgrPtr pFightFormationMgr = pPlayer->GetFightFormationMgr();
    if(pFightFormationMgr)
    {
        pFightFormationMgr->OnGetFormation(wBattleType,fnAck->oFightFormation);
    }

    return true;
}

//接收：设置阵形信息
bool CFightFormationS::OnRecv_SetFightFormation(
	UINT16 wBattleType, //战斗类型
	const FightFormationInfo& oFightFormation, //阵形ID
	shared_func<SSetFightFormationAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CFightFormationMgrPtr pFightFormationMgr = pPlayer->GetFightFormationMgr();
    if(pFightFormationMgr)
    {
        fnAck->eRet = pFightFormationMgr->OnSetFormation(wBattleType,oFightFormation);
    }

    return true;
}
//接收：战斗散仙信息
bool CFightFormationS::OnRecv_GetFightHeroInfo(
	UINT16 wBattleType, //战斗类型 EBattleType
	shared_func<SGetFightHeroInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CFightHeroInfoMgrPtr pFightHeroInfoMgr = pPlayer->GetFightHeroInfoMgr();
    if(pFightHeroInfoMgr)
    {
        pFightHeroInfoMgr->OnGetFightHeroInfo(wBattleType,fnAck->vecFightHeroInfo);
    }

    return true;
}

