#include "stdafx.h"
#include "Task.h"
#include "TaskPkg.h"
#include "Protocols.h"
#include "ItemMgr.h"
#include "Player.h"
#include "User.h"
//#include "LogMgr.h"
#include "MapMgr.h"
//#include "MercenMgr.h"
#include "TaskMgr.h"
#include "Monster.h"
#include "IconAppearManager.h"
#include "FighterManager.h"
#include "HorseMgr.h"
#include "Tokenizer.h"
#include "GroupTaskManager.h"
#include "YaMenTaskManager.h"
#include "VIPMgr.h"
#include "Trump.h"
#include "HeroFighter.h"
#include "BeautyMgr.h"
STaskConfig& CTask::GetConfig() 
{
    /*
       if(CTaskMgr::GetVersion() != _qwVersion)
       {
       _pTaskConf = CTaskMgr::GetTaskConfig(_pTaskConf->wID);
       }
       */

    return *_pTaskConf;
}
void CTask::ToRoleTaskInfo(RoleTaskInfo& rTaskInfo)
{
    rTaskInfo.eTaskState = _eTaskState;
    rTaskInfo.dwLastAcceptTimer =_dwAcceptTime; 
    rTaskInfo.dwRepeatAcceptTimes = _byAcceptTimes;
    UINT8 byCount = 0;
    for(auto iter = _mapType2Info.begin();iter != _mapType2Info.end() && byCount < 3;iter++,byCount++)
    {
        if(byCount == 0)
        {
            SetTaskInfo(iter->second,rTaskInfo.byProcessType1,rTaskInfo.dwProcessParam11,rTaskInfo.dwProcessParam12);
        }
        else if(byCount == 1)
        {
            SetTaskInfo(iter->second,rTaskInfo.byProcessType2,rTaskInfo.dwProcessParam21,rTaskInfo.dwProcessParam22);
        }
        else if(byCount == 2 )
        {
            SetTaskInfo(iter->second,rTaskInfo.byProcessType3,rTaskInfo.dwProcessParam31,rTaskInfo.dwProcessParam32);
        }
    }
}
void CTask::SetTaskInfo(STaskInfoPtr pInfo ,UINT8 &byType,UINT32 &dwParam1,UINT32 &dwParam2)
{
    byType = pInfo->GetClassType(); 
    switch(byType) 
    {
        case eType_STaskCollectInfo:
            {
                STaskCollectInfoPtr ptr = dynamic_pointer_cast<STaskCollectInfo>(pInfo);
                if(ptr)
                {
                    dwParam1 = ptr->wItemID;
                }
            }
            break;
        case eType_STaskGatherInfo:
            {
                STaskGatherInfoPtr ptr = dynamic_pointer_cast<STaskGatherInfo>(pInfo);
                if(ptr)
                {
                    dwParam1 = ptr->wGatherID;
                    dwParam2 = ptr->wCount;
                }

            }
            break;
        case eType_STaskMonsterInfo:
            {
                STaskMonsterInfoPtr ptr = dynamic_pointer_cast<STaskMonsterInfo>(pInfo);
                if(ptr)
                {
                    dwParam1 = ptr->wMonsterID;
                    dwParam2 = ptr->wMonsterCount;
                }
            }
            break;
        case eType_STaskTalkInfo:
            {
                STaskTalkInfoPtr ptr = dynamic_pointer_cast<STaskTalkInfo>(pInfo);
                if(ptr)
                {
                    dwParam1 = ptr->wNpcID;
                    dwParam2 = ptr->wTalkCount;
                }
            }
            break;
        case eType_STaskProbeInfo:
            {
                STaskProbeInfoPtr ptr = dynamic_pointer_cast<STaskProbeInfo>(pInfo);
                if(ptr)
                {
                    dwParam1 = ptr->byIndex;
                    dwParam2 = ptr->bProbed ? 1:0;
                }

            }
            break;
        case eType_STaskBuildInfo:
            {
#if 0
                STaskBuildInfoPtr ptr = dynamic_pointer_cast<STaskBuildInfo>(pInfo);
                if(ptr)
                {
                    dwParam1 = ptr->wBuildID;
                }
#endif
            }
            break;
        case eType_STaskScienceInfo:
            {
#if 0            
                STaskScienceInfoPtr ptr = dynamic_pointer_cast<STaskScienceInfo>(pInfo);
                if(ptr)
                {
                    dwParam1 = ptr->wScienceID;
                }
#endif 
            }
            break;
        case eType_STaskActionInfo:
            {
                STaskActionInfoPtr  ptr = dynamic_pointer_cast<STaskActionInfo>(pInfo);
                if(ptr)
                {
                    dwParam1 = ptr->wAction;
                    dwParam2 = ptr->wCount;
                }

            }
            break;
        case eType_STaskGrowInfo:
            {
                STaskGrowInfoPtr  ptr = dynamic_pointer_cast<STaskGrowInfo>(pInfo);
                if(ptr)
                {
                    dwParam1 = ptr->wType;
                }

            }
        default:	
            break;
    }



}
STaskInfoPtr CTask::GetTaskInfo(UINT8 byType,UINT32 dwParam1,UINT32 dwParam2)
{
    switch(byType) 
    {
        case eType_STaskCollectInfo:
            {
                STaskCollectInfoPtr pTaskCollectInfo(new STaskCollectInfo);
                if(pTaskCollectInfo == NULL)
                    break;
                UINT16 wItemID = dwParam1;
                pTaskCollectInfo->wItemID = wItemID;
                pTaskCollectInfo->wItemCount = _rTaskPkg.GetUserPack().GetItemCount(wItemID);
                return  pTaskCollectInfo;

            }
            break;
        case eType_STaskGatherInfo:
            {
                STaskGatherInfoPtr pTaskGatherInfo(new STaskGatherInfo);
                if(pTaskGatherInfo == NULL)
                    break;
                pTaskGatherInfo->wGatherID =  dwParam1;
                pTaskGatherInfo->wCount = dwParam2;
                return  pTaskGatherInfo;
            }
            break;
        case eType_STaskMonsterInfo:
            {
                STaskMonsterInfoPtr pTaskMonsterInfo(new STaskMonsterInfo);
                if(pTaskMonsterInfo == NULL)
                    break;
                pTaskMonsterInfo->wMonsterID = dwParam1;
                pTaskMonsterInfo->wMonsterCount = dwParam2;
                return  pTaskMonsterInfo;
            }
            break;
        case eType_STaskTalkInfo:
            {
                STaskTalkInfoPtr pTaskTalkInfo(new STaskTalkInfo);
                if(pTaskTalkInfo == NULL)
                    break;
                pTaskTalkInfo->wNpcID =dwParam1;
                pTaskTalkInfo->wTalkCount = dwParam2;
                return  pTaskTalkInfo;
            }
            break;
        case eType_STaskProbeInfo:
            {
                STaskProbeInfoPtr pTaskProbeInfo(new STaskProbeInfo);
                if(pTaskProbeInfo == NULL)
                    break;
                pTaskProbeInfo->byIndex =  dwParam1;
                pTaskProbeInfo->bProbed = dwParam2 > 0;
                return  pTaskProbeInfo;

            }
            break;
        case eType_STaskBuildInfo:
            {
#if 0
                STaskBuildInfoPtr pTaskBuildInfo(new STaskBuildInfo);
                if(pTaskBuildInfo == NULL)
                    break;
                pTaskBuildInfo->wBuildID = (UINT16)dwParam1;
                _mapType2Info.insert(make_pair(eType_STaskBuildInfo, pTaskBuildInfo));
#endif
            }
            break;
        case eType_STaskScienceInfo:
            {
#if 0            
                STaskScienceInfoPtr pTaskScienceInfo(new STaskScienceInfo);
                if(pTaskScienceInfo == NULL)
                    break;
                pTaskScienceInfo->wScienceID = (UINT8)dwParam1;
                pTaskScienceInfo->wLevel = _rTaskPkg.GetUser().GetLibrary().GetTechLevel((UINT8)pTaskScienceInfo->wScienceID);
                _mapType2Info.insert(make_pair(eType_STaskScienceInfo, pTaskScienceInfo));
#endif 
            }
            break;
        case eType_STaskActionInfo:
            {
                STaskActionInfoPtr pTaskActionInfo(new STaskActionInfo);
                if(pTaskActionInfo == NULL)
                    break;
                pTaskActionInfo->wAction = (UINT16)dwParam1;
                pTaskActionInfo->wCount = (UINT16)dwParam2;
                switch(pTaskActionInfo->wAction)
                {
#if 0
                    case eProcessAction_JoinGuild:     //加入公会
                        {
                            if (_rTaskPkg.GetUser().GetGuildID() > 0)
                                pTaskActionInfo->wCount = 1;
                        }
                        break;
                    case eProcessAction_JoinFamily:      //加入家族
                        {
                            if (_rTaskPkg.GetUser().GetFamilyID() > 0)
                                pTaskActionInfo->wCount = 1;
                        }
                        break;

                    case eProcessAction_MercenUp:      //佣兵升阶
                        {
                            pTaskActionInfo->wCount = _rTaskPkg.GetUser().GetAllMercenUpClassTotal();
                        }
                        break;
#endif
                    default:
                        break;
                }
                return  pTaskActionInfo;

            }
            break;
        case eType_STaskGrowInfo:
            {
                CPlayerPtr pPlayer = _rTaskPkg.GetPlayer();
                STaskGrowInfoPtr pTaskGrowInfo(new STaskGrowInfo);
                if(pTaskGrowInfo == NULL)
                    break;
                pTaskGrowInfo->wType = (UINT16)dwParam1;
                switch(pTaskGrowInfo->wType)
                {
                    case eProcessRoleProperty_level:     //等级
                        {
                            if(pPlayer != NULL)
                                pTaskGrowInfo->wLevel = pPlayer->GetLevel();
                        }
                        break;
                    case eProcessRoleProperty_repute:    //声望
                        break;
#if 0
                    case eProcessRoleProperty_contri:    //贡献
                        break;
                    case eProcessRoleProperty_mercen:	 //佣兵
                        {
                            pTaskGrowInfo->wLevel = _rTaskPkg.GetUser().GetAllMercenUpClass((UINT16)GetConfig().vecRoleProps[i].dwExtID);
                        }
                        break;
#endif
                    default:
                        return NULL;
                }
                return pTaskGrowInfo;

            }
            break;
    }
    return NULL;
}
void CTask::SynData(RoleTaskInfo& rTaskInfo)
{
    ToRoleTaskInfo(rTaskInfo);
    _rTaskPkg.UpdateRoleTaskInfo(rTaskInfo);
}
void CTask::FromRoleTaskInfo(const RoleTaskInfo& rTaskInfo)
{
    _eTaskState  = rTaskInfo.eTaskState ;
    _byAcceptTimes = rTaskInfo.dwRepeatAcceptTimes;

    _dwAcceptTime = rTaskInfo.dwLastAcceptTimer; 
    STaskInfoPtr pTaskInfo = GetTaskInfo(rTaskInfo.byProcessType1,rTaskInfo.dwProcessParam11,rTaskInfo.dwProcessParam12);
    EType_STaskInfo eType1 = static_cast<EType_STaskInfo>(rTaskInfo.byProcessType1);
    if(NULL != pTaskInfo)
    {
        _mapType2Info.insert(make_pair(eType1,pTaskInfo));
    }
    pTaskInfo = GetTaskInfo(rTaskInfo.byProcessType2,rTaskInfo.dwProcessParam21,rTaskInfo.dwProcessParam22);
    EType_STaskInfo eType2 = static_cast<EType_STaskInfo>(rTaskInfo.byProcessType2);
    if(NULL != pTaskInfo)
    {
        _mapType2Info.insert(make_pair(eType2,pTaskInfo));
    }
    pTaskInfo = GetTaskInfo(rTaskInfo.byProcessType3,rTaskInfo.dwProcessParam31,rTaskInfo.dwProcessParam32);
    EType_STaskInfo eType3 = static_cast<EType_STaskInfo>(rTaskInfo.byProcessType3);
    if(NULL != pTaskInfo)
    {
        _mapType2Info.insert(make_pair(eType3,pTaskInfo));
    }

}

void CTask::GetTaskInfoList(TVecTaskInfo& vecTaskInfo) const
{
    for(auto it = _mapType2Info.begin(); it != _mapType2Info.end(); ++it)
    {
        STaskInfoPtr pTaskInfo = it->second;
        vecTaskInfo.push_back(pTaskInfo);
    }
}

bool CTask::Init()
{
    if((GetConfig().dwContentType & eContentCollect) != 0)
    {
        for(size_t i = 0; i < GetConfig().vecItemCollect.size(); ++i)
        {
            const SCollectItem& rCollectItem = GetConfig().vecItemCollect[i];
            STaskCollectInfoPtr pTaskCollectInfo(new STaskCollectInfo);
            if(pTaskCollectInfo == NULL)
                goto FAIL;
            UINT16 wItemID = rCollectItem.wItemID;
            pTaskCollectInfo->wItemID = wItemID;
            pTaskCollectInfo->wItemCount = _rTaskPkg.GetUserPack().GetItemCount(wItemID);
            _mapType2Info.insert(make_pair(eType_STaskCollectInfo, pTaskCollectInfo));
        }
    }

    if((GetConfig().dwContentType & eContentGather) != 0)
    {
        for(size_t i = 0; i < GetConfig().vecGather.size(); ++i)
        {
            const SIdxCount& rIdxCount = GetConfig().vecGather[i];
            STaskGatherInfoPtr pTaskGatherInfo(new STaskGatherInfo);
            if(pTaskGatherInfo == NULL)
                goto FAIL;
            UINT16 wGatherID = (UINT16)rIdxCount.dwIdx;
            pTaskGatherInfo->wGatherID = wGatherID;
            pTaskGatherInfo->wCount = 0;
            _mapType2Info.insert(make_pair(eType_STaskGatherInfo, pTaskGatherInfo));
        }
    }

    if((GetConfig().dwContentType & eContentTalk) != 0)
    {
        for(auto it = GetConfig().mapNpc2Talk.begin(); it != GetConfig().mapNpc2Talk.end(); ++it)
        {
            UINT16 wNpcID = (UINT16)it->first;
            STaskTalkInfoPtr pTaskTalkInfo(new STaskTalkInfo);
            if(pTaskTalkInfo == NULL)
                goto FAIL;
            pTaskTalkInfo->wNpcID = wNpcID;
            _mapType2Info.insert(make_pair(eType_STaskTalkInfo, pTaskTalkInfo));
        }
    }

    if((GetConfig().dwContentType & eContentKill) != 0)
    {
        for(size_t i = 0; i < GetConfig().vecMonsterKill.size(); ++i)
        {
            const SKillMonster& rKillMonster = GetConfig().vecMonsterKill[i];
            STaskMonsterInfoPtr pTaskMonsterInfo(new STaskMonsterInfo);
            if(pTaskMonsterInfo == NULL)
                goto FAIL;
            pTaskMonsterInfo->wMonsterID = rKillMonster.wMonsterID;
            _mapType2Info.insert(make_pair(eType_STaskMonsterInfo, pTaskMonsterInfo));
        }
    }

    if((GetConfig().dwContentType & eContentProbe) != 0)
    {
        for(size_t i = 0; i < GetConfig().vecProbe.size(); ++i)
        {
            STaskProbeInfoPtr pTaskProbeInfo(new STaskProbeInfo);
            if(pTaskProbeInfo == NULL)
                goto FAIL;
            pTaskProbeInfo->byIndex = (UINT8)i;
            _mapType2Info.insert(make_pair(eType_STaskProbeInfo, pTaskProbeInfo));
        }
    }

    if((GetConfig().dwContentType & eContentBehave) != 0)
    {
        for(size_t i = 0; i < GetConfig().vecRoleActions.size(); ++i)
        {
            const SProcessAction& rProcessAction = GetConfig().vecRoleActions[i];
            STaskActionInfoPtr pTaskActionInfo(new STaskActionInfo);
            if(pTaskActionInfo == NULL)
                goto FAIL;
            pTaskActionInfo->wAction = rProcessAction.type;
            if(CheckTaskAction(pTaskActionInfo->wAction,rProcessAction.param) == 0)
            {
                pTaskActionInfo->wCount = 1;
            }
            _mapType2Info.insert(make_pair(eType_STaskActionInfo, pTaskActionInfo));

        }
    }

    if((GetConfig().dwContentType & eContentGrow) != 0)
    {
        CPlayerPtr pPlayer = _rTaskPkg.GetPlayer();
        for(size_t i = 0; i < GetConfig().vecRoleProps.size(); ++i)
        {
            STaskGrowInfoPtr pTaskGrowInfo(new STaskGrowInfo);
            if(pTaskGrowInfo == NULL)
                goto FAIL;
            pTaskGrowInfo->wType = (UINT16)GetConfig().vecRoleProps[i].type;
            switch(GetConfig().vecRoleProps[i].type)
            {
                case eProcessRoleProperty_level:     //等级
                    {
                        if(pPlayer != NULL)
                            pTaskGrowInfo->wLevel = pPlayer->GetLevel();
                    }
                    break;
                case eProcessRoleProperty_repute:    //声望
                    break;
#if 0
                case eProcessRoleProperty_contri:    //贡献
                    break;
                case eProcessRoleProperty_mercen:	 //佣兵
                    {
                        pTaskGrowInfo->wLevel = _rTaskPkg.GetUser().GetAllMercenUpClass((UINT16)GetConfig().vecRoleProps[i].dwExtID);
                    }
                    break;
#endif
                default:
                    break;
            }
            _mapType2Info.insert(make_pair(eType_STaskGrowInfo, pTaskGrowInfo));
        }
    }

    /*if((GetConfig().dwContentType & eContentBuild) != 0)
      {
      for(size_t i = 0; i < GetConfig().vecBuildings.size(); ++i)
      {
      STaskBuildInfoPtr pTaskBuildInfo(new STaskBuildInfo);
      if(pTaskBuildInfo == NULL)
      goto FAIL;
      pTaskBuildInfo->wBuildID = (UINT16)GetConfig().vecBuildings[i].dwIdx;
      _mapType2Info.insert(make_pair(eType_STaskBuildInfo, pTaskBuildInfo));
      }
      }*/
#if 0
    if((GetConfig().dwContentType & eContentTechnics) != 0)
    {
        for(size_t i = 0; i < GetConfig().vecTechnics.size(); ++i)
        {
            STaskScienceInfoPtr pTaskScienceInfo(new STaskScienceInfo);
            if(pTaskScienceInfo == NULL)
                goto FAIL;
            pTaskScienceInfo->wScienceID = (UINT16)GetConfig().vecTechnics[i].dwIdx;
            pTaskScienceInfo->wLevel = _rTaskPkg.GetUser().GetLibrary().GetTechLevel((UINT8)pTaskScienceInfo->wScienceID);
            _mapType2Info.insert(make_pair(eType_STaskScienceInfo, pTaskScienceInfo));
        }
    }
#endif
    return true;
FAIL:
    _mapType2Info.clear();
    return false;
}
CTask::~CTask()
{
}
bool CTask::RefreshSurroundTaskMonster(bool bAccept)
{
    CPlayerPtr pPlayer = _rTaskPkg.GetUser().GetPlayer();
    if(NULL == pPlayer)
        return false;
    CGameMapPtr pMap = pPlayer->GetMap();
    if(pMap == NULL)
        return false;
    if(pMap->GetMapInfo().IsDungeon())
        return false;
    TVecUINT16 vecMonsterID;
    for(auto& rKillMonster : GetConfig().vecMonsterKill)
        vecMonsterID.push_back(rKillMonster.wMonsterID);
    for(auto& rCollectItem : GetConfig().vecItemCollect)
    {
        UINT16 wMonsterID = rCollectItem.wMonsterID;
        if(wMonsterID != 0)
            vecMonsterID.push_back(wMonsterID);
    }
    if(vecMonsterID.empty())
        return false;
    vector<CMonsterPtr> vecMonster;
    pMap->GetSurroundObject(eVisitAllMonster, *pPlayer, vecMonster);
    multimap<UINT16, CMonsterPtr> mapID2Monster;
    for(auto& pMonster : vecMonster)
        mapID2Monster.insert(make_pair(pMonster->GetMonsterID(), pMonster));
    set<CBaseObjPtr> setObj;
    for(UINT16 wMonsterID : vecMonsterID)
    {
        for(auto it = mapID2Monster.lower_bound(wMonsterID), itUB = mapID2Monster.upper_bound(wMonsterID); it != itUB; ++it)
        {
            CMonsterPtr pMonster = it->second;
            if(bAccept)
            {
                if(!pPlayer->CanSee(*pMonster))
                    setObj.insert(pMonster);
            }
            else
            {
                if(pPlayer->CheckFinishMonsterTask(*pMonster, GetTaskID()))
                    setObj.insert(pMonster);
            }
        }
    }
    if(bAccept)
        g_MapProtS.NotifySurroundAppear(*pPlayer, setObj);
    else
        g_MapProtS.NotifySurroundDisappear(*pPlayer, setObj);
    return true;
}

bool CTask::OnAccept(bool bNotify/* = true*/)
{
    auto it = GetConfig().vecItemGive.begin();
    TVecItemGenInfo vecItemGen;
#if 0
    TVecLogItemData vecData;
#endif
    for(;it != GetConfig().vecItemGive.end();it++)
    {
        if(it->dwIdx == 0 || it->wCount == 0)
            continue;
        SItemGenInfo oItemGenInfo;
        oItemGenInfo.eBindType = eBindGet;
        oItemGenInfo.dwCount = it->wCount;
        oItemGenInfo.wItemID = (UINT16)it->dwIdx;
        vecItemGen.push_back(oItemGenInfo);
#if 0 
        SLogItemData oTemp(oItemGenInfo.wItemID, oItemGenInfo.dwCount, oItemGenInfo.byQuality);
        vecData.push_back(oTemp);
#endif
    }
    if(!vecItemGen.empty() && !_rTaskPkg.GetUserPack().AddItem(vecItemGen,NLogDataDefine::ItemFrom_Task))
        return false;

    CPlayerPtr pPlayer = _rTaskPkg.GetUser().GetPlayer();
#if 0
    if(NULL != pPlayer && !vecData.empty())
        ItemLog.LogItemOper(LogOPID, *pPlayer, eItemLog_Gain, eOperLog_Task, vecData);
#endif
    RefreshSurroundTaskMonster(true);
    CheckStateAndUpdate(false);
    if(bNotify)
    {
        //同步添加任务
        _rTaskPkg.GetUser().SendPkg(g_TaskProtS.BuildPkg_AddTaskAck(0,ToStask()));
    }
    return true;
}

STask CTask::ToStask()
{
    STask task;
    task.eTaskState =_eTaskState;
    task.wTaskID = GetTaskID();
    task.dwAcceptTime = _dwAcceptTime;
    task.byRepeat = _byAcceptTimes;
    GetTaskInfoList(task.vecTaskInfo);
    return task;
}
void CTask::OnGiveUp()
{
    //删除掉任务给予的道具
    //	UINT32 dwOPID = LogOPID;
    auto it = GetConfig().vecItemGive.begin();
    for(;it != GetConfig().vecItemGive.end();it++)
    {
        if(it->dwIdx == 0 || it->wCount == 0)
            continue;
        _rTaskPkg.GetUserPack().DelItemByItemID((UINT16)it->dwIdx, it->wCount, true, NLogDataDefine::ItemTo_Task);
#if 0
        CPlayerPtr pPlayer = _rTaskPkg.GetPlayer();
        if(NULL != pPlayer)
            ItemLog.LogItemOper(dwOPID, *pPlayer, eItemLog_Drop, eOperLog_Task, SLogItemData((UINT16)it->dwIdx, it->wCount, 0));
#endif        
    }
    RoleTaskInfo * pTaskRecord = _rTaskPkg.GetRoleTaskInfo(GetTaskID());
    if(NULL == pTaskRecord)
        return ;
    _eTaskState = eTaskNone;
    SynData(*pTaskRecord);

}

ETaskResult CTask::OnFinish(UINT8 byIndex,UINT8 &byAcceptTimes,bool bForce)
{
    ETaskResult eResult;
    CUser& rUser = _rTaskPkg.GetUser();
    CPlayerPtr pPlayer = rUser.GetPlayer();
    if (NULL == pPlayer)
        return eTaskErrOther;
    RoleTaskInfo * pTaskRecord = _rTaskPkg.GetRoleTaskInfo(GetTaskID());
    if(NULL == pTaskRecord)
        return eTaskNotExist;
    //扣钱
    if(bForce)
    {
        switch (GetConfig().eTaskType) 
        {
            case eTaskForGroup:
                {
                    if(!rUser.CanSubMoney(EMONEY_GOLD,SParamConfig::dwFinishShiMenTaskCost))
                    {
                        return eTaskNoGold;
                    }
                }
                break;
            case eTaskForYaMen:
                {
                    if(!rUser.CanSubMoney(EMONEY_GOLD,SParamConfig::dwFinishYaMenTaskCost))
                    {
                        return eTaskNoGold;
                    }
                }
                break;
            case eTaskCircle:
                {
                    if(!rUser.CanSubMoney(EMONEY_GOLD,SParamConfig::wCircleTaskFinishOne))
                    {
                        return eTaskNoGold;
                    }
                }
                break;

            default:
                return eTaskErrOther; 
        }
    }
    eResult = OnGiveAward(byIndex,bForce);
    if(eTaskSucceed == eResult)
    {
        //给予奖励
        if(bForce)
        {

            switch (GetConfig().eTaskType) 
            {
                case eTaskForGroup:
                    {
                        rUser.SubMoney(EMONEY_GOLD,SParamConfig::dwFinishShiMenTaskCost,NLogDataDefine::ItemTo_TaskForGroupAward);
                    }
                    break;
                case eTaskForYaMen:
                    {
                        rUser.SubMoney(EMONEY_GOLD,SParamConfig::dwFinishYaMenTaskCost,NLogDataDefine::ItemTo_TaskForYaMenAward);
                    }
                    break;
                case eTaskCircle:
                    {
                        rUser.SubMoney(EMONEY_GOLD,SParamConfig::wCircleTaskFinishOne,NLogDataDefine::ItemTo_CircleOneKey);
                    }
                    break;

                default:
                    break;
            }
        }
        byAcceptTimes = bForce ? 1:_byAcceptTimes;
        pTaskRecord->dwFinishTimes += byAcceptTimes;
        pTaskRecord->dwLastFinishTimer = (UINT32)time(NULL);
        AwardGeneral(rUser, *pPlayer,bForce);
        _byAcceptTimes -= byAcceptTimes;
        if(_byAcceptTimes == 0)
        {
            _eTaskState = eTaskNone; 
            pTaskRecord->dwRepeatAcceptTimes = 0;
        }
        else
        {
            pTaskRecord->dwRepeatAcceptTimes = _byAcceptTimes;
        }
        SynData(*pTaskRecord);        
        NotifyTaskFinish();  

    }
    return eResult;
}

void CTask::NotifyTaskFinish()
{
    CIconAppearMgr::Instance().UserFinishTask(_rTaskPkg.GetUser());
}
ETaskResult CTask::OnGiveAward(UINT8 byIndex,bool bForce)
{
    CUser& rUser = _rTaskPkg.GetUser();
    CPlayerPtr pPlayer = rUser.GetPlayer();
    if(NULL == pPlayer)
        return eTaskErrOther;

    if(GetConfig().vecOptAwardItem.size() != 0 && GetConfig().vecOptAwardItem.size() <= byIndex)
        return eTaskErrNoSelOptAward;

    //背包空间
    TVecItemGenInfo vecItemGenInfo;
    UINT8 byAcceptTimes = bForce? 1: _byAcceptTimes;
    auto funcAward = [pPlayer, &vecItemGenInfo,byAcceptTimes](const SIdxCountJob& rConf) {
        UINT16 wItemID = (UINT16)rConf.dwIdx;
        UINT16 wItemCount = rConf.wCount*byAcceptTimes;
        UINT8 byJob = rConf.byJob;
        if(wItemID == 0 || wItemCount == 0 || (byJob != 0 && byJob != pPlayer->GetJob()))
            return;
        SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
        if(NULL != pItemInfo)
        {
            SItemGenInfo oItemGenInfo;
            oItemGenInfo.eBindType = eBindGet;
            oItemGenInfo.dwCount = wItemCount;
            oItemGenInfo.wItemID = wItemID;
            vecItemGenInfo.push_back(oItemGenInfo);
        }
    };

    for(size_t i=0; i<GetConfig().vecMustAwardItem.size(); i++)
        funcAward(GetConfig().vecMustAwardItem[i]);

    if(byIndex < GetConfig().vecOptAwardItem.size())
        funcAward(GetConfig().vecOptAwardItem[byIndex]);
    //如果是最后一环

    if(GetConfig().eTaskType == eTaskCircle)
    {
        TVecItemGenInfo rvec = vecItemGenInfo;
        if(rUser.GetVars().GetVar(ePlayerCircleTaskNum) + 1 == SParamConfig::byCircleTaskMaxNum)
        {
            if(CTaskMgr::GetCircleFinishAward(rUser,rvec))
            {
                if(!_rTaskPkg.GetUserPack().CanAddItem(rvec))
                    return eTaskErrPackFull;
            }
        }


        /*
           TVecINT32 vecParam;
           vecParam.push_back(1);
           pPlayer->OnEvent(eEventType_CircleTaskFinish,vecParam);
           */

    }
    if( !vecItemGenInfo.empty())
    {
        if(!_rTaskPkg.GetUserPack().CanAddItem(vecItemGenInfo))
            return eTaskErrPackFull;
        _rTaskPkg.GetUserPack().AddItem(vecItemGenInfo,NLogDataDefine::ItemFrom_Task);

    }
#if 0
    TVecLogItemData vecData;
    for(size_t i = 0;i < vecItemGenInfo.size();i++)
    {
        SItemGenInfo& rGenInfo = vecItemGenInfo[i];
        SLogItemData oTemp(rGenInfo.wItemID, rGenInfo.dwCount, rGenInfo.byQuality);
        vecData.push_back(oTemp);
    }
    UINT32 dwOPID = LogOPID;
    if(!vecData.empty())
        ItemLog.LogItemOper(dwOPID, *pPlayer, eItemLog_Gain, eOperLog_Task, vecData);
#endif
    //删除任务道具
    for(UINT8 i = 0; i< byAcceptTimes; i++)
    {
        _rTaskPkg.GetUserPack().DelItemFromList(GetConfig().vecItemCollect);
        _rTaskPkg.GetUserPack().DelItemFromList(GetConfig().vecItemGive);
        _rTaskPkg.GetUserPack().DelGatherItemFromList(GetConfig().vecGather);
    }
    //奖励头衔title
    //const vector<UINT32>& vecTitle = GetConfig().vecAwardTitle;
    //for(auto it_title = vecTitle.begin();it_title != vecTitle.end();it_title++)
    //	CTitleMgr::AddTitle(*pPlayer, *it_title);
#if 0
    //奖励贡献属性
    auto it_Prop = GetConfig().vecAwardProp.begin();
    for(;it_Prop != GetConfig().vecAwardProp.end();it_Prop++)
    {
        UINT32 dwValue = it_Prop->value;
        switch(it_Prop->type)
        {
            case eAwardProperty_repute:				//声望
                rUser.GetCampRep().AddCampRep((UINT8)GetConfig().wAwardPropCampID, dwValue);
                break;
            case eAwardProperty_familyPrestige:		//家族贡献
                {
                    UINT64 qwFamilyID = rUser.GetFamilyID();
                    if(0 != qwFamilyID)
                        g_FamilyGS2CSC.Send_AddFamilyPrestige(qwFamilyID, rUser.GetUserID(), dwValue);
                }
                break;
            case eAwardProperty_factionContri:		//公会贡献
                {
                    UINT64 qwGuildID = rUser.GetGuildID();
                    if(0 != qwGuildID)
                        rUser.SendCenterSvrPkg(g_GuildGS2CSC.BuildPkg_AddMemberContributePt(qwGuildID, rUser.GetUserID(), dwValue));
                }
                break;
        }
    }

    //奖励佣兵
    CFightForm& rFightForm = pPlayer->GetFightForm();
    CMercenCamp& rCamp = rUser.GetMercenCamp();
    for(auto& rAwardMercen : GetConfig().vecAwardMercen)
    {
        if(!rFightForm.AddMercenToForm(rAwardMercen.wMonsterID, rAwardMercen.wNameID, rAwardMercen.byPos))
        {
            LOG_CRI << "AddMercenToForm fails! TaskID: " << GetTaskID() << " MonsterID: " << rAwardMercen.wMonsterID << ", Pos: " << rAwardMercen.byPos;
            if(!rCamp.AddMercenToCamp(rAwardMercen.wMonsterID, rAwardMercen.wNameID))
                LOG_CRI << "AddMercenToCamp fails! TaskID: " << GetTaskID() << " MonsterID: " << rAwardMercen.wMonsterID;
        }
    }
#endif
    return eTaskSucceed;
}

bool CTask::OnCollectItem(UINT16 wItemID)
{
    if((GetConfig().dwContentType & eContentCollect) == 0)
        return false;
    for(auto it = _mapType2Info.lower_bound(eType_STaskCollectInfo), itUB = _mapType2Info.upper_bound(eType_STaskCollectInfo); it != itUB; ++it)
    {
        STaskInfoPtr pTaskInfo = it->second;
        STaskCollectInfoPtr pTaskCollectInfo = dynamic_pointer_cast<STaskCollectInfo>(pTaskInfo);
        if(wItemID == pTaskCollectInfo->wItemID)
        {
            pTaskCollectInfo->wItemCount = _rTaskPkg.GetUserPack().GetItemCount(wItemID);
        }
    }
    return CheckStateAndUpdate();
}

bool CTask::OnGather(UINT16 wGatherID)
{
    if((GetConfig().dwContentType & eContentGather) == 0)
        return false;
    for(auto it = _mapType2Info.lower_bound(eType_STaskGatherInfo), itUB = _mapType2Info.upper_bound(eType_STaskGatherInfo); it != itUB; ++it)
    {
        STaskInfoPtr pTaskInfo = it->second;
        STaskGatherInfoPtr pTaskGatherInfo = dynamic_pointer_cast<STaskGatherInfo>(pTaskInfo);
        if(wGatherID == pTaskGatherInfo->wGatherID)
        {
            pTaskGatherInfo->wCount++;
        }
    }
    return CheckStateAndUpdate();
}

bool CTask::OnNpcTalk(UINT16 wNpcID)
{
    if((GetConfig().dwContentType & eContentTalk) == 0)
        return false;
    for(auto it = _mapType2Info.lower_bound(eType_STaskTalkInfo), itUB = _mapType2Info.upper_bound(eType_STaskTalkInfo); it != itUB; ++it)
    {
        STaskInfoPtr pTaskInfo = it->second;
        STaskTalkInfoPtr pTaskTalkInfo = dynamic_pointer_cast<STaskTalkInfo>(pTaskInfo);
        if(wNpcID == pTaskTalkInfo->wNpcID)
        {
            pTaskTalkInfo->wTalkCount = 1;
        }
    }
    return CheckStateAndUpdate();
}

bool CTask::OnKillMonster(UINT16 wMonsterID)
{
    if((GetConfig().dwContentType & eContentKill) == 0)
        return false;
    for(auto it = _mapType2Info.lower_bound(eType_STaskMonsterInfo), itUB = _mapType2Info.upper_bound(eType_STaskMonsterInfo); it != itUB; ++it)
    {
        STaskInfoPtr pTaskInfo = it->second;
        STaskMonsterInfoPtr pTaskMonsterInfo = dynamic_pointer_cast<STaskMonsterInfo>(pTaskInfo);
        if(wMonsterID == pTaskMonsterInfo->wMonsterID)
        {
            ++pTaskMonsterInfo->wMonsterCount;
        }
    }
    return CheckStateAndUpdate();
}

bool CTask::OnProbe(SMapArea& rMapArea)
{
    if((GetConfig().dwContentType & eContentProbe) == 0)
        return false;
    for(size_t i = 0; i < GetConfig().vecProbe.size(); ++i)
    {
        if(rMapArea == GetConfig().vecProbe[i])
        {
            for(auto it = _mapType2Info.lower_bound(eType_STaskProbeInfo), itUB = _mapType2Info.upper_bound(eType_STaskProbeInfo); it != itUB; ++it)
            {
                STaskInfoPtr pTaskInfo = it->second;
                STaskProbeInfoPtr pTaskProbeInfo = dynamic_pointer_cast<STaskProbeInfo>(pTaskInfo);
                if(pTaskProbeInfo->byIndex == (UINT8)i)
                {
                    pTaskProbeInfo->bProbed = true;
                    return CheckStateAndUpdate();
                }
            }
        }
    }
    return false;
}

bool CTask::OnGrow(CPlayer& rPlayer, EProcessRoleProperty eProperty)
{
    if((GetConfig().dwContentType & eContentGrow) == 0)
        return false;
    UINT16 wLevel = 0;
    switch(eProperty)
    {
        case eProcessRoleProperty_level: 	//等级
            wLevel = rPlayer.GetLevel();
            break;
            /*
               case eProcessRoleProperty_contri:
               break;
               case eProcessRoleProperty_repute:
               break;
               case eProcessRoleProperty_mercen:
               {
               for(size_t i = 0; i < GetConfig().vecRoleProps.size(); ++i)
               {
               if (eProperty == GetConfig().vecRoleProps[i].type)
               {
               wLevel = _rTaskPkg.GetUser().GetAllMercenUpClass((UINT16)GetConfig().vecRoleProps[i].dwExtID);
               break;
               }
               }
               }
               break;
               */
        default:
            break;
    }
    for(auto it = _mapType2Info.lower_bound(eType_STaskGrowInfo), itUB = _mapType2Info.upper_bound(eType_STaskGrowInfo); it != itUB; ++it)
    {
        STaskInfoPtr pTaskInfo = it->second;
        STaskGrowInfoPtr pTaskGrowInfo = dynamic_pointer_cast<STaskGrowInfo>(pTaskInfo);
        if(pTaskGrowInfo != NULL && (UINT16)eProperty == pTaskGrowInfo->wType)
        {
            pTaskGrowInfo->wLevel = wLevel;
            CheckStateAndUpdate();
            return true;
        }
    }
    return false;
}

bool CTask::OnAction(EProcessAction eProcessAction, UINT32 dwValue)
{
    if((GetConfig().dwContentType & eContentBehave) == 0)
        return false;
    for(auto it = _mapType2Info.lower_bound(eType_STaskActionInfo), itUB = _mapType2Info.upper_bound(eType_STaskActionInfo); it != itUB; ++it)
    {
        STaskInfoPtr pTaskInfo = it->second;
        STaskActionInfoPtr pTaskActionInfo = dynamic_pointer_cast<STaskActionInfo>(pTaskInfo);
        STaskActionInfo& rTaskActionInfo = (STaskActionInfo&)*pTaskInfo;
        for(auto itAct = GetConfig().vecRoleActions.begin(); itAct != GetConfig().vecRoleActions.end(); ++itAct)
        {
            if(itAct->type == rTaskActionInfo.wAction && itAct->type == eProcessAction)
            {
                UINT8 byType = CheckTaskAction(itAct->type,itAct->param);
                if(byType == 2)
                {
                    rTaskActionInfo.wCount += dwValue; 
                }
                else if(byType == 0)
                {
                    rTaskActionInfo.wCount = 1;
                }
                else
                {
                    rTaskActionInfo.wCount = 0;
                }
                CheckStateAndUpdate();  
                return true;
            }

        }
    }

    return false;
}

bool CTask::OnBuild(UINT16 wBuildID, UINT16 wLevel)
{
    /*if((GetConfig().dwContentType & eContentBuild) == 0)
      return false;
      for(auto it = _mapType2Info.lower_bound(eType_STaskBuildInfo), itUB = _mapType2Info.upper_bound(eType_STaskBuildInfo); it != itUB; ++it)
      {
      STaskInfo* pTaskInfo = it->second;
      STaskBuildInfo* pTaskBuildInfo = dynamic_cast<STaskBuildInfo*>(pTaskInfo);
      if(pTaskBuildInfo != NULL && wBuildID == pTaskBuildInfo->wBuildID)
      {
      pTaskBuildInfo->wLevel = wLevel;
      CheckStateAndUpdate();
      return true;
      }
      }*/
    return false;
}

bool CTask::OnTechnics(UINT16 wTechnicsID, UINT16 wLevel)
{
    if((GetConfig().dwContentType & eContentTechnics) == 0)
        return false;
    for(auto it = _mapType2Info.lower_bound(eType_STaskScienceInfo), itUB = _mapType2Info.upper_bound(eType_STaskScienceInfo); it != itUB; ++it)
    {
        STaskInfoPtr pTaskInfo = it->second;
        STaskScienceInfoPtr pTaskScienceInfo = dynamic_pointer_cast<STaskScienceInfo>(pTaskInfo);
        if(pTaskScienceInfo != NULL && wTechnicsID == pTaskScienceInfo->wScienceID)
        {
            pTaskScienceInfo->wLevel = wLevel;
            CheckStateAndUpdate();
            return true;
        }
    }
    return false;
}

bool CTask::CheckStateAndUpdate(bool bNotify/* = true*/)
{
    if(GetConfig().dwLimitTime > 0)
    {
        UINT32 dwNow = (UINT32)time(NULL);
        if(dwNow > _dwAcceptTime && dwNow - _dwAcceptTime > GetConfig().dwLimitTime)
        {
            OnStateUpdate(eTaskFail, bNotify);
            return false;
        }
    }
    if(CheckFinishState())
    {
        RefreshSurroundTaskMonster(false);
        OnStateUpdate(eTaskFinish, bNotify);
        return true;
    }

    OnStateUpdate(eTaskAccept, bNotify);
    return false;
}

bool CTask::CheckFinishState()
{
    if(GetConfig().dwCharge && (_rTaskPkg.GetUser().GetTotalRecharge() >= GetConfig().dwCharge))
        return true;

    STaskScript *pTaskScript = CTaskMgr::GetTaskScript(GetTaskID());
    if(NULL != pTaskScript && pTaskScript->_bHasCanFinishTask/* && pTaskScript->_pScript*/)
    {
        //bool bCan = Config.GetScript().CanFinishTask(GetTaskID());
        /*
           if(!pTaskScript->_pScript->ExecuteFunc("CanFinishTask", bCan, _rTaskPkg.GetPlayer()->GetRoleID(), GetTaskID()))
           {
           LOG_CRI << "ExecuteFunc fails! taskid: " << GetTaskID();
           return false;
           }
           else
           return bCan;
           */
        if(!Config.GetScript().CanFinishTask(GetTaskID(),_rTaskPkg.GetUser()))
        {
            return false;
        }
    }
    UINT8 byProbeFinish = 0;
    for(auto it = _mapType2Info.begin(); it != _mapType2Info.end(); ++it)
    {
        STaskInfoPtr pTaskInfo = it->second;
        switch(pTaskInfo->GetClassType())
        {
            case eType_STaskCollectInfo:
                {
                    STaskCollectInfo& rTaskCollectInfo = (STaskCollectInfo&)*pTaskInfo;
                    for(size_t i = 0; i < GetConfig().vecItemCollect.size(); ++i)
                    {
                        const SCollectItem& rCollectItem = GetConfig().vecItemCollect[i];
                        UINT16 wItemID = rCollectItem.wItemID;
                        if(wItemID == rTaskCollectInfo.wItemID && rTaskCollectInfo.wItemCount < rCollectItem.wCount)
                            return false;
                    }
                }
                break;
            case eType_STaskGatherInfo:
                {
                    STaskGatherInfo& rTaskGatherInfo = (STaskGatherInfo&)*pTaskInfo;
                    for(size_t i = 0; i < GetConfig().vecGather.size(); ++i)
                    {
                        const SIdxCount& rIdxCount = GetConfig().vecGather[i];
                        UINT16 wGatherID = (UINT16)rIdxCount.dwIdx;
                        if(wGatherID == rTaskGatherInfo.wGatherID && rTaskGatherInfo.wCount < rIdxCount.wCount)
                            return false;
                    }
                }
                break;
            case eType_STaskMonsterInfo:
                {
                    STaskMonsterInfo& rTaskMonsterInfo = (STaskMonsterInfo&)*pTaskInfo;
                    for(size_t i = 0; i < GetConfig().vecMonsterKill.size(); ++i)
                    {
                        const SKillMonster& rKillMonster = GetConfig().vecMonsterKill[i];
                        if(rTaskMonsterInfo.wMonsterID == rKillMonster.wMonsterID && rTaskMonsterInfo.wMonsterCount < rKillMonster.wCount)
                            return false;
                    }
                }
                break;
            case eType_STaskTalkInfo:
                {
                    STaskTalkInfo& rTaskTalkInfo = (STaskTalkInfo&)*pTaskInfo;
                    for(auto itTalk = GetConfig().mapNpc2Talk.begin(); itTalk != GetConfig().mapNpc2Talk.end(); ++itTalk)
                    {
                        UINT16 wNpcID = (UINT16)itTalk->first;
                        if(wNpcID == rTaskTalkInfo.wNpcID && rTaskTalkInfo.wTalkCount == 0)
                            return false;
                    }
                }
                break;
            case eType_STaskProbeInfo:
                {
                    STaskProbeInfo& rTaskProbeInfo = (STaskProbeInfo&)*pTaskInfo;
                    if(rTaskProbeInfo.bProbed)
                        byProbeFinish++;
                }
                break;
            case eType_STaskBuildInfo:
                {
                    STaskBuildInfo& rTaskBuildInfo = (STaskBuildInfo&)*pTaskInfo;
                    for(auto itBuild = GetConfig().vecBuildings.begin(); itBuild != GetConfig().vecBuildings.end(); ++itBuild)
                    {
                        UINT16 wBuildID = (UINT16)itBuild->dwIdx;
                        if(wBuildID == rTaskBuildInfo.wBuildID && rTaskBuildInfo.wLevel < itBuild->wCount)
                            return false;
                    }
                }
                break;
            case eType_STaskScienceInfo:
                {
                    STaskScienceInfo& rTaskScienceInfo = (STaskScienceInfo&)*pTaskInfo;
                    for(auto itTech = GetConfig().vecTechnics.begin(); itTech != GetConfig().vecTechnics.end(); ++itTech)
                    {
                        UINT16 wTechID = (UINT16)itTech->dwIdx;
                        if(wTechID == rTaskScienceInfo.wScienceID && rTaskScienceInfo.wLevel < itTech->wCount)
                            return false;
                    }
                }
                break;
            case eType_STaskActionInfo:
                {
                    STaskActionInfo& rTaskActionInfo = (STaskActionInfo&)*pTaskInfo;
                    for(auto itAct = GetConfig().vecRoleActions.begin(); itAct != GetConfig().vecRoleActions.end(); ++itAct)
                    {
                        if(itAct->type == rTaskActionInfo.wAction)
                        {
                            UINT8 byType= CheckTaskAction(itAct->type,itAct->param);
                            if(byType == 0)
                            {
                                rTaskActionInfo.wCount = 1; 
                            }
                            else if(byType == 1)
                            {
                                rTaskActionInfo.wCount = 0;
                            }
                            return rTaskActionInfo.wCount >= itAct->value;
                        }

                    }
                    return false;

                }
                break;
            case eType_STaskGrowInfo:
                {
                    STaskGrowInfo& rTaskGrowInfo = (STaskGrowInfo&)*pTaskInfo;
                    for(auto itGrow = GetConfig().vecRoleProps.begin(); itGrow != GetConfig().vecRoleProps.end(); ++itGrow)
                    {
                        UINT16 wtype = (UINT16)itGrow->type;
                        if(wtype == rTaskGrowInfo.wType && rTaskGrowInfo.wLevel < (UINT16)itGrow->value)
                            return false;
                    }
                }
                break;
            default:
                break;
        }
    }

    UINT8 byProbe = (UINT8)GetConfig().vecProbe.size();
    if(byProbe > 0)
    {
        if(0 == GetConfig().byProbeFlag)
        {
            if(byProbe > byProbeFinish)
                return false;
        }
        else if(1 == GetConfig().byProbeFlag)
        {
            if(byProbeFinish < 1)
                return false;
        }
    }
    return true;
}

UINT8 CTask::CheckTaskAction(UINT16 type, string strParam)
{
    CUser& rUser = _rTaskPkg.GetUser();
    CPlayerPtr pPlayer = rUser.GetPlayer();
    if(NULL == pPlayer)
        return 2;
    UINT32 valueA = 0;
    UINT32 valueB = 0;
    UINT32 valueC = 0;
    UINT32 valueD = 0;
    buf::Tokenizer tk(strParam, ',');
    for (size_t i = 0 ; i< tk.size();++i)
    {
        if(0 == i)
            valueA = atoi(tk[i].c_str());
        else if(1 == i)
            valueB = atoi(tk[i].c_str());
        else if(2 == i)
            valueC = atoi(tk[i].c_str());
        else if(3 == i)
            valueD = atoi(tk[i].c_str());
    }

    UINT8 byJob = pPlayer->GetJob();
    UINT32 value = 0;
    if(ECAREER_RU == byJob)
        value = valueA;
    else if(ECAREER_SHI == byJob)
        value = valueB;
    else if(ECAREER_DAO == byJob)
        value = valueC;
    else if(ECAREER_MO == byJob)
        value = valueD;

    UINT64 status = _rTaskPkg.GetUser().GetVars().GetVar(NVarDefine::ePlayerVarTaskMark);
    switch(type)
    {
        //var判定
        case eProcessAction_WorldBoss://世界Boss
        case eProcessAction_JoinGuild://加入帮派
        case eProcessAction_MoneyTree://摇钱树
            {
                if(GET_BIT(status, (type - 1)) > 0)
                {
                    return 0;
                }
            }
            break;
        case eProcessAction_SpecialHeroLevel://指定某散仙某等级
            {
                CFighterPtr pFighter = NULL ;
                if(valueA != 0)
                {
                    pFighter = pPlayer->GetFighterManager()->GetFighterByID(valueA);

                }
                else
                {
                    pFighter =  pPlayer->GetFighterManager()->GetMainFighter();

                }
                if(pFighter == NULL)
                {
                    break;
                }
                if(pFighter->GetLevel() >= valueB)
                {
                    return 0;
                }

            }
            break;
        case eProcessAction_HeroXinFa://指定某散仙激活某心法
            {
                CFighterPtr pFighter = NULL ;
                if(valueA != 0)
                {
                    pFighter = pPlayer->GetFighterManager()->GetFighterByID(valueA);

                }
                else
                {
                    pFighter =  pPlayer->GetFighterManager()->GetMainFighter();

                }
                if(pFighter == NULL)
                {
                    break;
                }
                CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
                if(!pHeroFighter)
                {
                    break;
                }

                if(pHeroFighter->GetXinFas().IsXinFa(valueB))
                {
                    return 0;
                }

            }
            break;
        case eProcessAction_SpecialHeroToTalCTLv://指定某散仙总淬体等级
            {
                CFighterPtr pFighter = NULL ;
                if(valueA != 0)
                {
                    pFighter = pPlayer->GetFighterManager()->GetFighterByID(valueA);

                }
                else
                {
                    pFighter =  pPlayer->GetFighterManager()->GetMainFighter();

                }
                if(pFighter == NULL)
                {
                    break;
                }
                UINT32 dwCountLv = pFighter->GetLianPi() + pFighter->GetTongJin() + pFighter->GetQiangJi() + pFighter->GetDuanGu() + pFighter->GetHuoLuo() + pFighter->GetXiSui();
                if(dwCountLv >= valueB)
                {
                    return 0;
                }

            }
            break;
        case eProcessAction_SpecialTrumpUpdate://特定法宝，升到特定等级
            {
                vector<CItemPtr> rVecItem;
                pPlayer->GetFighterManager()->GetTrumpSlots().GetItemList(valueA,rVecItem);
                if(rVecItem.empty())
                {
                    break;
                }
                for(auto it = rVecItem.begin();it != rVecItem.end();it++)
                {
                    CItemPtr pItem = *it;
                    CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(pItem);
                    if(!pTrump)
                    {
                        continue;
                    }
                    if(pTrump->GetIntensifyLevel() >= valueB)
                    {
                        return 0;
                    }
                }
            }
            break;
        case eProcessAction_RecruitCortege://参数：散仙ID
            {
                if (pPlayer->GetFighterManager()->HasFighter(value))
                {
                    return 0;
                }
            }
            break;
        case eProcessAction_SpecialHeroDuJie:
            {
                CFighterPtr pFighter = NULL ;
                if(valueA != 0)
                {
                    pFighter = pPlayer->GetFighterManager()->GetFighterByID(valueA);

                }
                else
                {
                    pFighter =  pPlayer->GetFighterManager()->GetMainFighter();

                }
                if(pFighter == NULL)
                {
                    break;
                }
                CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
                if(!pHeroFighter)
                {
                    break;
                }
                if(pHeroFighter->GetDujieLevel() >= valueB)
                {
                    return 0;
                }

            }
            break;
        case eProcessAction_GetTrump://参数：法宝ID
            {
                UINT32 TrumpCount = pPlayer->GetFighterManager()->GetTrumpSlots().GetItemCount(value);
                if(TrumpCount > 0)
                    return 0;
            }
            break;
        case eProcessAction_ActFormation://参数：阵型ID
            {
                //if(pPlayer->GetFighterManager()->GetFormationPet().GetFormationSlots().GetFormation(value))
                return 0;
            }
            break;
        case eProcessAction_ActMounts://参数：坐骑ID
            {
                if(pPlayer->GetHorseMgr()->IsActiveModel(value))
                    return 0;
            }
            break;

        case eProcessAction_ActPet://参数：阵灵ID
            {
                if(NULL != pPlayer->GetFighterManager()->GetFormationPet().GetPetSlots().GetPet(value))
                    return 0;
            }
            break;
        case eProcessAction_FighterWork://参数：无，有散仙出战即可
            {
                CFormation& rFormation = pPlayer->GetFighterManager()->GetFormation();
                {
                    TVecLineup vecLineup;
                    rFormation.GetLineup(vecLineup);
                    if(vecLineup.size() > 1)
                        return 0;
                }
            }
            break;
        case eProcessAction_FighterSkill://参数：察看技能是否存在
            {
                if(pPlayer->GetFighterManager()->FindHeroFighterSkillAndTrump(value))
                    return 0;
            }
            break;
        case eProcessAction_TodayActivity://参数：索妖塔层数
            {
                if(rUser.GetVars().GetVar(NVarDefine::ePlayerActivity) >= value)
                {
                    return 0;
                }
            }
            break;
        case eProcessAction_TowerLevel://参数：最高层数
            {
                if(pPlayer->GetTopDemonFloorID() >= value)
                {
                    return 0;
                }
            }
            break;
        case eProcessAction_GetItem:
            {
                UINT16 wCount = rUser.GetPack().GetItemCount(valueA);
                if (wCount >= valueB)
                    return 0;
            }
            break;
        case eProcessAction_SpecialHeroCTLvl:
            {
                CFighterPtr pFighter = NULL ;
                if(valueA != 0)
                {
                    pFighter = pPlayer->GetFighterManager()->GetFighterByID(valueA);

                }
                else
                {
                    pFighter =  pPlayer->GetFighterManager()->GetMainFighter();

                }
                if(pFighter == NULL)
                {
                    break;
                }

                if (pFighter->GetLianPi() >= valueB 
                        && pFighter->GetTongJin() >= valueB 
                        && pFighter->GetQiangJi() >=valueB 
                        && pFighter->GetDuanGu() >= valueB 
                        && pFighter->GetHuoLuo() >= valueB 
                        && pFighter->GetXiSui() >= valueB)
                {
                    return 0;
                }
            }
            break;
        case eProcessAction_SpecialHeroSkillLvl:
            {
                CFighterPtr pFighter = NULL ;
                if(valueA != 0)
                {
                    pFighter = pPlayer->GetFighterManager()->GetFighterByID(valueA);

                }
                else
                {
                    pFighter =  pPlayer->GetFighterManager()->GetMainFighter();

                }
                if(pFighter == NULL)
                {
                    break;
                }
                TVecUINT32 vecSkillID;
                dynamic_pointer_cast<CHeroFighter>(pFighter)->GetAllSkillsID(vecSkillID);
                for (auto it = vecSkillID.begin(); it != vecSkillID.end(); ++it)
                {
                    if (valueB == SKILL_ID(*it))
                    {
                        if (SKILL_LEVEL(*it) >= valueC)
                            return 0;
                        else
                            break;
                    }
                }
            }
            break;
        case eProcessAction_SpecialPetLvl:
            {
                CPetPtr pPet = pPlayer->GetFighterManager()->GetFormationPet().GetPetSlots().GetPet(valueA);
                if (NULL == pPet)
                    break;

                if (pPet->GetPetLevel() >= valueB)
                    return 0;
            }
            break;
        case eProcessAction_SpecialHorseLvl:
            {
                CHorsePtr pHorse = pPlayer->GetHorseMgr()->GetHorseByID(valueA);
                if (NULL == pHorse)
                    break;

                if (pHorse->GetHorseLevel() >= valueB)
                    return 0;
            }
            break;
        case eProcessAction_CombinedActivation:
            {
                CHeroFighterCombinationPtr pFgtComb = pPlayer->GetFighterManager()->GetHeroFighterCombinationSlots().GetFighterCombination(valueA);
                if (pFgtComb)
                    return 0;
            }
            break;
        case eProcessAction_SpecialFighterWork:   //特定散仙出战
            {

                CFormation& rFormation = pPlayer->GetFighterManager()->GetFormation();
                TVecLineup vecLineup;
                rFormation.GetLineup(vecLineup);
                for(auto it = vecLineup.begin(); it != vecLineup.end();++it)
                {
                    Lineup &rLineUp = *it;
                    if(rLineUp.pFighter == NULL)
                    {
                        continue;
                    }
                    if(rLineUp.pFighter->GetFighterID() == valueA)
                    {
                        return 0;
                    }


                }

            }
            break;
        case eProcessAction_SpecialBeautyPoint:            //特定美女，特定亲密度
            {
                SBeautyPtr pBeauty = pPlayer->GetBeautyMgr()->GetBeauty(valueA);
                if (NULL == pBeauty)
                    break;
                if (pBeauty->dwBeautyExp >= valueB)
                    return 0;
            }
            break;
        case eProcessAction_SpecialStone://指定宝石镶嵌
            {
                TVecFighterPtr rvecFighters;
                if(!pPlayer->GetFighterManager()->GetAllFighters(rvecFighters))
                {
                    break;
                }
                for(auto it = rvecFighters.begin();it != rvecFighters.end();it++)
                {
                    CFighterPtr &pFighter = *it;
                    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
                    if(!pHeroFighter)
                    {
                        continue;;
                    }
                    TVecGemstonePtr vecStone;
                    pHeroFighter->GetGemstoneSlots().GetGemstoneAll(vecStone);
                    for(auto iter = vecStone.begin();iter != vecStone.end();iter++)
                    {
                        CGemstonePtr& pStone = *iter;
                        if(pStone->GetItemID() == valueA)
                        {
                            return 0;
                        }
                    }
                }
            }
        case eProcessAction_GetBeast://激活指定兽魂
            {
               if (pPlayer->GetFighterManager()->GetFormationPet().GetBeastSoul().FindBeastSoul(NRoleInfoDefine::EBeastSoulType(valueB), valueC, valueA))
                   return 0;
            }
            break;

        default:
            return 2;
    }
    return 1;
}

void CTask::OnStateUpdate(ETaskState eTaskState, bool bNotify/* = true*/)
{
    _eTaskState = eTaskState;
    if(eTaskFinish == _eTaskState)
    {
#if 0
        CPlayerPtr pPlayer = _rTaskPkg.GetPlayer();
        if(NULL != pPlayer)
            TaskLog.LogTask(*pPlayer, eTaskLog_Finish, (UINT8)GetTaskType(), GetConfig().wID);
#endif
    }
    if(bNotify)
    {
        //	STaskPtr pTask = ToProt();
        //	if(NULL != pTask)
        _rTaskPkg.GetUser().SendPkg(g_TaskProtS.BuildPkg_TaskUpdateNtf(ToStask()));
    }
    RoleTaskInfo * pTaskRecord = _rTaskPkg.GetRoleTaskInfo(GetTaskID());
    if(NULL != pTaskRecord)
    {
        SynData(*pTaskRecord); 
    }
}

bool CTask::CanTalkWithNpc(UINT16 wNpcID)
{
    if((GetConfig().dwContentType & eContentTalk) != 0)
    {
        auto itNpc = GetConfig().mapNpc2Talk.find(wNpcID);
        if(itNpc == GetConfig().mapNpc2Talk.end())
            return false;
        for(auto it = _mapType2Info.lower_bound(eType_STaskTalkInfo), itUB = _mapType2Info.upper_bound(eType_STaskTalkInfo); it != itUB; ++it)
        {
            STaskInfoPtr pTaskInfo = it->second;
            STaskTalkInfoPtr pTaskTalkInfo = dynamic_pointer_cast<STaskTalkInfo>(pTaskInfo);
            if(pTaskTalkInfo != NULL && wNpcID == pTaskTalkInfo->wNpcID)
                return pTaskTalkInfo->wTalkCount == 0;
        }
    }
    return false;
}

void CTask::OnReset()
{
    for(auto it = _mapType2Info.begin(); it != _mapType2Info.end(); ++it)
    {
        STaskInfoPtr pTaskInfo = it->second;
        switch(pTaskInfo->GetClassType())
        {
            case eType_STaskCollectInfo:
                {
                    STaskCollectInfo& rTaskCollectInfo = (STaskCollectInfo&)*pTaskInfo;
                    for(size_t i = 0; i < GetConfig().vecItemCollect.size(); ++i)
                    {
                        const SCollectItem& rCollectItem = GetConfig().vecItemCollect[i];
                        UINT16 wItemID = rCollectItem.wItemID;
                        if(wItemID == rTaskCollectInfo.wItemID)
                        {
                            rTaskCollectInfo.wItemCount = 0;
                        }
                    }
                }
                break;
            case eType_STaskGatherInfo:
                {
                    STaskGatherInfo& rTaskGatherInfo = (STaskGatherInfo&)*pTaskInfo;
                    for(size_t i = 0; i < GetConfig().vecGather.size(); ++i)
                    {
                        const SIdxCount& rIdxCount = GetConfig().vecGather[i];
                        UINT16 wGatherID = (UINT16)rIdxCount.dwIdx;
                        if(wGatherID == rTaskGatherInfo.wGatherID)
                        {
                            rTaskGatherInfo.wCount = 0;
                        }
                    }
                }
                break;
            case eType_STaskMonsterInfo:
                {
                    STaskMonsterInfo& rTaskMonsterInfo = (STaskMonsterInfo&)*pTaskInfo;
                    for(size_t i = 0; i < GetConfig().vecMonsterKill.size(); ++i)
                    {
                        const SKillMonster& rKillMonster = GetConfig().vecMonsterKill[i];
                        if(rTaskMonsterInfo.wMonsterID == rKillMonster.wMonsterID)
                        {
                            rTaskMonsterInfo.wMonsterCount = 0;
                        }
                    }
                }
                break;
            case eType_STaskTalkInfo:
                {
                    STaskTalkInfo& rTaskTalkInfo = (STaskTalkInfo&)*pTaskInfo;
                    for(auto itTalk = GetConfig().mapNpc2Talk.begin(); itTalk != GetConfig().mapNpc2Talk.end(); ++itTalk)
                    {
                        UINT16 wNpcID = (UINT16)itTalk->first;
                        if(wNpcID == rTaskTalkInfo.wNpcID)
                        {
                            rTaskTalkInfo.wTalkCount = 0;
                        }
                    }
                }
                break;
            case eType_STaskProbeInfo:
                {
                    STaskProbeInfo& rTaskProbeInfo = (STaskProbeInfo&)*pTaskInfo;
                    rTaskProbeInfo.bProbed = false;
                }
                break;
            case eType_STaskBuildInfo:
                {
                    STaskBuildInfo& rTaskBuildInfo = (STaskBuildInfo&)*pTaskInfo;
                    rTaskBuildInfo.wLevel = 0;
                }
                break;
            case eType_STaskScienceInfo:
                {
                    STaskScienceInfo& rTaskScienceInfo = (STaskScienceInfo&)*pTaskInfo;
                    rTaskScienceInfo.wLevel = 0;
                }
                break;
            case eType_STaskActionInfo:
                {
                    STaskActionInfo& rTaskActionInfo = (STaskActionInfo&)*pTaskInfo;
                    rTaskActionInfo.wCount = 0;
                }
                break;
            case eType_STaskGrowInfo:
                {
                    STaskGrowInfo& rTaskGrowInfo = (STaskGrowInfo&)*pTaskInfo;
                    rTaskGrowInfo.wLevel = 0;
                }
                break;
            default:
                break;
        }
    }
    OnStateUpdate(eTaskAccept);
}

void CTask::SetFinishTask()
{
    for(auto it = _mapType2Info.begin(); it != _mapType2Info.end(); ++it)
    {
        STaskInfoPtr pTaskInfo = it->second;
        switch(pTaskInfo->GetClassType())
        {
            case eType_STaskCollectInfo:
                {
                    STaskCollectInfo& rTaskCollectInfo = (STaskCollectInfo&)*pTaskInfo;
                    for(size_t i = 0; i < GetConfig().vecItemCollect.size(); ++i)
                    {
                        const SCollectItem& rCollectItem = GetConfig().vecItemCollect[i];
                        UINT16 wItemID = rCollectItem.wItemID;
                        if(wItemID == rTaskCollectInfo.wItemID)
                            rTaskCollectInfo.wItemCount = rCollectItem.wCount;
                    }
                }
                break;
            case eType_STaskGatherInfo:
                {
                    STaskGatherInfo& rTaskGatherInfo = (STaskGatherInfo&)*pTaskInfo;
                    for(size_t i = 0; i < GetConfig().vecGather.size(); ++i)
                    {
                        const SIdxCount& rIdxCount = GetConfig().vecGather[i];
                        UINT16 wGatherID = (UINT16)rIdxCount.dwIdx;
                        if(wGatherID == rTaskGatherInfo.wGatherID)
                            rTaskGatherInfo.wCount = rIdxCount.wCount;
                    }
                }
                break;
            case eType_STaskMonsterInfo:
                {
                    STaskMonsterInfo& rTaskMonsterInfo = (STaskMonsterInfo&)*pTaskInfo;
                    for(size_t i = 0; i < GetConfig().vecMonsterKill.size(); ++i)
                    {
                        const SKillMonster& rKillMonster = GetConfig().vecMonsterKill[i];
                        if(rTaskMonsterInfo.wMonsterID == rKillMonster.wMonsterID)
                            rTaskMonsterInfo.wMonsterCount = rKillMonster.wCount;
                    }
                }
                break;
            case eType_STaskTalkInfo:
                {
                    STaskTalkInfo& rTaskTalkInfo = (STaskTalkInfo&)*pTaskInfo;
                    for(auto itTalk = GetConfig().mapNpc2Talk.begin(); itTalk != GetConfig().mapNpc2Talk.end(); ++itTalk)
                    {
                        UINT16 wNpcID = (UINT16)itTalk->first;
                        if(wNpcID == rTaskTalkInfo.wNpcID)
                            rTaskTalkInfo.wTalkCount = 1;
                    }
                }
                break;
            case eType_STaskProbeInfo:
                {
                    STaskProbeInfo& rTaskProbeInfo = (STaskProbeInfo&)*pTaskInfo;
                    rTaskProbeInfo.bProbed = true;
                }
                break;
            case eType_STaskBuildInfo:
                {
                    STaskBuildInfo& rTaskBuildInfo = (STaskBuildInfo&)*pTaskInfo;
                    for(auto itBuild = GetConfig().vecBuildings.begin(); itBuild != GetConfig().vecBuildings.end(); ++itBuild)
                    {
                        UINT16 wBuildID = (UINT16)itBuild->dwIdx;
                        if(wBuildID == rTaskBuildInfo.wBuildID)
                            rTaskBuildInfo.wLevel = itBuild->wCount;
                    }
                }
                break;
            case eType_STaskScienceInfo:
                {
                    STaskScienceInfo& rTaskScienceInfo = (STaskScienceInfo&)*pTaskInfo;
                    for(auto itTech = GetConfig().vecTechnics.begin(); itTech != GetConfig().vecTechnics.end(); ++itTech)
                    {
                        UINT16 wTechID = (UINT16)itTech->dwIdx;
                        if(wTechID == rTaskScienceInfo.wScienceID)
                            rTaskScienceInfo.wLevel = itTech->wCount;
                    }
                }
                break;
            case eType_STaskActionInfo:
                {
                    STaskActionInfo& rTaskActionInfo = (STaskActionInfo&)*pTaskInfo;
                    for(auto itAct = GetConfig().vecRoleActions.begin(); itAct != GetConfig().vecRoleActions.end(); ++itAct)
                    {
                        UINT16 wtype = (UINT16)itAct->type;
                        if(wtype == rTaskActionInfo.wAction)
                            rTaskActionInfo.wCount = (UINT16)itAct->value;
                    }
                }
                break;
            case eType_STaskGrowInfo:
                {
                    STaskGrowInfo& rTaskGrowInfo = (STaskGrowInfo&)*pTaskInfo;
                    for(auto itGrow = GetConfig().vecRoleProps.begin(); itGrow != GetConfig().vecRoleProps.end(); ++itGrow)
                    {
                        UINT16 wtype = (UINT16)itGrow->type;
                        if(wtype == rTaskGrowInfo.wType)
                            rTaskGrowInfo.wLevel = (UINT16)itGrow->value;
                    }
                }
                break;
            default:
                break;
        }
    }
    OnStateUpdate(eTaskFinish);
}

bool CTask::ForceFinishProbe()
{
    CPlayerPtr pPlayer = _rTaskPkg.GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_CRI << "Can't find Player! TaskID: " << GetTaskID();
        return false;
    }
    auto it = _mapType2Info.find(eType_STaskProbeInfo);
    if(it == _mapType2Info.end())
        return false;
    if(GetConfig().vecProbe.empty())
    {
        LOG_CRI << "Can't find probe area! TaskID: " << GetTaskID();
        return false;
    }
    const SMapArea& rMapArea = GetConfig().vecProbe[0];
    CGameMapPtr pMap = pPlayer->GetMap();
    if(pMap == NULL)
    {
        LOG_CRI << "Player is not on map! MapID: " << rMapArea.wMapID;
        return false;
    }
    if(pMap->GetMapID() != rMapArea.wMapID)
    {
        pMap = CMapMgr::GetMap(rMapArea.wMapID);
        if(pMap == NULL)
        {
            LOG_CRI << "Can't find map! MapID: " << rMapArea.wMapID;
            return false;
        }
    }
    SPoint oPoint((rMapArea.fX1 + rMapArea.fX2) / 2, (rMapArea.fZ1 + rMapArea.fZ2) / 2);
    float fRadius = min(abs((rMapArea.fX2 - rMapArea.fX1) / 2), abs((rMapArea.fZ2 - rMapArea.fZ1) / 2));
    TVecPoint vecPoint;
    pMap->GetRandPoint(oPoint, fRadius, 1, vecPoint);
    if(vecPoint.empty())
    {
        LOG_CRI << "Can't find movable point! TaskID: " << GetTaskID();
        return false;
    }
    if(!pPlayer->JumpMap(pMap, vecPoint[0]))
        return false;
    SetFinishTask();
    return true;
}

bool CTask::IsFakeMonsterTask() 
{
    bool bIsMonsterType = false;
    for(auto p : _mapType2Info)
    {
        if(p.first != eType_STaskMonsterInfo)
            return false;
        bIsMonsterType = true;
    }
    if(!bIsMonsterType)
        return false;
    for(auto& rKillMonster : GetConfig().vecMonsterKill)
    {
        if(!rKillMonster.bFake)
            return false;
    }
    return true;
}

void CTask::AwardGeneral(CUser& rUser, CPlayer& rPlayer,bool bForce)
{
    //UINT32 dwOPID = LogOPID;
    //给予奖励
    UINT8 byAcceptTimes = bForce ? 1: _byAcceptTimes;
    for(size_t i = 0;i < GetConfig().vecAwardGeneral.size();++i)
    {
        const SAwardGeneral& rAward = GetConfig().vecAwardGeneral[i];
        UINT32 dwValue = rAward.value*byAcceptTimes;
        rUser.AddMoney((EMoneyType)rAward.type,dwValue,NLogDataDefine::ItemFrom_Task);
    }

    switch (GetConfig().eTaskType) 
    {
        case eTaskForGroup:
            {
                const SDaily_shimentaskColorCFG * pCfg =  g_CGroupTaskManager.GetConfigByTaskID(GetTaskID()); 
                if(pCfg)
                {
                    //师门加经验
                    UINT32 dwValue = pCfg->_Exp*byAcceptTimes;
                    SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(rUser.GetVIPLevel());
                    if(pCfgVip)
                        dwValue += dwValue * pCfgVip->_ShimenGet / 100;

                    rUser.GetPlayer()->AddExp(dwValue);
                }
            }
            break;
        case eTaskForYaMen:
            {
                const SDaily_yamentaskColorCFG * pCfg =  g_CYaMenTaskManager.GetConfigByTaskID(GetTaskID()); 
                if(pCfg)
                {
                    //衙门加银币
                    UINT32 dwValue = pCfg->_Exp*byAcceptTimes;
                    SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(rUser.GetVIPLevel());
                    if(pCfgVip)
                        dwValue += dwValue * pCfgVip->_YamenGet / 100;
                    rUser.AddMoney(EMONEY_SILVER,dwValue,NLogDataDefine::ItemFrom_Task);
                }
            }
            break;
        case eTaskCircle:
            {
                UINT8 byNum =  rUser.GetVars().GetVar(ePlayerCircleTaskNum) + 1;
                UINT8 byStar =  rUser.GetVars().GetVar(ePlayerCircleTaskStar); 
                TVecItemGenInfo rvec;
                if(!CTaskMgr::GetCircleTaskAward(rUser,byStar, byNum,rvec))
                {
                    LOG_CRI << "ERR GetGetCircleTaskAward";
                    break;
                }
                rUser.GetPack().AddItem(rvec,NLogDataDefine::ItemFrom_CircleTask);
                rvec.clear();
                //如果是最后一环
                if(byNum == SParamConfig::byCircleTaskMaxNum)
                {
                    if(!CTaskMgr::GetCircleFinishAward(rUser,rvec))
                    {
                        LOG_CRI << "ERR GetGetCircleFinishAward";
                        break;
                    }
                }
                rUser.GetPack().AddItem(rvec,NLogDataDefine::ItemFrom_CircleTaskFinish);
            }
            break;
        default:
            break;
    }
}

bool CTask::IsClrCheckTask(EProcessAction eProcessAction) 
{
    if (eProcessAction_CollectGame != eProcessAction)
        return false;

    if((GetConfig().dwContentType & eContentBehave) == 0)
        return false;
    for(auto it = _mapType2Info.lower_bound(eType_STaskActionInfo), itUB = _mapType2Info.upper_bound(eType_STaskActionInfo); it != itUB; ++it)
    {
        STaskInfoPtr pTaskInfo = it->second;
        STaskActionInfoPtr pTaskActionInfo = dynamic_pointer_cast<STaskActionInfo>(pTaskInfo);
        if(pTaskActionInfo != NULL && (UINT16)eProcessAction == pTaskActionInfo->wAction)
            return true;
    }
    return false;
}
