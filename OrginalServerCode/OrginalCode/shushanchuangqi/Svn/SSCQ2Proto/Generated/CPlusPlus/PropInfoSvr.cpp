/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    PropInfo.cpp
//  Purpose:      属性相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "PropInfoSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NPropInfo
{

CPropInfoSvr::THandleFunc CPropInfoSvr::_HandleFuncs[] =
{
	&CPropInfoSvr::_DoRecv_MoneyExchange, //FuncID: 1
};

bool CPropInfoSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：属性列表通知(改变后通知)
bool CPropInfoSvr::Send_PropListNotify(
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropValue& vecPropValue //属性列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 17, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CPropInfoSvr::SendClt_PropListNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropValue& vecPropValue //属性列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 17, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CPropInfoSvr::BuildPkg_PropListNotify(
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropValue& vecPropValue //属性列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 17, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：属性列表通知(改变后通知)
bool CPropInfoSvr::Send_PropNotify(
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropValue& vecPropValue, //属性列表
	bool bType //是否飘字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValue << bType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 17, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CPropInfoSvr::SendClt_PropNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropValue& vecPropValue, //属性列表
	bool bType //是否飘字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValue << bType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 17, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CPropInfoSvr::BuildPkg_PropNotify(
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropValue& vecPropValue, //属性列表
	bool bType //是否飘字
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValue << bType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 17, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：扩展属性列表通知(改变后通知)
bool CPropInfoSvr::Send_PropExtListNotify(
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropValExt& vecPropValExt //扩展属性列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValExt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 17, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CPropInfoSvr::SendClt_PropExtListNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropValExt& vecPropValExt //扩展属性列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValExt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 17, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CPropInfoSvr::BuildPkg_PropExtListNotify(
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropValExt& vecPropValExt //扩展属性列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValExt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 17, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：属性列表通知(改变后通知)
bool CPropInfoSvr::Send_PropQWListNotify(
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropQWValue& vecPropValue //属性列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 17, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CPropInfoSvr::SendClt_PropQWListNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropQWValue& vecPropValue //属性列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 17, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CPropInfoSvr::BuildPkg_PropQWListNotify(
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropQWValue& vecPropValue //属性列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 17, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：扩展属性列表通知(改变后通知)
bool CPropInfoSvr::Send_PropQWExtListNotify(
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropQWValExt& vecPropValExt //扩展属性列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValExt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 17, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CPropInfoSvr::SendClt_PropQWExtListNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropQWValExt& vecPropValExt //扩展属性列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValExt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 17, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CPropInfoSvr::BuildPkg_PropQWExtListNotify(
	UINT64 qwInstID, //变更对象ID
	EPropClass eClass, //变更对象类型
	const TVecPropQWValExt& vecPropValExt //扩展属性列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eClass << vecPropValExt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 17, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：Creature的名字改变通知
bool CPropInfoSvr::Send_NameChangeNotify(
	UINT64 qwCreatureID, //生物ID
	const std::string& strName //新名字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 17, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CPropInfoSvr::SendClt_NameChangeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwCreatureID, //生物ID
	const std::string& strName //新名字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 17, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CPropInfoSvr::BuildPkg_NameChangeNotify(
	UINT64 qwCreatureID, //生物ID
	const std::string& strName //新名字
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 17, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

CPropInfoSvr::SMoneyExchangeAck::SMoneyExchangeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EExchangeResult)0) { }

void CPropInfoSvr::SMoneyExchangeAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 17, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPropInfoSvr::_DoRecv_MoneyExchange(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EPropType eSrcProp = (EPropType)0;
	EPropType eDestProp = (EPropType)0;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT16&)eSrcProp >> (UINT16&)eDestProp >> dwCount;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 17, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SMoneyExchangeAck> fnAck_(new SMoneyExchangeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_MoneyExchange(eSrcProp, eDestProp, dwCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NPropInfo
