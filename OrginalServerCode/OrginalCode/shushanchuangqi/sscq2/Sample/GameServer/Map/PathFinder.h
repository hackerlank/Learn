/********************************************************************
//	Game Server Source File.
//	File name:	PathFinder.h
//	Created:	2012/11/22	10:00
//	Organization:
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:
//	Version:	1.0
//	Histroy:
*********************************************************************/

#pragma once
#include "Point.h"
#include "MapInfo.h"
#include "Monster.h"
#define PATH_FINDER_COUNT 3

typedef CSpinLock CLock;

class CPathEvt
{
	friend class CPathFindMgr;
public:
	UINT32 GetIndex();
	void OnFindPath();
	void OnResult();
protected:
	DEF_NEW_DELETE(CPathEvt);
	CPathEvt(const SMapInfo& rMapInfo) : _qwCreatureID(0),
		/*TODO _eMonsterState(eMonsterNone),*/ _rMapInfo(rMapInfo) { }

	UINT64 _qwCreatureID;
	//TODO EMonsterState _eMonsterState;
	SPoint _oStartPoint;
	SPoint _oDestPoint;
	const SMapInfo& _rMapInfo;

	vector<SPoint> _vecPath;
};

class CPathFinder
{
	friend class CPathFindMgr;
public:
	CPathFinder(UINT32 dwIndex) : _dwIndex(dwIndex) { }
	void Run();
	static void PathFindThread(CPathFinder* pThis);
protected:
	UINT32 _dwIndex;
	CThread _thread;
};

class CPathFindMgr
{
public:
	CPathFindMgr() : _bRun(false) { }
	~CPathFindMgr();

	static CPathFindMgr& Instance();

	static bool ProcessResult();

	bool Start();
	void Stop();
	bool IsRunning() const { return _bRun; }

    bool FindPath(CMonster& rMonster, SPoint& rDestPoint);

	void PushRequestEvt(CPathEvt& rPathEvt);
	CPathEvt* PopRequestEvt(UINT32 dwIndex);

	void PushResultEvt(CPathEvt& rPathEvt);
	CPathEvt* PopResultEvt();

private:

	list<CPathEvt*> _arRequestEvt[PATH_FINDER_COUNT];
	CLock _arReqLock[PATH_FINDER_COUNT];

	list<CPathEvt*> _lstResultEvt;
	CLock _oResLock;

	vector<CPathFinder*> _vecPathFinder;
	bool _bRun;
};
