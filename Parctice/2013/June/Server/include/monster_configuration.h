/********************************************************************

    created:   2012/2/24  15:24
	
	文件名：	monster_configuration.h

    author:       Tory 

    purpose:  monster_configuration.h头文件
	
	修改：	

*********************************************************************/
#ifndef MONSTER_CONFIGURATION_H
#define MONSTER_CONFIGURATION_H
#include<set>
#include<string>
#include<vector>
#include"wholeDefine.h"
using namespace std;
class Monster_Inform
{
	
	public:
	
	Monster_Inform(char * _typeId, char *_type, char *_kand,double rank,char *_nickName, double _lifeUpperVal, double _lifeVal,\
		int _magicUpperVal,int _magicVal,int  _getHrtSud,double _outHrt,double _inHrt, double _outAttVal, double _inAttVal,\
		double _outDefVal, double _inDefVal, int _defSumVal,double _hit,double _crit,double _voids,double _tenacity,int _moveRange,\
		int _hatRange,int _attRange,int _failGoodsless,int _failGoodsmost,int _hatVal,int _angVal,\
		vector<string> _skiIdSet,char *genAttId,int _gold,set<string>& _failId,char *_photoId,\
		char* _stage,int _experience,double _cdTime,int _fiveEleInt,int _fiveHurt,\
		int _fiveEleRank,int _goFor,int _expTme,int _monyTme,int _speed,int _ownerAttriType,\
		char* _ownerAttri,double _attackRatio,bool _isInnerAttack,int _radius = 0);

		~Monster_Inform(void);
		
	public:
		char *typeId;		//怪物类型
	
		char *nickName;		//名称
		
		char *photoId;
		
		double lifeUpperVal;	//生命值上限	
		
		double lifeVal;		//当前生命值
		
		int magicUpperVal;	//魔法值上限
		
		int magicVal;		//当前魔法值
		
		
		int attack_range;	//攻击范围
		
		int walk_range;		//行走范围		
		int sum;
		
		
		char *type;         //怪物类型（被动，主动，巡逻）
		
		char *kind;       //怪物种类（普通，精英，boss）
		
		double rank;         //等级
		
		
		int hrtSud;      //秒伤
		double outHrt;     //外伤
		double inHrt;      //内伤
		double outAttVal;    //外功攻击值
		double inAttVal;    //内功攻击值
		double outDefVal;    //外功防御值
		double inDefVal;    //内功防御值
		int defSumVal;   //防御值总和
		double hit;        //命中
		double crit;       //暴击
		double voids;      //闪避
		double tenacity;       //韧性	
		int hatRange;      //仇恨范围
		int failGoodsLess;   //怪物掉落最大值
		int failGoodsMost;   //怪物掉落最大值
		int hatVal;      //仇恨值
		int gold;       //金币		
		
		set<string> failList;  //掉落列表
		
		char* stage;
		
		int radius;
		
		double cdTime;    	//cd时间		
		
		int experience;     //经验
		
		int angVal;         //怒气值
		
		vector<string>skiIdSet;   //技能id列表
		
		int speed;
		
		
		int fiveEleInt;      //五行属性代表值
		int fiveEleRank;     //五行等级值
		int fiveHurt;        //五行伤害值
		
		
		int goFor;          //走动频率
		
		int expTme;         //经验倍数
		
		int monyTme;        //金钱倍数
		
		int ownerAttriType;            //类型，帮派为1，阵营为2，其余的暂为0
		char ownerAttri[SHOR_MID_VALUE_LENGTH + 1];     //帮派，阵营属性
		
		
		char genAttId[SHOR_MID_VALUE_LENGTH + 1];
		
		double attackRatio;          //击杀红名怪按比例来算
		
		bool isInnerAttack;          //偏内功为真，偏外功为假
		
		char* getstage(void);
		int getgold(void);
		int getrank(void);
		char* getkind(void);
		int getExperience(void);
		
		int getAngVal(void);
		vector<string> getSkiIdSet(void);
		
		int getRank(void);
		
		int getSpeed(void);
		
		void print(char *monKindId);

};	


#endif

