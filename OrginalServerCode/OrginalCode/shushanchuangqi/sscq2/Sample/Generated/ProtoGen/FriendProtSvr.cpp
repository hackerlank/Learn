/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    FriendProt.cpp
//  Purpose:      好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "FriendProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NFriendProt
{

CFriendProtSvr::THandleFunc CFriendProtSvr::_HandleFuncs[] =
{
	&CFriendProtSvr::_DoRecv_AddFriendReq1, //FuncID: 1
	&CFriendProtSvr::_DoRecv_AddFriendReq2, //FuncID: 2
	&CFriendProtSvr::_DoRecv_AnswerAddFriend, //FuncID: 3
	&CFriendProtSvr::_DoRecv_RemoveFriendReq, //FuncID: 4
	&CFriendProtSvr::_DoRecv_MoveFriend, //FuncID: 5
	&CFriendProtSvr::_DoRecv_Whisper, //FuncID: 6
	&CFriendProtSvr::_DoRecv_FindUserIDNameReq, //FuncID: 7
	&CFriendProtSvr::_DoRecv_FindReferFriendReq, //FuncID: 8
	&CFriendProtSvr::_DoRecv_GetFriendInfo, //FuncID: 9
	&CFriendProtSvr::_DoRecv_SetSign, //FuncID: 10
	&CFriendProtSvr::_DoRecv_SetMood, //FuncID: 11
};

bool CFriendProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：询问增加好友
bool CFriendProtSvr::Send_AskAddFriend(
	const std::string& strRoleName, //角色名字
	UINT64 qwUserID, //帐号ID
	UINT16 wFighterID, //主将ID
	NProtoCommon::ESexType eSex, //性别
	UINT8 byLevel //等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << strRoleName << qwUserID << wFighterID << (UINT8&)eSex << byLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_AskAddFriend(const UINT64* pUsrID_, UINT16 wCnt_,
	const std::string& strRoleName, //角色名字
	UINT64 qwUserID, //帐号ID
	UINT16 wFighterID, //主将ID
	NProtoCommon::ESexType eSex, //性别
	UINT8 byLevel //等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << strRoleName << qwUserID << wFighterID << (UINT8&)eSex << byLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_AskAddFriend(
	const std::string& strRoleName, //角色名字
	UINT64 qwUserID, //帐号ID
	UINT16 wFighterID, //主将ID
	NProtoCommon::ESexType eSex, //性别
	UINT8 byLevel //等级
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << strRoleName << qwUserID << wFighterID << (UINT8&)eSex << byLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加好友/黑名单回应
bool CFriendProtSvr::Send_AddFriendAck(
	EFriendResult eResult, //增加好友的结果
	const std::string& strName, //名字 XXX: 如果主将改名需要修改此处
	NProtoCommon::ESexType eSex //性别
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult << strName << (UINT8&)eSex;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_AddFriendAck(const UINT64* pUsrID_, UINT16 wCnt_,
	EFriendResult eResult, //增加好友的结果
	const std::string& strName, //名字 XXX: 如果主将改名需要修改此处
	NProtoCommon::ESexType eSex //性别
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult << strName << (UINT8&)eSex;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_AddFriendAck(
	EFriendResult eResult, //增加好友的结果
	const std::string& strName, //名字 XXX: 如果主将改名需要修改此处
	NProtoCommon::ESexType eSex //性别
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult << strName << (UINT8&)eSex;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加好友/黑名单回应Ex
bool CFriendProtSvr::Send_AddFriendAckEx(
	const SFriendEntry& rFriendEntry //增加的好友
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << rFriendEntry;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_AddFriendAckEx(const UINT64* pUsrID_, UINT16 wCnt_,
	const SFriendEntry& rFriendEntry //增加的好友
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << rFriendEntry;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_AddFriendAckEx(
	const SFriendEntry& rFriendEntry //增加的好友
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << rFriendEntry;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：删除好友/黑名单回应
bool CFriendProtSvr::Send_RemoveFriendAck(
	EFriendResult eResult, //删除好友的结果
	UINT64 qwUserID //删除的好友帐号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_RemoveFriendAck(const UINT64* pUsrID_, UINT16 wCnt_,
	EFriendResult eResult, //删除好友的结果
	UINT64 qwUserID //删除的好友帐号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_RemoveFriendAck(
	EFriendResult eResult, //删除好友的结果
	UINT64 qwUserID //删除的好友帐号ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：私聊失败通知
bool CFriendProtSvr::Send_WhisperFailNotify(
	EFriendResult eResult //私聊通知的结果，成功不通知
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_WhisperFailNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	EFriendResult eResult //私聊通知的结果，成功不通知
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_WhisperFailNotify(
	EFriendResult eResult //私聊通知的结果，成功不通知
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：私聊成功通知
bool CFriendProtSvr::Send_WhisperSuccessNotify(
	UINT64 qwUserID, //帐号ID
	const std::string& strBaseInfo //聊天基本信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << strBaseInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_WhisperSuccessNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwUserID, //帐号ID
	const std::string& strBaseInfo //聊天基本信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << strBaseInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_WhisperSuccessNotify(
	UINT64 qwUserID, //帐号ID
	const std::string& strBaseInfo //聊天基本信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << strBaseInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：好友信息通知
bool CFriendProtSvr::Send_FriendInfoNotify(
	const SFriend& rFriend //好友信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << rFriend;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_FriendInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const SFriend& rFriend //好友信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << rFriend;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_FriendInfoNotify(
	const SFriend& rFriend //好友信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << rFriend;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：状态通知
bool CFriendProtSvr::Send_OnlineStatusNotify(
	UINT64 qwUserID, //帐号ID
	bool bOnlineStatus //在线状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << bOnlineStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_OnlineStatusNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwUserID, //帐号ID
	bool bOnlineStatus //在线状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << bOnlineStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_OnlineStatusNotify(
	UINT64 qwUserID, //帐号ID
	bool bOnlineStatus //在线状态
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << bOnlineStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：等级变化通知
bool CFriendProtSvr::Send_LevelChangeNotify(
	UINT64 qwUserID, //帐号ID
	UINT8 byLevel //当前等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_LevelChangeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwUserID, //帐号ID
	UINT8 byLevel //当前等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_LevelChangeNotify(
	UINT64 qwUserID, //帐号ID
	UINT8 byLevel //当前等级
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：VIP变化通知
bool CFriendProtSvr::Send_VIPChangeNotify(
	UINT64 qwUserID, //帐号ID
	UINT8 byLevel //当前等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_VIPChangeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwUserID, //帐号ID
	UINT8 byLevel //当前等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_VIPChangeNotify(
	UINT64 qwUserID, //帐号ID
	UINT8 byLevel //当前等级
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：品质变化通知
bool CFriendProtSvr::Send_ColorChangeNotify(
	UINT64 qwUserID, //帐号ID
	UINT8 byColor //当前品质
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byColor;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_ColorChangeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwUserID, //帐号ID
	UINT8 byColor //当前品质
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byColor;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_ColorChangeNotify(
	UINT64 qwUserID, //帐号ID
	UINT8 byColor //当前品质
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byColor;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 11";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：QQ黄钻好友通知
bool CFriendProtSvr::Send_YellowDiamondNotify(
	UINT64 qwUserID, //帐号ID
	UINT8 byLevel, //等级
	bool bYearlyPay //是否年费黄钻
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byLevel << bYearlyPay;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_YellowDiamondNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwUserID, //帐号ID
	UINT8 byLevel, //等级
	bool bYearlyPay //是否年费黄钻
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byLevel << bYearlyPay;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_YellowDiamondNotify(
	UINT64 qwUserID, //帐号ID
	UINT8 byLevel, //等级
	bool bYearlyPay //是否年费黄钻
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byLevel << bYearlyPay;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 12";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：签名改变通知
bool CFriendProtSvr::Send_SignChangeNotify(
	UINT64 qwUserID, //帐号ID
	const std::string& strSign //签名
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << strSign;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_SignChangeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwUserID, //帐号ID
	const std::string& strSign //签名
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << strSign;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_SignChangeNotify(
	UINT64 qwUserID, //帐号ID
	const std::string& strSign //签名
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << strSign;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 13";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：签名改变通知
bool CFriendProtSvr::Send_MoodChangeNotify(
	UINT64 qwUserID, //帐号ID
	UINT16 wMood //心情表情
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << wMood;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_MoodChangeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwUserID, //帐号ID
	UINT16 wMood //心情表情
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << wMood;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_MoodChangeNotify(
	UINT64 qwUserID, //帐号ID
	UINT16 wMood //心情表情
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << wMood;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 14";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：签名改变通知
bool CFriendProtSvr::Send_VIPLevelChangeNotify(
	UINT64 qwUserID, //帐号ID
	UINT8 byVIPLevel //VIP等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byVIPLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 15";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_VIPLevelChangeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwUserID, //帐号ID
	UINT8 byVIPLevel //VIP等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byVIPLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 15";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_VIPLevelChangeNotify(
	UINT64 qwUserID, //帐号ID
	UINT8 byVIPLevel //VIP等级
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byVIPLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 15";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：角色查询
bool CFriendProtSvr::Send_FindUserIDNameAck(
	EFriendResult eResult, //查询返回
	UINT64 qwUserID, //帐号ID
	const std::string& strRoleName, //主角色名
	UINT16 wHeroID, //主将ID
	UINT8 byLevel, //用户等级
	bool bOnlineStatus //在线状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult << qwUserID << strRoleName << wHeroID << byLevel << bOnlineStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 24, Function: 16";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFriendProtSvr::SendClt_FindUserIDNameAck(const UINT64* pUsrID_, UINT16 wCnt_,
	EFriendResult eResult, //查询返回
	UINT64 qwUserID, //帐号ID
	const std::string& strRoleName, //主角色名
	UINT16 wHeroID, //主将ID
	UINT8 byLevel, //用户等级
	bool bOnlineStatus //在线状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult << qwUserID << strRoleName << wHeroID << byLevel << bOnlineStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 24, Function: 16";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFriendProtSvr::BuildPkg_FindUserIDNameAck(
	EFriendResult eResult, //查询返回
	UINT64 qwUserID, //帐号ID
	const std::string& strRoleName, //主角色名
	UINT16 wHeroID, //主将ID
	UINT8 byLevel, //用户等级
	bool bOnlineStatus //在线状态
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult << qwUserID << strRoleName << wHeroID << byLevel << bOnlineStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 24, Function: 16";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CFriendProtSvr::_DoRecv_AddFriendReq1(const char* pBuf_, UINT32 dwLen_)
{
	EFriendGroupType eGroupType = (EFriendGroupType)0;
	TVecUINT64 vecUserID;
	UINT8 byNeedRet = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eGroupType >> vecUserID >> byNeedRet;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 24, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_AddFriendReq1(eGroupType, vecUserID, byNeedRet);
	return true;
}

bool CFriendProtSvr::_DoRecv_AddFriendReq2(const char* pBuf_, UINT32 dwLen_)
{
	EFriendGroupType eGroupType = (EFriendGroupType)0;
	std::string strName;
	UINT8 byNeedRet = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eGroupType >> strName >> byNeedRet;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 24, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_AddFriendReq2(eGroupType, strName, byNeedRet);
	return true;
}

bool CFriendProtSvr::_DoRecv_AnswerAddFriend(const char* pBuf_, UINT32 dwLen_)
{
	bool bAgree = false;
	UINT64 qwUserID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> bAgree >> qwUserID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 24, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_AnswerAddFriend(bAgree, qwUserID);
	return true;
}

bool CFriendProtSvr::_DoRecv_RemoveFriendReq(const char* pBuf_, UINT32 dwLen_)
{
	TVecUINT64 vecUserID;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecUserID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 24, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_RemoveFriendReq(vecUserID);
	return true;
}

CFriendProtSvr::SMoveFriendAck::SMoveFriendAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EFriendResult)0) { }

void CFriendProtSvr::SMoveFriendAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 24, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFriendProtSvr::_DoRecv_MoveFriend(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUserID = 0;
	EFriendGroupType eGroupType = (EFriendGroupType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUserID >> (UINT8&)eGroupType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 24, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SMoveFriendAck> fnAck_(new SMoveFriendAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_MoveFriend(qwUserID, eGroupType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CFriendProtSvr::_DoRecv_Whisper(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 24, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_Whisper(qwUserID);
	return true;
}

bool CFriendProtSvr::_DoRecv_FindUserIDNameReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	std::string strRoleName;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID >> strRoleName;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 24, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_FindUserIDNameReq(qwUserID, strRoleName);
	return true;
}

CFriendProtSvr::SFindReferFriendReqAck::SFindReferFriendReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CFriendProtSvr::SFindReferFriendReqAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecReferFriend;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 24, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFriendProtSvr::_DoRecv_FindReferFriendReq(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 24, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFindReferFriendReqAck> fnAck_(new SFindReferFriendReqAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FindReferFriendReq(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CFriendProtSvr::_DoRecv_GetFriendInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetFriendInfo();
	return true;
}

CFriendProtSvr::SSetSignAck::SSetSignAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EFriendResult)0) { }

void CFriendProtSvr::SSetSignAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 24, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFriendProtSvr::_DoRecv_SetSign(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	std::string strSign;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> strSign;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 24, Function: 10";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSetSignAck> fnAck_(new SSetSignAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_SetSign(strSign, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFriendProtSvr::SSetMoodAck::SSetMoodAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EFriendResult)0) { }

void CFriendProtSvr::SSetMoodAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 24, Function: 11";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFriendProtSvr::_DoRecv_SetMood(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wMood = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wMood;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 24, Function: 11";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSetMoodAck> fnAck_(new SSetMoodAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_SetMood(wMood, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NFriendProt
