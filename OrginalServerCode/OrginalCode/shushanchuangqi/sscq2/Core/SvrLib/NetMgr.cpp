/********************************************************************
//	Server Common Library Source File.
//	File name:	NetMgr.cpp
//	Created:	2011/06/06	10:00
//	Organization:
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:
//	Version:	1.0
//	Histroy:
*********************************************************************/

#include "GlobalDefine.h"
#include "ServerID.h"
#include "BatchFunc.h"
#include "NetMgr.h"
#include "UtilFunc.h"

CNetMgr* CNetMgr::_pNetMgr;

void CConnectHandler::OnConnect(ISocket& rSocket, bool bSucceed)
{
	CNetMgr* pNetMgr = CNetMgr::GetNetMgr(); //XXX: 获得 本服务器网关
	if(pNetMgr == NULL)
		return;
	CConfig::GetConfig()->OnConnect(rSocket, bSucceed); //控制连接，全部连接后通知CenterServer
	if(!bSucceed)
		return;
	EHostType eSvrType = rSocket.GetPeerType();
	IConnectionHandler* pConnectionHandler = pNetMgr->GetConnectionHandler(eSvrType);
	if(pConnectionHandler != NULL)
		pConnectionHandler->OnEstablish(rSocket, false);
	else
		LOG_CRI << "Can't find Connection Handler! Peer Server: " << GetServerInfo(rSocket.GetPeerID());
}

bool CAcceptHandler::OnAccept(ISocket& rSocket)
{
	CNetMgr* pNetMgr = CNetMgr::GetNetMgr();
	if(pNetMgr == NULL)
		return false;
	EHostType ePeerType = rSocket.GetPeerType();
	IConnectionHandler* pHandler = pNetMgr->GetConnectionHandler(ePeerType);
	if(pHandler == NULL)
	{
		LOG_CRI << "Can't find Connection Handler for PeerType: " << GetServerName(ePeerType);
		return false;
	}
	return pHandler->OnEstablish(rSocket, true); //通知连接处理器 接收到了新的Iscoket
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

CNetMgr::~CNetMgr()
{
	for(auto it = _mapSvr2Handler.begin(); it != _mapSvr2Handler.end(); ++it)
		delete it->second;
	_mapSvr2Handler.clear();
	delete _pAcceptHandler;
	_pAcceptHandler = NULL;
	delete _pConnectHandler;
	_pConnectHandler = NULL;
}

bool CNetMgr::Init()
{
	CConfig* pConfig = CConfig::GetConfig();
	assert(pConfig != NULL);
	_eHostType = GetServerType(pConfig->GetServerID()); //本主机的服务器类型
	_pAcceptHandler = CreateAcceptHandler();
	if(_pAcceptHandler == NULL)
		return false;
	_pConnectHandler = CreateConnectHandler();
	if(_pConnectHandler == NULL)
		return false;
	map<EHostType, bool> mapSvrType; //确定谁连接了我，我连接了谁
	pConfig->GetAllServerTypes(mapSvrType);
	for(auto it = mapSvrType.begin(); it != mapSvrType.end(); ++it)
	{
		EHostType eSvrType = it->first;
		bool bAccept = it->second;
		if(_mapSvr2Handler.find(eSvrType) != _mapSvr2Handler.end())
			continue;
		CConnHandler* pConnHandler = NULL;
		if(eSvrType == eHostGate)
			pConnHandler = CreateGateHandler();
		else
			pConnHandler = CreateSvrHandler(eSvrType, bAccept);
		if(!pConnHandler->AllocBuf(SERVER_BUFFER_SIZE))
			return false;
		AddSvrHandler(eSvrType, *pConnHandler); // 主机类型<---->连接
	}
	CAuthHandler* pAuthHandler = CreateAuthHandler();
	if(pAuthHandler == NULL)
		return false;
	AddSvrHandler(eHostNone, *pAuthHandler);
	if(!InitNetMgr())
		return false;
	InitProtocol();
	NetInterface::SetUserLogicFunc(&UserLogicFunc);
	NetInterface::SetExceptionCallbackFunc(&ExceptionCallback);
	NetInterface::SetUserLogicExit(&UserLogicExit);
	NetInterface::SetPreShutdown(&PreShutdownFunc);
	if(!NetInterface::InitNetwork(pConfig->GetServerID(), CLIENT_BUFFER_SIZE, SERVER_BUFFER_SIZE*5,pConfig->_byIndex)) //启动监听，接收，发送进程（EPOLL）
		return false;
	return true;
}

void CNetMgr::FinishInit()
{
	NetInterface::OnLogicInitFinish();
}

void CNetMgr::Shutdown()
{
	for(auto it = _mapSvr2Handler.begin(); it != _mapSvr2Handler.end();)
	{
		auto pHandler = it->second;
		++it;
		pHandler->ForeachSocket([](ISocket& rSocket){ rSocket.Close(eSockShutdown); });
	}
	NetInterface::ShutdownNetwork();
}

bool CNetMgr::AddSvrHandler(EHostType eHostType, IConnectionHandler& rHandler)
{
	return _mapSvr2Handler.insert(make_pair(eHostType, &rHandler)).second;
}

bool CNetMgr::UserLogic()
{
	_oQueLock.Lock();
	std::list<std::function<bool()>> lst;
	lst.swap(_lstUserLogic);
	_oQueLock.UnLock();
	bool bBusy = false;
	for(auto it = lst.begin(); it != lst.end(); ++it)
	{
		if((*it)())
			bBusy = true;
	}
	if(OnUserLogic())
		bBusy = true;
	return bBusy;
}

void CNetMgr::OnClose( ISocket& rSocket )
{
    switch(rSocket.GetPeerType())
    {
    case eHostGate:
        OnGateClosed(rSocket);
        break;
    case eHostGame:
        OnGameClosed(rSocket);
        break;
    case eHostCenter:
        OnCenterClosed(rSocket);
        break;
    case eHostDB:
        OnDBClosed(rSocket);
        break;
    case eHostLog:
        OnLoggerClosed(rSocket);
        break;
    case eHostLogin:
        OnLoginClosed(rSocket);
        break;
    default:
        break;
    }
}

bool CNetMgr::UserLogicFunc()
{
	return GetNetMgr()->UserLogic();
}

void CNetMgr::UserLogicExit()
{
	GetNetMgr()->OnUserLogicExit();
}

void CNetMgr::PreShutdownFunc()
{
	GetNetMgr()->OnPreShutdown();
}

bool CNetMgr::ListenOnPort(UINT32 dwPort, UINT32 dwBackLog, bool bIsClient)
{
	if(!NetInterface::ListenOnPort(dwPort, bIsClient, dwBackLog, *_pAcceptHandler))
		return false;
	return true;
}

bool CNetMgr::Connect(const char* szAddr, UINT32 dwPort, UINT32 dwPeerID, EHostType ePeerType)
{
	if(!NetInterface::Connect(szAddr, dwPort, ePeerType, dwPeerID, *_pConnectHandler))
		return false;
	return true;
}

IConnectionHandler* CNetMgr::GetConnectionHandler(EHostType eHostType)
{
	auto it = _mapSvr2Handler.find(eHostType);
	if(it == _mapSvr2Handler.end())
		return NULL;
	return it->second;
}

CGateHandler* CNetMgr::GetGateHandler()
{
	IConnectionHandler* pConnectionHandler = GetConnectionHandler(eHostGate);
	CGateHandler* pGateHandler = dynamic_cast<CGateHandler*>(pConnectionHandler);
	assert(CConfig::GetConfig()->_bIsCrossServer || pGateHandler != NULL);
	return pGateHandler;
}

CSvrHandler* CNetMgr::GetSvrHandler(EHostType eHostType)
{
	IConnectionHandler* pConnectionHandler = GetConnectionHandler(eHostType);
	CSvrHandler* pSvrHandler = dynamic_cast<CSvrHandler*>(pConnectionHandler);
	assert(CConfig::GetConfig()->_bIsCrossServer || pSvrHandler != NULL);
	return pSvrHandler;
}

UINT8 CNetMgr::GetCurProtID() const
{
	if(_pCurConnHandler == NULL)
		return 0;
	return _pCurConnHandler->GetCurProt();
}

void CNetMgr::OnRecvFail(UINT64 qwUsrID, UINT8 byProtID, UINT8 byFuncID)
{
	LOG_CRI << "Receive exceptions occur! ProtID: " << byProtID << ", FuncID: " << byFuncID << ", UsrID: " << GetUserDesc(qwUsrID);
}

void CNetMgr::TimerCheck()
{
	for(auto it = _mapSvr2Handler.begin(); it != _mapSvr2Handler.end(); ++it)
	{
		IConnectionHandler* pConnectionHandler = it->second;
		if(pConnectionHandler->IsAccept())
			pConnectionHandler->TimerCheck();
	}
}

void CNetMgr::SetCurUsrID(UINT64 qwUsrID)
{
	_qwCurUsrID = qwUsrID;
}

UINT64 CNetMgr::GetCurUsrID()
{
	UINT64 qwUsrID = 0;
	if(_pCurConnHandler != NULL)
		qwUsrID = _pCurConnHandler->GetCurUsrID();
	if(qwUsrID == 0)
		qwUsrID = _qwCurUsrID;
	return qwUsrID;
}

#ifdef _WIN32
static void LogError(EExceptType eExceptType, UINT64 qwUsrID)
{
	LOG_CRI << "Exception Handling fails! eExceptType: " << eExceptType << ", dwUsrID: " << GetUserDesc(qwUsrID);
}
#endif

bool CNetMgr::ExceptionCallback(EExceptType eExceptType)
{
	bool bRet = false;
#ifdef _WIN32
	CNetMgr* pNetMgr = CNetMgr::GetNetMgr();
	__try
	{
		bRet = pNetMgr->OnException(eExceptType);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		LogError(eExceptType, pNetMgr->GetCurUsrID());
	}
#else
	bRet = CNetMgr::GetNetMgr()->OnException(eExceptType);
#endif
	return bRet;
}

CAcceptHandler* CNetMgr::CreateAcceptHandler()
{
	return new CAcceptHandler;
}

CConnectHandler* CNetMgr::CreateConnectHandler()
{
	return new CConnectHandler;
}

CGateHandler* CNetMgr::CreateGateHandler()
{
	return new CGateHandler(_oSessionMgr);
}

CSvrHandler* CNetMgr::CreateSvrHandler(EHostType ePeerType, bool bAccept)
{
	return new CSvrHandler(ePeerType, bAccept, _oSessionMgr);
}

CAuthHandler* CNetMgr::CreateAuthHandler()
{
	if(_pAcceptHandler == NULL)
		return NULL;
	return new CAuthHandler(*_pAcceptHandler, _oSessionMgr);
}

void CNetMgr::ExecUserLogic(std::function<bool()> func)
{
	_oQueLock.Lock();
	_lstUserLogic.push_back(func);
	_oQueLock.UnLock();
}
