#include"guild_club.h"
#include "money_operator.h"
#include"guild_asist.h"
#include "systemMessage.h"
#include"takeGoods.h"
#include"map_src.h"
extern map<string, GuildFeastConf_T> feastId_2_feastConf;

extern map<string,Map_Src*> mapId_connect_map;
extern char g_out_buf[20480];
extern int shengyanDouble;
extern map<string, Hero*> heroId_to_pHero;

//盛宴到期处理
static void treat_timer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	Guild *guild=(Guild*) think->target;
	char *guildClubId=think->targetId;
	// GuildClub *club = (GuildClub *)think->target;
	GuildClub *club = guild->getGuildClub(guildClubId);
	if (club == NULL)
	{
		return;
	}
	//结束盛宴
	club->end_feast();

	guild->deleteGuildClub(guildClubId);
}
GuildClub::GuildClub(void)
{
	invitedPerson.clear();		
	strncpy(invitePerson,"0",IDL + 1);
	strncpy(typeId,"0",IDL + 1);
	joinMoney=0;				//赴宴者获得金钱值
	joinGlory=0;				//赴宴者获得帮贡值
	joinReputation=0;			//赴宴者获得声望值
	mapNow=NULL;					//地图实例
}

void GuildClub::setIdentity(char *_identity)
{
	strncpy(identity,_identity,sizeof(identity));
}

char *GuildClub::getIdentity(void)
{
	return identity;
}

Map_Inform *GuildClub::getMap(void)
{
	return mapNow;
}

void GuildClub::setMap(Map_Inform *_mapNow)
{
	if (_mapNow ==NULL)
	{
		cout<<"艹，怎么地图用空了 jolly"<<endl;
	}
	else
	{
		mapNow=_mapNow;
	}
}
/* int GuildClub::enter(Hero *hero)
{
	if (clubMap == NULL)
	{
		cout<<"[GuildClubWarn]: Club has not been inited when the hero wants to enter club!"<<endl;
		return -1;
	}
	char* heroId = hero->getIdentity();
	
	if (herosInRoom.find(heroId) != herosInRoom.end())
	{
		cout<<"[GuildClubWarn]: hero is already in guild club when he wants to enter club!"<<endl;
		return -2;
	}
	
	char mapNewId[32];

	//切地图的通信消息
	char msg[400];
	//保存切图前的点
	char* oldMapId = hero->getMapId();
	if (strlen(oldMapId) > 8)
	{
		//如果在动态衍生图（副本图，阵营战图，帮战图）中，就设置为主城
		oldMapId = (char*)"map_001";
		Point beforePt(8002, 3771);
		hero->setBeforePiexPt(beforePt);
	} else {
		hero->setBeforePiexPt(hero->getLocation());
	}
	hero->setMainSrc(oldMapId);	//设置跳转前的地图,便于返回；
	//切入地图诞生点
	Point targetPt = clubMap->getEntPt();
	
	hero->quit_scene();
	hero->setMap(clubMap);
	
	char *nowMapId = clubMap->getMapId();
	int pos = findChar(nowMapId, '_', strlen(nowMapId));
	sub_str(mapNewId, nowMapId, 0, pos);
	sprintf(msg, "2,%d,1,%s,%d,%d", CHANGE_SCENE,mapNewId, targetPt._x, targetPt._y);
	send_msg(hero->getFd(),msg); 
	
	hero->setLocation(targetPt);	
	hero->enter_scene();
	herosInRoom.insert(pair<string, Hero*>(hero->getIdentity(), hero));
	return 0;
}

int GuildClub::exit(Hero *hero)
{
	char* mainSrcId;   
	Map_Src *mainSrcMap;
	char* heroId = hero->getIdentity();
	if (herosInRoom.find(heroId) == herosInRoom.end())
	{
		cout<<"[GuildClubWarn] hero is not in guild club when he want to exit guild!"<<endl;
		return -1;
	}
	mainSrcId = hero->getMainSrc();	
	map<string,Map_Src*>::iterator mainSrc_it;
	mainSrc_it = mapId_connect_map.find(mainSrcId);
	if(mainSrc_it == mapId_connect_map.end())
	{
		//没有原来的地图
		cout<<"when hero out guild war map can't find his srcMap!"<<endl;
		return -2;
	}
	mainSrcMap = mainSrc_it->second;
	//退出房间地图
	quit_scene(hero, hero->getMap());
	//进入原来地图
	enter_scenes(hero, mainSrcMap, 3);
	herosInRoom.erase(heroId);
	return 0;
}
 */
/***********************************************************
 * int2str - 整型数转换成固定长度的字符串，位数不够的补零
 *author: bison
 * @val: 所要转换的整形数
 * @figure: 所要转换成的字符串位数
 * Return: 返回转换的字符串。如figure为4时,23则转成"0023"
 ***********************************************************/
static string int2str(int val, int figure)
{
	string str;
	while(figure--)
	{
		str.insert(str.begin(), (char)('0' + val % 10));
		val /= 10;
	}
	return str;
}

//请客
void GuildClub::treat(Hero *hero, char* _typeId,Guild *guild,char *_identity)
{
	mapNow=hero->getMap();
	if (hero==NULL||_typeId==NULL || mapNow==NULL)
	{
		return;
	}

	char* heroId = hero->getIdentity();
	map<string,GuildFeastConf_T>::iterator it_feastConf;
	it_feastConf = feastId_2_feastConf.find(_typeId);
	if (it_feastConf == feastId_2_feastConf.end())
	{
		cout<<"[GuildClubWarn] there is no treat of this class "<<_typeId<<" when the hero want to give a treat!"<<endl;
		return;
	}
	else
	{
		Money *heroMoney = hero->getMoney();
		cout<<"[GuildClubWarn] feast cost is "<<it_feastConf->second.cost<<" and hero current gold is "<<heroMoney->money_getGold()<<endl;
		TakeGoods *dish=NULL;
		dish=mapNow->olderKandy(_typeId,_identity,hero->getIdentity(),hero->getNickName());
		if (dish!=NULL)
		{			
			if (useGold(hero,it_feastConf->second.cost))
			{			
				beginTime=myTime.tv_sec;
				joinMoney=it_feastConf->second.joinMoney;
				joinGlory=it_feastConf->second.joinGlory;
				joinReputation=it_feastConf->second.joinReputation;
				//可以请客,修改各种数据
				strncpy(invitePerson,hero->getIdentity(),IDL);			//宴请者,自己
				invitedPerson.insert(hero->getIdentity());				//自己宴请,不能再领取			
				strncpy(typeId,_typeId,IDL + 1);						//宴请的类型id,用来做领取的标示
				strncpy(identity,dish->getId(),sizeof(identity));
				totalTime=it_feastConf->second.lastTime;
				//开个定时器，时间到了结束
				ext_ev_timer_init(&feastTimer, treat_timer_cb, it_feastConf->second.lastTime, 0, guild, dish->getId());
				ev_timer_start(loops, &feastTimer);
				//发送消息，邀请来赴宴
				char sysMessage[1024]={0};
				if (strcmp(_typeId,"item016")==0)
				{
					snprintf(sysMessage,sizeof(sysMessage),"%s,%d,%d,%s,%s,%d,%d","xf022",1,1,hero->getNickName(),hero->getIdentity(),0,0);	
				}
				else if (strcmp(_typeId,"item017")==0)
				{
					snprintf(sysMessage,sizeof(sysMessage),"%s,%d,%d,%s,%s,%d,%d","xf023",1,1,hero->getNickName(),hero->getIdentity(),0,0);		
				}
				else if (strcmp(_typeId,"item018")==0)
				{
					snprintf(sysMessage,sizeof(sysMessage),"%s,%d,%d,%s,%s,%d,%d","xf024",1,1,hero->getNickName(),hero->getIdentity(),0,0);		
				}
				else if (strcmp(_typeId,"item019")==0)
				{
					snprintf(sysMessage,sizeof(sysMessage),"%s,%d,%d,%s,%s,%d,%d","xf025",1,1,hero->getNickName(),hero->getIdentity(),0,0);	
				}		
				cout<<"sysMessage:"<<sysMessage<<endl;
				systemSendMssage(hero,sysMessage,3);
				
				//给自己发消息获得奖励
				snprintf(g_out_buf,sizeof(g_out_buf),"12,29,1,%d,%d,%d,%d",it_feastConf->second.hostMoney*shengyanDouble,it_feastConf->second.hostGlory*shengyanDouble,it_feastConf->second.hostReputation*shengyanDouble,it_feastConf->second.contb*shengyanDouble);
				send_msg(hero->getFd(),g_out_buf);
				increaseBoundGameMoney(hero,it_feastConf->second.hostMoney*shengyanDouble);					//增加绑定游戏币
				// guild->addGloryOfHero(heroId, it_feastConf->second.hostGlory*shengyanDouble);					//增加玩家帮贡
				addMyGuildGlory(guild->getName(), heroId, it_feastConf->second.hostGlory*shengyanDouble);
				guild->addHeroContb(heroId, it_feastConf->second.contb*shengyanDouble);						//增加请宴者帮派贡献度
				hero->addPrestigeValue(it_feastConf->second.hostReputation*shengyanDouble);					//增加玩家帮派声望			
				// guild->send_msg_feast();
				hero->updataSingleTarget(4,7);
			}
		}
	}
}

//系统请客
void GuildClub::sysTreat(Map_Inform *_mapNow,char* _typeId,Guild *guild)
{
	if (_mapNow==NULL||_typeId==NULL || guild==NULL)
	{
		cout<<"GuildClub::sysTreat the argument is NULL:"<<endl;
		return;
	}
	
	mapNow=_mapNow;
	map<string,GuildFeastConf_T>::iterator it_feastConf;
	it_feastConf = feastId_2_feastConf.find(_typeId);
	if (it_feastConf == feastId_2_feastConf.end())
	{
		cout<<"[GuildClubWarn] there is no treat of this class "<<_typeId<<" when the hero want to give a treat!"<<endl;
		return;
	}
	else
	{				
		TakeGoods *dish=NULL;
		// dish=mapNow->olderKandy(_typeId,hero->getIdentity(),hero->getNickName());
		
		/*add chenzhen 203102021559 系统点菜*/
		dish = mapNow->systemTreatAsist();	
		
		
		if(dish == NULL)
		{
			return;
		}
		
		/*系统请客失败*/
		if(!((Map_Src*)mapNow)->systemTreat(dish))
		{
			return;
		}
		
		beginTime=myTime.tv_sec;
		joinMoney=it_feastConf->second.joinMoney;
		joinGlory=it_feastConf->second.joinGlory;
		joinReputation=it_feastConf->second.joinReputation;
		//可以请客,修改各种数据
		strncpy(invitePerson,"123456",IDL);			//宴请者,自己		
		strncpy(typeId,_typeId,IDL + 1);						//宴请的类型id,用来做领取的标示
		strncpy(identity,dish->getId(),sizeof(identity));
		totalTime=it_feastConf->second.lastTime;
		//开个定时器，时间到了结束
		ext_ev_timer_init(&feastTimer, treat_timer_cb, it_feastConf->second.lastTime, 0, guild, dish->getId());
		ev_timer_start(loops, &feastTimer);
		
		// guild->send_msg_feast();		
	}
	cout<<"GuildClub::sysTreat fun end:"<<endl;
	
}

void GuildClub::end_feast(void)
{	
	ev_timer_stop(loops,&feastTimer);
	strncpy(invitePerson,"0",IDL + 1);
	strncpy(typeId,"0",IDL + 1);
	invitedPerson.clear();
	{
		std::set<string> tmp;
		invitedPerson.swap(tmp);
	}
	TakeGoods *dish=NULL;
	dish=mapNow->getTakeObj(identity);
	if (dish==NULL)
	{
		return;
	}
	else
	{
//		dish->disperMsg();
		mapNow->delOneDish(identity);
	}
}

GuildClub::~GuildClub(void)
{
	ev_timer_stop(loops,&feastTimer);
	mapNow=NULL;
	invitedPerson.clear();
	{
		std::set<string> tmp;
		invitedPerson.swap(tmp);
	}
}

//赴宴
void GuildClub::joinDinner(Hero *hero,Guild *guild)
{
	if (hero==NULL)
	{
		return;
	}
	if (guild==NULL)
	{
		return;
	}

	set<string>::iterator it;
	it=invitedPerson.find(hero->getIdentity());
	if (it!=invitedPerson.end())
	{
		msg_error(g_out_buf,78);
		send_msg(hero->getFd(),g_out_buf);
	}
	else
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"12,29,2,%d,%d,%d",joinMoney*shengyanDouble,joinGlory*shengyanDouble,joinReputation*shengyanDouble);
		send_msg(hero->getFd(),g_out_buf);
		//可以开宴	
		increaseBoundGameMoney(hero,joinMoney*shengyanDouble);
		// guild->addGloryOfHero(hero->getIdentity(), joinGlory*shengyanDouble);	
		addMyGuildGlory(guild->getName(), hero->getIdentity(), joinGlory*shengyanDouble);		
		hero->addPrestigeValue(joinReputation*shengyanDouble);			//增加声望
		invitedPerson.insert(hero->getIdentity());
	}	
}

//盛宴是否开始
bool GuildClub::feastStart(void)
{
	if (strcmp(invitePerson,"0")==0)
	{			
		msg_error(g_out_buf,104);
		send_msg(pg_hero->getFd(),g_out_buf);
		return false;
	}
	else
	{
		return true;
	}
}
//返回剩余时间
int GuildClub::getRemainTime(void)
{
	return totalTime-(myTime.tv_sec-beginTime);
}


//返回看盛宴的玩家
char *GuildClub::getInvitePerson(void)
{
	return invitePerson;
}

bool GuildClub::isThisDish(char *_identity)
{
	if (strcmp(identity,_identity)==0)
	{
		return true;
	}
	else
	{		
		return false;
	}
}

//判断是否可以试用盛宴
bool GuildClub::canEatDish(Hero *hero)
{
	if (hero==NULL)
	{
		return false;
	}
	
	TakeGoods *dish=NULL;
	dish=mapNow->getTakeObj(identity);
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	if (dish->getDishState()==1)
	{
		msg_error(g_out_buf,112);
		send_msg(hero->getFd(),g_out_buf);
		return false;
	}
	
	if (strcmp(hero->getIdentity(),invitePerson)==0)
	{
		msg_error(g_out_buf,97);
		send_msg(hero->getFd(),g_out_buf);
		return false;
	}
	
	set<string>::iterator it;
	it=invitedPerson.find(hero->getIdentity());
	if (it==invitedPerson.end())
	{
		return true;
	}
	else
	{
		msg_error(g_out_buf,78);
		send_msg(hero->getFd(),g_out_buf);
		return false;
	}
}
