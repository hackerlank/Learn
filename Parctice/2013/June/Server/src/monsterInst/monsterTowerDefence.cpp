/********************************************************************
* author: 	Tory
* date	:	2012/8/21  
* Description:塔防副本怪物，继承于怪物基类 
*********************************************************************/
#include<math.h>
#include <assert.h>
#include "monsterTowerDefence.h"
// #include "towerDefTeamAsist.h"
extern int Rd;
extern Instancing_manage *Inst_MNG;
extern map<string, Hero *> heroId_to_pHero;

//构造函数
monsterTowerDefence::monsterTowerDefence(char *_mapId,char *_typeId,char *_nickName,char *_identity, char *_type,char *_kind, int _experience, double _cdTime,int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,int _getHrtSud, int _outHrt,int _inHrt, int _outAttVal, int _inAttVal,int _outDefVal,int _inDefVal,int _defSumVal,double _hit, double _crit,int _voids,int _tenacity,int _moveRange,int _hatRange,int _attRange,int _failGoodsless, int _failGoodsmost,int _hatVal,int _gold,set<string>& _failId, Point _pt,int _rank,int _speed, int _fiveEleInt,int _fiveHurt,int _fiveRank,int _forGo,int _expTme,int _monyTme,char *_stage,char *_photoId,vector<string> &skiIdSet,char *_genAttId, double _angVal,int _ownerAttriType,char* _ownerAttri,double _attackRatio,bool _isInnerAttack,LveCtnManger _lveCtnMager)	
		 :MonsterBase(_mapId,_typeId,_nickName,_identity,_type,_kind,_experience,_cdTime,_lifeUpperVal,_lifeVal, _magicUpperVal,_magicVal, _getHrtSud,_outHrt,_inHrt, _outAttVal, _inAttVal, _outDefVal,_inDefVal,_defSumVal, _hit,_crit,_voids,_tenacity, _moveRange, _hatRange,_attRange,_failGoodsless,_failGoodsmost, _hatVal,_gold,_failId,_pt,_rank,_speed,_fiveEleInt,_fiveHurt,                _fiveRank,_forGo,_expTme,_monyTme,_stage,_photoId,skiIdSet,_genAttId,_angVal,_ownerAttriType,_ownerAttri,_attackRatio,_isInnerAttack,_lveCtnMager),\
		diedNoThink(false), count4route(0), cur_position(0), forSelf(0), flgRec(false), state(new StopState()) 
 		{
 			//为塔防怪初始化移动路径(暂时全部用基本难度的怪物路径) 
			map<string, TD_Conf_T>::iterator iter_tdConf = id_2_tdConf.begin();//塔防配置文件的检测已在塔防管理类初始化的时候检测通过 tory 2013.1.11
			TD_Conf_T tdConf = iter_tdConf->second;
			td_strategy = tdConf.strategy;

			char monster_route[2] = { 0 };
			monster_route[0] = identity[strlen(identity) - 1];
			monster_route[1] = '\0';
			if(atoi(monster_route) % 2 == 0)
				route = td_strategy.route_left;
			else
				route = td_strategy.route_right; 	
		}	 
		
monsterTowerDefence::~monsterTowerDefence(void)
{

}

//地图怪物拷贝函数
MonsterBase* monsterTowerDefence::copyMon(char *_mapId)
{
    MonsterBase *newMon;
    char newIntId[100] = {0};     //怪物在新地图上的id
	
	if(_mapId == NULL)	return NULL;
	
    //追加地图id，为了保证副本怪物id的唯一性
	strncpy(newIntId,_mapId,strlen(_mapId));
	strncat(newIntId,"_",strlen("_"));
	strncat(newIntId,identity,strlen(identity));

    vector<string> skiIdSet;
    getSkiIdSet(skiIdSet);

    newMon = new monsterTowerDefence(_mapId, typeId,nickName, newIntId,type, kind, experience, cdTime, lifeUpperVal,\
	lifeVal, magicUpperVal,magicVal, hrtSud, outHrt, inHrt, outAttVal, inAttVal,outDefVal, inDefVal, defSumVal, hit,\
	crit, voids, tenacity,walk_ranage, hatRge, attack_range, failGoodsLess, failGoodsMost,hatVal, gold, failList, pt,\
	rank, speed, fiveEleInt, fiveHurt,fiveEleRank, forGo, expTme, monyTme,stage,photoId, skiIdSet, genAttId,\
	angVal,ownerAttriType,ownerAttri,attackRatio,isInnerAttack,lveCtnMager);
	reStart=0;
	newMon->setIsCallType(isCallType);
    return newMon;
}

/*
* author: 	Tory
* date	:	2012/8/21  
* Description:在怪物受到玩家攻击的情况下，考虑是否将该玩家加入进怪物的仇恨列表，
* 判定条件如下：
* 1、怪物的攻击范围等于仇恨范围的情况下（可对角色进行攻击）
* 2、当前玩家吸引的怪物数目是否小于配置文件指定的数目
*/
void monsterTowerDefence::InpushEnmityValues(HatVal& hatva)
{
    string des_heroId = hatva.id;
    map<string, Hero *>::iterator hero_it;
    hero_it = heroId_to_pHero.find(des_heroId);
    if (hero_it == heroId_to_pHero.end())
    {
        cout << "return from monsterTowerDefence::InpushEnmityValues(),cause can't find heroId: " << des_heroId << endl;
        return;
    }
    Hero *in_hero = hero_it->second;            //in_hero--->怪物判定范围之内包含的角色
    int fight_state = attackRangePoint(pt, in_hero->getLocation(), attack_range);
    //    cout<<"attack_range"<<attack_range<<"is_fight_state "<<fight_state<<endl;
    //    cout<<"@@@@ attrcak monster number:"<<in_hero->getAttracMonNum()<<endl;
    if (fight_state == 1)               //怪物的攻击范围等于仇恨范围的情况下，可对角色进行攻击
    {
        if (in_hero->getAttracMonNum() < 3)  //判断当前角色吸引的怪物数目是否小于配置文件指定的数目
        {
            list<HatVal>::iterator enmityValues_it;
            for (enmityValues_it = enmityValues.begin(); enmityValues_it != enmityValues.end(); enmityValues_it++)
            {
                if (strcmp((*enmityValues_it).id, hatva.id) == 0) //当前角色已加入怪物的仇恨列表，本次攻击仅增加仇恨值
                {
                    //    cout<<"20000 is old hateValue is add: "<<hatva.id<<endl;
                    (*enmityValues_it).value += hatva.value;
                    break;
                }
            }
            if (enmityValues_it == enmityValues.end())   //当前角色未加入怪物的仇恨列表，本次攻击将把角色加进怪物的仇恨列表，同时把怪物ID加入角色吸引的怪物ID容器
            {
                //    cout<<"add new hero to hateValue list: "<<hatva.id<<endl;
                enmityValues.push_back(hatva);
                in_hero->addAttracMonId(identity);
                cout << "attrack monster number:" << in_hero->getAttracMonNum() << endl;
            }
            enmityValues.sort(ComFun);

        } /* else
        {
            cout << "in monsterTowerDefence::have attrack 2 monster so not care: " << hatva.id << endl;
            return;
        } */
    }
}


/*
* author: 	Tory
* date	:	2012/8/21  
* describe:怪物思考函数，由定时器的触发，从怪物思考队列中取出将要思考的怪物实例指针，进行回调
*/
void monsterTowerDefence::response(void)
{
	forSelf++;	
	//无敌持续时间处理
    // MonsterBase::unEnemyTme();
    //处理延时性技能
    MonsterBase::hitedSkiFun();
    //地图上没人，则返回
    if (map_now->getFdSze() == 0)	return;
    //判断是否已定身
    if (!MonsterBase::skiBody)     return;   

    //无仇恨列表
    if (enmityValues.empty()){
        monsterTowerDefence::walk();
    }else{	//有仇恨列表
        cout<<"enmityValues isn't empty!"<<endl;
        HatVal *hat_val = MonsterBase::getOneEnmityValues();
        if (hat_val == NULL) return;
        string des_heroId = hat_val->id;
        map<string, Hero *>::iterator hero_it = heroId_to_pHero.find(des_heroId);
        if (hero_it == heroId_to_pHero.end())	 return;
        Hero *in_hero = hero_it->second;
		if(in_hero == NULL) return;
		//判读是否在攻击范围内，fight_state为1，可以攻击，否则不可攻击
        int fight_state = attackRangePoint(pt, in_hero->getLocation(), attack_range);
        if (fight_state != 1){
            //	cout<<"out of hate_range before delete hateValue from list: "<<enmityValues.size()<<endl;
            dropOneEnmityValues(*getOneEnmityValues());
            cout << "out of hate_range after delete hateValue from list: " << enmityValues.size() << endl;
            in_hero->delAttracMonId(identity);
            monsterTowerDefence::walk();
        } else {      //当前怪物仇恨范围内的角色未跑出仇恨范围，则进行攻击
			monsterTowerDefence::attack();
		}	
    }
	//怪物走到终点，停止计时器，发送怪物下线消息，增加漏怪数目
 	if(pt._x == route.back()._x && pt._y == route.back()._y){
		cout<<"pt._x:"<<pt._x<<" pt._y:"<<pt._y<<endl;
		monsterTowerDefence::diedNoThink = true;	
		monsterTowerDefence::stop();
	} 
	
}

/*
* author: 	Tory
* date	:	2012/8/21  
* describe: 向客户端发送怪物移动路径，是怪物向着目标点移动
*/
void monsterTowerDefence::GoStraight()
{
 	if(count4route < route.size()){
		char msg[1024] = {0};
		sprintf(msg, "%d,%d,%s,%d,%d,%d",2, 1, identity, 2, pt._x, pt._y);
	
		Point wayPt = route[count4route];
		sprintf(msg+strlen(msg), ",%d,%d,%d", wayPt._x, wayPt._y, 120);	
				
		StyObj obj(identity,MONSTER_STYLE_TYPE);
		Nbox *box = map_now->getBox();	
		if(box == NULL)	return;
		box->getStaInSrcVec(obj);
		box->sentBoxMsg(msg);
		
	} 
}

/*
* author: 	Tory
* date	:	2012/8/21  
* describe: 攻击处理函数
*/
void monsterTowerDefence::reAttack()
{
	char msg_others[1024] = {0};
    HatVal *hat_val = MonsterBase::getOneEnmityValues();
    if (hat_val == NULL) return;
    string des_heroId = hat_val->id;
    map<string, Hero *>::iterator hero_it = heroId_to_pHero.find(des_heroId);
    if (hero_it == heroId_to_pHero.end())
    {
        cout << "in monsterTower::find hero error!" << endl;
        return;
    }
    Hero *in_hero = hero_it->second;
    MonsterBase::attPerHero(msg_others, sizeof(msg_others), in_hero, false);
    
	StyObj obj(identity,MONSTER_STYLE_TYPE);
	Nbox *box = map_now->getBox();	
	if(box == NULL)	return;
	box->getStaInSrcVec(obj);
	box->sentBoxMsg(msg_others);
}

/*
* author: 	Tory
* date	:	2012/8/21  
* describe: 向客户端发送怪物消失的数据
*/
void monsterTowerDefence::disappear()
{
	char msg[1024] = {0};
	sprintf(msg, "%d,%d,%s,%d",2, 5, identity, 0);
		
	StyObj obj(identity,MONSTER_STYLE_TYPE);
	Nbox *box = map_now->getBox();	
	if(box == NULL)	return;
	box->getStaInSrcVec(obj);
	box->sentBoxMsg(msg);
}

/*
* author: 	Tory
* date	:	2012/8/21  
* describe: 向客户端发送怪物停止移动的命令
*/
void monsterTowerDefence::StandStill()
{
/* 	char msg[1024] = {0};
	sprintf(msg, "%d,%d,%s,%d,%d,%d",2, 1, identity, 1, pt._x, pt._y);
			
	StyObj obj(identity,MONSTER_STYLE_TYPE);
	Nbox *box = map_now->getBox();	
	if(box == NULL)	return;
	box->getStaInSrcVec(obj);
	box->sentBoxMsg(msg); */
	cout<<"@@Tory enforce stop monster think_timer"<<endl;
	ev_timer_stop(loops,&think_timer);
	monsterTowerDefence::diedNoThink = true;
}
/*
* author: 	bison
* date	:	2012/7/4  
* 传入参数：void
* Description: 返回diedNoThink(bool)值,表示怪物是否还需要下一步的思考轮询
*/
bool monsterTowerDefence::getDiedNoThink(void)
{
    return diedNoThink;
}


//怪物死亡函数
void monsterTowerDefence::die(bool flgInit)
{
	MonsterBase::die(flgInit);	
    count4route = 0;
    forSelf = 0;	
	reStart=0;
    flgRec = false;
	isAlive = false;    //chenzhen add 20130109
	//life_station = DEAD;	
}

bool monsterTowerDefence::addTowerDefLostCount()
{

	if(map_now == NULL)
		return false;
		
	string towerDefRoomId = map_now->getTd_roomid();
	if(towerDefRoomId.empty())
		return false;
		
	TD_Instancing * myTD_Instancing = Inst_MNG->id2tdRoom(towerDefRoomId);	
	if(NULL == myTD_Instancing)
		return false;

	myTD_Instancing->AddSelfInstancingStatus(INST_STATUS_LOSE_COUNT);
	
	count4route = 0;

    forSelf = 0;
	
	reStart=0;  
	
	resetRoute();

    flgRec = false;
	
	MonsterBase::die(true);
	
	return true;

}


void monsterTowerDefence::resetRoute()
{
	char monster_route[2] = { 0 };
	monster_route[0] = identity[strlen(identity) - 1];
	monster_route[1] = '\0';
	if(atoi(monster_route) % 2 == 0)
		route = td_strategy.route_left;
	else
		route = td_strategy.route_right; 
	
	cur_position=0;	
	logic_pt._x == route.front()._x;
	logic_pt._y == route.front()._y;
}
