#include "GM.h"
using namespace std;
extern set<string>	heroid_to_gm;
extern set<string> freeze_money;
extern set<string> freeWorldTalk;

bool isGM(Hero *hero)
{
	char* identity=hero->getIdentity();
	set<string>::iterator it;
	// for (it=heroid_to_gm.begin();it!=heroid_to_gm.end();it++)
	// {
		// cout<<*it<<endl;
		cout<<"!!!!!!!!!!!!!!!!!"<<endl;
	// }
	cout<<identity<<endl;
	it=heroid_to_gm.find(identity);
	if (it==heroid_to_gm.end())
	{
		cout<<"jolly:you are not a GM,information error GM.cpp 11"<<endl;
		return false;
	}
	else
	{
		return true;
	}
}

bool GM_isLocked(string heroid)
{
	set<string>::iterator it;
	it=freeze_money.find(heroid);
	if (it==freeze_money.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
	
bool isWorldFreeTalk(char *identity)
{
	set<string>::iterator it;
	it=freeWorldTalk.find(identity);
	if (it==freeWorldTalk.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}