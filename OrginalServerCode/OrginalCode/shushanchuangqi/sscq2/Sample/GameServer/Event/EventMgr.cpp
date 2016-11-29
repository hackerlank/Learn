#include "stdafx.h"
#include "EventMgr.h"
#include "Tokenizer.h"
#include "Player.h"
#include "Protocols.h"
#include "GetCondMgr.h"
#include "Game2CenterLogC.h"
#include "Bubble.h"
extern CGame2CenterLogC g_Game2CenterLog; 
CRegiserterEvent::CRegiserterEvent(EActClass eActClassID,CPlayer& rPlayer):
    _eActClassID(eActClassID),
    _bInit(false),
    _rRegisterPlayer(rPlayer)
{

}
CRegiserterEvent::~CRegiserterEvent()
{

}

void CRegiserterEvent::RegisterEventInit()
{
    _bInit = true;

    CEventMgrPtr pEventMgr = _rRegisterPlayer.GetEventMgr();
    if(pEventMgr)
    {
        pEventMgr->RegisterClass(this);
    }
}

//添加关注的事件
bool CRegiserterEvent::AddEvent(UINT32 dwEventInstID,UINT32 dwApplyID,UINT32 dwStartTime)
{
    bool bRet = false;
    CEventMgrPtr pEventMgr = _rRegisterPlayer.GetEventMgr();
    if(pEventMgr)
    {
        CRegiserterEvent* pRegEvent =  pEventMgr->GetActByClassID(GetActClassID());
        if(NULL == pRegEvent)
        {
            RegisterEventInit();
        }

        bRet = pEventMgr->AddEvent(GetActClassID(),dwEventInstID,dwApplyID,dwStartTime);
    }

    return bRet;
}

//删除某个事件
void CRegiserterEvent::RemoveEvent(UINT32 dwEventInstID,UINT32 dwApplyID)
{
    CEventMgrPtr pEventMgr = _rRegisterPlayer.GetEventMgr();
    if(pEventMgr)
    {
        pEventMgr->RemoveEvent(GetActClassID(),dwEventInstID,dwApplyID);
    }

}

//删除所有关注事件
void CRegiserterEvent::ClearEvent()
{
    CEventMgrPtr pEventMgr = _rRegisterPlayer.GetEventMgr();
    if(pEventMgr)
    {
        pEventMgr->ClearEventByActClassID(GetActClassID());
    }
}

//获取事件信息
SEventInfoPtr CRegiserterEvent::GetEventInfo(UINT32 dwEventInstID,UINT32 dwApplyID)
{

    CEventMgrPtr pEventMgr = _rRegisterPlayer.GetEventMgr();
    if(pEventMgr)
    {
        return pEventMgr->GetEventInfo(GetActClassID(),dwEventInstID,dwApplyID);
    }

    return NULL;

}

//该事件是否完成
bool CRegiserterEvent::IsFinish(UINT32 dwEventInstID,UINT32 dwApplyID)
{
    SEventInfoPtr pEventInfo = GetEventInfo(dwEventInstID,dwApplyID);
    if(NULL == pEventInfo)
    {
        return false;
    }

    return eEventStatus_Finish == pEventInfo->wEventStatus; 
}

TMapEventCFGExPtr CEventMgr::_mapEventCFGExPtr;
TMapGlobalEvent CEventMgr::_mapGlobalEvent;
TMapMapEventInst  CEventMgr::_mapMapEventInst;
TMapDataUploadPtr CEventMgr::_mapDataUploadPtr;
CEventMgr::CEventMgr(CPlayer& rPlayer):_rPlayer(rPlayer)
{
    _bLog = true;
    _vecRegiserterEventPtr.resize(eActclass_End,NULL);
}

bool CEventMgr::EventInit()
{
    string strPath = Config._strConfigDir + "Conf/Table/EventCenter.xml";
    CEventCenterLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        return false;
    }

    for(size_t i = 0; i < oLoader._vecData.size(); ++i)
    {
        SEventCenterCFG* pCFG = oLoader._vecData[i];
        if(pCFG)
        {
            SEventCFGExPtr pEvent(new SEventCFGEx);
            pEvent->CopyFrom(*pCFG);
            Tokenizer tk(pCFG->_VecParamLimit, ","); 
            for (size_t i = 0; i < tk.size(); ++i)
            {
                UINT32 dwValue = atoi(tk[i].c_str());
                pEvent->_vecParam.push_back(dwValue);
            }
            CEventMgr::_mapEventCFGExPtr.insert(make_pair(pEvent->_EventInstID,pEvent));

            auto itr = _mapMapEventInst.find(pEvent->_EventType);
            if(itr != _mapMapEventInst.end())
            {
                itr->second.push_back(pEvent->_EventInstID);
            }
            else
            {
                TVecUINT32 vecEventInst;
                vecEventInst.push_back(pEvent->_EventInstID);
                _mapMapEventInst.insert(make_pair(pEvent->_EventType,vecEventInst));
            }


            if(pEvent->_EventType >= eEventType_Max)
            {
                LOG_CRI<<"Error evnet type:"<<pEvent->_EventType; 

                //return false;
            }

        }
    }


    strPath = Config._strConfigDir + "Conf/Table/DataUpload.xml";
    CDataUploadLoader oDataUploadLoader;
    if(!oDataUploadLoader.LoadData(strPath))
    {
        return false;
    }

    for(size_t i=0;i < oDataUploadLoader._vecData.size(); i++)
    {
        SDataUploadCFG *pCFG = oDataUploadLoader._vecData[i];
        SDataUploadCFGPtr pCFGPtr(new SDataUploadCFG);
        *pCFGPtr=*pCFG; 
        _mapDataUploadPtr.insert(make_pair(pCFGPtr->_EventID,pCFGPtr));
    }

    return true;
}

SEventCFGExPtr CEventMgr::GetEventByID(UINT32 dwEventID)
{
    auto itr = CEventMgr::_mapEventCFGExPtr.find(dwEventID);
    if(itr != CEventMgr::_mapEventCFGExPtr.end())
    {
        return itr->second;
    }
    return NULL;
}
void CEventMgr::DoEventForTask(EventType eEvent,const TVecINT32& vecParam,UINT32 dwEventTimer)
{
    INT32 dwValue = 1;
    EProcessAction eTaskAction = eProcessAction_none;
    EProcessAction eTaskAction2 = eProcessAction_none;
    switch(eEvent)
    {
        case eEventType_TrumpForging:
            {
                eTaskAction = eProcessAction_UpdateTrump;
                if(vecParam.size() >= 2 )
                {
                    dwValue = vecParam[1];
                }
                eTaskAction2 = eProcessAction_SpecialTrumpUpdate;

            }
            break;
        case eEventType_HorseUpgrade:
            {
                eTaskAction = eProcessAction_MountsUp;
                if(vecParam.size() >= 3)
                {
                    dwValue = vecParam[2];
                }
                else
                {
                    LOG_CRI<<"Error param eEventType_HorseUpgrade < 3";
                }

            }
            break;
        case eEventType_DivisionFinish:
            {
                eTaskAction = eProcessAction_FinishGroupTask;
            }
            break;
        case eEventType_GovernmentTaskFinish:
            {
                eTaskAction = eProcessAction_FinishYaMenYask;
            }
            break;
        case eEventType_PlayerDujieSuccess: 
            {
                eTaskAction = eProcessAction_FighterDuJie;
                eTaskAction2 = eProcessAction_SpecialHeroDuJie;
            }
            break;
        case eEventType_FighterSkillUpgrade: 
            {
                eTaskAction =  eProcessAction_FighterSkillUpLevel;
            }
            break;
        case eEventType_GuildJoining:
            {
                eTaskAction =   eProcessAction_JoinGuild;
            }
            break;
        case eEventType_GuildDonate:
            {
                eTaskAction =  eProcessAction_GuildContrib;
            }
            break;
        case eEventType_ExperienceChallenge:
            {
                eTaskAction =   eProcessAction_ArenaChallenge;
            }
            break;
        case eEventType_ArenaChallenge:
            {
                eTaskAction =   eProcessAction_LadderChallenge;
            }
            break;
        case eEventType_SkillUpgrade:
            {
                eTaskAction =   eProcessAction_Skill;
            }
            break;
        case eEventType_DungeonAutoFight:
            {
                eTaskAction =   eProcessAction_Chest;
            }
            break;
        case eEventType_DemonTowerHighestChanging:
            {
                eTaskAction =  eProcessAction_TowerLevel;
            }
            break;
        case eEventType_TeamBattleVictory:
            {
                eTaskAction = eProcessAction_mCopy;
            }
            break;
        case eEventType_FighterLevelUp:
            {
                eTaskAction =  eProcessAction_SpecialHeroLevel;
            }
            break;
        case eEventType_FighterLearningRecipe:
            {
                eTaskAction =  eProcessAction_HeroXinFa;
            }
            break;
        case eEventType_WorldBossAttack:
            {
                eTaskAction =  eProcessAction_WorldBoss;
            }
            break;
        case eEventType_MysteryTreasureJoin:
            {
                eTaskAction =  eProcessAction_ZhanQi;
            }
            break;
        case eEventType_TrumpEquip:
            {
                eTaskAction =  eProcessAction_ActiveNewEquipTrump;
            }
            break;
        case eEventType_TrumpToStrongSucess:
        case eEventType_TrumpToStrongFaild:
            {
                eTaskAction =  eProcessAction_StrongEquipTrump;
            }
            break;
        case eEventType_TrumpPu:
            {
                eTaskAction =  eProcessAction_XiLianEquipTrump;
            }
            break;
        case eEventType_TrumpDes:
            {
                eTaskAction =  eProcessAction_DeComposeEquipTrump;
            }
            break;
        case eEventType_ShenglingPlay:
            {
                eTaskAction =  eProcessAction_EnterShengLing;
            }
            break;
        default:
            break;
    }
    if(eTaskAction != eProcessAction_none)
    { 
        _rPlayer.GetUser().GetTaskPkg().OnAction(_rPlayer,eTaskAction,(UINT32)dwValue,dwEventTimer);
    }
    if(eTaskAction2 != eProcessAction_none)
    { 
        _rPlayer.GetUser().GetTaskPkg().OnAction(_rPlayer,eTaskAction2,(UINT32)dwValue,dwEventTimer);
    }
}

const UINT32 TASK_INSTID      = 30539; //任务事件
const UINT32 NEWPLAYER_INSTID = 30540; //新手引导事件
void CEventMgr::OnUDPLog(SEventInfoPtr pEventInfoPtr, const TVecINT32& vecParam,const string& strParam,bool bLog)
{
    if(!bLog)
    {
        return;
    }
    SDataUploadCFGPtr pDataUploadCFG = GetUDPLogCFG(pEventInfoPtr->dwEventInstID);
    //udp log
    if(pDataUploadCFG)
    {
        ostringstream ostr;
        if(999 == pDataUploadCFG->_Para)
        {
            ostr<<strParam;
        }
        else if(998 == pDataUploadCFG->_Para)
        {
            for(size_t i = 0; i < vecParam.size();i++)
            {
                ostr<<vecParam[i]<<";";
            }
        }
        else
        {
            if(0 == pDataUploadCFG->_Para)
            {
                ostr<<1;
            }
            else if(static_cast<size_t>((pDataUploadCFG->_Para-1)) < vecParam.size())
            {
                ostr<<vecParam[pDataUploadCFG->_Para-1];
            }
            else
            {
                ostr<<1;
            }
        }

        if(NEWPLAYER_INSTID == pEventInfoPtr->dwEventInstID)
        {
            Tokenizer tk(strParam, ",");
            if(tk.size() < 2 )
            {
                LOG_CRI<<"Error guide "<<strParam;
                return;
            }

            UINT32 dwTaskID = atoi(tk[0].c_str())*10 + atoi(tk[1].c_str());
            g_Game2CenterLog.Send_LogAct(_rPlayer.GetUserID(),pDataUploadCFG->_category,NumberToString(dwTaskID),"","","","",1);

        }
        else if(TASK_INSTID == pEventInfoPtr->dwEventInstID)
        {
            if(vecParam.size()< 1)
            {
                LOG_CRI<<"Error task param!!!";
                return;
            }
            UINT32 dwTaskID = (UINT32)(vecParam[0]);
            g_Game2CenterLog.Send_LogGuideChange(_rPlayer.GetUserID(),"guide",NumberToString(dwTaskID));
        }
        else
        {
            g_Game2CenterLog.Send_LogAct(_rPlayer.GetUserID(),pDataUploadCFG->_category,pDataUploadCFG->_action,ostr.str(),"","","",1);
        }


        if(pEventInfoPtr->wEventStatus == eEventStatus_Finish)
        {
            RemoveEvent((EActClass)pEventInfoPtr->byActClassID,pEventInfoPtr->dwEventInstID,pEventInfoPtr->dwApplyID);
            AddEvent(eActClass_UDPLOG,pEventInfoPtr->dwEventInstID,pEventInfoPtr->dwApplyID,0);
        }
    }
    else
    {
        RemoveEvent((EActClass)pEventInfoPtr->byActClassID,pEventInfoPtr->dwEventInstID,pEventInfoPtr->dwApplyID);
    }

}
void CEventMgr::OnEvent(const EventType eEvent, const TVecINT32& vecParam,const string& strParam,bool bLog,UINT32 dwEventTime)
{
    UINT32 dwOnEventBeginTime = time(NULL);
    if(_bLog)
    {
        if( eEvent != eEventType_OnlineTime)
        {
            //LOG_INF<<"CEventMgr::OnEvent eEvent: "<<eEvent<<" begin time: "<<time(NULL);
            //for(size_t i = 0; i < vecParam.size(); ++i)
            //{
            //    LOG_INF<<"CEventMgr::OnEvent Param: "<<vecParam[i];
            //}
        }
    }

    //task
    DoEventForTask(eEvent,vecParam,dwEventTime);
    

    if(eEvent == eEventType_ExperienceLevelChange)
    {
        CBubbleOwnerPtr pBubbleOwner = _rPlayer.GetUser().GetBubbleOwner();
        if (pBubbleOwner)
        {
            TVecINT64 vecBubParam;
            if(vecParam.size() == 2)
            {
                if(vecParam[0] == vecParam[1])
                {
                    vecBubParam.push_back(vecParam[0]);
                    pBubbleOwner->CreateBubble(15, vecBubParam);

                }
                else
                { 
                    for(auto it = vecParam.begin();it != vecParam.end();it++)
                    {
                        vecBubParam.push_back(*it);
                    }
                    pBubbleOwner->CreateBubble(13, vecBubParam);

                }
            }
        }
    }
    else if(eEvent == eEventType_ArenaRankDwon)
    {
        CBubbleOwnerPtr pBubbleOwner = _rPlayer.GetUser().GetBubbleOwner();
        if (pBubbleOwner)
        {
            TVecINT64 vecBubParam;
            for(auto it = vecParam.begin();it != vecParam.end();it++)
            {
                vecBubParam.push_back(*it);
            }
            pBubbleOwner->CreateBubble(14, vecBubParam);
        }
    }

    if( eEvent >= eEventType_Max)
    {
        LOG_CRI<<"Error EventType: "<<eEvent;
        return;
    }

    TMapEventInfoPtr* pMapEventInfoPtr = GetMapEventInfo(eEvent);
    if(NULL == pMapEventInfoPtr)
    {
        //LOG_CRI<<"unuse EventType:"<<eEvent;
        return;
    }

    TVecApplyKey vecDelApplyKey;

    //LOG_INF<<"pMapEventInfoPtr:"<<pMapEventInfoPtr->size();
    for(auto itr = pMapEventInfoPtr->begin(); itr != pMapEventInfoPtr->end(); )
    {
        auto itrTemp = itr;
        itr++;

        SEventInfoPtr pEventInfoPtr = itrTemp->second;

        //checktime
        if(pEventInfoPtr->dwStartTime&&dwEventTime)
        {
            if(dwEventTime < pEventInfoPtr->dwStartTime)
            {
                continue;
            }
        }
        //process
        //
        bool bNotify = OnProcess(pEventInfoPtr,vecParam);
        if(!bNotify)
        {
            continue;
        }

        if(IsAllFinish(pEventInfoPtr))
        {
            SApplyKey oKey(pEventInfoPtr->byActClassID,pEventInfoPtr->dwApplyID);
            vecDelApplyKey.push_back(oKey);
        }
        else
        {
            if(pEventInfoPtr->bySave)
            {
                Update2DB(*pEventInfoPtr);
            }

        }

        if(pEventInfoPtr->byActClassID == (UINT8)eActClass_UDPLOG)
        {
            //udplog 特殊处理
            OnUDPLog(pEventInfoPtr,vecParam,strParam,bLog);
        }
        else
        {

            CRegiserterEvent* pRegiserterEvent = GetActByClassID((EActClass)pEventInfoPtr->byActClassID);
            if(pRegiserterEvent)
            {

                //LOG_INF<<"pRegiserterEvent->OnEvent begin byActClassID:"<<pEventInfoPtr->byActClassID<<" dwApplyID:"<<pEventInfoPtr->dwApplyID;
                pRegiserterEvent->OnEvent(pEventInfoPtr);
                //LOG_INF<<"pRegiserterEvent->OnEvent  end";
            }
        }


    }

    //删除已经完成事件
    for(size_t i=0; i<vecDelApplyKey.size(); i++)
    {
        SApplyKey& oKey = vecDelApplyKey[i];
        ClearApply((EActClass)oKey._byActClassID,oKey._dwApplyID);
    }

    //LOG_INF<<"CEventMgr::OnEvent eEvent: "<<eEvent<<" end time: "<<time(NULL);

    if(time(NULL) - dwOnEventBeginTime > 2 )
    {
        LOG_CRI<<"more delay time!!! "<<(time(NULL) - dwOnEventBeginTime);
    }

}

UINT32 DiffDays(UINT32 dwTime1,UINT32 dwTime2)
{
    time_t t1=(time_t)dwTime1;
    time_t t2=(time_t)dwTime2;
    //保证dwTime2=dwTime1
    if(dwTime1>dwTime2)
    {
        t1 = dwTime2;
        t2 =dwTime1;
    }

    struct tm *pTm2 = localtime(&t2);
    pTm2->tm_sec=0;
    pTm2->tm_min=0;
    pTm2->tm_hour=0;
    UINT32 dwMaxMidTime=mktime(pTm2);

    struct tm *pTm1 = localtime(&t1);
    pTm1->tm_sec=0;
    pTm1->tm_min=0;
    pTm1->tm_hour=0;
    UINT32 dwMinMidTime=mktime(pTm1);

    //LOG_INF<<"DiffDays:"<<dwMaxMidTime<<"|"<<dwMinMidTime<<"->"<<(dwMaxMidTime-dwMinMidTime)/(3600*24);

    return (UINT32)((dwMaxMidTime-dwMinMidTime)/(3600*24));
}

bool IsSaveDB(UINT32 dwOpType)
{
    EEventOp eOpType = (EEventOp)dwOpType;
    switch(eOpType)
    {
        case eEventOp_Sum:
        case eEventOp_TotalLogin:
        case eEventOp_ContinueLogin:
            {
                return true;
            }
            break;
        default:
            return false;
    }

    return true;
}

bool CEventMgr::CheckIsSaveDB(SEventCFGExPtr pEventCFGEx)
{
    if(IsSaveDB(pEventCFGEx->_OpType1))
    {
        return true;
    }

    if(IsSaveDB(pEventCFGEx->_OpType2))
    {
        return true;
    }

    if(IsSaveDB(pEventCFGEx->_OpVecType))
    {
        return true;
    }

    return false;
}

bool CEventMgr::OnProcess(SEventInfoPtr pEventInfoPtr,const TVecINT32& vecParam)
{
    bool bNotify = false;

    SEventCFGExPtr pEventCFGEx = GetEventByID(pEventInfoPtr->dwEventInstID);
    if(NULL == pEventCFGEx)
    {
        LOG_CRI<<"Error dwEventInstID:"<<pEventInfoPtr->dwEventInstID;
        return bNotify;
    }

    if(pEventInfoPtr->wEventStatus == eEventStatus_Finish)
    {
        return bNotify;
    }

    if(CheckIsSaveDB(pEventCFGEx))
    {
        pEventInfoPtr->bySave = 1;
    }

    UINT16 wCondID = pEventCFGEx->_GetCondType;
    if(wCondID)
    {
        CUser& rUser=_rPlayer.GetUser();
        bool bRet = CGetCondMgr::Instance().TestCond(rUser, wCondID);
        if(bRet)
        {
            pEventInfoPtr->wEventStatus = eEventStatus_Finish;
            return true;
        }

        return false;
    }

    if(pEventCFGEx->_OpType1)
    {
        if(vecParam.size()<1&&pEventCFGEx->_OpType1!= (UINT16)eEventOp_Sum)
        {
            return bNotify;
        }
        EEventOp eOpType1 = (EEventOp)pEventCFGEx->_OpType1;
        switch(eOpType1)
        {
            case eEventOp_Equal:
                {
                    if(pEventCFGEx->_ParamLimit1 != (UINT32)vecParam[0])
                    {
                        return bNotify;
                    }
                }
                break;
            case eEventOp_GreaterOrEqual:
                {
                    if((UINT32)vecParam[0] >= pEventCFGEx->_ParamLimit1)
                    {
                    }
                    else
                    {
                        return bNotify;
                    }
                }
                break;
            case eEventOp_Sum:
                {
                    if(pEventInfoPtr->dwParam1< pEventCFGEx->_ParamLimit1)
                    {
                        bNotify = true;

                        pEventInfoPtr->bySave = true;

                        if(vecParam.size()>=1)
                        {
                            pEventInfoPtr->dwParam1 += (UINT32)vecParam[0];
                        }
                        else
                        {
                            pEventInfoPtr->dwParam1 += 1;
                        }
                        if(pEventInfoPtr->dwParam1 >= pEventCFGEx->_ParamLimit1)
                        {
                            pEventInfoPtr->dwParam1 = pEventCFGEx->_ParamLimit1;
                            //Update2DB(*pEventInfoPtr);
                        }
                        else
                        {
                            return bNotify;
                        }
                    }


                }
                break;
            case eEventOp_LessOrEqual:
                {
                    if( (UINT32)vecParam[0] <=  pEventCFGEx->_ParamLimit1)
                    {
                    }
                    else
                    {
                        return bNotify;
                    }
                }
                break;
            default:
                {
                    return bNotify;
                }
        }
    }

    if(pEventCFGEx->_OpType2)
    {
        if(vecParam.size() < 2&& pEventCFGEx->_OpType2 != eEventOp_Sum)
        {
            return bNotify;
        }

        EEventOp eOpType2 = (EEventOp)pEventCFGEx->_OpType2;
        switch(eOpType2)
        {
            case eEventOp_Equal:
                {

                    if(pEventCFGEx->_ParamLimit2 != (UINT32)vecParam[1])
                    {
                        return bNotify;
                    }
                }
                break;
            case eEventOp_GreaterOrEqual:

                {
                    if( (UINT32)vecParam[1] >= pEventCFGEx->_ParamLimit2)
                    {
                    }
                    else
                    {
                        return bNotify;
                    }
                }
                break;
            case eEventOp_Sum:
                {
                    if((UINT32)pEventInfoPtr->dwParam2< pEventCFGEx->_ParamLimit2)
                    {
                        bNotify = true;
                        pEventInfoPtr->bySave = true;
                        if(vecParam.size()>=2)
                        {
                            pEventInfoPtr->dwParam2 += (UINT32)vecParam[1];
                        }
                        else
                        {
                            pEventInfoPtr->dwParam2 += 1;
                        }
                        if((UINT32)pEventInfoPtr->dwParam2 >= pEventCFGEx->_ParamLimit2)
                        {
                            pEventInfoPtr->dwParam2 = pEventCFGEx->_ParamLimit2;
                            //Update2DB(*pEventInfoPtr);
                        }
                        else
                        {
                            return bNotify;
                        }
                    }
                }
                break;
            case eEventOp_LessOrEqual:
                {
                    if( (UINT32)vecParam[1] <= pEventCFGEx->_ParamLimit2)
                    {
                    }
                    else
                    {
                        return bNotify;
                    }
                }
                break;
            default:
                {
                    return bNotify;
                }
        }
    }

    if(pEventCFGEx->_OpVecType&& !pEventCFGEx->_vecParam.empty())
    {
        EEventOp eOpVecType = (EEventOp)pEventCFGEx->_OpVecType;
        switch(eOpVecType)
        {
            case eEventOp_Equal:
                {
                    if(pEventCFGEx->_vecParam.size()<1) return bNotify;
                    if(vecParam.size()<3) return bNotify;

                    UINT32 dwParam = pEventCFGEx->_vecParam[0];

                    if(dwParam != (UINT32)vecParam[2])
                    {
                        return bNotify;
                    }
                }
                break;
            case eEventOp_GreaterOrEqual:

                {
                    if(pEventCFGEx->_vecParam.size()<1) return bNotify;
                    if(vecParam.size()<3) return bNotify;
                    UINT32 dwParam = pEventCFGEx->_vecParam[0];
                    if( (UINT32)vecParam[2] >= dwParam)
                    {
                    }
                    else
                    {
                        return bNotify;
                    }
                }
                break;
            case eEventOp_LessOrEqual:
                {
                    if(pEventCFGEx->_vecParam.size()<1) return bNotify;
                    if(vecParam.size()<3) return bNotify;
                    UINT32 dwParam = pEventCFGEx->_vecParam[0];
                    if( (UINT32)vecParam[2] <= dwParam)
                    {
                    }
                    else
                    {
                        return bNotify;
                    }
                }
                break;

            case eEventOp_Sum:

                {
                    if(pEventCFGEx->_vecParam.size()<1)
                    {
                        return bNotify;

                    }

                    const UINT32 dwTotal = pEventCFGEx->_vecParam[0];
                    UINT32 dwAdd = 1;
                    if(vecParam.size() >= 3)
                    {
                        dwAdd = (UINT32)vecParam[2];

                    }

                    if(pEventInfoPtr->dwParam1< dwTotal)
                    {
                        bNotify = true;
                        pEventInfoPtr->dwParam1 += dwAdd;

                        pEventInfoPtr->bySave = true;

                        if(pEventInfoPtr->dwParam1 >= dwTotal)
                        {
                            pEventInfoPtr->dwParam1 = dwTotal;
                            //Update2DB(*pEventInfoPtr);
                        }
                        else
                        {
                            return bNotify;
                        }
                    }
                }
                break;

            case eEventOp_TotalLogin: //累计登陆
                {
                    if(pEventCFGEx->_vecParam.size()<1)
                    {
                        return bNotify;

                    }

                    bNotify = true;

                    UINT32 dwTotalDay = pEventCFGEx->_vecParam[0];
                    UINT32 dwDiff = DiffDays(pEventInfoPtr->dwParam2,time(NULL));
                    if(dwDiff>0)
                    {
                        pEventInfoPtr->dwParam1 +=1;
                        pEventInfoPtr->dwParam2 = time(NULL);
                        LOG_CRI<<"TOTAL DAYS "<<pEventInfoPtr->dwParam1<<"---"<<pEventInfoPtr->dwParam2;
                    }

                    if(pEventInfoPtr->dwParam1>=dwTotalDay)
                    {
                        //pEventInfoPtr->dwParam1 = dwTotalDay;
                    }
                    else
                    {
                        return bNotify;
                    }
                }
                break;
            case eEventOp_ContinueLogin://连续登陆
                {

                    if(pEventCFGEx->_vecParam.size()<1)
                    {
                        return bNotify;

                    }


                    UINT32 dwTotalDay = pEventCFGEx->_vecParam[0];
                    UINT32 dwDiff = DiffDays(pEventInfoPtr->dwParam2,time(NULL));
                    if(dwDiff == 0)
                    {
                        return bNotify;
                    }
                    else if(dwDiff==1)
                    {

                        bNotify = true;
                        pEventInfoPtr->dwParam1 +=1;
                        pEventInfoPtr->dwParam2 = time(NULL);
                    }
                    else
                    {

                        bNotify = true;
                        pEventInfoPtr->dwParam1 = 1;
                        pEventInfoPtr->dwParam2 = time(NULL);
                    }

                    if(pEventInfoPtr->dwParam1>=dwTotalDay)
                    {
                        pEventInfoPtr->dwParam1 = dwTotalDay;
                    }
                    else
                    {
                        return bNotify;
                    }

                }
                break;
            case eEventOp_MinCount:
                {
                    if(pEventCFGEx->_vecParam.size()<2)
                    {
                        return bNotify;

                    }

                    UINT32 dwMinValue = pEventCFGEx->_vecParam[0];
                    UINT32 dwLimitCount =  pEventCFGEx->_vecParam[1];

                    UINT32 dwCount = 0;
                    for(UINT32 i = 2; i < vecParam.size(); i++)
                    {
                        if((UINT32)vecParam[i] >= dwMinValue)
                        {
                            dwCount++;
                        }
                    }

                    //完成
                    if(dwCount>=dwLimitCount)
                    {
                        pEventInfoPtr->dwParam1 = dwLimitCount;
                        bNotify = true;
                    }
                    else
                    {
                        if(dwCount)
                        {
                            pEventInfoPtr->dwParam1 = dwCount;
                            bNotify = true;
                        }

                        return bNotify;

                    }

                }
                break;
            default:
                {
                    return bNotify;
                }
        }
    }
    if(TASK_INSTID != pEventInfoPtr->dwEventInstID)
        pEventInfoPtr->wEventStatus = eEventStatus_Finish; 
    //Update2DB(*pEventInfoPtr);
    return true;
}

void CEventMgr::RegisterClass(CRegiserterEvent* pRegiserterEvent)
{
    if(NULL == pRegiserterEvent)
    {
        return;
    }

    if(pRegiserterEvent->GetActClassID() < _vecRegiserterEventPtr.size())
    {
        _vecRegiserterEventPtr[pRegiserterEvent->GetActClassID()] = pRegiserterEvent;
    }


}

bool CEventMgr::AddEvent(EActClass eActClassID,UINT32 dwEventInstID,UINT32 dwApplyID,UINT32 dwStartTime)
{
    SEventCFGExPtr pEventCFGEx = GetEventByID(dwEventInstID);
    if(NULL == pEventCFGEx)
    {
        LOG_CRI<<"Error dwEventInstID:"<<dwEventInstID;
        return false;
    }

    EventType eEventType = (EventType)pEventCFGEx->_EventType;

    SEventInfoPtr pInfo(new SEventInfo);
    pInfo->qwRoleID = _rPlayer.GetRoleID();
    pInfo->byActClassID = eActClassID;
    pInfo->dwEventInstID = dwEventInstID;
    pInfo->dwApplyID = dwApplyID;
    pInfo->wEventStatus = eEventStatus_Init; 
    pInfo->dwStartTime = dwStartTime;

    TMapEventInfoPtr* pMapEventInfo = GetMapEventInfo(eEventType);
    if(NULL == pMapEventInfo)
    {
        TMapEventInfoPtr mapEventInfoPtr;
        _mapMapEventInfoPtr.insert(make_pair(eEventType,mapEventInfoPtr));

    }

    pMapEventInfo = GetMapEventInfo(eEventType);
    if(NULL == pMapEventInfo)
    {
        LOG_CRI<<"fatal error!!!";
        return false;
    }

    bool bFinish = false;

    UINT16 wCondID = pEventCFGEx->_GetCondType;
    if(wCondID)
    {
        CUser& rUser=_rPlayer.GetUser();
        bool bRet = CGetCondMgr::Instance().TestCond(rUser, wCondID);
        if(bRet)
        {
            pInfo->wEventStatus = eEventStatus_Finish;
            bFinish = true;
        }
    }

    InsertEventInfo(*pMapEventInfo,pInfo);

    // LOG_INF << "AddEvent:" << eActClassID << "|" << dwEventInstID << "|" << dwApplyID << "," "eventType:" << eEventType << "," "size:" << pMapEventInfo->size();

    if(bFinish)
    {
        CRegiserterEvent* pRegiserterEvent = GetActByClassID((EActClass)pInfo->byActClassID);
        if(pRegiserterEvent)
        {
            pRegiserterEvent->OnEvent(pInfo);
        }
    }

    return bFinish;
}

void CEventMgr::RemoveEvent(EActClass eActClassID,UINT32 dwEventInstID,UINT32 dwApplyID)
{
    SEventCFGExPtr pEventCFGEx = GetEventByID(dwEventInstID);
    if(NULL == pEventCFGEx)
    {
        LOG_CRI<<"Error dwEventInstID:"<<dwEventInstID;
        return;
    }

    EventType eEventType = (EventType)pEventCFGEx->_EventType;
    TMapEventInfoPtr* pMapEventInfo = GetMapEventInfo(eEventType);
    if(NULL == pMapEventInfo)
    {
        return;
    }

    //LOG_INF<<"RemoveEvent"<<" eActClassID:"<<eActClassID<<" dwEventInstID:"<<dwEventInstID<<" dwApplyID:"<<dwApplyID<<" eEventType:"<<eEventType;

    RemoveEventInfo(*pMapEventInfo,eActClassID,dwEventInstID,dwApplyID);
}

void CEventMgr::ClearEventByActClassID(EActClass eActClassID)
{

    for(auto itr = _mapMapEventInfoPtr.begin(); itr != _mapMapEventInfoPtr.end();)
    {
        auto itrTmp = itr;
        itr++;
        RemoveEventByClassID(itrTmp->second,eActClassID);
    }

    ClearApply(eActClassID);

}

void CEventMgr::ClearApply(EActClass eActClassID,UINT32 dwApplyID)
{
    SApplyKey oKey(eActClassID,dwApplyID); 
    auto itr = _mapApply.find(oKey);
    if(itr == _mapApply.end())
    {
        return;
    }

    //下面功能暂时不做
    /*
       for(size_t i = 0; i < itr->second.size(); i++)
       {
       UINT32 dwEventInstID = itr->second[i];
       RemoveEvent(eActClassID,dwEventInstID,dwApplyID);
       }
       */

}

void CEventMgr::ClearApply(EActClass eActClassID)
{
    for(auto itr = _mapApply.begin(); itr != _mapApply.end();)
    {
        auto itrTmp = itr;
        itr++;
        if(itrTmp->first._byActClassID == eActClassID)
        {
            _mapApply.erase(itrTmp);
        }
    }
}

//是否所有事件实例都完成
bool CEventMgr::IsAllFinish(SEventInfoPtr pEventInfoPtr)
{
    if(eEventStatus_Finish != pEventInfoPtr->wEventStatus)
    {
        return false;
    }

    //保存1个应用关注的事件实例
    SApplyKey oKey(pEventInfoPtr->byActClassID,pEventInfoPtr->dwApplyID); 
    auto itr = _mapApply.find(oKey);
    if(itr == _mapApply.end())
    {
        return true;
    }

    for(size_t i = 0; i < itr->second.size(); i++)
    {
        UINT32 dwEventInstID = itr->second[i];
        if(dwEventInstID == pEventInfoPtr->dwEventInstID)
        {
            continue;
        }

        SEventInfoPtr pEvent = GetEventInfo((EActClass)pEventInfoPtr->byActClassID,dwEventInstID,pEventInfoPtr->dwApplyID);
        if(NULL == pEvent)
        {
            return false;
        }

        if(eEventStatus_Finish != pEvent->wEventStatus)
        {
            return false;
        }
    }

    return true;

}

CRegiserterEvent* CEventMgr::GetActByClassID(EActClass eActClassID)
{
    if(eActClassID < _vecRegiserterEventPtr.size())
    {
        return _vecRegiserterEventPtr[eActClassID];
    }

    return NULL;
}


SEventInfoPtr CEventMgr::GetEventInfo(EActClass eActClassID,UINT32 dwEventInstID,UINT32 dwApplyID)
{
    SEventCFGExPtr pEventCFGEx = GetEventByID(dwEventInstID);
    if(NULL == pEventCFGEx)
    {
        LOG_CRI<<"Error dwEventInstID:"<<dwEventInstID;
        return NULL;
    }

    EventType eEventType = (EventType)pEventCFGEx->_EventType;
    TMapEventInfoPtr* pMapEventInfo = GetMapEventInfo(eEventType);
    if(NULL == pMapEventInfo)
    {
        return NULL;
    }

    return FindEventInfoInMap(*pMapEventInfo,eActClassID,dwEventInstID,dwApplyID);

}

SEventInfoPtr CEventMgr::FindEventInfoInMap(TMapEventInfoPtr& mapEventInfoPtr,EActClass eActClassID,UINT32 dwEventInstID,UINT32 dwApplyID)
{
    SEventKey oKey(eActClassID,dwEventInstID,dwApplyID);
    auto itr = mapEventInfoPtr.find(oKey);
    if(itr != mapEventInfoPtr.end())
    {
        return itr->second;
    }
    return NULL;
}

bool CEventMgr::InsertEventInfo(TMapEventInfoPtr& mapEventInfoPtr,SEventInfoPtr pEventInfoPtr)
{
    SEventKey oKey(pEventInfoPtr->byActClassID,pEventInfoPtr->dwEventInstID,pEventInfoPtr->dwApplyID);
    if(mapEventInfoPtr.find(oKey) != mapEventInfoPtr.end())
    {
        return false;
    }

    mapEventInfoPtr.insert(make_pair(oKey,pEventInfoPtr));

    //保存1个应用关注的事件实例
    SApplyKey oApplayKey(pEventInfoPtr->byActClassID,pEventInfoPtr->dwApplyID); 
    auto itr = _mapApply.find(oApplayKey);
    if(itr != _mapApply.end())
    {
        itr->second.push_back(pEventInfoPtr->dwEventInstID);
    }
    else
    {
        TVecUINT32 vecInstID;
        vecInstID.push_back(pEventInfoPtr->dwEventInstID);
        _mapApply.insert(make_pair(oApplayKey,vecInstID));
    }

    return true;
}

void CEventMgr::RemoveEventByClassID(TMapEventInfoPtr& mapEventInfoPtr,EActClass eActClassID)
{

    for(auto itr = mapEventInfoPtr.begin(); itr != mapEventInfoPtr.end();)
    {
        auto itrTmp = itr;
        itr++;
        if(itrTmp->second->byActClassID == eActClassID)
        {
            if(itrTmp->second->bySave)
                Update2DB(*(itrTmp->second),eOpDel); 
            mapEventInfoPtr.erase(itrTmp);
        }
    }

}

void CEventMgr::RemoveEventInfo(TMapEventInfoPtr& mapEventInfoPtr,EActClass eActClassID,UINT32 dwEventInstID,UINT32 dwApplyID)
{
    SEventKey oKey(eActClassID,dwEventInstID,dwApplyID);
    auto itr = mapEventInfoPtr.find(oKey);
    if(itr != mapEventInfoPtr.end())
    {
        //remove from db
        if(itr->second->bySave)
        {
            Update2DB(*(itr->second),eOpDel);

        }
        mapEventInfoPtr.erase(oKey);
    }
}

void CEventMgr::ClearEventInfo(TMapEventInfoPtr& mapEventInfoPtr)
{
    for(auto itr = mapEventInfoPtr.begin(); itr != mapEventInfoPtr.end(); ++itr)
    {
        //remove from db 
        if(itr->second->bySave)
        {
            Update2DB(*(itr->second),eOpDel);
        }
    }

    mapEventInfoPtr.clear();
}

bool CEventMgr::LoadFromDB(const RoleDataInfo& rRoleDataInfo)
{
    for(size_t i = 0; i < rRoleDataInfo.vecEventInfo.size(); i++)
    {
        const SEventInfo& rInfo = rRoleDataInfo.vecEventInfo[i];
        {
            SEventCFGExPtr pEventCFGEx = GetEventByID(rInfo.dwEventInstID);
            if(NULL == pEventCFGEx)
            {
                LOG_CRI<<"Error dwEventInstID:"<<rInfo.dwEventInstID;
                continue;
            }

            EventType eEventType = (EventType)pEventCFGEx->_EventType;
            SEventInfoPtr pEventInfo(new SEventInfo);
            *pEventInfo = rInfo;

            TMapEventInfoPtr* pMapEventInfo = GetMapEventInfo(eEventType);
            if(NULL == pMapEventInfo)
            {
                TMapEventInfoPtr mapEventInfoPtr;
                _mapMapEventInfoPtr.insert(make_pair(eEventType,mapEventInfoPtr));
            }

            pMapEventInfo = GetMapEventInfo(eEventType);
            if(NULL == pMapEventInfo)
            {
                LOG_CRI<<"fatal error!!!";
                continue;
            }

            InsertEventInfo(*pMapEventInfo,pEventInfo);


        }
    }

    for(auto itr = _mapDataUploadPtr.begin(); itr != _mapDataUploadPtr.end(); itr++)
    {
        if(itr->second->_EventID)
            AddEvent(eActClass_UDPLOG,itr->second->_EventID,itr->second->_EventID,0);
    }

    return true;

}

void CEventMgr::Update2DB(SEventInfo& rInfo, EDataChange eDataChange)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;

    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeEventInfo, eDataChange, strData);
}

//获取事件下面的列表
TMapEventInfoPtr* CEventMgr::GetMapEventInfo(EventType eEventType)
{
    auto itr = _mapMapEventInfoPtr.find(eEventType);
    if(itr != _mapMapEventInfoPtr.end())
    {
        return &itr->second;
    }

    return NULL;
}
//获取udplog配置
SDataUploadCFGPtr CEventMgr::GetUDPLogCFG(UINT32 dwEventInstID)
{
    auto itr = _mapDataUploadPtr.find(dwEventInstID);
    if(itr != _mapDataUploadPtr.end())
    {
        return itr->second;
    }
    return NULL;
}


void CEventMgr::RegGlobalClass(CGlobalEvent* pGlobalEvent)
{
    if(NULL == pGlobalEvent)
    {
        return;
    }

    if(_mapGlobalEvent.find(pGlobalEvent->GetActClassID()) != _mapGlobalEvent.end())
    {
        LOG_CRI<<"repeat ClassID! "<<pGlobalEvent->GetActClassID();
        return;
    }
    _mapGlobalEvent[pGlobalEvent->GetActClassID()]=pGlobalEvent;

}

void CEventMgr::PrintEventSize()
{
    for(auto itr = _mapMapEventInfoPtr.begin(); itr != _mapMapEventInfoPtr.end(); itr++)
    {
        LOG_INF<<"eEventType:"<<itr->first<<" size:"<<itr->second.size();
        for(auto itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++)
        {
            SEventInfoPtr pEventInfoPtr = itr2->second;
            LOG_INF<<"OnEvent finish byActClassID:"<<pEventInfoPtr->byActClassID<<" dwApplyID:"<<pEventInfoPtr->dwApplyID;
        }
    }

}
