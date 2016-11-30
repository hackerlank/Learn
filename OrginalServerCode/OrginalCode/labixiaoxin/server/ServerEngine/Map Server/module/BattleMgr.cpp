#include "BattleMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\..\GameBase\res\PlayerRes.h"
#include "..\..\GameBase\res\EquipmentRes.h"
#include "..\..\GameBase\res\ImproveRes.h"
#include "..\..\GameBase\res\SkillRes.h"
#include "..\..\GameBase\res\MonsterRes.h"
#include "..\..\GameBase\res\MapRes.h"
#include "EquipmentMgr.h"
#include "PlayerMgr.h"
#include "SkillMgr.h"
#include "WeaponSkillMgr.h"
#include "..\Map.h"
#include "StageInfoMgr.h"

StreamRW BattleMgr::m_stream;
//int BattleMgr::m_nBattleStep = 0;
//int BattleMgr::m_nCurrentSection = 0;
ACE_UINT32 BattleMgr::m_unCurrentMapID = 0;
int BattleMgr::m_nSectionCount = 0;

BattleSnapInfo *BattleMgr::m_battleSnap = NULL;

TeamMember *BattleMgr::m_team = NULL;
CharacterInfoExt *BattleMgr::m_friendCharacter = NULL;

BattleUnit BattleMgr::m_playerTeam[MAX_PLAYER_SELECTED_COUNT + 2];
BattleSection BattleMgr::m_sectionList[MAX_SECTION_PER_BATTLE];
int BattleMgr::m_waitQueue[MAX_PLAYER_SELECTED_COUNT + 2];
int BattleMgr::m_attackQueue[MAX_PLAYER_SELECTED_COUNT + 2];
int BattleMgr::m_nCurrentAttackIndex = 0;
int BattleMgr::m_nLaunchCount = 0;
int BattleMgr::m_monsterAttackFlag[MAX_MONSTER_PER_SECTION];
//int BattleMgr::m_nCurrentAttackCamp = 0;
//BattleUnit *BattleMgr::m_pCurrentAttack = NULL;
AttackQueueInfo BattleMgr::m_attackerQueue[MAX_ATTACK_COUNT_PER_SECTION];
int BattleMgr::m_nCurrentAttackID = 0;
int BattleMgr::m_nTeamMemberCount = 0;

BattleMgr::BattleMgr()
{
}

BattleMgr::~BattleMgr()
{

}

bool BattleMgr::verify(ACE_UINT32 unMapID, char *data, int size, TeamMember *team, int nMemberCount, CharacterInfoExt *friendCharacter, BattleSnapInfo *snapInfo)
{
	int offset = 0;

	int c = 0;
	int tmp_size = size;
	char command_buff[256];

	m_battleSnap = snapInfo;

	m_nTeamMemberCount = nMemberCount;

	//ACE_OS::memset(command_buff, 0, 256);
	m_team = team;
	m_friendCharacter = friendCharacter;

	BattleCommand *command = (BattleCommand *)command_buff;

	/*
	if(init_stage_data(unMapID) == -1)
	{
		return true;
	}
	*/

	printf("battle log data = \n");

	for(int i = 0;i < size;i ++)
	{
		int ttt = data[i];
		ttt = ttt & 0xff;
		printf("%02x ", ttt);
	
	}

	printf("\n\n");

	while((c = command_token(&data[offset], tmp_size, command)) != -1)
	{
		//printf("command token, type = %d\n", command->nCommandType);

		if(!process_command(command))
		{
			return true;
		}

		offset += c;
		tmp_size -= c;
	}
	

	return true;
}

int BattleMgr::init_stage_data(ACE_UINT32 unMapID)
{
	ACE_UINT32 unTmpID = (unMapID / 10) * 10;
	//int stage_level = unMapID % 10;

	StageEntityInfo *info = STAGE_INFO_MGR_INSTANCE::instance()->get_stage_info(unTmpID);

	if(info == NULL)
	{
		return -1;
	}

	int c = 0;
	int offset = 0;
	int i;
	ACE_UINT32 unID;

	MonsterRes *monsterRes;
	StageRes *stageRes;

	m_nSectionCount = 0;

	MapRes *mapRes;

	mapRes = (MapRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unMapID);

	if(mapRes == NULL)
	{
		return -1;
	}

	while(info->monsterOffset[c] != -1)
	{
		m_sectionList[c].nMonsterCount = info->monsterOffset[c];
		for(i = 0;i < info->monsterOffset[c];i ++)
		{
			unID = info->unMonsterIDList[offset + i];

			//get monster info
			monsterRes = (MonsterRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unID);

			if(monsterRes == NULL)
			{
				return -1;
			}

			/*
			1	ÆÕÍ¨¹ÖÎï	¹¥»÷=4*lv			
			ÑªÁ¿=30*lv											
2	Ð¡boss	¹¥»÷=5*lv			
			ÑªÁ¿=60*lv											
4	boss		¹¥»÷=8*lv			
			ÑªÁ¿=100*lv			
																
3	ÂÒÈëboss	¹¥»÷=10*lv			
			ÑªÁ¿=150*lv

°¢Ë®  11:12:26
1	ÆÕÍ¨¹ÖÎï	ÑªÁ¿=20*lv
			*/
			int damage_scale = 1;
			int hp_sacle = 1;
			int lv = mapRes->m_unLevelUp + monsterRes->m_unLevel;

			switch(monsterRes->m_unSubType)
			{
			case 1:
				damage_scale = 4;
				hp_sacle = 20;
				break;
			case 2:
				damage_scale = 5;
				hp_sacle = 60;
				break;
			case 3:
				damage_scale = 10;
				hp_sacle = 150;
				break;
			case 4:
				damage_scale = 8;
				hp_sacle = 100;
				break;
			default:
				return -1;
			}
			m_sectionList[c].monsterList[i].originalDamage = damage_scale * lv;
			m_sectionList[c].monsterList[i].originalHP = hp_sacle * lv;
		}

		offset += info->monsterOffset[c];

		c ++;
	}

	m_nSectionCount = c;

	c = 0;
	offset = 0;

	while(info->itemOffset[c] != -1)
	{
		m_sectionList[c].nItemCount = info->itemOffset[c];

		for(i = 0;i < info->itemOffset[c];i ++)
		{
			unID = info->unItemIDList[offset + i];

			//get item info
			stageRes = (StageRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unID);

			if(stageRes == NULL)
			{
				return -1;
			}

			m_sectionList[c].itemList[i].res = stageRes;
		}

		offset += info->itemOffset[c];

		c ++;
	}

	if(m_nSectionCount < c)
	{
		m_nSectionCount = c;
	}

	return 0;
}

int BattleMgr::init_player_team(ACE_UINT32 *list)
{
	//m_playerTeam[0].

	int i, j;
	int flag[MAX_PLAYER_SELECTED_COUNT];

	PropertyComponent tmp_property_list[MAX_PLAYER_SELECTED_COUNT + 2][PROPERTY_ID_MAX];

	ACE_OS::memset(tmp_property_list, 0, sizeof(PropertyComponent) * (MAX_PLAYER_SELECTED_COUNT + 2));

	ACE_UINT32 skill_list[MAX_PLAYER_SELECTED_COUNT + 2];

	ACE_OS::memset(flag, 0, MAX_PLAYER_SELECTED_COUNT * sizeof(int));
	for(i = 0;i < (m_nTeamMemberCount - 1);i ++)
	{
		for(j = 0;j < (m_nTeamMemberCount - 1);j ++)
		{
			if(list[i] == m_team[j + 1].unItemID)
			{
				break;
			}
		}

		if(j >= (m_nTeamMemberCount - 1))
		{
			return -1;
		}

		if(flag[j] == 1)
		{
			return -1;
		}

		flag[j] = 1;

		tmp_property_list[i + 1][PROPERTY_ID_HP].fValue = m_team[j + 1].propertyList[PROPERTY_ID_HP].fValue;
		tmp_property_list[i + 1][PROPERTY_ID_HP].fScale = m_team[j + 1].propertyList[PROPERTY_ID_HP].fScale;
		skill_list[i + 1] = m_team[j + 1].unSkillID;
	}

	skill_list[0] = m_team[0].unSkillID;
	skill_list[m_nTeamMemberCount] = m_friendCharacter->unSkillID;

	tmp_property_list[0][PROPERTY_ID_HP] = m_team[0].propertyList[PROPERTY_ID_HP];
	tmp_property_list[0][PROPERTY_ID_DAMAGE] = m_team[0].propertyList[PROPERTY_ID_DAMAGE];

	tmp_property_list[m_nTeamMemberCount][PROPERTY_ID_HP]= m_friendCharacter->propertyList[PROPERTY_ID_HP];
	tmp_property_list[m_nTeamMemberCount][PROPERTY_ID_DAMAGE]= m_friendCharacter->propertyList[PROPERTY_ID_DAMAGE];

	tmp_property_list[0][PROPERTY_ID_ALL_HP].fValue = m_team[0].propertyList[PROPERTY_ID_ALL_HP].fValue + m_friendCharacter->propertyList[PROPERTY_ID_ALL_HP].fValue;
	tmp_property_list[0][PROPERTY_ID_ALL_HP].fScale = m_team[0].propertyList[PROPERTY_ID_ALL_HP].fScale + m_friendCharacter->propertyList[PROPERTY_ID_ALL_HP].fScale;
	tmp_property_list[0][PROPERTY_ID_ALL_DAMAGE].fValue = m_team[0].propertyList[PROPERTY_ID_ALL_DAMAGE].fValue + m_friendCharacter->propertyList[PROPERTY_ID_ALL_DAMAGE].fValue;
	tmp_property_list[0][PROPERTY_ID_ALL_DAMAGE].fScale = m_team[0].propertyList[PROPERTY_ID_ALL_DAMAGE].fScale + m_friendCharacter->propertyList[PROPERTY_ID_ALL_DAMAGE].fScale;


	float tmp_v;
	float tmp_s;

	//float tmp_global_v;
	//float tmp_global_s;

	//tmp_global_v = tmp_property_list[0]
	SkillRes *skillRes;

	for(i = 0;i < (m_nTeamMemberCount + 1);i ++)
	{
		//m_playerTeam[i].
		skillRes = (SkillRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(skill_list[i]);

		if(skillRes == NULL)
		{
			return -1;
		}

		tmp_v = 0.0f;
		tmp_s = 1.0f;

		for(j = 0;j < skillRes->m_propertyList.unCount;j ++)
		{
			if(skillRes->m_propertyList.list[j].unPropertyID == PROPERTY_ID_HP)
			{
				if(skillRes->m_propertyList.list[j].unType == 1)
				{
					tmp_s += skillRes->m_propertyList.list[j].fValue;
				}
				else
				{
					tmp_v += skillRes->m_propertyList.list[j].fValue;
				}
			}
		}

		tmp_v += tmp_property_list[i][PROPERTY_ID_HP].fValue + tmp_property_list[0][PROPERTY_ID_ALL_HP].fValue;
		tmp_s += tmp_property_list[i][PROPERTY_ID_HP].fScale + tmp_property_list[0][PROPERTY_ID_ALL_HP].fScale;

		m_playerTeam[i].originalHP = (int)(tmp_v * tmp_s);


		tmp_v = 0.0f;
		tmp_s = 1.0f;

		for(j = 0;j < skillRes->m_propertyList.unCount;j ++)
		{
			if(skillRes->m_propertyList.list[j].unPropertyID == PROPERTY_ID_DAMAGE)
			{
				if(skillRes->m_propertyList.list[j].unType == 1)
				{
					tmp_s += skillRes->m_propertyList.list[j].fValue;
				}
				else
				{
					tmp_v += skillRes->m_propertyList.list[j].fValue;
				}
			}
		}

		tmp_v += tmp_property_list[i][PROPERTY_ID_DAMAGE].fValue + tmp_property_list[0][PROPERTY_ID_ALL_DAMAGE].fValue;
		tmp_s += tmp_property_list[i][PROPERTY_ID_DAMAGE].fScale + tmp_property_list[0][PROPERTY_ID_ALL_DAMAGE].fScale;
		m_playerTeam[i].originalDamage = (int)(tmp_v * tmp_s);
	}

	return 0;
}

void BattleMgr::init_battle()
{
}

void BattleMgr::init_section(int nSectionIdx)
{
}

int BattleMgr::command_token(char *data, int size, BattleCommand *command)
{
	m_stream.reset(data, size);

	command->nCommandType = 0;

	if(m_stream.readNumber((char *)&command->nCommandType, 1) == -1)
	{
		return -1;
	}
	
	int nRet = 0;
	int i;

	switch(command->nCommandType)
	{
	case BATTLE_RECORD_TYPE_START:
		{
			BattleCommandStart *p = (BattleCommandStart *)command;

			p->nCount = 0;

			if(m_stream.readNumber((char *)&p->nCount, 1) == -1)
			{
				nRet = -1;
			}

			if(nRet == 0 && p->nCount != (m_nTeamMemberCount - 1))
			{
				nRet = -1;
			}

			if(nRet == 0)
			{
				for(i = 0;i < p->nCount;i ++)
				{
					p->list[i] = 0;
					if(m_stream.readNumber((char *)&p->list[i], 4) == -1)
					{
						nRet = -1;
						break;
					}
				}
			}

			if(nRet != -1)
			{
				printf("command token, type = %d [", p->nCommandType);
				for(i = 0;i < p->nCount;i ++)
				{
					printf("%d,", p->list[i]);
				}
				
				printf("]\n");
			}
		}
		break;
	case BATTLE_RECORD_TYPE_NEXT_SECTION:
		printf("command token, type = %d\n", command->nCommandType);
		break;
	case BATTLE_RECORD_TYPE_ATTACK:
		{
			BattleCommandAttack *p = (BattleCommandAttack *)command;

			p->nAttackID = 0;
			p->target.nIndex = 0;
			p->target.nDamage = 0;

			if(m_stream.readNumber((char *)&p->nAttackID, 1) == -1 || m_stream.readNumber((char *)&p->target.nIndex, 1) == -1 || m_stream.readNumber((char *)&p->target.nDamage, 4) == -1)
			{
				nRet = -1;
				break;
			}


			if(nRet != -1)
			{
				printf("command token, type = %d [%d, %d, %d]\n", p->nCommandType, p->nAttackID, p->target.nIndex, p->target.nDamage);
			}
		}
		break;
	case BATTLE_RECORD_LAUNCH:
		{
			BattleCommandLaunch *p = (BattleCommandLaunch *)command;
			p->nIndex = 0;
			if(m_stream.readNumber((char *)&p->nIndex, 1) == -1)
			{
				nRet = -1;
			}
			if(nRet != -1)
			{
				printf("command token, type = %d [%d]\n", p->nCommandType, p->nIndex);
			}
		}
		break;
	case BATTLE_RECORD_GET_ITEM:
		{
			BattleCommandGetItem *p = (BattleCommandGetItem *)command;

			p->nItemIndex = 0;
			p->nCampType = 0;
			p->nIndex = 0;
			if(m_stream.readNumber((char *)&p->nItemIndex, 1) == -1 || m_stream.readNumber((char *)&p->nCampType, 1) == -1 || m_stream.readNumber((char *)&p->nIndex, 1) == -1)
			{
				nRet = -1;
			}

			if(nRet != -1)
			{
				printf("command token, type = %d [%d, %d, %d]\n", p->nCommandType, p->nItemIndex, p->nCampType, p->nIndex);
			}
		}
		break;
	case BATTLE_RECORD_ATTACK_START:
		{
			BattleCommandAttackStart *p = (BattleCommandAttackStart *)command;

			p->nAttackID = 0;
			p->nCampType = 0;
			p->nAttackerIndex = 0;
			if(m_stream.readNumber((char *)&p->nAttackID, 1) == -1 || m_stream.readNumber((char *)&p->nCampType, 1) == -1 || m_stream.readNumber((char *)&p->nAttackerIndex, 1) == -1)
			{
				nRet = -1;
			}

			if(nRet != -1)
			{
				printf("command token, type = %d [%d, %d, %d]\n", p->nCommandType, p->nAttackID, p->nCampType, p->nAttackerIndex);
			}
		}
		break;
	case BATTLE_RECORD_ATTACK_END:
		{
			BattleCommandAttackEnd *p = (BattleCommandAttackEnd *)command;

			p->nAttackID = 0;
			if(m_stream.readNumber((char *)&p->nAttackID, 1) == -1)
			{
				nRet = -1;
			}

			if(nRet != -1)
			{
				printf("command token, type = %d [%d]\n", p->nCommandType, p->nAttackID);
			}
		}
		break;
	case BATTLE_RECORD_FALL:
		{
			BattleCommandFall *p = (BattleCommandFall *)command;

			p->nIndex = 0;
			
			if(m_stream.readNumber((char *)&p->nIndex, 1) == -1)
			{
				nRet = -1;
			}

			if(nRet != -1)
			{
				printf("command token, type = %d [%d]\n", p->nCommandType, p->nIndex);
			}
		}
		break;
	default:
		nRet = -1;
		break;
	}

	if(nRet != -1)
	{
		nRet = m_stream.getCursor();
	}
	else
	{
		printf("command token failed[%d]\n", command->nCommandType);
	}

	return nRet;
}

/*
bool BattleMgr::process_command(BattleCommand *command)
{
	bool ret = false;
	int i;
	switch(m_nBattleStep)
	{
	case BATTLE_STEP_WAIT:
		if(command->nCommandType == BATTLE_RECORD_TYPE_START)
		{
			BattleCommandStart *p = (BattleCommandStart *)command;
			if(init_player_team(p->list) == 0)
			{
				reset_stage();
				m_nBattleStep = BATTLE_STEP_IDLE;
				ret = true;
			}
		}
		break;
	case BATTLE_STEP_IDLE:
		if(command->nCommandType == BATTLE_RECORD_TYPE_SECTION_START)
		{
			if(m_nCurrentSection < m_nSectionCount)
			{
				m_nBattleStep = BATTLE_STEP_SECTION;
				ret = true;
				init_section();
			}
		}
		else if(command->nCommandType == BATTLE_RECORD_TYPE_END)
		{
			m_nBattleStep = BATTLE_STEP_DONE;
			ret = true;
		}
		break;
	case BATTLE_STEP_SECTION:
		if(command->nCommandType == BATTLE_RECORD_TYPE_SECTION_END)
		{
			if(can_end_section())
			{
				m_nBattleStep = BATTLE_STEP_IDLE;
				m_nCurrentSection ++;
				ret = true;
			}
		}
		else if(command->nCommandType == BATTLE_RECORD_ATTACK_START)
		{
			BattleCommandAttackStart *p = (BattleCommandAttackStart *)command;

			if(p->nAttackID == m_nCurrentAttackID)
			{
				m_attackerQueue[m_nCurrentAttackID].nCampType = p->nCampType;
				m_attackerQueue[m_nCurrentAttackID].unit = get_unit(p->nCampType, p->nAttackerIndex, true);
				m_attackerQueue[m_nCurrentAttackID].nDone = 0;
				if(m_attackerQueue[m_nCurrentAttackID].unit != NULL)
				{
					m_nCurrentAttackID ++;
					ret = true;
				}
			}
		}
		else if(command->nCommandType == BATTLE_RECORD_ATTACK_END)
		{
			BattleCommandAttackEnd *p = (BattleCommandAttackEnd *)command;

			if(p->nAttackID >= 0 && p->nAttackID < m_nCurrentAttackID)
			{
				if(m_attackerQueue[p->nAttackID].nDone == 0)
				{
					m_attackerQueue[p->nAttackID].nDone = 1;
					ret = true;
				}
			}
		}
		else if(command->nCommandType == BATTLE_RECORD_TYPE_ATTACK)
		{
			BattleCommandAttack *p = (BattleCommandAttack *)command;

			if(p->nAttackID >= 0 && p->nAttackID < m_nCurrentAttackID)
			{
				if(m_attackerQueue[p->nAttackID].nDone == 0)
				{
					int otherCamp = 1 ^ m_attackerQueue[p->nAttackID].nCampType;
					BattleUnit *target = NULL;
					target = get_unit(otherCamp, p->target.nIndex, false);
					if(target != NULL)
					{
						hurt_unit(target, p->target.nDamage);
						ret = true;
					}
				}
			}
		}
		else if(command->nCommandType == BATTLE_RECORD_LAUNCH)
		{
			BattleCommandLaunch *p = (BattleCommandLaunch *)command;

			for(i = 0;i < (m_nTeamMemberCount + 1);i ++)
			{
				if(m_waitQueue[i] == p->nIndex)
				{
					m_waitQueue[i] = -1;
					m_attackQueue[m_nLaunchCount] = p->nIndex;
					m_nLaunchCount ++;
					ret = true;
					ACE_OS::memset(m_monsterAttackFlag, 0, sizeof(int) * MAX_MONSTER_PER_SECTION);
					m_nCurrentAttackIndex = m_nLaunchCount - 1;
					break;
				}
			}
		}
		else if(command->nCommandType == BATTLE_RECORD_REBORN)
		{
			for(i = 0;i < (m_nTeamMemberCount + 1);i ++)
			{
				m_playerTeam[i].hp = m_playerTeam[i].maxHP;
			}

			init_section();
		}
		else if(command->nCommandType == BATTLE_RECORD_GET_ITEM)
		{
			BattleCommandGetItem *p = (BattleCommandGetItem *)command;

			BattleUnit *unit = get_unit(p->nCampType, p->nIndex, false);

			if(get_item(unit, p->nItemIndex) == 0)
			{
				ret = true;
			}	
		}
		else if(command->nCommandType == BATTLE_RECORD_FALL)
		{
			BattleCommandFall *p = (BattleCommandFall *)command;

			BattleUnit *unit = get_unit(0,p->nIndex, false);
			if(unit != NULL)
			{
				unit->hp = 0;
				ret = true;
			}
		}
		break;
	case BATTLE_STEP_DONE:
		break;
	}

	return ret;
}
*/

bool BattleMgr::process_command(BattleCommand *command)
{
	bool ret = false;

	switch(command->nCommandType)
	{
	case BATTLE_RECORD_TYPE_START:
		{
			//init battle info
			init_battle();
			//init section 0
			init_section(0);

		}
		break;
	case BATTLE_RECORD_TYPE_NEXT_SECTION:
		{
			//next section
			
		}
		break;
	case BATTLE_RECORD_TYPE_ATTACK:
		break;
	case BATTLE_RECORD_LAUNCH:
		break;
	case BATTLE_RECORD_GET_ITEM:
		break;
	case BATTLE_RECORD_ATTACK_START:
		break;
	case BATTLE_RECORD_ATTACK_END:
		break;
	case BATTLE_RECORD_FALL:
		break;
	}

	return ret;
}

void BattleMgr::init_section()
{
	int i;
	for(i = 0;i < (m_nTeamMemberCount + 1);i ++)
	{
		m_waitQueue[i] = i;
		m_attackQueue[i] = -1;

		//reborn die player
		if(m_playerTeam[i].hp == 0)
		{
			m_playerTeam[i].hp = 1;
		}
	}

	m_nLaunchCount = 0;
	m_nCurrentAttackID = 0;
}

BattleUnit *BattleMgr::get_unit(int nCamp, int nIndex, bool isAttack)
{
	//int offset = 0;
	BattleUnit *unit = NULL;
	int i;
	if(nCamp == 0)
	{
		int s = 0;
		int e = 0;
		if(isAttack)
		{
			if(m_nCurrentAttackIndex == (m_nLaunchCount - 1))
			{
				s = -1;
			}
			else 
			{
				s = m_nCurrentAttackIndex;
			}
			e = m_nLaunchCount - 1;
		}
		else
		{
			s = 0;
			e = m_nLaunchCount;
		}
		for(i = s;i < e;i ++)
		{
			int tmp_idx = i;
			if(tmp_idx < 0)
			{
				tmp_idx += m_nLaunchCount;
			}
			if(m_attackQueue[tmp_idx] == nIndex)
			{
				unit = &m_playerTeam[nIndex];
				if(isAttack)
				{
					m_nCurrentAttackIndex = (i + 1) % m_nLaunchCount;
				}
				break;
			}
		}
	}
	else if(nCamp == 1)
	{
		nIndex = nIndex - 1;
		if(nIndex >= 0 && nIndex < m_sectionList[m_nCurrentSection].nMonsterCount)
		{
			if(isAttack)
			{
				if(m_monsterAttackFlag[nIndex] == 0)
				{
					m_monsterAttackFlag[nIndex] = 1;
					unit = &m_sectionList[m_nCurrentSection].monsterList[nIndex];
				}
			}
			else
			{
				unit = &m_sectionList[m_nCurrentSection].monsterList[nIndex];
			}
		}
	}

	if(unit != NULL && unit->hp == 0)
	{
		unit = NULL;
	}

	return unit;
}

bool BattleMgr::can_end_section()
{
	int i;
	for(i = 0;i < m_sectionList[m_nCurrentSection].nMonsterCount;i ++)
	{
		if(m_sectionList[m_nCurrentSection].monsterList[i].hp > 0)
		{
			return false;
		}
	}

	for(i = 0;i < m_nCurrentAttackID;i ++)
	{
		if(m_attackerQueue[i].nDone == 0)
		{
			return false;
		}
	}

	return true;
}

void BattleMgr::reset_stage()
{
	int i, j;
	for(i = 0;i < (m_nTeamMemberCount + 1);i ++)
	{
		m_playerTeam[i].maxHP = m_playerTeam[i].hp = m_playerTeam[i].originalHP;
		m_playerTeam[i].maxDamage = m_playerTeam[i].damage = m_playerTeam[i].originalDamage;
	}

	for(i = 0;i < m_nSectionCount;i ++)
	{
		for(j = 0;j < m_sectionList[i].nMonsterCount;j ++)
		{
			m_sectionList[i].monsterList[j].maxHP = m_sectionList[i].monsterList[j].hp = m_sectionList[i].monsterList[j].originalHP;
			m_sectionList[i].monsterList[j].maxDamage = m_sectionList[i].monsterList[j].damage = m_sectionList[i].monsterList[j].originalDamage;
		}

		for(j = 0;j < m_sectionList[i].nItemCount;j ++)
		{
			m_sectionList[i].itemList[j].used = 0;
		}
	}
}

void BattleMgr::hurt_unit(BattleUnit *unit, int damage)
{
	unit->hp = unit->hp - damage;

	if(unit->hp <= 0)
	{
		unit->hp = 0;
		unit->maxHP = unit->originalHP;
		unit->maxDamage = unit->originalDamage;
	}
	else if(unit->hp > unit->maxHP)
	{
		unit->hp = unit->maxHP;
	}
}

int BattleMgr::get_item(BattleUnit *unit, int itemIdx)
{
	int tmp_item_index = itemIdx - 1;
	int ret = -1;
	int i;

	if(unit != NULL)
	{
		if(tmp_item_index >= 0 && tmp_item_index < m_sectionList[m_nCurrentSection].nItemCount)
		{
			BattleItem *item = &m_sectionList[m_nCurrentSection].itemList[tmp_item_index];

			if(item->used == 0)
			{
				float tmp_v = 0.0f;
				float tmp_s = 0.0f;
				for(i = 0;i < item->res->m_propertyList.unCount;i ++)
				{
					if(item->res->m_propertyList.list[i].unPropertyID == PROPERTY_ID_DAMAGE)
					{
						tmp_v = (float)unit->originalDamage;
						tmp_s = 1.0f;

						if(item->res->m_propertyList.list[i].unType == 1)
						{
							tmp_s += item->res->m_propertyList.list[i].fValue;
						}
						else
						{
							tmp_v += item->res->m_propertyList.list[i].fValue;
						}

						unit->maxDamage = (int)(tmp_s * tmp_v);
					}
					else if(item->res->m_propertyList.list[i].unPropertyID == PROPERTY_ID_HP)
					{
						tmp_v = (float)unit->originalHP;
						tmp_s = 1.0f;

						if(item->res->m_propertyList.list[i].unType == 1)
						{
							tmp_s += item->res->m_propertyList.list[i].fValue;
						}
						else
						{
							tmp_v += item->res->m_propertyList.list[i].fValue;
						}

						unit->maxHP = (int)(tmp_s * tmp_v);
					}
				}

				if(item->res->m_fDamagePercent != 0.0f)
				{
					int t = (int)(unit->maxHP * item->res->m_fDamagePercent);

					hurt_unit(unit, t);
				}

				item->used = 1;
				ret = 0;
			}
		}
	}

	return ret;
}