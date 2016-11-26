#include"guild_club_assist.h"

map<string, GuildClub*> guildName_2_guildClub;
map<string, GuildClub*> guildId_2_guildClub;

extern map<string,Map_Src*> mapId_connect_map;
string guildClubMapId;

bool createOneGuildClub(char* guildId, char* guildName)
{
	// Map_Src  *clubMap = NULL;	
	// map<string,Map_Src*>::iterator it_map;
	
	// it_map = mapId_connect_map.find(guildClubMapId);
	// if(it_map == mapId_connect_map.end()){
		// return false;
	// }
	// clubMap = it_map->second;
	// Map_Src *scene = NULL;
	// 调用地图里面的复制方法
	// static int i = 0;
	// scene = clubMap->copyMap(i++);
	
	// GuildClub *club = new GuildClub(guildId, guildName, scene);
	
	// guildName_2_guildClub.insert(pair<string, GuildClub*>(guildName, club));
	// guildId_2_guildClub.insert(pair<string, GuildClub*>(guildId, club));
	// return true;
	
}

int enterGuildClub(Hero *hero)
{	
	// Guild* guild = hero->getGuild();
	// if (guild == NULL)
	// {
		// 玩家没有帮派
		// cout<<"[BisonWarn] hero can't enter guildRoom because he doesn't join a guild!"<<endl;
		// return 1;
	// }
	
	// char* guildId = guild->getId();
	// map<string, GuildClub*>::iterator it_club;
	// it_club = guildId_2_guildClub.find(guildId);
	// if (it_club == guildId_2_guildClub.end())
	// {
		// 帮派没有对应的帮派房间
		// cout<<"[BisonWarn] hero can't enter guildRoom because there isn't a guildRoom bound with his guild!"<<endl;
		// return 2;
	// }
	
	// GuildClub *club = it_club->second;
	
	// int ret = club->enter(hero);
	// return ret;
}

//注：特殊情况下：玩家在帮派房间中离开帮派或者被踢出帮派，要先把玩家强制退出club才能做离开guild操作，否则没guild索引玩家就离不开club了
int exitGuildClub(Hero *hero)
{
	// Guild* guild = hero->getGuild();
	// if (guild == NULL)
	// {
		// 玩家没有帮派
		// cout<<"[BisonWarn] hero can't exit guildRoom because he isn't in a guild!"<<endl;
		// return 1;
	// }
	
	// char* guildId = guild->getId();
	// map<string, GuildClub*>::iterator it_club;
	// it_club = guildId_2_guildClub.find(guildId);
	// if (it_club == guildId_2_guildClub.end())
	// {
		// 帮派没有对应的帮派房间
		// cout<<"[BisonWarn] hero can't exit guildRoom because there isn't a guildRoom bound with his guild!"<<endl;
		// return 2;
	// }
	
	// GuildClub *club = it_club->second;
	
	// int ret = club->exit(hero);
	// return ret;
}