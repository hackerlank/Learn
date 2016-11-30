#pragma once

#include "ace\ace.h"
#include "ace\Singleton.h"
#include "..\..\Base\Event\EventListener.h"
#include "..\..\Base\Communication\StreamRW.h"
#include "..\..\GameBase\res\StageRes.h"

/*
typedef struct tagPropertyBuffData
{
	ACE_UINT32 unPropertyID;
	float baseValue;
	float scaleValue;
}PropertyBuffData;

typedef struct tagPropertyBuffList
{
	ACE_UINT32 unCount;
	PropertyBuffData list[MAX_PROPERTY_COUNT];
}PropertyBuffList;
*/



enum
{
	BATTLE_RECORD_TYPE_START = 0,
	BATTLE_RECORD_TYPE_NEXT_SECTION,
	BATTLE_RECORD_TYPE_ATTACK,
	BATTLE_RECORD_LAUNCH,
	BATTLE_RECORD_GET_ITEM,
	BATTLE_RECORD_ATTACK_START,
	BATTLE_RECORD_ATTACK_END,
	BATTLE_RECORD_FALL
};

typedef struct tagBattleCommand{
	int nCommandType;
}BattleCommand;

typedef struct tagBattleCommandStart : public BattleCommand
{
	int nCount;
	ACE_UINT32 list[MAX_PLAYER_SELECTED_COUNT];
}BattleCommandStart;

typedef struct tagBattleCommandNextSection : public BattleCommand
{
}BattleCommandNextSection;

typedef struct tagBattleAttackTarget
{
	int nIndex;
	int nDamage;
}BattleAttackTarget;

typedef struct tagBattleCommandAttack : public BattleCommand
{
	int nAttackID;
	BattleAttackTarget target;
}BattleCommandAttack;

typedef struct tagBattleCommandLaunch : public BattleCommand
{
	int nIndex;
}BattleCommandLaunch;

typedef struct tagBattleCommandGetItem : public BattleCommand
{
	int nItemIndex;
	int nCampType;
	int nIndex;
}BattleCommandGetItem;

typedef struct tagBattleCommandAttackStart : public BattleCommand
{
	int nAttackID;
	int nCampType;
	int nAttackerIndex;
}BattleCommandAttackStart;

typedef struct tagBattleCommandAttackEnd : public BattleCommand
{
	int nAttackID;
}BattleCommandAttackEnd;

typedef struct tagBattleCommandFall : public BattleCommand
{
	int nIndex;
}BattleCommandFall;

/*
队员index
0代表主将
1-4代表副将
5代表友将

BATTLE_RECORD_TYPE_START,
16个字节，分别是4个副将的ID

BATTLE_RECORD_TYPE_END
没有字节

BATTLE_RECORD_TYPE_SECTION_START
没有字节

BATTLE_RECORD_TYPE_SECTION_END
没有字节
	
BATTLE_RECORD_TYPE_ATTACK
1个字节，攻击者类型（0，1），0代表自己队员，1代表怪物
1个字节，攻击者index
1个字节，伤害的次数（大于等于1）
{
	1个字节，被攻击者index
	4个字节，伤害
}

BATTLE_RECORD_LAUNCH
1个字节，队员的index（0-5）

BATTLE_RECORD_GET_ITEM
1个字节，道具index
1个字节，获得者类型（0，1），0代表自己队员，1代表怪物
1个字节，获得者index
*/


typedef struct tagBattleUnit
{
	int hp;
	int damage;
	int originalHP;
	int originalDamage;
	int maxHP;
	int maxDamage;
}BattleUnit;


#define MAX_SECTION_PER_BATTLE 16
#define MAX_ATTACK_COUNT_PER_SECTION 64

typedef struct tagAttackQueueInfo
{
	int nCampType;
	BattleUnit *unit;
	int nDone;
}AttackQueueInfo;

typedef struct tagBattleItem
{
	StageRes *res;
	int used;
}BattleItem;

typedef struct tagBattleSection
{
	int nMonsterCount;
	BattleUnit monsterList[MAX_MONSTER_PER_SECTION];

	int nItemCount;
	BattleItem itemList[MAX_ITEM_PER_SECTION];
}BattleSection;

class BattleMgr
{
public:
	BattleMgr();
	~BattleMgr();

	static bool verify(ACE_UINT32 unMapID, char *data, int size, TeamMember *team, int nMemberCount, CharacterInfoExt *friendCharacter, BattleSnapInfo *snapInfo);

private:
	static int command_token(char *data, int size, BattleCommand *command);
	static bool process_command(BattleCommand *command);
	static int init_stage_data(ACE_UINT32 unMapID);
	static int init_player_team(ACE_UINT32 *list);
	static void init_section();
	static void init_battle();
	static void init_section(int nSectionIdx);
	static BattleUnit *get_unit(int nCamp, int nIndex, bool isAttack);
	static bool can_end_section();
	static void reset_stage();
	static void hurt_unit(BattleUnit *unit, int damage);
	static int get_item(BattleUnit *unit, int itemIdx);

	static StreamRW m_stream;
	//static int m_nBattleStep;
	//static int m_nCurrentSection;
	static int m_nSectionCount;
	static ACE_UINT32 m_unCurrentMapID;
	static TeamMember *m_team;
	static int m_nTeamMemberCount;
	static CharacterInfoExt *m_friendCharacter;
	static int m_nCurrentAttackIndex;
	static int m_nLaunchCount;
	static AttackQueueInfo m_attackerQueue[MAX_ATTACK_COUNT_PER_SECTION];
	static int m_nCurrentAttackID;
	//static int m_nCurrentAttackCamp;
	//static BattleUnit *m_pCurrentAttack;
	static BattleSnapInfo *m_battleSnap;

	static BattleUnit m_playerTeam[MAX_PLAYER_SELECTED_COUNT + 2];
	static BattleSection m_sectionList[MAX_SECTION_PER_BATTLE];
	static int m_monsterAttackFlag[MAX_MONSTER_PER_SECTION];

	static int m_waitQueue[MAX_PLAYER_SELECTED_COUNT + 2];
	static int m_attackQueue[MAX_PLAYER_SELECTED_COUNT + 2];


};
