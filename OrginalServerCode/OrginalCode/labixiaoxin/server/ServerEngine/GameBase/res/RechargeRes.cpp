#include "RechargeRes.h"
#include "RewardRes.h"

RechargeRes::RechargeRes( ACE_UINT32 unType )
:BaseRes(unType)
{
	//m_price = 0;//需要支付的实际货币值
	//m_buy_card = 0;//金卡的购买数量
	ZeroVar(m_reward);
	m_gift_card = 0;//金卡的赠送数量
	m_unSubType = 0;//是否为月卡
}

RechargeRes::~RechargeRes()
{

}

int RechargeRes::parse_xml_node( xmlNodePtr node )
{
	BaseRes::parse_xml_node(node);

// 	if(xmlStrcasecmp(node->name, BAD_CAST"price") == 0)//xxj 2015/04/23 20:57:11  加人名字
// 	{
// 		m_price = ACE_OS::atoi((char *)xmlNodeGetContent(node));
// 	}
// 	if(xmlStrcasecmp(node->name, BAD_CAST"buy_card") == 0)
// 	{
// 		m_buy_card = ACE_OS::atoi((char *)xmlNodeGetContent(node));
// 	}
	if(xmlStrcasecmp(node->name, BAD_CAST"commodity") == 0)
	{
		RewardRes::parse_reward_list(m_reward, (char *)xmlNodeGetContent(node));
	}
	else if (xmlStrcasecmp(node->name, BAD_CAST"gift_card") == 0)
	{
		m_gift_card = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
// 	else if(xmlStrcasecmp(node->name, BAD_CAST"type") == 0)//xxj 2015/04/23 20:57:11  加人名字
// 	{
// 		m_type = ACE_OS::atoi((char *)xmlNodeGetContent(node));
// 	}
	return 0;
}
