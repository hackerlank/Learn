#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include "..\..\GameBase\res\BehaviorRes.h"


class CooldownMgr : public BaseModule
{
public:
	CooldownMgr();
	~CooldownMgr();

	void init(CooldownInstanceInfo *list);
	virtual void update(ACE_UINT32 unCurrentTime);
	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN);

	CooldownInstanceInfo m_list[MAX_COOLDOWN_INFO];

	ACE_UINT32 m_unCooldownInfoCount;

	int can_do(ACE_UINT32 unCurrentTime, ACE_UINT32 unID, ACE_UINT32 unTimes = -1);//判断是否已过冷却时间
	int get_count(ACE_UINT32 unCurrentTime, ACE_UINT32 unID, ACE_UINT32 unTimes = -1);//判断是否已过冷却时间
	int do_once(ACE_UINT32 unCurrentTime, ACE_UINT32 unID);

private:
	int get_cd_info(ACE_UINT32 unID);

	int get_current_count(ACE_UINT32 unCurrentTime, CooldownInstanceInfo *info, BaseRes *res);
	int add_count(ACE_UINT32 unCurrentTime, CooldownInstanceInfo *info, BaseRes *res);

	//bool update_cooldown(ACE_UINT32 unCurrentTime, CooldownInstanceInfo *info);
	//bool update_cooldown(ACE_UINT32 unCurrentTime, CooldownInstanceInfo *info, BaseRes *res);

	//bool is_reach_max_count(ACE_UINT32 unID, int maxCount);
	//int add_count(ACE_UINT32 unID, int maxCount);

	void update_2_db();
};