#include "stdafx.h"
#include "BlockerMgr.h"
#include "Blocker.h"
#include "ResistCFG.h"
std::map<UINT32, CBlockerPtr> CBlockerMgr::_mapID2Blocker;
UINT32 CBlockerMgr::_dwNextInstID = BLOCKER_ID_MIN;
std::map<UINT32,SResistCFG> CBlockerMgr::_mapConfig;

bool CBlockerMgr::Init()
{
    CResistLoader oLoader;
    string strPath = Config._strConfigDir + "Conf/Table/Resist.xml";
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(auto it = oLoader._vecData.begin() ;it != oLoader._vecData.end();it++)
    {
        SResistCFG* pCfg = *it;
        if(!(_mapConfig.insert(make_pair(pCfg->_wResistId,*pCfg))).second)
        {
         LOG_CRI << "oLoader.LoadData fails! RepeatKey: " << pCfg->_wResistId;
        return false;
        }

    }
	return true;
}

const SResistCFG* CBlockerMgr::GetConfig(UINT32 dwID)
{
    auto it = _mapConfig.find(dwID);
    if(it == _mapConfig.end())
    {
        return NULL;
    }
    return &(it->second);
}
void CBlockerMgr::Destroy()
{
	_mapID2Blocker.clear();
}

UINT32 CBlockerMgr::GetNewInstID()
{
	UINT32 dwNewInstID = _dwNextInstID++;
	if(_dwNextInstID > BLOCKER_ID_MAX)
		_dwNextInstID = BLOCKER_ID_MIN;
	return dwNewInstID;
}

void CBlockerMgr::TimerCheck()
{
	for(auto it = _mapID2Blocker.begin(); it != _mapID2Blocker.end(); ++it)
	{
		CBlockerPtr pBlocker = it->second;
		if(pBlocker->IsDisappeared())
		{
			pBlocker->Disappear();
		}
	}
    for(auto it = _mapID2Blocker.begin(); it != _mapID2Blocker.end();)
	{
		CBlockerPtr pBlocker = it->second;
		if(pBlocker->IsDel())
		{
			it = _mapID2Blocker.erase(it);
		}
        else
        {
            ++it;
        }
	}

}

CBlockerPtr CBlockerMgr::CreateBlocker(UINT32 dwBlockerID)
{
    if(GetConfig(dwBlockerID) == NULL)
    {
        return NULL;
    }
	CBlockerPtr pBlocker(new CBlocker(dwBlockerID));
	if(pBlocker == NULL)
		return NULL;
	pBlocker->SetInstID(GetNewInstID());
	if(!_mapID2Blocker.insert(std::make_pair(pBlocker->GetInstID(), pBlocker)).second)
		LOG_DBG << "Blocker is already exist";
	return pBlocker;
}

void CBlockerMgr::DestroyBlocker(CBlocker& rBlocker)
{
    rBlocker.SetDel();
	//_mapID2Blocker.erase(rBlocker.GetInstID());
}
