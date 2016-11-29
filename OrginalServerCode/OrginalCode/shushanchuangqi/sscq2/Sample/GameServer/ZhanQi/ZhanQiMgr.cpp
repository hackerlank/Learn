#include "stdafx.h"
#include "ZhanQiMgr.h"
#include "Player.h"
#include "User.h"
#include "SysMsgDefine.h"
#include "ItemMgr.h"
#include "Tokenizer.h"
#include "Monster.h"
#include "MonsterMgr.h"
#include "VIPMgr.h"
#include "ZhanQiRoom.h"
#include "GetCondMgr.h"
#include "GameServerSysMail.h"
#include "ExpMgr.h"
#include "AutoStoreMgr.h"

CZhanQiMgr g_ZhanQiMgr;

void GetPathFromString(TSetUINT16& vecPath,const string strPath)
{
    Tokenizer tk(strPath, "|");
    for (size_t i = 0; i < tk.size(); ++i)
    {
        UINT16 wPathID = atoi(tk[i].c_str());
        if(wPathID)
        vecPath.insert(wPathID);
    }
}

void GetInitPathFromString(TVecUINT16& vecPath,const string strPath)
{
    Tokenizer tk(strPath, "|");
    for (size_t i = 0; i < tk.size(); ++i)
    {
        UINT16 wPathID = atoi(tk[i].c_str());
        if(wPathID)
        vecPath.push_back(wPathID);
    }
}


 extern void GetItemFromString(TVecItemGenInfo& vecItem, const string strItem); 

bool CZhanQiMgr::ZhanQiInit()
{
    if(!SParamConfig::wSecretAreaMoveSuiYuan)
    {
        SParamConfig::wSecretAreaMoveSuiYuan = 10;
    }

    if(!SParamConfig::wSecretAreaSuiYan2Item)
    {
        SParamConfig::wSecretAreaSuiYan2Item = 100;
    }
    
    string strLingShanMapPath = Config._strConfigDir + "Conf/Table/LingShanMap.xml";
    CLingShanMapLoader oLingShanMapPath;
    if(!oLingShanMapPath.LoadData(strLingShanMapPath))
    {
        LOG_CRI << "CZhanQiLoaderLoader fails! Path: " << strLingShanMapPath;
        return false;
    }

    for(size_t i  = 0; i < oLingShanMapPath._vecData.size(); ++i)
    {
        SLingShanMapCFGExPtr pLingShanMapCFGEx(new SLingShanMapCFGEx);
        pLingShanMapCFGEx->CopyFrom(*oLingShanMapPath._vecData[i]);
        GetPathFromString(pLingShanMapCFGEx->setPath,pLingShanMapCFGEx->_Adj);

        TVecLingShanMapCFGExPtr& vecMapCFG = GetMapCFG(pLingShanMapCFGEx->_Type);
        if(pLingShanMapCFGEx->_ID >= vecMapCFG.size())
        {
            vecMapCFG.resize(pLingShanMapCFGEx->_ID+1);
        }

        if(pLingShanMapCFGEx->_ID >= vecMapCFG.size())
        {
            LOG_CRI<<"ZhanQiInit Unkown Error!!!";
            return false;
        }
        vecMapCFG[pLingShanMapCFGEx->_ID]=pLingShanMapCFGEx;
    }
 
    string strLingShanPath = Config._strConfigDir + "Conf/Table/LingShan.xml";
    CLingShanLoader oLingShanPath;
    if(!oLingShanPath.LoadData(strLingShanPath))
    {
        LOG_CRI << "CZhanQiLoaderLoader fails! Path: " << strLingShanPath;
        return false;
    }

    for(size_t i  = 0; i < oLingShanPath._vecData.size(); ++i)
    {
        SLingShanCFGExPtr pLingShanCFGEx(new SLingShanCFGEx);
        pLingShanCFGEx->CopyFrom(*oLingShanPath._vecData[i]);
        GetInitPathFromString(pLingShanCFGEx->vecInitPath,pLingShanCFGEx->_BornID);
        GetItemFromString(pLingShanCFGEx->vecItemGenInfo,pLingShanCFGEx->_PlayAward);
        _mapLingShanCFGExPtr[pLingShanCFGEx->_ActID]=pLingShanCFGEx;

        _vecItemGenInfo = pLingShanCFGEx->vecItemGenInfo;
    }

    string strLingShanKillPrizePath = Config._strConfigDir + "Conf/Table/LingShanKillPrize.xml";
    CLingShanKillPrizeLoader oLingShanKillPrizePath;
    if(!oLingShanKillPrizePath.LoadData(strLingShanKillPrizePath))
    {
        LOG_CRI << "CZhanQiLoaderLoader fails! Path: " << strLingShanKillPrizePath;
        return false;
    }

    for(size_t i  = 0; i < oLingShanKillPrizePath._vecData.size(); ++i)
    {
        SLingShanKillPrizeCFGExPtr pLingShanKillPrizeCFGEx(new SLingShanKillPrizeCFGEx);
        pLingShanKillPrizeCFGEx->CopyFrom(*oLingShanKillPrizePath._vecData[i]);

        _vecLingShanKillPrizeCFGExPtr.push_back(pLingShanKillPrizeCFGEx);
    }

   
    //模型配置
    string strLingShanModelPath = Config._strConfigDir + "Conf/Table/LingShanModel.xml";
    CLingShanModelLoader oLingShanModelPath;
    if(!oLingShanModelPath.LoadData(strLingShanModelPath))
    {
        LOG_CRI << "CZhanQiLoaderLoader fails! Path: " << strLingShanModelPath;
        return false;
    }


    for(size_t i  = 0; i < oLingShanModelPath._vecData.size(); ++i)
    {
        SLingShanModelCFGExPtr pLingShanModelCFGEx(new SLingShanModelCFGEx);
        pLingShanModelCFGEx->CopyFrom(*oLingShanModelPath._vecData[i]);
        _mapLingShanModelCFGExPtr.insert(make_pair(pLingShanModelCFGEx->_ID,pLingShanModelCFGEx));
    }

    return true;
}

CZhanQiMgr::CZhanQiMgr():CDayActivity(eActTypeLingShan)
{
    _wCurMapID = 0;
    bNeedUpdateRoom = false;
    _wMapSize = 0;
    
}
//获取玩家状态
void CZhanQiMgr::OnGetPlayerStatus(CPlayerPtr pPlayer)
{
    SZhanQiPlayerPtr pZhanQiPlayer = GetMatchPlayer(pPlayer->GetRoleID());
    if(NULL == pZhanQiPlayer)
    {
        pPlayer->SendPkg(g_LingShanProtS.BuildPkg_StatusNotify(eLingShanStatus_Init,0,time(NULL),0));
        return ;
    }

    if(pZhanQiPlayer->eStatus == eLingShanStatus_Wait)
    {

    pPlayer->SendPkg(g_LingShanProtS.BuildPkg_StatusNotify(pZhanQiPlayer->eStatus,pZhanQiPlayer->dwWaitNo,time(NULL),0));
    }
    else
    {

        if(0 == pZhanQiPlayer->dwRoomID)
        {
            LOG_INF<<"not in room!";
            //rPlayer.SendSysMsg(eMsgLingShanNotInRoom);
            return;
        }
        
        CZhanQiRoomPtr pRoom = GetRoom(pZhanQiPlayer->dwRoomID);
        if(NULL == pRoom)
        {
            LOG_CRI<<"eLingShanOP_ErrorRoomId:"<<pZhanQiPlayer->dwRoomID;
            //rPlayer.SendSysMsg(eMsgLingShanErrorRoomId);
            return;
        }
        
        ELingShanStatus eStatus; 
        UINT32 dwTime;
        pRoom->GetRoomPlayerStatus(eStatus,dwTime);
        pPlayer->SendPkg(g_LingShanProtS.BuildPkg_StatusNotify(pZhanQiPlayer->eStatus,dwTime,time(NULL),dwTime));
 
    }
}


//玩家报名
UINT32 CZhanQiMgr::OnPlayerReg(CPlayerPtr pPlayer)
{
    if(NULL == pPlayer)
        return eLingShanOP_Fail;
    // 不在期间
    if(GetStatus() != eDayActivityStatusProcess &&  GetStatus() != eDayActivityStatusReady)
    {
        pPlayer->SendSysMsg(eMsgLingShanNoOpen);
        return eLingShanOP_NoOpen;
    }

    if(GetMatchPlayer(pPlayer->GetRoleID()))
    {
        LOG_INF<<"Has reg!!qwRoleID:"<<pPlayer->GetRoleID();
        return eLingShanOP_Sucess;
    }

    SZhanQiPlayerPtr pZhanQiPlayer(new SZhanQiPlayer);
    pZhanQiPlayer->eStatus  = eLingShanStatus_Wait;
    pZhanQiPlayer->pPlayer  = pPlayer;
    pZhanQiPlayer->qwRoleID = pPlayer->GetRoleID();
    PushWait(pZhanQiPlayer);

    _mapZhanQiPlayerPtr.insert(make_pair(pPlayer->GetRoleID(),pZhanQiPlayer));

    //event
    TVecINT32 vecParam;
    vecParam.push_back(1);
    pPlayer->OnEvent(eEventType_MysteryTreasureJoin,vecParam);
    pPlayer->GetUserPtr()->GetVars().SetVar(NVarDefine::ePlayerVarZhanQi,1);
    LOG_INF<<"OnPlayerReg qwRoleID:"<<pPlayer->GetRoleID();
    return eLingShanOP_Sucess;
}

//玩家移动
UINT32 CZhanQiMgr::OnPlayerMove(CPlayer& rPlayer,UINT16 wDestPos,UINT32& dwMoveCd)
{
    SZhanQiPlayerPtr pZhanQiPlayer = GetMatchPlayer(rPlayer.GetRoleID());
    if(NULL == pZhanQiPlayer)
    {
        LOG_CRI<<"eLingShanOP_NoReg qwRoleID:"<<rPlayer.GetRoleID();
        rPlayer.SendSysMsg(eMsgLingShanNoReg);
        return eLingShanOP_NoReg;
    }

    if( eLingShanStatus_Move != pZhanQiPlayer->eStatus)
    {
        rPlayer.SendSysMsg(eMsgLingShanNoMove);
        return eLingShanOP_NoMove;
    }

    if(pZhanQiPlayer->dwMoveCd > time(NULL))
    {
        rPlayer.SendSysMsg(eMsgLingShanMoveCd);
        return eLingShanOP_MoveCd;
    }

    //1秒cd,不管操作是否有效
    dwMoveCd = time(NULL) + SParamConfig::wSecretAreaMoveCd;
    pZhanQiPlayer->dwMoveCd = dwMoveCd;

    CZhanQiRoomPtr pRoom = GetRoom(pZhanQiPlayer->dwRoomID);
    if(NULL == pRoom)
    {
        LOG_CRI<<"eLingShanOP_ErrorRoomId:"<<pZhanQiPlayer->dwRoomID;
        //rPlayer.SendSysMsg(eMsgLingShanErrorRoomId);
        return eLingShanOP_ErrorRoomId;
    }

    UINT32 eRet = pRoom->OnMove(pZhanQiPlayer,wDestPos);

    if(eRet == eLingShanOP_Sucess)
    {
        TVecINT32 vecParam;
        vecParam.push_back(pRoom->GetCurTurn());
        rPlayer.OnEvent(eEventType_MysteryTreasureMove,vecParam);

    }

    return eRet;
}

//玩家
UINT32 CZhanQiMgr::OnPlayerLeave(CPlayer& rPlayer)
{
    return eLingShanOP_Sucess;
}

//接收：当前棋盘信息状态
UINT32 CZhanQiMgr::OnGetMatchInfo(CPlayer& rPlayer,shared_func<CLingShanProtS::SGetMatchInfoAck>& fnAck)
{
    SZhanQiPlayerPtr pZhanQiPlayer = GetMatchPlayer(rPlayer.GetRoleID());
    if(NULL == pZhanQiPlayer)
    {
        LOG_CRI<<"eLingShanOP_NoReg qwRoleID:"<<rPlayer.GetRoleID();
        rPlayer.SendSysMsg(eMsgLingShanNoReg);
        return eLingShanOP_NoReg;
    }

    if(pZhanQiPlayer->GetVisitRoomID())
    {
        CZhanQiRoomPtr pVisitRoom = GetRoom(pZhanQiPlayer->GetVisitRoomID());
        if(NULL == pVisitRoom)
        {
            LOG_CRI<<"eLingShanOP_ErrorRoomId:"<<pZhanQiPlayer->GetVisitRoomID();
            return eLingShanOP_ErrorRoomId;
        }

        pVisitRoom->OnGetMatchInfo(pZhanQiPlayer,fnAck);

        return eLingShanOP_Sucess;
    }

    if(0 == pZhanQiPlayer->dwRoomID)
    {
        LOG_INF<<"not in room!";
        rPlayer.SendSysMsg(eMsgLingShanNotInRoom);
        return eLingShanOP_NotInRoom;
    }

    CZhanQiRoomPtr pRoom = GetRoom(pZhanQiPlayer->dwRoomID);
    if(NULL == pRoom)
    {
        LOG_CRI<<"eLingShanOP_ErrorRoomId:"<<pZhanQiPlayer->dwRoomID;
        //rPlayer.SendSysMsg(eMsgLingShanErrorRoomId);
        return eLingShanOP_ErrorRoomId;
    }

    pRoom->OnGetMatchInfo(pZhanQiPlayer,fnAck);

    fnAck->dwFreshTurn = pRoom->GetNexFreshTurns();

    //LOG_INF<<"OnGetMatchInfo sucess";

    return eLingShanOP_Sucess;
}

//接收：获取自己的比赛信息 
UINT32 CZhanQiMgr::OnGetMathSelInfo(CPlayer& rPlayer,shared_func<CLingShanProtSvr::SGetMathSelInfoAck>& fnAck)
{
    SZhanQiPlayerPtr pZhanQiPlayer = GetMatchPlayer(rPlayer.GetRoleID());
    if(NULL == pZhanQiPlayer)
    {
        LOG_CRI<<"eLingShanOP_NoReg qwRoleID:"<<rPlayer.GetRoleID();
        rPlayer.SendSysMsg(eMsgLingShanNoReg); 
        return eLingShanOP_NoReg;
    }
    
    fnAck->eStatus   =   pZhanQiPlayer->eStatus;
    fnAck->fHPRate   =   pZhanQiPlayer->fHPRate;
    fnAck->dwBoxCnt  =   pZhanQiPlayer->dwNormalBoxCnt; 
    fnAck->dwSuiYuan =   pZhanQiPlayer->dwSuiYuan;
    fnAck->dwModelID =   pZhanQiPlayer->dwModelID;

    if(0 == pZhanQiPlayer->dwRoomID)
    {
        return eLingShanOP_Sucess;
    }

    CZhanQiRoomPtr pRoom = GetRoom(pZhanQiPlayer->dwRoomID);
    if(NULL == pRoom)
    {
        LOG_CRI<<"eLingShanOP_ErrorRoomId:"<<pZhanQiPlayer->dwRoomID;
        rPlayer.SendSysMsg(eMsgLingShanNotInRoom);
        return eLingShanOP_ErrorRoomId;
    }

    pZhanQiPlayer->GetRoomInfo(fnAck->oRoomPlayInfo);

    fnAck->dwRoomID  =   pZhanQiPlayer->dwRoomID;
    fnAck->dwFreshTurn = pRoom->GetNexFreshTurns();

    //LOG_INF<<"OnGetMathSelInfo";
    //LOG_INF<<"eStatus:"<<pZhanQiPlayer->eStatus;
    //LOG_INF<<"dwBoxCnt:"<<pZhanQiPlayer->GetTotleItemCnt();
    //LOG_INF<<"dwSuiYuan:"<<pZhanQiPlayer->dwSuiYuan;
    //LOG_INF<<"fHPRate:"<<pZhanQiPlayer->fHPRate;
    return eLingShanOP_Sucess;
}



//接收：更换模型信息
UINT32 CZhanQiMgr::OnChangeModel(CPlayer& rPlayer,UINT32 dwModelID,UINT32& dwRetModelID)
{
    SZhanQiPlayerPtr pZhanQiPlayer = GetMatchPlayer(rPlayer.GetRoleID());
    if(NULL == pZhanQiPlayer)
    {
        LOG_CRI<<"eLingShanOP_NoReg qwRoleID:"<<rPlayer.GetRoleID();
        rPlayer.SendSysMsg(eMsgLingShanNoReg);
        return eLingShanOP_NoReg;
    }

    pZhanQiPlayer->dwModelID = dwModelID;

    dwRetModelID = pZhanQiPlayer->dwModelID;

    SLingShanModelCFGExPtr pCFG = GetModelCFG(dwModelID);
    if(NULL == pCFG)
    {
        return eLingShanOP_ErrorModelID;
    }

    //pCFG
    if(pCFG->_CondId)
    {
        CUser& rUser = rPlayer.GetUser();
        UINT16 wCondID = pCFG->_CondId;
        if (!wCondID || !CGetCondMgr::Instance().TestCond(rUser, wCondID))
        {
            rPlayer.SendSysMsg(eMsgLingShanErrorCondID);
            LOG_INF<<"eMsgBeautyGondError";
            return eLingShanOP_ErrorCondID;
        }

        if (!CGetCondMgr::Instance().ProcessCond(rUser, wCondID, NLogDataDefine::ItemTo_LingShan))
        {
            rPlayer.SendSysMsg(eMsgLingShanErrorCondID);
            LOG_INF<<"eMsgBeautyGondError ProcessCond";
            return eLingShanOP_ErrorCondID;
        }
    }

    dwRetModelID = dwModelID;
    
    CZhanQiRoomPtr pRoom = GetRoom(pZhanQiPlayer->dwRoomID);
    if(pRoom)
    {
        pRoom->OnChangeModel(pZhanQiPlayer,dwModelID);
    }

    return eLingShanOP_Sucess;
}

//gain math info
UINT32 CZhanQiMgr::OnGetActInfo(CPlayer& rPlayer,shared_func<CLingShanProtSvr::SGetActInfoAck>& fnAck)
{
    // 不在期间
    if(GetStatus() != eDayActivityStatusProcess &&  GetStatus() != eDayActivityStatusReady)
    {
        rPlayer.SendSysMsg(eMsgLingShanNoOpen);
        return eLingShanOP_NoOpen;
    }

    fnAck->dwBeginTime = _dwBeginTime;
    fnAck->dwEndTime   = _dwEndTime;

    return eLingShanOP_Sucess;
}

//接收：聊天
UINT32 CZhanQiMgr::OnChat(CPlayer& rPlayer,const std::string& strChatMsg)
{
    SZhanQiPlayerPtr pZhanQiPlayer = GetMatchPlayer(rPlayer.GetRoleID());
    if(NULL == pZhanQiPlayer)
    {
        LOG_CRI<<"eLingShanOP_NoReg qwRoleID:"<<rPlayer.GetRoleID();
        rPlayer.SendSysMsg(eMsgLingShanNoReg);
        return eLingShanOP_NoReg;
    }

    if(pZhanQiPlayer->dwNextChatTime >time(NULL))
    {
        LOG_CRI<<"OnChat CD! qwRolID:"<<rPlayer.GetRoleID();
        return eLingShanOP_ChatCD;
    }

    CZhanQiRoomPtr pRoom = GetRoom(pZhanQiPlayer->dwRoomID);
    if(pRoom)
    {
        pRoom->OnChat(rPlayer,strChatMsg);
    }


    return eLingShanOP_Sucess;
}

//获取房间信息
UINT32 CZhanQiMgr::OnGetRoomList(CPlayer& rPlayer,TVecRoomInfo& vecRoomInfo)
{
    SZhanQiPlayerPtr pZhanQiPlayer = GetMatchPlayer(rPlayer.GetRoleID());
    if(NULL == pZhanQiPlayer)
    {
        LOG_CRI<<"eLingShanOP_NoReg qwRoleID:"<<rPlayer.GetRoleID();
        rPlayer.SendSysMsg(eMsgLingShanNoReg);
        return eLingShanOP_NoReg;
    }

    for(size_t i = 0; i < _vecZhanQiRoom.size(); i++)
    {
        CZhanQiRoomPtr pRoom = _vecZhanQiRoom[i];
        if(pRoom)
        {
            SRoomInfo oRoomInfo;
            oRoomInfo.wRoomID = pRoom->GetRoomID();
            oRoomInfo.wPlayerCnt = pRoom->GetPlayerCnt();
            vecRoomInfo.push_back(oRoomInfo);
        }
    }
    return eLingShanOP_Sucess;
}



//进入参观房间
UINT32 CZhanQiMgr::OnEnterVisitRoom(CPlayer& rPlayer,UINT16 wRoomID)
{
    SZhanQiPlayerPtr pZhanQiPlayer = GetMatchPlayer(rPlayer.GetRoleID());
    if(NULL == pZhanQiPlayer)
    {
        LOG_CRI<<"eLingShanOP_NoReg qwRoleID:"<<rPlayer.GetRoleID();
        rPlayer.SendSysMsg(eMsgLingShanNoReg);
        return eLingShanOP_NoReg;
    }

    //离开原先的房间
    CZhanQiRoomPtr pVisitRoom = GetRoom(pZhanQiPlayer->GetVisitRoomID());
    if(pVisitRoom)
    {
        pVisitRoom->OnLeaveVisitRoom(pZhanQiPlayer);
    }

    CZhanQiRoomPtr pEnterRoom = GetRoom(wRoomID);
    if(NULL == pEnterRoom)
    {
        LOG_CRI<<"Unkown RoomID:"<<wRoomID;
        return eLingShanOP_ErrorRoomId;
    }

    pEnterRoom->OnEnterVisitRoom(pZhanQiPlayer);

    pZhanQiPlayer->SetVisitRoomID(wRoomID);


    return eLingShanOP_Sucess;
}

//离开参观房间
UINT32 CZhanQiMgr::OnLeaveVisitRoom(CPlayer& rPlayer)
{
    SZhanQiPlayerPtr pZhanQiPlayer = GetMatchPlayer(rPlayer.GetRoleID());
    if(NULL == pZhanQiPlayer)
    {
        LOG_CRI<<"eLingShanOP_NoReg qwRoleID:"<<rPlayer.GetRoleID();
        rPlayer.SendSysMsg(eMsgLingShanNoReg);
        return eLingShanOP_NoReg;
    }

    //离开原先的房间
    CZhanQiRoomPtr pVisitRoom = GetRoom(pZhanQiPlayer->GetVisitRoomID());
    if(pVisitRoom)
    {
        pVisitRoom->OnLeaveVisitRoom(pZhanQiPlayer);
    }

    pZhanQiPlayer->SetVisitRoomID(0);

    return eLingShanOP_Sucess;
}

//接收：获取动画播放信息
UINT32 CZhanQiMgr::OnGetPlayMovieInfo(CPlayer& rPlayer,shared_func<CLingShanProtSvr::SGetPlayMovieInfoAck> fnAck)
{
    SZhanQiPlayerPtr pZhanQiPlayer = GetMatchPlayer(rPlayer.GetRoleID());
    if(NULL == pZhanQiPlayer)
    {
        LOG_CRI<<"eLingShanOP_NoReg qwRoleID:"<<rPlayer.GetRoleID();
        rPlayer.SendSysMsg(eMsgLingShanNoReg);
        return eLingShanOP_NoReg;
    }

    if(pZhanQiPlayer->GetVisitRoomID())
    {
        CZhanQiRoomPtr pVisitRoom = GetRoom(pZhanQiPlayer->GetVisitRoomID());
        if(NULL == pVisitRoom)
        {
            LOG_CRI<<"eLingShanOP_ErrorRoomId:"<<pZhanQiPlayer->GetVisitRoomID();
            return eLingShanOP_ErrorRoomId;
        }

        return pVisitRoom->OnGetRoomPlayMovieInfo(rPlayer,fnAck);

        //return eLingShanOP_Sucess;
    }

    if(0 == pZhanQiPlayer->dwRoomID)
    {
        LOG_INF<<"not in room!";
        rPlayer.SendSysMsg(eMsgLingShanNotInRoom);
        return eLingShanOP_NotInRoom;
    }

    CZhanQiRoomPtr pRoom = GetRoom(pZhanQiPlayer->dwRoomID);
    if(NULL == pRoom)
    {
        LOG_CRI<<"eLingShanOP_ErrorRoomId:"<<pZhanQiPlayer->dwRoomID;
        //rPlayer.SendSysMsg(eMsgLingShanErrorRoomId);
        return eLingShanOP_ErrorRoomId;
    }

    ELingShanOP eRet = pRoom->OnGetRoomPlayMovieInfo(rPlayer,fnAck);

    //LOG_INF<<"OnGetPlayMovieInfo sucess";

    return eRet;

}



// GM指令直接开启活动
bool CZhanQiMgr::GMOpen()
{

 //if(_bLog)
   LOG_INF<<"CZhanQiMgr::GMOpen";
   
   if(GetStatus()!=eDayActivityStatusInit)
   {
       LOG_CRI<<"LingShan is In run!!!";
       return false;
   }
   
   time_t tNow = time(NULL);
   _dwAlarmTime = tNow;
   _dwReadyTime = tNow;
   _dwBeginTime = tNow + 30;  //
   _dwEndTime   = tNow + 10*60; //

   ClearEvent();

   SetStatus(eDayActivityStatusAlarm);


    return true;
}

// 程序开始准备
bool CZhanQiMgr::OnAlarm()
{
    if(!_vecZhanQiRoom.empty()) 
    {
        LOG_CRI<<"Activity Has run!!!";
        return false;
    }

    CDayActivity::OnAlarm();
    LOG_INF<<"CZhanQiMgr::OnAlarm";

    ClearEvent();
    return true;
}

// 开始通知
void CZhanQiMgr::OnReady()
{
    CDayActivity::OnReady();

    //UINT32 dwActID = GetParam();
    LOG_INF<<"CZhanQiMgr::OnReady";

    g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgLingShanReady);
}
void CZhanQiMgr::OnBegin()
{    
    if(!_vecZhanQiRoom.empty())
    {
        //OnAllEnd();
        LOG_CRI<<" activit has not end!!!";
        return;
    }

    CDayActivity::OnBegin();

    //设置当前配置
    SetCurLingShanCFGEx();

    //1s
    AddPeriodEvent(Event_Update,time(NULL),-1,1);

    //60s
    AddPeriodEvent(Event_AddExp,time(NULL),-1,60);

    LOG_INF<<"CZhanQiMgr::OnBegin:"<<GetParam();
    g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgLingShanBegin);

}

void CZhanQiMgr::OnEnd()
{
    CDayActivity::OnEnd();

    //AddEvent(Event_SendPrize,time(NULL) + 60 );

    for(size_t i = 0; i < _vecZhanQiRoom.size();i++)
    {
        if(_vecZhanQiRoom[i])
        {
            _vecZhanQiRoom[i]->OnGameOver();
        }
    }

    g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgLingShanEnd); 

    ClearEvent(Event_AddExp);

    OnAllEnd(); 
}

bool   CZhanQiMgr::IsEnd()
{
    return GetStatus() == eDayActivityStatusEnd;
}
// 服务器重启,处于活动期间的处理 
void CZhanQiMgr::OnReBegin()
{
    //默认活动正常开启
    OnAlarm();
}

// 重置原始状态
void CZhanQiMgr::ResetState()
{
    CDayActivity::ResetState();
}

//是否开放
bool CZhanQiMgr::IsOpen()
{
    return GetStatus() == eDayActivityStatusProcess;
}


// 注册事件触发
void CZhanQiMgr::OnEvent(SActEventData& oSActEventData)
{
    switch(oSActEventData.dwEventID)
    {
        case Event_Update:
            {
                OnSecUpdate();
            }
            break;
        case Event_SendPrize:
            {
                //OnAllEnd();
            }
            break;
        case Event_AddExp:
            {
                OnAddExp();
            }
            break;
    }
}

//每秒更新
void CZhanQiMgr::OnSecUpdate()
{
    for(size_t i = 0; i < _vecZhanQiRoom.size();i++)
    {
        if(_vecZhanQiRoom[i])
        {
            _vecZhanQiRoom[i]->OnSecUpdate();
        }
    }
    //Process阶段
    if(!IsOpen())
    {
        return;
    }

    if(NULL == _pCurLingShanCFGEx)
            return;

    if(IsNeedCreateRoom())
    {
        CreateRoom();
    }

}

//检查是否创建房间
bool CZhanQiMgr::IsNeedCreateRoom()
{
    if(NULL == _pCurLingShanCFGEx)
        return false;

    //no player
    if(_dequeZhanQiPlayerPtr.empty())
        return false;

    if(_vecZhanQiRoom.empty())
        return true;

    //测试代码
    //if(_vecZhanQiRoom.size() < 2)
    //    return true;
    //else
    //    return false;

    if(_dequeZhanQiPlayerPtr.size() < _pCurLingShanCFGEx->_SpawPlayerCnt*_vecZhanQiRoom.size())
    {
        return false;
    }

    //（排队人数-每轮加入人数×当前房间数）>房间标准人数
    UINT32 dwCnt = _dequeZhanQiPlayerPtr.size() - _pCurLingShanCFGEx->_SpawPlayerCnt*_vecZhanQiRoom.size();

    if(dwCnt>_pCurLingShanCFGEx->_TotalPlayerCnt)
        return true;
    return false;
}

//创建新的房间
void CZhanQiMgr::CreateRoom()
{
    LOG_INF<<"CreateRoom!!!";
    if(NULL == _pCurLingShanCFGEx)
    {
        LOG_CRI<<"NULL == _pCurLingShanCFGEx";
        return;
    }

    CZhanQiRoomPtr pZhanQiRoom(new CZhanQiRoom);

    _vecZhanQiRoom.push_back(pZhanQiRoom);

    pZhanQiRoom->SetRoomID(_vecZhanQiRoom.size());

    UINT32 dwMaxSize = _pCurLingShanCFGEx->_InitPlayerCnt > _pCurLingShanCFGEx->vecInitPath.size()?_pCurLingShanCFGEx->vecInitPath.size():_pCurLingShanCFGEx->_InitPlayerCnt; 

    TVecZhanQiPlayerPtr vecZhanQiPlayerPtr;
    GetWaitPlayer(vecZhanQiPlayerPtr,dwMaxSize); 
    pZhanQiRoom->StartGame(vecZhanQiPlayerPtr,_pCurLingShanCFGEx->vecInitPath,_wMapSize);
   // _vecZhanQiRoom.push_back(pZhanQiRoom);
}

//一定数量的获取排队的玩家
void CZhanQiMgr::GetWaitPlayer(TVecZhanQiPlayerPtr& vecZhanQiPlayerPtr,UINT16 wPlayerCnt)
{
    UINT16 wPopCnt = 0;

    while(!_dequeZhanQiPlayerPtr.empty() && wPopCnt<wPlayerCnt)
    {
        SZhanQiPlayerPtr pZhanQiPlayer = _dequeZhanQiPlayerPtr.front();
        vecZhanQiPlayerPtr.push_back(pZhanQiPlayer);
        _dequeZhanQiPlayerPtr.pop_front();

        if(NULL == pZhanQiPlayer->pPlayer.lock())
        {
            CUserMgr::LoadUser(pZhanQiPlayer->qwRoleID,[pZhanQiPlayer](CUserPtr pUser)
                    {
                        pZhanQiPlayer->pPlayer=pUser->GetPlayer();
                    }
                );
            LOG_CRI<<"Login offline qwRoleID:"<<pZhanQiPlayer->qwRoleID;
        }
        wPopCnt++;
    }

    LOG_INF<<"GetWaitPlayer:"<<vecZhanQiPlayerPtr.size();
    NotifyWaitNoUpdate();

}

//通知队列状态改变
void CZhanQiMgr::NotifyWaitNoUpdate()
{
    UINT32 dwWaitNo = 0;
    for(auto itr=_dequeZhanQiPlayerPtr.begin(); itr != _dequeZhanQiPlayerPtr.end();itr++)
    {
        dwWaitNo++;
        SZhanQiPlayerPtr pZhanQiPlayer = *itr;
        if(pZhanQiPlayer)
        {
            pZhanQiPlayer->dwWaitNo = dwWaitNo;

            CPlayerPtr pPlayer = pZhanQiPlayer->pPlayer.lock();
            if(pPlayer)
            {
                pPlayer->SendPkg(g_LingShanProtS.BuildPkg_StatusNotify(eLingShanStatus_Wait,pZhanQiPlayer->dwWaitNo,time(NULL),0));


            }
        }
    }
}


//加入等待队列
void CZhanQiMgr::PushWait(SZhanQiPlayerPtr pZhanQiPlayerPtr)
{
    if(NULL == pZhanQiPlayerPtr)
        return;

    pZhanQiPlayerPtr->ResetWait();
    _dequeZhanQiPlayerPtr.push_back(pZhanQiPlayerPtr);
    pZhanQiPlayerPtr->dwWaitNo = _dequeZhanQiPlayerPtr.size();
    pZhanQiPlayerPtr->eStatus = eLingShanStatus_Wait;
    pZhanQiPlayerPtr->dwRoomID = 0;

    CPlayerPtr pPlayer = pZhanQiPlayerPtr->pPlayer.lock();
    if(pPlayer)
    {
        pPlayer->SendPkg(g_LingShanProtS.BuildPkg_StatusNotify(eLingShanStatus_Wait,pZhanQiPlayerPtr->dwWaitNo,time(NULL),0));

    }
}

//获取报名玩家
SZhanQiPlayerPtr CZhanQiMgr::GetMatchPlayer(UINT64 qwRoleID)
{
    auto itr = _mapZhanQiPlayerPtr.find(qwRoleID);
    if(itr != _mapZhanQiPlayerPtr.end())
        return itr->second;
    return NULL;
}

//获取连杀奖励,wKillCnts>=1
UINT32 CZhanQiMgr::GetLastKillPrize(UINT16 wKillCnts)
{
    if(0 == wKillCnts)
        return 0;

    if(_vecLingShanKillPrizeCFGExPtr.empty())
    {
        LOG_CRI<<"_vecLingShanKillPrizeCFGExPtr.empty";
        return 0;
    }

    SLingShanKillPrizeCFGExPtr pLingShanKillPrizeCFGEx;
    UINT32 dwPos = wKillCnts - 1;
    if(dwPos>=_vecLingShanKillPrizeCFGExPtr.size())
    {
        pLingShanKillPrizeCFGEx = _vecLingShanKillPrizeCFGExPtr[_vecLingShanKillPrizeCFGExPtr.size()-1];
    }
    else
    {
        pLingShanKillPrizeCFGEx = _vecLingShanKillPrizeCFGExPtr[dwPos];
    }

    if(NULL == pLingShanKillPrizeCFGEx)
    {
        LOG_CRI<<"NULL == pLingShanKillPrizeCFGEx";
        return 0;
    }

    return pLingShanKillPrizeCFGEx->_SuiYuan;
}

//取当前活动配置活动配置
SLingShanCFGExPtr CZhanQiMgr::GetCurLingShanCFG()
{
    UINT32 dwActID = GetParam();
    return GetLingShanCFG(dwActID);
}

//取当前活动配置地图
TVecLingShanMapCFGExPtr& CZhanQiMgr::GetCurMapCFG()
{
    return _mapVecLingShanMapCFGExPtr[_wCurMapID];
}




//获取活动配置
SLingShanCFGExPtr CZhanQiMgr::GetLingShanCFG(UINT32 dwActID)
{
    auto itr = _mapLingShanCFGExPtr.find(dwActID);
    if(itr != _mapLingShanCFGExPtr.end())
        return itr->second;

    LOG_CRI<<"Error dwActID:"<<dwActID;

    return NULL;
}

//设置当前活动
void CZhanQiMgr::SetCurLingShanCFGEx()
{
    _pCurLingShanCFGEx = GetCurLingShanCFG();
    if(NULL == _pCurLingShanCFGEx)
    {
        LOG_CRI<<"Error NULL == CurLingShanCFGEx";
        return;
    }

    _vecItemGenInfo = _pCurLingShanCFGEx->vecItemGenInfo; 

    _wCurMapID = _pCurLingShanCFGEx->_MapID;

    TVecLingShanMapCFGExPtr& rVecCFG = GetCurMapCFG();
    _wMapSize = rVecCFG.size();
    LOG_INF<<"SetCurLingShanCFGEx MAP:"<<_wCurMapID<<"Max size:"<<_wMapSize;

}

CZhanQiRoomPtr CZhanQiMgr::GetRoom(UINT32 dwRoomID)
{
    if(0 == dwRoomID)
    {
        return NULL;
    }
    
    if(dwRoomID>_vecZhanQiRoom.size())
    {
        return NULL;
    }

    return _vecZhanQiRoom[dwRoomID-1];
}
    
//获取模型锁定条件
SLingShanModelCFGExPtr CZhanQiMgr::GetModelCFG(UINT32 dwModelID)
{
    auto itr = _mapLingShanModelCFGExPtr.find(dwModelID);

    if(itr != _mapLingShanModelCFGExPtr.end())
    {
        return itr->second;
    }
    return NULL;
}

void CZhanQiMgr::OnAllEnd()
{
    if( NULL == _pCurLingShanCFGEx)
    {
        return;
    }

    UINT16 wItemID = _pCurLingShanCFGEx->_NormalBoxID;
    
    TVecUINT64 vecSendUserID;
    for(auto itr = _mapZhanQiPlayerPtr.begin(); itr != _mapZhanQiPlayerPtr.end(); itr++)
    {
        SZhanQiPlayerPtr pZhanQiPlayer = itr->second;
        if(pZhanQiPlayer)
        {
            //clear db
            ClearItemDB(pZhanQiPlayer);

            TVecItemGenInfo vecItems;
            SItemGenInfo oItemGenInfo;
            oItemGenInfo.wItemID = wItemID;
            oItemGenInfo.dwCount = pZhanQiPlayer->GetTotleItemCnt();
            vecItems.push_back(oItemGenInfo);

            for(size_t i = 0;i < _vecItemGenInfo.size();i++)
            {
                vecItems.push_back(_vecItemGenInfo[i]);
            }

            TVecUINT64 vecUserID;
            vecUserID.push_back(pZhanQiPlayer->qwRoleID);
            NMailProt::SysMailSendTxt stBody;
            stBody.dwstrMsgID = BODY_LINGSHAN;
            //stBody.vecParam.push_back(NumberToString(pPlayer->dwNo));
            GameServerSysMail::SendSysMail(SEND_LINGSHAN, TITLE_LINGSHAN, stBody, vecUserID, &vecItems);

            vecSendUserID.push_back(pZhanQiPlayer->qwRoleID);

            CPlayerPtr pPlayer = pZhanQiPlayer->pPlayer.lock();
            if(pPlayer)
            {
                TVecINT32 vecParam;
                vecParam.push_back(pZhanQiPlayer->GetTotleItemCnt());
                pPlayer->OnEvent(eEventType_MysteryTreasureBox,vecParam);
            }
            else
            {
                LOG_CRI<<"Player offline!!!";
            }
        }
    }

    _mapZhanQiPlayerPtr.clear();

    _dequeZhanQiPlayerPtr.clear();

    _vecZhanQiRoom.clear();

    if(!vecSendUserID.empty())
    {
        g_LingShanProtS.SendClt_StatusNotify(vecSendUserID.data(),(UINT16)vecSendUserID.size(),eLingShanStatus_End,0,time(NULL),0);
    }

    ResetState();
}

//所有参加活动的玩家加经验
void CZhanQiMgr::OnAddExp()
{
    for(auto itr = _mapZhanQiPlayerPtr.begin(); itr != _mapZhanQiPlayerPtr.end(); itr++)
    {
        SZhanQiPlayerPtr pZhanQiPlayer = itr->second;
        if(pZhanQiPlayer)
        {
           CPlayerPtr pPlayer =  pZhanQiPlayer->pPlayer.lock();
           if(pPlayer)
           {
               UINT64 qwExp = CExpMgr::GetBaseSitExp(pPlayer->GetLevel()) * SParamConfig::wSecretAreaExp;
               pPlayer->AddExp(qwExp,true);

           }
        }
    }
}


//是否可以下线
bool CZhanQiMgr::IsInAct(UINT64 qwRoleID)
{

    if(_mapZhanQiPlayerPtr.empty())
        return false;

    return (_mapZhanQiPlayerPtr.find(qwRoleID) != _mapZhanQiPlayerPtr.end());
}


 //登陆事件
void   CZhanQiMgr::OnLogin(CPlayer& rPlayer)
{
    SZhanQiPlayerPtr pZhanQiPlayer = GetMatchPlayer(rPlayer.GetRoleID()); 
    if(NULL != pZhanQiPlayer)
        return;
    CAutoStoreMgrPtr pAutoStoreMgr = rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        UINT16 wItemCnt = pAutoStoreMgr->GetValue(eAutoStore_ZhanQi,eZhanQiAuto_ItemCnt);
        if(0 == wItemCnt)
            return;

        UINT16 wItemID =  pAutoStoreMgr->GetValue(eAutoStore_ZhanQi,eZhanQiAuto_ItemID);

        //当机补偿邮件
        pAutoStoreMgr->ClearValue(eAutoStore_ZhanQi);
        TVecItemGenInfo vecItems;
        SItemGenInfo oItemGenInfo;
        oItemGenInfo.wItemID = wItemID;
        oItemGenInfo.dwCount = wItemCnt; //pZhanQiPlayer->GetTotleItemCnt();
        vecItems.push_back(oItemGenInfo);
        TVecUINT64 vecUserID;
        vecUserID.push_back(rPlayer.GetRoleID());
        NMailProt::SysMailSendTxt stBody;
        stBody.dwstrMsgID = BODY_LINGSHAN;
        //stBody.vecParam.push_back(NumberToString(pPlayer->dwNo));
        if(oItemGenInfo.dwCount)
            GameServerSysMail::SendSysMail(SEND_LINGSHAN, TITLE_LINGSHAN, stBody, vecUserID, &vecItems);

    }

}

//保存当前获得的物品
void   CZhanQiMgr::SaveItem(SZhanQiPlayerPtr pZhanQiPlayer)
{
    if(NULL == pZhanQiPlayer)
    {
        return;
    }

    if( NULL == _pCurLingShanCFGEx)
        return;
    CPlayerPtr pPlayer = pZhanQiPlayer->pPlayer.lock();
    if(pPlayer)
    {
        CAutoStoreMgrPtr pAutoStoreMgr = pPlayer->GetAutoStoreMgr();
        if(pAutoStoreMgr)
        {
            pAutoStoreMgr->SetValue(eAutoStore_ZhanQi,eZhanQiAuto_ItemID,_pCurLingShanCFGEx->_NormalBoxID);
            pAutoStoreMgr->SetValue(eAutoStore_ZhanQi,eZhanQiAuto_ItemCnt,pZhanQiPlayer->GetTotleItemCnt());
        }
    }
}

//数据库数据
void   CZhanQiMgr::ClearItemDB(SZhanQiPlayerPtr pZhanQiPlayer)
{
    if(NULL == pZhanQiPlayer)
    {
        return;
    }
    CPlayerPtr pPlayer = pZhanQiPlayer->pPlayer.lock();
    if(pPlayer)
    {
        CAutoStoreMgrPtr pAutoStoreMgr = pPlayer->GetAutoStoreMgr();
        if(pAutoStoreMgr)
        {
            pAutoStoreMgr->ClearValue(eAutoStore_ZhanQi);

        }
    }

}

   
    

    
    
