#include "stdafx.h"
#include "AchievementMgr.h"
#include "Tokenizer.h"
#include "Player.h"
#include "ItemMgr.h"
#include "FighterManager.h"
#include "Protocols.h"
#include "AchievementProtS.h"
#include "LogDataDefine.h"
#include "TitleManager.h"
#include "AutoStoreMgr.h"
TMapAchievementCFGExPtr CAchievementMgr::_mapAchievementCFGExPtr;
TVecAchievementLevelCFGExPtr CAchievementMgr::_VecAchievementLevelCFGExPtr;
//std::vector<TVecAchievementCFGExPtr> CAchievementMgr::_vecEventList;

extern void GetItemFromString(TVecItemGenInfo& vecItem, const string strItem);

CAchievementMgr::CAchievementMgr(CPlayer& rPlayer):CRegiserterEvent(eActClass_Achieve,rPlayer),
    _rPlayer(rPlayer)
{
    _vecAttr.resize(EFIGHTATTR_MAX, 0.f);

    _bLog = true;
    _bGetData = false;
}

bool CAchievementMgr::AchievementInit()
{

    //_vecEventList.resize(3);

    string strPath = Config._strConfigDir + "Conf/Table/Achievement.xml";
    CAchievementLoader oAchievementLoader;
    if(!oAchievementLoader.LoadData(strPath))
    {
        return false;
    }

    for(size_t i = 0; i < oAchievementLoader._vecData.size(); ++i)
    {
        SAchievementCFG* pCFG = oAchievementLoader._vecData[i];
        if(pCFG)
        {
            SAchievementCFGExPtr pAchievement(new SAchievementCFGEx);
            pAchievement->CopyFrom(*pCFG);
            
            Tokenizer tk(pCFG->_EventGroup, ","); 
            for (size_t i = 0; i < tk.size(); ++i)
            {
               UINT32 dwValue = atoi(tk[i].c_str());
               pAchievement->_vecEventInstID.push_back(dwValue);
            }

            GetItemFromString(pAchievement->_vecPrize,pAchievement->_AwardId);
            GetItemFromString(pAchievement->_vecSharePrize,pAchievement->_ShareAwardId);

            _mapAchievementCFGExPtr.insert(make_pair(pAchievement->_ID,pAchievement));

        }
    }

    strPath = Config._strConfigDir + "Conf/Table/AchievementLevel.xml";
    CAchievementLevelLoader oAchievementLevelLoader;
    if(!oAchievementLevelLoader.LoadData(strPath))
    {
        return false;
    }

    for(size_t i = 0; i < oAchievementLevelLoader._vecData.size(); ++i)
    {
        SAchievementLevelCFG* pCFG = oAchievementLevelLoader._vecData[i];
        if(pCFG)
        {
            SAchievementLevelCFGExPtr pAchievementLevel(new SAchievementLevelCFGEx);
            pAchievementLevel->CopyFrom(*pCFG);
            _VecAchievementLevelCFGExPtr.push_back(pAchievementLevel);
        }
    }

    return true;
}

bool CAchievementMgr::ReLoadConfig(const string& strFile)
{
    string strPath;
    if("Achievement.xml" == strFile)
    {
        //_vecEventList.clear();
        //_vecEventList.resize(3);
        strPath = Config._strConfigDir + "Conf/Table/Achievement.xml";
        CAchievementLoader oAchievementLoader;
        if(!oAchievementLoader.LoadData(strPath))
        {
            return false;
        }

        for(size_t i = 0; i < oAchievementLoader._vecData.size(); ++i)
        {
            SAchievementCFG* pCFG = oAchievementLoader._vecData[i];
            if(pCFG)
            {
                SAchievementCFGExPtr pAchievement(new SAchievementCFGEx);
                pAchievement->CopyFrom(*pCFG);

                _mapAchievementCFGExPtr.insert(make_pair(pAchievement->_ID,pAchievement));

                /*

                if(pAchievement->_EventID >= _vecEventList.size())
                {
                    _vecEventList.resize(pAchievement->_EventID+3);

                }

                if(pAchievement->_EventID < _vecEventList.size())
                {
                    _vecEventList[pAchievement->_EventID].push_back(pAchievement);
                }
                else
                {
                    LOG_CRI<<"_vecEventList.size() TOO SMALLL!!";
                    return false;
                }
                */
            }
        }
    }else if("AchievementLevel.xml" == strFile)
    {
        _VecAchievementLevelCFGExPtr.clear();
        strPath = Config._strConfigDir + "Conf/Table/AchievementLevel.xml";
        CAchievementLevelLoader oAchievementLevelLoader;
        if(!oAchievementLevelLoader.LoadData(strPath))
        {
            return false;
        }

        for(size_t i = 0; i < oAchievementLevelLoader._vecData.size(); ++i)
        {
            SAchievementLevelCFG* pCFG = oAchievementLevelLoader._vecData[i];
            if(pCFG)
            {
                SAchievementLevelCFGExPtr pAchievementLevel(new SAchievementLevelCFGEx);
                pAchievementLevel->CopyFrom(*pCFG);
                _VecAchievementLevelCFGExPtr.push_back(pAchievementLevel);
            }
        }
    }
    return true;

}
void CAchievementMgr::TiggerEvent(const UINT32 dwEventId,const TVecINT32& _vecParam,const EEventCondition eEventCondition,const SEventCFGExPtr pEventCFGExPtr)
{
    if(_bLog)
    {
        LOG_INF<<"TiggerEvent dwEventId: "<<dwEventId;
    }

}

bool CAchievementMgr::IsFinished(UINT16 dwAchieveID)
{
    auto itr = _mapAchievementInfo.find(dwAchieveID);
    if(itr != _mapAchievementInfo.end())
    {
        //已经完成
        if(itr->second.dwCount != 0 )
        {
            return true;
        }
    }

    return false;

}

void CAchievementMgr::OnFinishAchieve(const SAchievementCFGExPtr& pAchievementCFGEx)
{

    UINT16 wAchieveId = pAchievementCFGEx->_ID;

    auto itr = _mapAchievementInfo.find(wAchieveId);
    if(itr != _mapAchievementInfo.end())
    {
        //已经完成
        if(itr->second.dwCount)
        {

        }
        else
        {
            itr->second.dwCount = 1;
            itr->second.dwFinishTime = time(NULL);
            OnNewFinishAchieve(pAchievementCFGEx);
            UpdateToDB(itr->second);
            NotifiyUpdate(itr->second);
            CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
            if(pEventMgr)
            {
                TVecINT32 vecParam;
                vecParam.push_back(wAchieveId);
                pEventMgr->OnEvent(eEventType_AchievementGet,vecParam);

            }
        }
    }
    else
    {
        SAchievementInfo oInfo;                                 
        oInfo.dwCount = 1;                              
        oInfo.qwRoleID = _rPlayer.GetRoleID();
        oInfo.wAchievementID = wAchieveId;
        oInfo.dwFinishTime = time(NULL);
        _mapAchievementInfo.insert(make_pair(wAchieveId,oInfo)); 
        OnNewFinishAchieve(pAchievementCFGEx);
        UpdateToDB(oInfo);
        NotifiyUpdate(oInfo);

        CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
        if(pEventMgr)
        {
            TVecINT32 vecParam;
            vecParam.push_back(wAchieveId);
            pEventMgr->OnEvent(eEventType_AchievementGet,vecParam);

        }
    }

    for(size_t i=0; i < pAchievementCFGEx->_vecEventInstID.size();i++)
    {
        RemoveEvent(pAchievementCFGEx->_vecEventInstID[i],wAchieveId);
    }

    if(_bLog)
    {
        LOG_INF<<"OnFinishAchieve wAchieveId: "<<wAchieveId;
    }

}

void CAchievementMgr::OnNewFinishAchieve(const SAchievementCFGExPtr& pAchievementCFGEx)
{
    CUser& rUser = _rPlayer.GetUser();

    rUser.AddMoney(EMONEY_ACHIEVEMENTAP,pAchievementCFGEx->_AP,NLogDataDefine::ItemFrom_NewAchieve,false);

    _rPlayer.SendPkg(g_AchievementProtS.BuildPkg_APNotify(rUser.GetMoney(EMONEY_ACHIEVEMENTAP)));

    OnCheckLevel();

    if(pAchievementCFGEx->_Share == eAchievementShareType_Friend)
    {
        SAchievementShare oAchievementShare;
        oAchievementShare.wAchievementID = pAchievementCFGEx->_ID;
        oAchievementShare.eProcess  = eAchievementProcess_Finish;
        _mapAchievementShare[oAchievementShare.wAchievementID] = oAchievementShare;
        _rPlayer.SendPkg(g_AchievementProtS.BuildPkg_AchievementShareNotify(oAchievementShare));
    }

/*
    if(pAchievementCFGEx->_AwardType == AWARDTYPE_TITLE)
    {
        CTitlePkg& rTitlePkg =  _rPlayer.GetTitlePkg(); 
        rTitlePkg.AddTitle(pAchievementCFGEx->_AwardPara);
        if(_bLog)
        {
            LOG_INF<<"roleID:"<<_rPlayer.GetRoleID()<<" AddTitle TitleID: "<<pAchievementCFGEx->_AwardPara;
        }
        
    }
    */
}

UINT32 CAchievementMgr::GetProcess(UINT16 wAchieveID)
{
    auto itr = _mapAchievementInfo.find(wAchieveID);
    if(itr != _mapAchievementInfo.end())
    {
        return itr->second.dwProcess;
    }
    return 0;
}

void CAchievementMgr::SetProcess(UINT16 wAchieveID,UINT32 dwTotal,bool bInit)
{
    UINT32 dwCount = 0;
    auto itr = _mapAchievementInfo.find(wAchieveID);

    if(itr != _mapAchievementInfo.end())
    {
        if(itr->second.dwProcess != dwTotal)
        {
            itr->second.dwProcess = dwTotal;
            dwCount = itr->second.dwCount;
            UpdateToDB(itr->second);
            NotifiyUpdate(itr->second);
        }
    }
    else
    {
        SAchievementInfo oInfo;
        oInfo.dwProcess = dwTotal;
        oInfo.qwRoleID  = _rPlayer.GetRoleID();
        oInfo.wAchievementID = wAchieveID;
        _mapAchievementInfo.insert(make_pair(wAchieveID,oInfo));
        UpdateToDB(oInfo);
        NotifiyUpdate(oInfo);
    }

    if(_bLog)
    {
        LOG_INF<<"SetProcess wAchieveID: "<<wAchieveID<<" dwTotal: "<<dwTotal<<"|"<<dwCount;
    }
}

void CAchievementMgr::LoadFromDB(const TVecAchievementInfo& vecAchievementInfo)
{
    RebuildAttr();
    CFighterManagerPtr& pFighterManager = _rPlayer.GetFighterManager();
    if(pFighterManager)
    {
        pFighterManager->SetDirty(eAttrGpAchievement);
    }

    if(_bLog)
    {
        LOG_INF<<"CAchievementMgr::LoadFromDB "<<vecAchievementInfo.size();
    }

    for(auto itr = vecAchievementInfo.begin(); itr != vecAchievementInfo.end(); ++itr)
    {
        _mapAchievementInfo.insert(make_pair(itr->wAchievementID,*itr));
        if(_bLog)
        {
            //LOG_INF<<"wAchievementID: "<<itr->wAchievementID<<"dwCount: "<<itr->dwCount <<"dwProcess: "<<itr->dwProcess;
        }

        if(itr->dwCount)
        {
            //
            SAchievementCFGExPtr pAchievementCFGEx = GetAchievementCFGByID(itr->wAchievementID);
            if(pAchievementCFGEx && pAchievementCFGEx->_Share == eAchievementShareType_Friend)
            {
                
                SAchievementShare oAchievementShare;
                oAchievementShare.wAchievementID = itr->wAchievementID;
                oAchievementShare.eProcess = IsTakeSharePrize(itr->wAchievementID)?eAchievementProcess_TakePrize:eAchievementProcess_Finish;
                _mapAchievementShare.insert(make_pair(oAchievementShare.wAchievementID,oAchievementShare));
            }
        }
    }

    RegisterEventInit();

    TVecUINT32 vecAchieveID;

    //查询完成状态
    for(auto itr =  CAchievementMgr::_mapAchievementCFGExPtr.begin(); itr != CAchievementMgr::_mapAchievementCFGExPtr.end(); itr++)
    {
        UINT32 wAchieveID = itr->second->_ID;
        if(IsFinished(wAchieveID))
        {
            vecAchieveID.push_back(wAchieveID);
            continue;
        }


        for(size_t i=0; i < itr->second->_vecEventInstID.size(); i++)
        {
            UINT32 dwEventInstID = itr->second->_vecEventInstID[i];
            SEventInfoPtr pEventInfo = GetEventInfo(dwEventInstID,wAchieveID);
            if(pEventInfo)
            {
                if(pEventInfo->wEventStatus != eEventStatus_Finish)
                {
                    if(pEventInfo->dwParam1)
                        SetProcess(wAchieveID,pEventInfo->dwParam1,true);
                }
            }
            else
            {
                AddEvent(dwEventInstID,wAchieveID);
            }

        }


    }

    {
        CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
        if(pEventMgr)
        {
            for(size_t i=0; i<vecAchieveID.size(); i++)
            {
                UINT16 wAchieveId = vecAchieveID[i];
                TVecINT32 vecParam;
                vecParam.push_back(wAchieveId);
                pEventMgr->OnEvent(eEventType_AchievementGet,vecParam,"",false);
            }

        }
    }



    CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
    if(pEventMgr)
    {
        TVecINT32 vecParam;
        vecParam.push_back(_rPlayer.GetAchievementLevel());
        pEventMgr->OnEvent(eEventType_AchievementLevelUp,vecParam,"",false);
    }


}

void CAchievementMgr::UpdateToDB(SAchievementInfo& rInfo,EDataChange eDataChange)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeAchievementInfo, eDataChange, strData);

}

//检查升级
void CAchievementMgr::OnCheckLevel()
{
    CUser& rUser = _rPlayer.GetUser();
    rUser.GetMoney(EMONEY_ACHIEVEMENTAP);
    UINT16 wLevel = _rPlayer.GetAchievementLevel();
    UINT16 wNextLevel = wLevel + 1;
    UINT16 wNewLevel = wLevel;

    UINT16 wCheckWhile = 0;

    while(1)
    {
        wCheckWhile++;
        if(wCheckWhile > 100000)
        {
            LOG_CRI<<" while not End! Error!!!!";
            return;
        }
        SAchievementLevelCFGExPtr pCFG = CAchievementMgr::GetAchievementLevelCFGByLevel(wNextLevel);
        if(NULL == pCFG)
        {
            break;
        }

        if(rUser.CanSubMoney(EMONEY_ACHIEVEMENTAP,pCFG->_Point))
        {
            //rUser.SubMoney(EMONEY_ACHIEVEMENTAP,pCFG->_Point,false);
            wNewLevel = wNextLevel;

            //next
            wNextLevel += 1;
            _rPlayer.SendPkg(g_AchievementProtS.BuildPkg_APNotify(rUser.GetMoney(EMONEY_ACHIEVEMENTAP)));
        }
        else
        {
            break;
        }
    }

    if(wLevel != wNewLevel)
    {
        if(_bLog)
        {
            LOG_INF<<"Achievement upgrade: Level: "<<wLevel<<" -> "<<wNewLevel;
        }
        _rPlayer.SetAchievementLevel(wNewLevel);
        RebuildAttr();
        CFighterManagerPtr& pFighterManager = _rPlayer.GetFighterManager();
        if(pFighterManager)
        {
            pFighterManager->SetDirty(eAttrGpAchievement);
        }

        _rPlayer.SendPkg(g_AchievementProtS.BuildPkg_AchievementLevelNotify(wNewLevel));

        CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
        if(pEventMgr)
        {
            TVecINT32 vecParam;
            vecParam.push_back(_rPlayer.GetAchievementLevel());
            pEventMgr->OnEvent(eEventType_AchievementLevelUp,vecParam);
        }

    }

    if(_bLog)
    {
        LOG_INF<<"EMONEY_ACHIEVEMENTAP: "<< rUser.GetMoney(EMONEY_ACHIEVEMENTAP);
    }

}

void CAchievementMgr::RebuildAttr()
{
    VECATTR_RESET(_vecAttr);

    SAchievementLevelCFGExPtr pCFG = CAchievementMgr::GetAchievementLevelCFGByLevel(_rPlayer.GetAchievementLevel());
    if(pCFG)
    {
        SItemAttrCFGEx* pSItemAttrCFGEx = CItemMgr::GetItemAttrConfig(pCFG->_PropAward);
        if(pSItemAttrCFGEx)
        {
            pSItemAttrCFGEx->SetIntoVec(_vecAttr);
            if(_bLog)
            {
                LOG_INF<<"CAchievementMgr::RebuildAttr!:"<<pCFG->_PropAward;
                for(size_t i = 0; i < _vecAttr.size(); ++i)
                {
                    if(_vecAttr[i]>0)
                        LOG_INF<<"id: "<<i<<"value: "<<_vecAttr[i]; 
                }
            }
        }
    }

}

SAchievementLevelCFGExPtr CAchievementMgr::GetAchievementLevelCFGByLevel(UINT32 dwLevel)
{
    UINT32 dwIndexLevel = dwLevel -1;
    if(dwIndexLevel < _VecAchievementLevelCFGExPtr.size())
    {
        return _VecAchievementLevelCFGExPtr[dwIndexLevel];
    }
    return NULL;
}

void CAchievementMgr::GetAchieveInfo(TVecAchievementInfo& vecAchievementInfo)
{
    if(_bLog)
    {
        //LOG_INF<<"CAchievementMgr::GetAchieveInfo";
    }
    for(auto itr = _mapAchievementInfo.begin(); itr != _mapAchievementInfo.end(); ++itr)
    {
        vecAchievementInfo.push_back(itr->second);
        //if(_bLog)
            //LOG_INF<<"wAchievementID:"<<itr->second.wAchievementID;
    }

    _bGetData = true;
}

EAchievementRet CAchievementMgr::OnTakePrize(UINT16 wAchievementID)
{
    
    auto itr = _mapAchievementInfo.find(wAchievementID);

    if(itr == _mapAchievementInfo.end())
    {
        return eAchievementRet_NotFinish;
    }

    SAchievementInfo& rInfo = itr->second;
    
    //未完成
    if(rInfo.dwCount == eAchievementProcess_Init )
    {
        return eAchievementRet_NotFinish;
    }

    if(rInfo.dwCount == eAchievementProcess_TakePrize)
    {
        return eAchievementRet_TakePrized;
    }

    SAchievementCFGExPtr pAchievementCFGEx = GetAchievementCFGByID(wAchievementID);
    if(NULL == pAchievementCFGEx)
    {
        return eAchievementRet_ErrorCFG;
    }

    CUser& rUser = _rPlayer.GetUser();
    CPack& rPack = rUser.GetPack();
    if (!rPack.CanAddItem(pAchievementCFGEx->_vecPrize))
    {
        rUser.SendSysMsg(eMsgPackFullErr);
        //_rPlayer.SendSysMsg(eMsgBattleArrayPackError);
        return eAchievementRet_PackFull;
    }
    
    if (!rPack.AddItem(pAchievementCFGEx->_vecPrize, NLogDataDefine::ItemFrom_Achievement))
    {
        _rPlayer.SendSysMsg(eMsgPackFullErr);
        return eAchievementRet_PackFull;
    }

    if(pAchievementCFGEx->_AwardType == AWARDTYPE_TITLE)
    {
        CTitlePkg& rTitlePkg =  _rPlayer.GetTitlePkg(); 
        rTitlePkg.AddTitle(pAchievementCFGEx->_AwardPara);
        if(_bLog)
        {
            LOG_INF<<"roleID:"<<_rPlayer.GetRoleID()<<" AddTitle TitleID: "<<pAchievementCFGEx->_AwardPara;
        }
    }

    rInfo.dwCount = eAchievementProcess_TakePrize;

    UpdateToDB(rInfo);
    NotifiyUpdate(rInfo);
    
    if(_bLog)
    {
        LOG_INF<<"roleID:"<<_rPlayer.GetRoleID()<<" OnTakePrize wAchievementID:"<<wAchievementID;
    }
    return eAchievementRet_Sucess;
}

void CAchievementMgr::NotifiyUpdate(SAchievementInfo& oInfo)
{
    if(!_bGetData) return;

    LOG_INF<<"NotifiyUpdate wAchievementID:"<<oInfo.wAchievementID<<"dwCount:" <<oInfo.dwCount;

    _rPlayer.SendPkg(g_AchievementProtS.BuildPkg_AchievementInfoNotify(oInfo));

}

SAchievementCFGExPtr CAchievementMgr::GetAchievementCFGByID(UINT32 wAchieveID)
{
    auto itr = CAchievementMgr::_mapAchievementCFGExPtr.find(wAchieveID);
    if(itr != CAchievementMgr::_mapAchievementCFGExPtr.end())
    {
        return itr->second;
    }
    return NULL;
}

void CAchievementMgr::OnEvent(SEventInfoPtr pEventInfo)
{
    LOG_INF<<"CAchievementMgr::OnEvent";
    if(NULL == pEventInfo)
    {
        return;
    }

    SAchievementCFGExPtr pAchievementCFGEx = GetAchievementCFGByID(pEventInfo->dwApplyID); 
    if(NULL == pAchievementCFGEx)
    {
        return;
    }

    UINT16 wAchieveID = pEventInfo->dwApplyID;

    if(IsFinished(wAchieveID))
    {
        return;
    }

    //统计计数的
    if(pEventInfo->bySave)
        SetProcess(wAchieveID,pEventInfo->dwParam1);

    if(pEventInfo->wEventStatus == eEventStatus_Finish)
    {
        bool bFinish=true;
        for(size_t i = 0; i < pAchievementCFGEx->_vecEventInstID.size(); i++)
        {
            UINT32 dwEventInstID = pAchievementCFGEx->_vecEventInstID[i];
            if(dwEventInstID == pEventInfo->dwEventInstID)
                continue;
            SEventInfoPtr pEventInfo = GetEventInfo(dwEventInstID,wAchieveID);
            if(pEventInfo)
            {
                bFinish = false; 
                break;
            }

            if(pEventInfo->wEventStatus != eEventStatus_Finish)
            {
                bFinish = false;
                break;
            }
        }

        if(bFinish)
        {
            OnFinishAchieve(pAchievementCFGEx);
            for(size_t i = 0; i < pAchievementCFGEx->_vecEventInstID.size(); i++)
            {
                UINT32 dwEventInstID = pAchievementCFGEx->_vecEventInstID[i];
                RemoveEvent(dwEventInstID,wAchieveID);
            }
        }
        else
        {
            //保存当前事件
            pEventInfo->bySave = 1;

        }
    }
}

//接收：获取成就分享信息
void CAchievementMgr::OnGeAchievementShareList(TVecAchievementShare& vecAchievementShare)
{
    for(auto itr = _mapAchievementShare.begin(); itr != _mapAchievementShare.end(); itr++)
    {
        vecAchievementShare.push_back(itr->second);
    }

}

 //
void CAchievementMgr::SetSharePrize(UINT16 wAchievementID)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        pAutoStoreMgr->SetValue(eAutoStore_Achievement_ShareFriend,wAchievementID,eAchievementProcess_TakePrize);
    }

}

bool CAchievementMgr::IsTakeSharePrize(UINT16 wAchievementID)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        UINT32 dwFlag = pAutoStoreMgr->GetValue(eAutoStore_Achievement_ShareFriend,wAchievementID);
        return 0 != dwFlag;
    }
    return false;
}

void CAchievementMgr::ClearTakeSharePrize()
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        pAutoStoreMgr->ClearValue(eAutoStore_Achievement_ShareFriend);
    }

    for(auto itr = _mapAchievementShare.begin(); itr != _mapAchievementShare.end(); itr++)
    {
        itr->second.eProcess = eAchievementProcess_Finish;
    }
}


//接收：获取成就分享奖励
EAchievementRet CAchievementMgr::OnTakeSharePrize(UINT16 wAchievementID)
{
    auto itr = _mapAchievementShare.find(wAchievementID);
    if(itr == _mapAchievementShare.end())
    {
        LOG_CRI<<"Error not finish:"<<wAchievementID<<"qwRoleID:"<<_rPlayer.GetRoleID();
        return eAchievementRet_NotFinish;
    }

    if(itr->second.eProcess == eAchievementProcess_TakePrize)
    {
        LOG_INF<<"eAchievementRet_TakePrized";
        return eAchievementRet_TakePrized;
    }

    SAchievementCFGExPtr pAchievementCFGEx = GetAchievementCFGByID(wAchievementID);
    if(NULL == pAchievementCFGEx)
    {
        return eAchievementRet_ErrorCFG;
    }

    CUser& rUser = _rPlayer.GetUser();
    CPack& rPack = rUser.GetPack();
    if (!rPack.CanAddItem(pAchievementCFGEx->_vecSharePrize))
    {
        rUser.SendSysMsg(eMsgPackFullErr);
        return eAchievementRet_PackFull;
    }
    
    if (!rPack.AddItem(pAchievementCFGEx->_vecSharePrize, NLogDataDefine::ItemFrom_Achievement))
    {
        _rPlayer.SendSysMsg(eMsgPackFullErr);
        return eAchievementRet_PackFull;
    }

    itr->second.eProcess = eAchievementProcess_TakePrize;
    //save status
    SetSharePrize(wAchievementID);

    return eAchievementRet_Sucess;
}



