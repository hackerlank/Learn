/********************************************************************

    filename: monsterPatrol.h 

    author:       ChenZhen

    amend:   2012/5/09       by Tory

*********************************************************************/
#ifndef MONSTERPATROL_H
#define MONSTERPATROL_H
#include"monsterBase.h"
#include"map_inform.h"
/**
**塔防副本
**/
#include "TD_Instancing.h"


class MonsterPatrol : public MonsterBase
{
private:	

	Point endFinPt; 				//巡逻终点（网格逻辑点，通过像素点转换而得到）	       				
	
	int radius;              		//自己寻路半径
	
	bool flgEnd;        //寻路终点转换标记值
	
	
public :
	MonsterPatrol(char *_mapId,char *_typeId,char *_nickName,char *_identity, char *_type,char *_kind,\
	int _experience,double _cdTime,int _lifeUpperVal,int _lifeVal,\
	int _magicUpperVal,int _magicVal,int _getHrtSud,int _outHrt,int _inHrt, int _outAttVal, int _inAttVal,\
	int _outDefVal, int _inDefVal,int _defSumVal,double _hit,double _crit,int _voids,int _tenacity,\
	int _moveRange, int _hatRange,int _attRange,int _failGoodsless,int _failGoodsmost,\
	int _hatVal,int _gold,set<string>& _failId, Point _pt,int _rank,int _speed,int _fiveEleInt,int _fiveHurt,\
	int _fiveRank,int _forGo,int _expTme,int _monyTme,char *_stage,char *_photoId,\
	vector<string> &skiIdSet,char *_genAttId,double _angVal,int _ownerAttriType,char* _ownerAttri,\
	double _attackRatio,bool isInnerAttack,LveCtnManger _lveCtnMager,Point logicPt,int _radius);
		
	/*析构函数*/
	~MonsterPatrol(void);
	
	/*怪物思考函数*/
	virtual void response(void);
	
	void getEnd(Point _logicPt);
		
	/*深拷贝函数*/
	virtual MonsterBase* copyMon(char *_mapId);

	/*怪物死亡函数*/
	virtual void die(bool flgInit = false);
	
	/*重置整个怪物数据*/
	void initMonsterALL(void);
	
};
#endif

