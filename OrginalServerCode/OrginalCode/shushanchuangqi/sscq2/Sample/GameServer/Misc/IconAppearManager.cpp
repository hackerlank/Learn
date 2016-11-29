#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "IconAppearManager.h"
#include "Tokenizer.h"

IconAppearCondBase::IconAppearCondBase(EIconAppearCond eType)
:_eCondType(eType)
{
}

EIconAppearCond IconAppearCondBase::GetCondType()
{
    return _eCondType;
}


IconAppearCondBase::~IconAppearCondBase()
{
}

bool CIconAppearMgr::Init()
{
    return LoadConfig();
}

IconAppearCondTask::IconAppearCondTask(UINT16 wTaskId):IconAppearCondBase(eIconAppearTask),_wTaskId(wTaskId)
{
}

bool IconAppearCondTask::CanOpen(CUser &rUser)
{
    return  rUser.GetTaskPkg().IsTaskPass(_wTaskId);
}

IconAppearCondTask::~IconAppearCondTask()
{
}

IconAppearCondLevel::IconAppearCondLevel(UINT16 wLevel):IconAppearCondBase(eIconAppearTask),_wLevel(wLevel)
{
}

bool IconAppearCondLevel::CanOpen(CUser &rUser)
{
    return rUser.GetLevel() >= _wLevel;
}

IconAppearCondLevel::~IconAppearCondLevel()
{

}
bool CIconAppearMgr::LoadConfig(bool bReload)
{
    if(bReload)
    {
        _mapIconAppearInfo.clear();
        _vecActiveNoneCond.clear();
        _rSetActive.clear();
        _mapActionID.clear();
        _rSetReCharge.clear();
    }
    string strPath = Config._strConfigDir + "Conf/Table/IconAppear.xml";
    CIconAppearLoader oCIconAppearLoader;
    if(!oCIconAppearLoader.LoadData(strPath))
    {
        LOG_CRI << "oCIconAppearLoader fails! Path: " << strPath;
        return false;
    }

    for(size_t i = 0; i < oCIconAppearLoader._vecData.size(); ++i)
    {
        SIconAppearCFG* pIconAppearCfg = oCIconAppearLoader._vecData[i];
        if(pIconAppearCfg->_Type >= eIconAppearMax )
        {
            continue;
        }
        
        if(pIconAppearCfg->_RechageOpen > 0)
        {
            _rSetReCharge.insert(pIconAppearCfg->_ID);
        }

        SIconAppearCFGEx cFgEx(*pIconAppearCfg);
        EIconAppearCond eCond = static_cast<EIconAppearCond>(pIconAppearCfg->_Type);
        if(pIconAppearCfg->_IsActivity == 2)
        {
            _rSetActive.insert(pIconAppearCfg->_ID);
        }
        if(pIconAppearCfg->_activityID != 0)
        {
            _mapActionID[pIconAppearCfg->_activityID] = pIconAppearCfg->_ID;
        }
        switch (eCond)
        {
            case eIconAppearTask:
                {
                    UINT16 wTaskId = atoi(pIconAppearCfg-> _Parameter.c_str());
                    cFgEx._pCond.reset(new IconAppearCondTask(wTaskId));
                }
                break;
            case eIconAppearLevel:
                {
                    UINT16 wLevel = atoi(pIconAppearCfg-> _Parameter.c_str());
                    cFgEx._pCond.reset(new IconAppearCondLevel(wLevel));
                }
                break;
            case eIconAppearNone:
                {
                    if(pIconAppearCfg->_IsActivity == 2)
                    {
                        _vecActiveNoneCond.push_back(pIconAppearCfg->_ID);                    }
                }
            default:
                break;
        }
        _mapIconAppearInfo[eCond].push_back(cFgEx);
    }
    return true;
}

TVecAppearCFGEx * CIconAppearMgr::GetVecAppearCFGEx(EIconAppearCond eCond)
{
    auto it = _mapIconAppearInfo.find(eCond);
    if(it == _mapIconAppearInfo.end())
    {
        return NULL;
    }
    return &(it->second);
}

void CIconAppearMgr::CheckIconAppear(CUser &rUser,EIconAppearCond eCond)
{
    TVecAppearCFGEx* pVec = GetVecAppearCFGEx(eCond);
    if(pVec ==  NULL)
    {
        return ;
    }
    TVecAppearCFGEx& rvec = *pVec;
    TVecUINT16 vecIconAppear;
    for(size_t it = 0; it != rvec.size();it++)
    {
        SIconAppearCFGEx& rCfg = rvec[it];
        if(rCfg._pCond == NULL)
        {
            continue;
        }
        if(rUser.GetPlayer()->IconIsClose(rCfg._ID))
        {
            continue;
        }
        if(rUser.GetPlayer()->CheckIconIsOpen(rCfg._ID))
        {
            continue;
        }
        switch(eCond)
        {
            case eIconAppearTask:
            case eIconAppearLevel:
                {
                    if(rCfg._pCond->CanOpen(rUser))
                    {
                        rUser.GetPlayer()->OpenIcon(rCfg._ID);
                        vecIconAppear.push_back(rCfg._ID);
                    }
                }
                break;
            default:
                break;
        }
            }
    if(!vecIconAppear.empty())
    {
        SynToClientAddIconAppear(rUser,vecIconAppear);
    }

}


void CIconAppearMgr::UserFinishTask(CUser &rUser)
{
    CheckIconAppear(rUser,eIconAppearTask);
}

void CIconAppearMgr::UserLevelUp(CUser &rUser)
{
    CheckIconAppear(rUser,eIconAppearLevel);
}
void CIconAppearMgr::SynToClientAddIconAppear(CUser &rUser,const TVecUINT16& vecIconAppear)
{
    TVecUINT16 _vecActive;
    TVecUINT16 _vecIcon;
    for(auto it = vecIconAppear.begin();it != vecIconAppear.end();it++)
    {
        if(IsActive(*it))
            _vecActive.push_back(*it);
        else
            _vecIcon.push_back(*it); 
    }
    if(!_vecIcon.empty())
    {
        LOG_INF << "Open ICON : " << _vecIcon[0];
        rUser.SendPkg(g_RoleEventProtS.BuildPkg_AddAppearIconNotify(_vecIcon));
    }
    if(!_vecActive.empty())//TODO://根据活动时间判定是否开启
    {
        TVecUINT16 vecIconTmp;
        UINT32 dwActivityID = 0;
        for(auto &it : _vecActive)
        {
            dwActivityID = GetActivityIDByIcon(it);
            if(!dwActivityID)
                continue;
            if(CUserMgr::CheckIcon(dwActivityID))
            {
                vecIconTmp.push_back(it);
                LOG_CRI<<"IconID:"<<it;
            }
        }
        if(!vecIconTmp.empty())
            rUser.SendPkg(g_RoleEventProtS.BuildPkg_AddAppearIconNotify(vecIconTmp));
    }
}
void CIconAppearMgr::DelAction(CUser &rUser,UINT16 wIcon)
{
    rUser.GetPlayer()->DelIcon(wIcon);
    CloseActionToClient(rUser,wIcon);
}
void CIconAppearMgr::CloseActionToClient(CUser &rUser,UINT16 wIcon)
{
    LOG_CRI<<" wIconID="<<wIcon<<",closed";
    rUser.SendPkg(g_RoleEventProtS.BuildPkg_DelAppearIconNotify(wIcon));
}

void CIconAppearMgr::DoActiveIconForOnLine(CUser &rUser)
{
    TVecUINT16 vecIcon;
    rUser.GetPlayer()->GetOpenIcon(vecIcon,true);
    for(auto it =_vecActiveNoneCond.begin(); it != _vecActiveNoneCond.end();it++)
    {
        vecIcon.push_back(*it);
    }
    if(!vecIcon.empty())
    {
        SynToClientAddIconAppear(rUser,vecIcon);
    }
}

bool CIconAppearMgr::IsActivityOpen(CUser& rUser,UINT32 dwActiveID)
{
    UINT16 wIcon = GetIconByActiveID(dwActiveID); 
    TVecUINT16 vecIcon;
    rUser.GetPlayer()->GetOpenIcon(vecIcon,true);
    for(auto it =vecIcon.begin(); it != vecIcon.end();it++)
    {
        if(*it == wIcon)
            return true;
    }
    for(auto it =_vecActiveNoneCond.begin(); it != _vecActiveNoneCond.end();it++)
    {
        if(*it == wIcon)
            return true;
    }
    return false;
}

bool CIconAppearMgr::IsActive(UINT16 wIcon)
{
    return _rSetActive.find(wIcon) != _rSetActive.end();
}
UINT16  CIconAppearMgr::GetIconByActiveID(UINT32 dwActiveID)
{
    auto iter= _mapActionID.find(dwActiveID);
    if(iter == _mapActionID.end())
        return 0;
    return iter->second;
}

UINT32 CIconAppearMgr::GetActivityIDByIcon(UINT16 wIcon)
{
    for(auto &it : _mapActionID)
    {
        if(it.second == wIcon)
            return it.first;
    }
    return 0;
}

void CIconAppearMgr::OpenActionToClientForAll(UINT16 wIcon)
{
    LOG_DBG << "wIconID=" << wIcon << " open.";
    TVecUINT16 vecIcon;
    vecIcon.push_back(wIcon);
    g_RoleEventProtS.SendClt_AddAppearIconNotify(NULL,0,vecIcon);

}

void CIconAppearMgr::CloseActionToClientForAll(UINT16 wIcon)
{
    LOG_DBG << "wIconID=" << wIcon << " closed.";
    g_RoleEventProtS.SendClt_DelAppearIconNotify(NULL,0,wIcon);

}
void CIconAppearMgr::OpenActionToClient(CUser& rUser,TVecUINT16 vecIcon)
{
    rUser.SendPkg(g_RoleEventProtS.BuildPkg_AddAppearIconNotify(vecIcon));
}

void CIconAppearMgr::FinishReCharge(CUser &rUser)
{
    if(rUser.GetTotalRecharge() == 0 )
    {
        return ;
    }
    TVecUINT16 vecIconAppear;
    for(auto it = _rSetReCharge.begin();it != _rSetReCharge.end();
            it++)
    {
        UINT16 wIcon = *it;
        if(rUser.GetPlayer()->IconIsClose(wIcon))
        {
            continue;
        }
        if(rUser.GetPlayer()->CheckIconIsOpen(wIcon))
        {
            continue;
        }
        rUser.GetPlayer()->OpenIcon(wIcon);
        vecIconAppear.push_back(wIcon); 

    }
    if(!vecIconAppear.empty())
    {
        SynToClientAddIconAppear(rUser,vecIconAppear);
    }

}
