#pragma once

#include "FightFormationSvr.h"

#include "stdafx.h"

using namespace NFightFormation;

class CFightFormationS : public CFightFormationSvr
{
public:

	//接收：取得阵形信息
	virtual bool OnRecv_GetFightFormation(
		UINT16 wBattleType, //战斗类型
		shared_func<SGetFightFormationAck>& fnAck //返回回调函数
	);

	//接收：设置阵形信息
	virtual bool OnRecv_SetFightFormation(
		UINT16 wBattleType, //战斗类型
		const FightFormationInfo& oFightFormation, //阵形ID
		shared_func<SSetFightFormationAck>& fnAck //返回回调函数
	);

	//接收：战斗散仙信息
	virtual bool OnRecv_GetFightHeroInfo(
		UINT16 wBattleType, //战斗类型 EBattleType
		shared_func<SGetFightHeroInfoAck>& fnAck //返回回调函数
	);

};
extern CFightFormationS g_FightFormationS;
