/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Center2DBGuild.cpp
//  Purpose:      CenterServer到DBServer有关帮派的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Center2DBGuildSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NCenter2DBGuild
{

CCenter2DBGuildSvr::THandleFunc CCenter2DBGuildSvr::_HandleFuncs[] =
{
	&CCenter2DBGuildSvr::_DoRecv_GuildDataUpdate, //FuncID: 1
	&CCenter2DBGuildSvr::_DoRecv_GuildPubDataUpdate, //FuncID: 2
	&CCenter2DBGuildSvr::_DoRecv_GetGuildPubInfo, //FuncID: 3
	&CCenter2DBGuildSvr::_DoRecv_GetAllGuildInfo, //FuncID: 4
	&CCenter2DBGuildSvr::_DoRecv_GuildLogin, //FuncID: 5
	&CCenter2DBGuildSvr::_DoRecv_GuildUserLogin, //FuncID: 6
	&CCenter2DBGuildSvr::_DoRecv_GuildStatueReward, //FuncID: 7
	&CCenter2DBGuildSvr::_DoRecv_GetAllGuildXihe, //FuncID: 8
	&CCenter2DBGuildSvr::_DoRecv_UpdateGuildXihe, //FuncID: 9
	&CCenter2DBGuildSvr::_DoRecv_GetAllGuildExchangedItem, //FuncID: 10
	&CCenter2DBGuildSvr::_DoRecv_UpdateGuildExchangedItem, //FuncID: 11
};

bool CCenter2DBGuildSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：帮派公共信息加载返回
bool CCenter2DBGuildSvr::Send_GuildPubInfoNotify(
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NGuildProt::TVecPubGuildAllInfo& vecPubGuildAllInfo //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecPubGuildAllInfo;
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

bool CCenter2DBGuildSvr::SendSvr_GuildPubInfoNotify(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NGuildProt::TVecPubGuildAllInfo& vecPubGuildAllInfo //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecPubGuildAllInfo;
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

std::string& CCenter2DBGuildSvr::BuildPkg_GuildPubInfoNotify(
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NGuildProt::TVecPubGuildAllInfo& vecPubGuildAllInfo //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecPubGuildAllInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮派
bool CCenter2DBGuildSvr::Send_AllGuildLoginNotify(
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NGuildProt::TVecDBGuildAllInfo& vecData //帮派具体数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecData;
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

bool CCenter2DBGuildSvr::SendSvr_AllGuildLoginNotify(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NGuildProt::TVecDBGuildAllInfo& vecData //帮派具体数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecData;
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

std::string& CCenter2DBGuildSvr::BuildPkg_AllGuildLoginNotify(
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NGuildProt::TVecDBGuildAllInfo& vecData //帮派具体数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮派
bool CCenter2DBGuildSvr::Send_GuildLoginNotify(
	UINT64 qwGuildID, //帮派ID
	const NGuildProt::SDBGuildAllInfo& sData //帮派具体数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << sData;
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

bool CCenter2DBGuildSvr::SendSvr_GuildLoginNotify(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwGuildID, //帮派ID
	const NGuildProt::SDBGuildAllInfo& sData //帮派具体数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << sData;
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

std::string& CCenter2DBGuildSvr::BuildPkg_GuildLoginNotify(
	UINT64 qwGuildID, //帮派ID
	const NGuildProt::SDBGuildAllInfo& sData //帮派具体数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << sData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮派用户登录返回
bool CCenter2DBGuildSvr::Send_GuildUserLoginNotify(
	UINT64 qwRoleID, //玩家ID
	const NGuildProt::TVecDBGuildUserInfo& vecGuildUserInfo //用户信息，数量为0表示完全没有在或者加入过帮派
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecGuildUserInfo;
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

bool CCenter2DBGuildSvr::SendSvr_GuildUserLoginNotify(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	const NGuildProt::TVecDBGuildUserInfo& vecGuildUserInfo //用户信息，数量为0表示完全没有在或者加入过帮派
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecGuildUserInfo;
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

std::string& CCenter2DBGuildSvr::BuildPkg_GuildUserLoginNotify(
	UINT64 qwRoleID, //玩家ID
	const NGuildProt::TVecDBGuildUserInfo& vecGuildUserInfo //用户信息，数量为0表示完全没有在或者加入过帮派
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecGuildUserInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：返回请求帮派供奉人数
bool CCenter2DBGuildSvr::Send_SendAllGuildStatueWorshipCount(
	const TVecGSWorshipInfo& vecGSWorshiInfo //供奉人数信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecGSWorshiInfo;
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

bool CCenter2DBGuildSvr::SendSvr_SendAllGuildStatueWorshipCount(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecGSWorshipInfo& vecGSWorshiInfo //供奉人数信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecGSWorshiInfo;
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

std::string& CCenter2DBGuildSvr::BuildPkg_SendAllGuildStatueWorshipCount(
	const TVecGSWorshipInfo& vecGSWorshiInfo //供奉人数信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecGSWorshiInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：返回所有羲和神车信息
bool CCenter2DBGuildSvr::Send_SendAllGuildXihe(
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NGuildProt::TVecGuildXihe& vecSendData //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendData;
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

bool CCenter2DBGuildSvr::SendSvr_SendAllGuildXihe(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NGuildProt::TVecGuildXihe& vecSendData //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendData;
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

std::string& CCenter2DBGuildSvr::BuildPkg_SendAllGuildXihe(
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NGuildProt::TVecGuildXihe& vecSendData //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：所有帮派兑换物品加载返回
bool CCenter2DBGuildSvr::Send_SendAllGuildExchangedItem(
	const NGuildProt::TVecGuildExchangedItem& vecGuildExchangedItem //派兑换物品信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << vecGuildExchangedItem;
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

bool CCenter2DBGuildSvr::SendSvr_SendAllGuildExchangedItem(const UINT32* pSvrID_, UINT8 byCnt_,
	const NGuildProt::TVecGuildExchangedItem& vecGuildExchangedItem //派兑换物品信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << vecGuildExchangedItem;
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

std::string& CCenter2DBGuildSvr::BuildPkg_SendAllGuildExchangedItem(
	const NGuildProt::TVecGuildExchangedItem& vecGuildExchangedItem //派兑换物品信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << vecGuildExchangedItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 32, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CCenter2DBGuildSvr::_DoRecv_GuildDataUpdate(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwGuildID = 0;
	NGuildProt::EGuildDataType eDataType = (NGuildProt::EGuildDataType)0;
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	std::string strData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwGuildID >> (UINT8&)eDataType >> (UINT8&)eUpdateType >> strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 1";
		return false;
	}
	OnRecv_GuildDataUpdate(qwGuildID, eDataType, eUpdateType, strData);
	return true;
}

bool CCenter2DBGuildSvr::_DoRecv_GuildPubDataUpdate(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwGuildID = 0;
	NGuildProt::EGuildPubDataType eDataType = (NGuildProt::EGuildPubDataType)0;
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	std::string strData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwGuildID >> (UINT8&)eDataType >> (UINT8&)eUpdateType >> strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 2";
		return false;
	}
	OnRecv_GuildPubDataUpdate(qwGuildID, eDataType, eUpdateType, strData);
	return true;
}

bool CCenter2DBGuildSvr::_DoRecv_GetGuildPubInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetGuildPubInfo();
	return true;
}

bool CCenter2DBGuildSvr::_DoRecv_GetAllGuildInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetAllGuildInfo();
	return true;
}

bool CCenter2DBGuildSvr::_DoRecv_GuildLogin(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwGuildID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 5";
		return false;
	}
	OnRecv_GuildLogin(qwGuildID);
	return true;
}

bool CCenter2DBGuildSvr::_DoRecv_GuildUserLogin(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 6";
		return false;
	}
	OnRecv_GuildUserLogin(qwRoleID);
	return true;
}

bool CCenter2DBGuildSvr::_DoRecv_GuildStatueReward(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GuildStatueReward();
	return true;
}

bool CCenter2DBGuildSvr::_DoRecv_GetAllGuildXihe(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwPageSize = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 8";
		return false;
	}
	OnRecv_GetAllGuildXihe(dwPageSize);
	return true;
}

bool CCenter2DBGuildSvr::_DoRecv_UpdateGuildXihe(const char* pBuf_, UINT32 dwLen_)
{
	NGuildProt::SGuildXihe oGuildXihe;
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> oGuildXihe >> (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 9";
		return false;
	}
	OnRecv_UpdateGuildXihe(oGuildXihe, eUpdateType);
	return true;
}

bool CCenter2DBGuildSvr::_DoRecv_GetAllGuildExchangedItem(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetAllGuildExchangedItem();
	return true;
}

bool CCenter2DBGuildSvr::_DoRecv_UpdateGuildExchangedItem(const char* pBuf_, UINT32 dwLen_)
{
	NGuildProt::SGuildExchangedItem sGuildExchangedItem;
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> sGuildExchangedItem >> (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 32, Function: 11";
		return false;
	}
	OnRecv_UpdateGuildExchangedItem(sGuildExchangedItem, eUpdateType);
	return true;
}

} //namespace NCenter2DBGuild
