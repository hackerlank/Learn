#pragma once
#include "Point.h"

#define PLAYER_POS_RADIUS 1.0f

class CBaseObj;
enum EType
{
	eKillMonster,	//击杀怪物开关
//	eOpenSwitcher,	//打开开关
	ePlayerPos,		//玩家位置
	eAllMonsterKilled, //怪物被杀光
};

struct SObjCond : public enable_shared_from_this<SObjCond>
{
	virtual ~SObjCond() { }
	virtual EType GetType() = 0;
	virtual bool Check(CBaseObj& rBaseObj) = 0;
};

struct SKillMonsterCond : public SObjCond
{
	virtual EType GetType(){ return eKillMonster; }
	virtual bool Check(CBaseObj& rBaseObj);

	std::vector<UINT16> _vecMonsterID;
};
#if 0
struct SOpenSwitcherCond : public SObjCond
{
	virtual EType GetType(){ return eOpenSwitcher; }
	virtual bool Check(CBaseObj& rBaseObj);

	std::vector<UINT16> _vecSwitcherID;	
};
#endif
struct SPlayerPosCond : public SObjCond
{
	virtual EType GetType(){ return ePlayerPos; }
	virtual bool Check(CBaseObj& rBaseObj);

	std::vector<SPoint> _vecPoint;
};

struct SAllMonsterKilled : public SObjCond
{
	virtual EType GetType(){ return eAllMonsterKilled; }
	virtual bool Check(CBaseObj& rBaseObj);
};
	
