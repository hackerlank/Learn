/********************************************************************
//  Server Network Library Source File.
//  File name:  Interface.h
//  Created:    2012/08/21  11:00
//  Organization:
//  Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//  Author:     Jingyuan Wang
//  E-Mail:     tyketom@hotmail.com
//  Http://
// ------------------------------------------------------------------
//  Purpose:
//  Version:    1.0
//  Histroy:
*********************************************************************/
#pragma once
#include <map>
#include <vector>
#include <string>
#include <functional>
#include "Platform.h"

//网络主机类型
enum EHostType
{
	eHostNone,
	eHostClient = 1,	//Client
	eHostGate,			//GateServer
	eHostLogin,			//LoginServer
	eHostCenter,		//CenterServer
	eHostGame,			//GameServer
	eHostDB,			//DBServer
	eHostLog,			//LogServer
	eHostControl,		//ControlClient(PHP客服后台)
};

//连接建立类型
enum EActType
{
	eActNone,
	eActAccept,		//Accept到的连接
	eActConnect		//主动Connect的连接
};

//Socket错误类型
enum ESockErr
{
	eSockAppClose,		//应用程序关闭
	eSockConError,		//Connect错误
	eSockAccError,		//Accept错误
	eSockSendError,		//Send错误
	eSockRecvError,		//Recv错误
	eSockBufferError,	//缓冲区错误
	eSockSendOverflow,	//发送缓冲溢出
	eSockRecvOverflow,	//接收缓冲溢出
	eSockPacketError,	//协议数据包错误
	eSockNetError,		//网络错误
	eSockPeerClose,		//对方关闭
	eSockPolicy,		//Flash策略文件发送后关闭
	eSockShutdown,		//关服时关闭
	eSockOther			//其它
};

class IProtocol;
class IAcceptHandler;
class IConnectHandler;
class CSessionMgr;
class IConnectionHandler;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//网络底层Socket抽象类
class ISocket
{
public:
	void SetConnectionHandler(IConnectionHandler* pConnHandler) { _pConnHandler = pConnHandler; }
	IConnectionHandler* GetConnnectionHandler() { return _pConnHandler; }
	UINT32 GetPeerID() const { return _dwPeerID; }
	void SetPeerID(UINT32 dwPeerID) { _dwPeerID = dwPeerID; }
	EHostType GetPeerType() { return _ePeerType; }
	void SetPeerType(EHostType ePeerType) { _ePeerType = ePeerType; }
	std::string GetPeerName() const;
	EActType GetActType() { return _eActType; }
	void SetActType(EActType eActType) { _eActType = eActType; }

	typedef char TArMac[6];
	const TArMac& GetPeerMac() const { return _arPeerMac; } //获取对方的网卡Mac地址

	virtual bool IsSvrSocket() const { return false; }	//对方是否为服务器
	virtual bool IsCltSocket() const { return false; }	//对方是否为客户端(前端)

	virtual const char* GetHostAddrStr() = 0;	//获取自己的地址(字符串)
	virtual ULONG GetHostAddrNum() = 0;			//获取自己的地址(数字)
	virtual UINT16 GetHostPort() = 0;			//获取自己的端口号
	virtual const char* GetPeerAddrStr() = 0;	//获取对方的地址(字符串)
	virtual ULONG GetPeerAddrNum() = 0;			//获取对方的地址(数字)
	virtual UINT16 GetPeerPort() = 0;			//获取对方的端口号
	virtual bool Send(const char* pBuf, UINT32 dwLen,bool bCanSkip = false) = 0;	//发送数据到对方
	virtual void Close(ESockErr eSockErr = eSockPeerClose) = 0;	//关闭Socket
	virtual void Release() = 0;		//释放Socket的内存

	virtual UINT64 GetUserID() const = 0;	//获取对方的UserID(只对客户端Socket有效)
	virtual void SetUserID(UINT64 qwUsrID) = 0;
	virtual UINT32 GetSessionKey() const = 0;	//获取对方在连接时发过来的连接密码
	virtual void SetSessionKey(UINT32 dwSessionKey) = 0;

	bool Send(const std::string& strPkg,bool bCanSkip = false) { return Send(strPkg.c_str(), (UINT32)strPkg.size()); }
protected:
	ISocket();
	virtual ~ISocket();

	IConnectionHandler* _pConnHandler;	//连接的处理器
	UINT32 _dwPeerID;					//对方的服务器ID
	EHostType _ePeerType;				//对方的主机类型
	EActType _eActType;					//连接建立类型
	TArMac _arPeerMac;					//对方的网卡Mac地址
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Connect处理器抽象类
class IConnectHandler
{
public:
	virtual ~IConnectHandler() { }
	virtual void OnConnect(ISocket& rSocket, bool bSucceed) = 0;	//Connect后的处理函数
};

//Accept处理器抽象类
class IAcceptHandler
{
public:
	virtual ~IAcceptHandler() { }
	virtual bool OnAccept(ISocket& rSocket) = 0;	//Accept后的处理函数
};

//Socket连接的处理器抽象类(管理对方是同类型主机的多个连接)
class IConnectionHandler
{
public:
	IConnectionHandler() : _pSocket(NULL) { }
	virtual ~IConnectionHandler() { }
	virtual bool IsAccept() const = 0;		//是Accpet到的还是Connect到的连接
	virtual void TimerCheck() = 0;		//定时检查连接情况
	virtual ISocket* GetSocket(UINT32 dwSvrID) = 0;		//根据对方的服务器ID获取Socket
	virtual EHostType GetPeerType() const = 0;	//获取对方的主机类型
	virtual void ForeachSocket(std::function<void(ISocket&)> func) = 0;
	virtual void RegisterProtocol(IProtocol& rProtocol) = 0;	//注册连接上的协议
	virtual bool OnEstablish(ISocket& rSocket, bool bAccept) = 0;	//连接建立时的回调
	virtual bool OnRecv(const char* pBuf, UINT32 dwLen) = 0;	//连接上接收数据时的回调
	virtual void OnClose(ISocket& rSocket) = 0;		//连接关闭时的回调

	virtual bool Send(const char* pBuf, UINT32 dwLen) = 0;	//发送给当前协议处理的对端
	virtual bool SendClt(const UINT64* pUsrID, UINT16 wUsrCnt, const char* pBuf, UINT32 dwLen) = 0;	//发送给多个客户端
	virtual bool SendSvr(const UINT32* pSvrID, UINT8 bySvrCnt, const char* pBuf, UINT32 dwLen) = 0;	//发送给多个服务器

	virtual UINT64 GetCurUsrID() const = 0;		//获取当前协议对应的客户端
	virtual UINT32 GetCurSvrID() const = 0;		//获取当前协议对应的服务器
	ISocket* GetCurSock() const { return _pSocket; }
	void SetCurSock(ISocket* pSocket) { _pSocket = pSocket; }
private:
	ISocket* _pSocket;	//当前连接的Socket
};

//协议类的抽象类
class IProtocol
{
public:
	IProtocol() : _pConnHandler(NULL), _pSessionMgr(NULL) { }
	virtual ~IProtocol() { }
	CSessionMgr* GetSessionMgr() const { return _pSessionMgr; }
	void SetSessionMgr(CSessionMgr* pSessionMgr) { _pSessionMgr = pSessionMgr; }
	IConnectionHandler* GetConnectionHandler() const { return _pConnHandler; }
	void SetConnectionHandler(IConnectionHandler* pConnHandler) { _pConnHandler = pConnHandler; }
	ISocket* GetCurSock() const;	//获取当前协议处理对应的Socket
	EHostType GetPeerType() const;	//获取对方的主机类型
	UINT32 GetCurSvrID();	//获取当前对方的服务器ID(只对服务器Socket有效)
	UINT64 GetCurUsrID();	//获取当前对方的UserID(只对客户端Socket有效)
	virtual UINT8 GetProtID() const = 0;	//协议的编号
	virtual bool IsForClient() const = 0;	//是否为客户端(前端)与服务器的协议
	virtual void OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID) = 0; //有返回的RPC超时后的回调接口
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) = 0;	//协议包处理接口
protected:
	IConnectionHandler* _pConnHandler;	//协议实例被注册到的连接处理器
	CSessionMgr* _pSessionMgr;	//会话管理器
};

//定时器抽象类
class ITimer
{
public:
	virtual ~ITimer() { }
	virtual void OnTimer() = 0;
	HANDLE GetHandle() const { return _hTimer; }
	void SetHandle(HANDLE hTimer) { _hTimer = hTimer; }
	ITimer() : _hTimer(NULL) { }
protected:
	HANDLE _hTimer;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//网络底层的接口
namespace NetInterface
{
	//异常类型
	enum EExceptType
	{
		eExceptNone,
		eExceptCrash,	//进程崩溃
		eExceptLoop,	//死循环
		eExceptBuffer,	//缓冲区溢出
		eExceptParam	//STL参数错误
	};
	
	//初始化网络
	bool InitNetwork(UINT32 dwSvrID, UINT32 dwClientBufSize, UINT32 dwServerBufSize,UINT8 byIndex);

	//关闭网络
	void ShutdownNetwork();

	//逻辑初始化完成(可以创建网络线程)回调函数
	void OnLogicInitFinish();

	//在指定的端口上监听，bIsClient表示对方是否为客户端，rAcceptHandler为Accept时的处理器
	bool ListenOnPort(UINT16 wPort, bool bIsClient, UINT32 dwBackLog, IAcceptHandler& rAcceptHandler);

	//连接对方的服务器，ePeerType为对方类型，dwPeerID为对方的ID，rConnectHandler为Connect时的处理器
	bool Connect(const char* pszAddr, UINT16 wPort, EHostType ePeerType, UINT32 dwPeerID, IConnectHandler& rConnectHandler);

	typedef bool (*FnUserLogic)();
	//设置逻辑层在协议处理函数和时钟处理函数外需要执行的函数
	void SetUserLogicFunc(FnUserLogic fnUserLogic);

	typedef bool (*FnExceptionCallback)(EExceptType eExceptType);
	//设置进程发生异常时的处理函数
	void SetExceptionCallbackFunc(FnExceptionCallback fnExceptionCallback);

	typedef void (*FnUserLogicExit)();
	//设置在进程关闭前需要运行的函数
	void SetPreShutdown(FnUserLogicExit fnPreShutdown);

	//设置在逻辑线程退出前需要运行的函数
	void SetUserLogicExit(FnUserLogicExit fnUserLogicExit);

	//开启定时器
	bool OpenTimer(ITimer& rTimer, UINT32 dwPeriod);

	//关闭定时器
	bool CloseTimer(ITimer& rTimer);

	//启动所有定时器
	bool StartTimer();

	//获取本机的所有IP地址
	bool GetLocalAddress(std::vector<std::string>& vecAddr);
}
