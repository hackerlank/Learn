#include "ItemResMgr.h"
#include "ace\OS_NS_string.h"

#include "MonsterRes.h"
#include "DropRes.h"
#include "EquipmentRes.h"
#include "MapRes.h"
#include "PlayerRes.h"
#include "SkillRes.h"
#include "LuckRes.h"
#include "ImproveRes.h"
#include "StageRes.h"
#include "FunctionRes.h"
#include "VipRes.h"
#include "UnlockRes.h"
#include "BenifitRes.h"
#include "GiftRes.h"
#include "MallRes.h"
#include "ActivityRes.h"
#include "BehaviorRes.h"
#include "FormulaRes.h"
#include "MaterialRes.h"
#include "BasicPropertyRes.h"
#include "GrowingRes.h"
#include "ExtraSkillRes.h"
#include "PVPRewardRes.h"
#include "MoneyTreeRes.h"
#include "MapGroupRes.h"
#include "DropCurrencyRes.h"
#include "DropMaterialRes.h"

#include "..\..\GameBase\Common\GameDefine.h"
#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif
#include "ChannelRes.h"
#include "BuyEnergyCost.h"
#include "PieceRoleRes.h"
#include "RechargeRes.h"
#include "BadgeRes.h"
#include "PropsRes.h"

ItemResMgr::ItemResMgr()
{

}

ItemResMgr::~ItemResMgr()
{

}

int ItemResMgr::load_all_config()
{
	if(this->load_config(CONFIG_TYPE_MONSTER, "config/monster.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_DROP, "config/drop.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_EQUIPMENT, "config/equipment.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_PROPS, "config/items.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_MAP, "config/map.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_PLAYER, "config/character.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_SKILL, "config/skill.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_LUCK, "config/reward.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_IMPROVE, "config/improve.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_STAGE, "config/stage.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_FUNCTION, "config/function.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_VIP, "config/vip.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_UNLOCK, "config/unlock.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_BENIFIT, "config/benefit.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_GIFT, "config/gift.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_ACTIVITY, "config/activity.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_MALL, "config/mall.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_BEHAVIOR, "config/behavior.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_FORMULA, "config/formula.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_MATERIAL, "config/material.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_BASIC_PROPERTY, "config/basic.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_GROWING, "config/growing.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_EXTRA_SKILL, "config/extraskill.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_PVP_REWARD, "config/pvpreward.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_MAP_GROUP, "config/mapGroup.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_MONEY_TREE, "config/trees.xml") == -1)
	{
		return -1;
	}

	if (this->load_config(CONFIG_TYPE_DROP_CURRENCY, "config/dropcurrency.xml") == -1)//xxj 2015/04/17  14:26:01 货币类型 
	{
		return -1;
	}

	if (this->load_config(CONFIG_TYPE_DROP_MATERIAL, "config/dropmaterial.xml") == -1)//xxj 2015/04/20  19:50:13 掉落物品类型 
	{
		return -1;
	}
	if(this->load_config(CONFIG_TYPE_PIECE_ROLE_COST,"config/pieceRole.xml") == -1)//碎片转角色
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_RECHARGE,"config/recharge.xml") == -1)//充值
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_BADGE,"config/badge.xml") == -1)//徽章
	{
		return -1;
	}

	return 0;
}

int ItemResMgr::deal_config(int config_id, xmlNodePtr rootNode)
{
	int nType = -1;
	switch(config_id)
	{
	case CONFIG_TYPE_MONSTER:
		nType = ITEM_RES_TYPE_MONSTER;
		break;
	case CONFIG_TYPE_DROP:
		nType = ITEM_RES_TYPE_DROP;
		break;
	case CONFIG_TYPE_EQUIPMENT:
		nType = ITEM_RES_TYPE_EQUIPMENT;
		break;
	case CONFIG_TYPE_MAP:
		nType = ITEM_RES_TYPE_MAP;
		break;
	case CONFIG_TYPE_PLAYER:
		nType = ITEM_RES_TYPE_PLAYER;
		break;
	case CONFIG_TYPE_SKILL:
		nType = ITEM_RES_TYPE_SKILL;
		break;
	case CONFIG_TYPE_LUCK:
		nType = ITEM_RES_TYPE_LUCK;
		break;
	case CONFIG_TYPE_IMPROVE:
		nType = ITEM_RES_TYPE_IMPROVE;
		break;
	case CONFIG_TYPE_STAGE:
		nType = ITEM_RES_TYPE_STAGE;
		break;
	case CONFIG_TYPE_FUNCTION:
		nType = ITEM_RES_TYPE_FUNCTION;
		break;
	case CONFIG_TYPE_VIP:
		nType = ITEM_RES_TYPE_VIP;
		break;
	case CONFIG_TYPE_UNLOCK:
		nType = ITEM_RES_TYPE_UNLOCK;
		break;
	case CONFIG_TYPE_BENIFIT:
		nType = ITEM_RES_TYPE_BENIFIT;
		break;
	case CONFIG_TYPE_GIFT:
		nType = ITEM_RES_TYPE_GIFT;
		break;
	case CONFIG_TYPE_MALL:
		nType = ITEM_RES_TYPE_MALL;
		break;
	case CONFIG_TYPE_ACTIVITY:
		nType = ITEM_RES_TYPE_ACTIVITY;
		break;
	case CONFIG_TYPE_BEHAVIOR:
		nType = ITEM_RES_TYPE_BEHAVIOR;
		break;
	case CONFIG_TYPE_FORMULA:
		nType = ITEM_RES_TYPE_FORMULA;
		break;
	case CONFIG_TYPE_MATERIAL:
		nType = ITEM_RES_TYPE_MATERIAL;
		break;
	case CONFIG_TYPE_BASIC_PROPERTY:
		nType = ITEM_RES_TYPE_BASIC_PROPERTY;
		break;
	case CONFIG_TYPE_GROWING:
		nType = ITEM_RES_TYPE_GROWING;
		break;
	case CONFIG_TYPE_EXTRA_SKILL:
		nType = ITEM_RES_TYPE_EXTRA_SKILL;
		break;
	case CONFIG_TYPE_PVP_REWARD:
		nType = ITEM_RES_TYPE_PVP_REWARD;
		break;
	case CONFIG_TYPE_MONEY_TREE:
		nType = ITEM_RES_TYPE_MONEY_TREE;
		break;
	case CONFIG_TYPE_MAP_GROUP:
		nType = ITEM_RES_TYPE_MAP_GROUP;
		break;
	case CONFIG_TYPE_DROP_CURRENCY://xxj 2015/04/17  14:23:13 掉落货币
		nType = ITEM_RES_TYPE_DROP_CURRENCY;
		break;
	case CONFIG_TYPE_DROP_MATERIAL://xxj 2015/04/20  19:50:47 掉落物品
		nType = ITEM_RES_TYPE_DROP_MATERIAL;
		break;
	case CONFIG_TYPE_PIECE_ROLE_COST:
		nType = ITEM_RES_TYPE_PIECE_ROLE_COST;
		break;
	case CONFIG_TYPE_RECHARGE://充值
		nType = ITEM_RES_TYPE_RECHARGE;
		break;
	case CONFIG_TYPE_BADGE:
		nType = ITEM_RES_TYPE_BADGE;
		break;
	case CONFIG_TYPE_PROPS:
		nType = ITEM_RES_TYPE_PROPS;
		break;
	}

	if(nType == -1)
	{
		return -1;
	}

	xmlNodePtr childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"MaxId") == 0)
		{
			childNode = childNode->next;
			continue;
		}

		if(parse_item_res_list(childNode, nType) == -1)
		{
			return -1;
		}
		childNode = childNode->next;
	}

	return 0;
}


int ItemResMgr::parse_item_res_list(xmlNodePtr node, int nResType)
{
	BaseRes *pRes = NULL;

	switch(nResType)
	{
	case ITEM_RES_TYPE_MONSTER:
		pRes = new MonsterRes(nResType);
		break;
	case ITEM_RES_TYPE_DROP:
		pRes = new DropRes(nResType);
		break;
	case ITEM_RES_TYPE_EQUIPMENT:
		pRes = new EquipmentRes(nResType);
		break;
	case ITEM_RES_TYPE_MAP:
		pRes = new MapRes(nResType);
		break;
	case ITEM_RES_TYPE_PLAYER:
		pRes = new PlayerRes(nResType);
		break;
	case ITEM_RES_TYPE_SKILL:
		pRes = new SkillRes(nResType);
		break;
	case ITEM_RES_TYPE_LUCK:
		pRes = new LuckRes(nResType);
		break;
	case ITEM_RES_TYPE_IMPROVE:
		pRes = new ImproveRes(nResType);
		break;
	case ITEM_RES_TYPE_STAGE:
		pRes = new StageRes(nResType);
		break;
	case ITEM_RES_TYPE_FUNCTION:
		pRes = new FunctionRes(nResType);
		break;
	case ITEM_RES_TYPE_VIP:
		pRes = new VipRes(nResType);
		break;
	case ITEM_RES_TYPE_UNLOCK:
		pRes = new UnlockRes(nResType);
		break;
	case ITEM_RES_TYPE_BENIFIT:
		pRes = new BenifitRes(nResType);
		break;
	case ITEM_RES_TYPE_GIFT:
		pRes = new GiftRes(nResType);
		break;
	case ITEM_RES_TYPE_MALL:
		pRes = new MallRes(nResType);
		break;
	case ITEM_RES_TYPE_ACTIVITY:
		pRes = new ActivityRes(nResType);
		break;
	case ITEM_RES_TYPE_BEHAVIOR:
		pRes = new BehaviorRes(nResType);
		break;
	case ITEM_RES_TYPE_FORMULA:
		pRes = new FormulaRes(nResType);
		break;
	case ITEM_RES_TYPE_MATERIAL:
		pRes = new MaterialRes(nResType);
		break;
	case ITEM_RES_TYPE_BASIC_PROPERTY:
		pRes = new BasicPropertyRes(nResType);
		break;
	case ITEM_RES_TYPE_GROWING:
		pRes = new GrowingRes(nResType);
		break;
	case ITEM_RES_TYPE_EXTRA_SKILL:
		pRes = new ExtraSkillRes(nResType);
		break;
	case ITEM_RES_TYPE_PVP_REWARD:
		pRes = new PVPRewardRes(nResType);
		break;
	case ITEM_RES_TYPE_MONEY_TREE:
		pRes = new MoneyTreeRes(nResType);
		break;
	case ITEM_RES_TYPE_MAP_GROUP:
		pRes = new MapGroupRes(nResType);
		break;
	case ITEM_RES_TYPE_DROP_CURRENCY://xxj 2015/04/17  14:31:34 货币类型
		pRes = new CDropCurrencyRes(nResType);
		break;
	case ITEM_RES_TYPE_DROP_MATERIAL://xxj 2015/04/17  14:31:34 掉落物品类型
		pRes = new CDropMaterialRes(nResType);
		break;
	case ITEM_RES_TYPE_PIECE_ROLE_COST://碎片转角色
		pRes = new PieceRoleRes(nResType);
		break;
	case ITEM_RES_TYPE_RECHARGE://充值
		pRes = new RechargeRes(nResType);
		break;
	case ITEM_RES_TYPE_BADGE:
		pRes = new BadgeRes(nResType);
		break;
	case ITEM_RES_TYPE_PROPS:
		pRes = new PropsRes(nResType);
		break;
	}

	if(pRes == NULL)
	{
		return -1;
	}

	if(pRes->init(node) == -1)
	{
		delete pRes;
		return -1;
	}

	if(m_ItemResMap.bind(pRes->m_unResID, pRes) != 0)
	{
		delete pRes;
		//return -1;
		return 1;
	}

	return 0;
}

BaseRes *ItemResMgr::get_item_res(int unID)
{
	BaseRes *p = NULL;

	//unID = GET_RES_BASIC_ID(unID);

	if(m_ItemResMap.find(unID, p) == 0)
	{
		return p;
	}

	return NULL;
}

int ItemResMgr::get_item_id_list_by_type(ACE_UINT32 unType, ACE_UINT32 unSubInfo, int nInfoStart, int nInfoLen, ACE_UINT32 *destList, ACE_UINT32 unMask)
{
	int c = 0;

	ITEM_RES_MAP_ITERATOR iter(m_ItemResMap);
	BaseRes *res;
	ACE_UINT32 t;
	for(iter = m_ItemResMap.begin(); iter != m_ItemResMap.end(); iter++)
	{
		res = (*iter).int_id_;

		t = GET_ITEM_TYPE(res->m_unResID);

		if(t != unType)
		{
			continue;
		}

		if(unSubInfo != 0)
		{
			//t = GET_ITEM_SUB_TYPE(res->m_unResID);
			t = GET_ITEM_ID_INFO(res->m_unResID, nInfoStart, nInfoLen);
			if(t != unSubInfo)
			{
				continue;
			}
		}

		//t = (res->m_unResID / unMask) * unMask;
		t = GET_ITEM_MASK_ID(res->m_unResID,unMask);

		int j;

		for(j = 0;j < c;j ++)
		{
			if(destList[j] == t)
			{
				break;
			}
		}

		if(j >= c)
		{
			destList[c] = t;
			c ++;
		}
	}

	return c;
}