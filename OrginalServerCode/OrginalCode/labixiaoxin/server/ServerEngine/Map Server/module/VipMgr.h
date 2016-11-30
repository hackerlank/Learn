#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include "..\..\GameBase\res\VipRes.h"

class VipMgr : public BaseModule
{
public:
	VipMgr();
	~VipMgr();

	void init(ACE_UINT32 unRechargeCount, ACE_UINT32 unRechargeAmount,const VipInfo & vipInfo,const VipGift & vipGift);
	virtual void update(ACE_UINT32 unCurrentTime);

	void recharge(int amount, bool addCount);

	ACE_UINT32 m_unRechargeCount;
	ACE_UINT32 m_unRechargeAmount;
	VipRes *m_currentVipRes;

	ACE_UINT32 m_unVipLevel;
	
	//new 
	VipInfo m_vipInfo;
	VipGift m_vipGift;
	double GetVipGold_profit();
	ACE_UINT32 GetVipGolden_profit();
	
	void UpdateVipRes(const VipInfo & vipInfo);
	bool isEnergyCountIn(ACE_UINT32 unCount);//是否在购买体力次数范围内
	int GetResetlevellimit();//关卡重置次数
	int GetResetDngeonLimit();//副本重置次数

	/*
		unvipLevel 对应于 ungiftId
		unvipLevel 必须比当前vip等级<=
	*/
	int GetVipGift(ACE_UINT32 ungiftId,ACE_UINT32 unvipLevel,RewardInfo & reward);//获取vip礼包 Vip礼包ID,关联behavior表
private:
	VipRes *m_vipRes;
	void UpdateVipRes(bool isUpdateDb = false);

	void update_2_db();

	void Update_2_Gift_db();

	void set_vip_level(bool isInit);

	static bool m_bInitData;
	static void init_vip_data();
	bool HasVipGift(ACE_UINT32 ungiftId);//是否已经拿了礼包
};