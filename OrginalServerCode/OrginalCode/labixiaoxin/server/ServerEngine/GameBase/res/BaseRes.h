#pragma once

#include "ace\ace.h"
#include "ace\OS_NS_string.h"
#include "ace\OS_NS_stdlib.h"
#include "..\Common\GameUtils.h"

#include "libxml\parser.h"

#include "..\Common\GameDefine.h"

class BaseRes
{
public:
	BaseRes(ACE_UINT32 unType);
	virtual ~BaseRes();

	int init(xmlNodePtr rootNode);

	//static ACE_UINT32 parse_res_id(char *strID);

	virtual int parse_xml_node(xmlNodePtr node){return 0;};
	virtual void process_res_id_by_name(){};

	ACE_UINT32 m_unResID;
	ACE_UINT32 m_unType;
	ACE_UINT32 m_unSubType;
	ACE_UINT32 m_unTime;
	char m_strName[MAX_ITEM_NAME + 1];

	ACE_INT32 m_nLevelRequired;
	ACE_INT32 m_nVipLevelRequired;
	ACE_INT32 m_nCoinPrice;
	ACE_INT32 m_nMoneyPrice;
	ACE_INT32 m_nSoldPrice;

	ACE_UINT32 m_unPrice;

	ACE_UINT32 m_unQuality;

	ACE_UINT32 m_unResFlag;

	ACE_UINT32 m_unPackageIndex;

	CooldownInfo m_cdInfo;

	ACE_UINT32 m_unFormulaID;

	ACE_UINT32 m_unBuyCost;

	bool m_bCanUse;
	
	CostInfoList m_shop;//在神秘商店出售的价格

	ACE_UINT32 handbook_ID();
	static ACE_UINT32 handbook_ID(ACE_UINT32 unID);

	bool has_cooldown();//是否存在冷却时间

	//ACE_UINT32 m_unPropertyCount;
	//PropertyInfo m_propertyList[MAX_PROPERTY_PER_ITEM];
private:
	//ACE_UINT32 generate_id(ACE_UINT32 unID);
	//void parse_property_list(xmlNodePtr rootNode);
};

typedef BaseRes * PBaseRes;