#include "stdafx.h"
#include "GatherMgr.h"
#include "Player.h"
#include "User.h"
#include "Protocols.h"
#include "GatherCFG.h"
#include "Tokenizer.h"
#include "GatherCond.h"
using namespace NGatherProt;
UINT64 CGatherMgr::_qwVersion = VERSION_INIT;
map<UINT16, SGatherCFGEx> CGatherMgr::_mapID2GatherData;
map<UINT32, IGatherPtr> CGatherMgr::_mapID2Gather;
UINT32 CGatherMgr::_dwNextGatherInstID = GATHER_CREATURE_ID_MIN;
bool CGatherMgr::Init()
{
    CGatherLoader oGatherLoader;
    string strPath = Config._strConfigDir + "Conf/Table/Gather.xml";
    if(!oGatherLoader.LoadData(strPath))
        return false;

    for(auto it = oGatherLoader._vecData.begin(); it != oGatherLoader._vecData.end(); ++it)
    {
        SGatherCFGEx rCFG(*(*it)); 
        if(rCFG._byIsTask > 0)
        {
            rCFG._dwOtherType |= SGatherCFGEx::EOTHER_ISTASK;
        }
        buf::Tokenizer tkCost(rCFG._strCost,';');
        for(size_t i = 0; i < tkCost.size() ;i++)
        {
            buf::Tokenizer tkSubCost(tkCost[i],',');
            if(tkSubCost.size() != 3)
            {
                continue;

            }
            UINT8 byConType = atoi(tkSubCost[0].c_str());
            if(byConType < eGCT_None || byConType > eGCT_End)
            {
                return false;
            }
            EGatherConType eConType = static_cast<EGatherConType>(byConType);
            UINT32 dwParam1 = atoi(tkSubCost[1].c_str());
            UINT32 dwParam2 = atoi(tkSubCost[2].c_str());
            CGatherCondBase *pCond = CGatherCondBase::CreateCond(eConType,dwParam1,dwParam2);
            if(NULL != pCond) 
            {
                rCFG._vecCond.push_back(CGatherCondBasePtr(pCond));
            }
            else
            {
                return false;
            }

        }
        if(rCFG._wGatherId != 0)
        {
            _mapID2GatherData.insert(make_pair(rCFG._wGatherId,rCFG));
        }
    }
    return true;
}

bool CGatherMgr::ReloadConfig(bool bReload /* = true */)
{
    CGatherLoader oGatherLoader;
    string strPath = Config._strConfigDir + "Conf/Table/Gather.xml";
    if(!oGatherLoader.LoadData(strPath))
        return false;

    for(auto it = oGatherLoader._vecData.begin(); it != oGatherLoader._vecData.end(); ++it)
    {
        SGatherCFGEx rCFG(*(*it)); 
        if(rCFG._byIsTask > 0)
        {
            rCFG._dwOtherType |= SGatherCFGEx::EOTHER_ISTASK;
        }
        buf::Tokenizer tkCost(rCFG._strCost,';');
        for(size_t i = 0; i < tkCost.size() ;i++)
        {
            buf::Tokenizer tkSubCost(tkCost[i],',');
            if(tkSubCost.size() != 3)
            {
                continue;

            }
            UINT8 byConType = atoi(tkSubCost[0].c_str());
            if(byConType < eGCT_None || byConType > eGCT_End)
            {
                return false;
            }
            EGatherConType eConType = static_cast<EGatherConType>(byConType);
            UINT32 dwParam1 = atoi(tkSubCost[1].c_str());
            UINT32 dwParam2 = atoi(tkSubCost[2].c_str());
            CGatherCondBase *pCond = CGatherCondBase::CreateCond(eConType,dwParam1,dwParam2);
            if(NULL != pCond) 
            {
                rCFG._vecCond.push_back(CGatherCondBasePtr(pCond));
            }
            else
            {
                return false;
            }

        }
        if(rCFG._wGatherId != 0)
        {
            _mapID2GatherData.insert(make_pair(rCFG._wGatherId,rCFG));
        }
    }
    if(bReload)
        ++ _qwVersion;
    return true;
}

IGatherPtr CGatherMgr::CreateGather(UINT16 wGatherID,UINT8 byIndex)
{
    auto it = _mapID2GatherData.find(wGatherID);
    if(it == _mapID2GatherData.end())
        return NULL;
    SGatherCFGEx& rData = it->second;
    UINT32 dwInstID = _dwNextGatherInstID++;
    if(_dwNextGatherInstID > GATHER_CREATURE_ID_MAX)
        _dwNextGatherInstID = GATHER_CREATURE_ID_MIN;
     CGatherPtr pGather(new CGather(wGatherID, dwInstID, rData,_qwVersion));

    if(pGather == NULL)
        return NULL;
    _mapID2Gather.insert(make_pair(dwInstID, pGather));
    return pGather;
}

void CGatherMgr::DestroyGather(IGather& rGather)
{

    rGather.SetDel();
    //_mapID2Gather.erase(rGather.GetInstID());
}
IGatherPtr CGatherMgr::GetGatherByID(UINT32 dwInstanceID)
{
    auto it = _mapID2Gather.find(dwInstanceID);
    if(it != _mapID2Gather.end())
    {
        return it->second;
    }
    return NULL;
}

SGatherCFGEx* CGatherMgr::GetGatherConfig(UINT16 wGatherID)
{
    auto it = _mapID2GatherData.find(wGatherID);
    if(it == _mapID2GatherData.end())
        return NULL;
    return &it->second;
}

void CGatherMgr::TimerCheck(time_t tNow)
{
    for(auto it = _mapID2Gather.begin(); it != _mapID2Gather.end(); )
    {
        IGatherPtr pGather = it->second;
        if(pGather->IsDel())
        {
            it = _mapID2Gather.erase(it);
        }
        else
        {
           pGather->TimerCheck(tNow);
           ++it;
        }
    }
}

void CGatherMgr::ClearAllLua()
{
    for(auto it =  _mapID2GatherData.begin();it !=  _mapID2GatherData.end();it++)
    {
        it->second.ResetLua();
    }

}

void CGatherMgr::Destroy()
{
    _mapID2GatherData.clear();

    _mapID2Gather.clear();
}
