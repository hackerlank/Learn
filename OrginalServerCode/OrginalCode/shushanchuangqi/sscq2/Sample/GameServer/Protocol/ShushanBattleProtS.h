
#pragma once
#include "ShushanBattleProtSvr.h"

using namespace NShushanBattleProt;
using namespace NProtoCommon;

class CShushanBattleProtS : public CShushanBattleProtSvr
{
public:
    //接收：蜀山论剑准备/开始/结束信息
    virtual void OnRecv_GetBattleStartInfo(
    );

	//接收：请求蜀山论剑玩家的配对信息
	virtual void OnRecv_GetPlayerPairInfo(
	);

    //接收：请求连杀王、荣誉王信息
    virtual void OnRecv_GetFirstPlayer(
    );

	//接收：参加蜀山论剑活动
	virtual bool OnRecv_PlayerEnter(
		shared_func<SPlayerEnterAck>& fnAck //返回回调函数
	);

	//接收：退出蜀山论剑活动
	virtual bool OnRecv_PlayerLeave(
		shared_func<SPlayerLeaveAck>& fnAck //返回回调函数
	);

	//接收：使用蜀山论剑技能
	virtual bool OnRecv_UseSkill(
		UINT8 bySkillID, //技能ID
		shared_func<SUseSkillAck>& fnAck //返回回调函数
	);

	//接收：购买蜀山论剑霸气or怒气
	virtual bool OnRecv_BuySkill(
		UINT8 byFlag, //购买类型:0霸气 1怒气
		shared_func<SBuySkillAck>& fnAck //返回回调函数
	);

private:
};
