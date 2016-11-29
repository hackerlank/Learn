
#include "ShengLingProtS.h"
#include "User.h"
#include "Player.h"
#include "UserMgr.h"
#include "ShengLingProt.h"
#include "ShengLing.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "GameNetMgr.h"

CShengLingProtS g_ShengLingProtS;

//接收：玩家打开活动面板
bool CShengLingProtS::OnRecv_OnOpen(
        shared_func<SOnOpenAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    { 
        return false;                       
    }
    CShengLingPtr pShengLing = pPlayer->GetShengLing();
    if(pShengLing)
        pShengLing->OnOpen(fnAck->byUseEnter,fnAck->byBuyEnter,fnAck->byBuyEnterToday,fnAck->bContinue);
    return true;
}
//接收：玩家进入圣陵
bool CShengLingProtS::OnRecv_OnEnter(
		shared_func<SOnEnterAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    { 
        fnAck->eResult = EShengLingResultError;
        return false;                       
    }
    CShengLingPtr pShengLing = pPlayer->GetShengLing();
    if(pShengLing)
        fnAck->eResult = pShengLing->OnEnter(fnAck->sInfo);
    return true;
}

//接收：玩家摇骰子
bool CShengLingProtS::OnRecv_DrawDice(
		shared_func<SDrawDiceAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    { 
        fnAck->eResult = EShengLingResultError;
        return false;                       
    }
    CShengLingPtr pShengLing = pPlayer->GetShengLing();
    if(pShengLing)
        fnAck->eResult = pShengLing->OnDrawDice(fnAck->byIndex,fnAck->sInfo,false,fnAck->qwBattleID);
    return true;
}
	
//接收：使用卡片
bool CShengLingProtS::OnRecv_UseCard(
		ECardType eCardType, //卡片类型
		UINT8 byIndex, //骰子数(转向时byIndex=0)
		shared_func<SUseCardAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    { 
        fnAck->eResult = EShengLingResultError;
        return false;                       
    }
    CShengLingPtr pShengLing = pPlayer->GetShengLing();
    if(pShengLing)
        fnAck->eResult = pShengLing->OnUseCard(eCardType,byIndex,fnAck->sCard,fnAck->sInfo,fnAck->qwBattleID);
    return true;
}
    
//接收：购买
bool CShengLingProtS::OnRecv_Buy(
		EBuyType eBuyType, //购买类型
		UINT8 byNum, //购买次数
		shared_func<SBuyAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    { 
        fnAck->eResult = EShengLingResultError;
        return false;                       
    }
    CShengLingPtr pShengLing = pPlayer->GetShengLing();
    fnAck->eBuyTypeRet = eBuyType;
    if(pShengLing)
        fnAck->eResult = pShengLing->OnBuy(eBuyType,byNum,fnAck->byBuy,fnAck->byUse,fnAck->byBuyToday);
    return true;
}

//接收：玩家领奖
bool CShengLingProtS::OnRecv_TakePrize(
        EGridType eGridType, //格子类型(小游戏）
        UINT8 byIndex, //三消中第几个奖励(其他忽略此参数）
        shared_func<STakePrizeAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    { 
        fnAck->eResult = EShengLingResultError;
        return false;                       
    }
    CShengLingPtr pShengLing = pPlayer->GetShengLing();
    if(pShengLing)
        fnAck->eResult = pShengLing->OnTakePrize(eGridType,byIndex,fnAck->byBit);
    return true;
}

//接收：三消中积分累计
bool CShengLingProtS::OnRecv_AddScore(
        UINT16 wScore, //积分
        UINT8 byStep, //减少步数
        UINT16 wPassword, //密码
        shared_func<SAddScoreAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    { 
        fnAck->eResult = EShengLingResultError;
        return false;                       
    }
    CShengLingPtr pShengLing = pPlayer->GetShengLing();
    if(pShengLing)
        fnAck->eResult = pShengLing->AddScore(wScore,byStep,wPassword,fnAck->wNextPwd,fnAck->byTotalStep,fnAck->wTotalScore);
    return true;
}
//接收：玩家完成或者放弃小游戏
bool CShengLingProtS::OnRecv_FinishTrapGrid(
        shared_func<SFinishTrapGridAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    { 
        fnAck->eResult = EShengLingResultError;
        return false;                       
    }
    CShengLingPtr pShengLing = pPlayer->GetShengLing();
    if(pShengLing)
        fnAck->eResult = pShengLing->OnFinishTrap();
    return true;
}
//接收：玩家离开圣陵
void CShengLingProtS::OnRecv_Leave(
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    { 
        return;                       
    }
    CShengLingPtr pShengLing = pPlayer->GetShengLing();
    if(pShengLing)
        pShengLing->OnLeave();
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

