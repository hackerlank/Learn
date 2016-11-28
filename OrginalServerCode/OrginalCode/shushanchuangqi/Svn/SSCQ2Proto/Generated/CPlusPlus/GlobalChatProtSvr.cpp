/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    GlobalChatProt.cpp
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GlobalChatProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGlobalChatProt
{

CGlobalChatProtSvr::THandleFunc CGlobalChatProtSvr::_HandleFuncs[] =
{
	&CGlobalChatProtSvr::_DoRecv_Chat, //FuncID: 1
	&CGlobalChatProtSvr::_DoRecv_Whisper, //FuncID: 2
	&CGlobalChatProtSvr::_DoRecv_GetShowInfo, //FuncID: 3
	&CGlobalChatProtSvr::_DoRecv_ReqWhisperInfo, //FuncID: 4
};

bool CGlobalChatProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return false;
	INT8 byFuncID = pBuf[0];
	if(byFuncID == 0 || byFuncID > (INT8)ARRAYSIZE(_HandleFuncs))
	{
#ifdef _DEBUG
		LOG_CRI << "byFuncID is invalid: " << byFuncID;
#endif
		return false;
	}
	pBuf += sizeof(INT8);
	dwLen -= sizeof(INT8);
	if(byFuncID > 0)
	{
		--byFuncID;
		if(_HandleFuncs[static_cast<UINT8>(byFuncID)] != NULL)
			return (this->*_HandleFuncs[static_cast<UINT8>(byFuncID)])(pBuf, dwLen);
	}
	return true;
}

//发送：聊天信息通知
bool CGlobalChatProtSvr::Send_ChatInfoNotify(
	EChannelType eChannelType, //通道类型
	const SSenderInfo& rSenderInfo, //发送者信息
	const std::string& strInfo, //聊天信息
	const TVecShowInfo& vecShowInfo //炫耀物品信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eChannelType << rSenderInfo << strInfo << vecShowInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 28, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGlobalChatProtSvr::SendClt_ChatInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	EChannelType eChannelType, //通道类型
	const SSenderInfo& rSenderInfo, //发送者信息
	const std::string& strInfo, //聊天信息
	const TVecShowInfo& vecShowInfo //炫耀物品信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eChannelType << rSenderInfo << strInfo << vecShowInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 28, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGlobalChatProtSvr::BuildPkg_ChatInfoNotify(
	EChannelType eChannelType, //通道类型
	const SSenderInfo& rSenderInfo, //发送者信息
	const std::string& strInfo, //聊天信息
	const TVecShowInfo& vecShowInfo //炫耀物品信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eChannelType << rSenderInfo << strInfo << vecShowInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 28, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：私聊错误通知
bool CGlobalChatProtSvr::Send_WhisperErrorNotify(
	EWhisperErrorType eErrType, //错误类型
	UINT64 qwUsrID //帐号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eErrType << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 28, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGlobalChatProtSvr::SendClt_WhisperErrorNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	EWhisperErrorType eErrType, //错误类型
	UINT64 qwUsrID //帐号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eErrType << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 28, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGlobalChatProtSvr::BuildPkg_WhisperErrorNotify(
	EWhisperErrorType eErrType, //错误类型
	UINT64 qwUsrID //帐号ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eErrType << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 28, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：私聊信息通知
bool CGlobalChatProtSvr::Send_WhisperInfoNotify(
	const SSenderInfo& rSenderInfo, //发送者信息
	const std::string& strInfo, //私聊信息
	const TVecShowInfo& vecShowInfo //炫耀物品信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << rSenderInfo << strInfo << vecShowInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 28, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGlobalChatProtSvr::SendClt_WhisperInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const SSenderInfo& rSenderInfo, //发送者信息
	const std::string& strInfo, //私聊信息
	const TVecShowInfo& vecShowInfo //炫耀物品信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << rSenderInfo << strInfo << vecShowInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 28, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGlobalChatProtSvr::BuildPkg_WhisperInfoNotify(
	const SSenderInfo& rSenderInfo, //发送者信息
	const std::string& strInfo, //私聊信息
	const TVecShowInfo& vecShowInfo //炫耀物品信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << rSenderInfo << strInfo << vecShowInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 28, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：系统信息通知
bool CGlobalChatProtSvr::Send_SystemMsgNotify(
	EChannelType eChannelType, //通道类型
	const std::string& strInfo, //聊天信息
	EChannelSubType eSubType //额外信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eChannelType << strInfo << (UINT8&)eSubType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 28, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGlobalChatProtSvr::SendClt_SystemMsgNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	EChannelType eChannelType, //通道类型
	const std::string& strInfo, //聊天信息
	EChannelSubType eSubType //额外信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eChannelType << strInfo << (UINT8&)eSubType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 28, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGlobalChatProtSvr::BuildPkg_SystemMsgNotify(
	EChannelType eChannelType, //通道类型
	const std::string& strInfo, //聊天信息
	EChannelSubType eSubType //额外信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eChannelType << strInfo << (UINT8&)eSubType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 28, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：系统MsgID通知
bool CGlobalChatProtSvr::Send_SystemMsgIDNotify(
	UINT16 wMsgID //消息ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 28, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGlobalChatProtSvr::SendClt_SystemMsgIDNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wMsgID //消息ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 28, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGlobalChatProtSvr::BuildPkg_SystemMsgIDNotify(
	UINT16 wMsgID //消息ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 28, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：系统MsgID通知
bool CGlobalChatProtSvr::Send_SystemFormatMsgIDNotify(
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr //聊天信息参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID << vecStr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 28, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGlobalChatProtSvr::SendClt_SystemFormatMsgIDNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr //聊天信息参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID << vecStr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 28, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGlobalChatProtSvr::BuildPkg_SystemFormatMsgIDNotify(
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr //聊天信息参数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID << vecStr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 28, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：系统弹窗和公告更新通知
bool CGlobalChatProtSvr::Send_SysDialogAndNoticeUpdateNotify(
	UINT8 byNotifyType //通知类型1:系统弹窗通知；2、公告更新通知
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << byNotifyType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 28, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGlobalChatProtSvr::SendClt_SysDialogAndNoticeUpdateNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byNotifyType //通知类型1:系统弹窗通知；2、公告更新通知
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << byNotifyType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 28, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGlobalChatProtSvr::BuildPkg_SysDialogAndNoticeUpdateNotify(
	UINT8 byNotifyType //通知类型1:系统弹窗通知；2、公告更新通知
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << byNotifyType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 28, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CGlobalChatProtSvr::_DoRecv_Chat(const char* pBuf_, UINT32 dwLen_)
{
	EChannelType eChannelType = (EChannelType)0;
	std::string strInfo;
	TVecShowInfo vecShowInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eChannelType >> strInfo >> vecShowInfo;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 28, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_Chat(eChannelType, strInfo, vecShowInfo);
	return true;
}

CGlobalChatProtSvr::SWhisperAck::SWhisperAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			wMsgID(0) { }

void CGlobalChatProtSvr::SWhisperAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << wMsgID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 28, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGlobalChatProtSvr::_DoRecv_Whisper(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	std::string strInfo;
	TVecShowInfo vecShowInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> strInfo >> vecShowInfo;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 28, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SWhisperAck> fnAck_(new SWhisperAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_Whisper(qwUsrID, strInfo, vecShowInfo, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGlobalChatProtSvr::SGetShowInfoAck::SGetShowInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CGlobalChatProtSvr::SGetShowInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << rSenderInfo << strShowInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 28, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGlobalChatProtSvr::_DoRecv_GetShowInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 28, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetShowInfoAck> fnAck_(new SGetShowInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetShowInfo(qwInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGlobalChatProtSvr::SReqWhisperInfoAck::SReqWhisperInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CGlobalChatProtSvr::SReqWhisperInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << whisperInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 28, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGlobalChatProtSvr::_DoRecv_ReqWhisperInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	std::string strReceiveName;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> strReceiveName;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 28, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SReqWhisperInfoAck> fnAck_(new SReqWhisperInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReqWhisperInfo(strReceiveName, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NGlobalChatProt
