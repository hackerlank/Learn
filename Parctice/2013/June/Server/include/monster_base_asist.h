#ifndef MONSTER_BASE_ASIST_H
#define MONSTER_BASE_ASIST_H
#include<time.h>
#include<string>
#include<math.h>
using namespace std;
/************************************************************
	文件名：monster_base_asist.h
	文件作用：类MonsterBase类的辅助功能数据结构
	作者：chenzhen
	创建日期：2012.08.29
************************************************************/

#define MON_DEBUF_DIZZ_STATE			0x1				//眩晕
#define MON_DEBUF_FORB_MOVE_STATE		0x2				//定身：可操作不可移动
#define MON_DEBUF_FORB_ATTK_STATE		0x4				//点穴：可移动
#define MON_DEBUF_IN_POISON_STATE		0x8				//中毒：持续掉血
#define	MON_DEBUF_LOSE_HIT_STATE 		0x10			//丢失：降低命中
#define MON_DEBUF_LOSE_DF_AT_STATE		0x20			//黯灭：减攻减防
#define MON_DEBUF_LOSE_TENC_STATE		0x40			//虚弱：减少韧性
#define MON_DEBUF_LOSE_SPEED_STATE		0x2000			//减少移动速度






/*延时性技能*/
typedef struct SkillTime
{
	double cdTimes;                 //持续时间
	int alCtn;                      //已经跑过的时间（折算成思考次数）
	int thkCnt;                     //折算成思考次数
	int effectType;                 //技能效果类型,为了今后扩展
	int values;                  //每次掉血次数
	char attheroId[SHOR_MID_VALUE_LENGTH + 1];               //攻击者id
	
	
	SkillTime(char *_heroId,double _cdTimes,int _effectType,int _values)
	{
		memset(attheroId,'\0',SHOR_MID_VALUE_LENGTH + 1);
		alCtn = 0;
		cdTimes = _cdTimes;
		thkCnt = ceil(cdTimes/MONSTER_THINK_TIME);
		effectType = _effectType;
		values = _values;
		if(_heroId != NULL)
		{
			strncpy(attheroId,_heroId,strlen(_heroId));
		}
	}
	
	SkillTime(const SkillTime &skillTme)
	{
		memset(attheroId,'\0',sizeof(attheroId));
		alCtn = skillTme.alCtn;
		cdTimes = skillTme.cdTimes;
		thkCnt = ceil(cdTimes/MONSTER_THINK_TIME);
		effectType = skillTme.effectType;
		values = skillTme.values;		
		strncpy(attheroId,skillTme.attheroId,strlen(skillTme.attheroId));
		
	}
	
	SkillTime& operator= (const SkillTime &skillTme)
	{
		memset(attheroId,'\0',sizeof(attheroId));
		alCtn = skillTme.alCtn;
		cdTimes = skillTme.cdTimes;
		thkCnt = ceil(cdTimes/MONSTER_THINK_TIME);
		effectType = skillTme.effectType;
		values = skillTme.values;		
		strncpy(attheroId,skillTme.attheroId,strlen(skillTme.attheroId));
		return *this;		
	}
	
	
	
	/*cd时间判断*/
	bool timeOut(void)
	{
		return alCtn >= thkCnt;
	}
	
	/*"时间"自增*/
	void gain(void)
	{
		alCtn++;
	}
	
	/*时间是否为整秒数*/
	bool sentPos(void)
	{
		return alCtn %2 == 0;
	}
		
}SkillTime;	

/*怪物存活次数管理器*/	
typedef struct LveCtnManger
{
	int sumLveCtn;                     //存活次数
	int durTme;                     //刷出间隔（折合成地图思考次数）
	int lvedCtn;                    //以刷出次数；
	int waitTme;                    //时间等待次数
	LveCtnManger(int _sumLveCtn = 1,int _durTme = 0)
	{
		sumLveCtn = _sumLveCtn;
		durTme = _durTme;
		
		lvedCtn = 1;
		waitTme = 0;
	}
	
	LveCtnManger(const LveCtnManger &lveCtn)
	{
		sumLveCtn = lveCtn.sumLveCtn;
		durTme = lveCtn.durTme;
		
		lvedCtn = lveCtn.lvedCtn;
		waitTme = lveCtn.waitTme;
	}
	
	LveCtnManger& operator= (const LveCtnManger &lveCtn)
	{
		sumLveCtn = lveCtn.sumLveCtn;
		durTme = lveCtn.durTme;
		
		lvedCtn = lveCtn.lvedCtn;
		waitTme = lveCtn.waitTme;
		
		return *this;
	}
	
	
	/*存活次数是否刷够*/
	bool isLveCtn(void)
	{
		lvedCtn++;
		if(lvedCtn <= sumLveCtn)
		{	
			waitTme = 0;
			return true;
		}
		return false;			
	}
	
	/*判断刷出时间是否够*/
	bool isWaitTme(void)
	{
		if(waitTme >= durTme)
		{
			return true;
		}
		waitTme++;
		return false;		
	}
	
	/*重置*/
	void initCover(void)
	{
		lvedCtn = 1;
		waitTme = 0;
	}
	/*测试属性*/
	int testPro(void)
	{
		cout<<"sumLveCtn:"<<sumLveCtn<<endl;
		cout<<"lvedCtn:"<<lvedCtn<<endl;
		cout<<"durTme:"<<durTme<<endl;	
		return sumLveCtn;		
	}
	
	bool isAliveAgin(void)
	{
		return lvedCtn <= sumLveCtn;		
	}
		
		
}LveCtnManger;

#endif