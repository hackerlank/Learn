#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "HorseSvrS.h"
#include "HorseMgr.h"
#include "GameNetMgr.h"

CHorseSvrS g_HorseSvrS;

//接收：获取坐骑列表
void CHorseSvrS::OnRecv_GetHorseList(
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return;                       
    }                                       

    CHorseMgrPtr pHorseMgr = pPlayer->GetHorseMgr();

    if(pHorseMgr)
    {
        pHorseMgr->HorseNotifyList();
    }


}

//接收：激活坐骑
bool CHorseSvrS::OnRecv_ActiveHorse(
	UINT32 dwHorseID, //坐骑ID
	shared_func<SActiveHorseAck>& fnAck //返回回调函数
)
{
    fnAck->dwRet  = -1;
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }                                       

    CHorseMgrPtr pHorseMgr = pPlayer->GetHorseMgr();

    if(pHorseMgr)
    {
        if(pHorseMgr->ActiveHorse(dwHorseID))
        {
            fnAck->dwRet = 0;
        }
        else
        {
            fnAck->dwRet = 1;
        }
    }

    return true;
}
 //接收：坐骑进阶
 bool CHorseSvrS::OnRecv_UpgradeHorse(
        UINT32 dwHorseID, //坐骑ID
		bool bAll, //是否一键进阶
		shared_func<SUpgradeHorseAck>& fnAck //返回回调函数
	)

{
    fnAck->dwRet  = -1;
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }                                       

    CHorseMgrPtr pHorseMgr = pPlayer->GetHorseMgr();

    if(pHorseMgr)
    {
        if(bAll)
        {
            fnAck->dwRet = 0;
            //for(UINT32 i=0;i < 100000; i++)
            {
               pHorseMgr->UpgradeHorse(dwHorseID,bAll);
               //if(byRet != 2)
               // {
               //     break;
               // }
            }
        }
        else
        {
            UINT8 bRet = pHorseMgr->UpgradeHorse(dwHorseID);
            if(bRet)
            {
                fnAck->dwRet = 0;
            }
        }
    }
    return true;
}

//接收：骑乘状态修改
bool CHorseSvrS::OnRecv_SetHorseStatus(
        UINT32 dwHorseID, //坐骑ID
		UINT32 eHorseStatus, //骑乘状态
		shared_func<SSetHorseStatusAck>& fnAck //返回回调函数
	)
{
    fnAck->bRet = false;
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }                                       

    CHorseMgrPtr pHorseMgr = pPlayer->GetHorseMgr();

    if(pHorseMgr)
    {

       fnAck->bRet = pHorseMgr->SetHorseStatus(dwHorseID,eHorseStatus);
              
    }

    return true;

}


//接收：获取坐骑属性
bool CHorseSvrS::OnRecv_GetHorseAttr(
    UINT32 dwHorseID, //坐骑ID
	shared_func<SGetHorseAttrAck>& fnAck //返回回调函数
)
{
    fnAck->dwRet = -1;
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }                                       

    CHorseMgrPtr pHorseMgr = pPlayer->GetHorseMgr();

    if(pHorseMgr)
    {

       pHorseMgr->NotifyAttrList(dwHorseID);
       
       fnAck->dwRet = 0;
       
    }

    return true;

}


//接收：解锁技能属性
bool CHorseSvrS::OnRecv_UnLockHorseSkillAttr(
		UINT32 dwHorseID, //坐骑ID
		UINT32 dwPos, //第几个技能属性 1开始
		shared_func<SUnLockHorseSkillAttrAck>& fnAck //返回回调函数
	)
{
    fnAck->bRet = false;
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }                                       

    CHorseMgrPtr pHorseMgr = pPlayer->GetHorseMgr();

    if(pHorseMgr)
    {
       fnAck->bRet = pHorseMgr->UnLockHorseSkillAttr(dwHorseID,dwPos);
    }

    return true;

}

