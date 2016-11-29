/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterLog.cpp
//  Purpose:      GameServer到CenterServer的数据中心log协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterLogSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterLog
{

CGame2CenterLogSvr::THandleFunc CGame2CenterLogSvr::_HandleFuncs[] =
{
	&CGame2CenterLogSvr::_DoRecv_LogRegister, //FuncID: 1
	&CGame2CenterLogSvr::_DoRecv_LogUserLogin, //FuncID: 2
	&CGame2CenterLogSvr::_DoRecv_LogPlayerLogout, //FuncID: 3
	&CGame2CenterLogSvr::_DoRecv_LogRecharge, //FuncID: 4
	&CGame2CenterLogSvr::_DoRecv_LogMoneyChange, //FuncID: 5
	&CGame2CenterLogSvr::_DoRecv_LogItemChange, //FuncID: 6
	&CGame2CenterLogSvr::_DoRecv_LogGuideChange, //FuncID: 7
	&CGame2CenterLogSvr::_DoRecv_LogActiveChange, //FuncID: 8
	&CGame2CenterLogSvr::_DoRecv_LogAct, //FuncID: 9
	&CGame2CenterLogSvr::_DoRecv_LogServerInfo, //FuncID: 10
};

bool CGame2CenterLogSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

bool CGame2CenterLogSvr::_DoRecv_LogRegister(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	TVecString vecStrInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> vecStrInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 61, Function: 1";
		return false;
	}
	OnRecv_LogRegister(qwUsrID, vecStrInfo);
	return true;
}

bool CGame2CenterLogSvr::_DoRecv_LogUserLogin(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	TVecString vecStrInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> vecStrInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 61, Function: 2";
		return false;
	}
	OnRecv_LogUserLogin(qwUsrID, vecStrInfo);
	return true;
}

bool CGame2CenterLogSvr::_DoRecv_LogPlayerLogout(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwTime = 0;
	UINT64 qwUsrID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwTime >> qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 61, Function: 3";
		return false;
	}
	OnRecv_LogPlayerLogout(dwTime, qwUsrID);
	return true;
}

bool CGame2CenterLogSvr::_DoRecv_LogRecharge(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	std::string strUdp1;
	std::string strUdp2;
	UINT32 dwGold = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> strUdp1 >> strUdp2 >> dwGold;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 61, Function: 4";
		return false;
	}
	OnRecv_LogRecharge(qwUsrID, strUdp1, strUdp2, dwGold);
	return true;
}

bool CGame2CenterLogSvr::_DoRecv_LogMoneyChange(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	EOpType eType = (EOpType)0;
	TVecUserMoneyChange vecMoney;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> (UINT8&)eType >> vecMoney;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 61, Function: 5";
		return false;
	}
	OnRecv_LogMoneyChange(qwUsrID, eType, vecMoney);
	return true;
}

bool CGame2CenterLogSvr::_DoRecv_LogItemChange(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	EOpType eType = (EOpType)0;
	TVecUserItemChange vecItem;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> (UINT8&)eType >> vecItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 61, Function: 6";
		return false;
	}
	OnRecv_LogItemChange(qwUsrID, eType, vecItem);
	return true;
}

bool CGame2CenterLogSvr::_DoRecv_LogGuideChange(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	std::string strCategory;
	std::string strStep;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> strCategory >> strStep;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 61, Function: 7";
		return false;
	}
	OnRecv_LogGuideChange(qwUsrID, strCategory, strStep);
	return true;
}

bool CGame2CenterLogSvr::_DoRecv_LogActiveChange(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	std::string strCategory;
	std::string strAction;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> strCategory >> strAction >> dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 61, Function: 8";
		return false;
	}
	OnRecv_LogActiveChange(qwUsrID, strCategory, strAction, dwCount);
	return true;
}

bool CGame2CenterLogSvr::_DoRecv_LogAct(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	std::string strCategory;
	std::string strAction;
	std::string strParam3;
	std::string strParam4;
	std::string strParam5;
	std::string strParam6;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> strCategory >> strAction >> strParam3 >> strParam4 >> strParam5 >> strParam6 >> dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 61, Function: 9";
		return false;
	}
	OnRecv_LogAct(qwUsrID, strCategory, strAction, strParam3, strParam4, strParam5, strParam6, dwCount);
	return true;
}

bool CGame2CenterLogSvr::_DoRecv_LogServerInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwTime = 0;
	std::string strType;
	std::string strSubType;
	UINT32 dwNum = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwTime >> strType >> strSubType >> dwNum;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 61, Function: 10";
		return false;
	}
	OnRecv_LogServerInfo(dwTime, strType, strSubType, dwNum);
	return true;
}

} //namespace NGame2CenterLog
