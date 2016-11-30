#ifndef __RECHARGERES_H_
#define __RECHARGERES_H_
#include "BaseRes.h"

#define RechargeRes_type_general 1//普通充值
#define RechargeRes_type_monthcard 2//月卡
#define RechargeRes_type_LIMITED_ACTIVITY 3//限时活动

class RechargeRes : public BaseRes
{
public:
	RechargeRes(ACE_UINT32 unType);
	virtual ~RechargeRes();

	virtual int parse_xml_node(xmlNodePtr node);
	
	//ACE_UINT32 m_unPrice;//需要支付的实际货币值
	//ACE_UINT32 m_buy_card;//金卡的购买数量
	ConfigReward m_reward;
	ACE_UINT32 m_gift_card;//金卡的赠送数量
	//ACE_UINT32 m_is_monthcard;//是否为月卡
	//ACE_UINT32 m_type;//"类型【1】：普通充值【2】：月卡【3】：限时活动" m_unSubType

};

#endif