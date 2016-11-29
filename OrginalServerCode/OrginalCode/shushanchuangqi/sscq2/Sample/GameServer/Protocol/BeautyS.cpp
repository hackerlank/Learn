#include "stdafx.h"
#include "BeautyS.h"
#include "User.h"
#include "Player.h"
#include "BeautyMgr.h"
//#include "Game2CenterLogC.h"
#include "RoleInfoDefine.h"
#include "GameNetMgr.h"

using namespace NRoleInfoDefine;
CBeautyS g_BeautyS;

//extern CGame2CenterLogC g_Game2CenterLog;

//接收：获取美女信息
 bool CBeautyS::OnRecv_GetBeatyInfo(
	shared_func<SGetBeatyInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
    if(pBeautyMgr)
    {
        pBeautyMgr->OnGetBeatyInfo(fnAck);
    }

    return true;

}

//接收：结识美女
 bool CBeautyS::OnRecv_MeetBeauty(
	UINT16 wBeautyID, //美女id
	shared_func<SMeetBeautyAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
    if(pBeautyMgr)
    {
        fnAck->eRet = pBeautyMgr->OnMeetBeauty(wBeautyID);
    }

    return true;


}

//接收：和美女聊天
 bool CBeautyS::OnRecv_ChatBeauty(
	UINT16 wBeautyID, //美女id
	shared_func<SChatBeautyAck>& fnAck //返回回调函数
)
{   
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
    if(pBeautyMgr)
    {
        fnAck->eRet = pBeautyMgr->OnChatBeauty(wBeautyID);
    }

    return true;


}

//接收：送美女礼品
 bool CBeautyS::OnRecv_SendPrizeBeauty(
	UINT16 wBeautyID, //美女id
	const NItemProt::TVecItemCount& vecItemCount, //物品列表
	shared_func<SSendPrizeBeautyAck>& fnAck //返回回调函数
)
{   
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
    if(pBeautyMgr)
    {
        fnAck->eRet = pBeautyMgr->OnSendPrizeBeauty(wBeautyID,vecItemCount);
    }

    return true;


}
//接收：抽奖
 bool CBeautyS::OnRecv_LotteryBeauty(
	ELotteryBeautyType eLotteryBeautyType, //抽奖类型
	shared_func<SLotteryBeautyAck>& fnAck //返回回调函数
)
{   
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
    if(pBeautyMgr)
    {
        fnAck->eRet=pBeautyMgr->OnLotteryBeauty(eLotteryBeautyType,fnAck->vecItemGenInfo);
    }

    return true;

}
//接收：美女出战
bool CBeautyS::OnRecv_BeautyFight(
	UINT16 wBeautyID, //美女id
	shared_func<SBeautyFightAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
    if(pBeautyMgr)
    {
        fnAck->eRet=pBeautyMgr->OnBeautyFight(wBeautyID);
    }
    return true;
}

//接收：获取稀有物品列表
bool CBeautyS::OnRecv_GetRareItemList(
	shared_func<SGetRareItemListAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
    if(pBeautyMgr)
    {
        pBeautyMgr->GetTakedRareItem(fnAck->vecItemID);
    }

    return true;
}
//接收：获取当前已免费抽奖次数
void CBeautyS::OnRecv_GetLotteryFreeCnt(
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return ;                       
    }

    CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
    if(pBeautyMgr)
    {
        pBeautyMgr->OnGetLotteryFreeCnt();
    }
}

