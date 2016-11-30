#pragma once

#include "..\..\GameBase\Common\GameDefine.h"

//extern int gPlayerProperyCurveInfo[];
//extern int gMonsterProperyCurveInfo[][PROPERTY_ID_MAX];

//extern void reset_property_component(PropertyComponent &component);
//extern void add_property_component(PropertyComponent &dest, ACE_UINT32 unBattlePropertyID, PropertyComponent *singleList, PropertyComponent *allList);

//extern void init_monster_property_list(int type, int lv, PropertyComponent *list);

typedef struct tagCombatSkill
{

}CombatSkill;

typedef struct tagCombatUnit
{
	ACE_UINT32 unUnitID;
	int original_property[PLAYER_PROPERTY_MAX];
	//int real_property[PLAYER_PROPERTY_MAX];
	//int property_range[PLAYER_PROPERTY_MAX][2];
	ACE_UINT32 unSkillID;
	ACE_UINT32 unPlayerSkillID;
}CombatUnit;

class TeamProperty
{
public:
	TeamProperty();
	~TeamProperty();

	void init(PlayerTeamInfo *teamInfo); 

	CombatUnit m_unitList[MAX_PLAYER_SELECTED_COUNT];
	
	static PropertyComponent get_coin_property(PlayerTeamInfo *teamInfo);

	void build_property();
	void build_property(ACE_UINT32 unPower);

private:
	PlayerTeamInfo *m_teamInfo;

	static void add_player_property(PropertyComponent *componentList, PlayerInfo *player);
	static void add_equipment_property(PropertyComponent *componentList, ItemInfo *equipment);
};