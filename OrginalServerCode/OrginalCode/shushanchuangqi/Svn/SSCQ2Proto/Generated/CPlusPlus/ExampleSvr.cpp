/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Example.cpp
//  Purpose:      通信协议示例
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ExampleSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NExample
{

CExampleSvr::THandleFunc CExampleSvr::_HandleFuncs[] =
{
	&CExampleSvr::_DoRecv_SampleFunc1, //FuncID: 1
	&CExampleSvr::_DoRecv_SampleRetFunc2, //FuncID: 2
};

bool CExampleSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：S->C示例函数1
bool CExampleSvr::Send_SampleFuncAck1(
	INT8 byParam1, //8位有符号整数
	INT16 wParam2, //16位有符号整数
	INT32 dwParam3, //32位有符号整数
	INT64 qwParam4, //64位有符号整数
	UINT8 byParam5, //8位无符号整数
	UINT16 wParam6, //16位无符号整数
	UINT32 dwParam7, //32位无符号整数
	UINT64 qwParam8, //64位无符号整数
	bool bParam9, //布尔值
	float fParam10, //单精度浮点数
	double dParam11, //双精度浮点数
	const std::string& strParam12, //字符串
	const std::string& strParam13, //AS字节数组
	EExTest eTest14, //枚举值
	const TVecExDescend4& vecExDesc15 //继承结构体列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << byParam1 << wParam2 << dwParam3 << qwParam4 << byParam5 << wParam6 << dwParam7 << qwParam8 << bParam9 << fParam10 << dParam11 << strParam12 << strParam13 << (INT16&)eTest14 << vecExDesc15;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 255, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CExampleSvr::SendClt_SampleFuncAck1(const UINT64* pUsrID_, UINT16 wCnt_,
	INT8 byParam1, //8位有符号整数
	INT16 wParam2, //16位有符号整数
	INT32 dwParam3, //32位有符号整数
	INT64 qwParam4, //64位有符号整数
	UINT8 byParam5, //8位无符号整数
	UINT16 wParam6, //16位无符号整数
	UINT32 dwParam7, //32位无符号整数
	UINT64 qwParam8, //64位无符号整数
	bool bParam9, //布尔值
	float fParam10, //单精度浮点数
	double dParam11, //双精度浮点数
	const std::string& strParam12, //字符串
	const std::string& strParam13, //AS字节数组
	EExTest eTest14, //枚举值
	const TVecExDescend4& vecExDesc15 //继承结构体列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << byParam1 << wParam2 << dwParam3 << qwParam4 << byParam5 << wParam6 << dwParam7 << qwParam8 << bParam9 << fParam10 << dParam11 << strParam12 << strParam13 << (INT16&)eTest14 << vecExDesc15;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 255, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CExampleSvr::BuildPkg_SampleFuncAck1(
	INT8 byParam1, //8位有符号整数
	INT16 wParam2, //16位有符号整数
	INT32 dwParam3, //32位有符号整数
	INT64 qwParam4, //64位有符号整数
	UINT8 byParam5, //8位无符号整数
	UINT16 wParam6, //16位无符号整数
	UINT32 dwParam7, //32位无符号整数
	UINT64 qwParam8, //64位无符号整数
	bool bParam9, //布尔值
	float fParam10, //单精度浮点数
	double dParam11, //双精度浮点数
	const std::string& strParam12, //字符串
	const std::string& strParam13, //AS字节数组
	EExTest eTest14, //枚举值
	const TVecExDescend4& vecExDesc15 //继承结构体列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << byParam1 << wParam2 << dwParam3 << qwParam4 << byParam5 << wParam6 << dwParam7 << qwParam8 << bParam9 << fParam10 << dParam11 << strParam12 << strParam13 << (INT16&)eTest14 << vecExDesc15;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 255, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

std::string& CExampleSvr::BuildParamPkg_SampleFuncAck1(
	INT8 byParam1, //8位有符号整数
	INT16 wParam2, //16位有符号整数
	INT32 dwParam3, //32位有符号整数
	INT64 qwParam4, //64位有符号整数
	UINT8 byParam5, //8位无符号整数
	UINT16 wParam6, //16位无符号整数
	UINT32 dwParam7, //32位无符号整数
	UINT64 qwParam8, //64位无符号整数
	bool bParam9, //布尔值
	float fParam10, //单精度浮点数
	double dParam11, //双精度浮点数
	const std::string& strParam12, //字符串
	const std::string& strParam13, //AS字节数组
	EExTest eTest14, //枚举值
	const TVecExDescend4& vecExDesc15 //继承结构体列表
)
{
	COutArchive ar(_strPkg);
	try
	{
		ar << byParam1 << wParam2 << dwParam3 << qwParam4 << byParam5 << wParam6 << dwParam7 << qwParam8 << bParam9 << fParam10 << dParam11 << strParam12 << strParam13 << (INT16&)eTest14 << vecExDesc15;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 255, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

std::string& CExampleSvr::BuildFullPkg_SampleFuncAck1(const string& strParamPkg)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	ar << byProtID_ << byFuncID_;
	_strPkg += strParamPkg;
	return _strPkg;
}

bool CExampleSvr::_DoRecv_SampleFunc1(const char* pBuf_, UINT32 dwLen_)
{
	INT8 byParam1 = 0;
	INT16 wParam2 = 0;
	INT32 dwParam3 = 0;
	INT64 qwParam4 = 0;
	UINT8 byParam5 = 0;
	UINT16 wParam6 = 0;
	UINT32 dwParam7 = 0;
	UINT64 qwParam8 = 0;
	bool bParam9 = false;
	float fParam10 = 0;
	double dParam11 = 0;
	std::string strParam12;
	std::string strParam13;
	EExTest eTest14 = (EExTest)0;
	TVecExDescend4 vecExDesc15;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> byParam1 >> wParam2 >> dwParam3 >> qwParam4 >> byParam5 >> wParam6 >> dwParam7 >> qwParam8 >> bParam9 >> fParam10 >> dParam11 >> strParam12 >> strParam13 >> (INT16&)eTest14 >> vecExDesc15;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 255, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_SampleFunc1(byParam1, wParam2, dwParam3, qwParam4, byParam5, wParam6, dwParam7, qwParam8, bParam9, fParam10, dParam11, strParam12, strParam13, eTest14, vecExDesc15);
	return true;
}

CExampleSvr::SSampleRetFunc2Ack::SSampleRetFunc2Ack(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CExampleSvr::SSampleRetFunc2Ack::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecExDescend << strRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 255, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CExampleSvr::_DoRecv_SampleRetFunc2(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byParam1 = 0;
	UINT64 qwParam2 = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byParam1 >> qwParam2;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 255, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSampleRetFunc2Ack> fnAck_(new SSampleRetFunc2Ack(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_SampleRetFunc2(byParam1, qwParam2, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NExample
