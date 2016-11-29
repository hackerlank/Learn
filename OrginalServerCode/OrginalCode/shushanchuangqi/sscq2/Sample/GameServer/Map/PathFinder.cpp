/********************************************************************
//	Game Server Source File.
//	File name:	PathFinder.cpp
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

#include "stdafx.h"
#include "PathFinder.h"
#include "Map.h"
#include "MonsterMgr.h" 
inline CLogObj& operator<<(CLogObj& src, const SMapSearchNode& rNode)
{
	src << " [Point X: " << rNode.x << ", Y: " << rNode.y << "]";
	return src;
}

UINT32 CPathEvt::GetIndex()
{
	return _rMapInfo.wMapID % PATH_FINDER_COUNT;
}

void CPathEvt::OnFindPath()
{
	SCoord oStart, oDest;
	if(!_rMapInfo.ToIntCoord(_oStartPoint, oStart, true))
	{
		LOG_CRI << "StartPoint not in map!" << _oStartPoint;
		return;
	}
	if(!_rMapInfo.ToIntCoord(_oDestPoint, oDest, true))
	{
		LOG_CRI << "DestPoint not in map!" << _oDestPoint;
		return;
	}

	SMapSearchNode oStartNode(oStart.dwX, oStart.dwY);
	SMapSearchNode oDestNode(oDest.dwX, oDest.dwY);
	vector<SMapSearchNode> vecNode;

	if(!_rMapInfo.FindPath(oStartNode, oDestNode, vecNode))
	{
		LOG_CRI << "FindPath fails! Start: " << oStartNode << ", Dest: " << oDestNode << ", MapID: " << _rMapInfo.wMapID;
		return;
	}

	if(vecNode.size() < 2)
	{
		LOG_CRI << "FindPath fails!";
		return;
	}
	else if(vecNode.size() == 2)
	{
		_vecPath.push_back(_oStartPoint);
		_vecPath.push_back(_oDestPoint);
	}
	else
	{
		//LOG_DBG << "Path Found:";
		_vecPath.push_back(_oStartPoint);
		for(size_t i = 1; i < vecNode.size() - 1; ++i)
		{
			//LOG_DBG << "x: " << vecNode[i].x << ", y: " << vecNode[i].y;
			bool bAdd = false;
			if(i == 1)
			{
				bAdd = true;
			}
			else
			{
				INT32 dwLeftDeltaX = vecNode[i].x - vecNode[i - 1].x;
				INT32 dwLeftDeltaY = vecNode[i].y - vecNode[i - 1].y;
				INT32 dwRightDeltaX = vecNode[i + 1].x - vecNode[i].x;
				INT32 dwRightDeltaY = vecNode[i + 1].y - vecNode[i].y;
				if(dwLeftDeltaX * dwRightDeltaY != dwLeftDeltaY * dwRightDeltaX)
					bAdd = true;
			}
			if(bAdd)
			{
				SCoord oCoord(vecNode[i].x, vecNode[i].y);
				SPoint oPoint;
				_rMapInfo.ToFloatCoord(oCoord, oPoint, true);
				_vecPath.push_back(oPoint);
			}
		}
		_vecPath.push_back(_oDestPoint);
#ifdef _DEBUG
		for(size_t i = 1; i < _vecPath.size(); ++i)
		{
			if(_rMapInfo.HasBlockPoint(_vecPath[i - 1], _vecPath[i]))
				LOG_CRI << "HasBlockPoint: " << _vecPath[i - 1] << _vecPath[i];
		}
#endif
	}
	//LOG_DBG << "Final Path: " << _vecPath;
}

void CPathEvt::OnResult()
{
	CMonsterPtr pMonster = CMonsterMgr::GetMonster(_qwCreatureID);
	if(pMonster == NULL)
	{
		LOG_CRI << "Can't find Monster! qwCreatureID: " << _qwCreatureID;
		return;
	}
	pMonster->OnPathFound(_vecPath);
	pMonster->SetInPathFind(false);
}

void CPathFinder::Run()
{
	_thread.Start(PathFindThread, this);
}

void CPathFinder::PathFindThread(CPathFinder* pThis)
{
	CPathEvt* pPathEvt = NULL;
	while(CPathFindMgr::Instance().IsRunning())
	{
		pPathEvt = CPathFindMgr::Instance().PopRequestEvt(pThis->_dwIndex);
		if(pPathEvt != NULL)
		{
			pPathEvt->OnFindPath();
			CPathFindMgr::Instance().PushResultEvt(*pPathEvt);
		}
		else
		{
			Sleep(1);
		}
	}
}

CPathFindMgr::~CPathFindMgr()
{
	Stop();
}

CPathFindMgr& CPathFindMgr::Instance()
{
	static CPathFindMgr sPathFindMgr;
	return sPathFindMgr;
}

bool CPathFindMgr::Start()
{
	_bRun = true;
	for(UINT32 i = 0; i < PATH_FINDER_COUNT; ++i)
	{
		CPathFinder* pPathFinder = new CPathFinder(i);
		if(pPathFinder == NULL)
			return false;
		pPathFinder->Run();
		_vecPathFinder.push_back(pPathFinder);
	}
	return true;
}

void CPathFindMgr::Stop()
{
	_bRun = false;
	for(size_t i = 0; i < _vecPathFinder.size(); ++i)
	{
		_vecPathFinder[i]->_thread.Join();
		delete _vecPathFinder[i];
	}
	_vecPathFinder.clear();
}

bool CPathFindMgr::FindPath(CMonster& rMonster, SPoint& rDestPoint)
{
	CGameMapPtr pMap = rMonster.GetMap();
	if(pMap == NULL)
	{
		LOG_CRI << "pMap is NULL!";
		return false;
	}
	if(rMonster.GetPoint() == rDestPoint)
	{
		LOG_CRI << "Point is the same!";
		return false;
	}
	if(pMap->IsBlockPoint(rDestPoint))
		return false;
	CPathEvt* pPathEvt = new CPathEvt(pMap->GetMapInfo());
	if(pPathEvt == NULL)
		return false;
	pPathEvt->_qwCreatureID = rMonster.GetCreatureID();
	SPoint& rPoint = rMonster.GetPoint();
	if(pPathEvt->_rMapInfo.IsBlock(rPoint))
	{
		LOG_WRN << "Point is blocked: " << rPoint;
		if(!pMap->GetMovablePoint(rPoint, pPathEvt->_oStartPoint))
		{
			LOG_CRI << "GetMovablePoint fails: " << rPoint;
			delete pPathEvt;
			return false;
		}
	}
	else
	{
		pPathEvt->_oStartPoint = rPoint;
	}
	pPathEvt->_oStartPoint = rPoint;
	pPathEvt->_oDestPoint = rDestPoint;
	//pPathEvt->_eMonsterState = rMonster.GetMonsterState();
	rMonster.SetInPathFind(true);
	PushRequestEvt(*pPathEvt);
	return true;
}

bool CPathFindMgr::ProcessResult()
{
	CPathEvt* pPathEvt = Instance().PopResultEvt();
	if(pPathEvt == NULL)
		return false;
	pPathEvt->OnResult();
	delete pPathEvt;
	return true;
}

void CPathFindMgr::PushRequestEvt(CPathEvt& rPathEvt)
{
	UINT32 dwIndex = rPathEvt.GetIndex();
	CAutoLock<CLock> oAutoLock(_arReqLock[dwIndex]);
	_arRequestEvt[dwIndex].push_back(&rPathEvt);
}

CPathEvt* CPathFindMgr::PopRequestEvt(UINT32 dwIndex)
{
	CAutoLock<CLock> oAutoLock(_arReqLock[dwIndex]);
	CPathEvt* pPathEvt = NULL;
	if(_arRequestEvt[dwIndex].empty())
		return NULL;
	pPathEvt = _arRequestEvt[dwIndex].front();
	_arRequestEvt[dwIndex].pop_front();
	return pPathEvt;
}

void CPathFindMgr::PushResultEvt(CPathEvt& rPathEvt)
{
	CAutoLock<CLock> oAutoLock(_oResLock);
	_lstResultEvt.push_back(&rPathEvt);
}

CPathEvt* CPathFindMgr::PopResultEvt()
{
	CPathEvt* pPathEvt = NULL;
	CAutoLock<CLock> oAutoLock(_oResLock);
	if(_lstResultEvt.empty())
		return NULL;
	pPathEvt = _lstResultEvt.front();
	_lstResultEvt.pop_front();
	return pPathEvt;
}
