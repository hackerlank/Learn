/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    DBProt.cpp
//  Purpose:      数据库查询协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "DBProtClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NDBProt
{

CDBProtClt::THandleFunc CDBProtClt::_HandleFuncs[] =
{
	&CDBProtClt::_DoRecv_ResultRet, //FuncID: 1
	&CDBProtClt::_DoRecv_ResultDataRet, //FuncID: 2
};

bool CDBProtClt::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：查询请求
bool CDBProtClt::Send_QueryReq(
	UINT32 dwTransID, //事务的ID
	EQueryType eQueryType, //查询类型
	const SQuery& query //查询
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTransID << (UINT8&)eQueryType << query;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 9, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDBProtClt::SendSvr_QueryReq(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwTransID, //事务的ID
	EQueryType eQueryType, //查询类型
	const SQuery& query //查询
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTransID << (UINT8&)eQueryType << query;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 9, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDBProtClt::BuildPkg_QueryReq(
	UINT32 dwTransID, //事务的ID
	EQueryType eQueryType, //查询类型
	const SQuery& query //查询
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTransID << (UINT8&)eQueryType << query;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 9, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CDBProtClt::_DoRecv_ResultRet(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwTransID = 0;
	INT8 byRet = 0;
	UINT32 dwAffectRow = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwTransID >> byRet >> dwAffectRow;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 9, Function: 1";
		return false;
	}
	OnRecv_ResultRet(dwTransID, byRet, dwAffectRow);
	return true;
}

bool CDBProtClt::_DoRecv_ResultDataRet(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwTransID = 0;
	INT8 byRet = 0;
	TVecTable vecTable;
	UINT8 byCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwTransID >> byRet >> vecTable >> byCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 9, Function: 2";
		return false;
	}
	OnRecv_ResultDataRet(dwTransID, byRet, vecTable, byCount);
	return true;
}

} //namespace NDBProt
