/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Center2DBGuild.cpp
//  Purpose:      CenterServer到DBServer有关帮派的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Center2DBGuildClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NCenter2DBGuild
{

CCenter2DBGuildClt::THandleFunc CCenter2DBGuildClt::_HandleFuncs[] =
{
	&CCenter2DBGuildClt::_DoRecv_GuildPubInfoNotify, //FuncID: 1
	&CCenter2DBGuildClt::_DoRecv_AllGuildLoginNotify, //FuncID: 2
	&CCenter2DBGuildClt::_DoRecv_GuildLoginNotify, //FuncID: 3
	&CCenter2DBGuildClt::_DoRecv_GuildUserLoginNotify, //FuncID: 4
	&CCenter2DBGuildClt::_DoRecv_SendAllGuildStatueWorshipCount, //FuncID: 5
	&CCenter2DBGuildClt::_DoRecv_SendAllGuildXihe, //FuncID: 6
	&CCenter2DBGuildClt::_DoRecv_SendAllGuildExchangedItem, //FuncID: 7
};

bool CCenter2DBGuildClt::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：帮派数据更新
bool CCenter2DBGuildClt::Send_GuildDataUpdate(
	UINT64 qwGuildID, //帮派ID
	NGuildProt::EGuildDataType eDataType, //更新数据类型
	NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 32, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBGuildClt::SendSvr_GuildDataUpdate(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwGuildID, //帮派ID
	NGuildProt::EGuildDataType eDataType, //更新数据类型
	NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 32, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBGuildClt::BuildPkg_GuildDataUpdate(
	UINT64 qwGuildID, //帮派ID
	NGuildProt::EGuildDataType eDataType, //更新数据类型
	NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮派公共信息更新
bool CCenter2DBGuildClt::Send_GuildPubDataUpdate(
	UINT64 qwGuildID, //帮派ID
	NGuildProt::EGuildPubDataType eDataType, //更新数据类型
	NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 32, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBGuildClt::SendSvr_GuildPubDataUpdate(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwGuildID, //帮派ID
	NGuildProt::EGuildPubDataType eDataType, //更新数据类型
	NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 32, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBGuildClt::BuildPkg_GuildPubDataUpdate(
	UINT64 qwGuildID, //帮派ID
	NGuildProt::EGuildPubDataType eDataType, //更新数据类型
	NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取帮派公共信息（启动预加载调用）
bool CCenter2DBGuildClt::Send_GetGuildPubInfo(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 32, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBGuildClt::SendSvr_GetGuildPubInfo(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 32, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBGuildClt::BuildPkg_GetGuildPubInfo(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取所有帮派信息
bool CCenter2DBGuildClt::Send_GetAllGuildInfo(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 32, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBGuildClt::SendSvr_GetAllGuildInfo(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 32, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBGuildClt::BuildPkg_GetAllGuildInfo(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮派登录（通常是涉及到有关帮派的操作需要加载登录）
bool CCenter2DBGuildClt::Send_GuildLogin(
	UINT64 qwGuildID //帮派ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 32, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBGuildClt::SendSvr_GuildLogin(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwGuildID //帮派ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 32, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBGuildClt::BuildPkg_GuildLogin(
	UINT64 qwGuildID //帮派ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家登录，拉取可能存在的帮派信息
bool CCenter2DBGuildClt::Send_GuildUserLogin(
	UINT64 qwRoleID //玩家ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 32, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBGuildClt::SendSvr_GuildUserLogin(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID //玩家ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 32, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBGuildClt::BuildPkg_GuildUserLogin(
	UINT64 qwRoleID //玩家ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮派神像奖励结算
bool CCenter2DBGuildClt::Send_GuildStatueReward(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 32, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBGuildClt::SendSvr_GuildStatueReward(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 32, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBGuildClt::BuildPkg_GuildStatueReward(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求所有羲和神车信息
bool CCenter2DBGuildClt::Send_GetAllGuildXihe(
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 32, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBGuildClt::SendSvr_GetAllGuildXihe(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 32, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBGuildClt::BuildPkg_GetAllGuildXihe(
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新玩家羲和神车信息
bool CCenter2DBGuildClt::Send_UpdateGuildXihe(
	const NGuildProt::SGuildXihe& oGuildXihe, //玩家羲和神车的数据
	NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << oGuildXihe << (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 32, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBGuildClt::SendSvr_UpdateGuildXihe(const UINT32* pSvrID_, UINT8 byCnt_,
	const NGuildProt::SGuildXihe& oGuildXihe, //玩家羲和神车的数据
	NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << oGuildXihe << (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 32, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBGuildClt::BuildPkg_UpdateGuildXihe(
	const NGuildProt::SGuildXihe& oGuildXihe, //玩家羲和神车的数据
	NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << oGuildXihe << (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取帮派战兑换物品
bool CCenter2DBGuildClt::Send_GetAllGuildExchangedItem(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 32, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBGuildClt::SendSvr_GetAllGuildExchangedItem(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 32, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBGuildClt::BuildPkg_GetAllGuildExchangedItem(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新帮派战兑换物品信息
bool CCenter2DBGuildClt::Send_UpdateGuildExchangedItem(
	const NGuildProt::SGuildExchangedItem& sGuildExchangedItem, //帮派战兑换物品信息
	NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << sGuildExchangedItem << (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 32, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBGuildClt::SendSvr_UpdateGuildExchangedItem(const UINT32* pSvrID_, UINT8 byCnt_,
	const NGuildProt::SGuildExchangedItem& sGuildExchangedItem, //帮派战兑换物品信息
	NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << sGuildExchangedItem << (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 32, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBGuildClt::BuildPkg_UpdateGuildExchangedItem(
	const NGuildProt::SGuildExchangedItem& sGuildExchangedItem, //帮派战兑换物品信息
	NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << sGuildExchangedItem << (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 11";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CCenter2DBGuildClt::_DoRecv_GuildPubInfoNotify(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwCurSize = 0;
	UINT32 dwTotalSize = 0;
	NGuildProt::TVecPubGuildAllInfo vecPubGuildAllInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwCurSize >> dwTotalSize >> vecPubGuildAllInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 1";
		return false;
	}
	OnRecv_GuildPubInfoNotify(dwCurSize, dwTotalSize, vecPubGuildAllInfo);
	return true;
}

bool CCenter2DBGuildClt::_DoRecv_AllGuildLoginNotify(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwCurSize = 0;
	UINT32 dwTotalSize = 0;
	NGuildProt::TVecDBGuildAllInfo vecData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwCurSize >> dwTotalSize >> vecData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 2";
		return false;
	}
	OnRecv_AllGuildLoginNotify(dwCurSize, dwTotalSize, vecData);
	return true;
}

bool CCenter2DBGuildClt::_DoRecv_GuildLoginNotify(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwGuildID = 0;
	NGuildProt::SDBGuildAllInfo sData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwGuildID >> sData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 3";
		return false;
	}
	OnRecv_GuildLoginNotify(qwGuildID, sData);
	return true;
}

bool CCenter2DBGuildClt::_DoRecv_GuildUserLoginNotify(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	NGuildProt::TVecDBGuildUserInfo vecGuildUserInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> vecGuildUserInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 4";
		return false;
	}
	OnRecv_GuildUserLoginNotify(qwRoleID, vecGuildUserInfo);
	return true;
}

bool CCenter2DBGuildClt::_DoRecv_SendAllGuildStatueWorshipCount(const char* pBuf_, UINT32 dwLen_)
{
	TVecGSWorshipInfo vecGSWorshiInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecGSWorshiInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 5";
		return false;
	}
	OnRecv_SendAllGuildStatueWorshipCount(vecGSWorshiInfo);
	return true;
}

bool CCenter2DBGuildClt::_DoRecv_SendAllGuildXihe(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwPageSize = 0;
	UINT32 dwTotalSize = 0;
	NGuildProt::TVecGuildXihe vecSendData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwPageSize >> dwTotalSize >> vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 6";
		return false;
	}
	OnRecv_SendAllGuildXihe(dwPageSize, dwTotalSize, vecSendData);
	return true;
}

bool CCenter2DBGuildClt::_DoRecv_SendAllGuildExchangedItem(const char* pBuf_, UINT32 dwLen_)
{
	NGuildProt::TVecGuildExchangedItem vecGuildExchangedItem;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecGuildExchangedItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 7";
		return false;
	}
	OnRecv_SendAllGuildExchangedItem(vecGuildExchangedItem);
	return true;
}

} //namespace NCenter2DBGuild
