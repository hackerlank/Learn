#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <assert.h>
#include "TD_Instancing.h"
#include"cpyLimit.h"
// #include "towerDefTeamAsist.h"
#include "instancing_manage.h"
#include "monsterTowerDefence.h"
//引用全局变量声明，Hero ID索引Hero对象指针的map容器，管理所有已初始化的Hero对象
extern map<string, Hero *> heroId_to_pHero;

//等级查找副本奖励信息
extern map<int, Ectype_Reward_Info *> level_2_rewardInfo;

//塔防副本和桃园断后副本管理容器
extern Instancing_manage *Inst_MNG;

//普通副本管理容器
extern map<string,CpyLimit*> cpyId_to_cpyLimit;

/*
* author:tory
* date:2012.11.30
* des:创建塔防实例空数据，但会实例化房间号
*/
TD_Instancing::TD_Instancing(int _roomNum)
{
    td_inst_id =  "008_0_";
    td_inst_id += int2str(_roomNum, 4);     //将roomNum转成4位字符串，不够4位前面填0
    roomNum = _roomNum;

    timer = new ev_timer;

    mapNow = NULL;
    rewardSet = NULL;       //开始时没有副本奖励信息
    // currTeam  = NULL;

    // singleHero = NULL;  // add 2012.12.18
    // team = NULL;
}

/*
* author:xhm
* date:	2012.11.21
* des:	重置塔防副本数据，delete塔防地图，但保留房间号和定时器监听
*/
bool TD_Instancing::reset()
{
    record.data_reset();
    record.rotate_count = 0;
    record.time_gap_sum = strategy.time_gap[0];
	
	mon_vec.clear();
	cout << "@@Tory:reset mon_vec.size():" << mon_vec.size() << endl;
	 
    currMonster.clear();
    cout << "@@Tory:reset currMonster.size():" << currMonster.size() << endl;

    monster_store.clear();
    cout << "@@Tory:reset monster_store.size():" << monster_store.size() << endl;
    /*清零该对象时需释放的数据*/
    delete(mapNow);
    mapNow = NULL;

	//如果已领取奖励，需释放空间
	if(rewardSet != NULL)
	{
		delete rewardSet;
		rewardSet = NULL; //tory_add 2013.1.24
		cout<<"have delete rewardSet"<<endl;
	}
	
	heroPtr_vec.clear();	//清空当前副本的玩家集合，无需释放空间swap
	isSingleChall = true;	//初始化为单人挑战模式
    return true;
}

/*
* author:tory
* date:	2012.11.30
* des:	按塔防配置和塔防副本指定的地图重置塔防实例，原来房间号和定时器监听保持的不变
*/
bool TD_Instancing::loadNewInstance(const TD_Conf_T& tdConf, Map_Cpy *_mapNow)
{
    //重置塔防副本玩法配置
    infor = tdConf.infor;
    require = tdConf.require;
    strategy = tdConf.strategy;

    mapNow = _mapNow;;
    mapNow->getAllMonObj(monster_store); //获取所有怪物的指针对象
    mapNow->getMonObj(mon_vec);         //tory add 获取每批次要刷出的怪
	int number = 0;
	int i = 0;
	for(i; i < mon_vec.size(); i++)
	{
		number += mon_vec[i].size();	
	}
	cout<<"@@Tory:total number:"<<number<<endl;
	cout<<"@@Tory:monster_store.size():"<<monster_store.size()<<endl;
	//检查刷怪容器中的怪物数目和地图中怪物的总数目是否相等 
	if (number != monster_store.size())	//check config file is right?
    {
		cout<<"@@Tory:monster_store number is error"<<endl;
        mon_vec.clear();
        monster_store.clear();
        return false;
    } 
	// 刷怪时间间隔和刷怪批次是否相等
	if(mon_vec.size() != strategy.time_gap.size())
	{
		cout<<"@@Tory: strategy.time_gap.size() is error"<<endl;
		mon_vec.clear();
        monster_store.clear();
        return false;
	}
    mapNow->setTd_roomid(td_inst_id);   //设置当前地图所属副本Id

	record.rotate_count = 0;
    record.time_gap_sum = strategy.time_gap[0];	
    rewardSet = NULL;       //开始时没有副本奖励信息
	isSingleChall = true;	//默认为单人挑战模式
    return true;
}

//得到塔防副本的实例id(将废弃) 2012.12.25
string TD_Instancing::get_instancing_id()
{
    return td_inst_id;
}

//得到塔防副本的类型id
string TD_Instancing::get_instancing_confId()
{
    return infor.id;
}

Instancing_strategy TD_Instancing::getInstancing_strategy(void)
{
    return strategy;
}
//获得塔防进入限制要求
Instancing_require TD_Instancing::getInstancing_require(void)
{
    return require;
}

/*
* author:tory
* date:	2012.8.20
* des:	修改heroWillEnter中的位置数据：mapId, Map_Inform*,location
*/
void TD_Instancing::setHeroLocation(Hero *heroWillEnt, int _index)
{
    if (NULL == heroWillEnt) return;

    heroWillEnt->setMap(mapNow);
    heroWillEnt->setMapId(mapNow->getMapId());

    switch (_index)
    {
    case 0:
        heroWillEnt->setLocation(strategy.stand_point[0]);
        break;
    case 1:
        heroWillEnt->setLocation(strategy.stand_point[1]);
        break;
    case 2:
        heroWillEnt->setLocation(strategy.stand_point[2]);
        break;
    case 3:
        heroWillEnt->setLocation(strategy.stand_point[3]);
        break;
    default:                                                                    //默认的出生点在区域一;
        heroWillEnt->setLocation(strategy.stand_point[0]);
        break;
    }
}
/*
* author:tory
* date:	2012.8.20
* des:	斗气值满后，队长启动系统攻击，使怪物掉血，并同步给队员在客户端得到渲染
*/
void TD_Instancing::start_systerm_attack(vector<Hero *> team_unit)
{


}

TD_Instancing::~TD_Instancing()
{

}

int TD_Instancing::response(void)
{
    //副本思考轮询次数自增,(由于int值存在最大上限，暂时规定该副本需在一个小时内完成)
    record.poll_count++;
//	cout << "@@Tory 10000000 lose_count:" << record.lose_count << endl;
    if (record.lose_count >= ALL_MAX_LOSE)  
    {
		cout << "TEST XHM FROM THE RESPONSE1 poll_count:" << record.poll_count << endl;
 		char msg[1024] = {0};
		sprintf(msg, "6,12,%d,%d,%d", record.rotate_count, 1000, 1000);	//tory_unfinish
		
		for (vector<Hero*>::iterator memIter = heroPtr_vec.begin(); memIter != heroPtr_vec.end(); memIter++)
		{
			Hero *myHero = *memIter;
			if (myHero == NULL) 
				continue;
			else
				send_msg(myHero->getFd(), msg);
		}		

		/* 停止所有屏幕上正在移动的怪物定时器 */
		for (list<MonsterBase *>::iterator iter = currMonster.begin(); iter != currMonster.end(); iter++)
		{
            (*iter)->StandStill();
        }
        currMonster.clear();
        cout << "@@Tory currMonster.size():" << currMonster.size() << endl;		
        return 1;
    } else if (record.lose_count < ALL_MAX_LOSE) /*漏掉的怪物数目小于指定数目*/
    {
		// cout << "@@Tory record.lose_count:" << record.lose_count<<" record.help_val:"<<record.help_val<<" record.monster_disappear:"<<record.monster_disappear<<endl;
        //怪物已全部刷出且从客户端消亡掉,则副本通关成功
        if (record.monster_disappear >= monster_store.size())
        {
            // 	cout << "TEST XHM FROM THE RESPONSE2 poll_count:" << record.poll_count << endl;
        	cout << "@@Tory start rewardSet" << endl;							
			int min_cost = record.poll_count/60;
			int mark = 100-min_cost-record.lose_count*20;		//计算得分
				
			char result[1024] = { 0 };
			sprintf(result, ",%d", (int)heroPtr_vec.size());
			vector<string> hero_unit;
			CpyLimit* limitInst = getLimitInst(infor.id.c_str());
			size_t costFatigue = 5; 
			if(limitInst)
			{
				costFatigue = limitInst->getCostFatigue();
			}
			
			for (vector<Hero*>::iterator memIter = heroPtr_vec.begin(); memIter != heroPtr_vec.end(); memIter++)
			{
				Hero *myHero = *memIter;
				if (myHero == NULL) 
					continue;
				else
				{
					sprintf(result + strlen(result), ",%s,%s,%d,%d,%d", myHero->getIdentity(), myHero->getNickName(),\
																	record.poll_count, myHero->getCpyRevTme(), mark);    
					hero_unit.push_back(myHero->getIdentity());
					
					myHero->memHero->lastStrength -= costFatigue;		
					if(myHero->memHero->lastStrength < 0)
					{
						myHero->memHero->lastStrength = 0;			
					}
					char fatigueMsg[200] = {'\0'};
					sprintf(fatigueMsg,"8,12,%s,%d,%d",myHero->getIdentity(),myHero->memHero->lastStrength,\
					myHero->memHero->fatigueUpperVal);
		
					send_msg(myHero->getFd(),fatigueMsg);
				}				
			}	
			cout << "@@Tory team the result:" << result << endl;
			// rewardSet = new EctypeRewardSet("010", infor.degree, hero_unit, result, record.lose_count);	
			rewardSet = helpNewEctypeReward(const_cast<char*>(infor.id.c_str()), hero_unit, result, record.lose_count);

			//对于中等以上难度，单人挑战时将更新角色的副本通关记录
			if(isSingleChall == true && heroPtr_vec.size() == 1)
			{
				if(infor.id.compare("008_1") == 0 || infor.id.compare("008_2") == 0)	
				{
					char temp[50] = {0};			//传入副本ID：010
					strncpy(temp, infor.id.c_str(), 3);
					cout<<"@@Tory temp:"<<temp<<endl;
					vector<Hero*>::iterator memIter = heroPtr_vec.begin();
					if(memIter != heroPtr_vec.end())
					{
						Hero *myHero = *memIter;
						if(myHero != NULL)
						{
							myHero->getCpyRecord()->inputPasCtn(temp);
						}
					}			
				}
			}	
            
			return 2;
        } else
        {
            //是否处在怪物批次刷出的间隔时间
            if (record.time_gap_sum == 0)
            {
                if (record.rotate_count <= mon_vec.size() && record.poll_count % 2 == 0)   //检查怪物批次是否越界
                {
                    vector<string> vec = mon_vec[record.rotate_count-1];	//modify 2012.12.26 
                    if (record.monster_count < vec.size())      //刷怪状态
                    {
                        string mon_id = vec[record.monster_count];
                        MonsterBase *monster_show = mapNow->getMonsterObj(mon_id);
                        if (monster_show != NULL)
                        {
                            monster_show->brushMon();                                           //启动怪物的思考，并让其在地图上表现出来
							// monster_show->setLifeStation(LIVE);									//add by chenzhen 20130109
							monster_show->setLifeStation(true);	                                //修改生死状态
                            currMonster.push_front(monster_show);                               //在客户端表现出来的怪
                            AddSelfInstancingStatus(INST_STATUS_MONSTER_COUNT);                 //本批次已刷出数目自增
                            record.cur_live_count++;
                        }
                    } else	//本批次怪已刷完，进入刷怪间隔时间
                    {
						if(record.rotate_count < mon_vec.size())
						{
							record.time_gap_sum = strategy.time_gap[record.rotate_count];
						}else if(record.rotate_count == mon_vec.size()){							
							record.time_gap_sum = 0;
							record.rotate_count = mon_vec.size()+1;
						}						
                    }
                }
            } else
            {	
                record.time_gap_sum -= 1;   //怪物刷出批次间隔时间自减
                if (record.time_gap_sum < 0)
                {
                    record.time_gap_sum = 0;
                }
				
                /* 向客户端发送下一批次怪物刷出的倒计时间 */
                if (record.time_gap_sum <= strategy.time_gap[record.rotate_count] - 5)
                {
                    char msg2Send[1024] = { 0 };
                    sprintf(msg2Send, "%d,%d,%d,%d", 6, 11, record.rotate_count+1, record.time_gap_sum);
                    sendMsgInTower(msg2Send);
                }

				/* 修改怪物刷出批次 */
                if (record.time_gap_sum == 0)
                { 
                    record.monster_count = 0;   //清零本批次已刷出的怪物数目
                    AddSelfInstancingStatus(INST_STATUS_ROTATE_COUNT);      //怪物批次加1
                }
            }
            return 0;
        }
    }

}

/*
* author：	Tory	
* date:		2012.8.15
* description：用于所有的塔防副本注册的poll事件，当libev的定时器到期后，
*              通过此函数决定执行哪一个副本的response
*/
void inst_poll_callback(struct ev_loop *loop, ev_timer *think, int revents)
{
    TD_Instancing *tow_def = (TD_Instancing *)think->target;
    if (tow_def == NULL)	return;

    int ret = tow_def->response();
    if (ret == 1)
    {
        cout << "Warring(tower_def_instancting.cpp):(inst_poll_callback)::the towerdef fighter FAILUE" << endl;

        //	TowerDefWarEnd(tow_def->getCurrTeam(),ret);	//使队伍退出副本
        return;
    } else if (ret == 2)
    {
        cout << "Warring(tower_def_instancting.cpp):(inst_poll_callback)::the towerdef fighter SUCCSESS" << endl;

        //	TowerDefWarEnd(tow_def->getCurrTeam(),ret);	//使队伍退出副本
        return;
    } else if (ret == 0)      //副本定时器继续工作
    {
        ev_timer_start(loop, think);
    }
}

//获得副本奖励集合的对外接口
EctypeRewardSet* TD_Instancing::getRewardSet(void)
{
    return rewardSet;
}

/*
* author：	Tory	
* date:		2012.9.2
* description：通过传入不同的tower_def_instancing.h中定义的宏，获得相应的记录表中的值
*/
int  TD_Instancing::getInstancingStatus(DATA_CHOICE_INT data_choice)
{
    switch (data_choice)
    {
    case INST_STATUS_POLL_COUNT:
        return TD_Instancing::record.poll_count; //轮询次数
        break;
    case INST_STATUS_LOSE_COUNT:
        return TD_Instancing::record.lose_count; //顺利跑到终点怪物增加；
        break;
    case INST_STATUS_MONSTER_COUNT:             //已经刷出怪物个数；
        return TD_Instancing::record.monster_count;
        break;
    case INST_STATUS_MONSTER_DISAPPEAR:         //消失的怪物数目（走到终点+死亡）
        return TD_Instancing::record.monster_disappear;
        break;
    case INST_STATUS_ROTATE_COUNT:              //当前怪物批次；
        return TD_Instancing::record.rotate_count;
        break;
    case INST_STATUS_CUR_LIVE_COUNT:            //当前存活的怪物数目
        return TD_Instancing::record.cur_live_count;
        break;
    case INST_STATUS_HELP_VAL:
        return TD_Instancing::record.help_val;  //击杀怪物数目（斗气值）
        break;
    default:
        return -1;
        break;
    }

}

/*
* author：	Tory	
* date:		2012.9.2
* description：通过传入不同的tower_def_instancing.h中定义的宏，对副本记录表中相应的值加1
*/
bool TD_Instancing::AddSelfInstancingStatus(DATA_CHOICE_INT data_choice)
{
    bool sendMsgFlag = false;
    char msg2Send[1024] = { 0 };
    switch (data_choice)
    {
    case INST_STATUS_POLL_COUNT:    //轮询次数
        record.poll_count++;
		sendMsgFlag = true;
        break;
    case INST_STATUS_LOSE_COUNT:
        record.lose_count++;        //顺利跑到终点怪物增加；
        record.monster_disappear++; //顺利跑到终点相当于消失；
        if (currMonster.size()) 
		{
			currMonster.pop_back();
		}
        sendMsgFlag = true;
        break;
    case INST_STATUS_MONSTER_COUNT:
        record.monster_count++;     //已经刷出怪物个数；
        sendMsgFlag = true;
        break;
    case INST_STATUS_MONSTER_DISAPPEAR:
        record.monster_disappear++; //消失的怪物数目（走到终点+死亡）
        if (currMonster.size()) 
		{
			currMonster.pop_back();
        }
        sendMsgFlag = true;
		break;
    case INST_STATUS_ROTATE_COUNT:
        record.rotate_count++;      //当前怪物批次；
        sendMsgFlag = true;
        break;
    case INST_STATUS_CUR_LIVE_COUNT: //当前存活的怪物数目
        record.cur_live_count++;

        break;
    case INST_STATUS_HELP_VAL:
        record.help_val++;      //击杀怪物数目（斗气值）
        sendMsgFlag = true;
        break;
    default:
        return false;
        break;
    }

	cout << "@@Tory record.lose_count:" << record.lose_count<<"+"<<record.help_val<<" ="<<record.monster_disappear<<endl;
	
	if (sendMsgFlag && record.lose_count < ALL_MAX_LOSE+1)
	{
		if(record.rotate_count == mon_vec.size() + 1)
		{
			record.rotate_count -= 1;
		}
		
			
		if(record.rotate_count == 0)
		{
			sprintf(msg2Send, "7,28,%d,%d,%d,%d,%d,%d,%d,%d", record.monster_count,mon_vec[0].size(),0,mon_vec.size(),0,\
															ALL_MAX_LOSE, record.help_val, monster_store.size());
		}else if(record.rotate_count <= mon_vec.size())    //更新客户端的怪物刷出信息
		{		
			sprintf(msg2Send, "7,28,%d,%d,%d,%d,%d,%d,%d,%d", record.monster_count, mon_vec[record.rotate_count-1].size(), record.rotate_count,\
															mon_vec.size(), record.lose_count, ALL_MAX_LOSE, record.help_val, monster_store.size());

		}
		sendMsgInTower(msg2Send);
	}	

}

/*
* author：	tory	
* date:		2012.12.17
* describe: 停止副本活动的怪物定时器
*/
void TD_Instancing::stopMonThk()
{
    for (list<MonsterBase *>::iterator iter = currMonster.begin(); iter != currMonster.end(); iter++)
    {
        (*iter)->StandStill();
    }
}
/*
* author：	tory	
* date:		2012.12.25
* describe: 向在塔防副本中的所有角色广播消息
*/
void TD_Instancing::sendMsgInTower(char *msg2Send)
{
	if (strlen(msg2Send) == 0)
	{	
		return;
	}
	
	for (vector<Hero*>::iterator memIter = heroPtr_vec.begin(); memIter != heroPtr_vec.end(); memIter++)
	{
		Hero *myHero = *memIter;
		if (myHero != NULL) 
		{
			send_msg(myHero->getFd(), msg2Send);
		}
	}	
}

CpyLimit* getLimitInst(const char* cpyType)
{
	if(!cpyType)
	{
		cout<<"CpyLimit* getLimitInst cpyType is NULL:"<<endl;
		return NULL;
	}
	
	map<string,CpyLimit*>::iterator cpyLimt_it = cpyId_to_cpyLimit.find(cpyType);
	if(cpyLimt_it == cpyId_to_cpyLimit.end())
	{
		cout<<"CpyLimit* getLimitInst(const char* cpyType) the cpyType is error :"<<cpyType<<endl;
		return NULL;
	}
	return cpyLimt_it->second;
}