#ifndef MONSTEESCAPE_H
#define MONSTEESCAPE_H
#include"monsterBase.h"
class MonsterEscape :public MonsterBase
{
	list<Point> endListPt;
	
	Point endFinPt;
	
	bool flgEnd;
	
	/*获得巡逻终点*/
	void getEnd(void);
	
	int runDurTme;
	
	int runCtn;
	
	bool isRun;
	
public :
	MonsterEscape(char *_mapId,char *_typeId,char *_nickName,char *_identity, char *_type,char *_kind,\
	int _experience,double _cdTime,int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,\
	int _getHrtSud,int _outHrt,int _inHrt, int _outAttVal, int _inAttVal,\
	int _outDefVal, int _inDefVal,int _defSumVal,double _hit,double _crit,int _voids,int _tenacity,\
	int _moveRange, int _hatRange,int _attRange,int _failGoodsless,int _failGoodsmost,\
	int _hatVal,int _gold,set<string>& _failId, Point _pt,int _rank,int _speed,int _fiveEleInt,\
	int _fiveHurt,int _fiveRank,int _forGo,int _expTme,int _monyTme,char *_stage,char *_photoId,vector<string> &skiIdSet,\
	char *_genAttId,double _angVal,int _ownerAttriType,char* _ownerAttri,double _attackRatio,bool isInnerAttack,LveCtnManger _lveCtnMager,list<Point> _endListPt);	
	
	
	
	
	/*析构函数*/
	~MonsterEscape(void);
	
	
	
	/*怪物思考函数*/
	virtual void response(void);	
	
	
	/*深拷贝函数*/
	virtual MonsterBase* copyMon(char *_mapId);
	
	/* 被动怪的仇恨范围搜寻函数*/
	void redSchRge(void); 
	
	/*怪物死亡函数*/
	void die(bool flgInit = false);
	
	/*插入一个仇恨值*/
	virtual void InpushEnmityValues(HatVal &hatva);
	
	/*重置整个怪物数据*/
	void initMonsterALL(void);
	
	/*随机一个逃窜点*/
	void randEscapePt(void);
	
	/*逃窜*/
	void goEscape(void);
	
	/* 修改当前生命值*/
	void setLifeVal(int _lifeVal);
	
	/*随机一个逃窜点*/
	void getEscapePt(void);
	
	/*是否逃跑*/
	bool istimeRun(void);
	
};
#endif


