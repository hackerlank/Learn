#include "stdafx.h"
#include "SvrInfo.h"

UINT32 CSvrInfoMgr::_dwTotalUsrCnt;
map<UINT32, SSvrInfo> CSvrInfoMgr::_mapID2SvrInfo;

void CSvrInfoMgr::AddSvrInfo(SSvrInfo& rSvrInfo)
{
	_mapID2SvrInfo.insert(make_pair(rSvrInfo.dwSvrID, rSvrInfo));
}

SSvrInfo* CSvrInfoMgr::GetSvrInfo(UINT32 dwSvrID)
{
	auto it = _mapID2SvrInfo.find(dwSvrID);
	if(it == _mapID2SvrInfo.end())
		return NULL;
	return &it->second;
}

void CSvrInfoMgr::GetSvrInfo(EHostType eHostType, vector<SSvrInfo>& rVecSvrInfo)
{
	for(auto it = _mapID2SvrInfo.begin(); it != _mapID2SvrInfo.end(); ++it)
	{
		SSvrInfo& rSvrInfo = it->second;
		if(rSvrInfo.eHostType == eHostType)
			rVecSvrInfo.push_back(rSvrInfo);
	}
}

SSvrInfo* CSvrInfoMgr::GetMinUsrSvrInfo(EHostType eHostType)
{
	vector<SSvrInfo*> vecSvrInfo;
	for(auto it = _mapID2SvrInfo.begin(); it != _mapID2SvrInfo.end(); ++it)
	{
		SSvrInfo& rSvrInfo = it->second;
		if(rSvrInfo.eHostType == eHostType)
			vecSvrInfo.push_back(&rSvrInfo);
	}
	if(vecSvrInfo.empty())
		return NULL;
	sort(vecSvrInfo.begin(), vecSvrInfo.end(), [](SSvrInfo* left, SSvrInfo* right){ return left->dwUsrCnt < right->dwUsrCnt; });
	INT32 index = 0, count = 0;
	for(size_t i = 0, size = vecSvrInfo.size() - 1; i < size; ++i)
	{
		if(vecSvrInfo[i]->dwUsrCnt == vecSvrInfo[i + 1]->dwUsrCnt)
			++count;
		else
			break;
	}
	index = CRandom::RandInt(0, count);
	return vecSvrInfo[index];
}

UINT32 CSvrInfoMgr::GetTotalUsrCnt()
{
	UINT32 dwUsrCnt = 0;
	for(auto it = _mapID2SvrInfo.begin(); it != _mapID2SvrInfo.end(); ++it)
	{
		SSvrInfo& rSvrInfo = it->second;
		if(rSvrInfo.eHostType == eHostGate)
			dwUsrCnt = dwUsrCnt + rSvrInfo.dwUsrCnt;
	}
	return dwUsrCnt;
}
