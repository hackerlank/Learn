#include "stdafx.h"
#include "Protocols.h"
#include "Player.h"
#include "User.h"
#include "LevelPrizeAct.h"
#include "SysMsgDefine.h"

CLevelPrizeAct::CLevelPrizeAct(CPlayer &rPlayer):
    CRegiserterEvent(eActClass_LevelPrize,rPlayer),
    _rPlayer(rPlayer)
{
    _setEventIDs.clear();
}
void CLevelPrizeAct::OnEvent(SEventInfoPtr pEventInfoPtr)
{
    bool bUpdate = true;
    UINT32 dwEventID = pEventInfoPtr->dwEventInstID;
    UINT16 _wID = static_cast<UINT16>(pEventInfoPtr->dwApplyID); 
    if(pEventInfoPtr->wEventStatus == eEventStatus_Finish)
       _setEventIDs.insert(dwEventID);
    else 
        return ;
    SActInfoExPtr sInfo = g_WondActMgr.GetActInfo(_wID);
    if(sInfo)
    {
        SActConfigExPtr sConfig = g_WondActMgr.GetActConfig(sInfo->wConfigID);
        if(sConfig)
        {
            TVecID2PrizePtr vecID2Prize = sConfig->vecPrizes;
            for(UINT8 i=0; i<vecID2Prize.size(); ++i)
            {
                SID2PrizePtr pID2Prize = vecID2Prize.at(i);
                TVecUINT32 vecConds = pID2Prize->vecConds;
                for(auto it=vecConds.begin(); it!=vecConds.end(); ++it)
                {
                    if(!_setEventIDs.count(*it))
                        bUpdate = false;
                    if(!bUpdate)
                        break;
                }
                if(bUpdate)
                {
                    SPrize2DB sPrize;
                    sPrize.qwRoleID = _rPlayer.GetRoleID();
                    sPrize.wActID = pEventInfoPtr->dwApplyID;
                    sPrize.wLevel = (i+1);
                    if(!CheckFinish(sPrize.qwRoleID,sPrize.wActID,sPrize.wLevel))
                    {
                        sPrize.wStatus = 1;
                        Update2DB(sPrize,eOpAdd);
                        _vecPrize2DB.push_back(sPrize);
                        _rPlayer.SendPkg(g_LevelPrizeSvrS.BuildPkg_SendReachCondNfy(_wID,(i+1)));
                    }
                }
            }
        }
    }
}
bool CLevelPrizeAct::CheckFinish(UINT64 qwRoleID,UINT16 wActID,UINT16 wLevel)
{
   for(auto it=_vecPrize2DB.begin(); it!=_vecPrize2DB.end(); ++it)
   {
       SPrize2DB sPrize = *it;
       if(sPrize.qwRoleID ==  qwRoleID 
          && sPrize.wActID ==  wActID
          && sPrize.wLevel ==  wLevel)
       {
           return true;
       }
   }
   return false;
}

bool CLevelPrizeAct::LoadFromDB(const RoleDataInfo& rRoleDataInfo)
{
    _vecPrize2DB.clear();
   for(UINT8 i=0; i<rRoleDataInfo.vecLevelPrize.size(); ++i)
   {
       SPrize2DB sPrize = rRoleDataInfo.vecLevelPrize[i];
       _vecPrize2DB.push_back(sPrize);
   }

   RegisterEventInit(); 

   return true;
}
void CLevelPrizeAct::SetPrizeState(UINT8 wID,UINT8 byState)
{
   for(auto it= _vecPrize2DB.begin(); it!= _vecPrize2DB.end(); ++it)
   {
       if(it->wLevel == wID)
           it->wStatus = byState ;
   }
}
void CLevelPrizeAct::Update2DB(SPrize2DB& rInfo, EDataChange eDataChange/* = eOpUpdate*/)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeLevelPrize, eDataChange, strData);
}
TVecPrize2DB& CLevelPrizeAct::GetPrize2DB()
{
    return _vecPrize2DB;
}
void CLevelPrizeAct::RegisterActEvent(UINT16 _wID,UINT8 byIndex,TVecUINT32& vecConds)
{
    bool bFinish = true;

    for(size_t i=0; i<vecConds.size(); ++i)
    {
        AddEvent(vecConds[i],_wID,ThisDayZero());
        if(!IsFinish(vecConds[i],_wID))
        {
            bFinish = false;
        }else
        {
            _setEventIDs.insert(vecConds[i]);
        }
    }

    if(bFinish)
    {
        //process finish
        SPrize2DB sPrize;
        sPrize.qwRoleID = _rPlayer.GetRoleID();
        sPrize.wActID = 2;
        sPrize.wLevel = byIndex;
        if(!CheckFinish(sPrize.qwRoleID,sPrize.wActID,sPrize.wLevel))
        {
            sPrize.wStatus = 1;
            Update2DB(sPrize,eOpAdd);
            _vecPrize2DB.push_back(sPrize);
            _rPlayer.SendPkg(g_LevelPrizeSvrS.BuildPkg_SendReachCondNfy(_wID,byIndex));
        }
        //after
        RemoveActEvent(_wID,vecConds);
    }
}
UINT8 CLevelPrizeAct::GetPrizeStateByID(UINT8 byIndex)
{
    for(UINT8 i=0;  i<_vecPrize2DB.size(); ++i)
    {
        if(_vecPrize2DB[i].wLevel == byIndex)
            return _vecPrize2DB[i].wStatus;
    }
    return 0;
}
ELevelActStatus CLevelPrizeAct::TakePrize(UINT16 _wID,UINT8 byIndex)
{
    for(auto it=_vecPrize2DB.begin(); it!=_vecPrize2DB.end(); ++it)
    {
        if(it->wLevel == byIndex)
        {
            if(it->wStatus == 2)
                return eLevleActStatus_Error;
            else if(it->wStatus == 0)
                return eLevleActStatus_Init;
            else
            {
                TVecItemGenInfo vecItems;
                TVecUINT32 vecConds;
                if(!g_WondActMgr.GetPrizeByID(_wID,byIndex,vecItems))
                {
                    return eLevleActStatus_Error;
                }
                if(!g_WondActMgr.GetConds(_wID,byIndex,vecConds))
                {
                    return eLevleActStatus_Error;
                }
                CUserPtr pUser = CUserMgr::GetUserByUserID(_rPlayer.GetUserID());
                CPack &rPack = pUser->GetPack();
                if(!vecItems.empty())
                {
                    if(!rPack.CanAddItem(vecItems))
                        return eLevleActStatus_FullPack;
                    else
                    {
                        rPack.AddItem(vecItems, NLogDataDefine::ItemFrom_ExchangeItem);
                        LOG_INF << "Person LevelPrize Suc.";
                    }
                }
                it->wStatus = 2;
                Update2DB(*it,eOpUpdate);
                RemoveActEvent(_wID,vecConds);
                break; 
            }
        }
    }
    return eLevleActStatus_GetPrize;
}

void CLevelPrizeAct::RegisterEvent(UINT16 _wID)
{

    SActInfoExPtr sInfo = g_WondActMgr.GetActInfo(_wID);
    if(sInfo)
    {
        SActConfigExPtr sConfig = g_WondActMgr.GetActConfig(sInfo->wConfigID);
        if(sConfig)
        {
            TVecID2PrizePtr vecID2Prize = sConfig->vecPrizes;
            for(UINT8 i=0; i<vecID2Prize.size(); ++i)
            {
                SID2PrizePtr pID2Prize = vecID2Prize.at(i);
                TVecUINT32 vecConds = pID2Prize->vecConds;
                RegisterActEvent(_wID,i+1,vecConds);
            }
        }
    }
}
void CLevelPrizeAct::RemoveActEvent(UINT16 _wID,TVecUINT32 &vecConds)
{
    for(auto it=vecConds.begin(); it!=vecConds.end(); ++it)
    {
        RemoveEvent(*it,_wID);
        if(_setEventIDs.count(*it))
            _setEventIDs.erase(*it);
    }
}
void CLevelPrizeAct::RemoveAllEvent(UINT16 _wID)
{
    SActInfoExPtr sInfo = g_WondActMgr.GetActInfo(_wID);
    if(sInfo)
    {
        SActConfigExPtr sConfig = g_WondActMgr.GetActConfig(sInfo->wConfigID);
        if(sConfig)
        {
            TVecID2PrizePtr vecID2Prize = sConfig->vecPrizes;
            for(UINT8 i=0; i<vecID2Prize.size(); ++i)
            {
                SID2PrizePtr pID2Prize = vecID2Prize.at(i);
                TVecUINT32 vecConds = pID2Prize->vecConds;
                RemoveActEvent(_wID,vecConds);
            }
        }
    }
}

UINT32 CLevelPrizeAct::ThisDayZero()
{
    time_t now = Time::Now();
    return Time::TheDay(1,now);
}

void CLevelPrizeAct::ClearPrize2DB(SPrize2DB sPrize)
{
    for(auto oIt= _vecPrize2DB.begin(); oIt!=_vecPrize2DB.end();)
    {
        auto it = oIt;
        oIt ++;
        if(oIt->qwRoleID == sPrize.qwRoleID 
           && oIt->wActID == sPrize.wActID 
           && oIt->wLevel == sPrize.wLevel)
        {
            _vecPrize2DB.erase(it);
        }

    }
}
