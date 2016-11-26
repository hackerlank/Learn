
#include "camp_leader_and_chief.h"
#include "my_mem_group.h"
#include"dictionary_asist.h"
#include"camp_war_reward.h"
#include"statuaryAsist.h"
// #define QUICK_TEST_CAMP_LEADER_AND_CHIEF_VESION

map<string, int> guildId_2_guildWarScore[4];
map<INT, string> guildWarScore_2_guildId[4];


extern MyMemGroup* mem_group;

CampLeaderAndChiefSaveData_T newCampData;

string CampDataSaveKey = "CampDataSaveKey_VERSION_0015";

#if defined(QUICK_TEST_CAMP_LEADER_AND_CHIEF_VESION)
int testGameTimes = 0;
#endif

int addGuildWarScoreByName(char* guildName, int addScore)
{
#if defined(QUICK_TEST_CAMP_LEADER_AND_CHIEF_VESION)
	if (testGameTimes == 0)
	{
		clearLastWeekGuildWarScore();
	}
	
	testGameTimes++;
#endif

	Guild* guild = getGuildWithName(guildName);
	if (guild == NULL)
	{
		return 1;
	}
	
	int scoreValue = addScore * 10000;
	
	char *guildId = guild->getId();
	int guildCamp = guild->getCamp();
	int campRank = getGuildRankInCamp(guildId, guildCamp);
	int campRankValue = 10000 - campRank;
	int allRank =  getGuildRankInCamp(guildId, 3);
	int allRankValue = 10000 - allRank;
	map<string, int>::iterator it_camp = guildId_2_guildWarScore[guildCamp].find(guildId);
	if (it_camp == guildId_2_guildWarScore[guildCamp].end())
	{
		//为第一次加
		guildId_2_guildWarScore[guildCamp].insert(pair<string, int>(guildId, scoreValue + campRankValue));
		guildId_2_guildWarScore[3].insert(pair<string, int>(guildId, scoreValue + allRankValue));
	} else {
		it_camp->second += addScore;
		map<string, int>::iterator it_allCamp = guildId_2_guildWarScore[3].find(guildId);
		if (it_allCamp != guildId_2_guildWarScore[3].end())
		{
			it_allCamp->second += scoreValue;
		}
	}

	// test
#if defined(QUICK_TEST_CAMP_LEADER_AND_CHIEF_VESION)	
	rankGuildWarScore();
	if (testGameTimes == 7)
	{
		chooseLeaderAndChief();
		testGameTimes = 0;
	}
#endif	
	return 0;
}

int clearOneGuildWarScore(char* guildId)
{
	guildId_2_guildWarScore[0].erase(guildId);
	guildId_2_guildWarScore[1].erase(guildId);
	guildId_2_guildWarScore[2].erase(guildId);
	guildId_2_guildWarScore[3].erase(guildId);
	return 0;
}

void clearLastWeekGuildWarScore()
{
	for (int i = 0; i < 4; i++)
	{
		guildId_2_guildWarScore[i].clear();
		guildWarScore_2_guildId[i].clear();
		// memset(newCampData.leaderGuildId[i], 0, sizeof newCampData.leaderGuildId[i]);
	}
}

void rankGuildWarScore()
{
	map<string, int>::iterator it_src;
	for (int i = 0; i < 4; i++)
	{
		guildWarScore_2_guildId[i].clear();
		for (it_src = guildId_2_guildWarScore[i].begin(); it_src != guildId_2_guildWarScore[i].end(); it_src++)
		{
			guildWarScore_2_guildId[i].insert(pair<INT, string>(it_src->second, it_src->first));
		}
	}
	
}

void chooseLeaderAndChief()
{
	for (int j = 0; j < 4; j++)
	{
		char *guildId = newCampData.leaderGuildId[j];
		Guild *guild = getGuildWithId(guildId);
		if (guild != NULL)
		{
			guild->setCampTitle((1 + (j >= 3)), 1);
		}
		
		Hero *campHero = heroid_to_hero(newCampData.leaderId[j]);		
		
			
		if(!campHero)
		{
			continue;
		}
		
		if(j < 3)
		{		
			campHero->cutTitle(CAMP_LEADER_TITLE);
		}
		else
		{
			campHero->cutTitle(CAMP_CHIEF_TITLE);				
		}
		//清除leader头衔
		//wait to do by chenzhen
	}
	
	
	
	newCampData.clear(0);			//上届清掉
	newCampData.clear(1);			//上届公告清掉
	newCampData.clear(2);			//上届公告清掉
	
	//摧毁盟主雕像
	string titleStr = "SH_";
	titleStr += CAMP_CHIEF_TITLE;
	destoryStatuary(const_cast<char*>((titleStr).c_str()));
	string campChiefId;
	for (int i = 0; i < 4; i++)
	{
		map<INT, string>::iterator it = guildWarScore_2_guildId[i].begin();
		if (it != guildWarScore_2_guildId[i].end())
		{
			strncpy(newCampData.leaderGuildId[i], it->second.c_str(), sizeof (newCampData.leaderGuildId[i]));
			Guild* guild = getGuildWithId(newCampData.leaderGuildId[i]);
			{
				guild->setCampTitle(1 + (i >= 3), 0);
			}
			
			char* leaderId = guild->getPresidId();
			strncpy(newCampData.leaderId[i], leaderId, sizeof newCampData.leaderId[i]);
			Hero* leaderHero = heroid_to_hero(leaderId);

			if(i == 3)
			{
				campChiefId = leaderId;
			}
			
			if(!leaderHero)
			{
				continue;
			}
		
			if(i < 3)
			{		
				leaderHero->addTitle(CAMP_LEADER_TITLE);
			}
			else
			{
				leaderHero->addTitle(CAMP_CHIEF_TITLE);				
				
			}
		}
	}
	
	//建立盟主雕像
	titleStr = "SH_";
	titleStr += CAMP_CHIEF_TITLE;
	setUpStatuary(const_cast<char*>(campChiefId.c_str()),const_cast<char*>((titleStr).c_str()));
}

void init_leader_and_chief_from_mem()
{
	int size = 0;
	int where = 0;
	CampLeaderAndChiefSaveData_T *campData = (CampLeaderAndChiefSaveData_T*)mem_group->get_data(CampDataSaveKey, &size, &where, PUBLIC_MEMCACHED_INDEX);
	if (campData == NULL)
	{
		return;
	}
	
	newCampData.init(campData);
	free(campData);
	
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 400; i++)
		{
			if (newCampData.scoreData[j][i].isUsedFlag == 1)
			{
				guildId_2_guildWarScore[j].insert(pair<string, int>(newCampData.scoreData[j][i].guildId, newCampData.scoreData[j][i].guildScore));
			}
			
		}
	}
	rankGuildWarScore();
}

void save_leader_and_chief_to_mem()
{
	newCampData.clear(3);
	
	map<string, int>::iterator it;
	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		for (it = guildId_2_guildWarScore[i].begin(); it != guildId_2_guildWarScore[i].end(); it++)
		{
			newCampData.scoreData[i][k].isUsedFlag = 1;
			newCampData.scoreData[i][k].guildScore = it->second;
			strncpy(newCampData.scoreData[i][k].guildId, it->first.c_str(), sizeof (newCampData.scoreData[i][k++].guildId));
		}
	}
	
	bool isSuccess = mem_group->set_data(CampDataSaveKey.c_str(), (char*)&newCampData, sizeof(newCampData), PUBLIC_MEMCACHED_INDEX);
	if (!isSuccess)
	{
		cout<<"save_leader_and_chief_to_mem save failed!!!"<<endl;
	}
}

void viewCampLeader(char* buffer)
{
	int camp = pg_hero->getCamp();
	char msg[1024] = {0};
	sprintf(msg, "38,0,%s", newCampData.campNotices[camp]);
	bool isLeader = false;
	for (int i = 0; i < 4; i++)
	{
		char *guildId = newCampData.leaderGuildId[i];
		Guild* guild = getGuildWithId(guildId);
		if (guild == NULL)
		{
			sprintf(msg+strlen(msg), ",");
			continue;
		}
		
		char *leaderId = guild->getPresidId();
		Hero* hero = heroid_to_hero(leaderId);
		if (hero == NULL)
		{
			sprintf(msg+strlen(msg), ",%s", guild->getPresidNickName(0));
			continue;
		}
		
		if (!strcmp(leaderId, pg_hero->getIdentity()))
		{
			isLeader = true;
		}
		sprintf(msg + strlen(msg), ",%s", hero->getNickName());
	}
	
	sprintf(msg + strlen(msg), ",%d", isLeader);
	
	send_msg(pg_hero->getFd(), msg);
}

void viewGuildScoreList(char* buffer)
{
	char msg[20480] = {0};
	char temp[20480] = {0};
	int listNum = 0;
	map<INT, string>::iterator it_guild;
	for (it_guild = guildWarScore_2_guildId[3].begin(); it_guild != guildWarScore_2_guildId[3].end(); it_guild++)
	{
		char *guildId = const_cast<char*>(it_guild->second.c_str());
		Guild* guild = getGuildWithId(guildId);
		if (guild != NULL)
		{
			listNum++;
			int srcScore = it_guild->first;
			int realScore = srcScore / 10000;
			int rank = 10000 - srcScore % 10000;
			sprintf(temp + strlen(temp), ",%s,%d,%d,%d", guild->getName(), guild->getCamp(), rank, realScore);
		}
		
	}
	
	sprintf(msg, "38,2,%d%s", listNum, temp);
	send_msg(pg_hero->getFd(), msg);
}

void changeCampNotice(char* buffer)
{
	char *notices;
	char msg[1024] = {0};
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR(notices);
	
	if (isHaveIllSymbol(notices) == 1)
	{
		sprintf(msg, "38,1,0,1");
		send_msg(pg_hero->getFd(), msg);
		return;
	}
  
	if (isHaveDirtyWords(notices) == 1)
	{
		sprintf(msg, "38,1,0,2");
		send_msg(pg_hero->getFd(), msg);
		return;
	}
	
	int camp = pg_hero->getCamp();
	
	Guild* guild = getGuildWithId(newCampData.leaderGuildId[camp]);
	if (guild != NULL)
	{
		char *leaderId = guild->getPresidId();
		if (strcmp(pg_hero->getIdentity(), leaderId) == 0)
		{
			memset(newCampData.campNotices[camp], 0, sizeof newCampData.campNotices[camp]);
			strncpy(newCampData.campNotices[camp], notices, sizeof newCampData.campNotices[camp]);
			sprintf(msg, "38,1,1");
		} else {
			sprintf(msg, "38,1,0,3");
		}
	} else {
		sprintf(msg, "38,1,0,4");
	}
	
	send_msg(pg_hero->getFd(), msg);
}
