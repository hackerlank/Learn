#pragma once
#include "Game2CenterTeamSvr.h"
#include "stdafx.h"
using namespace NGame2CenterTeam;


class CGame2CenterTeamS : public CGame2CenterTeamSvr
{
    public:
    //接收：同步队伍成员
	virtual void OnRecv_SynTeamFighter(
		UINT64 qwUsrID, //帐号ID
		const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
	);
	//接收：同步增加阵灵,如果原来有阵灵，替换
	virtual void OnRecv_SynTeamAddBeauty(
		UINT64 qwUsrID, //帐号ID
		const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
	) ;
	//接收：同步删除阵灵
	virtual void OnRecv_SynTeamDelBeauty(
		UINT64 qwUsrID //帐号ID
	) ;
	//接收：同步奖励系数
	virtual void OnRecv_SynRewardRate(
		UINT32 dwRewardRate //奖励系数万分比
	);

};

extern CGame2CenterTeamS g_Game2CenterTeamS;

