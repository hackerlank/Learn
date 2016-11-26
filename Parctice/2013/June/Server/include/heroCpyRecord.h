/************************************************************
	文件名：heroCpyRecord.h
	文件作用：HeroCpyRecord类的方法和属性的申明
	作者：chenzhen
	创建日期：2012.09.11
************************************************************/
#ifndef HERO_CPY_RECORD_H
#define HERO_CPY_RECORD_H
#include"other_define_data.h"
#include"wholeDefine.h"
#include<iostream>
#include<string.h>
#include<vector>
#include<string>
#include<list>
#include<map>

using namespace std;
const int GLOAD = 1;
const int BLACK = 0;
const int FIRES = 2;
class Hero;


typedef struct CpyStateFlg
{
	char cpyTpeId[LITTLE_MID_VALUE_LENGTH + 1];
	int flg;
	CpyStateFlg(char *_cpyTpeId,int _flg = 0)
	{
		memset(cpyTpeId,'\0',sizeof(cpyTpeId));
		strncpy(cpyTpeId,_cpyTpeId,strlen(_cpyTpeId));
		flg = _flg;
	}
	
	CpyStateFlg(const CpyStateFlg &cpyState)
	{
		memset(cpyTpeId,'\0',sizeof(cpyTpeId));
		strncpy(cpyTpeId,cpyState.cpyTpeId,strlen(cpyState.cpyTpeId));
		flg = cpyState.flg;
	}
	
	CpyStateFlg& operator= (const CpyStateFlg &cpyState)
	{
		memset(cpyTpeId,'\0',sizeof(cpyTpeId));
		strncpy(cpyTpeId,cpyState.cpyTpeId,strlen(cpyState.cpyTpeId));
		flg = cpyState.flg;
		return *this;
	}
		
}CpyStateFlg;

/*副本记录表存mem*/
typedef struct HeroCpyRecMem
{	
	/*已进入次数<按天数>*/
	int entCtn[COPY_SUM_LEVEL];
	
	/*已通过副本次数<累计算>*/
	int passCtn[COPY_SUM_LEVEL];
	
	/*可进入副本次数，每天刷新*/
	int canEntCtn[COPY_SUM_LEVEL];
	
	/*已通过副本次数的分数<累计算>*/
	int passGoldCtn[COPY_SUM_LEVEL]; 
	
	/*副本状态值*/
	int cpyFlg[COPY_SUM_FLG];
	
	int sumPas;                 //所有副本通关总次数
	int sumEnt;                 //所有副本进入总次数
	int goldSum;                //总分数
	HeroCpyRecMem(void)
	{
		sumPas = 0;
		sumEnt = 0;
	}	
	
	/*已进入副本map初始化*/
	bool initEntData(map<string,int> &cpyEnterCtn)
	{
		int length,i;	
		map<string,int>::iterator ent_it;
		
		/*如果缓存取出来的为空*/		
		length = COPY_SUM_LEVEL;
		for(i = 0,ent_it = cpyEnterCtn.begin();ent_it != cpyEnterCtn.end() &&\
			i < length;++ent_it,++i)
		{
			ent_it->second = entCtn[i];
		}
		return true;
	}
	
	/*可进入副本map初始化*/
	bool initCanEntData(map<string,int> &cpyCanEntCtn)
	{	
		int length,i;	
		map<string,int>::iterator canEnt_it;
		
		/*如果缓存取出来的为空*/		
		length = COPY_SUM_LEVEL;
		for(i = 0,canEnt_it = cpyCanEntCtn.begin();canEnt_it != cpyCanEntCtn.end() &&\
			i < length;++canEnt_it,++i)
		{
			canEnt_it->second = canEntCtn[i];
		}
		return true;
	}
			
	/*已通关副本map初始化*/
	bool initPassEntData(map<string,int> &cpyPassCtn)
	{
		int length,i;	
		map<string,int>::iterator passEnt_it;
		
		/*如果缓存取出来的为空*/		
		length = COPY_SUM_LEVEL;
		for(i = 0,passEnt_it = cpyPassCtn.begin();passEnt_it != cpyPassCtn.end() &&\
			i < length;++passEnt_it,++i)
		{
			passEnt_it->second = passCtn[i];
		}
		return true;
	}
	
	/*已通关副本的分数map初始化*/
	bool initPassGoldData(map<string,int> &cpyPassGold)
	{
		int length,i;	
		map<string,int>::iterator passGold_it;
		
		/*如果缓存取出来的为空*/		
		length = COPY_SUM_LEVEL;
		for(i = 0,passGold_it = cpyPassGold.begin();passGold_it !=\
			cpyPassGold.end() && i < length;++passGold_it,++i)
		{
			passGold_it->second = passGoldCtn[i];
		}
		return true;
	}
	
	/*副本的状态初始化*/
	bool initCpyStateFlg(list<CpyStateFlg> &cpyStateFlg)
	{		
		list<CpyStateFlg>::iterator state_it;
		int i,length;
		
		length = COPY_SUM_FLG;
		for(i = 0,state_it = cpyStateFlg.begin();state_it != cpyStateFlg.end() &&\
			i < length;++state_it,++i)
		{
			state_it->flg = cpyFlg[i];
		}
		
		return true;
	}
	/*初始化通关总数*/
	bool initSumPas(int &sumCpyPas)
	{
		sumCpyPas = sumPas;
		return true;
	}
	/*初始化所有副本进入次总数*/
	bool initSumEnt(int &sumCpyEnt)
	{
		sumCpyEnt = sumEnt;
		return true;
	}
	
	/*初始化所有副本总分数*/
	bool initSumGold(int &sumCpyGold)
	{
		sumCpyGold = goldSum;
		return true;
	}
	
	/*更新通关总数*/
	bool updateSumPas(int sumCpyPas)
	{
		sumPas = sumCpyPas;
		return true;
	}
	
	/*更新通关总分数*/
	bool updateSumGold(int sumCpyGold)
	{
		goldSum = sumCpyGold;
		return true;
	}
	
	/*更新所有副本进入次总数*/
	bool updateSumEnt(int sumCpyEnt)
	{
		sumEnt = sumCpyEnt;
		return true;
	}
	
	/*更新canEntCtn的数据*/
	bool updateCanEntCtnVec(map<string,int> &cpyCanEntCtn)
	{
		map<string,int>::iterator canEnt_it;
		int i,length;	
		if(cpyCanEntCtn.empty())
		{
			return false;
		}		
		length = COPY_SUM_LEVEL;
		for(i = 0,canEnt_it = cpyCanEntCtn.begin();canEnt_it != cpyCanEntCtn.end() &&\
			i < length;++canEnt_it,++i)
		{
			canEntCtn[i] = canEnt_it->second;
		}
		
		return true;
	}
	
	/*更新entCtn的数据*/
	bool updateEntCtnVec(map<string,int> &cpyEnterCtn)
	{
		map<string,int>::iterator ent_it;
		int i,length;
		
		if(cpyEnterCtn.empty())
		{
			return false;
		}
		
		length = COPY_SUM_LEVEL;
		for(i = 0,ent_it = cpyEnterCtn.begin();ent_it != cpyEnterCtn.end() &&\
			i < length;++ent_it,++i)
		{
			entCtn[i] = ent_it->second;
		}
		
		return true;
	}
	
	/*更新已通关副本数据*/
	bool upDatePassEntData(map<string,int> &cpyPassCtn)
	{	
		map<string,int>::iterator pass_it;
		int i,length;
		
		if(cpyPassCtn.empty())
		{
			return false;
		}
		
		length = COPY_SUM_LEVEL;
		for(i = 0,pass_it = cpyPassCtn.begin();pass_it != cpyPassCtn.end() &&\
			i < length;++pass_it,++i)
		{
			passCtn[i] = pass_it->second;
		}
		
		return true;
	}
	
	/*更新已通关副本分数数据*/
	bool upDateCpyStateFlg(list<CpyStateFlg> &cpyStateFlg)
	{	
		
		list<CpyStateFlg>::iterator state_it;
		int i,length;
		
		if(cpyStateFlg.empty())
		{
			return false;
		}
		
		length = COPY_SUM_FLG;
		for(i = 0,state_it = cpyStateFlg.begin();state_it != cpyStateFlg.end() &&\
			i < length;++state_it,++i)
		{
			cpyFlg[i] = state_it->flg;
		}
		
		return true;
	}
	
	/*更新副本状态*/
	bool upDatePassGoldData(map<string,int> &cpyPassGold)
	{	
		map<string,int>::iterator gold_it;
		int i,length;
		
		if(cpyPassGold.empty())
		{
			return false;
		}
		
		length = COPY_SUM_LEVEL;
		for(i = 0,gold_it = cpyPassGold.begin();gold_it != cpyPassGold.end() &&\
			i < length;++gold_it,++i)
		{
			passGoldCtn[i] = gold_it->second;
		}
		
		return true;
	}
	
	/*测试已经入容器*/
	void testEntCtn(void)
	{
		int length,i;
		cout<<"test the entCtn container begin:"<<endl;
		length = COPY_SUM_LEVEL;
		for(i = 0; i < length;i++)
		{
			cout<<"the index:"<<i<<" the values:"<<entCtn[i]<<endl;
		}
		cout<<"test the entCtn container end:"<<endl;
	}
	/*测试已通关容器*/
	void testPasCtn(void)
	{
		int length,i;
		cout<<"test the passCtn container begin:"<<endl;
		length = COPY_SUM_LEVEL;
		for(i = 0; i < length;i++)
		{
			cout<<"the index:"<<i<<" the values:"<<passCtn[i]<<endl;
		}
		cout<<"test the passCtn container end:"<<endl;
	}
	/*测试可进入容器*/
	void testCanEntCtn(void)
	{
		int length,i;
		cout<<"test the canEntCtn container begin:"<<endl;
		length = COPY_SUM_LEVEL;
		for(i = 0; i < length;++i)
		{
			cout<<"the index:"<<i<<" the values:"<<canEntCtn[i]<<endl;
		}
		cout<<"test the canEntCtn container end:"<<endl;
	}
	
	void initRecordMem(void)
	{
		// entCtn.empty();
		
		// passCtn.empty();
		
		// canEntCtn.empty();
		
		sumPas = 0;   
		
		sumEnt = 0;  
	}
		
}HeroCpyRecMem;	

class HeroCpyRecord
{
	Hero *owner;       //归主
	map<string,int> cpyEnterCtn;   //每种副本已进入次数
	map<string,int> cpyPassCtn;    //每种副本通关次数
	map<string,int> cpyPassGold;    //每种副本通关分数
	map<string,int> cpyCanEntCtn;  //每种副本可进入次数
	list<CpyStateFlg> cpyEntState;  //每种副本状态
	int sumCpyPas;                 //所有副本通关总次数
	int sumCpyEnt;                 //所有副本进入总次数
	int sumGold;                   //所有副本通关总分数
	
	int canEntTmes;
	int VipEntTotal;          
	
	HeroCpyRecMem myHeroCpyRecMem;     //缓存里面的东西
	
	public:
	
	HeroCpyRecord(void);
	
	HeroCpyRecord(HeroCpyRecMem _myHeroCpyRecMem);
	
	void setOwner(Hero *_owner);
	
	/*增加已通关副本次数函数*/
	void inputPasCtn(char *cpyId);
	
	/*增加已通关副本分数函数*/
	void inputPasGold(char *cpyId,int gold);
	
	/*增加已进入副本次数函数*/
	void inputEntCtn(char *cpyId);
	
	/*析构函数*/
	~HeroCpyRecord(void);

	
	/*重置已通关副本次数*/
	void initPasCtn(void);
	
	
	/*获得所有的进入副本的总次数<记住，并不是每一天的>*/
	int getEntSum(void);
	
	/*获得所有的通关副本的总次数<记住，并不是每一天的>*/
	int getPasSum(void);
	
	/*获得所有的通关副本的总分数<记住，并不是每一天的>*/
	int getPasGoldSum(void);
	
	/*判断是否可以进入下个等级的副本*/
	bool judUperRank(char *cpyId);
	
	/*获得每种副本的状态*/
	int judgeState(int ent,int can);
	
	/*获得寄主*/
	Hero* getOwner(void);
	
	/*用从缓存中加载的数据来初始化类成员数据*/
	bool initRecordDate(void);
	
	/*下线时调用把成员数据保存在从缓存中*/
	bool storeRecordDate(void);
	
	/*返回缓存内容*/
	HeroCpyRecMem getMyHeroRecMem(void);
	
	
	/*判断是否可以进入下个等级的副本*/
	bool judUperRankAsist(char *cpyId);
	
	/*初始化副本状态值*/		
	void initOlder(void);
	
	/*测试副本状态值*/
	void testOlder(void);	
	
	/*通关后调用*/
	bool chgState(char *cpyId);
	
	/*判断副本是否可进*/
	bool judgeCanEnt(char *cpyId);
	
	/*发送所有副本状态值*/
	void sendEntMsg(void);
	
	/*初始化副本里面的数据*/		
	void initAllKindMap(void);
	
	/*判断某副本是否已通关，副本类型id，不带难度*/
	bool isPassCpy(char *cpyId);
	
	/*开启所有副本*/
	void GMPassAll(void);
};
#endif
	
	