/************************************************************
	文件名：heroCpyRecord.cpp
	文件作用：实现类HeroCpyRecord类的方法
	作者：chenzhen
	创建日期：2012.09.11
************************************************************/

#include"command_other_function_all_over.h"
#include"heroCpyRecord.h"
#include"cpyAsist.h"
#include"cpyLimit.h"
#include"stdlib.h"
#include<iostream>

using namespace std;
extern list<CpyStateFlg> CPYEntState;
extern map<string,CpyLimit*> cpyId_to_cpyLimit;

HeroCpyRecord::HeroCpyRecord(void)
{
	owner = NULL;
	initOlder();
	initAllKindMap();
}

/*缓存赋值*/
HeroCpyRecord::HeroCpyRecord(HeroCpyRecMem _myHeroCpyRecMem)
{
	/*初始化数据<可进入次数>*/
	
	myHeroCpyRecMem = _myHeroCpyRecMem;	

	initRecordDate();
	
	owner = NULL;
}

/*用从缓存中加载的数据来初始化类成员数据*/
bool HeroCpyRecord::initRecordDate(void)
{
	bool entFlg,canFlg,pasFlg,pasSumFlg,entSumFlg,pasGoldFlg,sumGoldFlg,stateFlg;
	
	/*已进入副本map初始化*/
	entFlg = myHeroCpyRecMem.initEntData(cpyEnterCtn);
	
	/*可进入副本map初始化*/
	canFlg =  myHeroCpyRecMem.initCanEntData(cpyCanEntCtn);
	
	/*已通关副本map初始化*/
	pasFlg =  myHeroCpyRecMem.initPassEntData(cpyPassCtn);
	
	/*初始化通关总数*/
	pasSumFlg =  myHeroCpyRecMem.initSumPas(sumCpyPas);
	
	/*初始化所有副本进入次总数*/
	entSumFlg =  myHeroCpyRecMem.initSumEnt(sumCpyEnt);
	
	/*初始化所有已通关副本总分数*/
	sumGoldFlg = myHeroCpyRecMem.initSumGold(sumGold);
	
	/*已通关副本的分数map初始化*/
	pasGoldFlg = myHeroCpyRecMem.initPassGoldData(cpyPassGold);
	
	initOlder();
	
	/*初始化所有副本状态值*/
	stateFlg = myHeroCpyRecMem.initCpyStateFlg(cpyEntState);
	
	if(!entFlg || !canFlg || !pasFlg || !pasSumFlg || !entSumFlg ||\
		!pasGoldFlg || !sumGoldFlg || !stateFlg)
	{
		return false;
	}
	return true;
}

/*下线时调用把成员数据保存在从缓存中*/
bool HeroCpyRecord::storeRecordDate(void)
{
	bool entFlg,canFlg,pasFlg,pasSumFlg,entSumFlg,sumGoldFlg,pasGoldFlg,stateFlg;
	
	/*跟新已进入副本map*/
	entFlg = myHeroCpyRecMem.updateEntCtnVec(cpyEnterCtn);
	
	/*跟新可进入副本map*/
	canFlg =  myHeroCpyRecMem.updateCanEntCtnVec(cpyCanEntCtn);
	
	/*跟新已通关副本map*/
	pasFlg =  myHeroCpyRecMem.upDatePassEntData(cpyPassCtn);
	
	/*跟新通关总数*/
	pasSumFlg =  myHeroCpyRecMem.updateSumPas(sumCpyPas);
	
	/*跟新所有副本进入次总数*/
	entSumFlg =  myHeroCpyRecMem.updateSumEnt(sumCpyEnt);
	
	/*跟新所有通关副本分数map*/
	pasGoldFlg = myHeroCpyRecMem.upDatePassGoldData(cpyPassGold);
	
	/*跟新所有通关副本总分数*/
	sumGoldFlg = myHeroCpyRecMem.updateSumGold(sumGold);
	
	/*跟新所有副本状态值*/
	stateFlg = myHeroCpyRecMem.upDateCpyStateFlg(cpyEntState);
	
	if(!entFlg || !canFlg || !pasFlg || !pasSumFlg || !entSumFlg ||\
	  !pasGoldFlg || !sumGoldFlg || !stateFlg)
	{
		return false;
	}
	return true;
}



Hero* HeroCpyRecord::getOwner(void)
{
	return owner;
}

void HeroCpyRecord::setOwner(Hero *_owner)
{
	if(_owner != NULL)
	{
		owner = _owner;
	}
}

/*增加已通关副本次数函数*/
void HeroCpyRecord::inputPasCtn(char *cpyId)
{
	
	char numStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};
	
	char cpyTypId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	
	map<string,int>::iterator cpyPas_it;
	
	if(cpyId == NULL || strlen(cpyId) == 0)
	{
		
		return;
	}
	
	cpyPas_it = cpyPassCtn.find(cpyId);
	if(cpyPas_it == cpyPassCtn.end())
	{
		cpyPassCtn[cpyId] = 1;
	}
	else
	{
		cpyPas_it->second = cpyPas_it->second + 1 >\
							cpyPas_it->second ?\
							cpyPas_it->second + 1 : cpyPas_it->second;						
	}	
	
	chgState(cpyId); //修复副本通关机制by benliao 2012.11.25 传进来的参数已经是副本类型ID无需转换
}

/*增加已进入副本次数函数*/
void HeroCpyRecord::inputEntCtn(char *cpyId)	
{
	char roomStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};
	char cpyTypId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,int>::iterator cpyEnt_it;
	
	if(cpyId == NULL || strlen(cpyId) == 0)
	{
		cout<<"the cpyId is empty or NULL:"<<endl;
		return;
	}
	
	if(!dealSerNumStr(cpyId,roomStr,cpyTypId))
	{
		cout<<"the cpyId is error:"<<cpyId<<endl;
		return;
	}		
	cpyEnt_it = cpyEnterCtn.find(cpyTypId);
	if(cpyEnt_it == cpyEnterCtn.end())
	{
		cpyEnterCtn[cpyTypId] = 1;
	}
	else
	{
		/*溢出情况也已处理*/
		cpyEnt_it->second = cpyEnt_it->second + 1 >\
							cpyEnt_it->second ?\
							cpyEnt_it->second + 1 : cpyEnt_it->second;			
	}
}

/*析构函数*/
HeroCpyRecord::~HeroCpyRecord(void)
{
	owner = NULL;
	cpyEnterCtn.clear();
	cpyPassCtn.clear();
	cpyCanEntCtn.clear();
}

/*获得所有的进入副本的总次数<记住，并不是每一天的>*/
int HeroCpyRecord::getEntSum(void)
{
	int sum;
	sum = 0;
	map<string,int>::iterator ent_it;
	for(ent_it = cpyEnterCtn.begin();ent_it != cpyEnterCtn.end();ent_it++)
	{
		sum += ent_it->second;
	}
	sumCpyEnt = sumCpyEnt + sum > sumCpyEnt ? sumCpyEnt + sum : sumCpyEnt;
	return sumCpyEnt;
}

/*获得所有的通关副本的总次数<记住，并不是每一天的>*/
int HeroCpyRecord::getPasSum(void)
{
	int sum;
	sum = 0;
	map<string,int>::iterator pas_it;
	for(pas_it = cpyPassCtn.begin();pas_it != cpyPassCtn.end();++pas_it)
	{
		sum += pas_it->second;
	}
	sumCpyPas = sumCpyPas + sum > sumCpyPas ? sumCpyPas + sum : sumCpyPas;
	return sumCpyPas;
}

/*判断是否可以进入下个等级的副本*/
bool HeroCpyRecord::judUperRank(char *cpyId)
{
	return judUperRankAsist(cpyId);
}


/*判断是否可以进入下个等级的副本*/
bool HeroCpyRecord::judUperRankAsist(char *cpyId)
{
	char numStr[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};	
	char lastStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};	

	
	/*处理房间号*/
	if(!dealSerNumStr(cpyId,numStr,lastStr))
	{
		cout<<"the cpyId is woring:"<<cpyId<<endl;
		return false;
	}
	
	return judgeCanEnt(lastStr);
}

/*发送所有副本状态值*/
void HeroCpyRecord::sendEntMsg(void)
{
	
	char  MsgCpyEnt[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	list<CpyStateFlg>::iterator cpyEnt_it;
	int state;	
	
	if(cpyEntState.empty())
	{
		cout<<"it is empty:"<<endl;
		return;
	}
	
	snprintf(MsgCpyEnt + strlen(MsgCpyEnt),sizeof(MsgCpyEnt) - strlen(MsgCpyEnt),"%d%s%d",1,",",4);
	
	for(cpyEnt_it = cpyEntState.begin();cpyEnt_it != cpyEntState.end();++cpyEnt_it)
	{
		snprintf(MsgCpyEnt + strlen(MsgCpyEnt),sizeof(MsgCpyEnt) - strlen(MsgCpyEnt),"%s%s%s%d",\
				",",cpyEnt_it->cpyTpeId,",",cpyEnt_it->flg);
	}
	
	if(owner != NULL)
	{
		send_msg(owner->getFd(),MsgCpyEnt);
		cout << "MsgCpyEnt:" << MsgCpyEnt << endl;
	}
}

/*获得每种副本的状态*/
int HeroCpyRecord::judgeState(int ent,int can)
{
	if(ent == 0)
	{
		return FIRES;
	}
	else if(ent < can  && ent > 0 && can == VipEntTotal)
	{
		return GLOAD;
	}
	else if(ent < can  && ent > 0)
	{
		return FIRES;
	}
	else if(ent == can)
	{
		return BLACK;
	}
	else
	{
		return 4;     //出错处理
	}
}
	
/*返回缓存内容*/
HeroCpyRecMem HeroCpyRecord::getMyHeroRecMem(void)
{
	storeRecordDate();	
	return myHeroCpyRecMem;
}
	
/*获得所有的通关副本的总分数<记住，并不是每一天的>*/
int HeroCpyRecord::getPasGoldSum(void)
{
	int sum;
	sum = 0;
	map<string,int>::iterator gold_it;
	for(gold_it = cpyPassGold.begin();gold_it != cpyPassGold.end();++gold_it)
	{
		sum += gold_it->second;
	}
	sumGold = sumGold + sum > sumGold ? sumGold + sum : sumGold;
	return sumGold;	
}

/*增加已通关副本次数和分数函数*/
void HeroCpyRecord::inputPasGold(char *cpyId,int gold)
{
	map<string,int>::iterator gold_it;
	
	if(cpyId == NULL || strlen(cpyId) == 0)
	{
		return;
	}
	
	gold_it = cpyPassGold.find(cpyId);
	if(gold_it == cpyPassGold.end())
	{
		cpyPassGold[cpyId] = gold;
	}
	else
	{
		gold_it->second = gold_it->second + gold >\
							gold_it->second ?\
							gold_it->second + gold : gold_it->second;
	}
}

/*初始化副本状态值*/		
void HeroCpyRecord::initOlder(void)
{
	 cpyEntState = CPYEntState;
}

/*测试副本状态值*/
void HeroCpyRecord::testOlder(void)
{
	cout<<" test older begin:"<<endl;
	list<CpyStateFlg>::iterator state_it;
	for(state_it = cpyEntState.begin() ; state_it != cpyEntState.end(); ++state_it)
	{
		cout<<"cpyId:"<<state_it->cpyTpeId<<endl;
		cout<<"state:"<<state_it->flg<<endl;	
	}
	cout<<" test older end:"<<endl;
}

/*通关后调用*/
bool HeroCpyRecord::chgState(char *cpyId)
{	
	char msg_pas[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	list<CpyStateFlg>::iterator state_it,chg_it;
	if(cpyId == NULL || strlen(cpyId) == 0)
	{
		cout<<"cpyId is error :"<<endl;
		return false;
	}
	
	sprintf(msg_pas + strlen(msg_pas),"%d%s%d",1,",",4);
	
	for(state_it = cpyEntState.begin() ; state_it != cpyEntState.end(); ++state_it)
	{
	
		if(strcmp(state_it->cpyTpeId,cpyId) == 0)
		{
			cout<<"@@Tory have found tower_defence EnterState"<<endl;
			chg_it = ++state_it;
			if (owner != NULL)
			{
				owner->updateHeroTaskStatus(PASS_ECTYPE_TASK_NEED_TYPE, cpyId);
				owner->clrTskStSomeBit(TASK_NEED_PASS_ECTYPE);
			}


 			if(chg_it == cpyEntState.end() || chg_it->flg == 1)
			{
				cout<<"have open the enter flag"<<endl;
				return false;
			} 
			
			chg_it->flg = 1;

			sprintf(msg_pas + strlen(msg_pas),"%s%s%s%d",",",chg_it->cpyTpeId,",",chg_it->flg);
			
			if(owner != NULL)
			{
				send_msg(owner->getFd(),msg_pas);
			}
			return true;				
		}
	}
	return false;
}


/*判断副本是否可进*/
bool HeroCpyRecord::judgeCanEnt(char *cpyId)
{
	list<CpyStateFlg>::iterator state_it;
	
	if(cpyId == NULL || strlen(cpyId) == 0 || cpyEntState.empty())
	{
		return false;
	}
	
	for(state_it = cpyEntState.begin() ; state_it != cpyEntState.end(); ++state_it)
	{
		if(strcmp(state_it->cpyTpeId,cpyId) == 0)
		{
			if(state_it->flg == 1)
			{
				return true;
			}
			return false;
		}
	}
	return false;
}		


/*初始化副本里面的数据*/		
void HeroCpyRecord::initAllKindMap(void)
{
	map<string,CpyLimit*>::iterator cpy_it;
	for(cpy_it = cpyId_to_cpyLimit.begin();cpy_it != cpyId_to_cpyLimit.end();++cpy_it)
	{
		cpyEnterCtn[cpy_it->first] = 0;
		cpyPassCtn[cpy_it->first] = 0;
		cpyPassGold[cpy_it->first] = 0;
		cpyCanEntCtn[cpy_it->first] = 0;
	}
}

/*判断某副本是否已通关，副本类型id，不带难度*/
bool HeroCpyRecord::isPassCpy(char *cpyId)
{
	
	map<string,int>::iterator cpyPas_it;
	
	if(cpyId == NULL || strlen(cpyId) == 0)
	{		
		return false;
	}
	
	cpyPas_it = cpyPassCtn.find(cpyId);
	if(cpyPas_it == cpyPassCtn.end())
	{
		return false;
	}
	if(cpyPas_it->second < 1)
	{
		return false;
	}
	return true;
}

/*开启所有副本*/
void HeroCpyRecord::GMPassAll(void)
{
	list<CpyStateFlg>::iterator state_it;
	for(state_it = cpyEntState.begin() ; state_it != cpyEntState.end(); ++state_it)
	{
		state_it->flg = 1;	
	}
	sendEntMsg();
}
