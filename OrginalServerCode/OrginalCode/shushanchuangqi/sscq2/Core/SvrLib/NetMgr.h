/********************************************************************
//	Server Common Library Source File.
//	File name:	NetMgr.h
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

#pragma once
#include <list>
#include <functional>
#include "Lock.h"
#include "Config.h"
#include "SvrHandler.h"
#include "GateHandler.h"
#include "AuthHandler.h"

//Connect处理器基础类
class CConnectHandler : public IConnectHandler
{
public:
	virtual void OnConnect(ISocket& rSocket, bool bSucceed);
};

//Accept处理器基础类
class CAcceptHandler : public IAcceptHandler
{
public:
	virtual bool OnAccept(ISocket& rSocket);
};

using NetInterface::EExceptType;

//网络层管理器基础类
class CNetMgr
{
public:
	virtual ~CNetMgr();
	bool Init();
	void Shutdown();	//清理并关闭网络层
	void FinishInit();	//逻辑层初始化后通知网络层
	bool Connect(const char* szAddr, UINT32 dwPort, UINT32 dwPeerID, EHostType ePeerType);	//连接对方服务器
	bool ListenOnPort(UINT32 dwPort, UINT32 dwBackLog, bool bIsClient);		//在端口上监听
	bool UserLogic();	//执行逻辑层需要执行的函数(在协议和定时器处理之外的)

	CSessionMgr& GetSessionMgr() { return _oSessionMgr; }
	CAcceptHandler* GetAcceptHandler() { return _pAcceptHandler; }
	CConnectHandler* GetConnectHandler() { return _pConnectHandler; }
	IConnectionHandler* GetConnectionHandler(EHostType eHostType);
	CGateHandler* GetGateHandler();		//获取网关的连接处理器(只有在连接网关时才有效)
	CSvrHandler* GetSvrHandler(EHostType eHostType);	//获取某类型主机对应的连接处理器
	void SetCurConnHandler(CConnHandler* pCurConnHandler) { _pCurConnHandler = pCurConnHandler; }
	UINT8 GetCurProtID() const;

	void SetCurUsrID(UINT64 qwUsrID);
	EHostType GetHostType() const { return _eHostType; }

	virtual void OnRecvFail(UINT64 qwUsrID, UINT8 byProtID, UINT8 byFuncID);	//在处理客户端协议异常时的回调函数
	virtual void TimerCheck();
	virtual void OnClose(ISocket& rSocket);

	//func返回值为true表示继续执行用户逻辑(50秒内)，为false表示结束执行用户逻辑(继续执行协议和时钟处理)
	void ExecUserLogic(std::function<bool()> func);

	static CNetMgr* GetNetMgr() { return _pNetMgr; }

protected:
	CNetMgr() : _pAcceptHandler(NULL), _pConnectHandler(NULL), _pCurConnHandler(NULL), _qwCurUsrID(0) { _pNetMgr = this; }

	virtual bool InitNetMgr() { return true; }
	virtual void InitProtocol() { }
	virtual bool OnUserLogic() { return false; } //返回值为true表示继续执行用户逻辑(50秒内)，为false表示结束执行用户逻辑(继续执行协议和时钟处理)
	virtual bool OnException(EExceptType eExceptType) { return false; }
	virtual void OnPreShutdown() { }
	virtual void OnUserLogicExit() { }

	static bool UserLogicFunc();
	static bool ExceptionCallback(EExceptType eExceptType);
	static void UserLogicExit();
	static void PreShutdownFunc();

	bool AddSvrHandler(EHostType eHostType, IConnectionHandler& rHandler);
	UINT64 GetCurUsrID();
// 上古移来的服务器异常断掉的虚函数
    virtual void OnGateClosed( ISocket& pSocket ) {}
    virtual void OnGameClosed( ISocket& pSocket ) {}
    virtual void OnCenterClosed( ISocket& pSocket ) {}
    virtual void OnDBClosed( ISocket& pSocket ) {}
    virtual void OnLoggerClosed( ISocket& pSocket ) {}
    virtual void OnLoginClosed( ISocket& pSocket ) {}
    
	virtual CAcceptHandler* CreateAcceptHandler();
	virtual CConnectHandler* CreateConnectHandler();
	virtual CGateHandler* CreateGateHandler();
	virtual CSvrHandler* CreateSvrHandler(EHostType ePeerType, bool bAccept);
	virtual CAuthHandler* CreateAuthHandler();

	CAcceptHandler* _pAcceptHandler;	//Accept处理器
	CConnectHandler* _pConnectHandler;	//Connect处理器
	CConnHandler* _pCurConnHandler;		//Socket连接的处理器
	CSessionMgr _oSessionMgr;	//会话管理器

	EHostType _eHostType;	//本服务器的主机类型

	map<EHostType, IConnectionHandler*> _mapSvr2Handler;	//主机类型到Socket连接处理器的映射

	CSpinLock _oQueLock;
	std::list<std::function<bool()>> _lstUserLogic;		//待执行用户逻辑函数列表

	UINT64 _qwCurUsrID;

	static CNetMgr* _pNetMgr;
};
