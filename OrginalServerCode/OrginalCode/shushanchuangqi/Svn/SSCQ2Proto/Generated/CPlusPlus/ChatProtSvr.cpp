/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    ChatProt.cpp
//  Purpose:      聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ChatProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NChatProt
{

CChatProtSvr::THandleFunc CChatProtSvr::_HandleFuncs[] =
{
	&CChatProtSvr::_DoRecv_Chat, //FuncID: 1
	&CChatProtSvr::_DoRecv_BubbleGet, //FuncID: 2
	&CChatProtSvr::_DoRecv_BubbleRespond, //FuncID: 3
	&CChatProtSvr::_DoRecv_InviteSuc, //FuncID: 4
};

bool CChatProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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
bool CChatProtSvr::Send_ChatInfoNotify(
	NGlobalChatProt::EChannelType eChannelType, //通道类型
	const NGlobalChatProt::SSenderInfo& rSenderInfo, //发送者信息
	const std::string& strInfo, //聊天信息
	const NGlobalChatProt::TVecShowInfo& vecShowInfo //炫耀物品信息
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
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 23, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CChatProtSvr::SendClt_ChatInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	NGlobalChatProt::EChannelType eChannelType, //通道类型
	const NGlobalChatProt::SSenderInfo& rSenderInfo, //发送者信息
	const std::string& strInfo, //聊天信息
	const NGlobalChatProt::TVecShowInfo& vecShowInfo //炫耀物品信息
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
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 23, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CChatProtSvr::BuildPkg_ChatInfoNotify(
	NGlobalChatProt::EChannelType eChannelType, //通道类型
	const NGlobalChatProt::SSenderInfo& rSenderInfo, //发送者信息
	const std::string& strInfo, //聊天信息
	const NGlobalChatProt::TVecShowInfo& vecShowInfo //炫耀物品信息
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
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 23, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：系统信息通知
bool CChatProtSvr::Send_SystemMsgNotify(
	NGlobalChatProt::EChannelType eChannelType, //通道类型
	const std::string& strInfo, //聊天信息
	NGlobalChatProt::EChannelSubType eSubType //额外信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eChannelType << strInfo << (UINT8&)eSubType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 23, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CChatProtSvr::SendClt_SystemMsgNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	NGlobalChatProt::EChannelType eChannelType, //通道类型
	const std::string& strInfo, //聊天信息
	NGlobalChatProt::EChannelSubType eSubType //额外信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eChannelType << strInfo << (UINT8&)eSubType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 23, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CChatProtSvr::BuildPkg_SystemMsgNotify(
	NGlobalChatProt::EChannelType eChannelType, //通道类型
	const std::string& strInfo, //聊天信息
	NGlobalChatProt::EChannelSubType eSubType //额外信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eChannelType << strInfo << (UINT8&)eSubType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 23, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：系统MsgID通知
bool CChatProtSvr::Send_SystemMsgIDNotify(
	UINT16 wMsgID //消息ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 23, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CChatProtSvr::SendClt_SystemMsgIDNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wMsgID //消息ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 23, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CChatProtSvr::BuildPkg_SystemMsgIDNotify(
	UINT16 wMsgID //消息ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 23, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：弹窗通知
bool CChatProtSvr::Send_ElasticFrameNotify(
	UINT16 wMsgID //消息ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 23, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CChatProtSvr::SendClt_ElasticFrameNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wMsgID //消息ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 23, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CChatProtSvr::BuildPkg_ElasticFrameNotify(
	UINT16 wMsgID //消息ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 23, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：系统MsgID通知
bool CChatProtSvr::Send_SystemFormatMsgIDNotify(
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr //聊天信息参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID << vecStr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 23, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CChatProtSvr::SendClt_SystemFormatMsgIDNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr //聊天信息参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID << vecStr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 23, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CChatProtSvr::BuildPkg_SystemFormatMsgIDNotify(
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr //聊天信息参数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID << vecStr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 23, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：气泡提示信息
bool CChatProtSvr::Send_BubbleNotify(
	const NRoleInfoDefine::TVecBubbleInfo& vecBubbleInfo //气泡列表信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecBubbleInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 23, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CChatProtSvr::SendClt_BubbleNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const NRoleInfoDefine::TVecBubbleInfo& vecBubbleInfo //气泡列表信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecBubbleInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 23, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CChatProtSvr::BuildPkg_BubbleNotify(
	const NRoleInfoDefine::TVecBubbleInfo& vecBubbleInfo //气泡列表信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecBubbleInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 23, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：气泡提示信息更新
bool CChatProtSvr::Send_BubbleUpdate(
	NProtoCommon::EDataChange eType, //更新类型，增加，删除，修改
	const NRoleInfoDefine::SBubbleInfo& sBubbleInfo //受影响的气泡信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eType << sBubbleInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 23, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CChatProtSvr::SendClt_BubbleUpdate(const UINT64* pUsrID_, UINT16 wCnt_,
	NProtoCommon::EDataChange eType, //更新类型，增加，删除，修改
	const NRoleInfoDefine::SBubbleInfo& sBubbleInfo //受影响的气泡信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eType << sBubbleInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 23, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CChatProtSvr::BuildPkg_BubbleUpdate(
	NProtoCommon::EDataChange eType, //更新类型，增加，删除，修改
	const NRoleInfoDefine::SBubbleInfo& sBubbleInfo //受影响的气泡信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eType << sBubbleInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 23, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：系统MsgID通知
bool CChatProtSvr::Send_SystemFormatMsgIDNotifyWithShow(
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr, //聊天信息参数
	const NGlobalChatProt::TVecShowInfo& vecShow //炫耀信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID << vecStr << vecShow;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 23, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CChatProtSvr::SendClt_SystemFormatMsgIDNotifyWithShow(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr, //聊天信息参数
	const NGlobalChatProt::TVecShowInfo& vecShow //炫耀信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID << vecStr << vecShow;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 23, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CChatProtSvr::BuildPkg_SystemFormatMsgIDNotifyWithShow(
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr, //聊天信息参数
	const NGlobalChatProt::TVecShowInfo& vecShow //炫耀信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID << vecStr << vecShow;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 23, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CChatProtSvr::_DoRecv_Chat(const char* pBuf_, UINT32 dwLen_)
{
	NGlobalChatProt::EChannelType eChannelType = (NGlobalChatProt::EChannelType)0;
	std::string strInfo;
	NGlobalChatProt::TVecShowInfo vecShowInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eChannelType >> strInfo >> vecShowInfo;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 23, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_Chat(eChannelType, strInfo, vecShowInfo);
	return true;
}

CChatProtSvr::SBubbleGetAck::SBubbleGetAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CChatProtSvr::SBubbleGetAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecBubbleInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 23, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CChatProtSvr::_DoRecv_BubbleGet(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 23, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBubbleGetAck> fnAck_(new SBubbleGetAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BubbleGet(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CChatProtSvr::SBubbleRespondAck::SBubbleRespondAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EBubbleResult)0) { }

void CChatProtSvr::SBubbleRespondAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 23, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CChatProtSvr::_DoRecv_BubbleRespond(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wIndex = 0;
	TVecINT64 vecParam;
	TVecString vecString;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wIndex >> vecParam >> vecString;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 23, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBubbleRespondAck> fnAck_(new SBubbleRespondAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BubbleRespond(wIndex, vecParam, vecString, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CChatProtSvr::_DoRecv_InviteSuc(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 23, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_InviteSuc(qwRoleID);
	return true;
}

} //namespace NChatProt
