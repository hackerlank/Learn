#include "Tokenizer.h"
#include "DgnCondManager.h"
CDgnCondManager g_CDgnCondManager;

bool DgnCondInstance::InitByID(const vector<TVecUINT16>& vecID)
{
    for(auto pos = vecID.begin();pos != vecID.end();pos++)
    {
        const TVecUINT16& vecCond = *pos;
        TVecDungeonCondBasePtr vecSubList;
        for(auto it = vecCond.begin();it != vecCond.end();it++)
        {
            DungeonCondBasePtr pCond =  g_CDgnCondManager.CreateCond(*it);
            if(pCond == NULL)
            {
                return false;
            }
            vecSubList.push_back(pCond);
        }
        if(!vecSubList.empty())
        {
            _vecCond.push_back(vecSubList);
        }
    }
    return true;
}
#define HappenEvent(Event,T,Param1) \
 bool DgnCondInstance::Event(T Param1) \
{\
    bool bSuc = false;\
    bool bPreSuc = true;\
    for(auto it = _vecCond.begin();it != _vecCond.end();it++)\
    { \
        if(!bPreSuc)\
        {\
            break;\
        }\
        TVecDungeonCondBasePtr &ptrVec = *it;\
        for(auto pos = ptrVec.begin();pos != ptrVec.end();pos++)\
        {\
            if((*pos)->Event(Param1))\
            {\
                bSuc = true;\
            }\
        }\
        bPreSuc = IsAllSuc(ptrVec);\
    }\
    return bSuc;\
}
HappenEvent(KillMonster,UINT16,wMonster);
HappenEvent(GatherFinish,UINT16,wGatherId);
HappenEvent(TimerCheck,UINT32,tNow);
HappenEvent(AddTurns,UINT8,wTurns);
HappenEvent(ArriveArea,UINT16,wAreaId);
HappenEvent(FightWithMonster,UINT16,wGroupId); 

void DgnCondInstance::GetStream(TVecMulCond &rMul)
{
    for (auto pos = _vecCond.begin();pos != _vecCond.end();pos++)
    {
        TVecDungeonCondBasePtr & rvec = *pos;
        MulCond mulCnd;;
        for(auto it = rvec.begin();it != rvec.end();it++)
        {
            mulCnd.vecCond.push_back((*it)->GetStream());
        }
        rMul.push_back(mulCnd);
    }
}

bool DgnCondInstance::IsAllSuc()
{
    for(auto it = _vecCond.begin();it != _vecCond.end();it++)
    {
        if(!IsAllSuc(*it))
        {
            return false;
        }
    }
    return true;
}
bool DgnCondInstance::IsAllSuc(TVecDungeonCondBasePtr & rvec) const
{
    for(auto it = rvec.begin();it != rvec.end();it++)
    {
        if((*it)->GetStatus() != eCondSuc)
        {
            return false;
        }
    }
    return true;

}
bool DgnCondInstance::IsOneFail(TVecDungeonCondBasePtr & rvec) const
{
    for(auto it = rvec.begin();it != rvec.end();it++)
    {
        if((*it)->GetStatus() ==  eCondFal)
        {
            return true;
        }
    }
    return false;

}
bool DgnCondInstance::IsOneFail()
{
    for(auto it = _vecCond.begin();it != _vecCond.end();it++)
    {
        if(IsOneFail(*it))
        {
            return true;
        }
    }
    return false;

}

UINT8 DgnCondInstance::GetSucNum()
{
    UINT8 bySuc = 0;
    for(auto it = _vecCond.begin();it != _vecCond.end();it++)
    {
        TVecDungeonCondBasePtr & rvec= *it;
        for(auto pos = rvec.begin();pos != rvec.end();pos++)
        {
            if((*pos)->GetStatus() == eCondSuc)
            {
                bySuc++;
            }
        }
    }
    return bySuc;
}
void DgnCondInstance::GetAllState(vector<EDgnCondStatus> &vecStatus)
{
 for(auto it = _vecCond.begin();it != _vecCond.end();it++)
    {
        TVecDungeonCondBasePtr & rvec= *it;
        for(auto pos = rvec.begin();pos != rvec.end();pos++)
        {
            vecStatus.push_back((*pos)->GetStatus());
        }
    }
}

DungeonCondBasePtr CDgnCondManager::CreateCond(UINT16 wID)
{
    const DungeonAssessCFGEx *pCfg = GetDgnConfig(wID);
    if(NULL == pCfg)
    {
        return NULL;
    }
    switch(pCfg->_eType)
    {
        case eType_SucMonster:
            {
                if(pCfg->_vecParam.size() < 2)
                {
                    return NULL;
                }
                DungeonCondSucMonsterPtr pCond(new DungeonCondSucMonster(wID,pCfg->_vecParam[0],pCfg->_vecParam[1]));
                return pCond; 
            }
            break;
        case eType_SucGather:
            {
                if(pCfg->_vecParam.size() < 2)
                {
                    return NULL;
                }
                DungeonCondSucGatherPtr pCond(new DungeonCondSucGather(wID,pCfg->_vecParam[0],pCfg->_vecParam[1]));
                return pCond;

            }
            break;
        case eType_SucTurns:
            {
                if(pCfg->_vecParam.size() < 1)
                {
                    return NULL;
                }
                DungeonCondSucTurnsPtr pCond(new DungeonCondSucTurns(wID,pCfg->_vecParam[0]));
                return pCond;    
            }
            break;
        case eType_SucInTimer:
            {
                if(pCfg->_vecParam.size() < 1)
                {
                    return NULL;
                }
                DungeonCondSucInTimerPtr pCond(new DungeonCondSucInTimer(wID,pCfg->_vecParam[0]));
                return pCond;
            }
            break;
        case eType_SucMonsterInTimer:
            {
                if(pCfg->_vecParam.size() < 3)
                {
                    return NULL;
                }
                DungeonCondSucMonsterInTimerPtr pCond(new DungeonCondSucMonsterInTimer(wID,pCfg->_vecParam[0],pCfg->_vecParam[1],pCfg->_vecParam[2]));
                return pCond;
            }
            break;
        case eType_SucGatherInTimer:
            {
                if(pCfg->_vecParam.size() < 3)
                {
                    return NULL;
                }
                DungeonCondSucGatherInTimerPtr pCond(new DungeonCondSucGatherInTimer(wID,pCfg->_vecParam[0],pCfg->_vecParam[1],pCfg->_vecParam[2]));
                return pCond; 
            }
            break;
        case eType_SucFightWithMonsterMinTimes:
            {
                if(pCfg->_vecParam.size() < 2)
                {
                    return NULL;
                }
                DungeonCondSucFightWithMonsterMinTimesPtr  pCond(new DungeonCondSucFightWithMonsterMinTimes(wID,pCfg->_vecParam[0],pCfg->_vecParam[1]));
                return pCond;
            }
            break;
        case eType_SucArriveArea:
            {
                if(pCfg->_vecParam.size() < 1)
                {
                    return NULL;
                }
                DungeonCondSucArriveAreaPtr  pCond(new DungeonCondSucArriveArea(wID,pCfg->_vecParam[0]));
                return pCond;
            }
            break;

        default:
            break;
    }
    return NULL;

}

const DungeonAssessCFGEx * CDgnCondManager::GetDgnConfig(UINT16 wID)
{
    auto it = _mapCfg.find(wID);
    if(it == _mapCfg.end())
    {
        return NULL;
    }
    return &(it->second);
}

bool CDgnCondManager::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/DungeonAssess.xml";
    CDungeonAssessLoader oDungeonAssessLoader;
    if(!oDungeonAssessLoader.LoadData(strPath))
    {
        LOG_CRI << "oDungeonAssessLoader.LoadData fails! Path: " << strPath;
        return false;
    }

    for(auto it = oDungeonAssessLoader._vecData.begin();it != oDungeonAssessLoader._vecData.end();++it)
    {
        DungeonAssessCFGEx cFg(*(*it));
        if(cFg._Type == 0 || cFg._Type > 8)
        {
            return false;
        }
        cFg._eType = static_cast<EType_DgnSucCond>(cFg._Type);
        buf::Tokenizer tkPassPara(cFg._TypePara, ',');
        for(size_t i = 0; i < tkPassPara.size();i++)
        {
            cFg._vecParam.push_back(atoi(tkPassPara[i].c_str()));
        }
        UINT8 bySize = cFg._vecParam.size();
        bool bNumIsTrue = false;
        switch (cFg._eType)
        {
            case eType_SucMonster:
                {
                    bNumIsTrue = (bySize >= 2);
                }
                break;
            case eType_SucGather:
                {
                    bNumIsTrue = (bySize >= 2);
                }
                break;
            case eType_SucTurns:
                {
                    bNumIsTrue = (bySize >= 1);
                }
                break;
            case eType_SucInTimer:
                {
                    bNumIsTrue = (bySize >= 1);
                }
                break;
            case eType_SucMonsterInTimer:
                {
                    bNumIsTrue = (bySize >= 3);
                }
                break;
            case eType_SucGatherInTimer:
                {
                    bNumIsTrue = (bySize >= 3);
                }
                break;
            case eType_SucFightWithMonsterMinTimes:
                {
                    bNumIsTrue = (bySize >= 2);
                }
                break;
            case eType_SucArriveArea:
                {
                    bNumIsTrue = (bySize >= 1);
                }
                break;

            default :
                break;
        }
        if(!bNumIsTrue)
        {
            LOG_CRI << "DungeonAssess ERR :" << cFg._ID;
        }
        _mapCfg[cFg._ID] = cFg;
    }
    return true;
}

