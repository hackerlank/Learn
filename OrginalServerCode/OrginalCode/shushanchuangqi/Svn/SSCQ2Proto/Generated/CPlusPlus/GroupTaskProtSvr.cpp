/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    GroupTaskProt.cpp
//  Purpose:      师门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GroupTaskProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGroupTaskProt
{

CGroupTaskProtSvr::THandleFunc CGroupTaskProtSvr::_HandleFuncs[] =
{
	&CGroupTaskProtSvr::_DoRecv_GroupTaskOp, //FuncID: 1
	&CGroupTaskProtSvr::_DoRecv_FlushTask, //FuncID: 2
	&CGroupTaskProtSvr::_DoRecv_GetAllInfoTask, //FuncID: 3
	&CGroupTaskProtSvr::_DoRecv_BuyTaskTimes, //FuncID: 4
};

bool CGroupTaskProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：获取师门任务详情
bool CGroupTaskProtSvr::Send_ReturnAllInfoTask(
	const SGroupTaskInfoForClient& stGroupTaskInfo //师门任务详情
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << stGroupTaskInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 51, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGroupTaskProtSvr::SendClt_ReturnAllInfoTask(const UINT64* pUsrID_, UINT16 wCnt_,
	const SGroupTaskInfoForClient& stGroupTaskInfo //师门任务详情
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << stGroupTaskInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 51, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGroupTaskProtSvr::BuildPkg_ReturnAllInfoTask(
	const SGroupTaskInfoForClient& stGroupTaskInfo //师门任务详情
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << stGroupTaskInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 51, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：任务列表更新
bool CGroupTaskProtSvr::Send_UpdateGroupTask(
	const SGroupTask& stTask //师门任务详情
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << stTask;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 51, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGroupTaskProtSvr::SendClt_UpdateGroupTask(const UINT64* pUsrID_, UINT16 wCnt_,
	const SGroupTask& stTask //师门任务详情
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << stTask;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 51, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGroupTaskProtSvr::BuildPkg_UpdateGroupTask(
	const SGroupTask& stTask //师门任务详情
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << stTask;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 51, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：完成任务数更新
bool CGroupTaskProtSvr::Send_UpdateFinishTask(
	UINT8 byFinishTask, //今日完成的师门任务数
	UINT8 byAcceptTaskTimes, //剩余可接任务数
	UINT8 byVIPTaskTimes, //购买的可接任务数
	UINT8 byBuyTimesToday //今日购买的任务数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << byFinishTask << byAcceptTaskTimes << byVIPTaskTimes << byBuyTimesToday;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 51, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGroupTaskProtSvr::SendClt_UpdateFinishTask(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byFinishTask, //今日完成的师门任务数
	UINT8 byAcceptTaskTimes, //剩余可接任务数
	UINT8 byVIPTaskTimes, //购买的可接任务数
	UINT8 byBuyTimesToday //今日购买的任务数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << byFinishTask << byAcceptTaskTimes << byVIPTaskTimes << byBuyTimesToday;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 51, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGroupTaskProtSvr::BuildPkg_UpdateFinishTask(
	UINT8 byFinishTask, //今日完成的师门任务数
	UINT8 byAcceptTaskTimes, //剩余可接任务数
	UINT8 byVIPTaskTimes, //购买的可接任务数
	UINT8 byBuyTimesToday //今日购买的任务数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << byFinishTask << byAcceptTaskTimes << byVIPTaskTimes << byBuyTimesToday;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 51, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新清修状态
bool CGroupTaskProtSvr::Send_UpdateStudyState(
	EGroupStudyState eStudyState //清修状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStudyState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 51, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGroupTaskProtSvr::SendClt_UpdateStudyState(const UINT64* pUsrID_, UINT16 wCnt_,
	EGroupStudyState eStudyState //清修状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStudyState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 51, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGroupTaskProtSvr::BuildPkg_UpdateStudyState(
	EGroupStudyState eStudyState //清修状态
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStudyState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 51, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新声望等级
bool CGroupTaskProtSvr::Send_UpdateGroupReputeLevel(
	UINT8 dwGroupLevel //声望等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGroupLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 51, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGroupTaskProtSvr::SendClt_UpdateGroupReputeLevel(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 dwGroupLevel //声望等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGroupLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 51, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGroupTaskProtSvr::BuildPkg_UpdateGroupReputeLevel(
	UINT8 dwGroupLevel //声望等级
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGroupLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 51, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新声望
bool CGroupTaskProtSvr::Send_UpdateGroupRepute(
	UINT32 dwGroupRepute //声望
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGroupRepute;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 51, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGroupTaskProtSvr::SendClt_UpdateGroupRepute(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwGroupRepute //声望
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGroupRepute;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 51, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGroupTaskProtSvr::BuildPkg_UpdateGroupRepute(
	UINT32 dwGroupRepute //声望
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGroupRepute;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 51, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新今日清修领奖次数
bool CGroupTaskProtSvr::Send_UpdateStudyAward(
	UINT8 byStudyAward //今日领取的清修次数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << byStudyAward;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 51, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGroupTaskProtSvr::SendClt_UpdateStudyAward(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byStudyAward //今日领取的清修次数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << byStudyAward;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 51, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGroupTaskProtSvr::BuildPkg_UpdateStudyAward(
	UINT8 byStudyAward //今日领取的清修次数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << byStudyAward;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 51, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

CGroupTaskProtSvr::SGroupTaskOpAck::SGroupTaskOpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGroupTaskResult)0), eState((EGroupStudyState)0) { }

void CGroupTaskProtSvr::SGroupTaskOpAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << (UINT8&)eState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 51, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGroupTaskProtSvr::_DoRecv_GroupTaskOp(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 51, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGroupTaskOpAck> fnAck_(new SGroupTaskOpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GroupTaskOp(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGroupTaskProtSvr::SFlushTaskAck::SFlushTaskAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGroupTaskResult)0), byFlushTask(0) { }

void CGroupTaskProtSvr::SFlushTaskAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecTask << byFlushTask;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 51, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGroupTaskProtSvr::_DoRecv_FlushTask(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 51, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFlushTaskAck> fnAck_(new SFlushTaskAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FlushTask(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGroupTaskProtSvr::_DoRecv_GetAllInfoTask(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetAllInfoTask();
	return true;
}

CGroupTaskProtSvr::SBuyTaskTimesAck::SBuyTaskTimesAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGroupTaskResult)0) { }

void CGroupTaskProtSvr::SBuyTaskTimesAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 51, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGroupTaskProtSvr::_DoRecv_BuyTaskTimes(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 51, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBuyTaskTimesAck> fnAck_(new SBuyTaskTimesAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BuyTaskTimes(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NGroupTaskProt
