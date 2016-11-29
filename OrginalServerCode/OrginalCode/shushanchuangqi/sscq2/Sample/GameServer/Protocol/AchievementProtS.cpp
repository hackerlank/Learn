
#include "AchievementProtS.h"
#include "User.h"
#include "Player.h"
#include "UserMgr.h"
#include "AchievementMgr.h"
#include "GameNetMgr.h"

CAchievementProtS g_AchievementProtS;

//接收：获取成就信息
bool CAchievementProtS::OnRecv_GeAchievementInfo(
	shared_func<SGeAchievementInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    CAchievementMgrPtr pAchievementMg =  pPlayer->GetAchievementMgr();
    if(pAchievementMg)
    {
        pAchievementMg->GetAchieveInfo(fnAck->vecAchievementInfo);
    }

    fnAck->wLevel = pPlayer->GetAchievementLevel();
    fnAck->dwAP   = pUser->GetMoney(EMONEY_ACHIEVEMENTAP);

    return true;


}
//接收：获取成就奖励
bool CAchievementProtS::OnRecv_TakePrize(
	UINT16 wAchievementID, //成就ID
	shared_func<STakePrizeAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    CAchievementMgrPtr pAchievementMg =  pPlayer->GetAchievementMgr();
    if(pAchievementMg)
    {
        fnAck->eRet = pAchievementMg->OnTakePrize(wAchievementID);
    }


    return true;
}
//接收：获取成就分享信息
bool CAchievementProtS::OnRecv_GeAchievementShareList(
	shared_func<SGeAchievementShareListAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CAchievementMgrPtr pAchievementMg =  pPlayer->GetAchievementMgr();
    if(pAchievementMg)
    {
        pAchievementMg->OnGeAchievementShareList(fnAck->vecAchievementShare);
    }

    return true;
}

//接收：获取成就分享奖励
bool CAchievementProtS::OnRecv_TakeSharePrize(
	UINT16 wAchievementID, //成就ID
	shared_func<STakeSharePrizeAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CAchievementMgrPtr pAchievementMg =  pPlayer->GetAchievementMgr();
    if(pAchievementMg)
    {
        fnAck->eRet = pAchievementMg->OnTakeSharePrize(wAchievementID);
    }


    return true;
}


/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

