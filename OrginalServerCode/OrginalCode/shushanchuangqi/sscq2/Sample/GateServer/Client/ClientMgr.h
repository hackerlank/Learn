/********************************************************************
//	Gate Server Source File.
//	File name:	ClientMgr.h
//	Created:	2011/06/03	10:00
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
#include "ServerCommon.h"

using namespace NServerCommon;

class ISocket;
class CClientObj;

class CClientMgr : public IConnectionHandler
{
public:
	CClientMgr() : _pCurClient(NULL), _bHasAddition(false), _bPeekPass(false) { }
	~CClientMgr();

	UINT32 GetAuthedClientCount();
	bool NotifyUserLogin(UINT64 qwUsrID, UINT32 dwSessionKey);

	CClientObjPtr GetNewClient(UINT64 qwUsrID);
	CClientObjPtr GetAuthedClient(UINT64 qwUsrID);

	bool RemoveClient(UINT64 qwUsrID, ELeaveType eLeaveType);
	bool KickClientOffLine(UINT64 qwUsrID, ELeaveType eLeaveType);

	CClientObjPtr GetCurClient() { return _pCurClient; }
	void SetCurClient(CClientObjPtr pClientObj) { _pCurClient = pClientObj; }

	string& GetAddition() { return _strAddition; }
	void SetHasAddition(bool bHasAddition) { _bHasAddition = bHasAddition; }

	void RegisterPeekProtC2S(IProtocol& rProtocol);
	void RegisterPeekProtS2C(IProtocol& rProtocol);

	bool PeekProtC2S(const char* pBuf, UINT32 dwLen);
	bool PeekProtS2C(const char* pBuf, UINT32 dwLen);

	void SetPeekPass(bool bPeekPass) { _bPeekPass = bPeekPass; }

	virtual bool IsAccept() const override { return true; }
	virtual void TimerCheck() override;
	virtual ISocket* GetSocket(UINT32 dwSvrID) override { return NULL; }
	virtual EHostType GetPeerType() const override { return eHostClient; }
	virtual void ForeachSocket(std::function<void(ISocket&)> func) override { }
	virtual void RegisterProtocol(IProtocol& rProtocol) override { }
	virtual bool OnEstablish(ISocket& rSocket, bool bAccept) override;
	virtual bool OnRecv(const char* pBuf, UINT32 dwLen) override;
	virtual void OnClose(ISocket& rSocket) override;
	virtual bool Send(const char* pBuf, UINT32 dwLen) override { return false; }
	virtual bool SendClt(const UINT64* pUsrID, UINT16 wUsrCnt, const char* pBuf, UINT32 dwLen) override;
	virtual bool SendSvr(const UINT32* pSvrID, UINT8 bySvrCnt, const char* pBuf, UINT32 dwLen) override { return false; }

	virtual UINT64 GetCurUsrID() const override;
	virtual UINT32 GetCurSvrID() const override { return 0; }
    void KickAllClient(ELeaveType eLeaveType);

protected:
	void OnAuthed(UINT64 qwUsrID, const CClientObjPtr& pClientObj);

private:
	map<ISocket*, CClientObjPtr> _mapSock2Client;
	map<UINT64, CClientObjPtr> _mapID2NewClient;
	map<UINT64, CClientObjPtr> _mapID2AuthedClient;

	map<UINT8, IProtocol*> _mapID2ProtC2S;
	map<UINT8, IProtocol*> _mapID2ProtS2C;

	CClientObjPtr _pCurClient;
	string _strAddition;
	bool _bHasAddition;
	bool _bPeekPass;
};
