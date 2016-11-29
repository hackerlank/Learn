
#pragma once
#include "HorseSvr.h"

using namespace NHorse;

//协议类：锁妖塔
class CHorseSvrS : public CHorseSvr
{
public:
	//接收：获取坐骑列表
	virtual void OnRecv_GetHorseList(
	);

	//接收：激活坐骑
	virtual bool OnRecv_ActiveHorse(
		UINT32 dwHorseID, //坐骑ID
		shared_func<SActiveHorseAck>& fnAck //返回回调函数
	);
    	
    //接收：坐骑进阶
	virtual bool OnRecv_UpgradeHorse(
        UINT32 dwHorseID, //坐骑ID
		bool bAll, //是否一键进阶
		shared_func<SUpgradeHorseAck>& fnAck //返回回调函数
	);

	//接收：骑乘状态修改
	virtual bool OnRecv_SetHorseStatus(
        UINT32 dwHorseID, //坐骑ID
		UINT32 eHorseStatus, //骑乘状态
		shared_func<SSetHorseStatusAck>& fnAck //返回回调函数
	);


	//接收：获取坐骑属性
	virtual bool OnRecv_GetHorseAttr(
        UINT32 dwHorseID, //坐骑ID
		shared_func<SGetHorseAttrAck>& fnAck //返回回调函数
	);


	//接收：解锁技能属性
	virtual bool OnRecv_UnLockHorseSkillAttr(
		UINT32 dwHorseID, //坐骑ID
		UINT32 dwPos, //第几个技能属性 1开始
		shared_func<SUnLockHorseSkillAttrAck>& fnAck //返回回调函数
	);


};

extern CHorseSvrS g_HorseSvrS;
