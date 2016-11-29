/********************************************************************
//	Server Common Library Source File.
//	File name:	GateHandler.cpp
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

#include "GlobalDefine.h"
#include "GateHandler.h"
#include "ServerID.h"
#include "CallStack.h"
#include "NetMgr.h"
#include "UtilFunc.h"

#define LOG_CANNOT_FIND_GATE(dwSvrID) \
	static time_t tLastTime = 0; \
	time_t tNow = time(NULL); \
	if(tNow > tLastTime && tNow - tLastTime >= 10) \
	{ \
		LOG_CRI << "Can't find GateServer: " << dwSvrID << ", Index: " << GetServerIndex(dwSvrID); \
		tLastTime = tNow; \
		PRINT_CALL_STACK; \
	}

void CGateHandler::RegisterProtocol(IProtocol& rProtocol)
{
	CConnHandler::RegisterProtocol(rProtocol);
	if(!rProtocol.IsForClient())
		_setDirectProtID.insert(rProtocol.GetProtID());
}

void CGateHandler::OnUserLogin(UINT64 qwUsrID)
{
	ISocket* pSocket = GetCurSock();
	if(pSocket == NULL)
	{
		LOG_CRI << "GetCurSock fails! qwUsrID: " << GetUserDesc(qwUsrID);
		return;
	}
	_mapUsr2Gate[qwUsrID] = pSocket->GetPeerID();
}

void CGateHandler::OnUserLogin(UINT64 qwUsrID, UINT32 dwSvrID)
{
    if(qwUsrID == 0)
    {
        LOG_CRI << "Invalid UserID: " << GetUserDesc(qwUsrID);
        return;
    }
    _mapUsr2Gate[qwUsrID] = dwSvrID;
}

void CGateHandler::OnUserLogout(UINT64 qwUsrID)
{
	_mapUsr2Gate.erase(qwUsrID);
}

UINT32 CGateHandler::GetGateID(UINT64 qwUsrID)
{
	auto it = _mapUsr2Gate.find(qwUsrID);
	if(it != _mapUsr2Gate.end())
		return it->second;
	LOG_CRI << "GetGateID fails! qwUsrID: " << GetUserDesc(qwUsrID);
	return 0;
}

UINT64 CGateHandler::GetCurUsrID() const
{
	UINT8 byCurProt = GetCurProt();
	if(_mapID2Prot.find(byCurProt) == _mapID2Prot.end())
	{
		LOG_CRI << "Can't find Protocol: " << byCurProt;
		PRINT_CALL_STACK;
		return 0;
	}
	return _qwCurUsrID;
}

bool CGateHandler::Send(const char* pBuf, UINT32 dwLen)
{
	if(!CConnHandler::Send(pBuf, dwLen))
		return false;
	UINT32 dwGateID = 0;
	UINT8 byCurProt = *(UINT8*)pBuf;
	UINT64 qwCurUsrID = 0;
	bool bDirectProt = _setDirectProtID.find(byCurProt) != _setDirectProtID.end();
	if(bDirectProt)
	{
		dwGateID = GetCurSvrID();
	}
	else
	{
		qwCurUsrID = GetCurUsrID();
		if(qwCurUsrID == 0)
		{
			LOG_CRI << "qwCurUsrID == 0! byCurProt: " << byCurProt;
#ifdef _DEBUG
			DebugBreak();
#endif
			return false;
		}
		auto itUsr = _mapUsr2Gate.find(qwCurUsrID);
		if(itUsr == _mapUsr2Gate.end())
		{
			LOG_CRI << "Can't find qwCurUsrID: " << qwCurUsrID;
			return false;
		}
		dwGateID = itUsr->second;
	}
	auto itGate = _mapID2Svr.find(dwGateID);
	if(itGate == _mapID2Svr.end())
	{
		LOG_CANNOT_FIND_GATE(dwGateID);
		return false;
	}
	ISocket* pSocket = itGate->second.pSocket;
	UINT32 dwNewLen = sizeof(UINT16);
	if(bDirectProt)
	{
		*(UINT16*)_pSendBuf = 0;
	}
	else
	{
		*(UINT16*)_pSendBuf = 1;
		memcpy_s(_pSendBuf + dwNewLen, _dwBufSize - dwNewLen, &qwCurUsrID, sizeof qwCurUsrID);
		dwNewLen += sizeof qwCurUsrID;
	}
	memcpy_s(_pSendBuf + dwNewLen, _dwBufSize - dwNewLen, pBuf, dwLen);
	dwNewLen += dwLen;
	return pSocket->Send(_pSendBuf, dwNewLen);
}

bool CGateHandler::SendClt(const UINT64* pUsrID, UINT16 wUsrCnt, const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return true;
	bool bRet = true;
	typedef map<UINT32, vector<UINT64> > TMapGate2VecUsr;
	TMapGate2VecUsr mapGate2VecUsr;
	if(wUsrCnt != 0)
	{
		if(pUsrID == NULL)
		{
			for(auto itUsr = _mapUsr2Gate.begin(); itUsr != _mapUsr2Gate.end(); ++itUsr)
				mapGate2VecUsr[itUsr->second].push_back(itUsr->first);
		}
		else
		{
			for(UINT16 i = 0; i < wUsrCnt; ++i)
			{
				auto itUsr = _mapUsr2Gate.find(pUsrID[i]);
				if(itUsr != _mapUsr2Gate.end())
					mapGate2VecUsr[itUsr->second].push_back(itUsr->first);
			}
		}
		for(auto itGate = mapGate2VecUsr.begin(); itGate != mapGate2VecUsr.end(); ++itGate)
		{
			vector<UINT64>& rVecUsrID = itGate->second;
			if(rVecUsrID.empty())
			{
				LOG_CRI << "rVecUsrID is empty!";
			}
			else
			{
				UINT32 dwGateID = itGate->first;
				auto itID = _mapID2Svr.find(dwGateID);
				if(itID != _mapID2Svr.end())
				{
					ISocket* pSocket = itID->second.pSocket;
					*(UINT16*)_pSendBuf = (UINT16)rVecUsrID.size();
					UINT32 dwNewLen = sizeof(UINT16);
					UINT32 dwUsrLen = UINT16(rVecUsrID.size()) * sizeof rVecUsrID[0];
					memcpy_s(_pSendBuf + dwNewLen, _dwBufSize - dwNewLen, &rVecUsrID[0], dwUsrLen);
					dwNewLen += dwUsrLen;
					memcpy_s(_pSendBuf + dwNewLen, _dwBufSize - dwNewLen, pBuf, dwLen);
					dwNewLen += dwLen;
					if(!pSocket->Send(_pSendBuf, dwNewLen))
						bRet = false;
				}
				else
				{
					LOG_CANNOT_FIND_GATE(dwGateID);
				}
			}
		}
	}
	else if(pUsrID == NULL)
	{
		*(UINT16*)_pSendBuf = 0;
		UINT32 dwNewLen = sizeof(UINT16);
		memcpy_s(_pSendBuf + dwNewLen, _dwBufSize - dwNewLen, pBuf, dwLen);
		dwNewLen += dwLen;
		for(auto itID = _mapID2Svr.begin(); itID != _mapID2Svr.end(); ++itID)
		{
			ISocket* pSocket = itID->second.pSocket;
			if(!pSocket->Send(_pSendBuf, dwNewLen))
				bRet = false;
		}
	}
	else
	{
		LOG_CRI << "pUsrID != NULL and wUsrCnt == 0";
#ifdef _DEBUG
		DebugBreak();
#endif
	}
	
	return bRet;
}

bool CGateHandler::SendSvr(const UINT32* pSvrID, UINT8 bySvrCnt, const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return true;
	bool bRet = true;
	UINT32 dwNewLen = sizeof(UINT16);
	*(UINT16*)_pSendBuf = 0;
	memcpy_s(_pSendBuf + dwNewLen, _dwBufSize - dwNewLen, pBuf, dwLen);
	dwNewLen += dwLen;
	if(pSvrID == NULL)
	{
		if(bySvrCnt != 0)
		{
			LOG_CRI << "bySvrCnt != 0";
#ifdef _DEBUG
			DebugBreak();
#endif
			return false;
		}
		if(_mapID2Svr.empty())
			return false;
		for(auto it = _mapID2Svr.begin(); it != _mapID2Svr.end(); ++it)
		{
			ISocket* pSocket = it->second.pSocket;
			if(!pSocket->Send(_pSendBuf, dwNewLen))
				bRet = false;
		}
	}
	else
	{
		for(UINT8 i = 0; i < bySvrCnt; ++i)
		{
			UINT32 dwGateID = pSvrID[i];
			auto it = _mapID2Svr.find(dwGateID);
			if(it == _mapID2Svr.end())
			{
				LOG_CANNOT_FIND_GATE(dwGateID);
				return false;
			}
			ISocket* pSocket = it->second.pSocket;
			if(!pSocket->Send(_pSendBuf, dwNewLen))
				bRet = false;
		}
	}
	return bRet;
}

bool CGateHandler::SendGate(UINT32 dwSvrID, UINT64* pUsrID, UINT16 wUsrCnt, const char* pBuf, UINT32 dwLen)
{
	if(pUsrID == NULL || wUsrCnt == 0)
		return false;
	if(pBuf == NULL || dwLen == 0)
		return true;
	auto it = _mapID2Svr.find(dwSvrID);
	if(it == _mapID2Svr.end())
	{
		LOG_CANNOT_FIND_GATE(dwSvrID);
		return false;
	}
	ISocket* pSocket = it->second.pSocket;
	*(UINT16*)_pSendBuf = wUsrCnt;
	UINT32 dwNewLen = sizeof(UINT16);
	UINT32 dwUsrLen = wUsrCnt * sizeof *pUsrID;
	memcpy_s(_pSendBuf + dwNewLen, _dwBufSize - dwNewLen, pUsrID, dwUsrLen);
	dwNewLen += dwUsrLen;
	memcpy_s(_pSendBuf + dwNewLen, _dwBufSize - dwNewLen, pBuf, dwLen);
	dwNewLen += dwLen;
	return pSocket->Send(_pSendBuf, dwNewLen);
}

UINT32 CGateHandler::ParseHeader(const char* pBuf, UINT32 dwLen)
{
	if(dwLen < sizeof(UINT64) + sizeof(UINT8))
	{
		LOG_CRI << "Invalid header length: " << dwLen;
		return 0;
	}
	_qwCurUsrID = *(UINT64*)pBuf;
	_byCurProt = *(UINT8*)(pBuf + sizeof(UINT64));
	return sizeof(UINT64);
}

bool CGateHandler::HandleMessage(const char* pBuf, UINT32 dwLen)
{
	if(CConnHandler::HandleMessage(pBuf, dwLen))
		return true;
	UINT8 byProtID = 0;
	UINT8 byFuncID = 0;
	if(dwLen >= sizeof(UINT8) * 2)
	{
		byProtID = *(UINT8*)pBuf;
		byFuncID = *(UINT8*)(pBuf + sizeof(UINT8));
	}
	CNetMgr::GetNetMgr()->OnRecvFail(_qwCurUsrID, byProtID, byFuncID);
	return false;
}
