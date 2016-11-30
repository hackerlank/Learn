#include "VipRes.h"
#include "ItemResMgr.h"
#include "GameConfig.h"

VipRes::VipRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	m_unVipLevel = 0;//vip等级
	m_unRechargeRequired = 0;//充值额度
	m_unGift_id = 0;//Vip礼包ID,关联behavior表
	m_gold_profit = 0;//闯关贝壳收益(百分比)
	m_package_limit = 0;//背包上限数量
	m_friends_limit = 0;//好友上限数量
	m_energy_limit = 0;//体力上限数量
	m_buyenergy_limit = 0;//购买体力上限数
	m_reset_level_limit = 0;//关卡重置次数
	m_reset_dngeon_limit = 0;//副本重置次数
	m_unBenefitCount = 0;
	m_golden_profit = 0;
	m_buy_gold_limit = 0;
	m_buy_pvp_limit = 0;
	ZeroVar(m_benifitList);
}

VipRes::~VipRes()
{

}

int VipRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"vip_level") == 0)
	{
		m_unVipLevel = ACE_OS::atoi((char *)xmlNodeGetContent(node));
		GAME_CONFIG_INSTANCE::instance()->m_vipGiftList[m_unVipLevel] = m_unResID; 
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"recharge_require") == 0)
	{
		m_unRechargeRequired = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"gift_id") == 0)
	{
		m_unGift_id = GameUtils::parse_res_id((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"gold_profit") == 0)
	{
		m_gold_profit = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"gold_profit") == 0)
	{
		m_gold_profit = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"package_limit") == 0)
	{
		m_package_limit = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"friends_limit") == 0)
	{
		m_friends_limit = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"energy_limit") == 0)
	{
		m_energy_limit = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"buyenergy_limit") == 0)
	{
		m_buyenergy_limit = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"reset_level_limit") == 0)
	{
		m_reset_level_limit = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"reset_dngeon_limit") == 0)
	{
		m_reset_dngeon_limit = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"golden_profit") == 0)
	{
		m_golden_profit = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"buy_gold_limit") == 0)
	{
		m_buy_gold_limit = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if (xmlStrcasecmp(node->name,BAD_CAST"buy_pvp_limit") == 0)
	{
		m_buy_pvp_limit = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}

	//else if(xmlStrcasecmp(node->name, BAD_CAST"vip_benefit") == 0)
	//{
	//	m_unBenefitCount = parse_benifit_list(m_benifitList, (char *)xmlNodeGetContent(node));
	//}

	return 0;
}

void VipRes::process_res_id_by_name()
{
}

int VipRes::parse_benifit_list(ACE_UINT32 list[], char *str)
{
	int c = 0;

	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		//list[c] = ACE_OS::atoi(tmp);
		//list[c] = ACE_OS::strtol(tmp, NULL, 16);
		list[c] = GameUtils::parse_res_id(tmp);

		c ++;
	}

	return c;
}