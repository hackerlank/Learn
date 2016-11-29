#pragma once

////////////////////////////////////////////////////////////////////////////////////////////
//Server Macro

#define GAME_SERVER

#define STRICT_SCRIPT_CHECK 0

//#define _BLOB_PRESS_TEST

////////////////////////////////////////////////////////////////////////////////////////////
//Game Macro

#define PI 3.14159265f

#define COORDINATE_CHECK 1

#define ENABLE_ROBOT 1

#ifdef _DEBUG
#define MAX_MONEY  0xFFFFFFFF
#else
#define MAX_MONEY  100000000
#endif

#define MAX_POSSIBLE_MONEY MAX_MONEY
#define MAX_MONEY_TYPE     100

#define PLAYER_WALK_TIME_INTERVAL 300

#define GATHER_CREATURE_ID_MIN 500000001
#define GATHER_CREATURE_ID_MAX 510000000

#define SWITCHER_ID_MIN 700000001
#define SWITCHER_ID_MAX 750000000

#define BLOCKER_ID_MIN 750000001
#define BLOCKER_ID_MAX 800000000

#define MERCEN_CAMP_INIT_COUNT 9
#define MERCEN_CAMP_MAX_COUNT 40

#define FAST_MONSTER_MAP_COUNT 5
#define SLOW_MONSTER_MAP_COUNT 10
#define PLAYER_WALK_MAP_COUNT 10
#define PLAYER_ROLE_MAP_COUNT 5
#define PLAYER_FIGHT_SET_COUNT 5
#define PLAYER_ACTION_SET_COUNT 3
#define MONSTER_MAP_COUNT 10

#define FAST_MONSTER_TIMER_INTERVAL 100
#define SLOW_MONSTER_TIMER_INTERVAL 500

#define MAX_ITEM_QUALITY 6

#define TIMER_SAVE_INTERVAL_NORMAL 5
#define TIMER_SAVE_INTERVAL_MAX 60

#ifdef _DEBUG
#define MAX_LEAVE_INTERVAL 1*60/*1*/ 
#else
#define MAX_LEAVE_INTERVAL 15*60/*60*/
#endif

#define MAX_REPLACE_INTERVEL 3 * 60

#define GAME_RANDOM_PERCENT 10000
#define GAME_COEF_PERCENT 10000

#define PER_HOUR_TO_S 3600
#define PER_MINUTE_TO_S 60
#define PER_DAY_TO_S 86400

////////////////////////////////////////////////////////////////////////////////////////////
//Smart Pointer

#define DEF_SMART_POINTER(type, name) \
type name; \
typedef shared_ptr<name> name##Ptr; \
typedef weak_ptr<name> name##Wtr;

DEF_SMART_POINTER(class, CGameMap);
DEF_SMART_POINTER(struct, SMapInfo);
DEF_SMART_POINTER(struct, SRegion);
DEF_SMART_POINTER(struct, SJumpRegion);
DEF_SMART_POINTER(struct, SProbeRegion);
DEF_SMART_POINTER(class ,CMapArea);

DEF_SMART_POINTER(class, CBaseObj);
DEF_SMART_POINTER(class, CUser);
DEF_SMART_POINTER(class, CCreature);
DEF_SMART_POINTER(class, CPlayer);
DEF_SMART_POINTER(class, CMonster);
DEF_SMART_POINTER(class, CWorldBoss);
DEF_SMART_POINTER(class, CNpc);
DEF_SMART_POINTER(class, IGather);
DEF_SMART_POINTER(class, CGather);
DEF_SMART_POINTER(class, CSwitcher);
DEF_SMART_POINTER(class, CJumpSwitcher);
DEF_SMART_POINTER(class, CTowerJumpSwitcher);
DEF_SMART_POINTER(class, CCampSwitcher);
DEF_SMART_POINTER(class, CBlocker);

DEF_SMART_POINTER(class, CSoulSpaceMgr);
DEF_SMART_POINTER(class, CHorseMgr);
DEF_SMART_POINTER(class, CAchievementMgr);
DEF_SMART_POINTER(class, CCollectionMgr);
DEF_SMART_POINTER(class, CAttackedMgr);
DEF_SMART_POINTER(class, CExchangeShopMgr);
DEF_SMART_POINTER(class, CEnergyMgr);
DEF_SMART_POINTER(class, CLevelPrizeAct);
DEF_SMART_POINTER(class, CEventMgr);
DEF_SMART_POINTER(class, CLoginPkgMgr);
DEF_SMART_POINTER(class, CShopItemMgr);
DEF_SMART_POINTER(class, CDayTargetMgr);
DEF_SMART_POINTER(class, CTreasureHunt);
DEF_SMART_POINTER(class, CGuardEMei);
DEF_SMART_POINTER(class, CMoneyTree);
DEF_SMART_POINTER(class, CRegisterSevenDays);
DEF_SMART_POINTER(class, CAutoStoreMgr);
DEF_SMART_POINTER(class, CBattleArrayMgr);
DEF_SMART_POINTER(class, CBeautyMgr);
DEF_SMART_POINTER(class, CShushanweiwei);
DEF_SMART_POINTER(class, CShengLing);
DEF_SMART_POINTER(class, CFenbaoyanMgr);

DEF_SMART_POINTER(class, CFightFormationMgr);
DEF_SMART_POINTER(class, CFightHeroInfoMgr);

DEF_SMART_POINTER(class, CFighter);
DEF_SMART_POINTER(class, CHeroFighter);
DEF_SMART_POINTER(class, CFighterManager);
DEF_SMART_POINTER(class, CHeroFighterCombination);
DEF_SMART_POINTER(class, CPet);
DEF_SMART_POINTER(class, CFormation);
DEF_SMART_POINTER(class, CFashion);
DEF_SMART_POINTER(class, CBeastSoul);


DEF_SMART_POINTER(class, CItem);
DEF_SMART_POINTER(class, CCitta);
DEF_SMART_POINTER(class, CStackItem);
DEF_SMART_POINTER(class, CTrump);
DEF_SMART_POINTER(class, CEquipTrump);
DEF_SMART_POINTER(class, CGemstone);

DEF_SMART_POINTER(class, CDungeon);
DEF_SMART_POINTER(class, CPlayerDgn);

DEF_SMART_POINTER(class, CScript);
DEF_SMART_POINTER(class, CAIScript);
DEF_SMART_POINTER(class, CGameScript);

DEF_SMART_POINTER(class, CDemonTowerDgn);

DEF_SMART_POINTER(class, CTask);

DEF_SMART_POINTER(struct, SObjCond);
DEF_SMART_POINTER(struct, SKillMonsterCond);
DEF_SMART_POINTER(struct, SPlayerPosCond);
DEF_SMART_POINTER(struct, SAllMonsterKilled);

DEF_SMART_POINTER(struct, SLuaUInt64);

DEF_SMART_POINTER(class, CForbidDB);

DEF_SMART_POINTER(struct, SSkillEf);
DEF_SMART_POINTER(struct, SSkill);


DEF_SMART_POINTER(class, CBubble);
DEF_SMART_POINTER(class, CBubbleOwner);

DEF_SMART_POINTER(class, CGuildBattle);
DEF_SMART_POINTER(class, CGuildBattleField);
DEF_SMART_POINTER(class, CGuildBattleSpot);
DEF_SMART_POINTER(class, CGuildBattleInfo);
DEF_SMART_POINTER(struct, SGuildBattleSpotPlayer);

DEF_SMART_POINTER(struct, SSBPlayerData);

DEF_SMART_POINTER(struct, CMonsterAI);

DEF_SMART_POINTER(class, CTavern);
DEF_SMART_POINTER(class, CHeroFighterInTavern);

DEF_SMART_POINTER(class, CDrawData);
DEF_SMART_POINTER(class, CDraw);

DEF_SMART_POINTER(struct, SDayActEx);
DEF_SMART_POINTER(class, CDayActivity);
DEF_SMART_POINTER(class, CDayActEvent);

//Smart Pointer
////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//typedef
typedef vector<CPlayerPtr>  TVecPlayerPtr;
typedef vector<CFighterPtr> TVecFighterPtr;

typedef vector<CBubblePtr>  TVecBubblePtr;

typedef vector<CGuildBattlePtr> TVecGuildBattlePtr;
typedef vector<CGuildBattleInfoPtr> TVecGuildBattleInfoPtr;

typedef list<SGuildBattleSpotPlayerPtr>     TListGBPlayerPtr;
typedef vector<SGuildBattleSpotPlayerPtr>   TVecGBPlayerPtr;
typedef vector<CEquipTrumpPtr> TVecEquipTrumpPtr;
typedef vector<CGemstonePtr> TVecGemstonePtr;


