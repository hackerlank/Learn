#pragma once
#include "AnswerProtSvr.h"

using namespace NAnswerProt;

class CAnswerProtS : public CAnswerProtSvr
{
public:	
	//接收：玩家答题
	bool OnRecv_Answer(
		UINT8 byAnswerID, //玩家选择答案
		shared_func<SAnswerAck>& fnAck //返回回调函数
	);
	//接收：玩家使用技能
	bool OnRecv_UseSkill(
		EAnswerSkill eSkillType, //技能ID
		shared_func<SUseSkillAck>& fnAck //返回回调函数
	);

    //接收：玩家报名
	virtual void OnRecv_Join(
	);

	//接收：玩家离开
	virtual void OnRecv_Leave(
	);

	//接收：获取活动开始倒计时
	virtual bool OnRecv_GetCoutdown(
		shared_func<SGetCoutdownAck>& fnAck //返回回调函数
	);
private:
};

extern CAnswerProtS g_AnswerProtS;
