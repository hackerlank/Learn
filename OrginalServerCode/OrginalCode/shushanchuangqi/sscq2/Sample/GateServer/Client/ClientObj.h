/********************************************************************
//	Gate Server Source File.
//	File name:	ClientObj.h
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
#include "Archive.h"

enum EAuthState
{
	eAuthNone,
	eAuthKey,
	eAuthImage
};

class CClientObj
{
public:
	DEF_NEW_DELETE(CClientObj);
	CClientObj() : _pSocket(NULL), _qwUsrID(0), _dwGameSvrID(0), _dwSessionKeyFromClient(0),_dwSessionKeyFromCenter(0),
		_eAuthState(eAuthNone), _dwStaleCount(0), _dwFailCount(0),_dwLastRevAlive(0) { }

	UINT64 GetUsrID() const { return _qwUsrID; }
	void SetUsrID(UINT64 qwUsrID);

	UINT32 GetGameSvrID() const { return _dwGameSvrID; }
	void SetGameSvrID(UINT32 dwGameSvrID) { _dwGameSvrID = dwGameSvrID; }

	EAuthState GetAuthState() const { return _eAuthState; }
	void SetAuthState(EAuthState eAuthState) { _eAuthState = eAuthState; }

	UINT32 GetSessionKeyFromClient() const { return _dwSessionKeyFromClient; }
	void SetSessionKeyFromClient(UINT32 dwSessionKey) { _dwSessionKeyFromClient = dwSessionKey; }
    UINT32 GetSessionKeyFromCenter() const { return _dwSessionKeyFromCenter; }
	void SetSessionKeyFromCenter(UINT32 dwSessionKey) { _dwSessionKeyFromCenter = dwSessionKey; }

	void OnLeave(ELeaveType eLeaveType);

	ISocket* GetSocket() const { return _pSocket; }
	void SetSocket(ISocket* pSocket) { _pSocket = pSocket; }

	bool Send(const char* pBuf, UINT32 dwLen,bool bCanSkip = false);
	bool Send(const string& strPkg,bool bCanSkip = false);
	bool ProxySend(const char* pBuf, UINT32 dwLen, const string* pStrAddition = NULL);

	void OnKeepAlive();
	bool CheckOverTime();
private:
    bool SetCreateRoleIp(char* pDest,UINT32 dwAllDestLen, UINT32 &dwNewLen,const char *pSource,UINT32 dwSourceLen);

private:
	ISocket* _pSocket;
	UINT64 _qwUsrID;
	UINT32 _dwGameSvrID;
    UINT32 _dwSessionKeyFromClient;
	UINT32 _dwSessionKeyFromCenter;
	EAuthState _eAuthState;
	UINT32 _dwStaleCount;
	UINT32 _dwFailCount;
    UINT32 _dwLastRevAlive;
};
