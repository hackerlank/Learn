#include"hero_fight.h"

#include"dropgoods.h"

// #include "TD_Instancing.h"	//塔防副本类头文件

#include "instancing_manage.h"		//副本管理类头文件

#include "campWarManagement.h"		//阵营战管理类头文件

#include "guild_war_asist.h"		//帮派战管理类头文件

#include"task_failed_comm.h"

#include"hatValRue.h"
#include "sitControl.h"
#include"monsterActiveBoss.h"
#include"monsterStatuary.h"
extern HatValRue *hatValRue; 
 
extern map<string,Map_Src*>mapId_connect_map;

extern campWarManagement campWarController;

extern Instancing_manage *Inst_MNG;

extern GuildWarAsist *guildWarManage;			//帮派战管理

extern map<string,Wagon*> wagonInstMap;						//马车实例

void proc_hero_lose_life(Hero* atker, Hero* atked, unsigned lifeHurt)
{
	atked->stopCollectTimer(3);			//玩家被攻击打断采集
	if (lifeHurt == 0)
	{
		return;
	}
	
	cout<<"***********************"<<endl;
	cout<<"atked state:"<<atked->getHeroState()<<endl;
	cout<<"atker state:"<<atker->getHeroState()<<endl;
	cout<<"***********************"<<endl;
	cancelSit(atker);
	cancelSit(atked);
	
	int lifeVal = atked->getLifeVal();
	if (lifeVal <= lifeHurt)
	{
		atked->setLifeVal(0);
		atked->setLifeStation(DEAD);
		
		if (atker == NULL)
		{
			return;
		}
		
		//战斗玩家都在帮派战房间中
		if (atker->isInGuildWarRoom() && atked->isInGuildWarRoom())
		{
			//增加攻击者的伤害统计
			guildWarManage->hurtCount(atker, lifeHurt);
			if (atked->getLifeStation() == DEAD)
			{
				//增加攻击者的杀人数
				guildWarManage->killCount(atker);
			}
		}
		
		//测试阵营战数据，有疑问请RTX xhm;
		if(atked->getLifeStation()==DEAD)
		{
			// if (atker->getTaskState() & TASK_NEED_PK_HERO)
			{
				string heroMapId = atker->getMapId();
				if (heroMapId == "map_021")
				{
					atker->updateHeroTaskStatus(PK_OTHER_HERO_TASK_NEED_TYPE, (char*)"pk", 1);
					atker->clrTskStSomeBit(TASK_NEED_PK_HERO);
				}
			}
			
			if(atked->getisRedName())//如果被击杀者是红名，增加角色击杀红名值大小；
			{
				if(atker->addReadNameKillsValue(1))
					cout<<"[XHM WARNING] AddReadNameKillsValue ERROR(game_fight_help_property_attackerAndhiter.cpp)."<<endl;
			}
			
			if(atked->isInCampWar()&&atker->isInCampWar())//如果击杀者和被击杀者都是在阵营战中，执行以下操作。
			{
				int campWarType = atked->getCampWarType();//如果被击杀者条件符合，增加被击杀者的死亡次数；
				if (campWarType == 4)
				{
					campWarController.campResWarKill(atker, atked);
				}
				else 
				{
					if(campWarType >= 2&& campWarController.addDeathInCampWar(atked) < 0)
					{
						cout<<"[XHM WARNING] Added deaths in the CampWar ERROR(game_fight_help_property_attackerAndhiter.cpp)."<<endl;
					}
					
					campWarType = atker->getCampWarType();//如果击杀者条件符合，增加击杀者的杀敌次数；
					if(campWarType >= 1 && campWarController.addKillsInCampWar(atker) < 0)
					{
						cout<<"[XHM WARNING] Added kills in the CampWar ERROR(game_fight_help_property_attackerAndhiter.cpp)."<<endl;
					}
				}
				
			}
		}
		/*红名判断*/
		atker->term(atked);
		
	} else {
		atked->setLifeVal(lifeVal - lifeHurt);
	}
}

void proc_mon_lose_life(Hero *atker, MonsterBase* mon, unsigned lifeHurt)
{
	if (lifeHurt == 0)
	{
		/*add chenzhen 201301311556 闪避也会产生仇恨*/
		HatVal hatval(atker->getIdentity(), hatValRue->getGenHitPer() * 10);  
		
		mon->InpushEnmityValues(hatval);
		
		/*自卫反应设置*/
		mon->setRepFlg(true);
			/*仇恨值 end*/
		mon->response();
		
		return;
	}
	
	int lifeVal = mon->getLifeVal();
	mon->setGoodsOwner(atker->getIdentity());
	// cout<<"lifeVal is "<<lifeVal<<" and lifeHurt is "<<lifeHurt<<endl;
	if (lifeVal <= lifeHurt)
	{
		mon->setLifeVal(0);
	//	mon->setLifeStation(DEAD);        //chenzhen add 20130109
		mon->setLifeStation(false);
		/*怪物死亡掉落*/	
		char* heroId=atker->getIdentity();
		char* ownerId=mon->getGoodsOwner();	
		
		/*活动boss没有所有者*/
		if(strcmp(mon->getType(),"ActiveBossMon") == 0)
		{			
		
	//		strncpy(ownerId,"0",2);
			
			/*追加头衔，boss终结者*/
			atker->addTitle("T050");
			
		}
		monsterDropGoods(ownerId,mon);
		// dropTaskGoods(atker, mon);
		
		/*add chenzhen by 201301291511 活动boss经验分成*/
		if(strcmp(mon->getType(),"ActiveBossMon") == 0)
		{
			/*记录最后一刀*/
			((MonsterActiveBoss*)mon)->inputLastHero(atker->getIdentity());			
			
			cout<<"give the last hero begin:"<<atker->getIdentity()<<endl;
			/*给最后一刀的人经验*/
			getexperience(atker, mon);
			cout<<"give the last hero end:"<<atker->getIdentity()<<endl;
			string firstHeroId = ((MonsterActiveBoss*)mon)->getFirstHero();
			Hero *firstHurt = heroid_to_hero(firstHeroId);
			if(firstHurt)
			{
				cout<<"give the first hero begin:"<<firstHurt->getIdentity()<<endl;
				/*给第一刀的人经验*/
				getexperience(firstHurt,mon);
				cout<<"give the first hero end:"<<firstHurt->getIdentity()<<endl;
			}
			
		}		
		else
		{
			// cout<<"ownerId is:"<<ownerId<<endl;
		
			// cout<<"ownerId:"<<ownerId<<"         heroId:"<<heroId<<endl;
			if (strcmp(ownerId,heroId)==0)
			{			
				dropTaskGoods(atker, mon);
				getexperience(atker, mon);
			}
			else
			{
				Hero *monsterOwner = heroid_to_hero(ownerId);
				if (monsterOwner != NULL)
				{
					dropTaskGoods(monsterOwner, mon);
					// cout<<"test begin():"<<endl;
					getexperience(monsterOwner, mon);
					// cout<<"test end():"<<endl;
				}
			}
		}
		//cout<<"property_attackerAndhiter:jolly add dropgoods end"<<endl;
		
		//Tory add 2012.7.20 starting 塔防怪物死亡后的数值处理
		//塔防副本怪,怪物死亡后应将死亡怪物ID从角色吸引怪物的Id列表中删除
		string behavior_type = mon->getType();
		if(behavior_type.find("Tower") != string::npos)   	
		{
			HatVal* hatva = mon->getOneEnmityValues();
			if(hatva != NULL)
			{
				string des_heroId = hatva->id;
				map<string, Hero*>::iterator hero_it;
				hero_it = heroId_to_pHero.find(des_heroId);
				if(hero_it == heroId_to_pHero.end())
				{
					cout<<"return from attack_monster_success,cause can't find the enermy hero: "<<des_heroId<<endl;
				}
				Hero *in_hero = hero_it->second;            //in_hero--->怪物判定范围之内包含的角色	
				//cout<<"before in_hero->getAttracMonNum()"<<in_hero->getAttracMonNum()<<endl;
				in_hero->delAttracMonId(mon->getIdentity());		//从吸引怪物ID容器删除掉死亡了的怪物ID
				//cout<<"after in_hero->getAttracMonNum()"<<in_hero->getAttracMonNum()<<endl;        
			}
				
			Map_Inform *map_now = mon->getMap();
			string td_room = map_now->getTd_roomid();
			TD_Instancing *this_inst = Inst_MNG->id2tdRoom(td_room);
			this_inst->AddSelfInstancingStatus(INST_STATUS_HELP_VAL);			//统计击杀怪物数目，增加斗气值
			this_inst->AddSelfInstancingStatus(INST_STATUS_MONSTER_DISAPPEAR);	//MONSTER_DISAPPEAR加1
			
		}
		// cout<<"die monsterId:"<<mon->getIdentity()<<endl;
		/*add chenzhen by 201303221511 雕像怪*/
		if(strcmp(mon->getType(),"MonStatuary") == 0)
		{
			/*记录最后一刀*/
			((MonsterStatuary*)mon)->setHeroId(atker->getIdentity());			
		}
		mon->die();
		//tory add 2012.7.20 ending
    } else {
	
		mon->setLifeVal(lifeVal - lifeHurt);
		
		/*add by chenzhen 201301291514 活动boss，记录第一刀的人*/
		if(strcmp(mon->getType(),"ActiveBossMon") == 0)
		{
			((MonsterActiveBoss*)mon)->inputFirstHero(atker->getIdentity());
		}
		
		/*add chenzhen by 201303221511 雕像怪暂时没有反应*/
		if(strcmp(mon->getType(),"MonStatuary") == 0)
		{
			return;		
		}
		
		//仇恨值 start
		//cout<<"property_attackerAndhiter:chenzhen monster chouhen start"<<endl;
		HatVal hatval(atker->getIdentity(), hatValRue->getGenHitPer() * lifeHurt);   	
		mon->InpushEnmityValues(hatval);
		
		/*自卫反应设置*/
		mon->setRepFlg(true);
			/*仇恨值 end*/
		mon->response();
			//cout<<"property_attackerAndhiter:chenzhen monster chouhen end"<<endl;
		
	}
}

void proc_wagon_lose_life(Hero* atker, Wagon* wagon, int lifeHurt)
{
	bool isLive = wagon->beAttacked();
	if (!isLive)
	{
		cout<<"[BisonSHow] the wagon has been distroyed!"<<endl;
		//向九宫格发马车死亡消息
		wagon->disperMsg();
			
		wagonInstMap.erase(wagon->getIdentity());
		
		Hero *owner = wagon->getOwner();
		if(owner != NULL)
		{
			
			//hero的马车没有了
			memset(owner->memHero->wagonId, 0, sizeof(owner->memHero->wagonId));
			//玩家的马车任务失败
			char taskId[10] = "task00295"; 
			taskFailedDeal(owner, taskId, 1);
			strncpy(taskId, "task00419", 10);
			taskFailedDeal(owner, taskId, 0);
		}
		delete wagon;
	}
}


void proc_bottle_lose_life(Hero* atker, Bottle* bottInst, int lifeHurt)
{
	bool isCHg = false;
	bottInst->beAttack(atker->getIdentity());
	
	cout<<"go proc_bottle_lose_life begin:"<<bottInst->getLifeVal()<<endl;

	if(bottInst->getLifeVal() == 0)
	{
		//打碎瓶罐掉落
		dropTaskGoods(atker,bottInst);

		useMoneyBox(atker,bottInst->getTypeId(),bottInst->getPiexPt());
		
		/*add chenzhen 20130128 打碎瓶罐会给打碎者会一定比例的血和蓝*/
		int reBlod = bottInst->getBloodPre() * atker->getLifeUpperVal();
		int reMagic = bottInst->getMagicPre() * atker->getMagicUpperVal();
		
		cout<<"go proc_bottle_lose_life second:"<<endl;
		
		if(atker->getLifeVal() < atker->getLifeUpperVal())
		{
			reBlod += atker->getLifeVal();
			if(reBlod >= atker->getLifeUpperVal())
			{
				reBlod = atker->getLifeUpperVal();
			}
			atker->setLifeVal(reBlod);
			isCHg = true;
			cout<<"the now blood :"<<atker->getLifeVal()<<endl;
		}
	
		if(atker->getMagicVal() < atker->getMagicUpperVal())
		{
			reMagic += atker->getMagicVal();
			if(reMagic >= atker->getMagicUpperVal())
			{
				reMagic = atker->getMagicUpperVal();
			}
			atker->setMagicVal(reMagic);
			isCHg = true;
			cout<<"the now magic :"<<atker->getMagicVal()<<endl;
		}
		
		cout<<"go proc_bottle_lose_life thrid:"<<endl;
		
		cout<<"the blood :"<<atker->getLifeVal()<<endl;
#if 0		
		/*给客户端跟新数据*/
		if(isCHg)
		{		
			atker->send_msg_att();
		}
#endif	
	}
	
	
	
	
}