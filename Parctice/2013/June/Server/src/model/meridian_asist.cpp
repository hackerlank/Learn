/****************************************************************
 * Filename: meridian_comm.cpp
 * 
 * Description: 经脉系统的操作处理
 *
 * Original Author : bison, 2012-7-16
 *
 ****************************************************************/

#include"meridian.h"
#include"meridian_asist.h"
#include "money_operator.h"
#include"hero.h"
#include"my_time.h"

//玩家属性增加,整合get和set方法
// #define addHeroAttr(hero, Item, val) hero->set##Item(hero->get##Item() + val)

extern struct ev_loop *loops;
extern map<string, Hero*> heroId_to_pHero;

static void meridCalBak(struct ev_loop *loop, ev_timer *think, int revents);

//经脉升级效果，只在内部使用，不提供外部接口
static void upgradeEffect(MERID_TYPE_T now, int level, Hero *hero)
{
	if (now < 0 || now > 7 || level <= 0 || level > 90)
	{
		return;
	}
	if (heroMeridConf.item[now].incType1[level] < 100)
	{
		hero->addAttr(heroMeridConf.item[now].incType1[level], heroMeridConf.item[now].incVal1[level]);
	}
	if (heroMeridConf.item[now].incType2[level] < 100)
	{
		hero->addAttr(heroMeridConf.item[now].incType2[level], heroMeridConf.item[now].incVal2[level]);
	}
#if 0
	switch (now)
	{
	//任脉
	case RENM:
		// addHeroAttr(hero, LifeUpperVal, 320);	//血上限加320
		// addHeroAttr(hero, MagicUpperVal, 320);	//魔上限加320
		hero->addAttr(0, 320);
		hero->addAttr(1, 320);
		break;
	//督脉
	case DUM:
		// addHeroAttr(hero, InAttack, 36);		//内攻 +36
		// addHeroAttr(hero, InHurt, 16);			//内伤 +16
		hero->addAttr(5, 36);
		hero->addAttr(11, 36);
		break;
	//冲脉
	case CHONGM:
		// addHeroAttr(hero, OutAttack, 36);		//外攻 +36
		// addHeroAttr(hero, OutHurt, 16);			//外伤 +16
		hero->addAttr(4, 36);
		hero->addAttr(10, 16);
		break;
	//带脉
	case DAIM:
		// addHeroAttr(hero, OutDefense, 36);		//外防 +36
		// addHeroAttr(hero, InDefense, 36);		//内防 +36
		hero->addAttr(2, 36);
		hero->addAttr(3, 36);
		break;
	//阴维
	case YINW:
		// addHeroAttr(hero, Hited, 1);			//命中 +1
		hero->addAttr(6, 1);
		break;
	//阳维
	case YANGW:
		// addHeroAttr(hero, Crit, 1);			//暴击 +1
		hero->addAttr(9, 1);
		break;
	//阴跷	
	case YINQ:
		// addHeroAttr(hero, Dodge, 1);			//闪避 +1
		hero->addAttr(7, 1);
		break;
	//阳跷
	case YANGQ:
		// addHeroAttr(hero, Tenacity, 1);		//韧性 +1
		hero->addAttr(8, 1);
		break;
	
	default:
		return;
	}
#endif
}

static void upgradeHeroMerid(Hero *hero)
{

	//修炼完成
	Meridian *merid = hero->getMerid();
	merid->upgrade();
	MERID_TYPE_T now = merid->getNow();
	upgradeEffect(now, merid->getLevel(), hero);
	hero->send_msg_att();
	if (now==YANGQ&&hero->memHero->meridData.level==MAX_MERIDIAN_LEVEL)
	{
		// hero->updataSingleTarget(44);
	}
	
	merid->setTimerBusy(false);			//置修炼定时器为空闲状态
	hero->memHero->meridData.now = now;
	hero->memHero->meridData.level = merid->getLevel();
	hero->memHero->meridData.timerBusy = false;
	hero->memHero->meridData.remainTime = 0;
	hero->memSet();
	
	if(hero->memHero->meridData.level==40||hero->memHero->meridData.level==50||hero->memHero->meridData.level==60)
	{		
		char info[1024]={'\0'};
		snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",7,SYSTEM_WARN,"xf013",3,1,hero->getNickName(),hero->getIdentity(),0,0,5,now,0,0,0,3,hero->memHero->meridData.level,0,0,0);
		map<string, Hero*>::iterator it_hero;

		for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
		{
			if (it_hero->second!=NULL)
			{						
				send_msg(it_hero->second->getFd(),info);
			}
		}
	}

	//给客户端发送一条消息，修炼结束，应该要等级和now节点
	char msg[64] = {0};
	int level = merid->getLevel();
	int i;
	sprintf(msg, "8,2");
	for (i = 0; i <= now; i++)
	{
		// msg += intTostring(level);
		sprintf(msg + strlen(msg), ",%d", level);
	}
	for (i = now; i < 7; i++)
	{
		// msg += intTostring(level - 1);
		sprintf(msg + strlen(msg), ",%d", level - 1);
	}
	// send_msg(hero->getFd(), msg);
}

//根据memcache上来的经脉剩余时间对经脉进行处理
void restartMeridStudy(Hero *hero)
{
	//cout<<"BisonDon'twantyoutocomehere!!!!!!!!!"<<endl;
	if (hero == NULL || !hero->memHero->meridData.timerBusy)
	{
		return;
	}
	MeridData_T meridData = hero->memHero->meridData;
	Meridian *merid = hero->getMerid();
	int awayTime = MY_TV_SEC - hero->memHero->offlineTime;
	//cout<<"Bison merid remain Time is "<<meridData.remainTime<<endl;
	//cout<<"Bison merid remain Time is "<<meridData.timerBusy<<endl;
	//定时器不使用或者经脉升到顶级
	if (!meridData.timerBusy || merid->getLevel() >= MAX_MERIDIAN_LEVEL)
	{
		return;
		
	} else if (awayTime >= meridData.remainTime) {
		//修炼完成, 只用整秒数判断
		upgradeHeroMerid(hero);
		return;
		
	}	else {
		int remain = meridData.remainTime - awayTime;
		ev_timer *meridTimer = merid->getTimer();
		ext_ev_timer_init(meridTimer, meridCalBak, remain, 0, hero);
		//把要处理的对象加到有序链表
		//timers4meridian->push_front(wait, hero, heroId);
		//timers4meridian->push_front(remain, hero, hero->getIdentity());
		ev_timer_start(loops, meridTimer);
		merid->setTimerBusy(true);
		
		//cout<<"###########################you can t come here OK!"<<endl;
		return;
	}
}

//开始经脉修炼
int startMeridStudy(Hero *hero, int index, char* result)
{
	if (hero->getLevel() < heroMeridConf.startLevel)
	{
		//经脉未开启
		return 1;
	}
	Meridian *merid = hero->getMerid();
	int level = merid->getLevel();
	ev_timer *meridTimer = merid->getTimer();
	MERID_TYPE_T now = merid->getNow();
	int willLevel = level;
	if (now == YANGQ)
	{
		willLevel += 1;
	}
	int currLevel = willLevel - 1;
	int willMerid = (now + 1) % 8;
	if (heroMeridConf.item[willMerid].needHeroLevel[willLevel] > hero->getLevel())
	// if (now == YANGQ && level >= hero->getLevel() - 15)
	{
		//人物等级不足以修炼当前等级经脉
		return 2;
	}
	if (now == YANGQ && currLevel == MAX_MERIDIAN_LEVEL)
	{
		//经脉已经达到最大等级
		return 3;
	}
	if (merid->getTimerBusy())
	{
		//正在修炼
		cout<<"The hero already has the studying merid now!"<<endl;
		return 4;
	}
	
#if 0	
	if (willMerid != index)
	{
		//选中的经脉不是当前经脉的下一层
		cout<<"selected merid is not the next to study!"<<endl;
		return 5;
	}
#endif	

	//跳到第一个的时候再升级
	// if (now != YANGQ)
	// {
		// level -= 1;
	// }
	
	//经脉修炼时间等于等级的立方
	// int wait = level * level * level;
	cout<<"now is "<<willMerid<<" level is "<<currLevel<<" time is"<<heroMeridConf.item[willMerid].time[currLevel]<<endl;
	int wait = heroMeridConf.item[willMerid].time[currLevel];
	
	// ret += intTostring((now + 1) % 8);
	// ret += intTostring(wait);
	// ret += intTostring(level);
	// cout<<"111111111111111111111111111111111111111111111111111"<<endl;
	sprintf(result, ",%d,%d,%d", willMerid, wait, currLevel);
	// cout<<result<<endl;
	if (wait == 0)
	{	
		//修炼完成
		upgradeHeroMerid(hero);
		
		merid->setTimerBusy(false);			//置修炼定时器为空闲状态
	} else {
		ext_ev_timer_init(meridTimer, meridCalBak, wait, 0, hero);
		//把要处理的对象加到有序链表
		//timers4meridian->push_front(wait, hero, heroId);
		//timers4meridian->push_front(wait, hero, hero->getIdentity());
		ev_timer_start(loops, meridTimer);
		merid->setTimerBusy(true);
		
		hero->memHero->meridData.now = now;
		hero->memHero->meridData.level = merid->getLevel();
		hero->memHero->meridData.timerBusy = true;
		hero->memHero->meridData.remainTime = wait;
		hero->memSet();
	}
	
	//jolly add wulintarget 12.4 start
	// hero->updataSingleTarget(8);
	//jolly add wulintarget 12.4 end
	
	
	return 0;
}

//经脉修炼到期回调函数，只在内部使用，不提供外部接口
static void meridCalBak(struct ev_loop *loop, ev_timer *think, int revents)
{
	ev_timer_stop(loop, think);
	
	//Hero *hero = timers4meridian->pop_front();
	Hero *hero = (Hero *)think->target;
	if (hero == NULL)
	{
		cout<<"BisonTest at meridian_asist.cpp:38: The timerList pop hero obj error!"<<endl;
		return;
	}
	
	upgradeHeroMerid(hero);
	
}


//玩家离线时停止经脉定时器
void stopMeridianTimer(char* heroId)
{
	//Hero *hero = timers4meridian->find(heroId);
	Hero *hero = heroid_to_hero(heroId);
	if (hero == NULL)
	{
		return;
	}
	if (!hero->memHero->meridData.timerBusy)
	{
		return;
	}
	Meridian *merid = hero->getMerid();
	ev_timer* timer = merid->getTimer();
	//int remain = timers4meridian->getTimerRemain(heroId);//定时器还剩余的时间
	int remain = (int)ev_timer_remaining(loops, timer);
	//timers4meridian->delInRun(heroId);					//删除未结束定时器对应的对象节点
	ev_timer_stop(loops, timer);							//停止定时器
	
	//转成int，不到1秒的就不计了
	if ((int)remain <= 0)
	{
		//修炼完成回调
		meridCalBak(loops, timer, 0);
		
	} else {
		hero->memHero->meridData.now = merid->getNow();
		hero->memHero->meridData.level = merid->getLevel();
		hero->memHero->meridData.timerBusy = true;
		hero->memHero->meridData.remainTime = remain;
		hero->memSet();
	}
}

//使用道具,先判断使用道具可以成功版
int useMeridGoods(Hero *hero, char* goodsId, int index, int num, char* result)
{
	Bag *bag = hero->getBag();
	char* heroId = hero->getIdentity();
	// string ret;
	
	//先预判使用道具可否成功
	if (!bag->test(index, goodsId))
	{
		cout<<"BisonTest: no this goodsId in bag when use MeridGoods"<<endl; 
		return 1;
	}
	
	if (bag->getGridNum(index) < num)
	//if (bag->getGridNum(index) < 1)
	{
		cout<<"BisonTest: num is not enough when use MeridGoods"<<endl;
		return 2;
	}
	
	//经过预判，道具可以使用成功
	//对经脉定时器进行操作
	
	Meridian* merid = hero->getMerid();
	ev_timer* timer = merid->getTimer();
	
	int remain = ev_timer_remaining(loops, timer);		//定时器还剩余的时间
	if (remain <= 0)
	{
		//指定的英雄的经脉定时器不在计时
		cout<<"BisonTest: hero has no meridianTimer in timers4meridian when use meridian goods!"<<endl;
		return 3;
	}
	
	//只要能进入到这里，就一定能使用成功
	useBagGoods(hero,goodsId, index, num); 
	//useBagGoods(hero,goodsId, index, 1); 
	
	MERID_TYPE_T now = merid->getNow();	//当前经脉
	
	ev_timer_stop(loops, timer);							//停止定时器
	//道具减少的修炼时间
	int dec = 10 * 60 * num;						//现在只有一种此类道具-地火丸
	//int dec = 10 * 60 * 1;						//现在只有一种此类道具-地火丸 
	// if (goodsId == "small_jm_dan")
	// {
		// dec = 10.;
	// } else if (goodsId =="mid_jm_dan") {
		// dec = 50.;
	// } else if (goodsId =="big_jm_dan") {
		// dec = 100.;
	// }
	
	
	//使用道具后还剩余的时间
	remain -= dec;
	if ((remain) <= 0)
	{
		//使用物品后修炼完成
		remain = 0;
		//meridCalBak(loops, timer, 0);
		upgradeHeroMerid(hero);
		
	} else {
		//这里减少的时间还不足以使定时器结束
		ev_timer_set(timer, remain, 0);
		ev_timer_start(loops, timer);
		
		hero->memHero->meridData.timerBusy = true;
		hero->memHero->meridData.remainTime = remain;
		hero->memSet();
	}
	
	int level = merid->getLevel();		//经脉等级
	
	// ret += intTostring((now + 1) % 8);		
	// ret += intTostring(remain);
	// ret += intTostring(level);
	sprintf(result, ",%d,%d,%d", (now + 1) % 8, remain, level);
	return 0;
}

//取消经脉学习
bool cancelMeridStudy(char* heroId)
{
	//角色id得到角色实例
	Hero *hero = heroid_to_hero(heroId);

	//指定的英雄不存在，
	if (hero == NULL)
	{
		cout<<"BisonTest at meridian_asist.cpp:175: can't find the specified timer!"<<endl;
		return false;
	}
	//经脉定时器不在计时
	Meridian *merid = hero->getMerid();
	ev_timer *timer = merid->getTimer();
	int remain = ev_timer_remaining(loops, timer);
	if (remain <= 0)
	{
		ev_timer_stop(loops, merid->getTimer());
	}
	merid->setTimerBusy(false);
	
	hero->memHero->meridData.timerBusy = false;
	hero->memHero->meridData.remainTime = 0;
	hero->memSet();
	return true;
	
}

//经脉强化
int strenMerid(Hero *hero, char* result)
{
	// string ret;
	/*
	Hero *hero;
	map<string, Hero*>::iterator iter;
	iter = heroId_to_pHero.find(heroId);
	if(iter == heroId_to_pHero.end())
	{
		return false;
	}
	hero = iter->second;
	*/
	Meridian *merid = hero->getMerid();
	
	//判断玩家的钱够不够扣
	Money *heroMoney = hero->getMoney();
	if (heroMoney->money_getGold() < merid->getLevel())
	{
		return 1;
	}
	
	if(!merid->strengthen())
	{
		return 2;
	}
	
	useGold(hero,merid->getLevel());
	MERID_TYPE_T now = merid->getNow();
	int level = merid->getLevel();
	
	upgradeEffect(now, level, hero);
	// ret += intTostring(now);
	// ret += intTostring(level);
	sprintf(result, ",%d,%d", now, level);
	hero->memHero->meridData.now = now;
	hero->memHero->meridData.level = level;
	hero->memSet();
	
	return 0;
}

int getTotalLevel(Hero *hero)
{
	if(NULL == hero)
		return 0;
		
	Meridian *merid = hero->getMerid();
	int now = merid->getNow();
	int level = merid->getLevel();
	int totalLevel = (now + 1) * level + (7 - now) * (level - 1);
	return totalLevel;
}

//花元宝减少经脉修炼时间
int decMeridTimeWithGold(Hero *hero, int flag, char *result)
{
	if (flag != 0 && flag != 1)
	{
		//使用元宝客户端发送的模式有错(0:元宝修炼；1:一键修炼)
		return 6;
	}
	char* heroId = hero->getIdentity();
	Meridian* merid = hero->getMerid();
	if (merid == NULL)
	{
		//玩家未开启经脉
		return 7;
	}
	ev_timer* timer = merid->getTimer();
	if (!merid->getTimerBusy())
	{
		//玩家经脉不在修炼中
		return 8;
	}
	
	int remain = ev_timer_remaining(loops, timer);		//定时器还剩余的时间
	if (remain <= 0)
	{
		//指定的英雄的经脉定时器不在计时
		cout<<"BisonTest: hero has no meridian in study!!!"<<endl;
		//玩家经脉修炼已经到期过
		return 9;
	}
	
	Money *heroMoney = hero->getMoney();
	if (flag == 0)
	{
		if (!useBoundGold(hero, heroMeridConf.needBoundGoldPerFiveMin))
		{
			//玩家元宝不够
			return 10;
#if 0		
			int boundGold = heroMoney->getBoundGold();
			if (boundGold < 0)
			{
				//boundGold为负值，就是坏账号了
				return 5;
			}
			if (!heroMoney->useGold(5 - boundGold))
			{
				return 6;
			}
			
			heroMoney->useBoundGold(boundGold);
#endif
		}
		
		if (remain <= 300)
		{
			upgradeHeroMerid(hero);
			remain = 0;
		}
		else
		{
			remain -= 300;
			//这里减少的时间还不足以使定时器结束
			ev_timer_set(timer, remain, 0);
			ev_timer_start(loops, timer);
			
			hero->memHero->meridData.timerBusy = true;
			hero->memHero->meridData.remainTime = remain;
			hero->memSet();
		}
	}
	//一键修炼，把所有时间都减了
	else if (flag == 1)
	{
		unsigned num = remain / 300 + ((remain % 300) ? 1 : 0);
		unsigned needGold = num * heroMeridConf.needBoundGoldPerFiveMin;
		if (!useBoundGold(hero,needGold))
		{
			//玩家元宝不足
			return 10;
#if 0		
			int boundGold = heroMoney->getBoundGold();
			if (boundGold < 0)
			{
				return 5;
			}
			if (!heroMoney->useGold(needGold - boundGold))
			{
				return 6;
			}
			
			heroMoney->useBoundGold(boundGold);
#endif
		}
		
		upgradeHeroMerid(hero);
		remain = 0;
	}
	
	int level = merid->getLevel();		//经脉等级
	int now = merid->getNow();
	sprintf(result, ",%d,%d,%d", (now + 1) % 8, remain, level);
	return 0;
}