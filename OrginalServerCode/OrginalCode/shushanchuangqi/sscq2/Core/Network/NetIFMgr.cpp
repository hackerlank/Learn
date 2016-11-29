/********************************************************************
// Server Network Library Source File.
// File name:  NetIFMgr.cpp
// Created:    2012/08/21  11:00
// Organization:
// Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
// Author:     Jingyuan Wang
// E-Mail:     tyketom@hotmail.com
// Http://
// ------------------------------------------------------------------
// Purpose:
// Version:    1.0
// Histroy:
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#ifndef _WIN32
#include <sys/syscall.h>
#include "LinuxTime.h"
#include "Exception.h"
#endif
#include "GlobalDefine.h"
#include "NetIFMgr.h"
#include "Directory.h"
#include "BaseSocket.h"
#include "BaseListener.h"
#include "ServerID.h"

#ifdef _WIN32
#define gettid() GetCurrentThreadId()
#elif defined(__MACH__)
#define gettid() syscall(SYS_thread_selfid)
#else
#define gettid() syscall(__NR_gettid)
#endif

CLog g_oNetLog;

FnUserLogic CNetIFMgr::_fnUserLogic;
FnExceptionCallback CNetIFMgr::_fnExceptionCallback;
FnUserLogicExit CNetIFMgr::_fnPreShutdown;
FnUserLogicExit CNetIFMgr::_fnUserLogicExit;

CNetIFMgr* CNetIFMgr::_pNetIFMgr;

    CNetIFMgr::CNetIFMgr()
    : _eSvrType(eHostNone)
    , _dwClientBufSize(0)
    , _dwServerBufSize(0)
    , _bRun(false)
    , _bLogicRun(false)
    , _bNetRun(false)
    , _bManRun(false)
    , _bListenRun(false)
    , _itEvt(_deqNetEvt.begin())
      , _qwLogicStartTick(0)
{
    _pNetIFMgr = this;
}

CNetIFMgr::~CNetIFMgr()
{
    _pNetIFMgr = NULL;
}

bool CNetIFMgr::Init(UINT32 dwSvrID, UINT32 dwClientBufSize, UINT32 dwServerBufSize,UINT8 byIndex)
{
    _eSvrType = ::GetServerType(dwSvrID);
    if(_eSvrType == eHostNone)
        return false;
#if USE_LOG
    string strDir;
    GetCurDirectory(strDir);
    strDir += "NetLog";
    if(!CreateDirectory(strDir))
        return false;
    string strShortName = GetServerShortName(_eSvrType);
    if(byIndex > 1)
    {
         char buf[255];
        snprintf(buf,10,"%d/n",byIndex);
        strShortName += string(buf);
    }
    string strCurDir;
    strCurDir = strDir + "/";
    strCurDir = strCurDir + strShortName;
    if(!CreateDirectory(strCurDir))
        return false;
    g_oNetLog.SetSvrID(dwSvrID);
    g_oNetLog.SetAutoFlush(true);
    g_oNetLog.OpenConsole();
    if(!g_oNetLog.OpenLog(strCurDir, "Net"))
        return false;
    if(!g_oNetLog.Start())
        return false;
#endif

    
    if(dwClientBufSize == 0 || dwServerBufSize == 0)
        return false;
    _dwClientBufSize = dwClientBufSize;
    _dwServerBufSize = dwServerBufSize;

    _bRun = _bNetRun = _bLogicRun = _bManRun = _bListenRun = true;
    UINT32 dwPageSize = GetSysPageSize();
    if(dwPageSize < 4096)
        dwPageSize = 4096;

    if((_dwClientBufSize % dwPageSize) != 0)
        _dwClientBufSize = (_dwClientBufSize / dwPageSize + 1) * dwPageSize;
    if((_dwServerBufSize % dwPageSize) != 0)
        _dwServerBufSize = (_dwServerBufSize / dwPageSize + 1) * dwPageSize;

    if(!CBaseSocket::AllocLogicBuf(dwServerBufSize))
        return false;

    return true;
}

void CNetIFMgr::Shutdown()
{
    _bRun = false;
    _evtShutdown.Set();
}

void CNetIFMgr::WaitForShutdown()
{
    _evtShutdown.Wait();
    g_oNetLog.Stop();
    ShutdownListener();
    ShutdownNotify();
    ShutdownWaitSending();
    ShutdownListenThread();
    ShutdownNetworkThread();
    ShutdownManageThread();
    ShutdownLogicThread();
    for(auto it = _mapListener.begin(); it != _mapListener.end(); ++it)
        delete it->second;
    _mapListener.clear();
    for(auto it = _mapConnector.begin(); it != _mapConnector.end(); ++it)
        AddSockToDel(it->second);
    _mapConnector.clear();
    CheckDelSock(false);
    CBaseSocket::ReleaseLogicBuf();
}

void CNetIFMgr::OnInitFinish()
{
    _evtInit.Set();
}

void CNetIFMgr::AddListener(UINT16 wPort, CBaseListener* pListener)
{
    if(!IsRun())  //判断网络是否在运行
    {
        delete pListener;
        return;
    }
    CAutoLock<CSpinLock> oAutoLock(_spLsn);
    _mapListener.insert(make_pair(wPort, pListener));
}

void CNetIFMgr::DelListener(UINT16 wPort)
{
    CAutoLock<CSpinLock> oAutoLock(_spLsn);
    auto it = _mapListener.find(wPort);
    if(it == _mapListener.end())
        return;
    delete it->second;
    _mapListener.erase(it);
}

CBaseListener* CNetIFMgr::GetListener(UINT16 wPort)
{
    CBaseListener* pListener = NULL;
    CAutoLock<CSpinLock> oAutoLock(_spLsn);
    auto it = _mapListener.find(wPort);
    if(it != _mapListener.end())
        pListener = it->second;
    return pListener;
}

void CNetIFMgr::GetListeners(map<UINT16, CBaseListener*>& rMapListener)
{
    CAutoLock<CSpinLock> oAutoLock(_spLsn);
    rMapListener = _mapListener;
}

void CNetIFMgr::AddConnector(SIPAndPort& rIPAndPort, CBaseSocket* pSocket)
{
    if(!IsRun())
        return;
    CAutoLock<CSpinLock> oAutoLock(_spCon);
    if(_mapConnector.insert(make_pair(rIPAndPort, pSocket)).second)
    {
        pSocket->SetSave();
    }
}

void CNetIFMgr::DelConnector(CBaseSocket* pSocket)
{
    CAutoLock<CSpinLock> oAutoLock(_spCon);
    if(pSocket)
    {
        pSocket->SetSave(false);
    }
    for(auto it = _mapConnector.begin(); it != _mapConnector.end(); ++it)
    {
        if(pSocket == it->second)
        {
            _mapConnector.erase(it);
            break;
        }
    }
}

bool CNetIFMgr::IsConnecting(SIPAndPort& rIPAndPort)
{
    CAutoLock<CSpinLock> oAutoLock(_spCon);
    return _mapConnector.find(rIPAndPort) != _mapConnector.end();
}

void CNetIFMgr::ManageThread(CNetIFMgr* pThis)
{
    while(pThis->_bManRun)
    {
        pThis->CheckDelSock(false);
        Sleep(100);
    }
}

void CNetIFMgr::LogicThread(CNetIFMgr* pThis)
{
    UINT64 qwStartTick = 0, qwCurTick = 0;
    pThis->_evtInit.Wait();
#if defined(__GNUG__) && defined(ROBUST_USER_LOGIC)
    if(sigsetjmp(CException::_env, 1) != 0)
        LOG_CRI << "thread " << gettid() << " restart!";
    else
#endif
        LOG_INF << "Thread: " << gettid() << " starts!";
    pThis->TrimNetEvent();
    while(pThis->_bLogicRun)
    {
        qwStartTick = GetTickCount64();
        do {
            if(pThis->PopNetEvent())
            {
                //try
                //{
                for(pThis->_itEvt = pThis->_deqNetEvt.begin(); pThis->_itEvt != pThis->_deqNetEvt.end();)
                {
                    SNetEvent& rEvt = *pThis->_itEvt++;
                    pThis->ProcessNetEvent(rEvt);
                }
                pThis->_deqNetEvt.clear();
                //}
#if 0
                catch(const char* e)
                {
                    LOG_CRI << "catch string: " << e;
                }
                catch(std::exception& e)
                {
                    LOG_CRI << "catch std::exception: " << e.what();
                }
                catch(...)
                {
                    LOG_CRI << "catch unknown exception!";
                }
#endif
            }
            else if(!pThis->ProcessUserLogic(0)) //处理一次用户逻辑
            {
                Sleep(1);
            }
            qwCurTick = GetTickCount64();
        }
        while(pThis->_bLogicRun && qwCurTick - qwStartTick < SERVER_LOGIC_MAX_MILLISECOND);
        pThis->ProcessUserLogic(USER_LOGIC_MAX_MILLISECOND); //批量处理用户逻辑
    }
    if(_fnUserLogicExit)
        _fnUserLogicExit();
}

bool CNetIFMgr::ProcessNetEvent(SNetEvent& rNetEvt)
{
    _qwLogicStartTick = GetTickCount64();
    switch(rNetEvt.eType)
    {
        case eConnect:
            rNetEvt.connect.pSocket->NotifyConnect(rNetEvt.connect.bSucceed);
            break;
        case eAccept:
            rNetEvt.accept.pSocket->NotifyAccept();
            break;
        case eRecv:
            rNetEvt.recv.pSocket->NotifyRecv(rNetEvt.recv.len);
            break;
        case eTimer:
            rNetEvt.timer.pTimer->OnTimer();
            break;
        case eClose:
        case eError:
            rNetEvt.close.pSocket->NotifyClose();
            break;
        case eFunc:
            rNetEvt.func.pFunc();
            break;
        default:
            LOG_CRI << "Event Error! Type: " << rNetEvt.eType;
            break;
    }
    return true;
}

bool CNetIFMgr::ProcessUserLogic(UINT64 dwMaxTickCount)
{
    bool bBusy = false;
    if(_bLogicRun && _fnUserLogic != NULL)
    {
        UINT64 qwCurTick = 0;
        _qwLogicStartTick = GetTickCount64();
        do
        {
            bBusy = _fnUserLogic();
            if(!bBusy)
                break;
            qwCurTick = GetTickCount64();
        }
        while(_bLogicRun && qwCurTick - _qwLogicStartTick < dwMaxTickCount);
    }
    return bBusy;
}

void CNetIFMgr::TrimNetEvent()
{
    if(_bLogicRun)
        _deqNetEvt.erase(_deqNetEvt.begin(), _itEvt);
}

bool CNetIFMgr::PushNetEvent(SNetEvent& rNetEvt)
{
    if(!_bLogicRun)
        return false;
    return _queEvent.Push(rNetEvt);
}

bool CNetIFMgr::PopNetEvent()
{
    _queEvent.PopAll(_deqNetEvt);
    return !_deqNetEvt.empty();
}

void CNetIFMgr::AddSockToDel(CBaseSocket* pSocket)
{
    pSocket->SetEstablished();
    pSocket->SetClose();
    CAutoLock<CSpinLock> oAutoLock(_spDel);
        _setDelSocket.insert(pSocket);
}

bool CNetIFMgr::CheckDelSock(bool bForce)
{
    CAutoLock<CSpinLock> oAutoLock(_spDel);
    for(auto it = _setDelSocket.begin(); it != _setDelSocket.end();)
    {
        CBaseSocket* pSocket = *it;
        if(pSocket)
        {
            if (bForce || pSocket->CanClose())
            {
                if(pSocket->IsSave())
                    DelConnector(pSocket);
                it = _setDelSocket.erase(it);
                delete pSocket;
                pSocket = NULL;
            }
            else
                ++it;
        }
        else
            it = _setDelSocket.erase(it);
    }
    return !_setDelSocket.empty();
}

bool CNetIFMgr::CheckDel()
{
    return CheckDelSock(false);
}

void CNetIFMgr::SetUserLogicFunc(FnUserLogic fnUserLogic)
{
    _fnUserLogic = fnUserLogic;
}

void CNetIFMgr::SetExceptionCallbackFunc(FnExceptionCallback fnExceptionCallback)
{
    _fnExceptionCallback = fnExceptionCallback;
}

void CNetIFMgr::OnExceptionCallback(EExceptType eExceptType)
{
    if(_fnExceptionCallback != NULL)
        _fnExceptionCallback(eExceptType);
}

void CNetIFMgr::SetUserLogicExit(FnUserLogicExit fnUserLogicExit)
{
    _fnUserLogicExit = fnUserLogicExit;
}

void CNetIFMgr::SetPreShutdown(FnUserLogicExit fnPreShutdown)
{
    _fnPreShutdown = fnPreShutdown;
}

void CNetIFMgr::ShutdownListener()
{
    map<UINT16, CBaseListener*> mapListeners;
    GetListeners(mapListeners);
    for(auto it = mapListeners.begin(); it != mapListeners.end(); ++it)
    {
        CBaseListener* pListener = it->second;
        pListener->StopListen();
    }
}

void CNetIFMgr::DoPreShutdown()
{
    CNetIFMgr& rMgr = Instance();
    if(rMgr._fnPreShutdown)
        rMgr._fnPreShutdown();
    rMgr._evtPreShutdown.Set();
}

void CNetIFMgr::ShutdownNotify()
{
    SNetEvent oEvt;
    oEvt.eType = eFunc;
    oEvt.func.pFunc = DoPreShutdown;
    PushNetEvent(oEvt);
    _evtPreShutdown.Wait();
}

void CNetIFMgr::ShutdownWaitSending()
{
    while(true)
    {
        {
            CAutoLock<CSpinLock> oAutoLock(_spDel);
            if(_setDelSocket.empty())
                break;
        }
        Sleep(50);
    }
}

void CNetIFMgr::ShutdownLogicThread()
{
    _bLogicRun = false;
    _tLogicThread.Join();
}

void CNetIFMgr::ShutdownListenThread()
{
    _bListenRun = false;
    _tListenThread.Join();
    map<UINT16, CBaseListener*> mapListener;
    GetListeners(mapListener);
    for(auto it = mapListener.begin(); it != mapListener.end(); ++it)
    {
        CBaseListener* pListener = it->second;
        pListener->WaitStop(300);
        DelListener(it->first);
    }
}

void CNetIFMgr::ShutdownNetworkThread()
{
    _bNetRun = false;
    for(CThread& t : _vecNetworkThreads)
        t.Join();
    _vecNetworkThreads.clear();
}

void CNetIFMgr::ShutdownManageThread()
{
    _bManRun = false;
    _tManageThread.Join();
}
