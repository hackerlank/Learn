#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include "..\..\Base\Event\EventListener.h"

class SkillMgr : public BaseModule, public EventListener
{
public:
	SkillMgr();
	~SkillMgr();

	void init(ACE_UINT32 *list, ACE_UINT32 *playerSkillList,SkillBook *bookRes);
//		void init(ACE_UINT32 *list, ACE_UINT32 *playerSkillList);

	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN);

	virtual void handle_event(BaseEvent *e);

	int level_up(ACE_UINT32 unSkillID, int dwLevelAdd,ACE_UINT32 & unDynamicEnergy);

	ACE_UINT32 get_skill_id(ACE_UINT32 unSkillID);

	//int get_player_skill(ACE_UINT32 unPlayerSkillID);
	bool has_player_skill(ACE_UINT32 unPlayerSkillID);
	void add_player_skill(ACE_UINT32 unPlayerSkillID);

	void update_2_db();


	ACE_UINT32 m_unSkillCount;
	ACE_UINT32 m_list[MAX_SKILL_COUNT];

	ACE_UINT32 m_unPlayerSkillCount;
	ACE_UINT32 m_playerSkillList[MAX_PLAYER_SKILL_COUNT];


	SkillBook m_bookRes[MAX_PLAYER_SKILL_COUNT];//作为合成用的技能图纸
	ACE_UINT32 m_unBookResCount;//最为升级图纸的种类个数
	int GetSkillStart(ACE_UINT32 id,int step);//通过进阶值得到星级
private:
	void parse();
};