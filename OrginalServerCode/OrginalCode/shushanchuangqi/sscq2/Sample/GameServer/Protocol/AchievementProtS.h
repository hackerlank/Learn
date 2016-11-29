
#pragma once
#include "AchievementProtSvr.h"

using namespace NAchievementProt;

class CAchievementProtS : public CAchievementProtSvr
{
public:
	//接收：获取成就信息
	virtual bool OnRecv_GeAchievementInfo(
		shared_func<SGeAchievementInfoAck>& fnAck //返回回调函数
	);
	//接收：获取成就奖励
	virtual bool OnRecv_TakePrize(
		UINT16 wAchievementID, //成就ID
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	);

	//接收：获取成就分享信息
	virtual bool OnRecv_GeAchievementShareList(
		shared_func<SGeAchievementShareListAck>& fnAck //返回回调函数
	);

	//接收：获取成就分享奖励
	virtual bool OnRecv_TakeSharePrize(
		UINT16 wAchievementID, //成就ID
		shared_func<STakeSharePrizeAck>& fnAck //返回回调函数
	);


private:
};

extern CAchievementProtS g_AchievementProtS;
