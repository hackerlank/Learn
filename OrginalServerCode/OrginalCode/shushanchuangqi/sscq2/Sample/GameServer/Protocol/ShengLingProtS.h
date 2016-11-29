
#pragma once
#include "ShengLingProtSvr.h"

using namespace NShengLingProt;

class CShengLingProtS : public CShengLingProtSvr
{
public:	
	//接收：玩家打开活动面板
	virtual bool OnRecv_OnOpen(
		shared_func<SOnOpenAck>& fnAck //返回回调函数
	);
	
    //接收：玩家进入圣陵
	virtual bool OnRecv_OnEnter(
		shared_func<SOnEnterAck>& fnAck //返回回调函数
	);

	//接收：玩家摇骰子
	virtual bool OnRecv_DrawDice(
		shared_func<SDrawDiceAck>& fnAck //返回回调函数
	);
	
    //接收：使用卡片
	virtual bool OnRecv_UseCard(
		ECardType eCardType, //卡片类型
		UINT8 byIndex, //骰子数(转向时byIndex=0)
		shared_func<SUseCardAck>& fnAck //返回回调函数
	);
    
    //接收：购买
	virtual bool OnRecv_Buy(
		EBuyType eBuyType, //购买类型
		UINT8 byNum, //购买次数
		shared_func<SBuyAck>& fnAck //返回回调函数
	);

	//接收：玩家领奖
	virtual bool OnRecv_TakePrize(
		EGridType eGridType, //格子类型(小游戏）
		UINT8 byIndex, //三消中第几个奖励(其他忽略此参数）
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	);
	
	//接收：三消中积分累计
	virtual bool OnRecv_AddScore(
		UINT16 wScore, //积分
		UINT8 byStep, //减少步数
		UINT16 wPassword, //密码
		shared_func<SAddScoreAck>& fnAck //返回回调函数
	);
	//接收：玩家完成或者放弃小游戏
	virtual bool OnRecv_FinishTrapGrid(
		shared_func<SFinishTrapGridAck>& fnAck //返回回调函数
	);
	
    //接收：玩家离开圣陵
	virtual void OnRecv_Leave(
	);
private:
};

extern CShengLingProtS g_ShengLingProtS;
