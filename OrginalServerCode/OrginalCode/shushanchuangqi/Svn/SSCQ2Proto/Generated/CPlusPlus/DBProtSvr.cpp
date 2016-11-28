/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    DBProt.cpp
//  Purpose:      数据库查询协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "DBProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NDBProt
{

CDBProtSvr::THandleFunc CDBProtSvr::_HandleFuncs[] =
{
	&CDBProtSvr::_DoRecv_QueryReq, //FuncID: 1
};

bool CDBProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：无结果集的返回
bool CDBProtSvr::Send_ResultRet(
	UINT32 dwTransID, //事务的ID
	INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
	UINT32 dwAffectRow //影响的行数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTransID << byRet << dwAffectRow;
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

bool CDBProtSvr::SendSvr_ResultRet(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwTransID, //事务的ID
	INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
	UINT32 dwAffectRow //影响的行数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTransID << byRet << dwAffectRow;
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

std::string& CDBProtSvr::BuildPkg_ResultRet(
	UINT32 dwTransID, //事务的ID
	INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
	UINT32 dwAffectRow //影响的行数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTransID << byRet << dwAffectRow;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 9, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：有结果集的返回
bool CDBProtSvr::Send_ResultDataRet(
	UINT32 dwTransID, //事务的ID
	INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
	const TVecTable& vecTable, //返回的结果表集
	UINT8 byCount //结果表数量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTransID << byRet << vecTable << byCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 9, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDBProtSvr::SendSvr_ResultDataRet(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwTransID, //事务的ID
	INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
	const TVecTable& vecTable, //返回的结果表集
	UINT8 byCount //结果表数量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTransID << byRet << vecTable << byCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 9, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDBProtSvr::BuildPkg_ResultDataRet(
	UINT32 dwTransID, //事务的ID
	INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
	const TVecTable& vecTable, //返回的结果表集
	UINT8 byCount //结果表数量
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTransID << byRet << vecTable << byCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 9, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CDBProtSvr::_DoRecv_QueryReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwTransID = 0;
	EQueryType eQueryType = (EQueryType)0;
	SQuery query;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwTransID >> (UINT8&)eQueryType >> query;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 9, Function: 1";
		return false;
	}
	OnRecv_QueryReq(dwTransID, eQueryType, query);
	return true;
}

} //namespace NDBProt
