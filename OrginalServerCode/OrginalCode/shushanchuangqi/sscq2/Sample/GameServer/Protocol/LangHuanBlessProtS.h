
#pragma once
#include "LangHuanBlessProtSvr.h"

using namespace NLangHuanBlessProt;

class CLangHuanBlessProtS : public CLangHuanBlessProtSvr
{
public:	
    //接收：进入LangHuanBless地图
	virtual bool OnRecv_EnterMap(
		shared_func<SEnterMapAck>& fnAck //返回回调函数
	);
    //接收：选择问道
	virtual bool OnRecv_SelectSkill(
		UINT64 qwPlayerID, //被选择的玩家
		ELHBSkillType eLHBSkillType, //技能类型
		shared_func<SSelectSkillAck>& fnAck //返回回调函数
	);
   //接收：获得的修为值
	virtual bool OnRecv_GetScore(
		shared_func<SGetScoreAck>& fnAck //返回回调函数
	);
    //接收：离开boss地图
	virtual bool OnRecv_LeaveMap(
		shared_func<SLeaveMapAck>& fnAck //返回回调函数
	);
    //接收：获得技能使用信息
	virtual bool OnRecv_GetSkillInfo(
		shared_func<SGetSkillInfoAck>& fnAck //返回回调函数
	);
    //接收：获得游戏中持续时间
	virtual bool OnRecv_GetSustainTime(
		shared_func<SGetSustainTimeAck>& fnAck //返回回调函数
	);
	//接收：获得玩家所有信息
	virtual bool OnRecv_GetTotalInfo(
		shared_func<SGetTotalInfoAck>& fnAck //返回回调函数
	);

    void SendSysMsg(ELHBResult eLHBResult);

private:
};

extern CLangHuanBlessProtS g_LangHuanBlessProtS;
