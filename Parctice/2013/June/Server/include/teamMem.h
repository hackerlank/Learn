#ifndef TEAM_MEM_H
#define TEAM_MEM_H
#include<string.h>
#include"hero.h"
const int TEAM_ID_LEN = 50;
typedef struct TeamMemInfo
{
	char memId[TEAM_ID_LEN + 1];
	char nickName[TEAM_ID_LEN + 1];
	char party[TEAM_ID_LEN + 1];
	size_t level,lifeVal,lifeUpperVal,magic,magicUpperVal;
	bool onLine;     //真为在线
	
	TeamMemInfo(const char *_memId,const char *_nickName = NULL,const char *_party = NULL,size_t _level = 0,size_t _lifeVal = 0,\
	size_t _lifeUpperVal = 0,size_t _magic = 0,size_t _magicUpperVal = 0,bool _onLine = true)
	{
		initVal();
		
		if(_memId)
		{
			strncpy(memId,_memId,strlen(_memId));
		}				
		
		if(_nickName)
		{
			strncpy(nickName,_nickName,strlen(_nickName));
		}
		
		if(_party)
		{
			strncpy(party,_party,strlen(_party));
		}
		
		level = _level;
		lifeVal = _lifeVal;
		lifeUpperVal = _lifeUpperVal;
		magic = _magic;
		magicUpperVal = _magicUpperVal;
		onLine = _onLine;
	}
	
	TeamMemInfo(const TeamMemInfo& teamMemInfo)
	{
		assignVal(teamMemInfo);	
	}
	
	TeamMemInfo& operator= (const TeamMemInfo& teamMemInfo)
	{		
		assignVal(teamMemInfo);		
		return *this;
	}
	
	bool operator< (const TeamMemInfo& teamMemInfo) const
	{
		if(strncmp(memId,teamMemInfo.memId,strlen(memId)) < 0)
		{
			return true;
		}
		return false;
		return strcmp(memId,teamMemInfo.memId);
	}	
	
	bool operator> (const TeamMemInfo& teamMemInfo) const
	{
		if(strncmp(memId,teamMemInfo.memId,strlen(memId)) > 0)
		{
			return true;
		}
		return false;
	}	
	
	bool operator== (const TeamMemInfo& teamMemInfo) const
	{
		if(strcmp(memId,teamMemInfo.memId) == 0)
		{
			return true;
		}
		return false;
	}
	
	void assignVal(const Hero *teamHero)
	{	
		if(!teamHero)
		{
			cout<<"assignVal(const Hero *teamHero) the teamHero is NULL:"<<endl;
			return;
		}
		
		initVal();		
		strncpy(memId,teamHero->getIdentity(),strlen(teamHero->getIdentity()));
		strncpy(nickName,teamHero->getNickName(),strlen(teamHero->getNickName()));
		strncpy(party,const_cast<Hero*>(teamHero)->getParty(),strlen(const_cast<Hero*>(teamHero)->getParty()));
		level = const_cast<Hero*>(teamHero)->getGradeNow();
		lifeVal = const_cast<Hero*>(teamHero)->getLifeVal();
		lifeUpperVal = const_cast<Hero*>(teamHero)->getLifeUpperVal();
		magic = const_cast<Hero*>(teamHero)->getMagicVal();
		magicUpperVal = const_cast<Hero*>(teamHero)->getMagicUpperVal();
		onLine = true;
	}

private:	
	void initVal()
	{
		memset(memId,'\0',sizeof(memId));
		memset(nickName,'\0',sizeof(nickName));
		memset(party,'\0',sizeof(party));
		onLine = false;
		level = 0;
		lifeVal = 0;
		lifeUpperVal = 0;
		magic = 0;
		magicUpperVal = 0;
	}
	
	void assignVal(const TeamMemInfo& teamMemInfo)
	{		
		initVal();
		
		strncpy(memId,teamMemInfo.memId,strlen(teamMemInfo.memId));
		
		strncpy(nickName,teamMemInfo.nickName,strlen(teamMemInfo.nickName));
		
		strncpy(party,teamMemInfo.party,strlen(teamMemInfo.party));
		
		level = teamMemInfo.level;
		
		lifeVal = teamMemInfo.lifeVal;
		
		lifeUpperVal = teamMemInfo.lifeUpperVal;
		
		magic = teamMemInfo.magic;
		
		magicUpperVal = teamMemInfo.magicUpperVal;
		
		onLine = teamMemInfo.onLine;
	}
	
}TeamMemInfo;

#endif