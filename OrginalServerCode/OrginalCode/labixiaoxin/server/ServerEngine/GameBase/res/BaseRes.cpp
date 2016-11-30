#include "BaseRes.h"
#include "ItemResMgr.h"

BaseRes::BaseRes(ACE_UINT32 unType)
{
	m_unType = unType;
	m_unSubType = 0;
	m_unTime = 0;
	m_unResID = 0;

	m_nLevelRequired = 1;
	m_nVipLevelRequired = 0;
	m_nCoinPrice = -1;
	m_nMoneyPrice = -1;
	m_nSoldPrice = -1;
	//m_unPropertyCount = 0;
	m_unPrice = 0;
	m_unResFlag = 0;

	m_unQuality = 1;

	m_unPackageIndex = 0;

	m_unFormulaID = 0;

	m_unBuyCost = (ACE_UINT32)-1;
	m_bCanUse = true;

	ACE_OS::memset(&m_cdInfo, 0, sizeof(CooldownInfo));
	ACE_OS::memset(&m_strName, 0, sizeof(m_strName));
}

BaseRes::~BaseRes()
{

}

ACE_UINT32 BaseRes::handbook_ID()
{
	return handbook_ID(m_unResID);
}

ACE_UINT32 BaseRes::handbook_ID(ACE_UINT32 unID)
{
	ACE_UINT32 ret = unID + (ITEM_RES_TYPE_HANDBOOK_OFFSET << 24);

	return ret;
}

bool BaseRes::has_cooldown()
{
	if(m_cdInfo.unCD == 0)
	{
		return false;
	}

	return true;
}

int BaseRes::init(xmlNodePtr rootNode)
{
	int nRet = 0;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"id") == 0)
		{
			//m_unResID = generate_id(ACE_OS::atoi((char *)xmlNodeGetContent(childNode)));
			//m_unResID = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			//m_unResID = ACE_OS::strtol((char *)xmlNodeGetContent(childNode), NULL, 16);
			m_unResID = GameUtils::parse_res_id((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"type") == 0)
		{
			m_unSubType = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"time") == 0)
		{
			m_unTime = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"coin_price") == 0)
		{
			m_nCoinPrice = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"money_price") == 0)
		{
			m_nMoneyPrice = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"sold_price") == 0)
		{
			m_nSoldPrice = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"required_level") == 0)
		{
			m_nLevelRequired = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"vip_level_require") == 0)
		{
			m_nVipLevelRequired = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"res_flag") == 0)
		{
			m_unResFlag = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"property_list") == 0)
		{
			//parse_property_list(childNode);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"buy_cost") == 0)
		{
			m_unBuyCost = (ACE_UINT32)ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"is_use") == 0)
		{
			m_bCanUse = (bool)ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"price") == 0)
		{
			m_unPrice = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"cooldown") == 0)
		{
			GameUtils::parse_cooldown_info(m_cdInfo, (char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"quality") == 0)
		{
			m_unQuality = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"formula_id") == 0)
		{
			//m_unFormulaID = ACE_OS::strtol((char *)xmlNodeGetContent(childNode), NULL, 16);
			m_unFormulaID = GameUtils::parse_res_id((char *)xmlNodeGetContent(childNode));
		}

		else if(xmlStrcasecmp(childNode->name, BAD_CAST"shop") == 0)  //added by jinpan for secret shop
		{
			GameUtils::parse_cost_list(m_shop, (char *)xmlNodeGetContent(childNode));
		}
		else
		{
			if(parse_xml_node(childNode) == -1)
			{
				nRet = -1;
				break;
			}
		}

		childNode = childNode->next;
	}

	return nRet;
}

/*
ACE_UINT32 BaseRes::generate_id(ACE_UINT32 unID)
{
	return SET_RES_TYPE(m_unType,unID);
}
*/

/*
void BaseRes::parse_property_list(xmlNodePtr rootNode)
{
	xmlNodePtr childNode = rootNode->xmlChildrenNode;
	xmlNodePtr subNode;

	int c = 0;

	while(childNode != NULL)
	{
		subNode = childNode->xmlChildrenNode;
		while(subNode != NULL)
		{
			if(xmlStrcasecmp(subNode->name, BAD_CAST"property") == 0)
			{
				m_propertyList[c].unPropertyID = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"value_type") == 0)
			{
				m_propertyList[c].unValueType = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"value") == 0)
			{
				m_propertyList[c].nValue = (float)ACE_OS::atof((char *)xmlNodeGetContent(subNode));
			}

			subNode = subNode->next;
		}

		c ++;
		
		childNode = childNode->next;
	}

	m_unPropertyCount = (ACE_UINT32)c;
}
*/
