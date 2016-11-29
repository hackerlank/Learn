/********************************************************************
// Server Network Library Source File.
// File name:  BaseSocket.cpp
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

#include "GlobalDefine.h"
#include "BaseSocket.h"
#include "ServerID.h"
#include "NetIFMgr.h"
#include "Linux.h"
#include "CallStack.h"
#include "Encode.h"

#define POLICY_REQ_STRING "<policy-file-request/>"
const size_t POLICY_REQ_LEN = sizeof(POLICY_REQ_STRING) - 1;

#define POLICY_STRING \
    "<?xml version=\"1.0\"?>" \
"<cross-domain-policy>" \
"<allow-access-from domain=\"*\" to-ports=\"*\" />" \
"</cross-domain-policy>"

#define HTTP_END "\r\n\r\n"

char* CBaseSocket::_pLogicBuf = NULL;
UINT32 CBaseSocket::_dwLogicBufSize = 0;

static map<ESockErr, const char*> mapErr2Desc;

const char* GetErrorDesc(ESockErr eSockErr)
{
    if(mapErr2Desc.empty())
    {
        mapErr2Desc.insert(make_pair(eSockConError, "Connection Error"));
        mapErr2Desc.insert(make_pair(eSockAccError, "Accept Error"));
        mapErr2Desc.insert(make_pair(eSockSendError, "Send Error"));
        mapErr2Desc.insert(make_pair(eSockRecvError, "Receive Error"));
        mapErr2Desc.insert(make_pair(eSockBufferError, "Buffer Error"));
        mapErr2Desc.insert(make_pair(eSockSendOverflow, "Send Buffer Overflow"));
        mapErr2Desc.insert(make_pair(eSockRecvOverflow, "Receive Buffer Overflow"));
        mapErr2Desc.insert(make_pair(eSockPacketError, "Packet Error"));
        mapErr2Desc.insert(make_pair(eSockNetError, "Network Error"));
        mapErr2Desc.insert(make_pair(eSockAppClose, "Application Close"));
        mapErr2Desc.insert(make_pair(eSockPeerClose, "Peer Close"));
        mapErr2Desc.insert(make_pair(eSockPolicy, "Policy Close"));
    }
    auto it = mapErr2Desc.find(eSockErr);
    if(it != mapErr2Desc.end())
        return it->second;
    return "Unknown Error";
}

    CBaseSocket::CBaseSocket(SOCKET sock)
    : _socket(sock)
    , _pHandler(NULL)
    , _dwSessionKey(0)
    , _eSockState(SOCK_STATE_NONE)
    , _dwDataToSend(0)
    , _dwDataRecved(0)
    , _wHostPort(0)
    , _wPeerPort(0)
      , _bInSave(false)
{
    _oHostAddr.s_addr = 0;
    _oPeerAddr.s_addr = 0;
    if(_socket == INVALID_SOCKET)
        _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(_socket == INVALID_SOCKET)
    {
        LOG_CRI << "Could not create socket: " << ERRDESC;
        SetError();
    }
}

CBaseSocket::~CBaseSocket()
{
    _oSendLoopBuffer.ReleaseBuffer();
    _oRecvLoopBuffer.ReleaseBuffer();
}

void CBaseSocket::Release()
{
    delete this;
}

bool CBaseSocket::MakeNonBlocking(SOCKET sock)
{
#ifdef _WIN32
    u_long mode = 1;
    if(ioctlsocket(sock, FIONBIO, &mode) == SOCKET_ERROR)
    {
        LOG_CRI<< "ioctlsocket fails: " << ERRDESC;
        return false;
    }
#else
    int flags = fcntl(sock, F_GETFL, 0);
    if(flags == -1)
    {
        LOG_CRI<< "get fcntl fails: " << ERRDESC;
        return false;
    }
    flags |= O_NONBLOCK;
    int s = fcntl(sock, F_SETFL, flags);
    if(s == -1)
    {
        LOG_CRI<< "set fcntl fails: " << ERRDESC;
        return false;
    }
#endif
    return true;
}

bool CBaseSocket::AssociateWithNetIF()
{
    return MakeNonBlocking(_socket);
}

bool CBaseSocket::SetConnecting()
{
    ESocketState expected = SOCK_STATE_NONE;
    ESocketState desired = SOCK_STATE_CONNECTING;
    return _eSockState.compare_exchange_strong(expected, desired);
}

bool CBaseSocket::SetAccepting()
{
    ESocketState expected = SOCK_STATE_NONE;
    ESocketState desired = SOCK_STATE_ACCEPTING;
    return _eSockState.compare_exchange_strong(expected, desired);
}

bool CBaseSocket::SetEstablished()
{
    ESocketState expected = SOCK_STATE_ACCEPTING;
    ESocketState desired = SOCK_STATE_ESTABLISH;
    if(_eSockState.compare_exchange_strong(expected, desired))
        return true;
    expected = SOCK_STATE_CONNECTING;
    if(_eSockState.compare_exchange_strong(expected, desired))
        return true;
    expected = SOCK_STATE_NONE;
    return _eSockState.compare_exchange_strong(expected, desired);
}

bool CBaseSocket::SetClose()
{
    ESocketState expected = SOCK_STATE_ESTABLISH;
    ESocketState desired = SOCK_STATE_CLOSE;
    return _eSockState.compare_exchange_strong(expected, desired);
}

bool CBaseSocket::SetError()
{
    _eSockState = SOCK_STATE_ERROR;
    return true;
}

bool CBaseSocket::AllocLogicBuf(UINT32 dwSize)
{
    if(dwSize == 0)
        return false;
    _pLogicBuf = (char*)malloc(dwSize);
    if(_pLogicBuf == NULL)
        return false;
    _dwLogicBufSize = dwSize;
    return true;
}

void CBaseSocket::ReleaseLogicBuf()
{
    if(_pLogicBuf)
        free(_pLogicBuf);
    _pLogicBuf = NULL;
    _dwLogicBufSize = 0;
}

bool CBaseSocket::AllocLoopBuf(UINT32 dwSize)
{
    if(dwSize == 0)
        return false;

    if(!_oSendLoopBuffer.AllocBuffer(dwSize))
        goto FAIL;
    if(!_oRecvLoopBuffer.AllocBuffer(dwSize))
        goto FAIL;
    return true;

FAIL:
    _oSendLoopBuffer.ReleaseBuffer();
    _oRecvLoopBuffer.ReleaseBuffer();
    return false;
}

void CBaseSocket::SendPolicyFile()
{
    if(!_oSendLoopBuffer.Write(POLICY_STRING, sizeof(POLICY_STRING)))
    {
        CloseEx(eSockSendOverflow);
#ifdef _DEBUG
        DebugBreak();
#endif
        return;
    }
    UINT32 dwOldLen = _dwDataToSend.fetch_add(sizeof(POLICY_STRING), memory_order_relaxed);
    if(dwOldLen == 0)
        ActiveSend();
    CloseEx(eSockPolicy); //发送完Flash策略文件后关闭连接
}

const char* CBaseSocket::GetHostAddrStr()
{
    return inet_ntoa(_oHostAddr);
}

ULONG CBaseSocket::GetHostAddrNum()
{
    return _oHostAddr.s_addr;
}

UINT16 CBaseSocket::GetHostPort()
{
    return _wHostPort;
}

void CBaseSocket::SetHostAddrPort(UINT32 dwAddr, UINT16 wPort)
{
    _oHostAddr.s_addr = dwAddr;
    _wHostPort = wPort;
}

const char* CBaseSocket::GetPeerAddrStr()
{
    return inet_ntoa(_oPeerAddr);
}

ULONG CBaseSocket::GetPeerAddrNum()
{
    return _oPeerAddr.s_addr;
}

UINT16 CBaseSocket::GetPeerPort()
{
    return _wPeerPort;
}

void CBaseSocket::SetPeerAddrPort(UINT32 dwAddr, UINT16 wPort)
{
    _oPeerAddr.s_addr = dwAddr;
    _wPeerPort = wPort;
}

bool CBaseSocket::Send(const char* pBuf, UINT32 dwLen,bool bCanSkip)
{
    if(_eSockState != SOCK_STATE_ESTABLISH)
        return false;
    if(pBuf == NULL || dwLen == 0)
        return false;
    UINT32 dwPacktLen = dwLen + sizeof(UINT32);
    //发送时要在数据前加上4个字节的包长度
    if(bCanSkip)
    {
        int dwFreeSize = _oSendLoopBuffer.GetFreeSize();
        if(dwPacktLen >= dwFreeSize)
        {
            LOG_CRI << "Now free size is " << dwFreeSize;
            LOG_CRI << "dwPacktLen is" << dwPacktLen;
            return false;
        }
    }

    if(!_oSendLoopBuffer.Write((char*)&dwLen, sizeof(UINT32)) || !_oSendLoopBuffer.Write(pBuf, dwLen))
    {
        LOG_CRI << "Send Buffer Overflow! Size: " << _oSendLoopBuffer.GetSize();
        CloseEx(eSockSendOverflow);
        SetError();
#ifdef _DEBUG
        //DebugBreak();
#endif
        return false;
    }
    UINT32 dwOldLen = _dwDataToSend.fetch_add(dwPacktLen, memory_order_relaxed);
    //为0表示当前没有活跃的发送操作，应激活发送
    if(dwOldLen == 0 && !ActiveSend())
    {
        LOG_CRI << "ActiveSend fails: " << ERRDESC;
        CloseEx(eSockNetError);
        SetError();
        return false;
    }
    return true;
}

INT32 CBaseSocket::ParsePacket()
{
    INT32 dwLen = _dwDataRecved;
    if(dwLen < static_cast<INT32>(sizeof(UINT32)))
    {
        LOG_CRI<<"dwLen < static_cast<INT32>(sizeof(UINT32))";
        return -1;
    }

    char arHead[4];
    if(!_oRecvLoopBuffer.Read(arHead, sizeof arHead, true))
    {
        LOG_CRI<<"_oRecvLoopBuffer.Read Error";
        return -2;
    }

    //为Flash的策略文件
    if(arHead[0] == '<' && arHead[1] == 'p' && arHead[2] == 'o' && arHead[3] == 'l')
    {
        if(dwLen < static_cast<INT32>(POLICY_REQ_LEN))
            return POLICY_REQ_LEN;
        string strData(POLICY_REQ_LEN, 0);
        _oRecvLoopBuffer.Read(&strData[0], (int)strData.size(), true);
        if(strData == POLICY_REQ_STRING)
            return -0xFF;
    }

    //为HTTP的GET请求，忽略
    if(arHead[0] == 'G' && arHead[1] == 'E' && arHead[2] == 'T' && arHead[3] == ' ')
    {
        string strData(dwLen, 0);
        _oRecvLoopBuffer.Read(&strData[0], (int)strData.size(), true);
        size_t pos = strData.find(HTTP_END);
        if(pos == string::npos)
            return dwLen + 1;
        INT32 dwPacketLen = INT32(pos + sizeof(HTTP_END) - 1);
        if(dwPacketLen > dwLen)
            return dwPacketLen;
        _oRecvLoopBuffer.ReadForward(dwPacketLen);
        _dwDataRecved -= dwPacketLen;
        return -0xFE;
    }

    INT32 dwPacketLen = *(UINT32*)arHead + sizeof(UINT32);
    if(dwPacketLen > _oRecvLoopBuffer.GetSize())
    {
        LOG_CRI << "dwPacketLen > _oRecvLoopBuffer.GetSize()";
        return -3;
    }

    if(dwPacketLen < (INT32)sizeof(UINT32))
    {
        LOG_CRI <<"dwPacketLen < (INT32)sizeof(UINT32)";
        return -4;
    }

    return dwPacketLen;
}

void CBaseSocket::NotifyRecv(int len)
{
    if(_eSockState != SOCK_STATE_ESTABLISH)
        return;

    if(_pConnHandler == NULL)
    {
        CloseEx(eSockAccError);
        SetError();
        return;
    }

    _dwDataRecved += len;
    while(_dwDataRecved > 0)
    {
        if(_dwDataRecved < sizeof(UINT32))
            break;
        INT32 dwPacketLen = ParsePacket();
        if(dwPacketLen == -0xFF)
        {
            SendPolicyFile(); //策略文件，在发送后关闭连接
            return;
        }
        if(dwPacketLen == -0xFE) //HTTP的GET请求，忽略
            continue;
        if(dwPacketLen < 0) //包错误
        {
            LOG_DBG << "Parse Packet error: " << dwPacketLen;
            CloseEx(eSockPacketError);
            SetError();
            return;
        }
        if(dwPacketLen > _oRecvLoopBuffer.GetSize()) //包长度超过接收缓冲区长度，断开连接
        {
            CloseEx(eSockRecvOverflow);
            SetError();
            return;
        }
        if((INT32)_dwDataRecved < dwPacketLen) //未收到一个完整的数据包
            break;
        if(_pConnHandler == NULL) //在协议处理时连接处理器有可能会改变，所以需要检查
            return;
        _pConnHandler->SetCurSock(this);
        char* pBuf = _oRecvLoopBuffer.PeekWithOutLoop(dwPacketLen); //能否在循环缓冲区中不绕回就能拿到一个完整的包
        if(pBuf == NULL)
        {
            if(dwPacketLen > (INT32)_dwLogicBufSize)
            {
                CloseEx(eSockRecvOverflow);
                SetError();
                return;
            }
            if(_oRecvLoopBuffer.Read(_pLogicBuf, dwPacketLen, true)) //不能的话，需要把包读到另一个缓冲区中
                pBuf = _pLogicBuf;
        }
        if(pBuf != NULL && *(int*)pBuf + (INT32)sizeof(UINT32) == dwPacketLen)
        {
            _pConnHandler->OnRecv(pBuf + sizeof(UINT32), dwPacketLen - sizeof(UINT32)); //通知逻辑上层，处理数据包
        }
        else
        {
            LOG_CRI << "Packet Error! len: " << dwPacketLen;
            CloseEx(eSockPacketError);
            SetError();
            return;
        }
        _oRecvLoopBuffer.ReadForward(dwPacketLen); //设置包已读取
        _dwDataRecved -= dwPacketLen;
    }
    if(_pConnHandler != NULL)
        _pConnHandler->SetCurSock(NULL);
}

void CBaseSocket::OnRecv(UINT32 dwRecv)
{
    _oRecvLoopBuffer.WriteForward(dwRecv); //设置dwRecv的数据已接收
    SNetEvent oEvt;
    oEvt.eType = eRecv;
    oEvt.recv.pSocket = this;
    oEvt.recv.len = dwRecv;
    CNetIFMgr::Instance().PushNetEvent(oEvt); //通知逻辑线程处理
}

void CBaseSocket::Close(ESockErr eSockErr)
{
    CloseEx(eSockErr);
}

void CBaseSocket::CloseEx(ESockErr eSockErr, UINT32 dwError, UINT32 dwExtError)
{
    if(SetClose())
    {
        SNetEvent oEvt;
        oEvt.eType = eError;
        oEvt.close.pSocket = this;
        oEvt.close.dwError = dwError;
        CNetIFMgr::Instance().PushNetEvent(oEvt);

        EHostType eSvrType = CNetIFMgr::Instance().GetServerType();
        bool bLogClose = true;
        switch(eSockErr)
        {
            case eSockPeerClose:
            case eSockPolicy:
            case eSockShutdown:
            case eSockOther:
                bLogClose = false;
                break;
            case eSockAppClose:
                if(eSvrType == eHostLogin || eSvrType == eHostGate)
                    bLogClose = false;
                break;
            default:
                break;
        }
        if(bLogClose)
            LOG_CRI << "Socket closed: " << GetErrorDesc(eSockErr) << ", Error: " << dwError << ", ExtError: " << dwExtError
                << ", Peer Type: " << GetServerName(_ePeerType) << ", Peer Index: " << GetServerIndex(_dwPeerID);
    }
}

void CBaseSocket::NotifyClose()
{
    if(_pConnHandler != NULL)
        _pConnHandler->OnClose(*this);
    CNetIFMgr::Instance().AddSockToDel(this);
}

bool CBaseSocket::CanClose()
{
    return _eSockState == SOCK_STATE_ERROR || (_eSockState == SOCK_STATE_CLOSE && _dwDataToSend == 0);
}

bool CBaseSocket::Connect(EHostType ePeerType, UINT32 dwPeerID, const char* pszAddr, UINT16 wPort, IConnectHandler& rHandler)
{
    if(!SetConnecting())
    {
        LOG_CRI << "Socket state invalid: " << _eSockState;
        return false;
    }

    if(!AssociateWithNetIF())
        return false;

    SIPAndPort stIpAndPort;
    stIpAndPort.strIP = pszAddr;
    stIpAndPort.wPort = wPort;
    CNetIFMgr::Instance().AddConnector(stIpAndPort, this);

    _ePeerType = ePeerType;
    _wPeerPort = wPort;
    _oPeerAddr.s_addr = inet_addr(pszAddr);
    SetSockHandler(&rHandler);
    SetPeerID(dwPeerID);

    sockaddr_in saLocal;
    memset(&saLocal, 0, sizeof saLocal);
    saLocal.sin_family = AF_INET;
    int rc = ::bind(_socket, (sockaddr*)&saLocal, sizeof saLocal);
    if(rc == -1)
    {
        LOG_DBG << "bind fails: " << ERRDESC;
        CNetIFMgr::Instance().AddSockToDel(this);
        return false;
    }

    if(!AsyncConnect())
    {
        LOG_DBG << "AsyncConnect fails!";
        CNetIFMgr::Instance().AddSockToDel(this);
        return false;
    }
    return true;
}

bool CBaseSocket::AsyncConnect()
{
    sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_addr = _oPeerAddr;
    sa.sin_port = htons(_wPeerPort);

    int rc = connect(_socket, (sockaddr*)&sa, sizeof sa);
    if(rc < 0)
    {
        if(errno == EINPROGRESS && ActiveSend())
            return true;
        LOG_CRI << "connect fails: " << ERRDESC;
        return false;
    }
    OnConnected(true);
    return true;
}

bool CBaseSocket::OnConnected(bool bIsConnected)
{
    bool bSucceed = false;
    UINT32 dwServerBufSize = CNetIFMgr::Instance().GetServerBufSize();
    if(bIsConnected && AllocLoopBuf(dwServerBufSize))
    {
        SetActType(eActConnect);
        SetEstablished();
        bSucceed = true;
        if(!ActiveRecv())
        {
            SetActType(eActNone);
            //force state to be connecting, so we can do cleaning up when closing the socket.
            _eSockState = SOCK_STATE_CONNECTING;
            bSucceed = false;
            LOG_CRI << "ActiveRecv failed!";
        }
    }
    SNetEvent oEvt;
    oEvt.eType = eConnect;
    oEvt.connect.pSocket = this;
    oEvt.connect.bSucceed = bSucceed;
    CNetIFMgr::Instance().PushNetEvent(oEvt);
    return true;
}

void CBaseSocket::NotifyConnect(bool bIsConnected)
{
    IConnectHandler* pHandler = (IConnectHandler*)GetSockHandler();
    CNetIFMgr::Instance().DelConnector(this);
    if(pHandler != NULL)
        pHandler->OnConnect(*this, bIsConnected);
    if(!bIsConnected)
        CNetIFMgr::Instance().AddSockToDel(this);
}

//Accepted socket function
bool CBaseSocket::OnAccepted()
{
    SetActType(eActAccept);
    SetEstablished();

    AssociateWithNetIF();

    LOG_DBG << "IOAccept";
    SNetEvent oEvt;
    oEvt.eType = eAccept;
    oEvt.accept.pSocket = this;
    CNetIFMgr::Instance().PushNetEvent(oEvt);
    if(!ActiveRecv())
    {
        LOG_CRI << "ActiveRecv fails: " << ERRDESC;
        return false;
    }
    return true;
}

void CBaseSocket::NotifyAccept()
{
    IAcceptHandler* pHandler = (IAcceptHandler*)GetSockHandler();
    if(pHandler == NULL || !pHandler->OnAccept(*this))
    {
        if(!SetClose())
        {
#ifdef _DEBUG
            DebugBreak();
#endif
            LOG_CRI << "SetClose fails!";
        }
        CNetIFMgr::Instance().AddSockToDel(this);
    }
}
