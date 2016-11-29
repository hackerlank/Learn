/********************************************************************
//	Gate Server Source File.
//	File name:	ClientObj.cpp
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
#include "ClientMgr.h"
#include "RoleEnterGameProt.h"

void CClientObj::SetUsrID(UINT64 qwUsrID)
{
    _qwUsrID = qwUsrID;
    if(_pSocket != NULL)
        _pSocket->SetUserID(qwUsrID);
}

void CClientObj::OnLeave(ELeaveType eLeaveType)
{
    if(eLeaveType != eLeaveNone && eLeaveType != eLeaveReplace)
    {
        if(_dwGameSvrID != 0)
            g_Gate2GameCommC.SendSvr_UserLogoutNtf(&_dwGameSvrID, 1, _qwUsrID, eLeaveType);
        g_Gate2CenterCommC.Send_UserLogoutNtf(_qwUsrID, eLeaveType);
        g_Gate2DBCommC.Send_UserLogoutNtf(_qwUsrID, eLeaveType);
    }
    EBreakReason eBreakReason = eBreakNone;
    switch(eLeaveType)
    {
        case eLeaveReplace:
            eBreakReason = eBreakUsrKick;
            break;
        case eLeaveKick:
            eBreakReason = eBreakSvrKick;
            break;
        case eLeaveExcept:
            eBreakReason = eBreakExcept;
            break;
        case eIndulgeKick:
            eBreakReason = eBreakIndulgeKick;
            break;
        case eIndulgeTimeKick:
            eBreakReason = eBreakIndulgeTimeKick;
            break;
        default:
            //LOG_CRI << "Invalid LeaveType: " << eLeaveType;
            return;
    }
    string& strPkg = g_GameSvrBasicS.BuildPkg_ServerDisconnectNtf(eBreakReason);
    static char arBuf[0x100];
    UINT32 dwNewLen = sizeof arBuf;
    if(CompressPacket(strPkg.c_str(), (UINT32)strPkg.size(), arBuf, dwNewLen))
        Send(arBuf, dwNewLen);
    else
        LOG_CRI << "CompressPacket fails!";
}

bool CClientObj::Send(const char* pBuf, UINT32 dwLen,bool bCanSkip)
{
    if(pBuf == NULL || dwLen == 0)
        return false;
    if(_pSocket == NULL)
        return false;
    XOR((char*)pBuf, dwLen, _dwSessionKeyFromCenter);
    return _pSocket->Send(pBuf, dwLen,bCanSkip);
}

bool CClientObj::Send(const string& strPkg,bool bCanSkip)
{
    if(strPkg.empty())
        return false;
    return Send(strPkg.c_str(), (UINT32)strPkg.size(),bCanSkip);
}

bool CClientObj::ProxySend(const char* pBuf, UINT32 dwLen, const string* pStrAddition /*= NULL*/)
{
    if(pBuf == NULL || dwLen < sizeof(UINT8) * 2)
        return false;
    UINT8 byProtID = *(UINT8*)pBuf;
    UINT8 byFuncID = *((UINT8*)pBuf + 1);
    //LOG_INF << "CClientObj::ProxySend UserID: " <<_qwUsrID<< " byProtID:" << byProtID <<" byFuncID:"<< byFuncID;
    static char arSendBuf[0x1000];
    memset(arSendBuf, 0, sizeof arSendBuf);
    if(_qwUsrID == 0)
    {
        LOG_CRI << "dwUsrID is 0!";
        return false;
    }
    memcpy_s(arSendBuf, sizeof _qwUsrID, &_qwUsrID, sizeof _qwUsrID);
    UINT32 dwNewLen = sizeof _qwUsrID;
    EHostType eHostType = Config.GetProxyByProt(byProtID);
    if(eHostType == eHostDB && byProtID == 3 && byFuncID == 2)
    {
        //改创角包
        if(!SetCreateRoleIp((char*)arSendBuf,sizeof arSendBuf, dwNewLen,pBuf,dwLen))
        {
            memcpy_s(arSendBuf + dwNewLen, sizeof arSendBuf - dwNewLen, pBuf, dwLen);
            dwNewLen += dwLen;
        }
    }
    else
    {
        memcpy_s(arSendBuf + dwNewLen, sizeof arSendBuf - dwNewLen, pBuf, dwLen);
        dwNewLen += dwLen;
    }
    if(sizeof arSendBuf < dwNewLen)
    {
        LOG_CRI << "dwNewLen too long: " << dwNewLen;
        return false;
    }
    if(pStrAddition != NULL && !pStrAddition->empty())
    {
        if(pStrAddition->size() <= sizeof arSendBuf - dwNewLen)
        {
            memcpy_s(arSendBuf + dwNewLen, sizeof arSendBuf - dwNewLen, pStrAddition->c_str(), pStrAddition->size());
            dwNewLen += (UINT32)pStrAddition->size();
        }
        else
        {
            LOG_CRI << "Invalid pStrAddition size: " << pStrAddition->size();
        }
    }
    switch(eHostType)
    {
        case eHostGame:
            if(_dwGameSvrID == 0 && byProtID == 13 && byFuncID == 1)//尚未进入GameServer,不发心跳包到GameServer
            {   
                break;
            }
            if(!NetMgr.GetSvrHandler(eHostGame)->ProxySend(_dwGameSvrID, arSendBuf, dwNewLen))
                LOG_CRI << "ProxySend for GameServer fails! byProtID: " << byProtID << ", byFuncID: " << byFuncID << ", Index: " << GetServerIndex(_dwGameSvrID);
            break;
        case eHostCenter:
            if(!NetMgr.GetSvrHandler(eHostCenter)->ProxySend(arSendBuf, dwNewLen))
                LOG_CRI << "ProxySend for CenterServer fails! byProtID: " << byProtID << ", byFuncID: " << byFuncID;
            break;
        case eHostDB:
            if(!NetMgr.GetSvrHandler(eHostDB)->ProxySend(arSendBuf, dwNewLen))
                LOG_CRI << "ProxySend for DBServer fails! byProtID: " << byProtID << ", byFuncID: " << byFuncID;
            break;
        default:
            ++_dwFailCount;
            if(_dwFailCount > 10)
            {
                NetMgr.GetClientMgr().RemoveClient(_qwUsrID, eLeaveKick);
                LOG_INF << "Client ProtID is invalid for more than 10 times! UsrID: " << GetUserDesc(_qwUsrID);
            }
            LOG_DBG << "Invalid ProtID: " << byProtID;
            return false;
    }
    return true;
}

void CClientObj::OnKeepAlive()
{
    _dwStaleCount = 0;
    _dwLastRevAlive = time(NULL);

}

bool CClientObj::CheckOverTime()
{

    ++_dwStaleCount;
    if((_eAuthState == eAuthNone && _dwStaleCount >= 2) || (_dwStaleCount > KEEP_ALIVE_MAX_STALE_COUNT))
    {
        char _szbuf[0x100];
        tm tmNow;    
        time_t tCheckTimer(_dwLastRevAlive);
        localtime_s(&tmNow, &tCheckTimer);
        sprintf_s(_szbuf,"[%02u:%02u:%02u]",tmNow.tm_hour,tmNow.tm_min,tmNow.tm_sec);
        LOG_CRI << "Client Keep Alive Overtime! _dwStaleCount: " << _dwStaleCount << ", UsrID: " << GetUserDesc(_qwUsrID) << " Last Alive timer is " << _szbuf << "Check for " << int(_eAuthState);
        return true;
    }
    return false;
}

bool CClientObj::SetCreateRoleIp(char* pDest, UINT32 dwAllDestLen,UINT32 &dwNewLen,const char *pSource,UINT32 dwSourceLen)
{
    UINT8 byProtID;
    UINT8 byFuncID;
    //解包
    NRoleEnterGameProt::SCreateRoleInfo stCreateInfo;
    CInArchive oInArchive(pSource,dwSourceLen);
    try
    {
        oInArchive >> byProtID >> byFuncID >> stCreateInfo;
    }
    catch(const char* szExcept)
    {
#ifdef _DEBUG
        LOG_CRI << "SetCreateRoleIp: " << szExcept ;
#endif
        return false;
    }
    ISocket* pSocket = GetSocket();
    if(!pSocket)
    {
        return false;
    }
    stCreateInfo.strIP = pSocket->GetPeerAddrStr();
    //压包
    COutArchive oOutArchive;
    try
    {
        oOutArchive << byProtID << byFuncID << stCreateInfo;
    }
    catch(const char* szExcept) 
    {
#ifdef _DEBUG
        LOG_CRI << "SetCreateRoleIp: " << szExcept ;
#endif
        return false;
    }
    UINT32 dwLen_ = 0;
    char* pBuf_ = oOutArchive.GetBuf(dwLen_);
    memcpy_s(pDest + dwNewLen, dwAllDestLen - dwNewLen, pBuf_, dwLen_);
    dwNewLen += dwLen_;
    return true;
}
