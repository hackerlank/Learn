#include "stdafx.h"
#include "InvitedFriendMgr.h"
#include "UserMgr.h"
#include "CenterDataMgr.h"
#include "Center2DBCommC.h"
#include "Game2CenterCommS.h"
#include "LogDataDefine.h"
#include "Tokenizer.h"
#include "InviteGSSvrS.h"
CInvitedFriendMgr g_InvitedFriendMgr;
extern CCenter2DBCommC g_Center2DBCommC; 
extern  CGame2CenterCommS g_Game2CenterCommS;
/*
void GetItemFromString(TVecItemGenInfo& vecItem, const string strItem)
{
        Tokenizer tk(strItem, "|"); // XXX: itemID,count|ItemID,count
        for (size_t i = 0; i < tk.size(); ++i)
        {
            Tokenizer yatk(tk[i], ",");
            UINT16 wItemID = atoi(yatk[0].c_str());
            if (wItemID)
            {
                UINT32 dwCount = 0;
                if (yatk.size() > 1)
                {
                    dwCount = atoi(yatk[1].c_str());
                    SItemGenInfo oItemGenInfo;
                    oItemGenInfo.wItemID = wItemID;
                    oItemGenInfo.dwCount = dwCount;
                    oItemGenInfo.eBindType = eBindGet;
                    vecItem.push_back(oItemGenInfo);
                }
            }
        }
}
*/
void GetItemFromString(TVecUserItem& vecItem, const string strItem)
{
        Tokenizer tk(strItem, "|"); // XXX: itemID,count|ItemID,count
        for (size_t i = 0; i < tk.size(); ++i)
        {
            Tokenizer yatk(tk[i], ",");
            UINT16 wItemID = atoi(yatk[0].c_str());
            if (wItemID)
            {
                UINT32 dwCount = 0;
                if (yatk.size() > 1)
                {
                    dwCount = atoi(yatk[1].c_str());
                    SUserItem oItemGenInfo;
                    oItemGenInfo.dwTypeID = wItemID;
                    oItemGenInfo.dwCount = dwCount;
                    vecItem.push_back(oItemGenInfo);
                }
            }
        }
}

CInvitedFriendMgr::CInvitedFriendMgr()
{
    _bLoading = true;

}

bool CInvitedFriendMgr::InvitedFriendMgr_Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/FriendInvitePrize.xml";
    CFriendInvitePrizeLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oItemLoader.LoadData fails! Path: " << strPath;
        return false;
    }

    for(size_t i=0; i<oLoader._vecData.size(); i++)
    {
        SFriendInvitePrizeCFG* pBaseCFG = oLoader._vecData[i];
        if(NULL == pBaseCFG)
            return false;
        SFriendInvitePrizeCFGExPtr pFriendInvitePrizeCFGEx(new SFriendInvitePrizeCFGEx(pBaseCFG));
        GetItemFromString(pFriendInvitePrizeCFGEx->_vecPrize,pFriendInvitePrizeCFGEx->_Prize);

        if(eInvitedTask_day == pFriendInvitePrizeCFGEx->_Type)
        {
           _mapDayInviteFriendPrizeCFGExPtr.insert(make_pair(pFriendInvitePrizeCFGEx->_ID,pFriendInvitePrizeCFGEx)); 

        }
        

        //所有任务
        {
            _mapFriendInvitePrizeCFGExPtr.insert(make_pair(pFriendInvitePrizeCFGEx->_ID,pFriendInvitePrizeCFGEx));
        }
    }

    return true;

}

void CInvitedFriendMgr::OnLoad_InviteFriend(const SCenterData& oCenterData)
{
    SInvitedFriendDBPtr pInvitedFriendDB(new SInvitedFriendDB);
    pInvitedFriendDB->qwUserID = oCenterData.qwInstID;
    pInvitedFriendDB->qwInviteID = oCenterData.qwInstID2;
    pInvitedFriendDB->strName  = oCenterData.strParam;
    pInvitedFriendDB->byVIPLevel = oCenterData.dwParam3;
    pInvitedFriendDB->dwTotalRecharge = oCenterData.qwParam;
    
    URoleInfo uRoleInfo;
    uRoleInfo.dwRole = oCenterData.dwParam1;

    pInvitedFriendDB->byColor =uRoleInfo.sRole.byColor;  
    pInvitedFriendDB->bySex   =uRoleInfo.sRole.bySex;    
    pInvitedFriendDB->byJob   =uRoleInfo.sRole.byCareer; 
    pInvitedFriendDB->byLevel =uRoleInfo.sRole.byLevel;  

    _mapInvitedFriendDBPtr.insert(make_pair(pInvitedFriendDB->qwUserID,pInvitedFriendDB));

    TMapInvitedFriendDBPtr& rMap = _mapmapInvitPtr[pInvitedFriendDB->qwInviteID];
    rMap.insert(make_pair(pInvitedFriendDB->qwUserID,pInvitedFriendDB));

}

void CInvitedFriendMgr::Update2DB(const SInvitedFriendDB& oInvitedFriendDB,bool bDelete)
{
    URoleInfo uRoleInfo;
    uRoleInfo.sRole.byColor = oInvitedFriendDB.byColor;
    uRoleInfo.sRole.bySex   = oInvitedFriendDB.bySex;
    uRoleInfo.sRole.byCareer= oInvitedFriendDB.byJob;
    uRoleInfo.sRole.byLevel = oInvitedFriendDB.byLevel;
 
    SCenterData oCenterData;
    oCenterData.wType =    eCenterDate_InviteFriend; 
    oCenterData.qwInstID=  oInvitedFriendDB.qwUserID;
    oCenterData.qwInstID2= oInvitedFriendDB.qwInviteID;
    oCenterData.strParam = oInvitedFriendDB.strName;
    oCenterData.dwParam1=  uRoleInfo.dwRole;
    oCenterData.dwParam3= oInvitedFriendDB.byVIPLevel;
    oCenterData.qwParam = oInvitedFriendDB.dwTotalRecharge;
    g_CenterDataMgr.Update2DB(oCenterData,bDelete);
}

void CInvitedFriendMgr::OnLoad_InviteTask(const SCenterData& oCenterData)
{
    UINT64 qwUserID = oCenterData.qwInstID;
    SInvitedTaskPtr pInvitedTask(new SInvitedTask);
    pInvitedTask->dwInviteTaskID = oCenterData.qwInstID2;
    pInvitedTask->eInvitedTask = (EInvitedTask)(oCenterData.dwParam1);
    pInvitedTask->wTaskType = oCenterData.dwParam2;
    if(eInvitedTask_day == oCenterData.dwParam2)
    {
        TMapInvitedTaskPtr& rMap =  GetDayTaskMap(qwUserID);
        rMap.insert(make_pair(pInvitedTask->dwInviteTaskID,pInvitedTask));
    }
    else
    {
        TMapInvitedTaskPtr& rMap = GetNormalTaskMap(qwUserID);
        rMap.insert(make_pair(pInvitedTask->dwInviteTaskID,pInvitedTask));
    }

}


void CInvitedFriendMgr::Update2DB(UINT64 qwUserID,const SInvitedTask& rSInvitedTask,bool bDelete)
{
    SCenterData oCenterData;
    oCenterData.wType = eCenterDate_InviteTask;
    oCenterData.qwInstID = qwUserID;
    oCenterData.qwInstID2 = rSInvitedTask.dwInviteTaskID;
    oCenterData.dwParam1  = rSInvitedTask.eInvitedTask;
    oCenterData.dwParam2  = rSInvitedTask.wTaskType;

    g_CenterDataMgr.Update2DB(oCenterData,bDelete);

}

//有被邀请的朋友加入
void CInvitedFriendMgr::OnAddFriend(SInvitedFriendDBPtr pInvitedFriendDBPtr,UINT64 qwInviteID)
{
    pInvitedFriendDBPtr->qwInviteID = qwInviteID;
    SInvitedFriendDBPtr pInvitedFriendDB = GetInvitedFriend(pInvitedFriendDBPtr->qwUserID);
    if(NULL != pInvitedFriendDB)
    {
        LOG_CRI<<"error!!!";
        UpdateFriend(*pInvitedFriendDBPtr);
        return;
    }

    InsertFriend(pInvitedFriendDBPtr,qwInviteID);

    //保存数据更新任务
    UpdateFriend(*pInvitedFriendDBPtr);

}

void CInvitedFriendMgr::InsertFriend(SInvitedFriendDBPtr pInvitedFriendDBPtr,UINT64 qwInviteID)
{
    _mapInvitedFriendDBPtr.insert(make_pair(pInvitedFriendDBPtr->qwUserID,pInvitedFriendDBPtr));
    TMapInvitedFriendDBPtr&  rMapInvitedFriendDB = CInvitedFriendMgr::GetInviteMap(qwInviteID);
    rMapInvitedFriendDB.insert(make_pair(pInvitedFriendDBPtr->qwUserID,pInvitedFriendDBPtr));
}

//被邀请朋友信息更新
void CInvitedFriendMgr::UpdateFriend(SInvitedFriendDB& rInvitedFriendDB)
{
    UINT64 qwInviteID = rInvitedFriendDB.qwInviteID;
    SInvitedFriendDBPtr pInvitedFriendDB = GetInvitedFriend(rInvitedFriendDB.qwUserID);
    if(NULL == pInvitedFriendDB)
        return;

    //save db
    Update2DB(rInvitedFriendDB,false);

    *pInvitedFriendDB = rInvitedFriendDB;

    TMapInvitedFriendDBPtr& rMapInvitedFriendDB =  GetInviteMap(qwInviteID);

    CUserPtr pUser =  CUserMgr::GetUserByUserID(qwInviteID);

    //更新任务列表

    for(auto itr = _mapFriendInvitePrizeCFGExPtr.begin(); itr != _mapFriendInvitePrizeCFGExPtr.end(); itr++)
    {
        const SFriendInvitePrizeCFGExPtr pFriendInvitePrizeCFGEx = itr->second;
        if(NULL == pFriendInvitePrizeCFGEx)
            continue;

        if(eInvitedTask_day == pFriendInvitePrizeCFGEx->_Type)
        {
            continue;
        }

        UINT32 dwPrizeID = pFriendInvitePrizeCFGEx->_ID;

        {
        SInvitedTaskPtr pInvitedTask = GetNormalTask(rInvitedFriendDB.qwUserID,dwPrizeID);

        //已经完成任务
        if(pInvitedTask)
            continue;
        }

        bool bRet = CheckTaskEnd(rMapInvitedFriendDB,pFriendInvitePrizeCFGEx);
        
        if(!bRet)
            continue;

        SInvitedTaskPtr pNewInvitedTask(new SInvitedTask);
        pNewInvitedTask->dwInviteTaskID = dwPrizeID;
        pNewInvitedTask->eInvitedTask = eInvitedTask_Finish;
        pNewInvitedTask->wTaskType = pFriendInvitePrizeCFGEx->_Type; 
        TMapInvitedTaskPtr&  rInviteMap = GetNormalTaskMap(qwInviteID);
        rInviteMap.insert(make_pair(dwPrizeID,pNewInvitedTask));

        //save db
        Update2DB(qwInviteID,*pNewInvitedTask,false);

        LOG_INF<<"task finish:"<<dwPrizeID<<" qwRoleID:"<<qwInviteID;
        
        if(pUser&&pUser->IsOnline())
        {
            pUser->SendPkg(g_InviteSvrS.BuildPkg_UpdateInvitedTask(*pNewInvitedTask));
        }

    }
    //被邀请人信息更新

    if(pUser&&pUser->IsOnline())
    {
        SInvitedFriend oInvitedFriend;
        GetInfo(oInvitedFriend,rInvitedFriendDB);
        pUser->SendPkg(g_InviteSvrS.BuildPkg_UpdateInvitedFriend(oInvitedFriend));
    }
}

void CInvitedFriendMgr::OnMiddNight()
{
   for( auto itr = _mapDayInvitedTaskPtr.begin(); itr != _mapDayInvitedTaskPtr.end();itr++)
   {
       Clear(itr->first,itr->second);
   }

}

//清理每日任务
void CInvitedFriendMgr::Clear(UINT64 qwUserID,TMapInvitedTaskPtr& rMapInvitedTask)
{
    for(auto itr = rMapInvitedTask.begin(); itr != rMapInvitedTask.end(); itr++)
    {
        Update2DB(qwUserID,*(itr->second),true);
    }

    //通知玩家
    CUserPtr pUser =  CUserMgr::GetUserByUserID(qwUserID);
    if(NULL == pUser)
        return;
    
    if(pUser&&pUser->IsOnline())
    {
       pUser->SendPkg(g_InviteSvrS.BuildPkg_UpdateDayInvitedFriends(0));
    }

    rMapInvitedTask.clear();
}


//获取奖励配置
SFriendInvitePrizeCFGExPtr CInvitedFriendMgr::GetPrizeCFG(UINT32 dwPrizeID)
{
    auto itr = _mapFriendInvitePrizeCFGExPtr.find(dwPrizeID);
    if(itr != _mapFriendInvitePrizeCFGExPtr.end())
    {
        return itr->second;
    }

    return NULL;
}


//获得被邀请任信息
SInvitedFriendDBPtr CInvitedFriendMgr::GetInvitedFriend(UINT64 qwUserID)
{
    auto itr = _mapInvitedFriendDBPtr.find(qwUserID);
    if(itr != _mapInvitedFriendDBPtr.end())
    {
        return itr->second;
    }

    return NULL;
}


//获得邀请人列表
TMapInvitedFriendDBPtr& CInvitedFriendMgr::GetInviteMap(UINT64 qwUserID)
{
    return _mapmapInvitPtr[qwUserID];
}

//检查任务是否完成
bool CInvitedFriendMgr::CheckTaskEnd(TMapInvitedFriendDBPtr& rMap, SFriendInvitePrizeCFGExPtr pFriendInvitePrizeCFGEx )
{
    if(NULL == pFriendInvitePrizeCFGEx)
    {
        return false;
    }

    UINT32 dwCnt = 0;
    for(auto itr = rMap.begin(); itr != rMap.end(); itr++)
    {
        SInvitedFriendDBPtr pInvitedFriendDB = itr->second;
        if(NULL == pInvitedFriendDB)
            continue;

        if(pFriendInvitePrizeCFGEx->_FriendLevel)  //好友等级
        {
            if(pInvitedFriendDB->byLevel < pFriendInvitePrizeCFGEx->_FriendLevel)
            {
                continue;
            }
        }

        if(pFriendInvitePrizeCFGEx->_VipLevel)
        {
            if(pInvitedFriendDB->byVIPLevel < pFriendInvitePrizeCFGEx->_VipLevel)
                continue;
        }

        if(pFriendInvitePrizeCFGEx->_BuyGold)
        {
            if(pInvitedFriendDB->dwTotalRecharge < pFriendInvitePrizeCFGEx->_BuyGold)
                continue;
        }

        dwCnt++;

    }

    if(dwCnt < pFriendInvitePrizeCFGEx->_GoodFriendCnt)
    {
        return false;
    }

    return true;
}

//获取日常任务
TMapInvitedTaskPtr&  CInvitedFriendMgr::GetDayTaskMap(UINT64 qwUserID)
{
    return _mapDayInvitedTaskPtr[qwUserID];
}

//获取日常任务
SInvitedTaskPtr CInvitedFriendMgr::GetDayTask(UINT64 qwUserID,UINT32 dwPrizeID)
{
    TMapInvitedTaskPtr& rMap = GetDayTaskMap(qwUserID);
    auto itr  = rMap.find(dwPrizeID);
    if(itr != rMap.end())
    {
        return itr->second;
    }

    return NULL;
}


//获取普通任务
TMapInvitedTaskPtr&  CInvitedFriendMgr::GetNormalTaskMap(UINT64 qwUserID)
{
    return _mapNormalInvitedTaskPtr[qwUserID];
}

//获取普通任务
SInvitedTaskPtr CInvitedFriendMgr::GetNormalTask(UINT64 qwUserID,UINT32 dwPrizeID)
{
    TMapInvitedTaskPtr& rMap = GetNormalTaskMap(qwUserID);
    auto itr = rMap.find(dwPrizeID);
    if(itr != rMap.end())
    {
        return itr->second;
    }

    return NULL;
}


void CInvitedFriendMgr::GetInfo(SInvitedFriend& rInvitedFriend, const SInvitedFriendDB& rInvitedFriendDB)
{
        rInvitedFriend.qwUserID = rInvitedFriendDB.qwUserID;
        rInvitedFriend.strName  = rInvitedFriendDB.strName;
        rInvitedFriend.byJob     = rInvitedFriendDB.byJob;
        rInvitedFriend.bySex     = rInvitedFriendDB.bySex; 
        rInvitedFriend.byLevel  = rInvitedFriendDB.byLevel;
        rInvitedFriend.byVIPLevel  = rInvitedFriendDB.byVIPLevel;
        rInvitedFriend.dwTotalRecharge = rInvitedFriendDB.dwTotalRecharge;
        rInvitedFriend.vecPlatforms = CUserMgr::GetPlatformParam(rInvitedFriendDB.qwUserID);
}

//接收：获取被邀请好友列表
void CInvitedFriendMgr::OnGetInvitedFriendList(UINT64 qwUserID,TVecInvitedFriend& vecInvitedFriend)
{
    TMapInvitedFriendDBPtr& rmapInvitedFriendDBPtr = GetInviteMap(qwUserID);
    for(auto itr = rmapInvitedFriendDBPtr.begin(); itr != rmapInvitedFriendDBPtr.end(); itr++)
    {
        SInvitedFriendDB& rSInvitedFriendDB = *(itr->second);

        SInvitedFriend oInvitedFriend;
        GetInfo(oInvitedFriend,rSInvitedFriendDB);
        vecInvitedFriend.push_back(oInvitedFriend);
    }

}

//接收：邀请任务列表
void CInvitedFriendMgr::OnGetInvitedTaskList(UINT64 qwUserID,TVecInvitedTask& vecInvitedTask)
{
    TMapInvitedTaskPtr& rDayMap = GetDayTaskMap(qwUserID);
    for(auto itr = rDayMap.begin(); itr != rDayMap.end(); itr++)
    {
        vecInvitedTask.push_back(*(itr->second));
        LOG_INF<<"dwInviteTaskID:"<<itr->second->dwInviteTaskID<<"eInvitedTask:"<<itr->second->eInvitedTask;

    }

    TMapInvitedTaskPtr& rNormalMap =  GetNormalTaskMap(qwUserID);
    for(auto itr = rNormalMap.begin(); itr != rNormalMap.end(); itr++)
    {
        vecInvitedTask.push_back(*(itr->second));
        LOG_INF<<"dwInviteTaskID:"<<itr->second->dwInviteTaskID<<"eInvitedTask:"<<itr->second->eInvitedTask;
    }

    LOG_INF<<"OnGetInvitedTaskList DayTask:"<<rDayMap.size()<<" NormalTask:"<<vecInvitedTask.size();
}

//接收：每日邀请好友数量
void CInvitedFriendMgr::OnGetDayInvitedFriends(UINT64 qwUserID,UINT32 &dwInviteCnt)
{
    CUserPtr pUser =  CUserMgr::GetUserByUserID(qwUserID);
    if(NULL == pUser)
        return;
    dwInviteCnt = pUser->GetDayInviteFriendCnt();
    LOG_INF<<"OnGetDayInvitedFriends:"<<dwInviteCnt;
}

//接收：领取奖励
EInviteResult CInvitedFriendMgr::OnTakeTaskPrize(UINT64 qwUserID,UINT32 dwPrizeID)
{
    LOG_INF<<"OnTakeTaskPrize qwRoleID:"<<qwUserID<<" dwPrizeID:"<<dwPrizeID;
   CUserPtr pUser =  CUserMgr::GetUserByUserID(qwUserID);
    if(NULL == pUser)
    {
        LOG_INF<<"Error UserID:"<<qwUserID;
        return eInvite_ErrorUserID;
    }

    if(pUser->IsAddItemCd())
    {
        LOG_INF<<"AddItem cd";
        return eInvite_ServerBusy;
    }
    const SFriendInvitePrizeCFGExPtr pFriendInvitePrizeCFGEx = GetPrizeCFG(dwPrizeID);
    if(NULL == pFriendInvitePrizeCFGEx)
    {
        LOG_INF<<"Error cfg dwPrizeID:"<<dwPrizeID;
        return eInvite_ErrorCFGID;
    }

    SInvitedTaskPtr pInvitedTask = NULL;
    if(pFriendInvitePrizeCFGEx->_Type == eInvitedTask_day)
    {
        pInvitedTask =  GetDayTask(qwUserID,dwPrizeID);
    }
    else
    {
        pInvitedTask =  GetNormalTask(qwUserID,dwPrizeID);
    }


    if(NULL == pInvitedTask)
    {
        LOG_INF<<"not finish Task";
      return eInvite_TaskInit;
    }

    if(pInvitedTask->eInvitedTask == eInvitedTask_TakePrized)
    {
        LOG_INF<<"Has TakePrize";
        return eInvite_TaskTakedPrize;
    }

    pUser->SetAddItemCd();
    
    {
        TVecINT32 vecParam;
        vecParam.push_back(dwPrizeID);
        vecParam.push_back(1);
        pInvitedTask->eInvitedTask = eInvitedTask_TakePrized;

    }

    UINT32 dwServerID = pUser->GetGameSvrID();
    LOG_INF<<"take invite prize:"<<dwPrizeID<<" qwUserID:"<<qwUserID;
    g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,qwUserID,NLogDataDefine::ItemFrom_InviteFriend,pFriendInvitePrizeCFGEx->_vecPrize,[this,pUser,pInvitedTask](UINT8 byRet_, UINT8 byError)
                                {
                                    
                                    if(byRet_ || byError)
                                    {   
                                        return;
                                    }   

                                    pInvitedTask->eInvitedTask = eInvitedTask_TakePrized;

                                    //save db
                                    Update2DB(pUser->GetUserID(),*pInvitedTask,false);

                                    //clear cd
                                    pUser->ClearAddItemCD();
                                    //LOG_INF<<"task finish:"<<dwPrizeID<<" qwRoleID:"<<qwInviteID;
        
                                    if(pUser&&pUser->IsOnline())
                                    {
                                        pUser->SendPkg(g_InviteSvrS.BuildPkg_UpdateInvitedTask(*pInvitedTask));
                                    }
                                     
                                });

    return eInvite_Success;
}

//接收：邀请好友成功
void CInvitedFriendMgr::OnInviteFriend(
    UINT64 qwUserID, //邀请人
    UINT64 qwInvitedUserID //被邀请人
)
{
    LOG_INF<<"OnInviteFriend qwSendRoleID:"<<qwUserID<<" qwInvitedUserID:"<<qwInvitedUserID;

    CUserPtr pUser =  CUserMgr::GetUserByUserID(qwUserID);
    if(NULL == pUser)
    {
        LOG_CRI<<"Error qwUserID:"<<qwUserID;
        return;
    }
    pUser->AddDayInviteFriendCnt(1);

    UINT32 dwInviteCnt = pUser->GetDayInviteFriendCnt();

    for(auto itr = _mapDayInviteFriendPrizeCFGExPtr.begin(); itr != _mapDayInviteFriendPrizeCFGExPtr.end();itr++)
    {
        SFriendInvitePrizeCFGExPtr pFriendInvitePrizeCFGEx = itr->second;
        if(NULL == pFriendInvitePrizeCFGEx)
            continue;

        if(dwInviteCnt < pFriendInvitePrizeCFGEx->_SendInviteCnt)
        {
            continue;
        }

        UINT32 dwPrizeID = pFriendInvitePrizeCFGEx->_ID;

        {
        SInvitedTaskPtr pInvitedTask = GetDayTask(qwUserID,dwPrizeID);
        if(pInvitedTask)
            continue;
        }
        
        SInvitedTaskPtr pNewInvitedTask(new SInvitedTask);
        pNewInvitedTask->dwInviteTaskID = dwPrizeID;
        pNewInvitedTask->eInvitedTask = eInvitedTask_Finish;
        pNewInvitedTask->wTaskType = pFriendInvitePrizeCFGEx->_Type;
        TMapInvitedTaskPtr&  rInviteMap = GetDayTaskMap(qwUserID);
        rInviteMap.insert(make_pair(dwPrizeID,pNewInvitedTask));

        //save db
        Update2DB(qwUserID,*pNewInvitedTask,false);

        LOG_INF<<"task finish:"<<dwPrizeID<<" qwRoleID:"<<qwUserID;
        
        if(pUser&&pUser->IsOnline())
        {
            pUser->SendPkg(g_InviteSvrS.BuildPkg_UpdateInvitedTask(*pNewInvitedTask));
        }

    }

    if(pUser&&pUser->IsOnline())
    {
       pUser->SendPkg(g_InviteSvrS.BuildPkg_UpdateDayInvitedFriends(dwInviteCnt));
    }

}

void CInvitedFriendMgr::OnUserPropChanged(CUser& rUser, NGame2CenterComm::EUserSyncPropField eField,UINT32 dwValue)
{
    UINT64 qwInviteID = rUser.GetInvitedID();
    if(!qwInviteID)
        return;

    SInvitedFriendDBPtr pInvitedFriendDB =  GetInvitedFriend(rUser.GetUserID());
    if(NULL == pInvitedFriendDB)
    {
        LOG_CRI<<"unkown invited:"<<rUser.GetUserID();
        return;
    }

    switch(eField)
    {
        case NGame2CenterComm::eSyncPropLevel:
            {
                pInvitedFriendDB->byLevel = dwValue;
            }
            break;
        case NGame2CenterComm::eSyncPropVIPLevel:
            {
                pInvitedFriendDB->byVIPLevel = dwValue;
            }
            break;
        case NGame2CenterComm::eSyncPropTotalRecharge:
            {
                pInvitedFriendDB->dwTotalRecharge += dwValue;
            }
            break;
        default:
            break;
    }

    UpdateFriend(*pInvitedFriendDB);
}

//邀请玩家登陆
void CInvitedFriendMgr::OnUserLogin(CUser& rUser)
{
    UINT64 qwInviteID = rUser.GetInvitedID();
    if(!qwInviteID)
        return;

    SInvitedFriendDBPtr pInvitedFriendDB = GetInvitedFriend(rUser.GetUserID());
    if(pInvitedFriendDB)
    {
        //pInvitedFriendDB->byJob = rUser.GetCareer();
        //pInvitedFriendDB->byLevel = rUser.GetLevel();
        //pNewInvitedFriend->byColor = rUser.GetColor();
        return;
    }
    SInvitedFriendDBPtr pNewInvitedFriend(new SInvitedFriendDB);
    pNewInvitedFriend->qwUserID   = rUser.GetUserID();
    pNewInvitedFriend->qwInviteID = qwInviteID;
    pNewInvitedFriend->strName    = rUser.GetRoleName();
    pNewInvitedFriend->byColor    = rUser.GetColor();
    pNewInvitedFriend->byJob      = rUser.GetCareer();
    pNewInvitedFriend->bySex      = rUser.GetSex();
    pNewInvitedFriend->byLevel    = rUser.GetLevel();
    pNewInvitedFriend->byVIPLevel = rUser.GetVIPLevel();
    pNewInvitedFriend->dwTotalRecharge = rUser.GetTotalRecharge();
    OnAddFriend(pNewInvitedFriend,qwInviteID);
}


