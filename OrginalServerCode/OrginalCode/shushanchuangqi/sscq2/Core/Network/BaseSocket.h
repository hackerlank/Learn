/********************************************************************
// Server Network Library Source File.
// File name:  BaseSocket.h
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
#pragma once
#include <string>
#include <atomic>
#include "Interface.h"
#include "LoopBuffer.h"
#include "ObjPool.h"
#include "Lock.h"
#include "Event.h"

using namespace std;

//IO事件
struct SIOEvent
{
	enum EIOType
	{
		eIONone,
		eIOAccept,
		eIORecv,
		eIOSend
	};

	const EIOType eIOType;
	const void* pData;

	SIOEvent(EIOType type_, void* ptr_) : eIOType(type_), pData(ptr_) { }
};

//Socket的基础类
class CBaseSocket : public ISocket
{
	friend class CNetIFMgr;
	friend class CEPollMgr;
	friend class CIOCPMgr;
public:
	CBaseSocket(SOCKET sock = INVALID_SOCKET);
	virtual ~CBaseSocket();

	virtual void Release();

	static bool AllocLogicBuf(UINT32 dwSize);
	static void ReleaseLogicBuf();

	bool AllocLoopBuf(UINT32 dwSize); //分配循环缓冲区

	CLoopBuffer& GetSendBuffer() { return _oSendLoopBuffer; }
	CLoopBuffer& GetRecvBuffer() { return _oRecvLoopBuffer; }

	void* GetSockHandler() { return _pHandler; }
	void SetSockHandler(void* pHandler) { _pHandler = pHandler; }
    
    //继承自父类
	const char* GetHostAddrStr();
	ULONG GetHostAddrNum();
	UINT16 GetHostPort();
	const char* GetPeerAddrStr();
	ULONG GetPeerAddrNum();
	UINT16 GetPeerPort();
    
	void SetHostAddrPort(UINT32 dwAddr, UINT16 wPort);
	void SetPeerAddrPort(UINT32 dwAddr, UINT16 wPort);

	virtual bool ActiveSend() = 0;	//激活发送事件
	bool Send(const char* pBuf, UINT32 dwLen,bool bCanSkip = false);

	virtual bool ActiveRecv() = 0;	//激活接收事件
	void OnRecv(UINT32 dwRecv);
	void NotifyRecv(int len); //通知逻辑线程Recv数据

	virtual bool Connect(EHostType ePeerType, UINT32 dwPeerID, const char* pszAddr, UINT16 wPort, IConnectHandler& rHandler);
	virtual bool AsyncConnect();
	virtual bool OnConnected(bool bIsConnected);
	void NotifyConnect(bool bIsConnected); //通知逻辑线程Connect结果

	//Accepted socket function
	virtual bool OnAccepted();
	void NotifyAccept(); //通知逻辑线程Accept结果

	virtual void Close(ESockErr eSockErr) override;
	void CloseEx(ESockErr eSockErr, UINT32 dwError = 0, UINT32 dwExtError = 0);
    
    //继承自父类,没有具体的实现(在AuthHandler授权以后 初始化)
	virtual UINT64 GetUserID() const override { assert(false); return 0; }
	virtual void SetUserID(UINT64 qwUsrID) override { assert(false); }
	virtual UINT32 GetSessionKey() const override { return _dwSessionKey; }
	virtual void SetSessionKey(UINT32 dwSessionKey) override { _dwSessionKey = dwSessionKey; }

	void NotifyClose(); //通知逻辑线程Socket关闭

	virtual bool CanClose();

	//Socket的状态
	enum ESocketState
	{
		SOCK_STATE_NONE,
		SOCK_STATE_CONNECTING,
		SOCK_STATE_ACCEPTING,
		SOCK_STATE_ESTABLISH,
		SOCK_STATE_CLOSE,
		SOCK_STATE_ERROR
	};

	bool SetConnecting();
	bool SetAccepting();
	bool SetEstablished();
	bool SetClose();
	bool SetError();
    bool IsSave() {return _bInSave;}
    void SetSave(bool bSave = true){_bInSave = bSave; }
	ESocketState GetSocketState() { return _eSockState; }

	static bool MakeNonBlocking(SOCKET sock);

protected:
	virtual bool AssociateWithNetIF();	//将Socket与网络层接口关联
	INT32 ParsePacket();	//解析协议包
	void SendPolicyFile();	//发送Flash策略文件

protected:
	SOCKET _socket;
    
	void* _pHandler;			//当前的Socket处理器，不同的Socket操作对应不同的处理器
	UINT32 _dwSessionKey;		//连接密码

	atomic<ESocketState> _eSockState;	//Socket状态

	CLoopBuffer _oSendLoopBuffer;	//发送循环缓冲区
	CLoopBuffer _oRecvLoopBuffer;	//接收循环缓冲区

	atomic<UINT32> _dwDataToSend;	//当前需要发送的数据长度
	UINT32 _dwDataRecved;			//当前接收到的数据长度

	in_addr _oHostAddr;				//主机地址
	UINT16 _wHostPort;				//主机端口

	in_addr _oPeerAddr;				//对方地址
	UINT16 _wPeerPort;				//对方端口

	static char* _pLogicBuf;		//逻辑线程在处理数据包时用到的缓冲区
	static UINT32 _dwLogicBufSize;	//在处理数据包时用到的缓冲区大小
    bool _bInSave;

};

//对应于客户端(前端)的Socket
template<typename T>
class CCltSocket : public T
{
public:
	DEF_NET_NEW_DELETE(CCltSocket);
	CCltSocket(SOCKET sock = INVALID_SOCKET) : T(sock), _qwUsrID(0) { }
	virtual bool IsCltSocket() const override { return true; }
	virtual UINT64 GetUserID() const override { return _qwUsrID; }
	virtual void SetUserID(UINT64 qwUsrID) override { _qwUsrID = qwUsrID; }
protected:
	UINT64 _qwUsrID;	//客户端帐号的ID
};
