/************************************************************
	文件名：cpyLimit.h
	文件作用：定义CpyLimit的属性和函数
	作者：chenzhen
	创建日期：2012.06.11
************************************************************/

#ifndef CPY_LIMIT_H
#define CPY_LIMIT_H
#include<vector>
#include<string>
#include"cpy.h"
#include "instancing_manage.h"

/*在45级和之后的副本，金陵进，否则在开封进*/
const int CPYRANK = 45;

/*进入副本错误提示信息*/

/*此副本没有开启*/
const int ERROR_NO_OPEN = 0; 

/*处于押镖状态*/
const int ERROR_YA_BIAO = 1;

/*处于pk场景*/
const int ERROR_PK = 2;

/*如果是帮派镖，则表示帮派等级不够*/
const int IS_PARTY_LEVE_LOW = 3;

/*在副本中*/
const int ERROR_IN_COPY = 4;

/*没有加入任何帮派*/
const int ERROR_NOT_JOIN_PARTY = 5;

/*单人进副本时，已组队，且不是队长*/
const int ERROR_IN_TEAM = 6;

/*单人进副本时，不在主城或者副本npc附近*/
const int ERROR_IN_MAIN_CITY = 7;

/*单人进副本时，不在对应的主城或者npc附近*/
const int ERROR_IN_JL_NPC = 8;

/*单人进副本时，不在对应的主城或者npc附近*/
const int ERROR_IN_KF_NPC = 9;

/*单人进副本时，处于摆摊状态*/
const int ERROR_IN_SELL = 10;

/*单人进副本时，处于摆摊状态*/
const int ERROR_OTHER = 11;

/*进任务副本时，而非单人*/
const int ERROR_NOT_ONE_PERSON = 12;

/*进副本角色等级不够*/
const int ERROR_LOWER_RANK = 14;

/*进副本角色耐力值不够*/
const int ERROR_LOWER_LAST_POWER = 13;


/*进入黑木崖副本塔没有开启*/
const int TOWER_LAYER_COPY_TOWER_CLOSED = 15;

/*进入黑木崖副本层没有开启*/
const int TOWER_LAYER_COPY_LAYER_CLOSED = 16;

/*进入黑木崖副本塔错误*/
const int TOWER_LAYER_COPY_TOWER_ERROR = 17;

/*进入黑木崖副本层错误*/
const int TOWER_LAYER_COPY_LAYER_ERROR = 18;

/*进入黑木崖副本ID错误*/
const int TOWER_LAYER_COPY_COPY_ERROR = 19;

/*娱乐地图*/
const int ERROR_IN_HAPPY = 20;

using namespace std;

typedef struct CpyMemRecord
{
	char nickName[HERO_MAME_LEN + 1];	//名字；
	char party[PARTY_LEN];				//门派；
	char heroId[HEROID_LENGTH + 1];  	//id
	char guildName[101];                //帮派名称
	int grad;							//等级	
	int campFlg;                       //阵营标志
	size_t vipLevel;                   //vip等级
	size_t recordTme;               	//通关记录
	
private:

	int values1;
	int values2;
	int values3;	
	char otherVal[200];               //预留属性值

public:

	CpyMemRecord(const CpyMemRecord& memRecord)
	{
		init();		
		strncpy(nickName,memRecord.nickName,strlen(memRecord.nickName));
		strncpy(party,memRecord.party,strlen(memRecord.party));
		strncpy(heroId,memRecord.heroId,strlen(memRecord.heroId));
		grad = memRecord.grad;
		campFlg = memRecord.campFlg;
		vipLevel = memRecord.vipLevel;
		recordTme = memRecord.recordTme;
	}
	
	CpyMemRecord()
	{
		init();		
	}
	
	explicit CpyMemRecord(Hero *recordHero,size_t _recordTmes)
	{
		init();
		
		if(!recordHero)
		{
			cout<<"CpyMemRecord CpyMemRecord(const Hero *recordHero,size_t _recordTmes) the  recordHero is NULL:"<<endl;
		}
		
		strncpy(nickName,recordHero->getNickName(),strlen(recordHero->getNickName()));
		strncpy(party,recordHero->getParty(),strlen(recordHero->getParty()));
		strncpy(heroId,recordHero->getIdentity(),strlen(recordHero->getIdentity()));
		grad = recordHero->getGradeNow();
		campFlg = recordHero->getCamp();
		vipLevel = recordHero->getVipStage();
		recordTme = _recordTmes;
	}
	
	bool changeRecord(Hero *recordHero,size_t _recordTmes)
	{
		if(!recordHero)
		{
			cout<<"changeRecord the  recordHero is NULL:"<<endl;
			return false;
		}
		if(strlen(heroId) != 0)
		{			
			if(recordTme <= _recordTmes)
			{
				cout<<"changeRecord the  _recordTmes is not the lower record:"<<endl;
				return false;
			}
		}
		
		init();
		strncpy(nickName,recordHero->getNickName(),strlen(recordHero->getNickName()));
		strncpy(party,recordHero->getParty(),strlen(recordHero->getParty()));
		strncpy(heroId,recordHero->getIdentity(),strlen(recordHero->getIdentity()));
		grad = recordHero->getGradeNow();
		campFlg = recordHero->getCamp();
		vipLevel = recordHero->getVipStage();
		recordTme = _recordTmes;
		return true;
	}
		
		
	CpyMemRecord& operator=(const CpyMemRecord& memRecord)
	{
		init();		
		strncpy(nickName,memRecord.nickName,strlen(memRecord.nickName));
		strncpy(party,memRecord.party,strlen(memRecord.party));
		strncpy(heroId,memRecord.heroId,strlen(memRecord.heroId));
		grad = memRecord.grad;
		campFlg = memRecord.campFlg;
		vipLevel = memRecord.vipLevel;
		recordTme = memRecord.recordTme;
	}

private:	
	void init()
	{
		memset(nickName,'\0',sizeof(nickName));
		
		memset(party,'\0',sizeof(party));
		
		memset(heroId,'\0',sizeof(heroId));
		
		memset(guildName,'\0',sizeof(guildName));
		
		grad = 0;
		campFlg = -1;
		vipLevel = 0;
		recordTme = 0;
	}
	
}CpyMemRecord;


class CpyLimit
{
	//包括动态的，所有群数量,统计作用，不用做别用
	size_t totalSize;

	int num;         //进副本所要求人数
	int rank;        //进副本所要求等级
	int room;         //副本房间数
	char cpyId[SHOR_MID_VALUE_LENGTH + 1];     //副本id
	char cpyLimitId[SHOR_MID_VALUE_LENGTH +1];  //副本限制id
	char name[SHOR_MID_VALUE_LENGTH +1];  //副本名称
	vector<Cpy*> initCpyRom; //副本房间
	
	list<int> asistList;     //辅助链表，用以管理副本房间
	
	//动态正在用下标
	set<int> dynamicUsedIndex;
	
	//借过来的房价号，对应在manager中的下标号
	map<int,int> dyRomIndexToMagIndex;
	
	
	//数组中的空孔部分
	list<int> dynamicUseAbleIndex;
	
	int judgeTme;            //评分时间
	double jugGodRat;           //评分系数
	int baseGole;            //基础分
	map<string,EctypeRewardSet*> swapHeroRewardMap;   //扫荡容器
	
	size_t costFatigue;           //消耗体力值
	 
	CpyMemRecord* memRecord;      //通关记录
	
public:
	/*构造函数*/
	CpyLimit(char *_cpyLimitId,char *_cpyId,char *_name,int _baseGole,int _judgeTme,double _jugGodRat,int _num,int _rank,size_t costFatigue,\
	int _room);
	
	/*获得副本房间数*/
	int getRoom(void);  
	
	/*插入副本房间*/
	void PushCpy(Cpy *newCpy);
	
	/*进入副本资格审查*/
	bool qualifyExam(vector<string> &heroId,Failure_Reason* failure_reason,\
					 bool isTol = false,bool isParty = false);
	
	/*组队进副本*/
	string enable_enter_cpy(vector<string> &heroId, Failure_Reason* reason,bool isParty = false);
	
	/*分配空房间,初进副本*/
	void assignRom(vector<string> &heroId,int roomNum);
	
	/*进入副本*/
	void enterRom(int _roomNum,vector<string> &heroId,char *_mapId,Point *pTargetPoint=NULL);
	
	/*副本回收房间*/
	void recoverRom(char *_cpyId);
	
	/*退出副本*/
	void exitCpy(int _roomNum,vector<string> &heroId);
	
	/*判断副本房间是否超出总房间数*/
	bool roomExist(int _roomNum);
	
	/*获得副本房间数*/
	Cpy* getRoomCpy(int roomNum);  
	
	/*获得要求等级*/
	int getRank(void);
	
	/*获得副本难度*/
	int getDiffcult(void);
	
	/*进副本之前进行申请房间号确认*/
	bool qualifyExamLast(vector<string> &heroId,int &_roomNum);
	
	/*分配房间，且进副本,单人进*/
	void assignRom(vector<string> &heroId);
	
	/*获得评分时间*/
	int getJdgTme(void);
	
	/*获得评分系数*/
	double getJdgRat(void);
	
	/*析构函数*/
	~CpyLimit(void);
	
	/*通过room,以及mapId找到map实例*/
	Map_Cpy* getMapCpy(int room,char *mapId);
	
	
	/*扩展副本*/
	bool borrowCpyFun(void);
	
	/*扩展副本回收*/
	void recoverBorrowCpy(int indexList);
	
	char *getCpyId(void);
	
	/*获得基础分*/
	int getBaseGole(void);
	
	/*组队后，有队员不同意之后，回收那个预定的房间号*/
	void recoverRom(int roomNum);
	
	/*只能单人进任务副本检测*/
	bool taskCpyQualifyExam(vector<string> &heroId,Failure_Reason* failure_reason);
	
	/*单人进黑木崖副本检测*/
	bool qualifyExamTowerLayerCopy(vector<string> &heroId,Failure_Reason* failure_reason);
	
	/*生成扫荡副本奖励*/
	void insertWipeOut(char *heroId);
	
	/*删除扫荡副本奖励*/
	void eraseWipeOut(char *heroId);
	
	const char* getName() const;
	
	size_t getCostFatigue() const;
	
	CpyMemRecord* getRecord();
	
	void recordLessTme(const char* recordHeroId,size_t secondstimes);
	
	//取
	void initMemRecord();
	
	//存
	void storeMemRecord();
	
	private:
	
	/*清除扫荡副本奖励*/
	void clearWipeOut(void);
	
	
	
	
};
#endif
