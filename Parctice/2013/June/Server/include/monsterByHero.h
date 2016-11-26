#ifndef MONSTER_BY_HERO_H
#define MONSTER_BY_HERO_H
#include"monsterBase.h"

/*怪物属性是人物属性的比例*/
typedef struct ValueRatio
{
	double lifeUpperValRatio;	//生命值上限系数			
	double lifeValRatio;		//当前生命值系数	
	double outHrtRatio;    	   //外伤系数
	double inHrtRatio;      	  //内伤系数
	double outAttValRatio;    //外功攻击值系数
	double inAttValRatio;    //内功攻击值系数
	double outDefValRatio;   //外功防御值系数
	double inDefValRatio;    //内功防御值系数
	
	double hitRatio;        //命中系数
	double critRatio;       //暴击系数
	double voidsRatio;      //闪避系数
	double tenacityRatio;   //韧性系数	
	double rankRatio;       //等级系数
	
	ValueRatio(double _lifeUpperValRatio = 0,double _lifeValRatio = 0,double _outHrtRatio = 0,double _inHrtRatio = 0,\
	double _outAttValRatio = 0,double _inAttValRatio = 0,double _outDefValRatio = 0,double _inDefValRatio = 0,\
	double _hitRatio = 0,double _critRatio = 0,double _voidsRatio = 0,double _tenacityRatio = 0,double _rankRatio = 0)
	{
		lifeUpperValRatio = _lifeUpperValRatio;
		
		lifeValRatio = _lifeValRatio;
		
		outHrtRatio = _outHrtRatio;
		
		inHrtRatio = _inHrtRatio;
		
		outAttValRatio = _outAttValRatio;
		
		inAttValRatio = _inAttValRatio;
		
		outDefValRatio = _outDefValRatio;
		
		inDefValRatio = _inDefValRatio;
		
		hitRatio = _hitRatio;
		
		critRatio = _critRatio;
		
		voidsRatio = _voidsRatio;
		
		tenacityRatio = _tenacityRatio;
		
		rankRatio = _rankRatio;
	}		
	
}ValueRatio;


class Map_Inform;
class MonsterByHero : public MonsterBase
{
	ValueRatio valueRatio;

public :
	MonsterByHero(char *_mapId,char *_typeId,char *_nickName,char *_identity,\
	char *_type,char *_kind,int _experience,double _cdTime,int _lifeUpperVal,\
	int _lifeVal,int _magicUpperVal,int _magicVal,int _getHrtSud,int _outHrt,\
	int _inHrt, int _outAttVal, int _inAttVal,int _outDefVal, int _inDefVal,\
	int _defSumVal,double _hit,double _crit,int _voids,int _tenacity,int _moveRange,\
	int _hatRange,int _attRange,int _failGoodsless,int _failGoodsmost,int _hatVal,\
	int _gold,set<string>& _failId,Point _pt,	int _rank,int _speed,int _fiveEleInt,\
	int _fiveHurt,int _fiveRank,int _forGo,int _expTme,int _monyTme,char *_stage,\
	char *_photoId,vector<string> &skiIdSet,char *_genAttId,double _angVal,\
	int _ownerAttriType,char* _ownerAttri,double _attackRatio,bool isInnerAttack,\
	LveCtnManger _lveCtnMager,ValueRatio valueRatio);
	
	
	
	/*析构函数*/
	~MonsterByHero(void);
	
	
	/*怪物思考函数*/
	void response(void);	
	

	
	/*深拷贝函数*/
	MonsterBase* copyMon(char *_mapId);	
	
	/*怪物死亡函数*/
	void die(bool flgInit = false);
	
	/*重置整个怪物数据*/
	void initMonsterALL(void);	
	
	/*根据角色生成怪物属性*/
	void initMonsterValuesByHero(Hero *enterHero);
};
#endif
