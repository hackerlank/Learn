#ifndef _CAMP_LEADER_AND_CHIEF_H_
#define _CAMP_LEADER_AND_CHIEF_H_

#include "guild.h"
#include "guild_asist.h"
#include "camp_res_war.h"

extern map<INT, string> guildWarScore_2_guildId[4];

extern map<string, int> guildId_2_guildWarScore[4];

typedef struct GuildWarScoreRecord_S
{
	int isUsedFlag;
	
	char guildId[51];
	
	int guildScore;
	
} GuildWarScoreRecord_T;

typedef struct CampLeaderAndChiefSaveData_S
{
	char leaderGuildId[4][51];			//盟主和统领所属帮派
	char leaderId[4][51];				//盟主和统领所属帮派
	
	char campNotices[3][1201];

	GuildWarScoreRecord_T scoreData[4][400];
	CampLeaderAndChiefSaveData_S()
	{
		memset(leaderGuildId, 0, sizeof leaderGuildId);
		memset(leaderId, 0, sizeof leaderId);
		memset(campNotices, 0, sizeof campNotices);
		memset(scoreData, 0, sizeof scoreData);
	}
	
	void init(struct CampLeaderAndChiefSaveData_S *campData)
	{
		memcpy(leaderGuildId, campData->leaderGuildId, sizeof leaderGuildId);
		memcpy(leaderId, campData->leaderId, sizeof leaderId);
		memcpy(campNotices, campData->campNotices, sizeof campNotices);
		memcpy(scoreData, campData->scoreData, sizeof scoreData);
	}
	
	void clear(int flag)
	{
		if (flag == 0)
		{
			memset(leaderGuildId, 0, sizeof leaderGuildId);
		} else if (flag == 1) {
			memset(leaderId, 0, sizeof leaderId);
		} else if (flag == 2)
		{
			memset(campNotices, 0, sizeof campNotices);
		} else {
			memset(scoreData, 0, sizeof scoreData);
		}
	}
	
	
}CampLeaderAndChiefSaveData_T;

extern CampLeaderAndChiefSaveData_T newCampData;

int addGuildWarScoreByName(char* guildName, int addScore);
int clearOneGuildWarScore(char* guildId);
void clearLastWeekGuildWarScore();
void chooseLeaderAndChief();
void rankGuildWarScore();

void save_leader_and_chief_to_mem();
void init_leader_and_chief_from_mem();

void viewCampLeader(char* buffer);
void viewGuildScoreList(char* buffer);
void changeCampNotice(char* buffer);
#endif