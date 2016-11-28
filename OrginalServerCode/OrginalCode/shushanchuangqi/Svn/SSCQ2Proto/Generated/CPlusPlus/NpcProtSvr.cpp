/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    NpcProt.cpp
//  Purpose:      NPC相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "NpcProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NNpcProt
{

CNpcProtSvr::THandleFunc CNpcProtSvr::_HandleFuncs[] =
{
	&CNpcProtSvr::_DoRecv_NpcTalkReq, //FuncID: 1
	&CNpcProtSvr::_DoRecv_ExecScriptFunc, //FuncID: 2
	&CNpcProtSvr::_DoRecv_NpcTaskStateReq, //FuncID: 3
	&CNpcProtSvr::_DoRecv_FinishTaskTalk, //FuncID: 4
};

bool CNpcProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：NPC对话通知
bool CNpcProtSvr::Send_NpcTalkNtf(
	UINT64 qwCreatureID, //NPC的生物ID
	ETalkResult eResult, //对话结果
	const std::string& strContent //对话内容
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << (UINT8&)eResult << strContent;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 14, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNpcProtSvr::SendClt_NpcTalkNtf(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwCreatureID, //NPC的生物ID
	ETalkResult eResult, //对话结果
	const std::string& strContent //对话内容
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << (UINT8&)eResult << strContent;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 14, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNpcProtSvr::BuildPkg_NpcTalkNtf(
	UINT64 qwCreatureID, //NPC的生物ID
	ETalkResult eResult, //对话结果
	const std::string& strContent //对话内容
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << (UINT8&)eResult << strContent;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 14, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：NPC任务状态通知
bool CNpcProtSvr::Send_NpcTaskStateNtf(
	const TVecNpcTask& rVecNpcTask //NPC任务状态列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << rVecNpcTask;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 14, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNpcProtSvr::SendClt_NpcTaskStateNtf(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecNpcTask& rVecNpcTask //NPC任务状态列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << rVecNpcTask;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 14, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNpcProtSvr::BuildPkg_NpcTaskStateNtf(
	const TVecNpcTask& rVecNpcTask //NPC任务状态列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << rVecNpcTask;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 14, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CNpcProtSvr::_DoRecv_NpcTalkReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwCreatureID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwCreatureID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 14, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_NpcTalkReq(qwCreatureID);
	return true;
}

bool CNpcProtSvr::_DoRecv_ExecScriptFunc(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwCreatureID = 0;
	std::string strFuncName;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwCreatureID >> strFuncName;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 14, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_ExecScriptFunc(qwCreatureID, strFuncName);
	return true;
}

bool CNpcProtSvr::_DoRecv_NpcTaskStateReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT16 wMapID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> wMapID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 14, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_NpcTaskStateReq(wMapID);
	return true;
}

CNpcProtSvr::SFinishTaskTalkAck::SFinishTaskTalkAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CNpcProtSvr::SFinishTaskTalkAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << strContent;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 14, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNpcProtSvr::_DoRecv_FinishTaskTalk(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwCreatureID = 0;
	UINT16 wTaskID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwCreatureID >> wTaskID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 14, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFinishTaskTalkAck> fnAck_(new SFinishTaskTalkAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FinishTaskTalk(qwCreatureID, wTaskID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NNpcProt
