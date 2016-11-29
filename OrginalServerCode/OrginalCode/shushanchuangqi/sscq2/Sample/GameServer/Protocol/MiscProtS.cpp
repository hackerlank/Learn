#include "stdafx.h"
#include "MiscProtS.h"
#include "User.h"
#include "Player.h"
#include "EnergyMgr.h"
#include "Game2CenterLogC.h"
#include "ProtoCommon.h"
#include "GodChest.h"
#include "Lottery.h"
#include "GameNetMgr.h"
#include "EverydayRecharge.h"

using namespace NProtoCommon;
CMiscProtS g_MiscProtS;

extern CGame2CenterLogC g_Game2CenterLog;

//接收：设置防沉迷状态
void CMiscProtS::OnRecv_SetIndulge(
        bool bIndulge //设置防沉迷状态
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return;

    /*
       if(pUser)
       pUser->SetIndulge(bIndulge);
       */

}
//接收：设置防沉迷收益率
void CMiscProtS::OnRecv_SetIndulgeRate(
        UINT32 dwIndulgeRate //设置防沉迷收益率
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
       return;

   if(pUser)
       pUser->SetIndulgeRate(dwIndulgeRate);
}

//接收：购买体力
bool CMiscProtS::OnRecv_BuyAction(
        shared_func<SBuyActionAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        return false;                       
    }

    CEnergyMgrPtr pEnergyMgr= pPlayer->GetEnergyMgr();

    if(pEnergyMgr)
    {
        fnAck->dwRet = pEnergyMgr->BuyAction();
        fnAck->dwCount = pEnergyMgr->GetBuyActionCount();
        fnAck->dwPrice = pEnergyMgr->GetBuyPrice();
    }


    return true;


}

//接收：获取购买体力次数
bool CMiscProtS::OnRecv_GetBuyActionCount(
        shared_func<SGetBuyActionCountAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        return false;                       
    }
    CEnergyMgrPtr pEnergyMgr= pPlayer->GetEnergyMgr();

    if(pEnergyMgr)
    {
        fnAck->dwCount =  pEnergyMgr->GetBuyActionCount();
        fnAck->dwPrice =  pEnergyMgr->GetBuyPrice();
        fnAck->dwAction = pUser->GetMoney(EMONEY_ACTION);

    }


    return true;

}
//接收：获取体力buff数值
void CMiscProtS::OnRecv_GetActionBuff(
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        return;                       
    }
    CEnergyMgrPtr pEnergyMgr= pPlayer->GetEnergyMgr();

    if(pEnergyMgr)
    {
        pEnergyMgr->NotifyActionBuffer();
    }
}
//接收：发送udplog
void CMiscProtS::OnRecv_SendUdpLog(
        const std::string& strParam1, //参数1
        const std::string& strParam2 //参数2
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        return;                       
    }

    g_Game2CenterLog.Send_LogAct(pPlayer->GetUserID(),strParam1,strParam2,"","","","",1);
}

//接收：获取货币基础数值
bool CMiscProtS::OnRecv_GetMoneyList(
        shared_func<SGetMoneyListAck>& fnAck //返回回调函数
        )
{

    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        return false;                       
    }

    pUser->GetMoneyList(fnAck->vecMoneyCount);

    return true;

}
//接收：领取体力buff
void CMiscProtS::OnRecv_TakeActionBuff(
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        return;                       
    }
    CEnergyMgrPtr pEnergyMgr= pPlayer->GetEnergyMgr();

    if(pEnergyMgr)
    {
        pEnergyMgr->OnTakeActionBuff();
    }

}
//接收：客户端黑屏Log
void CMiscProtS::OnRecv_ClientBlankScreenLog(
        const std::string& strParam1 //参数1
        )
{
    LOG_INF << "ClientBlankScreenLog: " << strParam1;

    return;
}

//接收：天赐宝箱
void CMiscProtS::OnRecv_OnEnter(
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        return ;                       
    }
    g_GodChest.OnEnter(*pPlayer);
    return ;

}

//接收：获得回合数和活动状态
void CMiscProtS::OnRecv_GetRount(
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        return;                       
    }
    g_GodChest.GetRount(*pPlayer);
    return ;
}
//接收：玩家抽奖
bool CMiscProtS::OnRecv_Draw(
        shared_func<SDrawAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        return false;                       
    }
    fnAck->eResult = g_Lottery.Draw(*pUser,fnAck->wLotteryID);
    return true;
}

//协议废置
//接收：客户端通知动画播放完毕
void CMiscProtS::OnRecv_DrawRet(
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        return ;                       
    }
    //g_Lottery.DrawRet(*pUser);
}

//接收：同步客户端玩家抽奖
void CMiscProtS::OnRecv_SendLottery(
        UINT32 dwTotalNum, //总的抽奖信息条数
        UINT32 dwSelfNum //自己的抽奖信息条数
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        return;                       
    }
    g_Lottery.SendLottery(*pUser,dwTotalNum,dwSelfNum);
}

//接收：获取每日冲值奖励
bool CMiscProtS::OnRecv_GetEveryDayRechargeAward(
        shared_func<SGetEveryDayRechargeAwardAck>& fnAck //返回回调函数
        ) 
{
    return false;
#if 0
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        return false;                       
    }
    g_EveryDayRechargeMgr.GetAward(*pUser,fnAck->eResult);
#endif
    return true;

}

//接收：获取每日冲值金额
bool CMiscProtS::OnRecv_GetEveryDayRecharge(
        shared_func<SGetEveryDayRechargeAck>& fnAck //返回回调函数
        ) 
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        return false;                       
    }
    fnAck->dwTotalRechargeToday = pUser->GetVars().GetVar(NVarDefine::ePlayerVarRechargeToday);
    return true;

}
//接收：分宝岩购买活动
bool CMiscProtS::OnRecv_BuyFenbaoyan(
        UINT16 wNum, //购买数量
        shared_func<SBuyFenbaoyanAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    { 
        fnAck->eRet = eMiscOptRes_Error;
        return false;                       
    }
    CFenbaoyanMgrPtr pFenbaoyan = pPlayer->GetFenbaoyan();
    if(pFenbaoyan)
        fnAck->eRet = pFenbaoyan->OnBuyFenbaoyan(wNum);
    return true;
}
//接收：分宝岩购买活动时间
bool CMiscProtS::OnRecv_FenbaoyanTime(
        shared_func<SFenbaoyanTimeAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    { 
        return false;                       
    }
    CFenbaoyanMgrPtr pFenbaoyan = pPlayer->GetFenbaoyan();
    if(pFenbaoyan)
        pFenbaoyan->GetTime(fnAck->dwBegin,fnAck->dwEnd);
    return true;
}

