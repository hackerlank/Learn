#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include "..\..\Base\Event\EventListener.h"
#include "TeamProperty.h"

#include "..\..\GameBase\res\PlayerRes.h"
#include "..\..\GameBase\res\ItemResMgr.h"

class PlayerMgr : public BaseModule, public EventListener
{
public:
	PlayerMgr();
	~PlayerMgr();

	void init(PlayerInfo *list, ACE_UINT32 *selectedList, ItemInfo *staff, ACE_UINT32 *selectPlayerSkillList, ACE_UINT32 unHighestPoint);
	int update_player(ACE_UINT32 *list, ACE_UINT32 *playerSkillList);

	virtual void handle_event(BaseEvent *e);

	//int select_player(int newIdx, int oldIdx);

	int add_player(ACE_UINT32 unItemID, ACE_UINT32 unNum,LogItemInfo & logInfo);
	int PieceToPlayer(ACE_UINT32 unItemID,/*CostInfoList & cost,*/ACE_UINT32 & playerID);//碎片转角色（如果此角色已经有了则不转换）

	int add_really_player(PlayerRes *temp,PlayerInfo *info);

	PlayerInfo *get_player_by_id(ACE_UINT32 unID);

	int level_up_equipment(ACE_UINT32 unPlayerID, ACE_UINT32 unEquipmentID, int dwLevelAdd);
	int level_up_player(ACE_UINT32 unPlayerID, int dwLevelAdd);
	int step_up_player(ACE_UINT32 unPlayerID);

	ItemInfo *get_equipment(ACE_UINT32 unPlayerID, ACE_UINT32 unEquipmentID);
	ItemInfo *get_equipment(PlayerInfo *info, ACE_UINT32 unEquipmentID);

	//static void sort(int count, PlayerInfo *list);

	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN);

	int get_selected_list(PlayerInfo *list); 

	int exchange_equipment(ACE_UINT32 unPlayerID, int packageIdx);
	int exchange_equipment(ACE_UINT32 unPlayerID1, ACE_UINT32 unPlayerID2, int equipment_type);
	//int exchange_player_skill(ACE_UINT32 unIndex, ACE_UINT32 unSkillID);

	ACE_UINT32 m_unPlayerCount;
	ACE_UINT32 m_unMaxSelected;
	PlayerInfo m_list[MAX_PLAYER_COUNT];
	ACE_UINT32 m_selectedList[MAX_PLAYER_SELECTED_COUNT];
	ACE_UINT32 m_playerSkillList[MAX_PLAYER_SELECTED_COUNT];
	ItemInfo m_staff;

	ACE_UINT32 m_unHighestPoint;

	void update_2_db();//更新到数据库

	bool set_player_skill(ACE_UINT32 *dest, ACE_UINT32 *list);
	//int levelup_extra_skill(ACE_UINT32 unExtralSkillID);
	//static bool can_player_skill_equip(ACE_UINT32 *list, int idx, ACE_UINT32 unNewID);

	PlayerTeamInfo m_teamInfo;
	TeamProperty m_teamProperty;
private:
	void update_pve_team();

public:
	void highest_team_info_2_db(ACE_UINT32 unType);
};