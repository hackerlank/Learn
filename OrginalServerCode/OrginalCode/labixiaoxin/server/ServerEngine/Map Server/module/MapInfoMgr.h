#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include "..\..\Base\Communication\StreamRW.h"
#include "..\..\GameBase\res\StageRes.h"
#include "..\..\Base\Event\EventListener.h"

#include "..\..\GameBase\res\MapRes.h"

#include <set>


class MapInfoMgr : public BaseModule, public EventListener
{
public:
	MapInfoMgr();
	~MapInfoMgr();

	void initEx(MapInstanceInfo &instanceInfo, RewardInfo &reward, MapFlagInfo *list, ACE_UINT32 unLastRewardTime, ACE_UINT32 unFreeRebornCount, ACE_UINT32 unLastRebornTime, MapFlagInfo *giftList);
	void init(MapInstanceInfo &instanceInfo, RewardInfo &reward, MapFlagInfo *list, ACE_UINT32 unLastRewardTime, ACE_UINT32 unFreeRebornCount, ACE_UINT32 unLastRebornTime, MapFlagInfo *giftList);
	void initDoubleDrop(MsgDBDoubleDropInfoResponse &info);
	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN);

	int enter_map(ACE_UINT32 unMapID,ACE_UINT32 unsMapID, int nGlobalMapEventType, CharacterInfoExt *friendInfo);
	int get_reward(ACE_UINT32 unMapID, ACE_UINT32 unCurrentTime, ACE_UINT32 unBellCount, ACE_UINT32 unLaunchCount,ACE_INT32 maxExp);
	int get_map_gift(ACE_UINT32 unMapGroupID, ACE_UINT32 unIdx, RewardInfo &reward);
	int reset_map(ACE_UINT32 unMapID);
	void Reset_map_day_different_count();

	void clear_map();

	int battle_reborn(ACE_UINT32 unCurrentTime);
	//void add_battle_command(char *battleData, int battleDataSize, MsgBattleCommandResponse &response);

	virtual void handle_event(BaseEvent *e);

	MapInstanceInfo m_info;
	RewardInfo m_reward;
	RewardInfo m_rewardTemp;
	MapFlagInfo m_flagList[MAX_MAP_COUNT];
	ACE_UINT32 m_unMapCount;
	ACE_UINT32 m_unLastRewardTime;
	ACE_UINT32 m_unFreeRebornCount;
	ACE_UINT32 m_unLastRebornTime;
	ACE_UINT32 m_unMapGroupCount;
	MapFlagInfo m_giftList[MAX_MAP_COUNT];

	std::set<ACE_UINT32> m_setUsedDouble;
	ACE_UINT32 m_unDoubleVersion;
	
	ACE_UINT32 m_unFreeRebornMax;

	int m_nVerifyBattleErrorCode;
	int m_nCurrentCommandIndex;
	char m_currentCommandBuff[MAX_COMMAND_BUFF_SIZE];
	//ACE_UINT32 m_rewardCount;
	ACE_UINT32 m_unReward3Star;//是否是首通3星

	int unlock_map(ACE_UINT32 unMapID);

	int get_map_star(ACE_UINT32 unMapID);//获当前map进入的星星

	void SetJinYingMapCount(ACE_UINT32 unMapID,ACE_UINT32 unCount);//设置精英副本次数
private:
	bool check_enter(MapFlagInfo *flagInfo, int level, MapRes *res);
	//void parse_flag_list();
	MapFlagInfo *get_map_flag_info(ACE_UINT32 unMapID);

	MapFlagInfo *add_map_flag_info(ACE_UINT32 unMapID);



	void add_star(ACE_UINT32 unMapID, int star, int old_star);

	void update_map_info_2_db();
	void update_map_flag_2_db();
	void update_star_count_2_db(int dwStarAdded);
	void update_double_drop_db();

	bool isSpecialMap;

	ACE_UINT32 m_starCountList[MAX_MAP_COUNT];
	ACE_UINT32 _unMapID;
	ACE_UINT32 _unsMapID;//密境地图id
};