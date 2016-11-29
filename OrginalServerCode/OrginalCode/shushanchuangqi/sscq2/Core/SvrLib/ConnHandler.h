/********************************************************************
//	Server Common Library Source File.
//	File name:	ConnHandler.h
//	Created:	2012/08/21	11:00
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
#include <map>
#include "Interface.h"
#include "SessionMgr.h"
#include "CallStack.h"

using namespace std;

#define LOG_CANNOT_FIND_SEVER(dwSvrID) \
static time_t tLastTime = 0; \
time_t tNow = time(NULL); \
if(tNow > tLastTime && tNow - tLastTime >= 10) \
{ \
	LOG_CRI << "Can't find " << GetServerName(GetServerType(dwSvrID)) << "! dwSvrID: " << dwSvrID << ", Index: " << GetServerIndex(dwSvrID); \
	tLastTime = tNow; \
	PRINT_CALL_STACK; \
}

//对方的信息
struct SPeerInfo
{
	ISocket* pSocket;
	UINT32 dwStaleCount;

	SPeerInfo(ISocket* pSocket_ = NULL, UINT32 dwStaleCount_ = 0) : pSocket(pSocket_), dwStaleCount(dwStaleCount_) { }
};

//连接处理器基础类
class CConnHandler : public IConnectionHandler
{
public:
	CConnHandler(CSessionMgr& rSessionMgr, bool bAccept) : _pSendBuf(NULL),	_dwBufSize(0),
		_rSessionMgr(rSessionMgr), _bAccept(bAccept), _byCurProt(0), _byCurFunc(0), _bySendProt(0), _bySendFunc(0) { }
	virtual ~CConnHandler();
	bool AllocBuf(UINT32 dwBufSize);	//分配发送缓冲区
	const map<UINT32, SPeerInfo>& GetServerMap() const { return _mapID2Svr; }
	bool HasConnection() const { return !_mapID2Svr.empty(); }	//对方是否有连接
	bool HasConnection(UINT8 byIndex) const;	//对方的某个编号的服务器是否有连接
	virtual bool OnEstablish(ISocket& rSocket, bool bAccept) override;	//连接建立时的处理函数
	virtual bool IsAccept() const override { return _bAccept; }
	virtual void OnClose(ISocket& rSocket);		//Socket关闭时的处理函数
	virtual ISocket* GetSocket(UINT32 dwSvrID);		//根据对方的服务器ID获得Socket
	virtual void ForeachSocket(std::function<void(ISocket&)> func) override;
	virtual void RegisterProtocol(IProtocol& rProtocol) override;	//在此类连接上注册协议
	void OnKeepAlive(UINT32 dwSvrID);	//保活检查
	virtual bool OnRecv(const char* pBuf, UINT32 dwLen) override;	//接收到数据时的处理函数
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen);

	virtual bool Send(const char* pBuf, UINT32 dwLen) override;
	virtual bool SendClt(const UINT64* pUsrID, UINT16 wUsrCnt, const char* pBuf, UINT32 dwLen) override { return false; }
	virtual bool SendSvr(const UINT32* pSvrID, UINT8 bySvrCnt, const char* pBuf, UINT32 dwLen) override { return false; }
	virtual bool SendGate(UINT32 dwSvrID, UINT64* pUsrID, UINT16 wUsrCnt, const char* pBuf, UINT32 dwLen) { return false; }

	virtual bool ProxySend(const char* pBuf, UINT32 dwLen) { return false; }	//协议数据包转发
	virtual bool ProxySend(UINT32 dwSvrID, const char* pBuf, UINT32 dwLen) { return false; }	//协议数据包转发到指定的服务器

	virtual UINT64 GetCurUsrID() const override { return 0; }
	virtual UINT32 GetCurSvrID() const override; //服务器有编号，客户端没有编号

	virtual UINT32 GetStaleCount() const;
	void TimerCheck();

	UINT8 GetCurProt() const { return _byCurProt; }
	void SetCurProt(UINT8 byCurProt) { _byCurProt = byCurProt; }

	UINT8 GetSendProt() const { return _bySendProt; }
	void SetSendProt(UINT8 bySendProt) { _bySendProt = bySendProt; }

protected:
	virtual UINT32 ParseHeader(const char* pBuf, UINT32 dwLen) { return 0; }	//解析协议头部，返回协议长度

	char* _pSendBuf;	//发送缓冲区
	UINT32 _dwBufSize;	//发送缓冲区大小
	map<UINT32, SPeerInfo> _mapID2Svr;	//所有对方的信息(对方都是同类型的主机)
	map<UINT8, IProtocol*> _mapID2Prot;	//在该连接上注册的所有协议
	CSessionMgr& _rSessionMgr;	//会话管理器
	bool _bAccept;	//该类连接是否为Accept到的
	UINT8 _byCurProt;	//当前处理的协议ID
	UINT8 _byCurFunc;	//当前处理的函数ID
	UINT8 _bySendProt;	//当前发送的协议ID
	UINT8 _bySendFunc;	//当前发送的函数ID
};
