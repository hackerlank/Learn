#pragma once

#include "BaseRes.h"

#define VIP_HEAD 0x05000000

class VipRes : public BaseRes
{
public:
	VipRes(ACE_UINT32 unType);
	virtual ~VipRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	ACE_UINT32 m_unVipLevel;//vip等级
	ACE_UINT32 m_unRechargeRequired;//充值额度
	ACE_UINT32 m_unGift_id;//Vip礼包ID,关联behavior表
	ACE_UINT32 m_gold_profit;//闯关贝壳收益(百分比)
	ACE_UINT32 m_package_limit;//背包上限数量
	ACE_UINT32 m_friends_limit;//好友上限数量
	ACE_UINT32 m_energy_limit;//体力上限数量
	ACE_UINT32 m_buyenergy_limit;//购买体力上限数
	ACE_UINT32 m_reset_level_limit;//关卡重置次数
	ACE_UINT32 m_reset_dngeon_limit;//副本重置次数
	ACE_UINT32 m_golden_profit;//点金手暴击收益百分比
	ACE_UINT32 m_buy_gold_limit;//贝壳购买次数
	ACE_UINT32 m_buy_pvp_limit;//pvp购买次数
	
	//老数据 保留
public:
	ACE_UINT32 m_unBenefitCount;
	ACE_UINT32 m_benifitList[MAX_VIP_BENIFIT_COUNT];
private:
	int parse_benifit_list(ACE_UINT32 list[], char *str);
};