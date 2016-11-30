#include "TeamProperty.h"
#include "ace\ace.h"
#include "ace\OS_NS_string.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\..\GameBase\res\PlayerRes.h"
#include "..\..\GameBase\res\BasicPropertyRes.h"
#include "..\..\GameBase\res\GrowingRes.h"
#include "..\..\GameBase\res\EquipmentRes.h"

TeamProperty::TeamProperty()
{
	ACE_OS::memset(m_unitList, 0, sizeof(CombatUnit) * MAX_PLAYER_SELECTED_COUNT);
	//m_unUnitCount = 0;
	//m_unPoint = 0;
}

TeamProperty::~TeamProperty()
{
}

PropertyComponent TeamProperty::get_coin_property(PlayerTeamInfo *teamInfo)
{
	PropertyComponent list[PLAYER_PROPERTY_MAX];
	ACE_OS::memset(list, 0, sizeof(PropertyComponent) * PLAYER_PROPERTY_MAX);

	add_equipment_property(list, &teamInfo->staff);

	return list[PLAYER_PROPERTY_COIN];
}

void TeamProperty::init(PlayerTeamInfo *teamInfo)
{
	m_teamInfo = teamInfo;

	//build_property();
}

//³É³¤ÊôÐÔ
void TeamProperty::build_property()
{
	int i, j;

	PropertyComponent allList[PLAYER_PROPERTY_MAX];
	PropertyComponent singleList[PLAYER_PROPERTY_MAX];

	ACE_OS::memset(allList, 0, sizeof(PropertyComponent) * PLAYER_PROPERTY_MAX);

	//add_equipment_property(allList, &m_teamInfo->staff);

	int c = 0;
	m_teamInfo->unCount = 0;
	//m_teamInfo->unPoint = 0;

	for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
	{
		if(m_teamInfo->playerList[i].unItemID == 0)
		{
			break;
		}

		//build property

		ACE_OS::memset(singleList, 0, sizeof(PropertyComponent) * PLAYER_PROPERTY_MAX);

		add_player_property(singleList, &m_teamInfo->playerList[i]);

		m_unitList[i].unUnitID = m_teamInfo->playerList[i].unItemID;
		m_unitList[i].unSkillID = m_teamInfo->skillList[i];
		//m_unitList[i].unPlayerSkillID = m_teamInfo->playerList[i].unPlayerSkillID;
		m_unitList[i].unPlayerSkillID = m_teamInfo->playerSkillList[i];

		for(j = 0;j < PLAYER_PROPERTY_MAX;j ++)
		{
			m_unitList[i].original_property[j] = (int)((allList[j].unValue + singleList[j].unValue)+(allList[j].unScale + singleList[j].unScale));
		}

		int s = GET_ITEM_ID_INFO(m_unitList[i].unSkillID, 0, 2);
		//int tmp_point = ((10 + s) * m_unitList[i].original_property[PLAYER_PROPERTY_ATTACK] + 5 * m_unitList[i].original_property[PLAYER_PROPERTY_HP] + 4 * m_unitList[i].original_property[PLAYER_PROPERTY_DEFENSE] + 3 * m_unitList[i].original_property[PLAYER_PROPERTY_CRITICAL]) / 10;
		int tmp_point = (
			m_unitList[i].original_property[PLAYER_PROPERTY_ATTACK] * 5 + s * 30 * (1 + s * 7.0 / 60) +
			m_unitList[i].original_property[PLAYER_PROPERTY_HP] * 4 + 
			m_unitList[i].original_property[PLAYER_PROPERTY_DEFENSE] * 3 +
			m_unitList[i].original_property[PLAYER_PROPERTY_CRITICAL] * 3) 
			/ 10;

		//m_teamInfo->unPoint += tmp_point;

		c ++;
	}

	//m_teamInfo->unPoint;
	m_teamInfo->unCount = c;
}

void TeamProperty::build_property( ACE_UINT32 unPower )
{
	build_property();
	m_teamInfo->unPoint = unPower;
}

void TeamProperty::add_player_property(PropertyComponent *componentList, PlayerInfo *player)
{
	PlayerRes * playerRes = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(player->unItemID);

	if(playerRes == NULL)
	{
		return;
	}

	BasicPropertyRes *basicRes = (BasicPropertyRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(playerRes->m_unBasicPropertyID);
	GrowingRes *growingRes = (GrowingRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(playerRes->m_unGrowingID);

	if(basicRes == NULL || growingRes == NULL)
	{
		return;
	}

	add_equipment_property(componentList, &player->weapon);
	add_equipment_property(componentList, &player->armor);
	add_equipment_property(componentList, &player->belt);
	add_equipment_property(componentList, &player->staff);

	int i;
	for(i = 0;i < PLAYER_PROPERTY_MAX;i ++)
	{
		componentList[i].unValue += (basicRes->m_valueList[i] + growingRes->m_valueList[i] * (player->unLevel - 1));
	}
}

void TeamProperty::add_equipment_property(PropertyComponent *componentList, ItemInfo *equipment)
{
	EquipmentRes *res = (EquipmentRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(equipment->unResID);

	if(res == NULL)
	{
		return;
	}

	int i;

	for(i = 0;i < PLAYER_PROPERTY_MAX;i ++)
	{
		componentList[i].unValue += (res->m_propertyList[i].unValue + res->m_improvePropertyList[i].unValue * (equipment->info.equipment.unLevel - 1));
		componentList[i].unScale += (res->m_propertyList[i].unScale + res->m_improvePropertyList[i].unScale * (equipment->info.equipment.unLevel - 1));
	}
}

