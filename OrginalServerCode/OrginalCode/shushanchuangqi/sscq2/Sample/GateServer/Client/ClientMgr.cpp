/********************************************************************
//	Gate Server Source File.
//	File name:	ClientMgr.cpp
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

#include "stdafx.h"
#include "Protocols.h"

CClientMgr::~CClientMgr()
{
    for(auto it = _mapID2NewClient.begin(); it != _mapID2NewClient.end(); ++it)
    {
        CClientObjPtr pClientObj = it->second;
        ISocket* pSocket = pClientObj->GetSocket();
        if(pSocket != NULL)
            pSocket->Release();
    }
    for(auto it = _mapID2AuthedClient.begin(); it != _mapID2AuthedClient.end(); ++it)
    {
        CClientObjPtr pClientObj = it->second;
        ISocket* pSocket = pClientObj->GetSocket();
        if(pSocket != NULL)
            pSocket->Release();
    }
}

UINT32 CClientMgr::GetAuthedClientCount()
{
    return (UINT32)_mapID2AuthedClient.size();
}

bool CClientMgr::NotifyUserLogin(UINT64 qwUsrID, UINT32 dwSessionKey)
{
    CClientObjPtr pClientObj = GetNewClient(qwUsrID);
    if(pClientObj != NULL)
    {
        ISocket* pSocket = pClientObj->GetSocket();
        if(pClientObj->GetAuthState() != eAuthNone)
        {
            LOG_WRN << "UserID: " << GetUserDesc(qwUsrID) << " logged twice!";
            return false;
        }
        if(pSocket)//客户端已到达
        {
            if(pClientObj->GetSessionKeyFromClient() != dwSessionKey)
            {
                LOG_WRN << "User ID " << GetUserDesc(qwUsrID) << " logged with a wrong session key!";
                pSocket->Close();
                _mapID2NewClient.erase(qwUsrID);

            }
            else
            {
                OnAuthed(qwUsrID, pClientObj);
            }

        }
        else
        {
            pClientObj->SetSessionKeyFromCenter(dwSessionKey);
        }
        /*
           if(pClientObj->GetSessionKeyFromClient() != dwSessionKey)
           {
           LOG_WRN << "User ID " << GetUserDesc(qwUsrID) << " logged with a wrong session key!";
           if(pSocket != NULL)
           {
           pSocket->Close();
           return false;
           }
           else
           {
           pClientObj->SetSessionKeyFromCenter(dwSessionKey);
           return true;
           }
           }
           if(pSocket != NULL)
           OnAuthed(qwUsrID, pClientObj);
           */
    }
    else
    {
        pClientObj.reset(new CClientObj);
        if(pClientObj == NULL)
            return false;
        pClientObj->SetUsrID(qwUsrID);
        pClientObj->SetSessionKeyFromCenter(dwSessionKey);
        auto pairRet = _mapID2NewClient.insert(make_pair(qwUsrID, pClientObj));
        if(!pairRet.second)
        {
            LOG_CRI << "Client logged again! UsrID: " << GetUserDesc(qwUsrID);
            auto& rpClientObj = pairRet.first->second;
            ISocket* pSocket = rpClientObj->GetSocket();
            if(pSocket != NULL)
                pSocket->Close();
            rpClientObj = pClientObj;
        }
    }
    return true;
}

CClientObjPtr CClientMgr::GetNewClient(UINT64 qwUsrID)
{
    auto it = _mapID2NewClient.find(qwUsrID);
    if(it == _mapID2NewClient.end())
        return NULL;
    return it->second;
}

CClientObjPtr CClientMgr::GetAuthedClient(UINT64 qwUsrID)
{
    auto it = _mapID2AuthedClient.find(qwUsrID);
    if(it == _mapID2AuthedClient.end())
        return NULL;
    return it->second;
}

bool CClientMgr::RemoveClient(UINT64 qwUsrID, ELeaveType eLeaveType)
{
    CClientObjPtr pClientObj;
    auto it = _mapID2AuthedClient.find(qwUsrID);
    if(it != _mapID2AuthedClient.end())
    {
        pClientObj = it->second;
        _mapID2AuthedClient.erase(it);
    }
    else
    {
        it = _mapID2NewClient.find(qwUsrID);
        if(it != _mapID2NewClient.end())
        {
            pClientObj = it->second;
            _mapID2NewClient.erase(it);
        }
    }
    if(pClientObj != NULL)
    {
        pClientObj->OnLeave(eLeaveType);
        LOG_DBG << "Leave Type: " << GetDescription(eLeaveType) << ", UsrID: " << qwUsrID;
        ISocket* pSocket = pClientObj->GetSocket();
        if(pSocket != NULL)
        {
            pSocket->Close();
            return true;
        }
    }
    return false;
}

bool CClientMgr::KickClientOffLine(UINT64 qwUsrID, ELeaveType eLeaveType)
{
    LOG_DBG << "Kick offline, UserID: " << GetUserDesc(qwUsrID) << ", LeaveType: " << GetDescription(eLeaveType);
    if(eLeaveType == eLeaveReplace)
    {
        LOG_CRI << "Invalid LeaveType: " << GetDescription(eLeaveType);
        return false;
    }
    return RemoveClient(qwUsrID, eLeaveType);
}

bool CClientMgr::OnEstablish(ISocket& rSocket, bool bAccept)
{
    assert(bAccept);
    UINT32 dwSessionKey = rSocket.GetSessionKey();
    UINT64 qwUsrID = rSocket.GetUserID();
    if(qwUsrID == 0)
    {
        LOG_DBG << "dwUsrID is 0!";
        return false;
    }
    CClientObjPtr pClientObj = GetNewClient(qwUsrID);
    if(pClientObj != NULL)
    {
        if(pClientObj->GetAuthState() != eAuthNone)
        {
            LOG_WRN << "UserID: " << GetUserDesc(qwUsrID) << " logged twice!";
            return false;
        }
        pClientObj->SetSocket(&rSocket);
        UINT32 dwOldSessionKey = pClientObj->GetSessionKeyFromCenter();
        if(dwOldSessionKey == dwSessionKey)
        {
            OnAuthed(qwUsrID, pClientObj);
        }
        else
        {
            _mapID2NewClient.erase(qwUsrID);
            return false;
        }
    }
    else
    {
        pClientObj.reset(new CClientObj);
        if(pClientObj == NULL)
            return false;
        pClientObj->SetUsrID(qwUsrID);
        pClientObj->SetSessionKeyFromClient(dwSessionKey);
        pClientObj->SetSocket(&rSocket);
        if(!_mapID2NewClient.insert(make_pair(qwUsrID, pClientObj)).second)
        {
            LOG_CRI << "_mapID2NewClient insert fails!";
            _mapID2NewClient[qwUsrID] = pClientObj;
        }
    }
    rSocket.SetConnectionHandler(this);
    if(!_mapSock2Client.insert(make_pair(&rSocket, pClientObj)).second)
    {
        LOG_CRI << "_mapSock2Client insert fails!";
        _mapSock2Client[&rSocket] = pClientObj;
    }
    LOG_INF << "Connected from IP: " << rSocket.GetPeerAddrStr() << " PORT: " << rSocket.GetPeerPort() << " With Session: " << pClientObj->GetSessionKeyFromCenter() << " UsrID" << qwUsrID;
    return true;
}

void CClientMgr::OnAuthed(UINT64 qwUsrID, const CClientObjPtr& pClientObj)
{
    if(pClientObj == NULL)
    {
        LOG_CRI << "pClientObj is NULL! UserID: " << GetUserDesc(qwUsrID);
        return;
    }
    ISocket* pSocket = pClientObj->GetSocket();
    if(pSocket == NULL)
    {
        LOG_CRI << "pSocket is NULL! UserID: " << GetUserDesc(qwUsrID);
        return;
    }
    pClientObj->SetUsrID(qwUsrID);
    if(_mapID2NewClient.erase(qwUsrID) == 0)
        LOG_CRI << "_mapID2NewClient erase fails!";
    LOG_INF << "User " << qwUsrID <<"OnAuthed";
    auto& pOldClientObj = _mapID2AuthedClient[qwUsrID];
    if(pOldClientObj != NULL)
    {
        LOG_INF << "Client logged again! UserID: " << GetUserDesc(qwUsrID);
        ISocket* pOldSocket = pOldClientObj->GetSocket();
        if(pOldSocket != NULL)
            pOldSocket->Close();
    }
    pOldClientObj = pClientObj;
    g_Gate2CenterCommC.Send_UserLoginNtf(qwUsrID, pSocket->GetPeerAddrStr());
    pClientObj->SetAuthState(eAuthKey);
    if(!Config.OnAccept(*pSocket))
        LOG_DBG << "OnAccept fails! UsrID: " << GetUserDesc(qwUsrID);
}

bool CClientMgr::OnRecv(const char* pBuf, UINT32 dwLen)
{
    if(pBuf == NULL || dwLen == 0)
        return false;
    ISocket* pSocket = GetCurSock();
    if(pSocket == NULL)
        return false;
    if(!pSocket->IsCltSocket())
    {
        LOG_CRI << "Socket is not for Client! PeerType: " << pSocket->GetPeerName() << ", PeerID: " << pSocket->GetPeerID();
        return false;
    }
    if(pSocket->GetSessionKey() == 0)
    {
        LOG_CRI << "Socket has no session key! PeerType: " << pSocket->GetPeerName() << ", PeerID: " << pSocket->GetPeerID();
        return false;
    }
    XOR((char*)pBuf, dwLen, pSocket->GetSessionKey());
    auto it = _mapSock2Client.find(pSocket);
    if(it == _mapSock2Client.end())
        return false;
    auto& pClientObj = it->second;
    _pCurClient = pClientObj;

    if(!PeekProtC2S(pBuf, dwLen))
        return false;
    string* pStrAddition = NULL;
    if(_bHasAddition)
    {
        pStrAddition = &_strAddition;
        _bHasAddition = false;
    }
    return pClientObj->ProxySend(pBuf, dwLen, pStrAddition);
}

void CClientMgr::OnClose(ISocket& rSocket)
{
    UINT64 qwUsrID = rSocket.GetUserID();
    CClientObjPtr pClientObj;
    auto it = _mapSock2Client.find(&rSocket);
    if(it != _mapSock2Client.end())
    {
        pClientObj = it->second;
        _mapSock2Client.erase(it);
        if(qwUsrID != pClientObj->GetUsrID())
            LOG_CRI << "Invalid UserID for pClientObj: " << pClientObj->GetUsrID() << ", dwUsrID: " << GetUserDesc(qwUsrID);
        if(pClientObj->GetAuthState() == eAuthNone)
        {
            auto itID = _mapID2NewClient.find(qwUsrID);
            if(itID != _mapID2NewClient.end())
            {
                auto& pNewClientObj = itID->second;
                if(pClientObj == pNewClientObj)
                    _mapID2NewClient.erase(itID);
            }
        }
        else
        {
            auto itID = _mapID2AuthedClient.find(qwUsrID);
            if(itID != _mapID2AuthedClient.end())
            {
                auto& pNewClientObj = itID->second;
                if(pClientObj == pNewClientObj)
                {
                    _mapID2AuthedClient.erase(itID);
                    if(pClientObj != NULL)
                        pClientObj->OnLeave(eLeaveAway);
                }
            }
        }
    }
    rSocket.SetConnectionHandler(NULL);
    Config.OnClose(rSocket);
}

bool CClientMgr::SendClt(const UINT64* pUsrID, UINT16 wUsrCnt, const char* pBuf, UINT32 dwLen)
{
    if(pBuf == NULL || dwLen == 0)
        return false;
    _pCurClient = NULL;
    static char arBuf[0x100000];
    UINT32 dwNewLen = sizeof arBuf;
    if(!CompressPacket(pBuf, dwLen, arBuf, dwNewLen))
        return false;
    static string strBuf;
    char tbuf[2];
    strncpy(tbuf,pBuf,2);
    UINT8 byPRPOTID = tbuf[0];
    INT8 byFUNID = tbuf[1];
    bool bCanskip = false;
    if(byPRPOTID == 5 && byFUNID == 7)
    {
        bCanskip = true;
    }
    if(wUsrCnt == 0)
    {
        for(auto it = _mapID2AuthedClient.begin(); it != _mapID2AuthedClient.end(); ++it)
        {
            CClientObjPtr pClientObj = it->second;
            strBuf.assign(arBuf, dwNewLen);
            pClientObj->Send(strBuf,bCanskip);
        }
    }
    else if(wUsrCnt == 1)
    {
        CClientObjPtr pClientObj = GetAuthedClient(pUsrID[0]);
        if(pClientObj != NULL)
        {
            _pCurClient = pClientObj;
            PeekProtS2C(pBuf, dwLen);
            bool bSend = pClientObj->Send(arBuf, dwNewLen,bCanskip);
            if(!bSend)
            { 
                LOG_CRI << "SEND TO " << pUsrID[0] << "PROT ID:" << byPRPOTID << " FunID :" << byFUNID  <<": ERR"  ;
            }
        }
    }
    else
    {
        for(UINT16 i = 0; i < wUsrCnt; ++i)
        {
            CClientObjPtr pClientObj = GetAuthedClient(pUsrID[i]);
            if(pClientObj != NULL)
            {
                strBuf.assign(arBuf, dwNewLen);
                bool bSend = pClientObj->Send(strBuf,bCanskip);
                if(!bSend)
                { 
                    LOG_INF << "SEND TO " << pUsrID[i] << "PROT ID:" << byPRPOTID << " FunID :" << byFUNID  <<" : ERR"  ;
                }

            }
        }
    }
    //LOG_INF << "SEND TO " << "PROT ID:" << byPRPOTID << " FunID :" << byFUNID  <<": Suc"  ;
    return true;
}

UINT64 CClientMgr::GetCurUsrID() const
{
    if(_pCurClient != NULL)
        return _pCurClient->GetUsrID();
    return 0;
}

void CClientMgr::RegisterPeekProtC2S(IProtocol& rProtocol)
{
    _mapID2ProtC2S[rProtocol.GetProtID()] = &rProtocol;
}

void CClientMgr::RegisterPeekProtS2C(IProtocol& rProtocol)
{
    _mapID2ProtS2C[rProtocol.GetProtID()] = &rProtocol;
}

bool CClientMgr::PeekProtC2S(const char* pBuf, UINT32 dwLen)
{
    if(pBuf == NULL || dwLen == 0)
        return false;
    UINT8 byProtID = *(UINT8*)pBuf;
    auto it = _mapID2ProtC2S.find(byProtID);
    if(it == _mapID2ProtC2S.end())
        return true;
    _bPeekPass = true;
    IProtocol* pProtocol = it->second;
    pProtocol->HandleMessage(pBuf + sizeof(UINT8), dwLen - sizeof(UINT8));
    return _bPeekPass;
}

bool CClientMgr::PeekProtS2C(const char* pBuf, UINT32 dwLen)
{
    if(pBuf == NULL || dwLen == 0)
        return false;
    UINT8 byProtID = *(UINT8*)pBuf;
    auto it = _mapID2ProtS2C.find(byProtID);
    if(it == _mapID2ProtS2C.end())
        return true;
    IProtocol* pProtocol = it->second;
    return pProtocol->HandleMessage(pBuf + sizeof(UINT8), dwLen - sizeof(UINT8));
}

void CClientMgr::TimerCheck()
{
    for(auto it = _mapSock2Client.begin(); it != _mapSock2Client.end();)
    {
        CClientObjPtr pClientObj = it->second;
        if(pClientObj->CheckOverTime())
        {
            ELeaveType eLeaveType = eLeaveNone;
            if(pClientObj->GetAuthState() != eAuthNone)
                eLeaveType = eLeaveKick;
            RemoveClient(pClientObj->GetUsrID(), eLeaveType);
            LOG_INF << " RemoveClient for TimerOut";
            it = _mapSock2Client.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void CClientMgr::KickAllClient(ELeaveType eLeaveType)
{
    for (auto it = _mapID2AuthedClient.begin(); it != _mapID2AuthedClient.end(); it++)
    {
        CClientObjPtr pClientObj = it->second;

        if(pClientObj != NULL)
        {
            pClientObj->OnLeave(eLeaveType);
            ISocket* pSocket = pClientObj->GetSocket();
            if(pSocket != NULL)
            {
                pSocket->Close();
            }
        }
    }
    for (auto it = _mapID2NewClient.begin(); it !=_mapID2NewClient.end(); it++)
    {
        CClientObjPtr pClientObj = it->second;

        if(pClientObj != NULL)
        {
            pClientObj->OnLeave(eLeaveType);
            ISocket* pSocket = pClientObj->GetSocket();
            if(pSocket != NULL)
            {
                pSocket->Close();
            }
        }
    }

    _mapID2NewClient.clear();
    _mapID2AuthedClient.clear();
}

