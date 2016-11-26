/*
        文件类型：实现文件
        文件名称：hero.cpp
        文件作用：实现类Hero里面的函数
        修改时间：2012.2.27 14:10
        修改人：Evan
        修改内容：增加一个技能列表，并实现其set，get方法
*/
#include<iostream>
#include<map>
#include <string.h>
#include"hero.h"
#include"map_src.h"
#include"command_other_function_all_over.h"
#include"command_return_define_data.h"
#include"command_game_fight_manage.h"
#include"user_role_manage_skill.h"
#include"pick.h"
#include"timerContainer.h"
#include"skill_configuration.h"
#include"meridian_asist.h" 
#include"wagon.h"
#include "my_memcached.h"
#include"hero_drugs_manage.h"
#include"user_role_manage_task.h"
#include"guild_asist.h"
#include"money_operator.h" 
#include"heroCpyRecord.h"
#include"commodity.h"
#include"command_other_function_all_over.h"
#include"wagon.h"
#include "campWarManagement.h"
#include "pet_operator.h"
#include"boxAsist.h"
#include"midasTouch.h"
#include "reward_recharge_config.h"
#include "campWarManagement.h"	
#include "move_asist.h"
#include "camp_war_reward.h"
#include "system_activity_reward_assist.h"
#include "rankInfoAsist.h"
#include "user_role_manage_assist.h"
#include "guild_war_asist.h"
#include "rob_flag_war_logic.h"
#include "internal_forces_manage.h"
//缓存服务器管理类
#include "my_mem_group.h"
#include"towerLayerRecord.h"
#include"chatGroupManager.h"
#include"chatGroup.h"
#include"team.h"
#include"teamManager.h"
#include "camp_leader_and_chief.h"

extern ChatGroupManager *chatManager;


extern map<int,int> campNumber;
extern MyMemGroup* mem_group;
extern map<string, HeroSkill*> skillId_2_heroSkill;		//角色技能
extern campWarManagement campWarController;		//阵营管理器；
extern map<int,list<Hero*> >	fingerGuessingGamePerson;			//等待猜拳中的hero
extern map<string,Ride_Config*> id_to_ride;
extern int sock_fd;
extern set<string> guildTaskList;				//帮派任务列表
extern set<string> dayTaskList;					//日常任务
extern set<string> campTaskList;				//阵营任务列表
extern DayLmtFindGroup_T dayLmtGroupForAll;		//全局的日限制项目
extern map<string,Wagon*> wagonInstMap;			//所有马车实例，还原马车任务使用
extern struct ev_loop *loops;
extern struct timeval myTime;
extern TimerContainer<Hero*> *heroThkContain;
extern map<string, Hero*> heroId_to_pHero;
extern VIPRewardData vipRewardData[20];
extern set<string>allTitle; 
extern map<int,Reward_recharge_config*>id_to_reward_recharge;
extern map<string,Map_Src*>mapId_connect_map; 
extern TimerContainer<Hero*> *petThk;  
extern char g_out_buf[20480];
extern campWarManagement campWarController;
extern map<string,Equip_config*>id_to_equip; //装备模版类容器
extern int dataVersion;
extern map<string,Pick*> goods_to_hero;
extern map<string,Skill_Configuration*>id_to_skill;
extern map<string ,VipDataInitial> vipDataStore;
extern map<string,Goods_Config*> id_to_cl;
extern struct tm* timeNow;
//打坐经验配置文件
extern map<int,RewardFactor> factor_reward;
extern map<string ,PrivateStall* > onLineStall; //在线摊位
extern map<string,string> mapIdToGoodsId; //副本id 找副本令id
// extern map<string , vector<BuffOintment *> > buffTimeRemain;  //buff药品使用时间记录
extern HappyMapReward_T HappyMapRewardConf;			//娱乐图奖励配置
extern GuildWarAsist *guildWarManage;			//帮派战管理
//缓存操作类实例指针，全局变量
// extern MyMemcache* mem_operate;
extern char server_name[10];
 
extern vector<string>globalHeroId;			//保存全局的memcached角色Key；

//用于昵称检查缓存的操作类指针实例引用声明
extern MyMemcache* mem_operate_nickname_inspection;

extern map<string,Equipment*> dropEquipMent;

extern map<string,map<string,string> >towerMapConf;

#define HAPPY_PER_TIME			20				//娱乐图加成时间

/*
* Author:	Tory
* Date	:	2012.9.12
* Amend :	
* Description：需要向memcached server中存储memHero数据时调用
*/
bool Hero::memSet(void)
{	
	// if(pet_box)
	// {
		// memHero->petboxdataNew=pet_box->getMemStruct();
	// }

	memHero->bagData=bag->getMemStruct();
	memHero->moneydata=money->getMemStruct();
	memHero->warehousedata=warehouse->getMemStruct();
	memHero->cpyRecordMem = cpyRecord->getMyHeroRecMem();
	memHero->mysteriousBussinessData = mysteriousbussiness->getMemStruct();
	memHero->midasTouchData=midasTouch->getMemStruct();
	memHero->onlineReward=online_reward->getMemStruct();
	memHero->rideData=ride->getMemStruct();
	memHero->offlineTime=MY_TV_SEC;
	// memHero->rewarddata.offline_time=MY_TV_SEC;
	memEquipSet();
	
	/* 按heroId,将memHero存储至Hero::where指定的memcached 服务器,上面注释代码将废弃 tory 2013.3.15 */
	bool isSuccess = mem_group->set_data(memHero->identity, (char*)memHero, (int)sizeof(MemHero), Hero::where);
 
    if(isSuccess == true)
    {
        cout<<"set memHero into memcached server success"<<endl;
    } else
    {
        cout<<"set memHero into memcached server failure"<<endl;
    }	
}

void init_basic_from_conf(HeroBasicData &heroBasic, char *party)
{
	map<string, Hero_Conf_T>::iterator it_conf = party_2_heroConf.find(party);
	if (it_conf == party_2_heroConf.end())
	{
		cout<<"No the hero_conf of the party "<<party<<endl;
		return;
	}
	Hero_Conf_T *p_conf = &it_conf->second;
	memset(&heroBasic, 0, sizeof (HeroBasicData));
	strncpy(heroBasic.mapId,  p_conf->mapId, sizeof (heroBasic.mapId));
	strncpy(heroBasic.party, p_conf->party, sizeof (heroBasic.party));
	heroBasic.pt = p_conf->bornPt;
	heroBasic.lifeUpperVal = p_conf->lifeUpperVal;
	heroBasic.lifeVal = heroBasic.lifeUpperVal;
	heroBasic.magicUpperVal = p_conf->magicUpperVal;
	heroBasic.magicVal = heroBasic.magicUpperVal;
	heroBasic.hited = p_conf->hited;   //命中
	heroBasic.crit = p_conf->crit;             //暴击
	heroBasic.dodge = p_conf->dodge;              //闪避
	heroBasic.tenacity = p_conf->tenacity;              //韧性
	heroBasic.outattack = p_conf->outAttack;              //外攻击
	heroBasic.inattack = p_conf->inAttack;              //内攻击
	heroBasic.outdefense = p_conf->outDef;              //外防御
	heroBasic.indefense = p_conf->inDef;              //内防御
	heroBasic.outhurt = p_conf->outHurt;              //外功伤害
	heroBasic.inhurt = p_conf->inHurt;              //内功伤害
	heroBasic.attkType = p_conf->attkType;
}

/*
* Author:	jolly
* Date	:	2012.10.10
* Amend :	
* Description：将装备的数据存入memcached,不同于Memhero的一张表
*/
bool Hero::memEquipSet(void)
{
	map<string,Equipment*>::iterator it;
	for (it=heroAllEquip.begin();it!=heroAllEquip.end();it++)
	{
		it->second->saveInStruct();
		string identity=it->second->getentityid();
		EquipmentData *memEquipData;
		memEquipData=it->second->getEquipmentData();
		mem_group->set_data(identity, (char*)memEquipData, (int)sizeof(EquipmentData), where);	
	}	
}


/* 
* author: tory
* date: xxxx.x.xx
* arg: connect_fd,当前角色对应的sockfd; where,角色数据属于第几区
* describe:用于玩家从memcached server中取出的memHero数据，生成的Hero类对象进入游戏逻辑处理
 */
Hero::Hero(MemHero *_memHero, int connect_fd, int _where)
{
	towerLayerRecord = NULL;	
	keyPath.clear();
	skillBuffState = 0;
	isLoading = false;	//刚上线进场景状态设置为false，直到客户端加载完成
	recoverTmeCtn = 0;
	memHero = _memHero;
	where = _where;
	memset(viewIdentity,0,sizeof(viewIdentity));
	saveCount=0;
	cout<<"memHero->worldSpeakTimes:"<<memHero->worldSpeakTimes<<endl;

	changeRedName();
	
	// memHero->dropProbabty = memHero->crimeValue;
	
    //属性设置
    setFun[0] = &Hero::setLifeUpperVal; setFun[1] = &Hero::setMagicUpperVal; setFun[2] = &Hero::setOutDefense;
    setFun[3] = &Hero::setInDefense; setFun[4] = &Hero::setOutAttack; setFun[5] = &Hero::setInAttack;
    setFun[6] = &Hero::setHited; setFun[7] = &Hero::setDodge; setFun[8] = &Hero::setTenacity;
    setFun[9] = &Hero::setCrit; setFun[10] = &Hero::setOutHurt; setFun[11] = &Hero::setInHurt;
    //属性获取
    getFun[0] = &Hero::getLifeUpperVal; getFun[1] = &Hero::getMagicUpperVal; getFun[2] = &Hero::getOutDefense;
    getFun[3] = &Hero::getInDefense; getFun[4] = &Hero::getOutAttack; getFun[5] = &Hero::getInAttack;
    getFun[6] = &Hero::getHited; getFun[7] = &Hero::getDodge; getFun[8] = &Hero::getTenacity;
    getFun[9] = &Hero::getCrit; getFun[10] = &Hero::getOutHurt; getFun[11] = &Hero::getInHurt;

	map<string, Hero_Conf_T>::iterator it_conf = party_2_heroConf.find(memHero->basicHeroData.party);
	if (it_conf == party_2_heroConf.end())
	{
		cout<<"No the hero_conf of the party "<<memHero->basicHeroData.party<<endl;
		exit(1);		//已在配置文件读取的时候对数据做了检查 tory 2013.1.11
	}
	p_conf = &it_conf->second;
	
	exerciseNeedMoney=20000;
	
	crimCount=0;
	powerCount = 0;
	bloodBottle=0;
	magicBottle=0;
	initCrimeTime();				//初始化罪恶时间 Cookie

	strncpy(memHero->copyCause,"0",1);
	memHero->copyCause[1]='\0';
	
	if (strcmp(memHero->basicHeroData.mapId,"map_030")==0||strcmp(memHero->basicHeroData.mapId,"map_031")==0)
	{
		strncpy(memHero->basicHeroData.mapId,"map_001",sizeof(memHero->basicHeroData.mapId));
	}
	
	map<string,Map_Src*>::iterator map_it;
	
	//验证下线前所在地图是否为衍生图，如果是衍生图，为防止找不到衍生图的bug，修改到主城
	char *lastMapId = memHero->basicHeroData.mapId; 
	if (lastMapId != NULL && strlen(lastMapId) > 7)
	{
		strncpy(memHero->basicHeroData.mapId,"map_001",7);
		memHero->basicHeroData.mapId[7] = '\0';
	}
	else
	{
		/*如果上限地图有问题，则设置主城*/
		map_it = mapId_connect_map.find(memHero->basicHeroData.mapId);
		if(map_it == mapId_connect_map.end())
		{
			memset(memHero->basicHeroData.mapId,'\0',50);
			strncpy(memHero->basicHeroData.mapId,"map_001",7);
		}
	}
		
    map_it=mapId_connect_map.find(memHero->basicHeroData.mapId);
    if(map_it == mapId_connect_map.end())
    {
	 strncpy(memHero->basicHeroData.mapId,"map_001",7);
         memHero->basicHeroData.mapId[7] = '\0';
	 map_it=mapId_connect_map.find(memHero->basicHeroData.mapId);
        cout<<"return from hero.cpp,cause initMap error"<<endl;
        //return;
    }
    map_now = map_it->second;
		
	memHero->autoRecover=myTime.tv_sec;

	Hero::setLocation(memHero->basicHeroData.pt); 
	
	//初始化青衣楼当前层数据
	initOldNowTowerId();
	
 	if(map_now->judgeLogPtHind(logPt) == false)
	{
		cout<<"hero's location is error: "<<logPt._x<<" "<<logPt._y<<endl;
		Hero::setLocation(map_now->getEntPt()); 
	} 

	try{
		cpyRecord = new HeroCpyRecord(memHero->cpyRecordMem);
		bag=new Bag(memHero->bagData);	
		money=new Money(memHero->moneydata);
		warehouse=new Warehouse(memHero->warehousedata);
		midasTouch=new MidasTouch(memHero->midasTouchData);
		online_reward=new Reward_Online(memHero->onlineReward);
		saveWarehouseEquip();
		saveBagEquip();
		pet_box=new Pet_Box(&memHero->petboxdataNew);
		mysteriousbussiness=new MysteriousBussiness(memHero->mysteriousBussinessData);
		ride=new Ride(memHero->rideData);			
	}
	catch(exception e){
		throw e;
	}
			
	if (memHero->level > MAX_HERO_LEVEL)
	{
		memHero->level = MAX_HERO_LEVEL;
	}
	
	if (pet_box==NULL)
	{
		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	}
	pet_box->carryNum(memHero->level);	
	memcpy(memHero->wearequipdata,_memHero->wearequipdata,sizeof(memHero->wearequipdata));
	////////////////////////jolly start 
	judgeSignFlag();
	judgeExercise();
	for (int i=0;i<4;i++)
	{
		exerciseTemp[i]=0;
	}
		
	/**********xhm add start************/
	//对进入活动次数赋值；
	memcpy(activityCounts,memHero->activityCounts,sizeof(activityCounts));
	prestige = memHero->prestige;
	readNameKills = memHero->readNameKills;
	friendInfo=new Friend(memHero->myFriendInfo, _where);
	
	//xhm added,有疑问RTX xhm
	time_t timeNow_t=time(NULL);
	if(!isNowRechargeReward(timeNow_t))//TODO
	{
		memHero->recharge_time=0;
		memHero->cum_recharge_awards=0;
	}
	if(!isNowConsumeReward(timeNow_t))//TODO 
		memHero->useGoldForActive=0;
		
	if(!isNowGoodsUseReward(timeNow_t))
		memHero->goods_use_size=0;
	
	if(!isNowGoodsGainReward(timeNow_t))
		memHero->goods_gain_size=0;

	//TODO 有待修改
	char *temp_nick_name=getNickName();
	char *temp_id = getIdentity();
	if(temp_nick_name != NULL  &&temp_id != NULL )
	{
		bool isSuccess = mem_operate_nickname_inspection->set_mem_data(temp_nick_name,temp_id, strlen(temp_id)); 
		if(isSuccess)
		{
			cout<<"[XHM MSG] TO ADD getNickName mem_operate_nickname_inspection Succ!"<<endl;
		}else{
			cout<<"[XHM MSG] TO ADD getNickName mem_operate_nickname_inspection Error!"<<endl;	
		}
	}
	/**********xhm add end************/
		
	if (!isSameDayWithNow(memHero->offlineTime))
	{
		////cout<<"BisonTest : you are the first today"<<endl;
		//如果天数不同或者天数相同年数不同，则这次是今天的第一次登陆）
		isFirstLoginInDay = true;
		cout<<"BisonShow: the hero is first login today!"<<endl;
		
		
		//更新声望书使用次数限制
		memHero->usePrestigeTime=5;
		
		//更新交易成功增加好友度限制；
		if(friendInfo){
			cout<<"[XHM TEST] initFriendDegLimit()(hero.cpp)!"<<endl;
			friendInfo->initFriendDegLimit();
		}
	} else {
		cout<<"BisonShow: It is not the first logining of the hero today!"<<endl;
		isFirstLoginInDay = false;
	}
	guild = NULL;
	memset(guildName, 0, sizeof(guildName));
	
    merid = new Meridian(memHero->meridData);

#if 0			//for jolly's need merid total add val
	for (int i = 0; i < 8; i++ )
	{
		int val1 = 0, val2 = 0;
		merid->getIncTotalVal(val1, val2, i);
		cout<<"merid val1 is "<<val1<<" merid's val2 is "<<val2<<endl;
	}
#endif

    memInitTask();					//恢复角色的任务数据 bison
	
	cout<<"[BBBB] show show show show show show show show before before before before"<<endl;
	//玩家下线前有帮派
	if (memHero->heroGuildData.guildTitle != -1)
	{
		cout<<"hero has guild for he has guildTitle != -1."<<endl;
		if (strlen(memHero->heroGuildData.guildId) != 0)
		{
			if (strlen(memHero->heroGuildData.guildId) < 38)
			{
				//为老的帮派名
				sprintf(guildName, "%s[%03d]", memHero->heroGuildData.guildId, where);
				cout<<"before his guildId is "<<memHero->heroGuildData.guildId<<" It's guildName and new guildName is "<<guildName<<endl;
				guild = getGuildWithName(guildName);
				
			} else {
				cout<<"according its lenth it's guildId "<<memHero->heroGuildData.guildId<<endl;
				guild = getGuildWithId(memHero->heroGuildData.guildId);
			}
			
			if (guild != NULL)
			{
				strncpy(memHero->heroGuildData.guildId, guild->getId(), sizeof(memHero->heroGuildData.guildId));
				strncpy(guildName, guild->getName(), sizeof(guildName));
				
				
				//更新帮派信息，以防下线时被踢出帮派或者被调整职务
				updateGuildInfo();
				
			} else {
				cout<<"fuck before memcache show he has guild but now find his guild is NULL"<<endl;
				//有头衔，帮派却找不到，说明离线期间帮派解散了
				clrGuildInfo();
			}	
		}
		
	} else {
		cout<<"Bison fuck you your guildTitle is "<<memHero->heroGuildData.guildTitle<<" and guildId is "<<memHero->heroGuildData.guildId<<endl;
	}
	cout<<"[BBBBBB] show show show show show show show after after"<<endl;
	
  	
	if (isFirstLoginInDay)
	{
		memHero->heroGuildData.guildSigned = false;
		//有限制次数的项目在每天第一次登陆的时候初始化
		dayLmtFindGroup = dayLmtGroupForAll;			
		//更新到memcached保存数据
		memcpy(memHero->dayLmtItemArr, dayLmtFindGroup.dayLmtItemArr, sizeof(memHero->dayLmtItemArr));
		//日限制项目使用的数量
		memHero->dayLmtUsedNum = dayLmtFindGroup.lastUsedIndex;
		
		memHero->internalForcesBrushExpTimes = 0;
		memHero->goldBrushExpTimes = 0;
		
		char refreshTask_msg[1024]={'\0'};
		snprintf(refreshTask_msg, sizeof(refreshTask_msg),"%d,%d,%s,%d,%s,%s,", 17, 0, server_name, (int)myTime.tv_sec, getIdentity(), getNickName());
		write_log(refreshTask_msg);	
		resetDailyTask(this);
		initCycleTask();
		freshHeroCycleTask(this);
		updateCycleTaskLevel();
		
		memHero->buyFatigueTmes = 0;
		
		#if 0
		/*现不刷新*/
		memHero->lastStrength = memHero->fatigueUpperVal;         //刷满疲劳值
		#endif
		
		//青衣楼数据
		initTowerLayerFlg();
		
	} else {
		//不是一天的第一次登陆从内存回来的
		dayLmtFindGroup.items2group(memHero->dayLmtItemArr, memHero->dayLmtUsedNum);
	}

    fiveElement = new FiveElem(memHero->fiveElementData);	//恢复角色的五行数据 bison
	
	//对某些状态数据赋值
	_fd = connect_fd;
	life_station = LIVE;
	
	status = 0;						//角色的无敌状态 jolly
	
	max_accepted_size = 10;     	//已接任务列表的最大容量暂设为10，待以后确定
	
	online_time = myTime.tv_sec;		//jolly
	
	inGuildWarRoom = false;			//不论何时上来都不让玩家在帮战房间中 bison 

	stillFlg = false;				//定身标记 Evan 	
	

	
	heroState=0;					
		
	initCopyCauseStore(); 			//由mem初始化 副本令数据
	teamAim="";

	/*上线还原玩家身上的装备 2012 10 17 jolly start*/
	for (int i=0;i<14;i++)
	{
		if (memHero->wearequipdata[i].flag==1)
		{
			string _identity=memHero->wearequipdata[i].goodsid;			
			int size=0;
			int equipWhere=0;
			EquipmentData *equipmentdata = (EquipmentData*)mem_group->get_data(_identity, &size,&equipWhere,where);
			if(equipmentdata!=NULL)
			{					
				Equipment *equipment=new Equipment(equipmentdata);
				free(equipmentdata);	
				if (i==0||i==13)
				{
					cout<<"上线还原玩家身上的装备"<<endl;
					equipment->isEffect(this);
				}
				// SuitManage(this,equipment,1);
				heroAllEquip.insert(map<string,Equipment*>::value_type(_identity,equipment));
				// if (i==0)
				// {
					// cout<<"这里是时装数据还原"<<endl;
				// }
			}
			else
			{
				continue;
			}
		}
	}
	
	//上线还原坐骑装备
	for (int i=0;i<4;i++)
	{
		if (memHero->rideData.equip[i].flag==1)
		{
			string _identity=memHero->rideData.equip[i].goodsid;			
			int size=0;
			int equipWhere=0;
			EquipmentData *equipmentdata = (EquipmentData*)mem_group->get_data(_identity, &size,&equipWhere,where);
			if(equipmentdata!=NULL)
			{					
				Equipment *equipment=new Equipment(equipmentdata);
				free(equipmentdata);	
				heroAllEquip.insert(map<string,Equipment*>::value_type(_identity,equipment));
			}
			else
			{
				continue;
			}
		}
	}
	
	canWalking = true;
	
	try
	{
		initTowerLayerRecord();	
	}
	catch(exception e)
	{
		throw e;
	}
	
	memset(guildWarRoomId, 0, IDL + 1);
	
	//由于下线,双倍经验仍然计时,所以在上限计算离线经验的时候,重新计算双倍经验的剩余时间
	memHero->expTimesCount=memHero->expTimesCount-(online_time-memHero->offlineTime);
	if (memHero->expTimesCount<=0)
	{
		memHero->expTimes=1;
		memHero->expTimesCount=0;
	}		
	
	startMoveTimer();
	//检查是否有娱乐图加经验
	// if (isInHappyTime)
	if (isInFirstRoomHappyTime)
	{
		if (!strcmp(memHero->basicHeroData.mapId, "map_023")
			|| !strncmp(memHero->basicHeroData.mapId, "map_024", 7)
			|| !strncmp(memHero->basicHeroData.mapId, "map_025", 7))
		{
			startHappyTimer();
		}
	} else if (isInSecondRoomHappyTime)
	{
		if (!strcmp(memHero->basicHeroData.mapId, "map_026")
			|| !strncmp(memHero->basicHeroData.mapId, "map_027", 7)
			|| !strncmp(memHero->basicHeroData.mapId, "map_028", 7))
		{
			startHappyTimer();
		}
	}
	
	//计算离线经验
	countOffline_exp();
	
	setFbRom(NULL);
	
	reCountHeroArr();

	if (strlen(memHero->wagonId) != 0)
	{
		speed = NORMAL_WAGON_SPEED;
		lastSpeed = NORMAL_WAGON_SPEED;
	} else {
		
		if (ride != NULL)
		{
			if (ride->ifFull())
			{
				if (memHero->rideState == RIDE_STATE_RIDING)
				{
					speed = NORMAL_HERO_SPEED + ride->getMove();
					lastSpeed = speed;
				} 
				else
				{
					memHero->rideState == RIDE_STATE_FREE;
					speed = NORMAL_HERO_SPEED;
					lastSpeed = NORMAL_HERO_SPEED;
				}
			} 
			else 
			{
				memHero->rideState = RIDE_STATE_FREE;
				speed = NORMAL_HERO_SPEED;
				lastSpeed = NORMAL_HERO_SPEED;
			}
		} 
		else 
		{
			memHero->rideState = RIDE_STATE_FREE;
			speed = NORMAL_HERO_SPEED;
			lastSpeed = NORMAL_HERO_SPEED;
		}
	}	

	
	if (memHero->heroVersion!=dataVersion)			//人物数据版本和最新数据版本不同,则在此对人物数据进行操作
	{	
		if (memHero->heroVersion==20130606)
		{
			//money->money_increaseBoundGold(500);
			money->money_increaseGold(1000);
			
			char accountMsg[1024]={0};
			snprintf(accountMsg,sizeof(accountMsg),"40,0,%s,%d,%s,%s,%d",server_name,(int)myTime.tv_sec,getIdentity(),getNickName(),1000);
			write_log(accountMsg);
		}
		memHero->heroVersion=dataVersion;
	}
	// updateHeroDaily();
}

void Hero::memInitTask()
{
	memHero->taskState = 0; 
#if 0
	memset((void*)(&memHero->taskSaveData), 0, sizeof (memHero->taskSaveData));
	int mapTest[25] = {-536870913,-1,-3873,2096959,-1024,-262143,-1,-1,16383,256,0,0,8257536,40,-268435456,0,0,0,0,0,0,0,0,0,0};
	memcpy((void*)&memHero->taskSaveData.finMap, (void*)&mapTest, sizeof(memHero->taskSaveData.finMap));
	TaskData_T taskDataTest;
	taskDataTest.taskFlag = 1;
	strncpy(taskDataTest.taskId, "task00408", 10);
	memcpy((void*)&memHero->taskSaveData.acced[0], (void*)&taskDataTest, sizeof (taskDataTest));
#endif
	accepted_task_list.clear();
    int i;
	bool wagonFlag = false;
	char* wagonId = memHero->wagonId;
	
    for(i = 0; i < 10; i++)
    {
        if(memHero->taskSaveData.acced[i].taskFlag == -1)
        {
            //string taskId;
            //taskId = taskSaveData.acced[i].taskId;
            ////cout<<"Before continue "<< "i = "<<i<<" "<<taskId<<endl;
            continue;
        }
        char* taskId = memHero->taskSaveData.acced[i].taskId; 
        ////cout<<"BisonTest After continue taskacced is "<<taskId<<endl;
        if(strlen(taskId) == 0)
        {
			memHero->taskSaveData.acced[i].taskFlag = -1;
            continue;
        }
		
		if (!strcmp(taskId, "task00295") || !strcmp(taskId, "task00419"))
		{
			//马车任务，要看马车还在不在
			//cout<<"!!!!!!!!!!!!!!!!!!!BisonTest :wagon id is "<<wagonId<<endl;
			if (strlen(wagonId) == 0)
			{
				//cout<<"!!!!!!!BisonTest: wagonId is size 000"<<endl;
				memHero->taskSaveData.acced[i].taskFlag = -1;
				continue;
			}
		
			map<string,Wagon*>::iterator it_wagon;
			//cout<<"!!!!!!!!!!!!!!!!!BisonTest：wagonInstMap size is "<<wagonInstMap.size()<<endl;
			it_wagon = wagonInstMap.find(wagonId);
			if (it_wagon == wagonInstMap.end())
			{
				//没有这个马车,把他的马车Id清掉
				// memset(memHero->wagonId, 0, sizeof(memHero->wagonId));
				memHero->taskSaveData.acced[i].taskFlag = -1;
				continue;
			}
			Wagon *myWagon = it_wagon->second;
			if (myWagon->getOwner() != NULL)
			{
				// memset(memHero->wagonId, 0, sizeof(memHero->wagonId));
				memHero->taskSaveData.acced[i].taskFlag = -1;
				continue;
			}
			myWagon->setOwnerId(getIdentity(), this);
			wagonFlag = true;
		}
		
        Task *task = new Task(memHero->taskSaveData.acced[i]);
        //accepted_task_list.insert(pair<string, Task*>(taskId, task));
		memHero->taskState |= (1 << memHero->taskSaveData.acced[i].taskFlag);
		
		accepted_task_list.push_back(task);
    }
	if (!wagonFlag)
	{
		memset(memHero->wagonId, 0, sizeof(memHero->wagonId));
	}
    memcpy(finishTaskMap, memHero->taskSaveData.finMap, sizeof(memHero->taskSaveData.finMap));
	
	abandTaskBySubType(1, false);
	memset(taskNeedKillNpcBossId, 0, sizeof taskNeedKillNpcBossId);
	
	memset(choiseLayerId,'\0',sizeof(choiseLayerId));	

}

/**********************************************
* Author:	Tory
* Date	:	2012.9.12
* Amend :	
* Description：用于构造函数，对game server 中的逻辑数据进程初始化
**********************************************/
void Hero::initHelp(void)
{
	inGuildWarRoom = false;				//不论何时上来都不让玩家在帮战房间中

    stillFlg = false;		//定身标识

    max_accepted_size = 10;     //已接任务列表的最大容量暂设为10，待以后确定

	initMemCopyCause();

}

/* 
* author: tory
* date: xxxx.x.xx
* describe:用于玩家创建新角色时，构建新的角色对象并保存至memcached server，
           调用此构造函数生成的对象完成数据的存储功能后，将会被马上析构
 */
Hero::Hero(char* _nickName, char* _party, int _where)
{
	
	towerLayerRecord = NULL;
	recoverTmeCtn = 0;
	heroState=0;
	memset(viewIdentity,0,sizeof(viewIdentity));	
	where = _where;
    memHero = (MemHero*)malloc(sizeof(MemHero));
	
	memset(memHero->teamerId,'\0',sizeof(memHero->teamerId));
	
	memset(guildWarRoomId, 0, sizeof(guildWarRoomId));
	
	// memHero->dropProbabty = 0;
	
	memHero->cpyRecordMem.initRecordMem();
	//将角色的基本数据赋值给memHero->basicHeroData  
		
	char short_cut_data[256]={0};//默认快捷数据;有疑问 RTX xhm；
	
	init_basic_from_conf(memHero->basicHeroData, _party);
	if(!strcmp(_party,"M"))
	{
		snprintf(short_cut_data,255,"M000,0,0,0,0,0,0,0,0,M014,0,0,0,0,0,0,0,0,0,0");
		for (int i = 0; i < HERO_SKILL_MAX_NUM; i++)
		{
			sprintf(memHero->skills[i].skillId, "M%03d", i);
			memHero->skills[i].level = 0;
		}
		// memcpy(memHero->skills, M_SkillBase, sizeof M_SkillBase);
	}
	if(!strcmp(_party,"H"))
	{
		snprintf(short_cut_data,255,"H000,0,0,0,0,0,0,0,0,H014,0,0,0,0,0,0,0,0,0,0");
		for (int i = 0; i < HERO_SKILL_MAX_NUM; i++)
		{
			sprintf(memHero->skills[i].skillId, "H%03d", i);
			memHero->skills[i].level = 0;
		}
		// memcpy(memHero->skills, H_SkillBase, sizeof H_SkillBase);
	}
	if(!strcmp(_party,"G"))
	{
		snprintf(short_cut_data,255,"G000,0,0,0,0,0,0,0,0,G014,0,0,0,0,0,0,0,0,0,0");
		for (int i = 0; i < HERO_SKILL_MAX_NUM; i++)
		{
			sprintf(memHero->skills[i].skillId, "G%03d", i);
			memHero->skills[i].level = 0;
		}
		// memcpy(memHero->skills, G_SkillBase, sizeof G_SkillBase);
	}
	if(!strcmp(_party,"X"))
	{
		snprintf(short_cut_data,255,"X000,0,0,0,0,0,0,0,0,X014,0,0,0,0,0,0,0,0,0,0");
		for (int i = 0; i < HERO_SKILL_MAX_NUM; i++)
		{
			sprintf(memHero->skills[i].skillId, "X%03d", i);
			memHero->skills[i].level = 0;
		}
		// memcpy(memHero->skills, X_SkillBase, sizeof X_SkillBase);
		
	}
	memHero->skills[0].level = 1;
	
	map<string, Hero_Conf_T>::iterator it_conf = party_2_heroConf.find(memHero->basicHeroData.party);
	if (it_conf == party_2_heroConf.end())
	{
		cout<<"No the hero_conf of the party "<<memHero->basicHeroData.party<<endl;
		exit(1);		//已在配置文件读取的时候对数据做了检查 tory 2013.1.11
	}
	p_conf = &it_conf->second;
	
	memHero->heroSkillExp = p_conf->bornHeroSkillExp;
	string hangUpdata = "0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,50,0,1,50,0,3";
	string systemSetData="0,0,0,0,0,0,50,50";
	string operationData="67,77,81,80,86,66,71,70,90,9,72,83,76,65,84,32,1,1,0,0";//(C,人物属性 M,大地图 Q,任务 P,宠物 V,技能 B,背包 G,帮派 F,好友 Z,挂机 TAB,锁定目标 H,锻造 S,商城 L,邮件 A,活动 T,组队 Space,拾取)+1+1
		
	memset(this->memHero->shortCutData,0,SHORT_CUT_BAR_DATA_SIZE+1);
	memcpy(this->memHero->shortCutData,short_cut_data,strlen(short_cut_data));
	
	memset(this->memHero->hangUpdata,0,HANG_UP_DATA_SIZE+1);
	memcpy(this->memHero->hangUpdata,hangUpdata.c_str(),strlen(hangUpdata.c_str()));	
	
	memset(this->memHero->systemSetData,0,SYSTEM_SET_DATA_SIZE+1);
	memcpy(this->memHero->systemSetData,systemSetData.c_str(),strlen(systemSetData.c_str()));
	
	memset(this->memHero->operationSetData,0,OPERATION_SET_DATA_SIZE+1);
	memcpy(this->memHero->operationSetData,operationData.c_str(),strlen(operationData.c_str()));		
	
	
	// cout<<"int he hero.cpp ---> this->memHero->hangUpdata:"<<this->memHero->hangUpdata<<endl;
	map<string,Map_Src*>::iterator map_it;
    map_it=mapId_connect_map.find(memHero->basicHeroData.mapId);
    if(map_it == mapId_connect_map.end())
    {
        cout<<"return from hero.cpp,cause initMap error"<<memHero->basicHeroData.mapId<<endl;
        return;
    }
	crimCount=0;
	powerCount = 0;
    map_now = map_it->second;
    logPt = MapExchangeLogical(memHero->basicHeroData.pt);
    logPt._y += map_now->getBaseDigst();
	
	char* uuid = cid();
	strncpy(memHero->identity, uuid, IDL+1);
	free(uuid); //avoid mem leak by benliao 20121129
	strncpy(memHero->nickName, _nickName, IDL+1);
		
	//设置人物vip权限
	setVipData(0);
	
	//阵营默认为-1，表示没有加入阵营； 								
	memHero->camp = -1;
	memHero->taskState = 0;
	
	status=0;
    initHelp();

	_fd = -1;
    life_station = LIVE;
	exerciseNeedMoney=20000;
    memHero->level = 1;
    memHero->expAgo = 0;
    memHero->expNow = 0;
    memHero->expForGrow = 100;
	memHero->exercisedata.physique=0;					//体魄
	memHero->exercisedata.wushu=0;						//武术
	memHero->exercisedata.will=0;						//意志
	memHero->exercisedata.shenfa=0;						//身法
	memHero->festivalRewardFlag=0;
	memHero->bloodBagdata.value=0;		//jolly modify
	memHero->magicBagdata.value=0;
	memHero->useGoldForActive=0;
	memHero->worldSpeakTimes=10;
	memHero->testVipTime=-1;
	memHero->downLineDay=myTime.tv_sec/86400;
	
	memHero->internalForcesLevel = 0;
	memHero->internalForces = 0;
	memHero->internalForcesExpNow = 0;
	memHero->internalForcesUpgradeNeedExp = 0;
	memHero->internalForcesBrushExpTimes = 0;
	memHero->goldBrushExpTimes = 0;
	memHero->heroVersion=dataVersion;
	memset(memHero->peiouId,0,sizeof(memHero->peiouId));
	strncpy(memHero->peiouId,"0",sizeof(memHero->peiouId));
	memset(memHero->peiouName,0,sizeof(memHero->peiouName));
	strncpy(memHero->peiouName,"0",sizeof(memHero->peiouName));
		
	judgeExercise();
	for (int i=0;i<4;i++)
	{
		exerciseTemp[i]=0;
	}
	/**********xhm add start************/
	for(int row =0; row <  MAX_ACTIVITY_TYPE;row++)//参加战斗次数为零,有问题RTX xhm
	{
		activityCounts[row ]=0;
	}
	prestige=0;	//默认玩家声望大小是零；
	readNameKills=0;
	memHero->friendLevel=0;
	friendInfo=new Friend();
	memset(memHero->myFriendInfo.myFriendID,'\0',sizeof(memHero->myFriendInfo.myFriendID));
	memset(memHero->myFriendInfo.myFriendInfo,'\0',sizeof(memHero->myFriendInfo.myFriendInfo));
	memset(memHero->myFriendInfo.myBlackListID,'\0',sizeof(memHero->myFriendInfo.myBlackListID));
	memset(memHero->myFriendInfo.myBlackListInfo,'\0',sizeof(memHero->myFriendInfo.myBlackListInfo));
	memset(memHero->titleStore,'\0',ALLTITLELEN);//玩家头衔容器
	memset(memHero->title,'\0',TITLELEN);//玩家当前头衔
	
	for(int row =0; row <  MAX_ACTIVITY_TYPE;row++)//参加战斗次数为零,有问题RTX xhm
	{
		memHero->activityCounts[row]=activityCounts[row];
	}
	memHero->prestige=prestige;
	memHero->readNameKills=readNameKills;
	memHero->cum_recharge_awards=0;//充值累积奖励用！
	memHero->recharge_time=0;
	memHero->useGoldForActive=0;//充值累积奖励用！
	memHero->goods_use_size=0;			//特定物品使用次数；
	memHero->goods_gain_size=0;			//特定物品获得次数；
	/**********xhm add end*************/	
	
    bag=new Bag();
    money=new Money();
	warehouse=new Warehouse();	
	memHero->petboxdataNew.number=0;
        memHero->petboxdataNew.maxNumber=0;
        memHero->petboxdataNew.index=-1;
    	pet_box=new Pet_Box(&memHero->petboxdataNew);
	mysteriousbussiness=new MysteriousBussiness();
	midasTouch=new MidasTouch();
	online_reward=new Reward_Online();
	ride=new Ride();
	online_time=0;
	memHero->rewarddata.last_day=0;
	memHero->rewarddata.last_day_flag=1;
	offline_exp=0;
	last_exp=0;
	memHero->levelFlag=0;
	memHero->rewarddata.chief_flag=0;
	memHero->rewarddata.offline_time=-1;
	
	memHero->fingerGuessingGameCount=0;
	
    for(int i = 0; i < MAX_TASK_MAP_SIZE; i++)
    {
		// cout<<"BisonTest: I hope you to see this@hero.cpp!"<<endl;
		// cout<<"acceptTaskMap["<<i<<"] is "<< acceptTaskMap[i]<<endl;
        finishTaskMap[i] = 0;
    }
	//看来要这么搞了，memHero上来除了一块内存，什么都没有
	TaskSaveData_T myTaskData;
	memHero->taskSaveData = myTaskData;
	MeridData_T meridData;
	memHero->meridData = meridData;
	
    memHero->heroGuildData.guildTitle = -1;            //表明还未加入帮会
    memset(memHero->heroGuildData.guildId, 0, sizeof(memHero->heroGuildData.guildId));     //未加入帮派
    memHero->heroGuildData.guildSigned = false;        //帮派未签到
	memHero->heroGuildData.guildDayRewardTime = 0;
	memset(guildName, 0, sizeof(guildName));
	guild = NULL;
	
    for(int i = 0; i < 10; i++)
    {
        memHero->heroGuildData.guildSkillAdd[i] = 0;
		memHero->heroGuildData.guildSkillAddTotal[i] = 0;
    }
    //离线时间先初始化为当前时间
    memHero->offlineTime = MY_TV_SEC;
	//第一次创建一定是当天的第一次登陆
	isFirstLoginInDay = true;
	cout<<"BisonShow It's the first logining of the hero today!"<<endl;
	 
	//有限制次数的项目在每天第一次登陆的时候初始化
	dayLmtFindGroup = dayLmtGroupForAll;
	//更新到memcached保存数据
	memcpy(memHero->dayLmtItemArr, dayLmtFindGroup.dayLmtItemArr, sizeof(memHero->dayLmtItemArr));
	//日限制项目使用的数量
	memHero->dayLmtUsedNum = dayLmtFindGroup.lastUsedIndex;
	
    merid = new Meridian(); 
    fiveElement = new FiveElem();
	
    memHero->fiveElementData.level = 0;
    memHero->fiveElementData.element = NOELEM;
    memHero->fiveElementData.expNow = 0;
    memHero->fiveElementData.expForNext = 0;
		
	memHero->usePrestigeTime=5;
	
	memHero->crimeValue = 0;					//罪恶值 evan add 2012.8.31
	cpyRecord = new HeroCpyRecord();
	
	for (int i=0;i<20;i++)
	{
		memHero->wearequipdata[i].flag=0;
		memcpy(memHero->wearequipdata[i].goodsid,"0",sizeof(memHero->wearequipdata[i].goodsid));
		memcpy(memHero->wearequipdata[i].typeId,"0",sizeof(memHero->wearequipdata[i].typeId));		
	}		
	canWalking = true;
	
	//初始化充值奖励数据
	memset(memHero->recharge_flag,'\0',sizeof(memHero->recharge_flag));
	memset(memHero->recharge_flag,'0',sizeof(memHero->recharge_flag)-1);
	//初始化血包,蓝包回血参数
	memHero->bloodBagRecoverValue=50;
	memHero->magicBagRecoverValue=25;
	firstIntoGame();
	//初始化人物使用经验丹的数据
	for (int i=0;i<3;i++)
	{
		memHero->expDrug[i]=0;
	}
	memset(memHero->systemOpen,'0',sizeof(memHero->systemOpen));
	//初始化人物使用双倍经验或者三倍经验的数据	
	memHero->expTimes=1;
	memHero->expTimesCount=0;
	//初始化角色个人资料 tory
	memset(memHero->heroInfor, 0, 1024);

	for(int i=0; i<10; i++)
	{
		memHero->allBuffDrug[i].level = 0;
		memset(memHero->allBuffDrug[i].type_id,0,sizeof(memHero->allBuffDrug[i].type_id));		//药品类型ID
		memHero->allBuffDrug[i].effect_type=0;		//buff药作用类型
		memHero->allBuffDrug[i].effect_value=0;		//buff药作用量
		memHero->allBuffDrug[i].remain_time=0;		//剩余时间	
	}
	
	memHero->rideState = RIDE_STATE_FREE;		//未骑乘状态
	prepareRideSecond = 0;						//骑乘准备时刻
	
	for (int i=0;i<10;i++)
	{
		for (int j=0;j<50;j++)
		{
			memHero->targetItem[i][j]=0;
		}
		memHero->targetFinishNumber[i]=0;
	}
}

//若完成武林目标 ，则根据对应索引修改武林目标完成状态 ，参数 容器下标
bool Hero::setWulinTarget(int page,int id)
{
	if (id<0||id>49)
	{
		return false;
	}
	if (page<0||page>9)
	{
		return false;
	}
	if(memHero->targetItem[page][id]==1)
	{
		return false;
	}
	else if (memHero->targetItem[page][id]==0)
	{
		memHero->targetItem[page][id]=1;
		if (memHero->targetFinishNumber[page]!=-1)
		{
			memHero->targetFinishNumber[page]++;
		}		
		return true;
	}
	else
	{
		return false;
	}
}

char* Hero::getMapId(void)
{
    ////cout<<"mapId is :"<<mapId<<endl;
    return memHero->basicHeroData.mapId;
} 
void Hero::setMapId(const char *_mapId)
{
	int ret = -1;
	if (_mapId != NULL)
	{
		ret = happyCheck(memHero->basicHeroData.mapId, _mapId);
	}
    int len=strlen(_mapId);
    strncpy(memHero->basicHeroData.mapId, _mapId, len + 1);
	if (ret == 1)
	{
		startHappyTimer();
	}
	else if (ret == 2)
	{
		endHappyTimer();
	}
    
}
int  Hero::gethero_PK_status(void)						//玩家PK模式：1，不能战斗；2，自由模式；3，阵营模式；4，帮派模式； evan add 2012.9.23
{
	return hero_PK_status;
}
void Hero::sethero_PK_status(int _hero_PK_status)
{
	hero_PK_status = _hero_PK_status;
}
	
/***************************************
* Author：Tory
* Date: 2012.9.24
* Description：设置角色实例ID,先通过cid生成heroID,已heroID为键值，将memHero存储
*               至memcached server成功后，调用此接口初始化角色下的identity
******************************************/
void Hero::setIdentity(char* _identity)
{
	if(_identity == NULL && strlen(_identity) > IDL)
	{
		strncpy(memHero->identity, "ERROR", IDL);
	}else
	{
		strncpy(memHero->identity, _identity, IDL+1);
	}
	
	
}
	
char* Hero::getIdentity(void) const
{
    return memHero->identity;
}
char* Hero::getNickName(void) const
{
    return memHero->nickName;
}

/************************************************************
	函数作用：  阵营相关操作函数； 有疑问RTX xhm;
	参数说明：  	  _camp	0:宗教 1:邪教 2:游侠；
				campWarType 阵营战类型（1,普通阵营战 2,统领战 3,盟主战）；
				campWarRoomNum  阵营战房间号；
				enterCampWarMark 是否在阵营战；
				CampWarFinishMark 阵营战是否结束；
	  返回值：  CampData_T 阵营战数据；
				bool 成功true，失败false；
************************************************************/	
void Hero::setCamp(int _camp)//设置阵营信息
{
    memHero->camp=_camp;
}
int Hero::getCamp() //获得角色阵营信息
{
    return memHero->camp;
}
void Hero::setCampWarData(int _campWarType,int _campWarRoomNum,bool _campWarStartMark,bool _CampWarFinishMark)
{
    campWarData.campWarType=_campWarType;
    campWarData.campWarRoomNum=_campWarRoomNum;
    campWarData.campWarStartMark=_campWarStartMark;
    campWarData.CampWarFinishMark=_CampWarFinishMark;
}
int  Hero::getCampWarType()
{
	return campWarData.campWarType;
}
CampData_T Hero::getCampWarData()
{
    return campWarData;
}

bool Hero::isInCampWar()
{
    return campWarData.campWarStartMark;
}

bool Hero::isInCampResWar()
{
	return (campWarData.campWarStartMark && campWarData.campWarType == 4);
}

bool Hero::exitCampWar()
{
    campWarData.campWarStartMark=false;
}

bool Hero::isEntCamp()
{
    if(memHero->camp>=0 && memHero->camp <=2)
        return true;
    return false;
}

void  Hero::setCampWarStartMark(bool _isStart)//设置阵营战开启标志；
{
    campWarData.campWarStartMark=_isStart;
	return;
}


/************************************************************
	函数作用：  增加活动列表对应类型的次数 有疑问RTX xhm;
	参数说明：  type 0:参与帮战次数 1:参与阵营战1次数 2:参与阵营战2次数 3:参与阵营战3次数 4:下副本次数 5:击打活动boss次数
				size 本次增加的次数；
				
	  返回值：  bool 成功true，失败false；
************************************************************/
bool 
Hero::addActivityCounts(int _type,unsigned int _size)
{
	if(_type >= MAX_ACTIVITY_TYPE && _type < 0)	//判断类型错误
		return false;
		
	if(_size < 0)//如果增加的次数为负数，返回；
		return false;
		
	if(activityCounts[_type]+_size < activityCounts[_type])//判断溢出，如果溢出不再增加；
		return false;
		
	activityCounts[_type]+=_size;
	memHero->activityCounts[_type]=activityCounts[_type];
	return true;
}
void
Hero::getActivityCounts(unsigned long  _activityCounts[])
{
	int temp=0;
	if(cpyRecord != NULL)
	{
		temp = cpyRecord->getEntSum();// 下副本次数
		if(temp < 0)
		{
			cout<<"[XHM WARNING] cpyRecord->getEntSum() value less than 0(hero.cpp)!"<<endl;
			//重新赋值；
			temp=0;
		}
		
		_activityCounts[4] = temp;	
		//_activityCounts[5]=;							// 击杀活动boss次数		等着真哥赋值；
	}else{
		cout<<"[XHM WARNING] cpyRecord == NULL,Data ERROR(hero.cpp)!"<<endl;
	}

	for(int index = 0; index < MAX_ACTIVITY_TYPE; index++)
	{
		if(activityCounts[index] < 0)
		{
			cout<<"[XHM WARNING] cactivityCounts[index] < 0,Data ERROR(hero.cpp)!"<<endl;	
			continue;
		}
		
		_activityCounts[index]=activityCounts[index];
	}
}



/*****************************************************
	函数作用：  声望函数说明 有疑问RTX xhm;
	参数说明：  addValue    要增加的Value大小；
				reduceValue 将要减少后的value大小；			
	  返回值：  unsigned int 操作后当前value的值；
******************************************************/
unsigned int 
Hero::getPrestigeValue()
{
	return prestige;
}

unsigned int 
Hero::addPrestigeValue(unsigned int addValue)
{
	if(prestige+addValue < prestige)
		return prestige;
		
	prestige+=addValue;
	memHero->prestige=prestige;
	
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",23,POPULARITY_RETURN,prestige);
	send_msg(_fd,g_out_buf);
	return prestige;	
}

unsigned int 
Hero::reducePrestigeValue(unsigned int reduceValue)
{
	if(prestige-reduceValue < 0)
		prestige=0;
	else
		prestige -= reduceValue;
		
	memHero->prestige=prestige;	
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",23,POPULARITY_RETURN,prestige);
	send_msg(_fd,g_out_buf);
	return prestige;
}


/*****************************************************
	函数作用：  击杀红名数函数接口 有疑问RTX xhm;
	参数说明：  addValue    要增加的Value大小；
				reduceValue 将要减少后的value大小；			
	  返回值：  unsigned int 操作后当前value的值；
******************************************************/
unsigned int 
Hero::getReadNameKills()
{
	return readNameKills;
}

unsigned int 
Hero::addReadNameKillsValue(unsigned int addValue)
{
	if(readNameKills+addValue < readNameKills)
		return readNameKills;
		
	readNameKills+=addValue;
	
	memHero->readNameKills=readNameKills;
	
	return readNameKills;
}

unsigned int 
Hero::reduceReadNameKillsValue(unsigned int reduceValue)
{
	if(readNameKills-reduceValue < 0)
		readNameKills=0;
	else
		readNameKills -= reduceValue;
		
	memHero->readNameKills=readNameKills;
	
	return readNameKills;
}



/*****************************************************************
	函数作用：  获取战力大小；这个函数获取数据用于排名，有疑问 RTX xhm
	参数说明：  注意：powerInfo必须大于5；
				将战力数据存储到参数powerInfo里面
				（ 0--16 0生命值上限 1,外功伤害.....）
		调用    src/viewInfo/rankInfo.cpp,注意：powerInfo必须大于17；
******************************************************************/
void
Hero::getPowerInfo(unsigned long powerInfo[])
{	
	int tempValue=0;
	tempValue = memHero->basicHeroData.lifeUpperVal;			//生命值上限
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.lifeUpperVal value less than 0(hero.cpp)!"<<endl;
		tempValue=0;
	}
	powerInfo[0]=tempValue;
	
	tempValue = memHero->basicHeroData.magicUpperVal;					//真气值上限
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.magicUpperVal value less than 0(hero.cpp)!"<<endl;
		tempValue=0;	
	}	
	powerInfo[1]=tempValue;
	
	tempValue = memHero->basicHeroData.outattack;				//外功攻击
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.outattack value less than 0(hero.cpp)!"<<endl;
		tempValue=0;	
	}		
	powerInfo[2]=tempValue;
	
	tempValue = memHero->basicHeroData.inattack;				//内功攻击
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.inattack value less than 0(hero.cpp)!"<<endl;	
		tempValue=0;	
	}	
	powerInfo[3]=tempValue;
	
	tempValue = memHero->basicHeroData.outdefense;				//外功防御
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.outdefense value less than 0(hero.cpp)!"<<endl;	
		tempValue=0;	
	}	
	powerInfo[4]=tempValue;
	
	tempValue = memHero->basicHeroData.indefense;				 //内功防御
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.indefense value less than 0(hero.cpp)!"<<endl;			
		tempValue=0;	
	}
	powerInfo[5]=tempValue;
	
	tempValue=memHero->basicHeroData.hited;					//命中
	if(tempValue < 0)
	{	
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.hited value less than 0(hero.cpp)!"<<endl;				
		tempValue=0;	
	}
	powerInfo[6]=tempValue;
	
	tempValue = memHero->basicHeroData.crit;					//暴击
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.crit value less than 0(hero.cpp)!"<<endl;		
		tempValue=0;	
	}
	powerInfo[7]=tempValue;
	
	tempValue=memHero->basicHeroData.dodge;					//闪避
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.dodge value less than 0(hero.cpp)!"<<endl;		
		tempValue=0;
	}
	powerInfo[8]=tempValue;
	
	tempValue = memHero->basicHeroData.tenacity;				//韧性
	if(tempValue < 0)
	{
		//重新计算值大小，欠缺方法计算；
		cout<<"[XHM WARNING] memHero->basicHeroData.tenacity value less than 0(hero.cpp)!"<<endl;			
		tempValue=0;
	}
	powerInfo[9]=tempValue;
}


	
/*****************************************************************
	函数作用：  好友度的相关操作，有疑问 RTX xhm  //策划将好友度改为魅力值，命名错误
	参数说明：  _addValue将要增加的好友度的大小；
				_reduceValue将要减少的好友度的大小；
	  返回值：	当前操作后好友度的大小；
******************************************************************/
int 
Hero::getFriendLevel()
{
	return memHero->friendLevel;
}

int 
Hero::addFriendLevel(int _addValue)
{
	if(_addValue+memHero->friendLevel < memHero->friendLevel)
			return memHero->friendLevel;
		
	memHero->friendLevel+=_addValue;						//保存好友度大小；
	return memHero->friendLevel;
}

int Hero::reduceFriendLevel(int _reduceValue)
{
	if(memHero->friendLevel - _reduceValue < 0)
	{
		return 0;
	}
	memHero->friendLevel-=_reduceValue;					//保存好友度大小；
	return memHero->friendLevel;
}

/*****************************************************************
函数作用：  塔防组队有关函数，有疑问 RTX xhm
参数说明：  _towerDefTeamId设置的塔防队伍ID；
  返回值：	当前当前塔防队伍的ID；
******************************************************************/
string 
Hero::getTowerDefTeamId(void)
{
	return myTowerDefTeamId;
}

void 
Hero::setTowerDefTeamId(string _towerDefTeamId)
{
	myTowerDefTeamId=_towerDefTeamId;
}
	
	
int Hero::getMagicUpperVal()
{
    return memHero->basicHeroData.magicUpperVal;
}
int Hero::getMagicVal(void)
{
    return memHero->basicHeroData.magicVal;
}

void Hero::setMagicUpperVal(int _magicUpperVal)
{
	if (_magicUpperVal<0)
	{
		cout<<"you want to modify magicUpperVal to <0 ,it is a big error "<<endl;
		return;
	}
    
	memHero->basicHeroData.magicUpperVal = _magicUpperVal;
	
	if(memHero->basicHeroData.magicVal >= memHero->basicHeroData.magicUpperVal)	//防止当前蓝量值大于蓝量上限值 <tory>
	{
		memHero->basicHeroData.magicVal = memHero->basicHeroData.magicUpperVal;
	}
}

void Hero::setMagicVal(int _magicVal)
{
	if(_magicVal < 0)
	{
		return; 
	}
	if(_magicVal >= memHero->basicHeroData.magicUpperVal)
	{
		memHero->basicHeroData.magicVal = memHero->basicHeroData.magicUpperVal; 
	}
    memHero->basicHeroData.magicVal = _magicVal+memHero->allBuffDrug[1].effect_value;

}

void Hero::setNickName(string _nickName)
{
	memset(memHero->nickName, 0, sizeof memHero->nickName);
    strncpy(memHero->nickName, _nickName.c_str(), _nickName.size() + 1);
}

//获得当前像素点坐标
Point Hero::getLocation(void) const
{
    return memHero->basicHeroData.pt;
}
//更新像素点坐标和逻辑点坐标
void Hero::setLocation(Point _pt, int flag)
{
	if (flag == 0)
	{			
		keyPath.clear();
		currPt = endPt = _pt;
	}
	Nbox * box = map_now->getBox();
	if (box == NULL)
	{
		return;
	}
	Point oldPt = box->mapLogToSrcPtv(memHero->basicHeroData.pt);
	Point newPt = box->mapLogToSrcPtv(_pt);
	if (oldPt == newPt)
	{
	} else {
		StyObj obj(memHero->identity,HERO_STYLE_TYPE);
		box->deleteInOldSrc(oldPt, obj);
		/*从新屏中插入*/
		box->inputInOldSrc(newPt, obj);
	}
	// cout<<"_pt._x"<<_pt._x<<endl;
	// cout<<"_pt._y"<<_pt._y<<endl;
    memHero->basicHeroData.pt._x=_pt._x;
    memHero->basicHeroData.pt._y=_pt._y;
    logPt = MapExchangeLogical(memHero->basicHeroData.pt);
    logPt._y += map_now->getBaseDigst();
	
	if (isInGuildWarRoom())
	{
		if (robFlagWarManage->scorePlaceCheck(this))
		{
			cout<<"robFlagWarManage->scorePlaceCheck(this) is true"<<endl;
			cout<<"robFlagWarManage->scorePlaceCheck(this) is true"<<endl;
			robFlagWarManage->bringFlagBack(this);
		}
	}
//    memHero->logPt=logPt;

}
int Hero::getAttack(void)
{
    return memHero->basicHeroData.attack;
}
void Hero::setAttack(int _attack)
{
    memHero->basicHeroData.attack=_attack;
    memSet();
}

void Hero::setFd(int fd)
{
    _fd=fd;
}
int Hero::getFd(void) const
{
    return _fd;
}
Hero::~Hero(void)
{
	cout<<"in ~Hero start"<<endl;
	StyObj obj(memHero->identity,HERO_STYLE_TYPE);
	map_now->deleteID(obj);
	heroId_to_pHero.erase(memHero->identity); //added by benliao 2012.12.1
	
	deleteTowerLayerRecord();
	if(cpyRecord != NULL)
	{
		delete cpyRecord;
		cpyRecord = NULL;
	}
	stopMoveTimer();
	
	stop_buff_debuff_timer(1);
	if(bag != NULL)	delete bag;
	if(money != NULL) delete money;
	if(warehouse != NULL) delete warehouse;
	if(pet_box != NULL)	delete pet_box; 
	//释放副本进出状态记录数据
	if(cpyRecord != NULL) delete cpyRecord;
	//释放五行数据的内存
   	if(fiveElement != NULL) delete fiveElement;
	//释放经脉数据的内存
	if(merid != NULL) delete merid;
	
	//释放掉好友信息实例；
	if(friendInfo != NULL) delete friendInfo;
	
	if(mysteriousbussiness!= NULL) delete mysteriousbussiness;
        if(midasTouch != NULL) delete midasTouch;
	if(online_reward != NULL) delete online_reward;

    //析构已接任务列表
    list<Task*>::iterator it_task;
    for(it_task = accepted_task_list.begin(); it_task != accepted_task_list.end();it_task++)
    {
        Task *task = (*it_task);
        delete task;
    }
    accepted_task_list.clear();
	
	//释放装备数据内存 jolly
    map<string,Equipment*>::iterator equip_it;
    for (equip_it=heroAllEquip.begin();equip_it!=heroAllEquip.end();equip_it++){
		Equipment *equipment=equip_it->second;
		if(equipment != NULL){
			delete(equipment);
			equipment = NULL;
		}
	}
	heroAllEquip.clear();	
	
	//delete memHero;
	if(memHero != NULL){
		free(memHero);
	}

	cout<<"in ~Hero end"<<endl;
}

int Hero::getLifeStation(void)
{
    return life_station;
}

void Hero::setLifeStation(int life)
{
	cout<<"FFFF has set lifeStation"<<endl;
    life_station=life;
	if (life==0)
	{
		stopCollectTimer(7);
		if (isInGuildWarRoom())
		{
			robFlagWarManage->stopBring(this);
		}
		
		stop_buff_debuff_timer();
		if (inGuildWarRoom)
		{
			cout<<"FFFFF in guild war room"<<endl;
			startRevivalTimer(5);
		} else if (isInCampResWar())
		{
			cout<<"FFFFF Start revival in camp res war room"<<endl;
			// startRevivalTimer(3);
			startRevivalTimer(5);
			cout<<"start 111111111111111 second"<<endl;
		} else {
			cout<<"FFFFFF not in guild war room"<<endl;
			startRevivalTimer(31);
			snprintf(g_out_buf,20480,"%d,%d,%d",7,HERO_DEAD,1);
			send_msg(_fd,g_out_buf);
		}
	}

}

static void revival_cb(struct event_base* loop, ev_timer *think, int revents)
{
	puts("Have really called the revival_cb function!!!!!!");
	cout<<"Have really called the revival_cb function!!!!!!"<<endl;
	Hero *hero = (Hero*)think->target;
	if (hero == NULL)
	{
		cout<<"revival hero find no hero no need to revival"<<endl;
		return;
	}
	if (hero->isInGuildWarRoom())
	{
		cout<<"hero in guild war room revival"<<endl;
		int ret = robFlagWarManage->revival(hero);
		if (ret != 0)
		{
			cout<<"hero in guild war revival failed!"<<endl;
			sendRevivalMsg(hero, 1);
		}
	} else if (hero->isInCampResWar())
	{
		cout<<"Have call the campWarController.campResWarRevival"<<endl;
		int ret = campWarController.campResWarRevival(hero);
		if (ret != 0)
		{
			cout<<"hero in guild war revival failed!"<<endl;
			sendRevivalMsg(hero, 1);
		}
	}
	else {
		cout<<"I don't believe it is come from here!!!"<<endl;
		sendRevivalMsg(hero, 1);
	}
}

//开启玩家复活倒计时
int Hero::startRevivalTimer(int revivalTime)
{
	if (life_station != DEAD)
	{
		cout<<"startRevivalTimer but lifeStation is not DEAD"<<endl;
		return 1;
	}
	
	ext_ev_timer_init(&revivalTimer, revival_cb, revivalTime, 0, this);
	ev_timer_start(loops, &revivalTimer);
	return 0;
}

//停止玩家复活倒计时
int Hero::stopRevivalTimer()
{
	if (ev_timer_is_running(loops, &revivalTimer))
	{
		ev_timer_stop(loops, &revivalTimer);
	}
}

//2012.3.26 Tory Add 获取角色的图片ID （已失效）
string Hero::getPhotoId(void)
{
    photoId.erase();
    photoId = "H";
    photoId.insert(1, memHero->basicHeroData.party);
    photoId = photoId+"00101";          //按角色等级选择图片组
    
    return photoId;
}

//Tory Add 2012.3.15
char*   Hero::getParty()                            //获得角色门派
{
    return memHero->basicHeroData.party;
}

int     Hero::getLevel(void)                            //获得角色等级
{
    return memHero->level;
}   

/* 
* authro: tory 20121.12.28
* describe:将角色状态设置为登陆加载状态 	 
*/
void Hero::setLoadState(bool _isLoading)                       
{
    isLoading = _isLoading;
}

/* 
* authro: tory 20121.12.28
* describe:获得角色的的登陆加载状态 	 
*/
bool Hero::getLoadState()                                 
{
    return isLoading;
}

	
//设置逻辑点坐标，同时更改玩家对应的像素点
void Hero::setLogPt(Point _logPt)
{
    logPt = _logPt; 
    _logPt._y -= map_now->getBaseDigst();
    memHero->basicHeroData.pt = LogicalExchangeMap(_logPt);  
}
//获得逻辑点坐标
Point Hero::getLogPt(void)
{
    return logPt;
};

//Add by Tory 2012.3.27 15:30
int  Hero::getAtk_range()                                   //获得角色攻击范围
{
    return memHero->basicHeroData.atk_range;
}

//设置生命上限值
void Hero::setLifeUpperVal(int _lifeUpperVal)
{
	if (_lifeUpperVal<0)
	{
		cout<<"SomeOne set lifeUpperVal <0 ,it is a big error"<<endl;
		return;
	}
    
	memHero->basicHeroData.lifeUpperVal = _lifeUpperVal;
	
	if(memHero->basicHeroData.lifeVal >= memHero->basicHeroData.lifeUpperVal)	//防止当前血量值大于血量上限值 <tory>
	{
		memHero->basicHeroData.lifeVal = memHero->basicHeroData.lifeUpperVal;
	}
}

int Hero::getAttkType()
{
	return memHero->basicHeroData.attkType;
}

int Hero::getLifeUpperVal(void)
{
    return memHero->basicHeroData.lifeUpperVal+memHero->allBuffDrug[0].effect_value;
}
int Hero::getLifeVal(void)
{
    return memHero->basicHeroData.lifeVal;
}

void Hero::setLifeVal(int _lifeVal)
{
	if (_lifeVal < 0)
	{
		memHero->basicHeroData.lifeVal = 1;	
		return;
	}
	if(_lifeVal >= memHero->basicHeroData.lifeUpperVal)
    {
		memHero->basicHeroData.lifeVal = memHero->basicHeroData.lifeUpperVal; 
	}
	memHero->basicHeroData.lifeVal = _lifeVal;
}

int  Hero::getAttackAndDefense(void)      //攻防总值
{
    return memHero->basicHeroData.AttackAndDefense;
}
void Hero::setAttackAndDefense(int _AttackAndDefense)
{
	if(_AttackAndDefense < 0) return;
    memHero->basicHeroData.AttackAndDefense = _AttackAndDefense;
//    memSet();
}
int Hero::getBufferCD(void)          //攻击CD
{
    return memHero->basicHeroData.bufferCD;
}
void Hero::setBufferCD(int _bufferCD)
{
	if(_bufferCD < 0) return;
    memHero->basicHeroData.bufferCD = _bufferCD;
//    memSet();
}                          
int Hero::getHited(void)                    //命中
{
	int hited = memHero->basicHeroData.hited;
	if (skillBuffState & DEBUF_LOSE_HIT_STATE)
	{
		hited -= skillBuff[getIndexByState(DEBUF_LOSE_HIT_STATE)].totalVal;
	}
	if (hited < 0)
	{
		hited = 0;
	}
    return hited+memHero->allBuffDrug[2].effect_value;
}
void Hero::setHited(int _hited)
{
	if(_hited < 0) return;
    memHero->basicHeroData.hited = _hited;
//    memSet();
}
int Hero::getCrit(void)        //暴击
{
	int crit = memHero->basicHeroData.crit;
	if (skillBuffState & BUFF_ADD_CRIT_STATE)
	{
		crit += skillBuff[getIndexByState(BUFF_ADD_CRIT_STATE)].totalVal;
	}
	if (crit <= 0)
	{
		crit = 0;
	}
	
    return crit+memHero->allBuffDrug[3].effect_value;
}
void Hero::setCrit(int _crit)
{
	if(_crit <0) return;
    memHero->basicHeroData.crit = _crit;
 //   memSet();
}

int Hero::getDodge(void)            //闪避
{
	int dodge = memHero->basicHeroData.dodge;
	if (skillBuffState & BUFF_ADD_DODGE_STATE)
	{
		dodge += skillBuff[getIndexByState(BUFF_ADD_DODGE_STATE)].totalVal;
	}
	if (dodge <= 0)
	{
		dodge = 0;
	}
	
    return dodge+memHero->allBuffDrug[4].effect_value;
}
void Hero::setDodge(int _dodge)
{
	if(_dodge < 0) return;
    memHero->basicHeroData.dodge = _dodge;
 //   memSet();
}

int  Hero::getTenacity(void)             //韧性
{
	int tenacity = memHero->basicHeroData.tenacity;
	if (skillBuffState & DEBUF_LOSE_TENC_STATE)
	{
		tenacity -= skillBuff[getIndexByState(DEBUF_LOSE_TENC_STATE)].totalVal;
	}
	
	if (tenacity <= 0)
	{
		tenacity = 0;
	}
	
    return tenacity+memHero->allBuffDrug[5].effect_value;
}
void Hero::setTenacity(int _tenacity)
{
	if(_tenacity < 0) return;
    memHero->basicHeroData.tenacity = _tenacity;
//    memSet();
}           
int Hero::getOutRatio(void)             //外攻比例
{
    return memHero->basicHeroData.outratio;
}
void Hero::setOutRatio(int _outratio)
{
    if(_outratio < 0) return;
    memHero->basicHeroData.outratio = _outratio;
 //   memSet();
}


int Hero::getInRatio(void)              //内攻比例
{
    return memHero->basicHeroData.inratio;
}
void Hero::setInRatio(int _inratio)  
{
    if(_inratio < 0) return;
    memHero->basicHeroData.inratio = _inratio;
 //   memSet();
}   

int Hero::getAttackRatio(void)//攻击比例
{
    return memHero->basicHeroData.attackratio;
}
void Hero::setAttackRatio(int _attackratio)
{
	if(_attackratio < 0) return;
    memHero->basicHeroData.attackratio = _attackratio;
//    memSet();
}
int Hero::getDefenseRatio(void)//防御比例
{
    return memHero->basicHeroData.defenseratio;
}
void Hero::setDefenseRatio(int _defenseratio)
{
    if(_defenseratio < 0) return;
    memHero->basicHeroData.defenseratio = _defenseratio;
 //   memSet();
}

int  Hero::getOutAttack(void)    //外功攻击
{
	int outattack = memHero->basicHeroData.outattack;
	if (skillBuffState & DEBUF_LOSE_DF_AT_STATE)
	{
		outattack -= skillBuff[getIndexByState(DEBUF_LOSE_DF_AT_STATE)].totalVal;
	}
	if (skillBuffState & BUFF_ADD_SACRF_STATE)
	{
		outattack += skillBuff[getIndexByState(BUFF_ADD_SACRF_STATE)].totalVal;
	}
	
	if (outattack <= 0)
	{
		outattack = 0;
	}
    return outattack+memHero->allBuffDrug[6].effect_value;
}
void Hero::setOutAttack(int _outattack)
{
    if(_outattack < 0) return;
    memHero->basicHeroData.outattack = _outattack;
//    memSet();
}

int Hero::getInAttack(void)         //内功攻击
{
	int inattack = memHero->basicHeroData.inattack;
	if (skillBuffState & DEBUF_LOSE_DF_AT_STATE)
	{
		inattack -= skillBuff[getIndexByState(DEBUF_LOSE_DF_AT_STATE)].totalVal;
	}
	if (inattack <= 0)
	{
		inattack = 0;
	}
    return inattack+memHero->allBuffDrug[7].effect_value;
}
void Hero::setInAttack(int _inattack)
{
    if(_inattack < 0) return;
    memHero->basicHeroData.inattack = _inattack;
 //   memSet();
}              
int Hero::getOutDefense(void)  //外功防御
{
	int outdefense = memHero->basicHeroData.outdefense;
	if (skillBuffState & DEBUF_LOSE_DF_AT_STATE)
	{
		outdefense -= skillBuff[getIndexByState(DEBUF_LOSE_DF_AT_STATE)].totalVal;
	}
	if (outdefense <= 0)
	{
		outdefense = 0;
	}
    return outdefense+memHero->allBuffDrug[8].effect_value;
}
void Hero::setOutDefense(int _outdefense)
{
    if(_outdefense < 0) return;
    memHero->basicHeroData.outdefense = _outdefense;
//    memSet();
}
int Hero::getInDefense(void)  //内功防御
{
	int indefense = memHero->basicHeroData.indefense;
	if (skillBuffState & DEBUF_LOSE_DF_AT_STATE)
	{
		indefense -= skillBuff[getIndexByState(DEBUF_LOSE_DF_AT_STATE)].totalVal;
	}
	if (indefense <= 0)
	{
		indefense = 0;
	}
    return indefense+memHero->allBuffDrug[9].effect_value;
}
void Hero::setInDefense(int _indefense)
{
	if(_indefense < 0) return;
    memHero->basicHeroData.indefense = _indefense;
//    memSet();
}

/**Evan add 2012.3.29   start**/
/*2012.4.5 evan add start*/
int Hero::getSec_Hurt(void)            //秒伤害
{
    return memHero->basicHeroData.sec_hurt;
}
void Hero::setSec_Hurt(int _sec_hurt)
{
    if(_sec_hurt < 0) return;
    memHero->basicHeroData.sec_hurt = _sec_hurt;
//    memSet();
}
int  Hero::getOutHurt(void)              //外功伤害
{
    return memHero->basicHeroData.outhurt;
}
void Hero::setOutHurt(int _out_hurt)
{
    if(_out_hurt < 0) return;
    memHero->basicHeroData.outhurt = _out_hurt;
//    memSet();
}
int Hero::getInHurt(void)               //内功伤害
{
    return memHero->basicHeroData.inhurt;
}
void Hero::setInHurt(int _inhurt)
{
    if(_inhurt < 0) return;
    memHero->basicHeroData.inhurt = _inhurt;
 //   memSet();
}


/*2012.4.5 evan add end*/
int  Hero::getexpAgo(void)                          //上一级升级所需经验 evan 2012.6.26
{
    return memHero->expAgo;
}

/*evan add  2012.4.10 start*/
// string Hero::getSkill_Before_Id(void)  //角色上次使用的技能
// {
    // return skill_before_id;
// }

// void Hero::setSkill_Before_Id(string _skill_before_id)
// {
    // skill_before_id = _skill_before_id;
// }
/*evan add  2012.4.10 end*/


//获取角色当前经验 tory 2012.12.21
int Hero::getExpNow(void)
{
    if (memHero->expNow < 0)
    {
        memHero->expNow = 0;
    }
    return memHero->expNow;
}

//更新当前角色拥有的经验值 evan add 2012.9.17 废弃     
bool Hero::useExpNow(int _expnow)				
{
	if (_expnow <= 0)
	{
		return false;
	}
	if (memHero->expNow - _expnow < 0)
	{
		return false;
	}
	else {
		memHero->expNow -= _expnow;
	}
	
	//检查是否能升级	
	growUp();
	return true;
}

/*  flag为0：增加角色的当前经验,并调用角色升级函数 
	flag为1：设置当前角色经验	tory 2012.12.21 */
void Hero::setExpNow(int exp, int flag)
{
	if (exp <= 0)
		return;
		
	if (flag == 0)		
		memHero->expNow += exp;
	else		
		memHero->expNow = exp;
	
	if (memHero->level >= MAX_HERO_LEVEL)    //已到满级
	{
		if (memHero->expNow >= memHero->expForGrow)
		{
			memHero->expNow = memHero->expForGrow - 1; //不再调用升级方法
		//	return;
		}
	}	
	
	//检查是否能升级	
	Hero::growUp();
} 

/*
* author: bison
* describe:人物经验变化处理
* amend:	tory 2012.12.21
*/
void Hero::growUp(void)
{
	bool isBeginCycleTask = false;
    if (memHero->expNow < memHero->expForGrow)
	{
		//这个玉迪说不能删掉，不够升级时，只发消息和客户端同步经验信息
		memset(g_out_buf, 0, 20480);
        	sprintf(g_out_buf, "3,7,0,%d,%d", memHero->expForGrow, memHero->expNow);
		send_msg(_fd, g_out_buf);
		// return;
	}
	else if(memHero->expNow >= memHero->expForGrow)
    {
        char account_msg[1024] = { '\0' };
        while (memHero->expNow >= memHero->expForGrow)
        {
            memHero->expNow -= memHero->expForGrow;
            memHero->level++;
			if (memHero->level >= MAX_HERO_LEVEL)
			{
				memHero->level = MAX_HERO_LEVEL;
				if (memHero->expNow >= memHero->expForGrow)
				{
					memHero->expNow = memHero->expForGrow - 1; //不再调用升级方法
				}
				// return;
			}
			if (memHero->level == BEGIN_CYCLE_TASK_LEVEL)
			{
				isBeginCycleTask = true;
			}
			
            pet_box->carryNum(memHero->level);
            memHero->expAgo = memHero->expForGrow;

            /* 更新升级到下一级需要的经验 */
            Hero::growExp();
            /* 更新角色升级后的属性 */
            Hero::herogrowup();

            /*记录升级的流水账 jolly 12.10 start*/
            snprintf(account_msg, sizeof(account_msg), "%d,%d,%s,%d,%s,%s,%d", 5, 0, server_name, (int)myTime.tv_sec, getNickName(), getIdentity(),\
                        getLevel());
            write_log(account_msg);
			cout<<"account_msg:"<<account_msg<<endl;
            //添加头衔，十级，初入江湖
            if (memHero->level == 10)
            {
                addTitle("T001");
            }
			else if (memHero->level == 20)
            {
				/*20级，初显锋芒*/
				addTitle("T002");				
                online_reward->startOnlineReward(g_out_buf, sizeof(g_out_buf));
                send_msg(_fd, g_out_buf);
            } 
			else if (memHero->level == 30)
            {
				/*30级，略有小成*/
				addTitle("T003");
            } 
			else if (memHero->level == 40)
            {
				/*40级，名声鹊起*/
				addTitle("T004");				
                online_reward->levelSetStage();
            } 
			else if (memHero->level == 50)
            {
				/*50级，锋芒毕露*/
				addTitle("T005");		
				updataSingleTarget(4,4);
			} 
			else if (memHero->level == 60)
            {
				/*60级，名声显赫*/
				addTitle("T006");
				
                online_reward->levelSetStage();
				
				updataSingleTarget(5,6);
            } 
			else if (memHero->level == 70)
            {
				/*70级，如雷贯耳*/
				addTitle("T007");
            } 
			else if (memHero->level == 80)
            {
				/*80级，威风八面*/
				addTitle("T008");
            }
        }

        /* 玩家等级有变化，把玩家等级同步到帮派内 */
		Guild* heroGuild = getGuildWithId(memHero->heroGuildData.guildId);
        if (heroGuild != NULL)
        {
	    //by benliao 2013.1.21  暂时屏蔽
            heroGuild->setHeroLevel(memHero->identity, memHero->level);
        }

        //tory modify 2012.12.21 It doesn't need to send message to client like this!!!
        memset(g_out_buf, 0, 20480);
        sprintf(g_out_buf, "%d,%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 3, 7, 1, memHero->identity, memHero->level,\
                   memHero->basicHeroData.lifeUpperVal, memHero->basicHeroData.magicUpperVal,\
                   memHero->expForGrow, memHero->expNow,\
                   memHero->basicHeroData.outattack, memHero->basicHeroData.inattack,\
                   memHero->basicHeroData.outdefense, memHero->basicHeroData.indefense,\
                   memHero->basicHeroData.hited, memHero->basicHeroData.crit,\
                   memHero->basicHeroData.dodge, memHero->basicHeroData.tenacity);
        send_msg(_fd, g_out_buf);   //播放升级动画，并更新客户端角色战斗属性面板 tory

        /* 向周围玩家广播升级的消息，并播放动画 */
        Nbox *box = map_now->getBox();
        if (box == NULL)
        {
            cout << "jolly:box is null hero 1858" << endl;
            return;
        }
        StyObj obj(memHero->identity, HERO_STYLE_TYPE);
        box->getStaInSrcVec(obj);

        memset(g_out_buf, 0, 20480);
        sprintf(g_out_buf, "%d,%d,%d,%s,%d,%d,%d", 3, 7, 1, memHero->identity, memHero->level, memHero->basicHeroData.lifeUpperVal,\
                   memHero->basicHeroData.magicUpperVal);
        box->sentBoxMsg(g_out_buf, memHero->identity);

        /* 人物升级,宠物栏大小改变,发送信息 jolly start */
        int petMaxNumber = pet_box->getMaxNumber();
        memset(g_out_buf, 0, 20480);
        snprintf(g_out_buf, sizeof(g_out_buf), "%d,%d,%d", 10, PET_BOX_NUMBER, petMaxNumber);
        send_msg(_fd, g_out_buf);
		
		if (isBeginCycleTask)
		{
			freshHeroCycleTask(this);
			updateCycleTaskLevel();
			viewCycleTaskInfo();
		}
		
        /* 人物升级,宠物栏大小改变,发送信息 jolly end */
		memSet();
		send_msg_att();	
    }
}

/* 更新角色下一级升级所需的经验值 */
void Hero::growExp(void)
{
	memHero->expForGrow = p_conf->upgradeNeedExp[memHero->level - 1];

	judgeExercise();

}


/*玩家升级改变玩家自身属性的方法实现*/
void Hero::herogrowup(void)
{
#if 0
    int index = 0;
    if(*(memHero->basicHeroData.party) == 'H')	index = 0;
    if(*(memHero->basicHeroData.party) == 'M')	index = 1;
    if(*(memHero->basicHeroData.party) == 'G')	index = 2;
    if(*(memHero->basicHeroData.party) == 'X')	index = 3;

    Hero_Conf_T h_c = ss[index];
    setLifeUpperVal(memHero->basicHeroData.lifeUpperVal+h_c.addLife[memHero->level]);           //生命上限
    setLifeVal(memHero->basicHeroData.lifeUpperVal+h_c.addLife[memHero->level]);                 //生命
    setMagicUpperVal(memHero->basicHeroData.magicUpperVal+h_c.addMagic[memHero->level])         //真气上限
    setMagicVal(memHero->basicHeroData.magicUpperVal+h_c.addMagic[memHero->level])          //真气
    setHited(memHero->basicHeroData.hited+h_c.addHited[memHero->level]);
    setCrit(memHero->basicHeroData.crit+h_c.addCrit[memHero->level]);
    setDodge( memHero->basicHeroData.dodge+h_c.addDodge[memHero->level]);
    setTenacity(memHero->basicHeroData.tenacity+h_c.addTenacity[memHero->level]);
    setOutAttack(memHero->basicHeroData.outattack+h_c.addOutAttack[memHero->level]);    //外功攻击
    setInAttack(memHero->basicHeroData.inattack+h_c.addInAttack[memHero->level]);
    setOutDefense(memHero->basicHeroData.outdefense+h_c.addOutDef[memHero->level]);
    setInDefense(memHero->basicHeroData.indefense+h_c.addInDef[memHero->level]);
    setOuthurt(memHero->basicHeroData.outhurt+h_c.addOutHurt[memHero->level]);
    setInhurt(memHero->basicHeroData.inhurt+h_c[memHero->level]);
#endif

	int index = memHero->level - 1;
	if (index < 0 || index > MAX_HERO_LEVEL - 1)
	{
		return;
	}
	
	cout<<"memHero lastLevel lifeUpperVal is "<<memHero->basicHeroData.lifeUpperVal<<endl;
	memHero->basicHeroData.lifeUpperVal += p_conf->addLife[index] ;			//生命上限
	cout<<"memHero thisLevel lifeUpperVal is "<<memHero->basicHeroData.lifeUpperVal<<endl;
	memHero->basicHeroData.lifeVal = memHero->basicHeroData.lifeUpperVal;	//生命
	memHero->basicHeroData.magicUpperVal += p_conf->addMagic[index] ;                        //真气上限
	memHero->basicHeroData.magicVal = memHero->basicHeroData.magicUpperVal ;     //真气
	memHero->basicHeroData.hited += p_conf->addHited[index] ;                              //命中
	memHero->basicHeroData.crit += p_conf->addCrit[index] ;                                          //暴击
	memHero->basicHeroData.dodge += p_conf->addDodge[index] ;                               //闪避
	memHero->basicHeroData.tenacity += p_conf->addTenacity[index] ;    
	memHero->basicHeroData.outattack += p_conf->addOutAttack[index];
	memHero->basicHeroData.inattack += p_conf->addInAttack[index];
	memHero->basicHeroData.outdefense += p_conf->addOutDef[index];
	memHero->basicHeroData.indefense += p_conf->addInDef[index];
	memHero->basicHeroData.outhurt += p_conf->addOutHurt[index];
	memHero->basicHeroData.inhurt += p_conf->addInHurt[index];
}

int Hero::getExpForGrow(void)
{
    return memHero->expForGrow;
}                  

int Hero::getGradeNow(void)
{
    return memHero->level;
}                   
//void	Hero::setGradeNow(int level)		//设置角色当前等级 
void Hero::setGradeNow(int _level)      // modified by bison
{
	if (_level < 1 || _level > 80)
	{
		return;
	}
    memHero->level = _level;
#if 0
    /* XXX:added by bison for test */
    /* XXX:测试使用，
     * 能给英雄一个任意等级，并使英雄的属性同步变化
     */ 
    // memHero->expAgo = 100 + 10 * (memHero->level * (memHero->level + 1) * (2 * memHero->level + 1) / 6 - 1); //上一次升级所需经验
    // growExp();  //更新expForGrow的值
    // memHero->expNow = 0; //当前经验值设为0 tory_01_16
    // memHero->basicHeroData.lifeUpperVal = HP_ratio*(1000*memHero->level+1000)/100;
    // memHero->basicHeroData.lifeVal = memHero->basicHeroData.lifeUpperVal;
    // memHero->basicHeroData.magicUpperVal=MP_ratio*(100*memHero->level+100)/100+MP_value;
    // memHero->basicHeroData.magicVal=memHero->basicHeroData.magicUpperVal;
    // memHero->basicHeroData.sec_hurt=DAM_ratio*(100*memHero->level+100)/100;
    // memHero->basicHeroData.AttackAndDefense=200*memHero->level;
    // memHero->basicHeroData.outhurt=memHero->basicHeroData.outratio*memHero->basicHeroData.sec_hurt;
    // memHero->basicHeroData.inhurt=memHero->basicHeroData.inratio*memHero->basicHeroData.sec_hurt;
    // memHero->basicHeroData.outattack=memHero->basicHeroData.attackratio *
	// memHero->basicHeroData.AttackAndDefense*memHero->basicHeroData.outratio;
    // memHero->basicHeroData.inattack=memHero->basicHeroData.attackratio *
	// memHero->basicHeroData.AttackAndDefense*memHero->basicHeroData.inratio;
    // memHero->basicHeroData.outdefense=memHero->basicHeroData.defenseratio *
	// memHero->basicHeroData.AttackAndDefense* memHero->basicHeroData.outratio;
    // memHero->basicHeroData.indefense=memHero->basicHeroData.defenseratio *
	// memHero->basicHeroData.AttackAndDefense*memHero->basicHeroData.inratio;
#endif

	int index = memHero->level - 1;
	if (index < 0 || index > MAX_HERO_LEVEL - 1)
	{
		return;
	}
	
	memHero->basicHeroData.lifeUpperVal += p_conf->addLife[index] ;			//生命上限
	memHero->basicHeroData.lifeVal = memHero->basicHeroData.lifeUpperVal;	//生命
	memHero->basicHeroData.magicUpperVal += p_conf->addMagic[index] ;                        //真气上限
	memHero->basicHeroData.magicVal = memHero->basicHeroData.magicUpperVal ;     //真气
	memHero->basicHeroData.hited += p_conf->addHited[index] ;                              //命中
	memHero->basicHeroData.crit += p_conf->addCrit[index] ;                                          //暴击
	memHero->basicHeroData.dodge += p_conf->addDodge[index] ;                               //闪避
	memHero->basicHeroData.tenacity += p_conf->addTenacity[index] ;    
	memHero->basicHeroData.outattack += p_conf->addOutAttack[index];
	memHero->basicHeroData.inattack += p_conf->addInAttack[index];
	memHero->basicHeroData.outdefense += p_conf->addOutDef[index];
	memHero->basicHeroData.indefense += p_conf->addInDef[index];
	memHero->basicHeroData.outhurt += p_conf->addOutHurt[index];
	memHero->basicHeroData.inhurt += p_conf->addInHurt[index];
}

Map_Inform* Hero::getMap(void)
{

    return map_now;
}
void Hero::setMap(Map_Inform *_map_now)
{
	StyObj obj(memHero->identity,HERO_STYLE_TYPE);
	map_now->deleteID(obj);
    map_now = _map_now;
//	map_now->insertID(obj);
    changeMapId(map_now->getMapId());
}
void Hero::changeMapId(char *_mapId)
{
	int ret = -1;
	if (_mapId != NULL)
	{
		ret = happyCheck(memHero->basicHeroData.mapId, _mapId);
	}
    int len=strlen(_mapId);
    strncpy(memHero->basicHeroData.mapId, _mapId, len + 1);
	if (ret == 1)
	{
		startHappyTimer();
	}
	else if (ret == 2)
	{
		endHappyTimer();
	}
}

/* add  2012.4.16 start  jolly modify 2012,11,1*/ 
Equipment* Hero::getWearEquip(int _index)   //角色身上装备属性，键：为身体部位名称，值：为装备Id
{
	if (_index<0||_index>13)
	{
		return NULL;
	}
	
	if (memHero->wearequipdata[_index].flag!=1)
	{
		return NULL;
	}
	
	map<string,Equipment*>::iterator it;
	it=heroAllEquip.find(memHero->wearequipdata[_index].goodsid);
	if (it==heroAllEquip.end())
	{
		cout<<"jolly:According to the Equipment id can't find the equip entity hero 2640"<<endl;
		return NULL;
	}
	else
	{
		return it->second;
	}
}
void Hero::setWearEquip(int _index,Equipment* _equipment)
{
	if (_equipment==NULL)
	{	
		// cout<<"***********************2160********************"<<endl;
		strncpy(memHero->wearequipdata[_index].goodsid,"0",sizeof(memHero->wearequipdata[_index].goodsid));
		strncpy(memHero->wearequipdata[_index].typeId,"0",sizeof(memHero->wearequipdata[_index].typeId));
		memHero->wearequipdata[_index].flag=0;	
	}
	else
	{
		// cout<<"***********************2167********************"<<endl;
		strncpy(memHero->wearequipdata[_index].goodsid,_equipment->getentityid(),sizeof(memHero->wearequipdata[_index].goodsid));
		strncpy(memHero->wearequipdata[_index].typeId,_equipment->getid(),sizeof(memHero->wearequipdata[_index].typeId));
		memHero->wearequipdata[_index].flag=1;	
	}   
}

Equipment* Hero::getEquip(string _identity)
{
	map<string,Equipment*>::iterator it;
	it=heroAllEquip.find(_identity);
	if (it==heroAllEquip.end())
	{
		cout<<"jolly:According to the Equipment id can't find the equip entity hero 2167"<<endl;
		return NULL;
	}
	else
	{
		return it->second;
	}
}

/*掉落装备*/
bool Hero::dropEquipInst(string _identity)
{
	map<string,Equipment*>::iterator it;
	it=heroAllEquip.find(_identity);
	if (it==heroAllEquip.end())
	{
		cout<<"can not find the equip error"<<_identity<<endl;
		return false;
	}
	else
	{
		heroAllEquip.erase(it);
	}
}


bool Hero::deleteEquip(string _identity)		//删除装备实例
{
	map<string,Equipment*>::iterator it;
	it=heroAllEquip.find(_identity);	
	if (it==heroAllEquip.end())
	{
		return false;
	}
	else
	{		
		Equipment *equipment=it->second;
		if (equipment!=NULL)
		{		
			/*记录摧毁装备的流水账 jolly 12.10 start*/
			char account_msg[2048]={'\0'};
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%s",7,1,server_name,(int)myTime.tv_sec,getNickName(),getIdentity(),\
			equipment->getentityid(),equipment->getname());
			write_log(account_msg);	
			/*记录摧毁装备的流水账 jolly 12.10 end*/
			heroAllEquip.erase(it);
			delete equipment;
			equipment=NULL;
			mem_group->delete_data(_identity,where);
			return true;
		}
		else
		{
			return false;
		}
	}
}


char* Hero::identity_to_goodsid(char* _identity)
{
	map<string,Equipment*>::iterator it;
	it=heroAllEquip.find(_identity);
	if (it==heroAllEquip.end())
	{
		cout<<"identity is error-------------------hero.cpp 2212"<<endl;
	}
	else
	{
		return it->second->getid();
	}
}

void Hero::insertEquip(Equipment *equipment)
{
	heroAllEquip.insert(map<string,Equipment*>::value_type (equipment->getentityid(),equipment));
}

/*evan add  2012.4.16 end*/


/*evan add  2012.4.18 start*/
void Hero::setAttack_Request(int _attack_request)   //攻击请求是否接受
{
    attack_request = _attack_request;
}
int Hero::getAttack_Request(void)
{
    return attack_request;
}
//玩家已接受的任务列表
list<Task*>  Hero::getAccepted_Task_List(void)
{
    return accepted_task_list;
}

/**
 * incAcceptedTaskList -- 向已接任务列表增加单条已接任务
 * @_task: 加入的任务指针
 * @return: 0:增加成功；1:任务已经在已接列表中
 */
int Hero::incAcceptedTaskList(Task* _task)
{
    list<Task*>::iterator iter;
    char* taskId = _task->getTaskId();

	for (iter = accepted_task_list.begin(); iter != accepted_task_list.end(); iter++)
	{
		if (!strcmp(taskId, (*iter)->getTaskId()))
		{
			return 1;
		}
	}
	cout<<"taskStatetaskState taskStatetaskState "<<memHero->taskState<<endl;
	accepted_task_list.push_back(_task);
	cout<<"[bison] increase one task ok"<<endl;
	return 0;
}


//放弃NPCboss任务
void Hero::abandTaskBySubType(int subType, bool offlineFlag)
{
	list<Task*>::iterator iter;
	set<char*> abandTaskId;
	for (iter = accepted_task_list.begin(); iter != accepted_task_list.end(); iter++)
	{
		Task* task = (*iter);
		if (task == NULL)
		{
			cout<<"fuck your fa"<<endl;
			continue;
		}
		int taskSubType = task->getSubType();
		if (subType == taskSubType)
		{
			abandTaskId.insert((*iter)->getTaskId());
		}
	}
	
	set<char*>::iterator it_taskId;
	for (it_taskId = abandTaskId.begin(); it_taskId != abandTaskId.end(); it_taskId++)
	{
		dealAbandTask(this, (*it_taskId), offlineFlag);
	}
}

//
void Hero::setTaskNeedKillNpcBossId(char *bossId)
{
	if (bossId == NULL)
	{
		memset(taskNeedKillNpcBossId, 0, sizeof taskNeedKillNpcBossId);
	} else {
		strncpy(taskNeedKillNpcBossId, bossId, sizeof taskNeedKillNpcBossId);
	}
}

//
char* Hero::getTaskNeedKillNpcBossId()
{
	return taskNeedKillNpcBossId;
}
	
/**
 * delAcceptedTaskList -- 删除已接任务列表中的单条记录
 * @_taskId: 要删除的单条任务对应的id
 * @return: 成功：返回删除任务的指针；失败：返回NULL
 */
Task* Hero::delAcceptedTaskList(char* _taskId)
{
    list<Task*>::iterator iter;
    Task *task;
	for (iter = accepted_task_list.begin(); iter != accepted_task_list.end(); iter++)
	{	
		task = (*iter);
		if (!strcmp(_taskId, task->getTaskId()))
		{
			accepted_task_list.erase(iter);
			for (int j = 0; j < 10; j++)
			{
				//从memcache存的玩家已接任务数据中删除该条记录
				if (!strcmp(_taskId, memHero->taskSaveData.acced[j].taskId))
				{
					memHero->taskState &= ~(memHero->taskSaveData.acced[j].taskFlag);
					memHero->taskSaveData.acced[j].taskFlag = -1;
				//	memSet();
					// break;
				}
			}
			return task;
		}
	}
	
	return NULL;
}

/**
 * findAcceptedTaskList -- 查找已接任务列表中是否存在指定任务
 * @_taskId: 要查找的任务对应的id
 * @return: 成功：返回查找到的任务的指针；失败：返回NULL
 */
Task* Hero::findAcceptedTaskList(char* _taskId)
{
    list<Task*>::iterator iter;
    Task *task;

	for (iter = accepted_task_list.begin(); iter != accepted_task_list.end(); iter++)
	{
		if (!strcmp(_taskId, (*iter)->getTaskId()))
		{
			return (*iter);
		}
	}
	
	return NULL;
	
}

/*********************************************************
 * setFinishTaskMap -- 对完成任务位图进行操作
 * @taskId: 所要设置为完成状态的任务id
 *********************************************************/
void Hero::setFinishTaskMap(char* taskId)
{
	if (dayLmtFindGroup.isOneItemFull(taskId) == 0)
	{
		set<string> aginTaskSet;
		aginTaskSet.insert(taskId);
		char canAcc[1200] = {0};
		checkAcceptAndSendMsg(this, aginTaskSet, canAcc);
		return;
	}
    //求该任务对应的位图下标
	char num[10];
	sub_str(num, taskId, 4, 0);
    int index = atoi(num);
    //置任务状态为已经完成
	if(index > MAX_TASK_MAP_SIZE * 32)
    {
        //现在最多能记录个任务，如果需要记录更多，再改位图数组大小
        return;
    }

    bit_ops(index - 1, finishTaskMap, SET_BIT);
	
    memcpy(memHero->taskSaveData.finMap, finishTaskMap, sizeof(finishTaskMap));

	// memSet();
}


//清除单条任务的已完成状态
void Hero::clrOneFinishTaskMap(char* taskId)
{
	//求该任务对应的位图下标
    char num[10];
	sub_str(num, taskId, 4, 0);
    int index = atoi(num);
    //置任务状态为已经完成
	if(index > MAX_TASK_MAP_SIZE * 32)
    {
        //现在最多能记录个任务，如果需要记录更多，再改位图数组大小
        return;
    }
    bit_ops(index - 1, finishTaskMap, CLEAR_BIT);
    memcpy(memHero->taskSaveData.finMap, finishTaskMap, sizeof(finishTaskMap));
//    memSet();
}

//每天第一次登陆清空日更新任务的已完成位图
void Hero::clrDayTaskFinishMap(void)
{
	//finishTaskMap[8] ^= 0xffffff00;		//为1的位清掉，为0的位保留
	//finishTaskMap[9] ^= 0xffffffff;
}

/*********************************************************
 * isTaskFinish - 查看任务是否完成
 * @taskId: 所要查看到任务ID
 * Return: true:任务已经完成；false:任务未完成
 *********************************************************/
bool Hero::isTaskFinish(char* taskId)
{
    //求该任务对应的位图下标
    char num[10];
	sub_str(num, taskId, 4, 0);
    int index = atoi(num);
    if(index > MAX_TASK_MAP_SIZE * 32)
    {
        //现在最多能记录个任务，如果需要记录更多，再改位图数组大小
        return false;
    }

    if(test_bit(index - 1, finishTaskMap) == 1)
    {
        return true;
    } else
    {
        return false;
    }
}

void Hero::setMaxAcceptedSize(int _size)
{
    max_accepted_size = _size;
}

int Hero::getMaxAcceptedSize(void)
{
    return max_accepted_size;
}       

// HeroHelp* Hero::getherohelp(void)                       //evan  2012.6.1
// {
    // return herohelp;
// }
// void      Hero::setherohelp(HeroHelp* _herohelp)
// {
    // herohelp = _herohelp;
// }   

/*修改副本房间信息*/
void  Hero::setFbRom(const char *newFbRom)      //add chenzhen 6.12
{
	memset(fbRom,'\0',SHOR_MID_VALUE_LENGTH + 1);
	if(newFbRom != NULL)
	{
		strncpy(fbRom,newFbRom,strlen(newFbRom));
	}
}

/*获得副本房间信息*/ 
char* Hero::getFbRom(void)                 //add chenzhen 6.12
{
    return fbRom;
}

void Hero::setMainSrc(char *_mainSrc)                  //设置进入副本之前的地图id
{

    mainSrcId= _mainSrc;
}

char* Hero::getMainSrc(void)               //获得进入副本之前的地图id
{
    return const_cast<char *>(mainSrcId.c_str());
}

/*
* author: tory
* date: 2012.8.16
* describe:角色进入塔防副本时，吸引的怪物ID（排重）
*/
void Hero::addAttracMonId(string attracMonId)
{
    list<string>::iterator iter = attracMonStore.begin();
    for (iter; iter != attracMonStore.end(); iter++)
    {
        if (attracMonId == (*iter))
        {
            //cout<<attracMonId<<"have add to attracMonstroe"<<endl;
            return;
        }
    }
    attracMonStore.push_back(attracMonId);

}

/*
* author: tory
* date: 2012.8.16
* describe:角色在塔防副本时，删除吸引的怪物ID
*/
void Hero::delAttracMonId(string delMonId)
{
    list<string>::iterator iter = attracMonStore.begin();
    for (iter; iter != attracMonStore.end(); iter++)
    {
        if (delMonId == (*iter)) break;
    }
    attracMonStore.erase(iter);
}

int  Hero::getAttracMonNum(void)
{
    return attracMonStore.size();
}

bool Hero::quit_scene()            
{           
	Wagon *wagon;
    Nbox *box;	
	Pet *myPet;
	
	StyObj obj(memHero->identity,HERO_STYLE_TYPE);
	
	box = map_now->getBox();                     
   	 
	if(box == NULL)
	{
		return false;
	}
	
	box->getStaInSrcVec(obj);
	
	box->heroEnter(this,2);
	
	/*获得当前下线角色所在点周围的id集合后，将自己的Id从地图信息中删除*/
	map_now->deleteID(obj);         
    
	map_now->delFd(getFd());  

	//马车退出
	wagon = getInstWgon(memHero->wagonId);
	if(wagon != NULL)
	{
		wagon->quit_scene();		
	}
	if (pet_box != NULL)
	{
		myPet = pet_box->getActivePet();
		
		if(myPet != NULL)
		{
			myPet->quit_scene(this);
		}
	}
	return true;
} 

/*
* author:	tory
* date:	2012.8.27
* Describe: 将heroID insert进当前Hero下保存的Map_Inform* map_now中，在数据上进入该地图，然后对map_now中的玩家发进入场景的消息
* Require :调用此函数发进入场景消息时，需要先对Hero下的Map_Inform* map_now赋值
*/
bool    Hero::enter_scene()
{

	// cout<<"enter the scence:"<<endl;
	// cout<<"memHero->basicHeroData.pt._x"<<memHero->basicHeroData.pt._x<<endl;
	// cout<<"memHero->basicHeroData.pt._y"<<memHero->basicHeroData.pt._y<<endl;

	Nbox *box;
	Wagon *wagon;
	Pet *myPet;
	
	wagon = getInstWgon(memHero->wagonId);
	
	StyObj obj(memHero->identity,HERO_STYLE_TYPE);
	
    map_now->insertID(obj);  
	
    map_now->inPutFd(getFd());                  
	
    box = map_now->getBox();
	
	
	if(box == NULL)
	{
		return false;
	}
		
	box->getStaInSrcVec(obj);	
	
	box->heroEnter(this,1);	
	

	if(wagon != NULL)
	{
		wagon->enter_scene();
	}
	
	if (pet_box != NULL)
	{
		cout<<"go here:"<<endl;
		myPet = pet_box->getActivePet();
	
		// cout<<"basicHeroData.pt._x:"<<memHero->basicHeroData.pt._x<<endl;
		// cout<<"basicHeroData.pt._y:"<<memHero->basicHeroData.pt._y<<endl;
		if(myPet != NULL)
		{
			cout<<"go first here:"<<endl;
			myPet->enter_scene(this);
		}
	}
	// canWalking = true;
		
	return true;
}

bool Hero::ent_fb_scene()
{
	StyObj obj(memHero->identity,HERO_STYLE_TYPE);	
    map_now->insertID(obj);
    map_now->inPutFd(getFd());                 
	string msg_broadcast = CreateMessage::come_into_view(this);
	//将自己的上线数据发送给地图上的其他角色
	SendMsgClass::sendMapMsg(map_now, const_cast<char *>(msg_broadcast.c_str()), _fd);
	//将整张地图的角色信息发送给指定的fd
	SendMsgClass::sendMapMsg(map_now, _fd);
	return true;
}

//外部获得人物五行属性的接口
FiveElem *Hero::getFiveElem(void)
{
    return fiveElement;
}

bool Hero::getStillFlg(void)                             //获得定身标记值
{
    return stillFlg;
}
void Hero::setStillFlg(bool _flg)                       //设置定身标记值
{
    stillFlg = _flg;
}

Meridian* Hero::getMerid()
{
	if (merid != NULL)
	{
		//cout<<"BisonTest merid is not null "<<merid->getTimerBusy()<<endl;
	}
    return merid;
}

bool Hero::insertAttList(string id)                     //将怪物id插入fightlist
{
	if (!fightlist.empty())	
	{
		list<string>::iterator it;
		for (it=fightlist.begin();it!=fightlist.end();it++)
		{
			if (id==*it)
			{
				return false;
			}
		}
	}	
	else
	{
		// cout<<"*******************"<<endl;
		// cout<<"insert monster "<<id<<endl;
		
		// cout<<"*******************"<<endl;
		fightlist.push_back(id);
		//cout<<fightlist.size()<<endl;
		if (fightlist.size()==1)
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",2,ENTER_QUIT_FIGHT,SUCCESS);
			send_msg(_fd,g_out_buf);
		}
		return true;
	}
}

bool Hero::deleteAttList(string id)                     //将怪物id从fightlist删除
{
	if (fightlist.empty())
	{
		return false;
	}
	else
	{				
		// cout<<"!!!!!!!!!!!!!!!!!!!"<<endl;
		// cout<<"delete monster "<<id<<endl;
		// cout<<"!!!!!!!!!!!!!!!!!!!"<<endl; 
		fightlist.remove(id);
		//cout<<fightlist.size()<<endl;
		if (fightlist.size()==0)
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",2,ENTER_QUIT_FIGHT,FAILED);
			send_msg(_fd,g_out_buf);
		}
		return true;
	}
}
string Hero::getMonsterId(void)                         //从fightlist中取得第一个
{
    list<string>::iterator it;
    it=fightlist.begin();
    if(it==fightlist.end())
    {
        return "0";
    } else
    {
        return *it;
    }
}

//设置玩家帮派信息
void Hero::setGuildInfo(Guild* _guild, int title)
{
	int currTitle = memHero->heroGuildData.guildTitle;
	
	if (currTitle == 0)
	{
		/*我是老大*/
		cutTitle("T032");
	}
	else if (currTitle == 1)
	{
		/*帮内一把手*/
		cutTitle("T033");
	}
	else if (currTitle == 5)
	{
		/*帮派新星*/
		cutTitle("T034");
	}
	
	if (title == 0)
	{
		//设置我是老大头衔
		addTitle("T032");
	} else if (title == 1) {
		//设置帮派一把手头衔
		addTitle("T033");
	} else if (title == 5) {
		//设置帮派新星头衔
		addTitle("T034");
	}
	
    strncpy(memHero->heroGuildData.guildId, _guild->getId(), sizeof(memHero->heroGuildData.guildId));
	strncpy(guildName, _guild->getName(), sizeof(guildName));
    memHero->heroGuildData.guildTitle = title;
    guild = _guild;
	//玩家有帮派，置玩家可接的帮派任务
	
	//cout<<"BisonTest: you have begin accept guildTask guildTaskList size is "<<guildTaskList.size()<<endl;
	//checkAcceptAndSendMsg(this, guildTaskList);
	
	//jolly add wulintarget 12.4 start
	if (guild->getLevel()==2)
	{
		updataSingleTarget(3,6);
	}
	else if (guild->getLevel()==3)
	{
		updataSingleTarget(4,6);
	}
	else if (guild->getLevel()==4)
	{
		updataSingleTarget(5,9);
	}
	updataSingleTarget(1,6);
	//jolly add wulintarget 12.4 end
	memSet();
}

//从memcached上来的数据，guildTitle不为-1才做此操作，以防玩家在离线期间被踢出或更改职位
void Hero::updateGuildInfo()
{
	if (guild != NULL && memHero->heroGuildData.guildTitle != -1)
	{
		int newTitle = guild->getHeroTitle(memHero->identity);
		if (newTitle == -1)
		{
			//离线期间被踢出了帮派
			clrGuildInfo();
		} else {
			//没被踢出，只重置下玩家帮派职务,因为帮派技能不会在离线时被操作，在离线被操作的只可能是头衔
			memHero->heroGuildData.guildTitle = newTitle;
			//在帮派里置玩家已上线
			guild->setHeroOnline(memHero->identity, true);
			if (guild->getHeroRefreshTaskNeed(memHero->identity))
			{
				refreshGuildTask();
			}
		
			if (newTitle == 0)
			{
				//设置我是老大头衔
				addTitle("T032");
			} else if (newTitle == 1) {
				//设置帮派一把手头衔
				addTitle("T033");
			} else if (newTitle == 5) {
				//设置帮派新星头衔
				addTitle("T034");
			}
		
			updataSingleTarget(1,6);
		
		}
	}
}

//清除玩家帮派信息
void Hero::clrGuildInfo()
{
	cutTitle("T016");
	cutTitle("T017");
	cutTitle("T018");
	memset(memHero->heroGuildData.guildId, 0, sizeof(memHero->heroGuildData.guildId));
	memset(guildName, 0, sizeof(guildName));
    memHero->heroGuildData.guildTitle = -1;
	memHero->heroGuildData.guildDayRewardTime = 0;
    guild = NULL;
	//清除帮派技能所加的属性记录
	clrGuildSkillAddTotal();
}

//获取玩家所在的帮会名
char* Hero::getGuildName(void)
{
    return guildName;
}

char* Hero::getGuildId()
{
	if(!memHero){
	return NULL;
	}
    return memHero->heroGuildData.guildId;
}

//获取玩家在帮会中的头衔
int Hero::getGuildTitle(void)
{
	if(!memHero){
        return 0;
        }

    return memHero->heroGuildData.guildTitle;
}

//获取所属帮派指针
Guild* Hero::getGuild()
{
    return guild;
}

//设置签到
void Hero::setGuildSigned(bool val)
{
    memHero->heroGuildData.guildSigned = val;
	memSet();
}

bool Hero::getGuildSigned()
{
    return memHero->heroGuildData.guildSigned;
}

void Hero::selSetFun(int index, int val)
{
    (this->*setFun[index])(val);
}

int Hero::selGetFun(int index)
{
    if((index<0) || (index > 9)){
	return 0;
    }
    return(this->*getFun[index])();
}

void Hero::incAttr(int index, int val)
{
    selSetFun(index, selGetFun(index) + val);
}

void Hero::decAttr(int index, int val)
{
    selSetFun(index, selGetFun(index) - val);
}

//设置新等级的帮派技能附加属性，同时更新总附加值
void Hero::setNewGuildSkillAdd(int index, int val)
{
    memHero->heroGuildData.guildSkillAdd[index] = val;
    memHero->heroGuildData.guildSkillAddTotal[index] += val;
    // incAttr(index, val);
	addAttr(index, val);
	memSet();
}

//获取当前帮派等级属性附加值
int Hero::getGuildSkillAdd(int index)
{
    return memHero->heroGuildData.guildSkillAdd[index];
}

void Hero::incGuildDayRewardTime()
{
	memHero->heroGuildData.guildDayRewardTime += 1;
	if (memHero->heroGuildData.guildDayRewardTime >= 10)
	{
		addTitle("T035");
	}
}


//帮派技能所加属性总值
int Hero::getGuildSkillTotalAdd(char* result)
{
	// string ret;
	for (int i = 0; i < 10; i++)
	{
		// ret += intTostring(memHero->heroGuildData.guildSkillAddTotal[i]);
		sprintf(result + strlen(result), ",%d", memHero->heroGuildData.guildSkillAddTotal[i]);
	}
	return 0;
}

//去除玩家帮派技能附加属性
void Hero::clrGuildSkillAddTotal(void)
{
    for(int i = 0; i < 10; i++)
    {
        memHero->heroGuildData.guildSkillAdd[i] = 0;
        if(memHero->heroGuildData.guildSkillAddTotal[i] > 0)
        {
            decAttr(i, memHero->heroGuildData.guildSkillAddTotal[i]);
            memHero->heroGuildData.guildSkillAddTotal[i] = 0;
        }
    }
	memSet();
}

/*add text start*/
map<string,int> Hero::getsuitlist(void)			//玩家身上的套装集合 evan add 2012.8.30
{
	return suitlist;
}
void Hero::setsuitlist(map<string,int> _suitlist)	//玩家身上的套装集合 evan add 2012.8.30
{
	suitlist = _suitlist;
}
	/*add text end*/

Friend* 
Hero::getFriendInfo()
{
	return friendInfo;
}

//设置是否在帮派战房间中
void Hero::setInGuildWarRoom(bool flag, char *roomId)
{
	if (flag == true)
	{
		if (strlen(roomId) != 8)
		{
			return;
		}
		memset(guildWarRoomId, 0, sizeof (guildWarRoomId));
		strncpy(guildWarRoomId, roomId, strlen(roomId));
	} else {
		memset(guildWarRoomId, 0, sizeof (guildWarRoomId));
	}
	inGuildWarRoom  = flag; 
}

//查看是否在帮战房间中
bool Hero::isInGuildWarRoom()
{
	return inGuildWarRoom;
}

//获取帮派战房间ID
char* Hero::getGuildWarRoomId()
{
	return guildWarRoomId;
}						
/*--------------------add---start--------------*/  
bool Hero::getisRedName(void)				//玩家是否红名，false，不红名；true，红名 evan add 2012.8.31
{
	return isRedName;
}
void Hero::setisRedName(bool _isRedName)
{
	isRedName = _isRedName;
}
int  Hero::getCrimeValue(void)				//罪恶值 evan add 2012.8.31
{
	if(memHero->crimeValue < 0)
		memHero->crimeValue=0;
		
	return memHero->crimeValue;
}
/*这个函数很邪恶*/
void Hero::setCrimeValue(int _CrimeValue)
{
	memHero->crimeValue = _CrimeValue;
	//memHero->crimeValue=crimeValue;
}
/*--------------------end---start--------------*/  

Warehouse* Hero::getWarehouse(void)
{
	return warehouse;
}

//返回是否为一天中的第一次登陆
bool Hero::isFirstLogin()
{
	return isFirstLoginInDay;
}

bool Hero::isInFight(void)				//判断角色是否在战斗状态,若在战斗状态则返回true;
{
	cout<<"fightlist size:"<<fightlist.size()<<endl;
	cout<<"fighthero size:"<<fighthero.size()<<endl;	
	if (fightlist.empty()&&fighthero.empty())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Hero::send_msg_attackFailed(void)
{
	string msg="2";
	msg+=intTostring(ATTACK_RETURN_SELF);
	msg+=intTostring(FAILED);
	send_msg(_fd,const_cast<char*>(msg.c_str()));
}

/*奖励系统相关 jolly add 2012.9.6 start */
	
//离线奖励
int Hero::getOffline_time(void)				//总共的离线时间
{
	return memHero->rewarddata.offline_time;
}

int Hero::getOnline_time(void)				//本次上线时间
{
	return online_time;
}

void Hero::setOffline_time(int _offline_time)
{
	memHero->rewarddata.offline_time=_offline_time;
}

void Hero::setOnline_time(int _online_time)
{	
	online_time=_online_time;
}

int Hero::getOffline_exp(void)
{
	return offline_exp;
}

void Hero::setOffline_exp(int _offline_exp)
{
	offline_exp=_offline_exp;
}

void Hero::countOffline_exp(void)
{	
	if (online_time==0)
	{
		offline_exp=0;
	}
	else
	{
		cout<<online_time<<endl;
		cout<<memHero->rewarddata.offline_time<<endl;
		cout<<online_time-memHero->offlineTime<<endl;
		memHero->rewarddata.offline_time=online_time-memHero->offlineTime;
		int offlinehour=memHero->rewarddata.offline_time/3600;
		// cout<<offlinehour<<endl;
		int stage = 0;
		if (offlinehour<4)
		{
			stage=0;
		}
		else if (offlinehour>=4&&offlinehour<8)
		{
			stage=1;
		}
		else if (offlinehour>=8&&offlinehour<12)
		{
			stage=2;
		}
		else if (offlinehour>=12&&offlinehour<24)
		{
			stage=3;
		}
		else
		{
			stage=4;
		}
		map<int,RewardFactor>::iterator it;
		it=factor_reward.find(getLevel());
		if (it==factor_reward.end())
		{
			offline_exp=100;
		}
		else
		{
			int factor=it->second.lixianFactor;
			offline_exp=stage*memHero->level*memHero->level*factor;	
		}		
	}
	
}

//连续签到奖励
int Hero::getLast_day(void)					//持续签到时间
{
	return memHero->rewarddata.last_day;
}

void Hero::setLast_day(int _last_day)
{
	memHero->rewarddata.last_day=_last_day;
}

int Hero::getLast_exp(void)
{
	return last_exp;
}

void Hero::setLast_exp(int _last_exp)
{
	last_exp=_last_exp;
}	

int Hero::getLast_day_flag(void)
{
	return memHero->rewarddata.last_day_flag;
}

void Hero::setLast_day_flag(int _last_day_flag)
{
	memHero->rewarddata.last_day_flag=_last_day_flag;
}

//初始化罪恶时间
void Hero::initCrimeTime(void)
{
	if(memHero->crimeValue)
	{
		crimeTime==myTime.tv_sec;		
	}
	else
	{
		crimeTime=0;
	}
}
//增加罪恶值
void Hero::addCrimeValue(void)
{
	memHero->crimeValue++;
	cout<<"memHero->crimeValue:"<<memHero->crimeValue<<endl;
	// if(memHero->dropProbabty < 100)
	// {
		// memHero->dropProbabty += 1;
	// }
	/*更改头衔*/
	if(memHero->crimeValue > 40)
	{
		return;
	}
	if(memHero->crimeValue < 5)
	{
		if(memHero->crimeValue == 1 || memHero->crimeValue == 2)
		{
			crimeTitle();
		}
		return;
	}
	if(memHero->crimeValue % 5 == 0)
	{
		crimeTitle();
	}
	
}

//减少罪恶值
void Hero::cutCrimeValue(void)
{
	memHero->crimeValue -=1 ;
	
	if(memHero->crimeValue<0)
	{
		memHero->crimeValue=0;
	}
	
	
	/*更改头衔*/
	if(memHero->crimeValue <= 0)
	{
		return;
	}
	if(memHero->crimeValue < 4)
	{
		if(memHero->crimeValue == 1)
		{
			crimeTitle();
		}
		return;
	}
	if(memHero->crimeValue % 5 == 4)
	{
		crimeTitle();
	}
}

//玩家变为红名
void Hero::changeRedName(void)
{
	isRedName = memHero->crimeValue >=2 ? true:false;
}

//参数hit 被杀者 ，杀死某人后调用该函数
void Hero::term(Hero *hit)
{
	char msgRedName[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	StyObj obj(memHero->identity,HERO_STYLE_TYPE);	
	Nbox* box;
	char *mapid;
	if(map_now == NULL || hit == NULL)
	{
		cout<<"map_now is error:"<<memHero->identity<<endl;
		return;	
	}
	mapid  = map_now->getMapId();
	box = map_now->getBox();
	if(box == NULL)
	{
		cout<<"box is error:"<<memHero->identity<<endl;
		return;
	}
	
	if(isInGuildWarRoom())
	{
		return;
	}
	
	cout<<"hitId:"<<hit->getIdentity()<<endl;
	cout<<"is red name:"<<hit->getisRedName()<<endl;
	if(memHero->camp==hit->getCamp() && !hit->getisRedName())
	{ 
		//map_012明显是pk地图，什么狗屁设计呀？
		// if(mapid == NULL || strcmp(mapid,"map_021")==0)
		// {
			// cout<<"map_021 is not a pk map"<<endl;
			// return;
		// }
		if(memHero->camp == -1)
		{
			return;
		}
		else
		{		
			box->getStaInSrcVec(obj);
			addCrimeValue();
			changeRedName();
			// crimeTitle();
			snprintf(msgRedName,sizeof(msgRedName),"%d,%d,%s,%d",19,3,memHero->identity,memHero->crimeValue);
			box->sentBoxMsg(msgRedName);			
		}
	} 
	else if(hit->getisRedName())
	{
		dropEquip(hit);
	}
}

//获取红名头衔
/*罪恶值=1	
误入歧途	
罪恶值=2	名字变红
著名流氓	
罪恶值=10	
心狠手辣	
罪恶值=15	
凶悍暴徒	
罪恶值=20	
造孽君王	
罪恶值=25	
恐怖天使	
罪恶值=30	
嗜血邪神	
罪恶值=35	
黑暗魔神	
罪恶值>=40	
至尊魔君*/
void Hero::crimeTitle(void)
{

	if(memHero->crimeValue>=1&&memHero->crimeValue<5)
	{
		cutTitle("T042");
		addTitle("T041");				
	}
	else if(memHero->crimeValue>=5&&memHero->crimeValue<10)
	{
		cutTitle("T041");
		addTitle("T042");
		cutTitle("T043");
		
	}
	else if(memHero->crimeValue>=10&&memHero->crimeValue<15)
	{
		cutTitle("T042");
		addTitle("T043");			
		cutTitle("T044");			
	}
	else if(memHero->crimeValue>=15&&memHero->crimeValue<20)
	{		
		cutTitle("T043");
		addTitle("T044");	
		cutTitle("T045");
	}
	else if(memHero->crimeValue>=20&&memHero->crimeValue<25)
	{	
		cutTitle("T044");
		addTitle("T045");
		cutTitle("T046");			
	}
	else if(memHero->crimeValue>=25&&memHero->crimeValue<30)
	{
		cutTitle("T045");
		addTitle("T046");
		cutTitle("T047");		
	}
	else if(memHero->crimeValue>=30&&memHero->crimeValue<35)
	{
		cutTitle("T046");
		addTitle("T047");
		cutTitle("T048");	
	}
	else if(memHero->crimeValue>=35&&memHero->crimeValue<40)
	{
		cutTitle("T047");
		addTitle("T048");
		cutTitle("T049");
	}
	else
	{
		cutTitle("T048");
		addTitle("T049");
	} 
}
//将game server中的副本令设置进mem里的copyCause Cookie 2012.9.26
void Hero::initMemCopyCause(void)
{	
	string str;
	for(set<string >::iterator i=copyCauseStore.begin();i!=copyCauseStore.end();++i)
	{
		str+=*i;
	}
	memcpy(memHero->copyCause,str.c_str(),str.size());
	memHero->copyCause[str.size()]='\0';
}
	
//根据mem初始化set copyCauseStore
void Hero::initCopyCauseStore(void)
{
	if(strcmp(memHero->copyCause,"0")==0)
	{
		cout<<"it is a Null CopyCause "<<endl;
		return;
	}
	for(int i=0;i!=strlen(memHero->copyCause);i+=CAUSELEN)
    {
        char r[CAUSELEN+1];
        r[CAUSELEN]='\0';
        strncpy(r,memHero->copyCause+i,CAUSELEN);
		copyCauseStore.insert(r);
    }
}

void Hero::setTitle(string _title)
{
	title=_title;
	sprintf(memHero->title,"%s",title.c_str());
}

string	Hero::getTitle(void)
{
	return title;
}
	
//选择头衔
bool Hero::chooseTitle(string id)
{
	if(id.empty())
		return false;
		
	set<string>::iterator i=titleStore.find(id);
	if(i==titleStore.end())
	{
		return false;
	}
	else
	{
		title=*i;
		sprintf(memHero->title,"%s",title.c_str());
		return true;
	}	
} 

//通过自己逻辑数据同步更新memcached数据
void  Hero::ownTitle()
{
	int len=0;
	memset(memHero->titleStore,0,sizeof(memHero->titleStore));				//缓存数据清空，xhm add；
	if(titleStore.size()==0)
	{
		return;
	}
	else
	{
		for(set<string>::iterator i=titleStore.begin();i!=titleStore.end();++i)
		{
			if(len >= ALLTITLELEN )
			{
				cout<<"[XHM Warning]:the memHero->titleStore will over range!"<<endl;
				break;
			}
			sprintf(memHero->titleStore + len,"%s|",(*i).c_str());	
			len=strlen(memHero->titleStore);		
		}
		
		memHero->titleStore[len-1]='\0';
		cout<<"[XHM MSG],we keep The memHero->titleStore date:"<<memHero->titleStore<<endl;
	}
	
	if(title.empty())
	{
		sprintf(memHero->title,"0");
	}else{
		sprintf(memHero->title,"%s",title.c_str());
	}
}


//增加头衔
bool Hero::addTitle(string id)
{
	if(id.empty())
		return false;
	
	if(allTitle.size() == 0)
		return false;
		
	set<string>::iterator i=allTitle.find(id);
	if(i==allTitle.end())
	{
		cout<<"[XHM Warning]::Add title Error,the id:"<<id<<"not find in the allTitle vector."<<endl;
		return false;
	}else{
		i=titleStore.find(id);
		if(i==titleStore.end())
		{
			char msg[50]={0};
			sprintf(msg,"19,0,%s",id.c_str());
			send_msg(_fd,msg);
	
			titleStore.insert(id);

			int size = strlen(memHero->titleStore);
			if(size!=0)
				id="|"+id;			
			
			if(size+strlen(id.c_str()) >= sizeof(memHero->titleStore))
			{
				cout<<"[XHM Warning] the memHero->titleStore will over the ranger,return it."<<endl;
				return false;
			}

			strcat(memHero->titleStore,id.c_str());
			
			return true;
		}else{
			cout<<"[XHM Warning]:: the title :"<<id<<"have exit"<<endl;
			return false;
		}
	}	
	
} 



/**头衔失效*/
void Hero::cutTitle(string id)
{
	if(id.empty())
		return;
	
	if(titleStore.size() == 0)
		return;
	
	set<string>::iterator i=titleStore.find(id);
	if(i==titleStore.end())
	{
		return;
	}else{
	
		char msg[50]={0};
		sprintf(msg,"19,1,%s",id.c_str());
		send_msg(_fd,msg);
		
		titleStore.erase(i);	
		if(id==title)
		{
			Map_Inform *map_now;
			Nbox* box;
	
			StyObj obj(memHero->identity,HERO_STYLE_TYPE);	
			map_now = getMap(); //updated by benliao 2012.12.11
			if(map_now == NULL)
			{
				return;
			}
	
			box = map_now->getBox();
			if(box == NULL)
			{
				return;
			}
		
			box->getStaInSrcVec(obj);	
			sprintf(msg,"19,5,%s,0",memHero->identity);
			box->sentBoxMsg(msg);		
			title="0";			
		}		
		ownTitle();
	}	
} 

//上线检查头衔
void Hero::checkTitle(void)
{
	for(int i = 0; i< 4;++i)
	{
		if(strcmp(getIdentity(), newCampData.leaderId[i]) == 0)
		{
			if(i < 3)
			{
				cutTitle(CAMP_LEADER_TITLE);
			}
			else
			{
				cutTitle(CAMP_CHIEF_TITLE);
			}
		}
	}
	
	for(int i = 0; i< 4;++i)
	{
		if(strcmp(getIdentity(), newCampData.leaderId[i]) == 0)
		{
			if(i < 3)
			{
				addTitle(CAMP_LEADER_TITLE);
			}
			else
			{
				addTitle(CAMP_CHIEF_TITLE);
			}
		}
	}
}
	
		


/**发送角色拥有头衔数据*/
void Hero::sendMsgTitle(void)
{
	int len = strlen(memHero->titleStore);
	
	if(len <= 0 || len>=ALLTITLELEN)
		return;
	
	char msg[ALLTITLELEN+10]={0};
	sprintf(msg,"19,2,%s",memHero->titleStore);
	
	if(msg[len+5-1] == '|')
	{
		msg[len+5-1]='\0';
	}
	
	if(msg[0]=='|')
	{
		msg[0]='\0';	
	}
	
	send_msg(_fd,msg); 
}


/**根据memecached初始化所有头衔*/
void Hero::initTitle(void)
{
	if(strlen(memHero->titleStore)==0)
		return;
		
	char tilteTemp[sizeof(memHero->titleStore)]={0};
	memcpy(tilteTemp,memHero->titleStore,sizeof(memHero->titleStore)-1);	//拷贝的目的在不影响缓存存储数据；add by xhm;
	
	bool titleFlag=false;													//标记是需要重新存储头衔数据；
	char *pch = strtok (tilteTemp,"|");										//线程不安全；added by xhm;
	char titleId[5]={0};	
	cout<<"[XHM WARNING] in the initTitle,the memHero->titleStore:"<<memHero->titleStore<<endl;
	while (pch != NULL)
	{	
		cout<<"[XHM MSG] the memcache Title:"<<pch<<endl;
		if(strlen(pch) >= 5)												//头衔出错处理；
		{
			titleFlag=true;
			pch = strtok(NULL, "|");	
			cout<<"[XHM WARNING] >= 5 the Title:"<<pch<<"is over Time!"<<endl;			
			continue;
		}
	
		if(!strcmp(pch,FIRST_TITLE))									//检测某些有时间限制的头衔,added by xhm；
		{
			if(!campWarController.isFukatsu(this))						//如果不是武神；
			{
				if(!strcmp(memHero->title,FIRST_TITLE))
					memset(memHero->title,0,sizeof(memHero->title));
				cout<<"[XHM WARNING] the Title:"<<pch<<"is over Time!"<<endl;					
				pch = strtok(NULL, "|");	
				titleFlag=true;
				continue;
			}
		}

		if(!strcmp(pch,SECOND_TITLE))						
		{
			if(!campWarController.isTakefu(this))						//如果不是武圣；
			{
				if(!strcmp(memHero->title,SECOND_TITLE))
					memset(memHero->title,0,sizeof(memHero->title));
				cout<<"[XHM WARNING] the Title:"<<pch<<"is over Time!"<<endl;
				pch = strtok(NULL, "|");	
				titleFlag=true;	
				continue;
			}
		}
		if(!strcmp(pch,THIRD_TITLE))						
		{
			if(!campWarController.isTakeru(this))		  			 	//如果不是武尊；
			{
				if(!strcmp(memHero->title,THIRD_TITLE))
					memset(memHero->title,0,sizeof(memHero->title));
				cout<<"[XHM WARNING] the Title:"<<pch<<"is over Time!"<<endl;
				pch = strtok(NULL, "|");	
				titleFlag=true;	
				continue;
			}
		}
		if(!strcmp(pch,CAMP_LEADER_TITLE))							
		{
			if(!campWarController.isCampLeader(this,memHero->camp))	  		 	//如果不是统领；
			{
				if(!strcmp(memHero->title,CAMP_LEADER_TITLE))
					memset(memHero->title,0,sizeof(memHero->title));			
				cout<<"[XHM WARNING] the Title:"<<pch<<"is over Time!"<<endl;				
				pch = strtok(NULL, "|");	
				titleFlag=true;			
				continue;
			}
		}
		if(!strcmp(pch,CAMP_CHIEF_TITLE))						
		{
			if(!campWarController.isCampChief(this))				  //如果不是盟主
			{
				if(!strcmp(memHero->title,CAMP_CHIEF_TITLE))
					memset(memHero->title,0,sizeof(memHero->title));	
				cout<<"[XHM WARNING] the Title:"<<pch<<"is over Time!"<<endl;					
				pch = strtok(NULL, "|");	
				titleFlag=true;					
				continue;
			}
		}
		
		titleStore.insert(pch);
		pch = strtok (NULL, "|");	
	}
	
	//阵营头衔验证下线后对角色设置头衔不成功，上线重新设置；
	campWarController.initCampTitle(this);
	
	title=memHero->title;
	
	ownTitle();//保存一次；
	
	cout<<" [XHM TEST] the current Title:"<<title<<endl;
	cout<<"[XHM TEST] the titleStore.size():"<<titleStore.size()<<endl;
}


HeroCpyRecord* Hero::getCpyRecord(void)
{
	return cpyRecord;
}

int Hero::getStatus(void)
{
	return status;
}

void Hero::setStatus(int _status)
{
	status=_status;
}


int Hero::getHeroState(void)
{
	return heroState;
}

void Hero::setHeroState(int _heroState)
{
	// cout<<"|||||||||||||||||||||||||||"<<endl;
	// cout<<"heroState changeTo:"<<_heroState<<endl;
	// cout<<"|||||||||||||||||||||||||||"<<endl;
	heroState=_heroState;
}

void Hero::sendMsgByStall(char *msg,int len)
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%s,%s",14,13,memHero->identity,stall.privateStallName);
}

void Hero::judgeSignFlag(void)											//判断本次登录是否拥有领取签到奖励的权限
{	
	if (!isSameDayWithNow(memHero->offlineTime))			//判断上次登陆和本次登陆是否是同一天
	{
		memHero->rewarddata.last_day_flag=1;												//使连续登陆奖励可以领取
		mysteriousbussiness->setRefreshMoney(10);
		int chief_camp=campWarController.getCheifFactionName();			
		if (chief_camp==memHero->camp&&chief_camp!=-1)											//判断自己的阵营和武林盟主是不是相同
		{	
			memHero->rewarddata.chief_flag=1;												//相同则可以领取
		}
		else
		{
			memHero->rewarddata.chief_flag=0;												//不同不能领取
		}		
			
		memHero->rewarddata.last_day_flag=1;
		
		midasTouch->reLoadMidasTouch(memHero->vipDailyData.midasTimes,memHero->vipDailyData.remidasTimes);				//本次登陆和上次登陆为不同的一天,因此,重置地石成金功能
		
		
		for (int i=0;i<3;i++)						//本次登陆和上次登陆为不同的一天,一次,人物使用经验药的次数重置
		{
			memHero->expDrug[i]=0;
		}
		
		online_reward->setNewDay();
		
		memHero->festivalRewardFlag=0;				//本次登陆和上次登陆为不同的一天,领取的圣诞奖励重置
		
		memHero->worldSpeakTimes=10;				//非vip的世界喊话次数
		
		ride->initCost();
		
		setVipRights(memHero->vipDailyData.stage,true);			//每天还原vip数据
	}
	if (memHero->rewarddata.offline_time==-1)							//本次是第一次登陆,则连续签到奖励肯定可以领取
	{
		memHero->rewarddata.last_day_flag=1;
	}
}

int Hero::getChief_flag(void)
{
	return memHero->rewarddata.chief_flag;
}

void Hero::setChief_flag(int _chief_flag)
{
	memHero->rewarddata.chief_flag=_chief_flag;
}

int Hero::getLevelFlag(void)
{
	return memHero->levelFlag;
}

void Hero::setLevelFlag(int _levelFlag)
{
	memHero->levelFlag=_levelFlag;
}

bool Hero::isRechargeRewardReceive(int index)
{
	if (index<0||index>strlen(memHero->recharge_flag))
	{
		cout<<"111111111111111111111111"<<endl;
		return false;
	}
	else
	{
		if (memHero->recharge_flag[index]=='1')
		{
			return true;
		}
		else
		{
			cout<<"22222222222222222222222222222"<<endl;
			return false;
		}
	}
}

void Hero::receiveRechargeChange(int index)
{
	memHero->recharge_flag[index]='2';
}

void Hero::canReceiveRechargeChange(int index)
{
	memHero->recharge_flag[index]='1';
}
	
void Hero::judgeRechargeReward(void)
{
	long accGold=money->getAccMoney();
	if (accGold==0)
	{
		return;
	}
	int index=0;
	map<int,Reward_recharge_config*>::iterator it;;
	for (it=id_to_reward_recharge.begin();it!=id_to_reward_recharge.end();++it)
	{
		if (accGold>=it->second->getType())
		{
			if (memHero->recharge_flag[index]=='0')
			{
				canReceiveRechargeChange(index);
			}
			index++;
		}
		else
		{
			break;
		}
	}
}

void Hero::send_msg_reward(void)
{
	//离线奖励
	cout<<"memHero->rewarddata.offline_time"<<memHero->rewarddata.offline_time<<endl;
	memset(g_out_buf,0,sizeof(g_out_buf));
	
	if (memHero->rewarddata.offline_time==0||memHero->rewarddata.offline_time==-1)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%d,%d,%d",36,3,0,0,0,0,0);
	}
	else
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%d,%s,%d",36,3,memHero->rewarddata.offline_time,offline_exp,0,"0",1);
	}
	cout<<"g_out_buf:"<<g_out_buf<<endl;
	//武林盟主奖励
	int expChief=memHero->level*memHero->level*300+5000;
	cout<<"memHero->level:"<<memHero->level<<endl;
	cout<<"expChief:"<<expChief<<endl;
	int money=memHero->level*1500;
	cout<<"money:"<<money<<endl;
	snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d,%d,%d,%s,%d",0,expChief,money,"0",memHero->rewarddata.chief_flag);
	cout<<"g_out_buf:"<<g_out_buf<<endl;
	//vip奖励
	snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d,%d,%d,%s,%d",memHero->vipDailyData.stage,0,0,memHero->vipDailyData.bagId,memHero->vipDailyData.receiveFlag);
	
	cout<<"g_out_buf:"<<g_out_buf<<endl;
	//每日签到奖励
	
	nowDay=myTime.tv_sec/86400;	
	int lastSign=memHero->downLineDay/86400;
	if (nowDay-lastSign>3)
	{
		memHero->rewarddata.last_day=0;
	}
	else if (nowDay==lastSign)
	{
		allowSign=0;
	}
	else 
	{
		allowSign=nowDay-lastSign;
	}

	if (memHero->rewarddata.last_day==0)
	{
		allowSign=0;
	}
	allowSignGold=10;
	cout<<"nowDay:"<<nowDay<<endl;
	cout<<"memHero->downLineDay:"<<memHero->downLineDay/86400<<endl;
	snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d,%d,%d",memHero->rewarddata.last_day,allowSign,memHero->rewarddata.last_day_flag);
	send_msg(_fd,g_out_buf);
	cout<<"g_out_buf:"<<g_out_buf<<endl;
}

void Hero::send_msg_att(void)
{
	if (getLifeVal()>getLifeUpperVal())
	{
		setLifeVal(getLifeUpperVal());
	}
	if (getMagicVal()>getMagicUpperVal())
	{
		setMagicVal(getMagicUpperVal());
	}
	char att_info[1024]={0};
	snprintf(att_info,1023,"3,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%lu,%u,%d,%d",\
										USER_ATTR_APPLY_RETURN,memHero->exercisedata.physique,memHero->exercisedata.wushu,\
										memHero->exercisedata.will,memHero->exercisedata.shenfa,physiqueMax,\
										wushuMax,willMax,shenfaMax,getLifeVal(),getLifeUpperVal(),\
										getMagicVal(),getMagicUpperVal(),getOutAttack(),getInAttack(),getOutDefense(),\
										getInDefense(),getHited(),getDodge(),getCrit(),getTenacity(),\
										GetPowerValue(memHero),memHero->prestige,memHero->friendLevel,getCrimeValue());
	send_msg(_fd,att_info);
	
	cout<<"att_info:"<<att_info<<endl;
}

void Hero::judgeExercise(void)		//根据等级判断人物训练的各种最大值
{
	if (memHero->level<=10)
	{					
		physiqueMax=50;				//体魄最大值
		wushuMax=50;					//武术最大值
		willMax=50;					//意志最大值
		shenfaMax=50;		
	}
	else if (memHero->level<=20)
	{
		physiqueMax=100;				//体魄最大值
		wushuMax=100;					//武术最大值
		willMax=100;					//意志最大值
		shenfaMax=100;	
	}
	else if (memHero->level<=30)
	{
		physiqueMax=150;				//体魄最大值
		wushuMax=150;					//武术最大值
		willMax=150;					//意志最大值
		shenfaMax=150;	
	}
	else if (memHero->level<=40)
	{
		physiqueMax=200;				//体魄最大值
		wushuMax=200;					//武术最大值
		willMax=200;					//意志最大值
		shenfaMax=200;	
	}
	else if (memHero->level<=50)
	{
		physiqueMax=250;				//体魄最大值
		wushuMax=250;					//武术最大值
		willMax=250;					//意志最大值
		shenfaMax=250;	
	}
	else if (memHero->level<=60)
	{
		physiqueMax=300;				//体魄最大值
		wushuMax=300;					//武术最大值
		willMax=300;					//意志最大值
		shenfaMax=300;	
	}
	else if (memHero->level<=70)
	{
		physiqueMax=350;				//体魄最大值
		wushuMax=350;					//武术最大值
		willMax=350;					//意志最大值
		shenfaMax=350;	
	}
	else if (memHero->level<=80)
	{
		physiqueMax=400;				//体魄最大值
		wushuMax=400;					//武术最大值
		willMax=400;					//意志最大值
		shenfaMax=400;			
	}
}

void Hero::Exercise(void)			//人物训练
{
	int temp[4];
	char msg[20];
	memset(msg,'\0',20);
	if (useBoundGameMoney(this,exerciseNeedMoney))
	{		
		//srand(MY_TV_USEC);
		for (int i=0;i<4;i++)
		{
			exerciseTemp[i]=0;	
			if (i==0)
			{
				temp[i]=memHero->exercisedata.physique;
			}
			else if (i==1)
			{
				temp[i]=memHero->exercisedata.wushu;
			}
			else if (i==2)
			{
				temp[i]=memHero->exercisedata.will;
			}
			else
			{
				temp[i]=memHero->exercisedata.shenfa;
			}
			
			if (temp[i]<=5)
			{
				exerciseTemp[i]=random_number(1,5);
			}
			else if (temp[i]<=50)
			{
				exerciseTemp[i]=random_number(0,10);
				exerciseTemp[i]=exerciseTemp[i]-5;
			}
			else if (temp[i]<=100)
			{					
				exerciseTemp[i]=random_number(0,15);
				exerciseTemp[i]=exerciseTemp[i]-10;
			}
			else if (temp[i]<=150)
			{
				exerciseTemp[i]=random_number(0,20);
				exerciseTemp[i]=exerciseTemp[i]-15;
			}
			else if (temp[i]<=200)
			{					
				exerciseTemp[i]=random_number(0,25);
				exerciseTemp[i]=exerciseTemp[i]-20;
			}
			else if (temp[i]<=250)
			{
				exerciseTemp[i]=random_number(0,30);
				exerciseTemp[i]=exerciseTemp[i]-25;
			}
			else if (temp[i]<=300)
			{					
				exerciseTemp[i]=random_number(0,35);
				exerciseTemp[i]=exerciseTemp[i]-30;
			}
			else if (temp[i]<=350)
			{					
				exerciseTemp[i]=random_number(0,40);
				exerciseTemp[i]=exerciseTemp[i]-35;
			}
			else if (temp[i]<=400)
			{					
				exerciseTemp[i]=random_number(0,45);
				exerciseTemp[i]=exerciseTemp[i]-40;
			}
		}	
		send_msg_exercise();
	}
}

void Hero::moneySaveExercise(void)		//游戏币保存训练结果
{
	savePhysique();
	saveWushu();
	saveWill();
	saveShenfa();
	send_msg_att();	
}

void Hero::onKeySaveExercise(void)		//一键保存结果
{
	int gold=0;
	for (int i=0;i<4;i++)
	{			
		if (exerciseTemp[i]>0)
		{
			gold+=2;
		}
	}
	
	if (gold!=0)
	{
		if (useBoundGold(this,gold))
		{
			if(exerciseTemp[0]>0)
			{
				savePhysique();
			}
			if (exerciseTemp[1]>0)
			{
				saveWushu();
			}
			if (exerciseTemp[2]>0)
			{
				saveWill();
			}
			if (exerciseTemp[3]>0)
			{
				saveShenfa();
			}
		}
		send_msg_att();
	}
}

void Hero::goldSaveExercise(int index)		//元宝保存训练结果
{
	if (useBoundGold(this,2))
	{			
		if (index==0)
		{
			savePhysique();
		}
		else if (index==1)
		{
			saveWushu();
		}
		else if (index==2)
		{
			saveWill();
		}
		else if (index==3)
		{
			saveShenfa();
		}
		send_msg_att();
	}
}

void Hero::savePhysique(void)			//保存体魄
{	
	int temp=memHero->exercisedata.physique+exerciseTemp[0];
	if (temp>physiqueMax)
	{
		exerciseTemp[0]=physiqueMax-memHero->exercisedata.physique;
		memHero->exercisedata.physique=physiqueMax;
	}
	else if (temp<=0)
	{
		exerciseTemp[0]=0-memHero->exercisedata.physique;
		memHero->exercisedata.physique=0;
	}
	else
	{
		memHero->exercisedata.physique+=exerciseTemp[0];
	}	
	if (memHero->exercisedata.physique>=100)
	{
		updataSingleTarget(6,0);
	}
	memHero->basicHeroData.lifeUpperVal += exerciseTemp[0]*29;
	memHero->basicHeroData.tenacity += exerciseTemp[0];
	exerciseTemp[0]=0;
}

void Hero::saveWushu(void)				//保存武术
{
	int temp=memHero->exercisedata.wushu+exerciseTemp[1];
	if (temp>wushuMax)
	{		
		exerciseTemp[1]=wushuMax-memHero->exercisedata.wushu;
		memHero->exercisedata.wushu=wushuMax;
	}
	else if (temp<=0)
	{
		exerciseTemp[1]=0-memHero->exercisedata.wushu;
		memHero->exercisedata.wushu=0;
	}
	else
	{
		memHero->exercisedata.wushu+=exerciseTemp[1];
	}		
	if (memHero->exercisedata.wushu>=100)
	{
		updataSingleTarget(6,1);
	}
	memHero->basicHeroData.outattack += exerciseTemp[1]*7;
	memHero->basicHeroData.inattack += exerciseTemp[1]*7;
	memHero->basicHeroData.hited += exerciseTemp[1];
	exerciseTemp[1]=0;
}

void Hero::saveWill(void)				//保存意志
{
	int temp=memHero->exercisedata.will+exerciseTemp[2];
	if (temp>willMax)
	{
		exerciseTemp[2]=willMax-memHero->exercisedata.will;
		memHero->exercisedata.will=willMax;
	}
	else if (temp<=0)
	{
		exerciseTemp[2]=0-memHero->exercisedata.will;
		memHero->exercisedata.will=0;
	}
	else
	{
		memHero->exercisedata.will+=exerciseTemp[2];
	}	
	if (memHero->exercisedata.will>=100)
	{
		updataSingleTarget(6,2);
	}
	memHero->basicHeroData.magicUpperVal += exerciseTemp[2]*29;
	memHero->basicHeroData.crit += exerciseTemp[2];
	exerciseTemp[2]=0;
}

void Hero::saveShenfa(void)				//保存身法
{
	int temp=memHero->exercisedata.shenfa+exerciseTemp[3];	
	if (temp>shenfaMax)
	{
		exerciseTemp[3]=shenfaMax-memHero->exercisedata.shenfa;
		memHero->exercisedata.shenfa=shenfaMax;
	}
	else if (temp<=0)
	{
		exerciseTemp[3]=0-memHero->exercisedata.shenfa;
		memHero->exercisedata.shenfa=0;
	}
	else
	{
		memHero->exercisedata.shenfa+=exerciseTemp[3];
	}	
	if (memHero->exercisedata.shenfa>=100)
	{
		updataSingleTarget(6,3);
	}
	memHero->basicHeroData.outdefense += exerciseTemp[3]*12;
	memHero->basicHeroData.indefense += exerciseTemp[3]*12;
	memHero->basicHeroData.dodge += exerciseTemp[3];
	exerciseTemp[3]=0;
}

void Hero::send_msg_exercise(void)		//发送锻炼信息
{
	string msg="8";
	msg+=intTostring(USER_EXERCISE);
	msg+=intTostring(exerciseTemp[0]);
	msg+=intTostring(exerciseTemp[1]);
	msg+=intTostring(exerciseTemp[2]);
	msg+=intTostring(exerciseTemp[3]);
	send_msg(_fd,const_cast<char*>(msg.c_str()));
}


int showHeroGrow(MemHero* obj, char *outfile)
{
	FILE *out;
	if((out = fopen(outfile, "w+")) == NULL){
		fprintf(stderr, "fopen file %s error!\n", outfile);
		return -1;
	//	exit(EXIT_FAILURE);
	}
 	fprintf(out, "test HeroData identity:%s\n", obj->identity);
	fprintf(out, "test HeroData nickName:%s\n", obj->nickName);
	fprintf(out, "test HeroData expNow:%d\n", obj->expNow);
	fprintf(out, "test HeroData expForGrow:%d\n", obj->expForGrow);
	fprintf(out, "test HeroData level:%d\n", obj->level);
	fprintf(out, "test HeroData expAgo:%d\n", obj->expAgo);
	fprintf(out, "test HeroData crimeValue:%d\n", obj->crimeValue);
	fprintf(out, "test HeroData friendLevel:%d\n", obj->friendLevel);
	fprintf(out, "test HeroData cum_recharge_awards:%d\n", obj->cum_recharge_awards);
	fprintf(out, "test HeroData prestige:%d\n", obj->prestige);
	fprintf(out, "test HeroData readNameKills:%d\n", obj->readNameKills);
				

	if(fclose(out) != 0){
		fprintf(stderr, "fclose file error!\n");
		return -1;
	//	exit(EXIT_FAILURE);
	} 	

	return 0;

}

/**************************************************************
 * updateHeroTaskState -- 玩家任务状态的更新
 * @needType: 任务需求类型
 * @needId:	任务的需求
 * @monsterLevel: 怪物等级：任务要求打某个等级差范围的怪物时使用
 * Return: 返回更新是否成功
 **************************************************************/
bool Hero::updateHeroTaskStatus(int needType, char* needId, int monsterLevel)
{
	list<Task*>::iterator iter_task;
	Task *task;
	bool retVal = false;
	//打不低于自己5级的怪
	if (needType == 11)
	{
		if (monsterLevel + 5 < memHero->level)
		{
			return retVal;
		}
	}
	
	// //cout<<"&&&&&&&&&&&&&&&&&&&&&bisonTest you Come&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
	// //cout<<"needType is "<<needType<<" needId is "<<needId<<endl;
	for (iter_task = accepted_task_list.begin(); iter_task != accepted_task_list.end(); iter_task++)
	{
		task = (*iter_task);
		char* taskId = task->getTaskId();	
		list<taskStatus_T*> taskStatus = task->getTaskStatus();
		
		list<taskStatus_T*>::iterator iter;
		iter = taskStatus.begin();
		//任务中need的序号，更新任务状态数据到memcached时使用
		int ret = 0;
		for (iter; iter != taskStatus.end(); iter++)
		{
			if (needType == (*iter)->type)
			{
				char* needIdSet = (*iter)->id;
				int pos = 0;
				char oneNeedId[51];
				int len = strlen(needIdSet);
				while (len > 0)
				{
					pos = findChar(needIdSet, ':', len);
					if (pos == -1)
					{
						//防止最后一个没加冒号
						sub_str(oneNeedId, needIdSet, 0, len);
						needIdSet = needIdSet + len;
					} else {
						sub_str(oneNeedId, needIdSet, 0, pos);
						needIdSet = needIdSet + pos + 1;
					}
					len = strlen(needIdSet);
					
					if (!strcmp(oneNeedId, needId))
					{
						// //cout<<"oneNeed is "<<oneNeedId<<" needId is "<<needId<<endl;
						if ((*iter)->value < (*iter)->num)
						{
							(*iter)->value += 1;
							//更新成功
							//更新要存到memcached中的数据
							for(int i = 0; i < 10; i++)
							{
								if (!strcmp(taskId, memHero->taskSaveData.acced[i].taskId))
								{
									cout<<"[] have see you here!"<<endl;
									memHero->taskSaveData.acced[i].status[ret] = (*iter)->value;
								}
							}
							//发送任务状态更新消息
							// //cout<<"&&&&&&&&&&&&&&&&&&&&&bisonTest you you you you you you  you &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
							sendTaskStatusUpdateMsg(taskId, (*iter)->type, (*iter)->id, (*iter)->value);
							retVal = true;
							goto LE;
							//return true;
						}
					}
				}
				
			}
			//need下标加1
			ret++;
		}
LE:		;
	}
	// //cout<<"&&&&&&&&&&&&&&&&&&&&&bisonTest you Come&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
	return retVal;
}


void Hero::saveHeroEquip(int _index,char* identity,char* typeId,int flag)				//玩家穿装备,并保存入结构体
{
	
	if (flag==1)
	{		
		// cout<<"#######################################"<<endl;
		// cout<<"wearEquip index is:"<<_index<<endl;
		// cout<<"identity:"<<identity<<endl;
		// cout<<"typeId:"<<typeId<<endl;
		// cout<<"#######################################"<<endl;
		strncpy(memHero->wearequipdata[_index].goodsid,identity,sizeof(memHero->wearequipdata[_index].goodsid));
		memHero->wearequipdata[_index].flag=1;
		strncpy(memHero->wearequipdata[_index].typeId,typeId,sizeof(memHero->wearequipdata[_index].typeId));	
	}
	else
	{		
		cout<<"***********************4720********************"<<endl;
		memHero->wearequipdata[_index].flag=0;
	}
}

void Hero::msg_wearEquip(char *msg,int len)					//玩家身上的装备信息返回
{
	snprintf(msg,len,"%d,%d",9,WEAR_EQUIP);//WEAR_EQUIP--->19	
	for (int i=0; i<14; i++)
	{
		if (memHero->wearequipdata[i].flag==1)
		{
			string _identity=memHero->wearequipdata[i].goodsid;
			snprintf(msg+strlen(msg),len-strlen(msg),",%d,%s,%s",i,memHero->wearequipdata[i].typeId,memHero->wearequipdata[i].goodsid);
		}
	}
}

bool Hero::destoryWearEquip(int index,string _identity)		//摧毁身上的装备
{
	
	string goodsid=memHero->wearequipdata[index].goodsid;
	if (goodsid==_identity&&memHero->wearequipdata[index].flag==1)
	{
		map<string,Equipment*>::iterator it;
		it=heroAllEquip.find(_identity);
		if (it==heroAllEquip.end())
		{
			cout<<"jolly: No this index Equip hero.cpp 4395"<<endl;
			return false;
		}
		else
		{
			Equipment *equipment=it->second;
			int type=equipment->gettype();
			string id=equipment->getid();
			string equip_identity=equipment->getentityid();
					
			string hero_id=memHero->identity;
			takeOffEquip(hero_id,-2,id,type);
			heroAllEquip.erase(it);
			mem_group->delete_data(equip_identity,where);
			delete equipment;
			equipment=NULL;
			return true;			
		}
	}	
}

/**************************************************************
 * sendTaskStatusUpdateMsg -- 向玩家发送任务状态更新消息
 * @taskId: 任务Id
 * @statusType:	状态类型
 * @statusId: 状态Id
 * @statusVal: 当前状态值
 * Return: 返回更新是否成功
 **************************************************************/
void Hero::sendTaskStatusUpdateMsg(char* taskId, int statusType,
	char* statusId, int statusVal)
{
	// string msg = "5";
	// msg += intTostring(TASK_UPDATE_RETURN);
	// msg += "," + taskId; 
	// msg += intTostring(SUCCESS);
	// msg += intTostring(statusType);
	// msg += "," + statusId;
	// msg += intTostring(statusVal);
	char msg[640] = {0};
	sprintf(msg, "5,%d,%s,1,%d,%s,%d", TASK_UPDATE_RETURN, taskId, statusType, statusId, statusVal);
	send_msg(getFd(), msg);
}

MidasTouch *Hero::getMidasTouch(void)
{
	return midasTouch;
}



/*生成技能消息*/
// string Hero::formSklMsg(void)
// {
	// string sklMsg;
	// map<string,Skill*>::iterator skill_it;
	
	// if(skill_list.empty())
	// {
		// return sklMsg;
	// }
	
	// sklMsg += intTostring(21);
	// sklMsg += intTostring(4);	
	// sklMsg += intTostring(skill_list.size());
	// for(skill_it = skill_list.begin();skill_it != skill_list.end();skill_it++)
	// {
		// sklMsg += skill_it->second->formSklMsg();
	// }
	// sklMsg.erase(sklMsg.begin());
	// return sklMsg;
// }

long Hero::getTaskState()
{
	return memHero->taskState;
}

int Hero::SetInTskStFstTenBit()
{
	int index = ffz(memHero->taskState);
	if (index > 9)
	{
		return -1;
	}
	bit_ops(index, &memHero->taskState, SET_BIT);
	return index;
}

int Hero::SetInTskStScdTenBit()
{
	long temp = memHero->taskState >> 10;
	int index = ffz(temp);
	if (index > 9)
	{
		return -1;
	}
	bit_ops(index + 10, &memHero->taskState, SET_BIT);
	return index;
}

int Hero::setTskStOneBit(int index)
{
	bit_ops(index, &memHero->taskState, SET_BIT);
}

int Hero::setTskStSomeBit(int val)
{
	memHero->taskState |= val;
}

int Hero::clrTskStOneBit(int index)
{
	bit_ops(index, &memHero->taskState, CLEAR_BIT);
}

int Hero::clrTskStSomeBit(int val)
{
	int value = ~val;
	memHero->taskState &= value;
}

// static void petDevelopRecall(struct ev_loop *loop,ev_timer *think,int revents)
// {	
	// ev_timer_stop(loop,think);
	// if(petThk->empty())
	// {
		// return;
	// }	
	// else
	// {
		// Hero *hero=NULL;
		// hero=petThk->outObj();
		// if(hero == NULL)
		// {
			// return;
		// }		
		// else
		// {
			// Pet *pet=hero->pet_box->getActivePet();
			// if (pet==NULL)
			// {
				// return ;
			// }
			// else
			// {					
				// petDevelop(pet,hero);
				// hero->restartPetTimer();
			// }
		// }		
	// }	
// }

Point Hero::getBeforePiexPt(void)
{
	return beforGoCpyPiexPt;
}

void Hero::setBeforePiexPt(Point beforePt)
{
	beforGoCpyPiexPt = beforePt;
}

MysteriousBussiness* Hero::getMysteriousBussiness()
{
	return mysteriousbussiness;
}

void Hero::send_bag_msg(char *msg,int len)
{ 		
	if (msg==NULL)
	{
		return;
	}
	int bagnum=bag->getBagNum();
	if (bagnum<0||bagnum>96)
	{
		bagnum=48;		
		snprintf(msg,len,"%d",bagnum);
		return;
	}
	snprintf(msg,len,"%d",bagnum);
	char msg_temp[15000]={'\0'};
	int num=0;
	int number;
	char identity[40]={'\0'};
	char goodsid[40]={'\0'};
	if (bagnum<40||bagnum>96)
	{
		cout<<"jolly:bagNum is error bag.628"<<endl;
	}
	else
	{
		for (int i=0;i<bagnum;i++)
		{
			number=bag->getGridNum(i);
			if (number!=0)
			{	
				memset(identity,0,sizeof(identity));
				strncpy(identity,bag->getIdentity(i),sizeof(identity)-1);
				memset(goodsid,0,sizeof(goodsid));
				strncpy(goodsid,identity,sizeof(goodsid)-1);
				int type=getGoodsType(identity);
				if (type==1)
				{
					map<string,Equipment*>::iterator it;
					it=heroAllEquip.find(identity);
					if (it==heroAllEquip.end())
					{
						cout<<"jolly :According to the equipment identity can't find the Equipment hero.cpp 4972"<<endl;
					}
					else
					{
						if (it->second==NULL)
						{
							continue;
						}
						if (it->second->gettype()==0||it->second->gettype()==13)
						{
							cout<<"背包数据还原"<<endl;
							if (!it->second->isEffect(this))
							{
								continue;
							}
						}
						strncpy(goodsid,it->second->getid(),sizeof(goodsid)-1);
					}
				}			
				snprintf(msg_temp+strlen(msg_temp),len-strlen(msg_temp),",%d,%d,%d,%s,%s",i,type,number,goodsid,identity);
				num++;
			}
		}
		snprintf(msg+strlen(msg),len-strlen(msg),",%d",num);
		if (num!=0)
		{
			snprintf(msg+strlen(msg),len-strlen(msg),"%s",msg_temp);
		}	
	}	
}

void Hero::msg_warehouse(char *msg)
{
	if (msg==NULL)
	{
		return;
	}
	int gridNum=warehouse->getGridNum();
	char identity[40]={'\0'};
	char goodsid[40]={'\0'};
	char msg_temp[10800]={'\0'};
	int number;
	int num=0;
	sprintf(msg,"%d,%d,%d",15,ONLINE_WAREHOUSE_RETURN,gridNum);
	for (int i=0;i<gridNum;i++)
	{
		number=warehouse->getGridGoodsNum(i);
		if (number!=0)
		{	
			memset(identity,0,sizeof(identity));
			strncpy(identity,warehouse->getGridGoodsid(i),sizeof(identity) -1);
			int type=getGoodsType(identity);
			memset(goodsid,0,sizeof(goodsid));
			strncpy(goodsid,identity,strlen(identity));
			if (type==1)
			{
				map<string,Equipment*>::iterator it;
				it=heroAllEquip.find(identity);
				if (it==heroAllEquip.end())
				{
					cout<<"jolly :According to the equipment identity can't find the Equipment hero.cpp 5026"<<endl;
				}
				else
				{
					if (it->second->gettype()==0||it->second->gettype()==13)
					{
						cout<<"背包数据还原"<<endl;
						// it->second->isEffect(this);
						if (!it->second->isEffect(this))
						{
							continue;
						}
					}
					strncpy(goodsid,it->second->getid(),sizeof(goodsid));
				}
			}
			sprintf(msg_temp,"%s,%d,%d,%d,%s,%s",msg_temp,i,type,number,goodsid,identity);
			num++;
		}
	}
	sprintf(msg,"%s,%d%s",msg,num,msg_temp);
}

/*将仓库中的装备实例保存起来 11.1 jolly*/	
void Hero::saveWarehouseEquip(void)
{
	int gridNun=warehouse->getGridNum();
	int number;
	for (int i=0;i<gridNun;i++)
	{
		number=warehouse->getGridGoodsNum(i);
		if (number!=0)
		{				
			char* goodsid=warehouse->getGridGoodsid(i);
			if (getGoodsType(goodsid)==1)
			{
				int size=0;
				int equipWhere=0;
				EquipmentData *equipmentdata = (EquipmentData*)mem_group->get_data(goodsid, &size, &equipWhere,where);
				if(equipmentdata!=NULL)
				{					
					Equipment *equipment=new Equipment(equipmentdata);
					free(equipmentdata);
					heroAllEquip.insert(map<string,Equipment*>::value_type(goodsid,equipment));
				}
			}
		}
	}
}
/*背包中的装备实例保存 11.1 jolly*/
void Hero::saveBagEquip(void)
{
	int bagnum=bag->getBagNum();
	int type;
	for (int i=0;i<bagnum;i++)
	{
		char* goodsid=bag->getIdentity(i);
		type=getGoodsType(goodsid);
		if (type==1)
		{
			int size=0;
			int equipWhere=0;
			EquipmentData *equipmentdata = (EquipmentData*)mem_group->get_data(goodsid, &size, &equipWhere,where);
			if(equipmentdata!=NULL)
			{					
				Equipment *equipment=new Equipment(equipmentdata);
				free(equipmentdata);
				heroAllEquip.insert(map<string,Equipment*>::value_type(goodsid,equipment));
			}
		}
	}	
}

/*获得跳转地图bool值*/
bool Hero::getWalkingFlg(void)
{
	return canWalking;
}

/*修改bool值*/
bool Hero::setWalkingFlg(bool _judFlg)
{
	canWalking = _judFlg;
}

static void heroVerify(struct ev_loop *loop,ev_timer *think,int revents)
{
	ev_timer_stop(loop,think);

	Hero *hero=(Hero*)think->target;
	
	if (hero==NULL)
	{
		cout<<"jolly:heroVerify timer has no Hero Verify 14"<<endl;
		return;
	}
	
	hero->saveCount++;
		
	int nowTime=myTime.tv_sec;									//当前时间
	int nowlife=hero->getLifeVal();								//当前血量
	int lifeUpper=hero->getLifeUpperVal();						//血量上限
	int nowMagic=hero->getMagicVal();							//当前魔量
	int magicUpper=hero->getMagicUpperVal();					//魔量上限
	int level=hero->getLevel();									//人物等级
	char* identity=hero->getIdentity();							//人物实例id
	
	// cout<<"nowlife:"<<nowlife<<endl;
	// cout<<"lifeUpper:"<<lifeUpper<<endl;
	// cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	if (nowlife>0)			//当前血量小于等于0,表示人物已经死亡,所以,回血回蓝功能暂停
	{
		if (nowlife<lifeUpper)				//当人物当前血量小于总血量的时候,执行以下代码
		{
			if (hero->memHero->bloodBagdata.value>0)			//判断人物是否有血包
			{
				int minute=nowTime-hero->memHero->bloodBagdata.lastTime;
				if (minute<0)
				{
					hero->memHero->bloodBagdata.lastTime=nowTime;
				}
				// cout<<"nowTime:"<<nowTime<<endl;
				// cout<<"hero->memHero->bloodBagdata.lastTime:"<<hero->memHero->bloodBagdata.lastTime<<endl;
				// cout<<"minute:"<<minute<<endl;
				// cout<<"hero->memHero->bloodBagdata.cd:"<<hero->memHero->bloodBagdata.cd<<endl;
				if (minute>=hero->memHero->bloodBagdata.cd)				//判断是否到了血包的使用时间	
				{
					if (hero->memHero->bloodBagRecoverValue<50||hero->memHero->bloodBagdata.value<0)//异常判断,若人物血包回复量的数值小于800和总量小于0,则重置
					{
						hero->memHero->bloodBagRecoverValue=50;
						hero->memHero->bloodBagdata.value=0;
					}
					else
					{
						int bloodMinute=level*(hero->memHero->bloodBagRecoverValue);
						if (bloodMinute>=hero->memHero->bloodBagdata.value)								//判断本次会多少血
						{
							bloodMinute=hero->memHero->bloodBagdata.value;
						}
						nowlife+=bloodMinute;
						if (nowlife>lifeUpper)
						{
							bloodMinute=bloodMinute-nowlife+lifeUpper;
							nowlife=lifeUpper;
						}
						hero->memHero->bloodBagdata.value-=bloodMinute;	
						if (hero->memHero->bloodBagdata.value<0)
						{	
							hero->memHero->bloodBagdata.value=0;
						}
						hero->setLifeVal(nowlife);
					}
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%d,%d",3,BLOODINCREASE,identity,nowlife,lifeUpper,hero->memHero->bloodBagdata.value);
					send_msg(hero->getFd(),g_out_buf);
					hero->memHero->bloodBagdata.lastTime=nowTime;
				}
			}
		}		
		// cout<<"nowMagic:"<<nowMagic<<endl;
		// cout<<"magicUpper:"<<magicUpper<<endl;
		// cout<<"value:"<<hero->memHero->magicBagdata.value<<endl;
		// cout<<"magicBagRecoverValue:"<<hero->memHero->magicBagRecoverValue<<endl;
		if (nowMagic<magicUpper)//当人物当前蓝量小于总蓝量的时候,执行以下代码
		{
			if (hero->memHero->magicBagdata.value>0)			//判断人物是否有魔包
			{
				int minute=nowTime-hero->memHero->magicBagdata.lastTime;
				if (minute<0)
				{
					hero->memHero->magicBagdata.lastTime=nowTime;
				}
				// cout<<"minute:"<<minute<<endl;
				// cout<<"cd:"<<hero->memHero->magicBagdata.cd<<endl;
				if (hero->memHero->magicBagdata.cd>15)
				{
					hero->memHero->magicBagdata.cd=10;
				}
				if (minute>=hero->memHero->magicBagdata.cd)				//判断是否到了魔包的使用时间	
				{
					if (hero->memHero->magicBagRecoverValue<25)//异常判断,若人物蓝包回复量的数值小于600,则重置
					{
						hero->memHero->magicBagRecoverValue=25;
					}
					else 
					{
						int magicMinute=level*(hero->memHero->magicBagRecoverValue);
						// cout<<"magicMinute is :"<<magicMinute<<endl;
						if (magicMinute>=hero->memHero->magicBagdata.value)								//判断本次会多少魔
						{	
							magicMinute=hero->memHero->magicBagdata.value;
						}
						nowMagic+=magicMinute;
						if (nowMagic>magicUpper)
						{
							magicMinute=magicMinute-nowMagic+magicUpper;
							nowMagic=magicUpper;
						}
						hero->memHero->magicBagdata.value-=magicMinute;	
						if (hero->memHero->magicBagdata.value<0)
						{
							hero->memHero->magicBagdata.value=0;
						}
						hero->setMagicVal(nowMagic);
					}					
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%d,%d",3,MAGICINCREASE,identity,nowMagic,magicUpper,hero->memHero->magicBagdata.value);
					send_msg(hero->getFd(),g_out_buf);					
					hero->memHero->magicBagdata.lastTime=nowTime;
				}
			}
			else if (hero->memHero->magicBagdata.value<0)
			{
				hero->memHero->magicBagRecoverValue=25;
				hero->memHero->magicBagdata.value=0;
			}
		}		

		/*人物打坐 每隔20s 自动回血回魔,暂定, 以后改为只有打坐的时候才会自动回血回魔*/
		if (hero->getHeroState()==6)
		{
			if (hero->memHero->autoRecover>nowTime)
			{
				hero->memHero->autoRecover=nowTime;
			}
			
			if (nowTime-hero->memHero->autoRecover>=5)
			{				
				if (nowlife<lifeUpper||nowMagic<magicUpper)   //当人物当前血量小于总血量或者蓝量小于总蓝量的时候,执行以下代码
				{			
					if (nowlife!=lifeUpper||nowMagic!=magicUpper)
					{
						nowlife+=lifeUpper*0.02;				//每次自动回血都会血量上限的2%
						if (nowlife>lifeUpper)
						{
							nowlife=lifeUpper;
						}
						nowMagic+=magicUpper*0.02;
						if (nowMagic>magicUpper)				//每次自动回魔都回魔量上限的2%
						{
							nowMagic=magicUpper;
						}	
						hero->setLifeVal(nowlife);
						hero->setMagicVal(nowMagic);
						snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d,%d,%d,%d",3,AOTUINCREASE,identity,nowlife,lifeUpper,nowMagic,magicUpper);
						send_msg(hero->getFd(),g_out_buf);
					}			
				}	
				int level=hero->getLevel();
				int exp;
				map<int,RewardFactor>::iterator dazuo_it;
				dazuo_it=factor_reward.find(level);
				if (dazuo_it==factor_reward.end())
				{
					exp=100;
				}
				else
				{
					int _factor=dazuo_it->second.dazuoFactor;
					exp=_factor;
				}
				exp=(exp*hero->memHero->vipDailyData.dazuoTimes)/10;
				hero->setExpNow(exp);			
				hero->memHero->autoRecover=nowTime;
			}
		}			
	}			
	
	//半小时罪恶点扣一
	Nbox* box;
	Map_Inform* map_now;
	map_now = hero->getMap();
	if(map_now == NULL)
	{
		cout<<"map_now is error:"<<hero->memHero->identity<<endl;
		return;
	}
	box = map_now->getBox();
	if(box == NULL)
	{
		cout<<"box is error:"<<hero->memHero->identity<<endl;
		return;
	}		
	StyObj obj(hero->memHero->identity,HERO_STYLE_TYPE);		
	
	box->getStaInSrcVec(obj);	
	
	int crimCount=hero->getCrimCount();
	crimCount+=5;
	if (crimCount>=1800)
	{
		char msgRedName[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
		if(hero->memHero->crimeValue > 0)
		{
						
					
			hero->cutCrimeValue();	
			hero->changeRedName();
			snprintf(msgRedName,sizeof(msgRedName),"%d,%d,%s,%d",19,3,hero->memHero->identity,hero->memHero->crimeValue);
			
			box->sentBoxMsg(msgRedName);	
			
			
		}
		// if(hero->memHero->dropProbabty > 0)
		// {
			// hero->memHero->dropProbabty -= 1;
		// }
		crimCount=0;
	}
	hero->setCrimCount(crimCount);
	
	
	//半小时耐力值加5点
	int powerCtn = hero->getPowerCount();
	powerCtn+=5;
	if (powerCtn>=1800)
	{
		char fatigueMsg[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
		StyObj obj(hero->memHero->identity,HERO_STYLE_TYPE);	
		Map_Inform* map_now;
		if(hero->memHero->lastStrength < hero->memHero->fatigueUpperVal)
		{	
			hero->memHero->lastStrength += 5;
			if(hero->memHero->lastStrength > hero->memHero->fatigueUpperVal)
			{
				hero->memHero->lastStrength = hero->memHero->fatigueUpperVal;
			}
			
			snprintf(fatigueMsg,sizeof(fatigueMsg),"8,12,%s,%d,%d",hero->memHero->identity,hero->memHero->lastStrength,hero->memHero->fatigueUpperVal);
			send_msg(hero->getFd(),fatigueMsg);
			
			
		}

		powerCtn=0;
	}
	hero->setPowerCount(powerCtn);
	
	
	
	//检测人物的经验状态
	if (hero->memHero->expTimes!=1)
	{			
		hero->memHero->expTimesCount-=5;
		if (hero->memHero->expTimesCount<=0)
		{
			hero->memHero->expTimes=1;
			hero->memHero->expTimesCount=0;
			
			memset(g_out_buf, 0, 20480);
			sprintf(g_out_buf, "%d,%d,%s", 3, 16, hero->getIdentity(), 22, 0);
			send_msg(hero->getFd(), g_out_buf);
		}
	}
	
	//检测人物时装是否到期
	// Equipment *equip=hero->getWearEquip(0);
	// if (equip!=NULL)
	// {
		// equip->isEffect(hero);
	// }
	// 检测人物翅膀是否到期
	// equip=NULL;
	// equip=hero->getWearEquip(13);
	// if (equip!=NULL)
	// {
		// equip->isEffect(hero);
	// }
	
	// buff药计时器
	int bufferFlag=0;
	for (int i=0;i<10;i++)
	{
		if (hero->memHero->allBuffDrug[i].level!=0)
		{
			// cout<<"hero->memHero->allBuffDrug[i].level:"<<hero->memHero->allBuffDrug[i].level<<endl;
			hero->memHero->allBuffDrug[i].remain_time=hero->memHero->allBuffDrug[i].remain_time-5;
			if (hero->memHero->allBuffDrug[i].remain_time<=0)
			{
				// buff药时间到期,将buff药效果消失
				int resultUse = attribute_decrease(hero, i); 	
				memset(g_out_buf, 0, sizeof(g_out_buf));
				snprintf(g_out_buf, sizeof(g_out_buf),"%d,%d,%s", 3, 16, hero->getIdentity(), i+2, resultUse);
				send_msg(hero->getFd(), g_out_buf);
				initBuffDrugData(i,hero);
				bufferFlag++;
			}
		}
	}
	if (bufferFlag!=0)
	{
		// cout<<"into bufferFlag bufferFlag:"<<bufferFlag<<endl;
		
		hero->send_msg_att();			//更新客户端的人物属性面板
	}
	
	// cout<<"begin hero->memHero->testVipTime:"<<hero->memHero->testVipTime<<endl;
	// if (hero->memHero->testVipTime!=-1&&hero->memHero->testVipTime!=-2)
	// {
		// cout<<"end hero->memHero->testVipTime"<<hero->memHero->testVipTime<<endl<<endl;
		// hero->memHero->testVipTime-=5;
		// if (hero->memHero->testVipTime<=0)
		// {
			// hero->memHero->testVipTime=-2;
			// hero->setVipRights(0);
		// }
	// }
	
	if(hero->saveCount%60==0)
	{
		hero->memSet();
	}
	
	
	ev_timer_start(loop,think);
}

void Hero::initTongBuTimer(void)			//初始化同步计时器
{
	ext_ev_timer_init(&tongBuTimer,heroVerify,5,0,this);
	ev_timer_start(loops,&tongBuTimer);
}

void Hero::stopTongBuTimer(void)
{
	ev_timer_stop(loops,&tongBuTimer);	
}


/*获得角色在副本里面复活次数*/
int Hero::getCpyRevTme(void)
{
	return recoverTmeCtn;
}

/*角色在副本里面复活次数自增1*/
void Hero::addCpyRecTme(void)
{
	recoverTmeCtn += 1;
}

/*初始化副本里面复活次数*/
void Hero::initCpyRecTme(void)
{
	recoverTmeCtn = 0;
}
//取bag指针
Bag* Hero::getBag(void)     								//jolly added 6.25
{
	return bag;
}
//取moeny指针
Money* Hero::getMoney(void)								//jolly added 7.10
{
	return money;
}
//取pet_box指针
Pet_Box* Hero::getPetBox(void)							//jolly added 7.16
{
	return pet_box;
}
//取online_reward指针
Reward_Online* Hero::getRewardOnline(void)
{
	return online_reward;
}
//取ride指针
Ride *Hero::getRide(void)
{
	return ride;
}

	
void happy_cb(struct event_base* loop, ev_timer *think, int revent);
//进入娱乐图开始happy
void Hero::startHappyTimer(void)
{
	cout<<"It's happy time to get reward"<<endl;
	happyAddExp = 0;
	happyAddMoney = 0;
	stayHappyTime = 0;

	ext_ev_timer_init(&happyTimer, happy_cb, 5, 0, this);
	ev_timer_start(loops, &happyTimer);
}

//检查是要happy还是happy结束 //1开2关0不动
int Hero::happyCheck(const char *oldMapId, const char *newMapId)
{
	cout<<"happy check old map is "<<oldMapId<<" new map id is "<<newMapId<<endl;
	// if (!isInHappyTime)
	if (!isInFirstRoomHappyTime && !isInSecondRoomHappyTime)
	{
		return 0;
	}
	if (strcmp(oldMapId, newMapId) == 0)
	{
		//老图和新图相同
		return 0;
	}
	bool happyedFlag = false;
	bool willHappyFlag = false;
	if ((isInFirstRoomHappyTime
			&& (!strcmp(oldMapId, "map_023")
				|| !strncmp(oldMapId, "map_025", 7)
				|| !strncmp(oldMapId, "map_026", 7)))
		|| (isInSecondRoomHappyTime
			&& !strcmp(oldMapId, "map_024")
				|| !strncmp(oldMapId, "map_027", 7)
				|| !strncmp(oldMapId, "map_028", 7)))
	{
		happyedFlag = true;
	} else {
		happyedFlag = false;
	}
	
	if ((isInFirstRoomHappyTime
			&& (!strcmp(newMapId, "map_023")
				|| !strncmp(newMapId, "map_025", 7)
				|| !strncmp(newMapId, "map_026", 7)))
		|| (isInSecondRoomHappyTime
			&& !strcmp(newMapId, "map_024")
				|| !strncmp(newMapId, "map_027", 7)
				|| !strncmp(newMapId, "map_028", 7)))
	{
		willHappyFlag = true;
	} else {
		willHappyFlag = false;
	}

#if 0	
	if (!strcmp(oldMapId, "map_023")
		|| !strcmp(oldMapId, "map_024")
		|| !strncmp(oldMapId, "map_025", 7)
		|| !strncmp(oldMapId, "map_026", 7)
		|| !strncmp(oldMapId, "map_027", 7)
		|| !strncmp(oldMapId, "map_028", 7))
	{
		happyedFlag = true;
	} else {
		happyedFlag = false;
	}

	if (!strcmp(newMapId, "map_023")
		|| !strcmp(newMapId, "map_024")
		|| !strncmp(newMapId, "map_025", 7)
		|| !strncmp(newMapId, "map_026", 7)
		|| !strncmp(newMapId, "map_027", 7)
		|| !strncmp(newMapId, "map_028", 7))
	{
		willHappyFlag = true;
	} else {
		willHappyFlag = false;
	}

#endif

	if (!happyedFlag)
	{
		if (!willHappyFlag)
		{
			return 0;
		} else {
			return 1;
		}
	} else {
		if (!willHappyFlag)
		{
			return 2;
		} else {
			return 0;
		}
	}
	
}

void Hero::endHappyTimer(int flag)
{
	if (flag == 0)
	{	
		char msg[1024] = {0};
		//24,1,
		//sprintf(msg, "24,%d,%d,%d,%d", HAPPY_END_RETURN, stayHappyTime, happyAddExp, happyAddMoney);
		sprintf(msg, "24,%d,%d,%d,%d", HAPPY_END_RETURN,  int(getHappyRemain()), happyAddExp, happyAddMoney);
		send_msg(_fd, msg);			//发送娱乐期间收获
	}
	happyAddExp = 0;
	happyAddMoney = 0;
	stayHappyTime = 0;
	ev_timer_stop(loops, &happyTimer);	
}

//单位时间娱乐收获
int Hero::happyAdd()
{
	char msg[1024] = {0};
	int vipClass = getVipStage();
	cout<<memHero->nickName<<": happy happy so happy and myVip is "<<vipClass<<endl;
	if (vipClass < 0 || vipClass > 10)
	{
		return -1;
	}
	
	unsigned incHappyExp = unsigned(HappyMapRewardConf.rewardLevel[memHero->level].ExpFactor[vipClass]);
	unsigned incHappyMoney = unsigned(HappyMapRewardConf.rewardLevel[memHero->level].MonFactor[vipClass]);
	//定时器触发的发消息事件，要发对fd
	sock_fd = _fd;
	setExpNow(incHappyExp);
	increaseMoney(3, incHappyMoney);	//增长绑定游戏币
	
	happyAddExp += incHappyExp;
	happyAddMoney += incHappyMoney;
	stayHappyTime += HAPPY_PER_TIME;
	sprintf(msg, "24,%d,%d,%d,%d", HAPPY_ADD_PER_TIME, int(getHappyRemain()), happyAddExp, happyAddMoney);
	send_msg(_fd, msg);			//发送娱乐期间收获
	return 0;
}
	
void happy_cb(struct event_base* loop, ev_timer *think, int revent)
{
	cout<<"happy happy calbak happy happy happy"<<endl;
	// char msg[1024] = {0};
	//OneHappyAddTotal_T *oneHappy = (OneHappyAddTotal_T *)think->target;
	Hero *hero = (Hero*)think->target;
	if (hero == NULL)
	{
		cout<<"happy happy calbak find no hero"<<endl;
		return;
	}
	
	char *heroId = hero->getIdentity();
	char *mapId = hero->getMapId();
	if (mapId == NULL)
	{
		cout<<"happy happy calbak find no map"<<endl;
		return;
	}
	
	if (isInFirstRoomHappyTime && (!strcmp(mapId, "map_023") || !strncmp(mapId, "map_025", 7) || !strncmp(mapId, "map_026", 7))
		|| isInSecondRoomHappyTime && (!strcmp(mapId, "map_024") || !strncmp(mapId, "map_027", 7) || !strncmp(mapId, "map_028", 7)))
	{
		hero->happyAdd();	
		ev_timer_start(loop, think);
	} else {
		cout<<"happy happy calbak find map not ok or not in map's happy time and mapId is "<<mapId<<endl;
		cout<<"tianxiadiyilou's happyflag is "<<isInFirstRoomHappyTime<<" and tianshangrenjian's happyflag is "<<isInSecondRoomHappyTime<<endl;
		hero->endHappyTimer(0);
		return;
	}
#if 0	
	if (strcmp(mapId, "map_023") != 0
		&& strcmp(mapId, "map_024") != 0
		&& strncmp(mapId, "map_025", 7) != 0
		&& strncmp(mapId, "map_026", 7) != 0
		&& strncmp(mapId, "map_027", 7) != 0
		&& strncmp(mapId, "map_028", 7) != 0)
	{
		cout<<"happy happy calbak find map not ok and mapId is "<<mapId<<endl;
		return;
	}
#endif
}

//设置金钱
// void Hero::setMoney(int flag, int val)
// {
	// sock_fd = _fd;
	// switch(flag)
	// {
	// case 0: money->setGold(val);return;
	// case 1: money->setBoundGold(val);return;
	// case 2: money->setGameMoney(val);return;
	// case 3: money->setBoundGameMoney(val);return;
	// default: return;
	// }
// }

//flag = 0: 元宝；flag = 1:绑定元宝；flag = 2:银两；flag = 3:绑定银两
//增长金钱
bool Hero::increaseMoney(int flag, int val)
{
	switch(flag)
	{
	case 0: return increaseGold(this,val);
	case 1: return increaseBoundGold(this,val);
	case 2: return increaseGameMoney(this,val);
	case 3: return increaseBoundGameMoney(this,val);
	default: return false;
	}
}

//使用金钱
bool Hero::useMoney(int flag, int val)
{
	switch(flag)
	{
	case 0: return useGold(this,val);
	case 1: return useBoundGold(this,val);
	case 2: return useGameMoney(this,val);
	case 3: return useBoundGameMoney(this,val);
	default: return false;
	}
}

/*红名装备掉落*/
void Hero::dropEquip(Hero *redHero)
{
	cout<<"go here:"<<endl;
	char dropGoodsId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,Equipment*>::iterator equip_it; 

	if(!isDropEquip())
	{
		cout<<"drop goods is falied:"<<endl;
		return;
	}

	int i;
	for(i = 1; i < 13; i++)
	{
		if(redHero->memHero->wearequipdata[i].flag == 1)
		{
			break;
		}
	}
	
    
	// cout<<"go here second:"<<redHero->memHero->wearequipdata[i].goodsid<<endl;
	// cout<<"i:"<<i<<endl;
	strncpy(dropGoodsId,redHero->memHero->wearequipdata[i].goodsid,sizeof(redHero->memHero->wearequipdata[i].goodsid));	
	redHero->memHero->wearequipdata[i].initEquip();
	
	Equipment *equipment=redHero->getEquip(dropGoodsId);
	if (equipment==NULL)
	{
		return;
	}
	cout<<"go here thrid:"<<endl;
	heroDropEquipment(redHero,equipment);
	dropEquipMent[dropGoodsId] = equipment;	
	redHero->dropEquipInst(dropGoodsId);	
	equipment->bronMsg(redHero,memHero->identity);
	equipment->initTime();	
	cout<<"read dropEquip:"<<i<<endl;
}
	

//更新武林目标
void Hero::updataSingleTarget(int page,int id)
{
	if (setWulinTarget(page,id))
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%d",23,COMPLETE_TARGET,1,page,id);
		send_msg(_fd,g_out_buf);
	}
}

//检查索引为index的目标是否完成		若完成返回false 
bool Hero::isTargetFinish(int page,int id)
{
	if (memHero->targetItem[page][id]==1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//领取奖励,更改目标标志为2
bool Hero::receiveTargetSuccess(int page,int id)
{
	memHero->targetItem[page][id]=2;
}

//取扣出罪恶值的标志
int Hero::getCrimCount(void)
{
	return crimCount;
}

void Hero::setCrimCount(int _crimCount)
{
	crimCount=_crimCount;
}

//取扣出耐力值的标志
int Hero::getPowerCount(void)
{
	return powerCount;
}

void Hero::setPowerCount(int _powerCount)
{
	powerCount=_powerCount;
}


bool Hero::pickDropEquipment(Equipment *equip)
{
	if (equip==NULL)
	{
		return false;
	}
	
	char *id=equip->getid();
	map<string,Equip_config*>::iterator it;
	it=id_to_equip.find(id);
	if (it==id_to_equip.end())
	{
		return false;
	}
	if (bag->bagIsFull(1))	//由于装备的堆叠数量为1,所以直接判断保存的数量和剩余格子的关系
	{			
		msg_error(g_out_buf,44);
		send_msg(pg_hero->getFd(),g_out_buf);
		return false;				//背包放不下这么多道具,则1个都不保存
	}
	else
	{
		equip->disperMsg();
		equip->initEquip(it->second);
		EquipmentData *memEquipData=equip->getEquipmentData();
		if (!mem_group->set_data(equip->getentityid(), (char*)memEquipData, (int)sizeof(EquipmentData),where))		//增加新装备的时候,立马向memcached中插入数据
		{						
			cout<<"jolly:save Equip in memcached error in bag.cpp 359"<<endl;
			return false;								//保存进memcached错误,先return,以后有了异常处理机制再修改
		}		
		takeOffEquipToBag(this,equip);
		insertEquip(equip);
	}	
	return true;
}

void Hero::startMoveTimer()
{
	currPt = endPt = getLocation();
	ext_ev_timer_init(&moveTimer, hero_move_cb, 0.5, 0, this);
	ev_timer_start(loops, &moveTimer);
}

//获取速度速度
int Hero::getSpeed()
{
	if (skillBuffState & DEBUF_LOSE_SPEED_STATE)
	{
		return speed - skillBuff[getIndexByState(DEBUF_LOSE_SPEED_STATE)].totalVal;
	}
	else {
		return speed;
	}
}
int Hero::getLastSpeed()
{
	return lastSpeed;
}

void Hero::setSpeed(int _speed)
{
	if (speed != _speed)
	{
		speed = _speed;
		hero_move_cb(loops, &moveTimer, 2);
		setLastSpeed(_speed);
	}
}

void Hero::setLastSpeed(int _speed)
{
	lastSpeed = _speed;
}

void Hero::stopMove()
{
	//停止移动
	hero_move_cb(loops, &moveTimer, 1);
}

void Hero::stopMoveTimer()
{
	ev_timer_stop(loops, &moveTimer);
}


/*判断是否掉装备*/
bool Hero::isDropEquip(void)
{	
	int randNum;
	randNum = random_number(0,100);
	if(randNum <= memHero->crimeValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}
	
int Hero::expDrugUsedNum(int _num)
{
	return memHero->expDrug[_num];
}
	
void Hero::setDrugUsedNum(int _index,int _num)
{
	memHero->expDrug[_index]=_num;
}

//节日活动相关
int Hero::getFestivalRewardFlag(void)
{
	return memHero->festivalRewardFlag;
}

void Hero::setFestivalRewardFlag(int _festivalRewardFlag)
{
	memHero->festivalRewardFlag=_festivalRewardFlag;
}

//猜拳相关 jolly 12-26
void Hero::winFingerGuessingGame(void)			//赢了一局
{
	memHero->fingerGuessingGameCount++;
}

void Hero::joinFingerGuessingGameAi(int money)		//加入与电脑对战猜拳
{
	if (fingerGuessingGame.flag==0&&strcmp(fingerGuessingGame.identity,"0")==0)
	{			
		strncpy(fingerGuessingGame.identity,"1",sizeof(fingerGuessingGame.identity));
		fingerGuessingGame.flag=-1;	
		fingerGuessingGame.money=money;
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",27,FINGERGUESSINGAI_ENTER,1,1);
	}
	else
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",27,FINGERGUESSINGAI_ENTER,1,0);
	}
	send_msg(_fd,g_out_buf);
}

void Hero::joinFingerGuessingGame(int money)			//加入猜拳
{
	if (fingerGuessingGame.flag==0)
	{
		map<int,list<Hero*> >::iterator map_it;	
		map_it=fingerGuessingGamePerson.find(money);
		if (map_it==fingerGuessingGamePerson.end())					//没有该金额的猜拳,则新建
		{
			list<Hero*> newList;
			newList.push_back(this);
			fingerGuessingGame.money=money;
			fingerGuessingGamePerson.insert(map<int,list<Hero*> >::value_type(money,newList));
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",27,FINGERGUESSINGAI_ENTER,2,0);
			send_msg(_fd,g_out_buf);
			fingerGuessingGame.flag=1;
		}
		else
		{
			Hero *other=NULL;
			other=map_it->second.front();
			if (other==NULL)
			{
				cout<<"fingerGuessingGameList error!need return"<<endl;
			}
			else
			{
				if (other->fingerGuessingGame.money==money)
				{
					strncpy(fingerGuessingGame.identity,other->getIdentity(),sizeof(fingerGuessingGame.identity));
					fingerGuessingGame.flag=1;
					fingerGuessingGame.money=money;
					map_it->second.pop_front();
					strncpy(other->fingerGuessingGame.identity,getIdentity(),sizeof(other->fingerGuessingGame.identity));
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%s",27,FINGERGUESSINGAI_ENTER,2,1,other->getNickName());		
					send_msg(_fd,g_out_buf);
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%s",27,FINGERGUESSINGAI_ENTER,2,1,getNickName());		
					send_msg(other->getFd(),g_out_buf);
				}
			}					
		}
	}
	else
	{
		msg_error(g_out_buf,86);	
		send_msg(_fd,g_out_buf);
	}
}

void Hero::exitFingerGuessingGame(void)		//退出猜拳
{
	// cout<<getNickName()<<"猜拳flag:"<<fingerGuessingGame.flag<<endl;
	if (fingerGuessingGame.flag==-1)						//标志为-1,证明在和电脑队长,清空数据即可
	{
		exitFingerGuessingGameInit();
	}
	else if (fingerGuessingGame.flag!=0)
	{
		map<int,list<Hero*> >::iterator map_it;	
		map_it=fingerGuessingGamePerson.find(fingerGuessingGame.money);
		if (strcmp(fingerGuessingGame.identity,"0")==0)		//没有对手,说明在猜拳队列中
		{
			if (map_it==fingerGuessingGamePerson.end())		//这个金额的猜拳没有队列,则说明数据出错
			{
				cout<<"this money has no list!So data is error hero.cpp 6118"<<endl;
			}
			else											//有队列,则找到我自己的顺序
			{
				list<Hero*>::iterator list_it;
				for (list_it=map_it->second.begin();list_it!=map_it->second.end();++list_it)
				{
					if (*list_it!=NULL)
					{				
						if (strcmp((*list_it)->getIdentity(),getIdentity())==0)			//在list中找到了自己,则把自己创建的房间删掉
						{
							map_it->second.erase(list_it);
							if (map_it->second.size()==0)								//若删了list后,list的长度为空了,则删掉这个map的key
							{
								fingerGuessingGamePerson.erase(map_it);
							}
							break;
						}
					}
				}
			}
		}
		else 												//说明有对手,则自己退出的时候需要通知对手自己退出了
		{			
			map<string, Hero*>::iterator it;
			it=heroId_to_pHero.find(fingerGuessingGame.identity);		
			if (it!=heroId_to_pHero.end())					//找到对手实例id
			{
				it->second->otherExitFingerModifyMineData();
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d",27,FINGERGUESSING_EXIT);	
				send_msg(it->second->getFd(),g_out_buf);	//告诉对手我已经退出了
				
				//将对手插入到排序队列中
				if (map_it==fingerGuessingGamePerson.end())	//这个金额的猜拳没有队列,则新建队列
				{
					list<Hero*> newList;
					newList.push_back(it->second);
					fingerGuessingGamePerson.insert(map<int,list<Hero*> >::value_type(fingerGuessingGame.money,newList));
				}
				else										//若之前就有这个队列了,则直接插入到末尾 
				{
					map_it->second.push_back(it->second);
				}
			}	
		}
		
		exitFingerGuessingGameInit();
	}
	
}

void Hero::exitFingerGuessingGameInit(void)		//退出猜拳,数据还原
{
	strncpy(fingerGuessingGame.identity,"0",sizeof(fingerGuessingGame.identity));
	fingerGuessingGame.flag=0;
	fingerGuessingGame.finger=0;
	fingerGuessingGame.money=0;
}

void Hero::otherExitFingerModifyMineData(void)		//对方退出猜拳,修改我的数据
{
	strncpy(fingerGuessingGame.identity,"0",sizeof(fingerGuessingGame.identity));
	fingerGuessingGame.flag=1;
	fingerGuessingGame.finger=0;
}

void Hero::startFingerGuessingGame(void)			//猜拳,点击开始按钮
{
	if (fingerGuessingGame.flag==0)
	{
		fingerGuessingGame.flag=1;
		if (strcmp(fingerGuessingGame.identity,"0")!=0)
		{
			map<string, Hero*>::iterator it;
			it=heroId_to_pHero.find(fingerGuessingGame.identity);	
			if (it!=heroId_to_pHero.end())
			{
				if (it->second->fingerGuessingGame.flag==1)
				{
					//双方都点了开始,猜拳开始
					
				}
			}
			else
			{
				//对方实例找不到,本人退出本次猜拳
				exitFingerGuessingGameInit();
			}
		}		
	}
	else
	{
		cout<<"jolly:this person fingerGuessingGame data is error hero.cpp6124"<<endl;
	}
}

void Hero::fingerGuessingAi(int other)			//猜拳ai逻辑,返回ai结果,目前暂定为纯随机
{
	if (fingerGuessingGame.flag==-1)
	{		
		if (campareBoundGameMoney(this,fingerGuessingGame.money))
		{
			int mine=random_number(1,3);
			int flag=judgeFingerGuessingGameWin(other,mine); 			//猜拳结果0输,1赢,2平
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",27,FINGERGUESSINGAI_RETURN,mine,flag);
			send_msg(_fd,g_out_buf);
			if (flag==0)
			{
				useGameMoney(this,fingerGuessingGame.money);
			}
			else if (flag==1)
			{
				increaseGameMoney(this,fingerGuessingGame.money);
			}
		}		
	}
	else
	{
		cout<<"jolly:you are not fighting wiht computer hero.cpp 6188"<<endl;
	}
}
	
void Hero::fingerGuessGamePlayerFight(int mine)	//玩家对战,猜拳逻辑
{
	if (strcmp(fingerGuessingGame.identity,"0")==0)
	{
		cout<<"jolly:this person fingerGuessingGame data is error hero.cpp6199"<<endl;
	}
	else
	{
		if (campareGameMoney(this,fingerGuessingGame.money))
		{
			if (fingerGuessingGame.finger==0)
			{
				fingerGuessingGame.finger=mine;
				map<string, Hero*>::iterator it;
				it=heroId_to_pHero.find(fingerGuessingGame.identity);	
				if (it!=heroId_to_pHero.end())
				{
					if (it->second->fingerGuessingGame.finger==0)
					{
						snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",27,FINGERGUESSING_WARN,0);		
						send_msg(_fd,g_out_buf);
					}
					else
					{
						int flag=judgeFingerGuessingGameWin(mine,it->second->fingerGuessingGame.finger);
						snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",27,FINGERGUESSINGAI_RETURN,it->second->fingerGuessingGame.finger,flag);		
						send_msg(_fd,g_out_buf);
						snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",27,FINGERGUESSINGAI_RETURN,mine,judgeFingerGuessingGameWin(it->second->fingerGuessingGame.finger,mine));		
						send_msg(it->second->getFd(),g_out_buf);
						it->second->fingerGuessingGame.finger=0;
						fingerGuessingGame.finger=0;
						if (flag==0)
						{
							useGameMoney(this,fingerGuessingGame.money);
							increaseGameMoney(it->second,fingerGuessingGame.money);
						}
						else if (flag==1)
						{
							useGameMoney(it->second,fingerGuessingGame.money);
							increaseGameMoney(this,fingerGuessingGame.money);
						}
					}
				}
				else
				{
					cout<<"jolly:this person fingerGuessingGame data is error hero.cpp6211"<<endl;
				}
			}
		}
		else
		{	
			msg_error(g_out_buf,77);
			send_msg(_fd,g_out_buf);
		}
	}
}

int Hero::judgeFingerGuessingGameWin(int finger1,int finger2)		//决定猜拳输赢
{
	int flag=0; 			//猜拳结果0输,1赢,2平
	if ((finger2-finger1)==1||(finger1==3&&finger2==1))
	{
		flag = 1;
	}
	else if ((finger1-finger2)==1||(finger1==1&&finger2==3))
	{
		flag = 0;
	}
	else
	{
		flag = 2;
	}
	return flag;
}


//人物属性增加
bool Hero::addAttr(int flag, int val)
{
	if (val < 0)
	{
		return false;
	}
	switch (flag)
	{
	case 0:
		memHero->basicHeroData.lifeUpperVal += val;
		break;
	case 1:
		memHero->basicHeroData.magicUpperVal += val;
		break;
	case 2:
		memHero->basicHeroData.outdefense += val;
		break;
	case 3:
		memHero->basicHeroData.indefense += val;
		break;
	case 4:
		memHero->basicHeroData.outattack += val;
		break;
	case 5:
		memHero->basicHeroData.inattack += val;
		break;
	case 6:
		memHero->basicHeroData.hited += val;
		break;
	case 7:
		memHero->basicHeroData.dodge += val;
		break;
	case 8:
		memHero->basicHeroData.tenacity += val;
		break;
	case 9:
		memHero->basicHeroData.crit += val;
		break;
	case 10:
		memHero->basicHeroData.outhurt += val;
		break;
	case 11:
		memHero->basicHeroData.inhurt += val;
		break;
	default:
		return false;
	}
	return true;
}

/*使用激活码*/
void Hero::useActiveCode(char *activeCode,int type)
{

	if(activeCode == NULL || strlen(activeCode) == 0)
	{
		cout<<"the argument activeCode is NULL:"<<endl;
		return;
	}
	
	if(type == 1)
	{
		if(strlen(memHero->partyCodeId) == 0)
		{
			strncpy(memHero->partyCodeId,activeCode,strlen(activeCode));
		}
	}
	
	if(type == 0)
	{		
		if(strlen(memHero->activeCodeId) == 0)
		{
			strncpy(memHero->activeCodeId,activeCode,strlen(activeCode));
		}
	}
}

/*判断是否已使用激活码，如果是则返回真*/
bool Hero::isActiveCodeUse(void)
{
	cout<<"memHero->activeCodeId:"<<memHero->activeCodeId<<endl;
	cout<<"memHero->partyCodeId:"<<memHero->partyCodeId<<endl;
	if(strlen(memHero->activeCodeId) == 0 || strlen(memHero->partyCodeId) == 0)
	{
		return true;
	}
	return false;
}	

//更新日常
void Hero::updateHeroDaily(void)
{
	memHero->heroGuildData.guildSigned = false;
	//有限制次数的项目在每天第一次登陆的时候初始化
	dayLmtFindGroup = dayLmtGroupForAll;			
	//更新到memcached保存数据
	memcpy(memHero->dayLmtItemArr, dayLmtFindGroup.dayLmtItemArr, sizeof(memHero->dayLmtItemArr));
	//日限制项目使用的数量
	memHero->dayLmtUsedNum = dayLmtFindGroup.lastUsedIndex;
	
	resetDailyTask(this);

	initCycleTask();
	freshHeroCycleTask(this);
	updateCycleTaskLevel();
	viewCycleTaskInfo();
	
	sendHeroTaskInfo(this, 1);
	
	memHero->rewarddata.last_day_flag=1;												//使连续登陆奖励可以领取
	mysteriousbussiness->setRefreshMoney(10);
	int chief_camp=campWarController.getCheifFactionName();			
	if (chief_camp==memHero->camp&&chief_camp!=-1)																//判断自己的阵营和武林盟主是不是相同
	{	
		memHero->rewarddata.chief_flag=1;												//相同则可以领取
	}
	else
	{
		memHero->rewarddata.chief_flag=0;												//不同不能领取
	}
	
	memHero->rewarddata.last_day_flag=1;

	midasTouch->reLoadMidasTouch(memHero->vipDailyData.midasTimes,memHero->vipDailyData.remidasTimes);				//本次登陆和上次登陆为不同的一天,因此,重置地石成金功能
	
	
	for (int i=0;i<3;i++)						//本次登陆和上次登陆为不同的一天,一次,人物使用经验药的次数重置
	{
		memHero->expDrug[i]=0;
	}
	
	online_reward->setNewDay();
	
	memHero->festivalRewardFlag=0;				//本次登陆和上次登陆为不同的一天,领取的圣诞奖励重置
	
	memHero->worldSpeakTimes=10;				//非vip的世界喊话次数
	
	
	
	ride->initCost();
	
	setVipRights(memHero->vipDailyData.stage,true);			//每天还原vip数据
	
	// memHero->fatigueUpperVal = memHero->vipDailyData.muscleTimes;
	// memHero->lastStrength = memHero->fatigueUpperVal;                 //疲劳值刷满
	
	//memHero->buyFatigueTmes = 0;
	
	memHero->internalForcesBrushExpTimes = 0;
	memHero->goldBrushExpTimes = 0;
}

//重新计算人物属性
void Hero::reCountHeroArr(void)
{
	//还原人物1级属性
	
	// memHero->basicHeroData.lifeUpperVal = 0;						//生命上限
	// memHero->basicHeroData.magicUpperVal = 0;                   //真气上限
	// memHero->basicHeroData.hited = 0;                           //命中
	// memHero->basicHeroData.crit = 0;                             //暴击
	// memHero->basicHeroData.dodge = 0;                           //闪避
	// memHero->basicHeroData.tenacity = 0;    					//韧性
	// memHero->basicHeroData.outattack = 0;					//外攻击
	// memHero->basicHeroData.inattack = 0;						//内攻击
	// memHero->basicHeroData.outdefense = 0;						//外防御
	// memHero->basicHeroData.indefense = 0;						//内防御
	// memHero->basicHeroData.outhurt = 0;						//外功伤害
	// memHero->basicHeroData.inhurt = 0;							//内功伤害
	
	memHero->basicHeroData.lifeUpperVal = p_conf->lifeUpperVal;						//生命上限
	memHero->basicHeroData.magicUpperVal = p_conf->magicUpperVal;                   //真气上限
	memHero->basicHeroData.hited = p_conf->hited;                           //命中
	memHero->basicHeroData.crit = p_conf->crit;                             //暴击
	memHero->basicHeroData.dodge = p_conf->dodge;                           //闪避
	memHero->basicHeroData.tenacity = p_conf->tenacity;    					//韧性
	memHero->basicHeroData.outattack = p_conf->outAttack;					//外攻击
	memHero->basicHeroData.inattack = p_conf->inAttack;						//内攻击
	memHero->basicHeroData.outdefense = p_conf->outDef;						//外防御
	memHero->basicHeroData.indefense = p_conf->inDef;						//内防御
	memHero->basicHeroData.outhurt = p_conf->outHurt;						//外功伤害
	memHero->basicHeroData.inhurt = p_conf->inHurt;							//内功伤害
	
	// cout<<"-----------------------------------------------"<<endl;
	// cout<<memHero->basicHeroData.lifeUpperVal<<endl;
	// cout<<memHero->basicHeroData.magicUpperVal<<endl;
	// cout<<memHero->basicHeroData.hited<<endl;
	// cout<<memHero->basicHeroData.crit<<endl;
	// cout<<memHero->basicHeroData.dodge<<endl;
	// cout<<memHero->basicHeroData.tenacity<<endl;
	// cout<<memHero->basicHeroData.outattack<<endl;
	// cout<<memHero->basicHeroData.inattack<<endl;
	// cout<<memHero->basicHeroData.outdefense<<endl;
	// cout<<memHero->basicHeroData.indefense<<endl;
	// cout<<memHero->basicHeroData.outhurt<<endl;
	// cout<<memHero->basicHeroData.inhurt<<endl;
	
	// heroBasic.lifeUpperVal = p_conf->lifeUpperVal;										//生命上限
	// heroBasic.magicUpperVal = p_conf->magicUpperVal;									//真气上限
	// heroBasic.hited = p_conf->hited;  					 								//命中
	// heroBasic.crit = p_conf->crit;           											//暴击
	// heroBasic.dodge = p_conf->dodge;          										    //闪避
	// heroBasic.tenacity = p_conf->tenacity;           									//韧性
	// heroBasic.outattack = p_conf->outAttack;              								//外攻击
	// heroBasic.inattack = p_conf->inAttack;              								//内攻击
	// heroBasic.outdefense = p_conf->outDef;              								//外防御
	// heroBasic.indefense = p_conf->inDef;              									//内防御
	// heroBasic.outhurt = p_conf->outHurt;              									//外功伤害
	// heroBasic.inhurt = p_conf->inHurt;              									//内功伤害
	// memHero->basicHeroData.magicVal = memHero->basicHeroData.magicUpperVal ;     		//真气
	// memHero->basicHeroData.lifeVal = memHero->basicHeroData.lifeUpperVal;				//生命
	
	//还原人物升级带来的属性
	for (int i=0;i<memHero->level;i++)
	{
		memHero->basicHeroData.lifeUpperVal += p_conf->addLife[i] ;						//生命上限
		memHero->basicHeroData.magicUpperVal += p_conf->addMagic[i] ;                   //真气上限
		memHero->basicHeroData.hited += p_conf->addHited[i] ;                           //命中
		memHero->basicHeroData.crit += p_conf->addCrit[i] ;                             //暴击
		memHero->basicHeroData.dodge += p_conf->addDodge[i] ;                           //闪避
		memHero->basicHeroData.tenacity += p_conf->addTenacity[i] ;    					//韧性
		memHero->basicHeroData.outattack += p_conf->addOutAttack[i];					//外攻击
		memHero->basicHeroData.inattack += p_conf->addInAttack[i];						//内攻击
		memHero->basicHeroData.outdefense += p_conf->addOutDef[i];						//外防御
		memHero->basicHeroData.indefense += p_conf->addInDef[i];						//内防御
		memHero->basicHeroData.outhurt += p_conf->addOutHurt[i];						//外功伤害
		memHero->basicHeroData.inhurt += p_conf->addInHurt[i];							//内功伤害
	}
	// cout<<"-----------------------------------------------"<<endl;
	// cout<<memHero->basicHeroData.lifeUpperVal<<endl;
	// cout<<memHero->basicHeroData.magicUpperVal<<endl;
	// cout<<memHero->basicHeroData.hited<<endl;
	// cout<<memHero->basicHeroData.crit<<endl;
	// cout<<memHero->basicHeroData.dodge<<endl;
	// cout<<memHero->basicHeroData.tenacity<<endl;
	// cout<<memHero->basicHeroData.outattack<<endl;
	// cout<<memHero->basicHeroData.inattack<<endl;
	// cout<<memHero->basicHeroData.outdefense<<endl;
	// cout<<memHero->basicHeroData.indefense<<endl;
	// cout<<memHero->basicHeroData.outhurt<<endl;
	// cout<<memHero->basicHeroData.inhurt<<endl;
	// cout<<"-----------------------------------------------"<<endl;
	
	//还原装备属性
	map<string,Equipment*>::iterator it;
	for (int i=0;i<14;i++)
	{
		if (memHero->wearequipdata[i].flag==1)
		{		
			it=heroAllEquip.find(memHero->wearequipdata[i].goodsid);
			if(it->second!=NULL)
			{					
				memHero->basicHeroData.lifeUpperVal += it->second->getlife();						//生命上限
				memHero->basicHeroData.magicUpperVal += it->second->getMagic();                   //真气上限
				memHero->basicHeroData.hited += it->second->gethit();                           //命中
				memHero->basicHeroData.crit += it->second->getcrit();                             //暴击
				memHero->basicHeroData.dodge += it->second->getdodge();                           //闪避
				memHero->basicHeroData.tenacity += it->second->gettenacity();    					//韧性
				memHero->basicHeroData.outattack += it->second->getoutattack();					//外攻击
				memHero->basicHeroData.inattack += it->second->getinattack();						//内攻击
				memHero->basicHeroData.outdefense += it->second->getoutdefence();						//外防御
				memHero->basicHeroData.indefense += it->second->getindefence();						//内防御
			}
			else
			{
				continue;
			}
		}
	}
	
	//还原人物锻炼属性还原
	memHero->basicHeroData.lifeUpperVal += memHero->exercisedata.physique*29;
	memHero->basicHeroData.magicUpperVal += memHero->exercisedata.will*29;
	memHero->basicHeroData.hited += memHero->exercisedata.wushu;
	memHero->basicHeroData.crit += memHero->exercisedata.will;
	memHero->basicHeroData.dodge += memHero->exercisedata.shenfa;	
	memHero->basicHeroData.tenacity += memHero->exercisedata.physique;
	memHero->basicHeroData.outattack += memHero->exercisedata.wushu*7;
	memHero->basicHeroData.inattack += memHero->exercisedata.wushu*7;
	memHero->basicHeroData.outdefense += memHero->exercisedata.shenfa*12;
	memHero->basicHeroData.indefense += memHero->exercisedata.shenfa*12;
	
	//经脉属性还原	
	for (int i = 0; i < 8; i++ )
	{
		int val1 = 0, val2 = 0;
		merid->getIncTotalVal(val1, val2, i);
		if (i==0)
		{
			memHero->basicHeroData.lifeUpperVal += val1;
			memHero->basicHeroData.magicUpperVal += val2;
		}
		else if (i==1)
		{
			memHero->basicHeroData.inattack += val1;
			memHero->basicHeroData.inhurt += val2;
		}
		else if (i==2)
		{
			memHero->basicHeroData.outattack +=val1;
			memHero->basicHeroData.outhurt+=val2;
		}
		else if (i==3)
		{			
			memHero->basicHeroData.outdefense += val1;
			memHero->basicHeroData.indefense += val2;
		}
		else if (i==4)
		{
			memHero->basicHeroData.hited += val1;
		}
		else if (i==5)
		{
			memHero->basicHeroData.crit += val1;
		}
		else if (i==6)
		{
			memHero->basicHeroData.dodge += val1;
		}
		else if (i==7)
		{
			memHero->basicHeroData.tenacity += val1;
		}
	}
	
	Guild* heroGuild = getGuildWithId(memHero->heroGuildData.guildId);
	if (heroGuild != NULL)
	{
		for (int k = 0; k < 10; k++)
		{
			addAttr(k, memHero->heroGuildData.guildSkillAddTotal[k]);
		}
	}
	
	for (int k = 0; k < HERO_SKILL_MAX_NUM; k++)
	{
		//所有技能CD清除，置为可使用
		memHero->skills[k].lastUsedTime = 0;
		if (k == 0 || memHero->skills[k].level <= 0)
		{
			//第一个技能是普攻或者该技能未学习
			continue;
		}
		HeroSkill* pSkill = NULL;
		map<string, HeroSkill*>::iterator it_skill;
		it_skill = skillId_2_heroSkill.find(memHero->skills[k].skillId);
		if (it_skill == skillId_2_heroSkill.end())
		{
			memset(memHero->skills[k].skillId, 0, sizeof (memHero->skills[k].skillId));
			memHero->skills[k].level = 0;
			continue;
		}
		pSkill = it_skill->second;
		if (strcmp(memHero->skills[k].skillId, "M003") == 0)
		{
			memHero->basicHeroData.outattack += pSkill->getTotalVal(memHero->skills[k].level);
		} else if (strcmp(memHero->skills[k].skillId, "M004") == 0)
		{
			memHero->basicHeroData.outdefense += pSkill->getTotalVal(memHero->skills[k].level);
		} else if (strcmp(memHero->skills[k].skillId, "M006") == 0)
		{
			memHero->basicHeroData.lifeUpperVal += pSkill->getTotalVal(memHero->skills[k].level);
		} else if (strcmp(memHero->skills[k].skillId, "H003") == 0)
		{
			memHero->basicHeroData.dodge += pSkill->getTotalVal(memHero->skills[k].level);
		} else if (strcmp(memHero->skills[k].skillId, "H004") == 0)
		{
			memHero->basicHeroData.crit += pSkill->getTotalVal(memHero->skills[k].level);
		} else if (strcmp(memHero->skills[k].skillId, "H006") == 0)
		{
			memHero->basicHeroData.outattack += pSkill->getTotalVal(memHero->skills[k].level);
		} else if (strcmp(memHero->skills[k].skillId, "X003") == 0)
		{
			memHero->basicHeroData.outattack += pSkill->getTotalVal(memHero->skills[k].level);
		} else if (strcmp(memHero->skills[k].skillId, "X004") == 0)
		{
			memHero->basicHeroData.hited += pSkill->getTotalVal(memHero->skills[k].level);
		} else if (strcmp(memHero->skills[k].skillId, "X006") == 0)
		{
			memHero->basicHeroData.crit += pSkill->getTotalVal(memHero->skills[k].level);
		} else if (strcmp(memHero->skills[k].skillId, "G003") == 0)
		{
			memHero->basicHeroData.indefense += pSkill->getTotalVal(memHero->skills[k].level);
		} else if (strcmp(memHero->skills[k].skillId, "G004") == 0)
		{
			memHero->basicHeroData.outdefense += pSkill->getTotalVal(memHero->skills[k].level);
		} else if (strcmp(memHero->skills[k].skillId, "G006") == 0)
		{
			memHero->basicHeroData.tenacity += pSkill->getTotalVal(memHero->skills[k].level);
		}
	}
	internalForcesAttrReCountByLevel(this);
	//坐骑给人物加的属性
	ride->increaseAtt(this);
}

void Hero::setHaveJoinedGuildWar()
{
	int index = dayLmtFindGroup.incOneItem("joinGuildWarTimes");
	if (index != -1)
	{
		//更新到memcached保存数据
		memHero->dayLmtItemArr[index].incVal();
	}
}

bool Hero::canJoinGuildWar()
{
	//等于0表示还可以参加
	return (dayLmtFindGroup.isOneItemFull("joinGuildWarTimes") == 0);
}

//玩家首次登录送时装
void Hero::firstIntoGame(void)
{
	map<string,Equip_config*>::iterator it;
	char goodsid[20]={0};
	if(strcmp(memHero->basicHeroData.party,"M")==0)
	{		
		strncpy(goodsid,"b_m_0002",sizeof(goodsid));
	}
	if(strcmp(memHero->basicHeroData.party,"H")==0)
	{		
		strncpy(goodsid,"b_h_0002",sizeof(goodsid));
	}
	if(strcmp(memHero->basicHeroData.party,"G")==0)
	{		
		strncpy(goodsid,"b_g_0002",sizeof(goodsid));
	}
	if(strcmp(memHero->basicHeroData.party,"X")==0)
	{	
		strncpy(goodsid,"b_x_0002",sizeof(goodsid));
	}	
	it=id_to_equip.find(goodsid);	
	if (it==id_to_equip.end())
	{
		cout<<"Jolly:According to the goodsid:"<<goodsid<<"can't find the entity"<<endl;
	}
	else
	{
		Equip_config *equip_config=it->second;
		Equipment *equipment=new Equipment(equip_config);
		equipment->beginTime();
		equipment->setisbag(1);
		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<equipment->getentityid()<<endl;
		heroAllEquip.insert(map<string,Equipment*>::value_type(equipment->getentityid(),equipment));
		EquipmentData *memEquipData=equipment->getEquipmentData();
		if (!mem_group->set_data(equipment->getentityid(), (char*)memEquipData, (int)sizeof(EquipmentData),where))		//增加新装备的时候,立马向memcached中插入数据
		{						
			cout<<"jolly:save Equipment into memcached error hero.cpp 6791"<<endl;
			return;								//保存进memcached错误,先return,以后有了异常处理机制再修改
		}
		memHero->wearequipdata[0].flag=1;
		strncpy(memHero->wearequipdata[0].goodsid,equipment->getentityid(),sizeof(memHero->wearequipdata[0].goodsid));
		strncpy(memHero->wearequipdata[0].typeId,equipment->getid(),sizeof(memHero->wearequipdata[0].typeId));
	}
}

//非会员是否可以免费世界喊话
bool Hero::ifNotVipCanSpeak(void)
{
	cout<<"memHero->worldSpeakTimes:"<<memHero->worldSpeakTimes<<endl;
	if (memHero->worldSpeakTimes>0&&memHero->worldSpeakTimes<=10)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//喊话成功,免费喊话次数-1,同时返回剩余的返回次数
int Hero::getWorldSpeakTimes(void)
{
	memHero->worldSpeakTimes--;
	if (memHero->worldSpeakTimes<0)
	{
		memHero->worldSpeakTimes=0;
	}
	else if (memHero->worldSpeakTimes>10)
	{
		memHero->worldSpeakTimes=10;
	}
	return memHero->worldSpeakTimes;
}

/* 获取当前角色所在服务器的区编号 */
int Hero::getArea()
{
	return where;
}

void Hero::setVipRights(int stage,bool isMemCahed)
{
	if (stage>10||stage<0)
	{
		return;
	}
	
	Nbox* box;
	Map_Inform* map_now;
	map_now = getMap();
	if(map_now == NULL)
	{
		cout<<"map_now is error:"<<memHero->identity<<endl;
		return;
	}
	box = map_now->getBox();
	if(box == NULL)
	{
		cout<<"box is error:"<<memHero->identity<<endl;
		return;
	}		
	StyObj obj(memHero->identity,HERO_STYLE_TYPE);		
	
	box->getStaInSrcVec(obj);	
	
	setVipData(stage,isMemCahed);	
	
	memset(g_out_buf,0,sizeof(g_out_buf));//00349
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d",19,4,getIdentity(),memHero->vipDailyData.stage);
	box->sentBoxMsg(g_out_buf);
	
	if(!isMemCahed)
	{
		char purchaseMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
		sprintf(purchaseMsg,"8,12,%s,%d,%d",getIdentity(),memHero->lastStrength,memHero->fatigueUpperVal);
		send_msg(getFd(), purchaseMsg);
	}
}

void Hero::setVipData(int stage,bool isMemCahed)
{
	memHero->vipDailyData.stage=stage;
	memHero->vipDailyData.recharge=vipRewardData[stage].recharge;			
	memHero->vipDailyData.store=vipRewardData[stage].store;			
	memHero->vipDailyData.warehouse=vipRewardData[stage].warehouse;			
	memHero->vipDailyData.flyTimes=vipRewardData[stage].flyTimes;			
	memHero->vipDailyData.callTimes=vipRewardData[stage].callTimes;			
	memHero->vipDailyData.lixianTimes=vipRewardData[stage].lixianTimes;			
	strncpy(memHero->vipDailyData.bagId,vipRewardData[stage].bagId,sizeof(memHero->vipDailyData.bagId));			
	memHero->vipDailyData.lianxuTimes=vipRewardData[stage].lianxuTimes;			
	memHero->vipDailyData.monTimes=vipRewardData[stage].monTimes;			
	memHero->vipDailyData.dazuoTimes=vipRewardData[stage].dazuoTimes;			
	memHero->vipDailyData.guildTimes=vipRewardData[stage].guildTimes;			
	memHero->vipDailyData.muscleTimes=vipRewardData[stage].muscleTimes;			
	memHero->vipDailyData.buyTimes=vipRewardData[stage].buyTimes;			
	memHero->vipDailyData.midasTimes=vipRewardData[stage].midasTimes;			
	memHero->vipDailyData.remidasTimes=vipRewardData[stage].remidasTimes;			
	memHero->vipDailyData.fubenRate=vipRewardData[stage].fubenRate;			
	memHero->vipDailyData.refreshTimes=vipRewardData[stage].refreshTimes;			
	memHero->vipDailyData.freshNumber=vipRewardData[stage].freshNumber;			
	memHero->vipDailyData.zuoqiFresh=vipRewardData[stage].zuoqiFresh;			
	memHero->vipDailyData.zuoqiNumber=vipRewardData[stage].zuoqiNumber;			
	memHero->vipDailyData.zuoqiRate=vipRewardData[stage].zuoqiRate;			
	memHero->vipDailyData.rongLianRate=vipRewardData[stage].rongLianRate;	
	memHero->vipDailyData.receiveFlag=1;
	
	if(!isMemCahed)
	{
		memHero->fatigueUpperVal = memHero->vipDailyData.muscleTimes;	/*刷新体力值*/		
		memHero->lastStrength = memHero->fatigueUpperVal;			//jolly 根据4.26号策划需求修改	
	}
	
}

void Hero::judgeVipLevel(void)
{
	int i=memHero->vipDailyData.stage;
	cout<<"begin i:"<<i<<endl;
	for (i;i<11;i++)
	{
		if (money->getAccMoney()<memHero->vipDailyData.recharge)
		{
			cout<<"return"<<endl;
			cout<<"accMoney:"<<money->getAccMoney()<<"    recharge:"<<memHero->vipDailyData.recharge<<endl;
			return;
		}
		else if (memHero->vipDailyData.stage!=10)
		{
			cout<<"accMoney:"<<money->getAccMoney()<<"    recharge:"<<memHero->vipDailyData.recharge<<endl;
			cout<<"setVipRights"<<endl;
			setVipRights(memHero->vipDailyData.stage+1);
		}
	}
}

/*原先的创建角色时，开启第一层塔的第一层*/
void Hero::initOldNowTowerId(void)
{

	map<string,map<string,string> >::iterator tower_it;
	map<string,string>::iterator layer_it;
	if(memHero == NULL)
	{
		cout<<"Hero::initNowTowerId the memHero is NULL:"<<endl;
		return;
	}
	
	tower_it = towerMapConf.find(memHero->nowTowerId);
	if(tower_it == towerMapConf.end())
	{
		cout<<" Hero::initOldNowTowerId old hero:"<<endl;
		initNowTowerId();
	}
}


/*创建角色时，开启第一层塔的第一层*/
void Hero::initNowTowerId(void)
{

	map<string,map<string,string> >::iterator tower_it;
	map<string,string>::iterator layer_it;
	if(memHero == NULL)
	{
		cout<<"Hero::initNowTowerId the memHero is NULL:"<<endl;
		return;
	}
	
	tower_it = towerMapConf.begin();
	
	memset(memHero->nowTowerId,'\0',sizeof(memHero->nowTowerId));
	memset(memHero->nowLayerId,'\0',sizeof(memHero->nowLayerId));
	
	strncpy(memHero->nowTowerId,tower_it->first.c_str(),tower_it->first.size());
	layer_it = tower_it->second.begin();
	strncpy(memHero->nowLayerId,layer_it->first.c_str(),layer_it->first.size());
}

/*初始化黑木崖数据*/
void Hero::initTowerLayerRecord(void)
{
	if(towerLayerRecord == NULL)
	{
		towerLayerRecord = new TowerLayerRecord(this);
	}
}

/*获得黑木崖数据*/
TowerLayerRecord* Hero::getTowerLayerRecord(void)
{
	return towerLayerRecord;
}

/*角色下线删掉黑木崖塔数据开启情况*/
void Hero::deleteTowerLayerRecord(void)
{
	if(towerLayerRecord)
	{
		delete towerLayerRecord;
		towerLayerRecord = NULL;
	}
}

/*调整体力值*/
void Hero::adjustFatigue(void)
{
	if(memHero == NULL)
	{
		cout<<"Hero::adjustFatigue the memHero is NULL:"<<getIdentity()<<endl;
		return;
	}
		
	memHero->fatigueUpperVal = memHero->vipDailyData.muscleTimes;
	
#if 0	
	if(memHero->fatigueUpperVal > 50 || memHero->fatigueUpperVal <= 0)
	{
		memHero->fatigueUpperVal = 50;
	}
#endif

	if(memHero->lastStrength > memHero->fatigueUpperVal || memHero->lastStrength < 0)
	{
		memHero->lastStrength = memHero->fatigueUpperVal;
	}
	
	/*初始化购买次数*/
	if(memHero->buyFatigueTmes > memHero->vipDailyData.buyTimes)
	{
		memHero->buyFatigueTmes = 0;
	}
	
	
	// memHero->rewarddata.offline_time=online_time-memHero->offlineTime;
	int offlinehour=(online_time-memHero->offlineTime)/3600;
	if (offlinehour<0)
	{
		return;
	}
	cout<<"offlinehour in Hero::adjustFatigue before:"<<offlinehour << endl;
	//把离线时间加上
	setFatigueVal(offlinehour * 10 + memHero->lastStrength);
	
	cout<<"offlinehour in Hero::adjustFatigue end:"<<offlinehour * 10 + memHero->lastStrength<<endl;
}

/*设置体力值*/
void Hero::setFatigueVal(int _fatigueVal)
{
	if(memHero == NULL)
	{
		cout<<"Hero::setFatigueVal the memHero is NULL:"<<getIdentity()<<endl;
		return;
	}
	if(_fatigueVal < 0)
	{
		cout<<"Hero::setFatigueVal the _fatigueVal is error:"<<getIdentity()<<endl;
		return;
	}
	
	memHero->lastStrength = _fatigueVal;
	
	if(memHero->lastStrength > memHero->fatigueUpperVal || memHero->lastStrength < 0)
	{
		memHero->lastStrength = memHero->fatigueUpperVal;
	}
}	

/*判断是否可以购买体力值*/
bool Hero::isCanBuyFatigue(void)
{
	if(memHero == NULL)
	{
		cout<<"Hero::isCanBuyFatigue the memHero is NULL:"<<getIdentity()<<endl;
		return false;
	}
	
	if(memHero->buyFatigueTmes < memHero->vipDailyData.buyTimes)
	{		
		return true;
	}
	return false;
}

/*计算防御伤害率*/
double Hero::ctnDefenseRatio(bool isInnerAttack)
{
	/*外防*/
	if(!isInnerAttack)
	{
		cout<<"hero isOutAttack:"<<(1.0 * memHero->basicHeroData.outdefense) / (memHero->level * 500 + memHero->basicHeroData.outdefense)<<" memHero->basicHeroData.outdefense:"<<memHero->basicHeroData.outdefense<<endl;
		return (1.0 * memHero->basicHeroData.outdefense) / (memHero->level * 500 + memHero->basicHeroData.outdefense);
		
	}
	
	// cout<<"hero isInnerAttack:"<<(1.0 * getInDefense()) / (memHero->level * 500 + getInDefense())<<" getInDefense():"<<getInDefense()<<endl;
		
	/*内防*/
	return (1.0 * getInDefense()) / (memHero->level * 500 + getInDefense());
}

/*计算防御伤害率*/
double Hero::ctnTenacityRatio(void)
{
	return 5 + getTenacity()/30;
}

/*设置角色在哪个层*/
void Hero::setChoiseLayerId(char *_choiseLayerId)
{
	if(!_choiseLayerId)
	{
		return;
	}
	memset(choiseLayerId,'\0',sizeof(choiseLayerId));
	strncpy(choiseLayerId,_choiseLayerId,strlen(_choiseLayerId));
}

/*获得角色在哪个层*/
char* Hero::getChoiseLayerId(void)
{
	return choiseLayerId;	
}

/*把可进层数组置0*/
void Hero::initZoreLayerFlg(void)
{
	if(!memHero)
	{
		cout<<"Hero::initZoreLayerFlg the memHero is NULL:"<<endl;
		return;
	}
	int len = sizeof(memHero->layerFlg)/sizeof(memHero->layerFlg[0]);
	for(size_t length = 0; length < len;++length)
	{
		memHero->layerFlg[length] = 0;
	}
	memHero->layerFlg[0] = 1;
}

/*更具当前层次设置每层可进入状态*/
void Hero::initTowerLayerFlg(void)
{
	if(!memHero)
	{
		cout<<"Hero::initZoreLayerFlg the memHero is NULL:"<<endl;
		return;
	}	
	
	/*从0层开始*/
	size_t index = *(memHero->nowLayerId + strlen(memHero->nowLayerId) - 1) - '0' - 1;
	
	index %= 5;
	
	int len = sizeof(memHero->layerFlg)/sizeof(memHero->layerFlg[0]);
	size_t length;
	
	for(length = 0; length <= index;++length)
	{
		memHero->layerFlg[length] = 1;
	}
	
	for(;length < len;++length)
	{
		memHero->layerFlg[length] = 0;
	}
}
	

//取vip等级
int Hero::getVipStage(void)
{
	return memHero->vipDailyData.stage;
}

//宠物技能点增加
void Hero::addPetSkillExp(int addVal)
{
	if (addVal > 0)
	{
		memHero->petSkillNumber += addVal;
		if (memHero->petSkillNumber & 0x80000000)
		{
			memHero->petSkillNumber = 0x7fffFFFF;
		}
	}
	
}

int Hero::getHeroSkillExp()
{
	return memHero->heroSkillExp;
}

void Hero::addHeroSkillExp(int addVal)
{
	if (addVal < 0)
	{
		return;
	}
	memHero->heroSkillExp += addVal;
	if (memHero->heroSkillExp >= 0x7fffFFFF)
	{
		memHero->heroSkillExp = 0x7fffFFFF;
	}
	
	char msg[1024] = {0};
	sprintf(msg, "26,5,%d", memHero->heroSkillExp);
	send_msg(getFd(), msg);
}

int Hero::useHeroSkillExp(int useVal)
{
	if (useVal <= 0)
	{
		return 1;
	}
	
	if (memHero->heroSkillExp < useVal)
	{
		return 2;
	}
	
	memHero->heroSkillExp -= useVal;
	return 0;
}


//体验vip
// void Hero::startTestVip(void)
// {
	// if (memHero->vipDailyData.stage==0&&memHero->testVipTime==-1)
	// {
		// memHero->testVipTime=1800;
		// setVipRights(10);	

		// memset(g_out_buf,0,sizeof(g_out_buf));
		// snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%d,%d",9,36,memHero->vipDailyData.stage,memHero->vipDailyData.recharge,money->getAccMoney(),0);
		// send_msg(_fd,g_out_buf);		
	// }
	// else
	// {
		// memset(g_out_buf,0,sizeof(g_out_buf));
		// msg_error(g_out_buf,139);
		// send_msg(_fd,g_out_buf);
	// }
// }

int Hero::getInternalForcesLevel()
{
	return memHero->internalForcesLevel;
}

bool Hero::internalForcesLevelUp()
{
	if (memHero->internalForcesLevel < MAX_INTERNAL_FORCES_LEVEL)
	{
		memHero->internalForcesLevel++;
		return true;
	}
	
	return false;
}

int Hero::getInternalForces()
{
	return memHero->internalForces;
}

void Hero::addInternalForces(int value)
{
	if (value <= 0)
	{
		return;
	}
	
	if (memHero->internalForces + (unsigned)value > 0x7fffFFFF)
	{
		memHero->internalForces = 0x7fffFFFF;
		return;
	}
	memHero->internalForces += (unsigned)value;
	bool canLvlUp = isInForsCanLvlUp(this);
	char msg[512] = {0};
	sprintf(msg, "8,18,%d,%d", memHero->internalForces, canLvlUp);
	send_msg(getFd(), msg);
}

bool Hero::useInternalForces(int value)
{
	if (value < 0)
	{
		return false;
	}
	
	if (memHero->internalForces < (unsigned)value)
	{
		return false;
	}
	
	memHero->internalForces -= (unsigned)value;
	return true;
}

int Hero::getInternalForcesExpNow()
{
	return memHero->internalForcesExpNow;
}

void Hero::setInternalForcesExpNow(int newExp)
{
	memHero->internalForcesExpNow = newExp;
}

int Hero::getInternalForcesUpgradeNeedExp()
{
	return memHero->internalForcesUpgradeNeedExp;
}

void Hero::setInternalForcesUpgradeNeedExp(int nextExp)
{
	memHero->internalForcesUpgradeNeedExp = nextExp;
}

int Hero::getInternalForcesBrushExpTimes()
{
	return memHero->internalForcesBrushExpTimes;
}

void Hero::incInternalForcesBrushExpTimes()
{
	memHero->internalForcesBrushExpTimes += 1;
}

int Hero::getGoldBrushExpTimes()
{
	return memHero->goldBrushExpTimes;
}

void Hero::incGoldBrushExpTimes()
{
	memHero->goldBrushExpTimes += 1;
}

//判断装备是否有12件紫装，给相应头衔，基础达标者
void Hero::titleOfPurpleEquip(void)		
{
	//先给橙装头衔
	titleOfOrangeEquip();
	
	if(heroAllEquip.size() < 12)
	{
		return;
	}
	size_t purpleEquipCtn = 0;
	for(map<string,Equipment*>::iterator it = heroAllEquip.begin();it != heroAllEquip.end();++it)
	{
		Equipment *wear = it->second;
		
		if(!wear)
		{
			/*紫装，且穿身上*/
			if(wear->getrank() == 3 && wear->getIsBag() == 1)
			{
				++purpleEquipCtn;
			}
		}
	}
	
	/*给头衔，基础达标者*/
	if(purpleEquipCtn >= 11)
	{
		addTitle("T015");
	}	
	
	
}


//判断装备是否有4件橙装，给相应头衔，名牌
void Hero::titleOfOrangeEquip(void)		
{
	
	if(heroAllEquip.size() < 4)
	{
		return;
	}
	size_t purpleEquipCtn = 0;
	for(map<string,Equipment*>::iterator it = heroAllEquip.begin();it != heroAllEquip.end();++it)
	{
		Equipment *wear = it->second;
		
		if(!wear)
		{
			/*橙装，且穿身上，满级*/
			if(wear->getrank() == 5 && wear->getIsBag() == 1 && wear->getRongLianLevel() == 50)
			{
				++purpleEquipCtn;
			}
		}
	}
	
	/*给头衔，名牌*/
	if(purpleEquipCtn >= 3)
	{
		addTitle("T017");
	}	
}


//刷新帮派任务
void Hero::refreshGuildTask()
{
	set<string>::iterator it_task;
	char msg[1024] = {0};
	sprintf(msg, "5,8,%d", (int)guildTaskList.size());
	//非今天完成的帮派任务
	for (it_task = guildTaskList.begin(); it_task != guildTaskList.end(); it_task++)
	{
		int index = dayLmtFindGroup.clrOneItemVal(*it_task);
		if (index != -1)
		{
			//更新到memcached保存数据
			memHero->dayLmtItemArr[index].clrVal();
		}
		
		// string taskId = (*it_task);
		clrOneFinishTaskMap(const_cast<char*>((*it_task).c_str()));
		sprintf(msg + strlen(msg), ",%s", const_cast<char*>((*it_task).c_str()));
	}
	send_msg(getFd(), msg);
}


void Hero::insertGroupId(const char *gorupId)
{
	chatGroupIdSet.insert(gorupId);
}

void Hero::eraseGroupId(const char *gorupId)
{
	chatGroupIdSet.erase(gorupId);
}

//退出时
void Hero::clearChatSet()
{
	for(set<string>::iterator group_it = chatGroupIdSet.begin();group_it != chatGroupIdSet.end();++group_it)
	{
		ChatGroup* chat = chatManager->getChatGroupHandle((*group_it).c_str());
		if(chat)
		{
			chat->erase((const char*)memHero->identity);
			
			//回收群
			if(chat->empty())
			{
				chatManager->recoverGroupHandle((*group_it).c_str());
			}
		}
	}
}


bool Hero::isPassTowerLayer(char *towerLayerId)
{
	if (strlen(towerLayerId) != 19)
	{
		return false;
	}
	
	if (strncmp(memHero->nowTowerId, towerLayerId, 9) > 0)
	{
		return true;
	} else {
		if (strncmp(memHero->nowLayerId, towerLayerId + 10, 9) > 0)
		{
			return true;
		}
	}
	
	return false;
}

int Hero::getNowDay(void)
{
	return nowDay;
}

void Hero::setNowDay(int _nowDay)
{
	nowDay=_nowDay;
}

int Hero::getAllowSignGold(void)
{
	return allowSignGold;
}

int Hero::getAllowSign(void)
{
	return allowSign;
}

void Hero::setAllowSign(int _allowSign)
{
	allowSign=_allowSign;
}

void Hero::setAllowSignGold(int _allowSignGold)
{
	allowSignGold=_allowSignGold;
}

int Hero::getVipCpyFreshNum()
{
	return memHero->vipDailyData.freshNumber;
}


void Hero::setTaskPassChapt(int chapt)
{
	if (chapt >= 1 && chapt < MAX_TASK_CHAPT_NUM)
	{
		memHero->taskSaveData.passChapt[chapt - 1] = 1;
	}
}

int Hero::isChaptTaskPass(int chapt)
{
	if (chapt >= 1 && chapt < MAX_TASK_CHAPT_NUM)
	{
		return memHero->taskSaveData.passChapt[chapt - 1];
	} else {
		//
		cout<<"taskChapt is not valid when check is ChaptTaskPass!"<<endl;
		return 0;
	}
}
 
int Hero::getTaskChaptReward(int chapt)
{
	if (chapt < 1 || chapt > MAX_TASK_CHAPT_NUM)
	{
		//该章节不是有效章节
		return 1;
	}
	
	if (memHero->taskSaveData.passChapt[chapt - 1] == 0)
	{
		//此章节任务未结束
		return 2;
	}
	
	if (memHero->taskSaveData.rewardChapt[chapt - 1] == 1)
	{
		//该章节奖励已经领取
		return 3;
	}
	
	map<int, TaskChaptReward_T>::iterator it_reward = chapt_2_taskReward.find(chapt);
	if (it_reward == chapt_2_taskReward.end())
	{
		//任务配置错误，该章节无章节奖励
		return 4;
	}
	
	if (bag == NULL)
	{
		//系统出错，玩家无背包数据
		return 5;
	}
	
	TaskChaptReward_T* chaptReward = &it_reward->second;
	int remainNum = bag->remainGridNum();
	
	if (remainNum < chaptReward->rewardNum)
	{
		//背包属于空间不足
		return 6;
	}
	
	if (!saveGoodsInBag(this, chaptReward->rewardId, chaptReward->rewardNum, 1))
	{
		//背包剩余空间不足
		return 7;
	}
	setGotTaskChaptReward(chapt);
	return 0;
}


bool Hero::isTaskChaptReward(int chapt)
{
	if (chapt >= 1 && chapt < MAX_TASK_CHAPT_NUM)
	{
		return (memHero->taskSaveData.rewardChapt[chapt - 1] == 1);
	}
	
	return false;
}

void Hero::setGotTaskChaptReward(int chapt)
{
	if (chapt >= 1 && chapt < MAX_TASK_CHAPT_NUM)
	{
		memHero->taskSaveData.rewardChapt[chapt - 1] = 1;
	}
}

const char* Hero::getTeamerId()const
{
	return memHero->teamerId;
}


void Hero::setTeamerId(const char *_teamerId)
{
	memset(memHero->teamerId,'\0',sizeof(memHero->teamerId));
	if(!_teamerId)
	{
		cout<<"Hero::setTeamerId the _teamerId is error:"<<endl;
		return;
	}
	
	strncpy(memHero->teamerId,_teamerId,strlen(_teamerId));
	
	brushTeamStation();
}


void Hero::adjustTeamerId(void)
{
	if(strlen(memHero->teamerId) == 0)
	{
		return;
	}
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	if(!teamManger)
	{
		cout<<"Hero::adjustTeamerId the teamManger is NULL:"<<endl;		
		memset(memHero->teamerId,'\0',sizeof(memHero->teamerId));
		return;
	}
	
	Team *team = teamManger->getTeamHandle(memHero->teamerId);
		
	if(!team)
	{
		cout<<"Hero::adjustTeamerId team is NULL:"<<endl;
		memset(memHero->teamerId,'\0',sizeof(memHero->teamerId));
		return;		
	}
}


void Hero::offLineTeam()
{
	if(strlen(memHero->teamerId) == 0)
	{
		return;
	}
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	if(!teamManger)
	{
		cout<<"Hero::offLineTeam the teamManger is NULL:"<<endl;		
		memset(memHero->teamerId,'\0',sizeof(memHero->teamerId));
		return;
	}
	
	Team *team = teamManger->getTeamHandle(memHero->teamerId);
		
	if(!team)
	{
		cout<<"Hero::offLineTeam team is NULL:"<<endl;
		memset(memHero->teamerId,'\0',sizeof(memHero->teamerId));
		return;		
	}
	
	if(team->memOffLine(this))
	{
		if(team->memOnLineSize() == 0)
		{			
			teamManger->recoverTeamHandle(memHero->teamerId);
			memset(memHero->teamerId,'\0',sizeof(memHero->teamerId));
			return;
		}
		
		team->formTeamMemMsg(getIdentity());
		
		team->sendMsg(team->getTeamMemMsg());
		
		const char* newHeader = team->getHeader();
		
		Hero *headHero = heroid_to_hero(newHeader);
		
		brushTeamStation();
		
		if(headHero)
		{
			headHero->brushTeamStation();
		}		
	}
	else
	{
		memset(memHero->teamerId,'\0',sizeof(memHero->teamerId));
	}	
}

void Hero::initTeamerId(void)
{
	memset(memHero->teamerId,'\0',sizeof(memHero->teamerId));	
}

void    Hero::brushTeamStation()
{
	StyObj obj(memHero->identity,HERO_STYLE_TYPE);	            
	
    Nbox *box = map_now->getBox();	
	
	if(!box)
	{
		return;
	}	
	
	box->getStaInSrcVec(obj);	
	
	string brushMsg =  CreateMessage::brushHeroTeamStation(this);
	
	box->sentBoxMsg(const_cast<char*>((brushMsg).c_str()));	
		
	return ;
}

int Hero::getAllFourDiamonNumber()		//取身上所有装备的4级宝石数量
{
	int diamonNumber=0;
	Equipment *equip=NULL;
	for (int i=0;i<14;i++)
	{
		equip=getEquip(memHero->wearequipdata[i].goodsid);
		if (equip==NULL)
		{
			continue;
		}
		diamonNumber+=equip->getFourDiamonNumber();
	}
	return diamonNumber;
}


int Hero::getCycleTaskLevel()
{
	return memHero->taskSaveData.cycleTaskLevel;
}

void Hero::updateCycleTaskLevel()
{
	memHero->taskSaveData.cycleTaskLevel = (getLevel() / 10) * 10;
}
	
int Hero::getCycleLoop()
{
	return memHero->taskSaveData.cycleTaskLoop;
}

void Hero::viewCycleTaskInfo()
{
	char msg[2048] = {0};
	if (getLevel() < BEGIN_CYCLE_TASK_LEVEL)
	{
		sprintf(msg, "5,10,0");
	} else {
		sprintf(msg, "5,10,1,%d,%d", memHero->taskSaveData.cycleTaskLevel, memHero->taskSaveData.cycleTaskLoop + 1);
		for (int i = 0; i < 10; i++)
		{
			sprintf(msg + strlen(msg), ",%d,%s", memHero->taskSaveData.cycleTaskFinishFlag[i], memHero->taskSaveData.cycleTaskId[i]);
		}
	}
	send_msg(getFd(), msg);
}

void Hero::setCycleTaskFinish(char* cycleTaskId)
{
	for (int i = 0; i < 10; i++)
	{
		if (!strcmp(cycleTaskId, memHero->taskSaveData.cycleTaskId[i]))
		{
			memHero->taskSaveData.cycleTaskFinishFlag[i] = 2;
			break;
		}
	}
	
	bool isLoopFinish = true;
	for (int i = 0; i < 10; i++)
	{
		if (memHero->taskSaveData.cycleTaskFinishFlag[i] != 2)
		{
			isLoopFinish = false;
			break;
		}
	}
	
	if (isLoopFinish)
	{
		clearLastLoopTask();			//防bug：防止配置没有下一等级段循环任务
		incCycleTaskLoop();
		freshHeroCycleTask(this);
		updateCycleTaskLevel();
		viewCycleTaskInfo();
	}
}

void Hero::clearLastLoopTask()
{
	for (int i = 0; i < 10; i++)
	{
		memHero->taskSaveData.cycleTaskFinishFlag[i] = 0;
		memset(memHero->taskSaveData.cycleTaskId[i], 0, sizeof memHero->taskSaveData.cycleTaskId[i]);
	}
}
	
void Hero::setOneCycleTask(int index, char* newTaskId)
{
	// memset(memHero->taskSaveData.cycleTaskId[index], 0, sizeof memHero->taskSaveData.cycleTaskId[index]);
	memHero->taskSaveData.cycleTaskFinishFlag[index] = 0;
	strncpy(memHero->taskSaveData.cycleTaskId[index], newTaskId, sizeof memHero->taskSaveData.cycleTaskId[index]);
}

void Hero::incCycleTaskLoop()
{
	memHero->taskSaveData.cycleTaskLoop++;
}

void Hero::initCycleTask()
{
	for (int i = 0; i < 10; i++)
	{
		memHero->taskSaveData.cycleTaskFinishFlag[i] = 0;
		memset(memHero->taskSaveData.cycleTaskId[i], 0, sizeof memHero->taskSaveData.cycleTaskId[i]);
	}
	
	memHero->taskSaveData.cycleTaskLoop = 0;
	memHero->taskSaveData.cycleTaskLevel = (getLevel() / 10) * 10;
}

double Hero::getCycleTaskRewardFactor()
{
	if (getLevel() < BEGIN_CYCLE_TASK_LEVEL)
	{
		return 0.;
	}
	
	map<int, vector<double> >::iterator it = cycleTaskRewardFactor.find(memHero->taskSaveData.cycleTaskLevel);	//谁对这个不满就让他和维亮互爆菊
	if (it == cycleTaskRewardFactor.end())
	{
		return 0.;
	}
	
	vector<double> *pFactor = &it->second;
	if (memHero->taskSaveData.cycleTaskLoop + 1 > pFactor->size())
	{
		return (*pFactor)[pFactor->size() - 1];
	}
	
	return (*pFactor)[memHero->taskSaveData.cycleTaskLoop];
}


int Hero::getTaskFinishFlag(char* cycleTaskId)
{
	for (int i = 0; i < 10; i++)
	{
		if (!strcmp(cycleTaskId, memHero->taskSaveData.cycleTaskId[i]))
		{
			return memHero->taskSaveData.cycleTaskFinishFlag[i];
		}
	}
	
	//玩家本次可接的cycleTask里没这个任务
	return -1;
	
}


void Hero::setCycleTaskAccepted(char* cycleTaskId)
{
	for (int i = 0; i < 10; i++)
	{
		if (!strcmp(cycleTaskId, memHero->taskSaveData.cycleTaskId[i]))
		{
			memHero->taskSaveData.cycleTaskFinishFlag[i] = 1;
			return;
		}
	}
}
