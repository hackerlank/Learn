/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    ShushanBattleProt.cpp
//  Purpose:      蜀山论剑相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ShushanBattleProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NShushanBattleProt
{

CShushanBattleProtSvr::THandleFunc CShushanBattleProtSvr::_HandleFuncs[] =
{
	&CShushanBattleProtSvr::_DoRecv_GetBattleStartInfo, //FuncID: 1
	&CShushanBattleProtSvr::_DoRecv_GetPlayerPairInfo, //FuncID: 2
	&CShushanBattleProtSvr::_DoRecv_GetFirstPlayer, //FuncID: 3
	&CShushanBattleProtSvr::_DoRecv_PlayerEnter, //FuncID: 4
	&CShushanBattleProtSvr::_DoRecv_PlayerLeave, //FuncID: 5
	&CShushanBattleProtSvr::_DoRecv_UseSkill, //FuncID: 6
	&CShushanBattleProtSvr::_DoRecv_BuySkill, //FuncID: 7
};

bool CShushanBattleProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：蜀山论剑准备/开始/结束信息
bool CShushanBattleProtSvr::Send_BattleStartInfo(
	UINT8 byStatus, //状态=>0:准备 1:开始 2:结束
	UINT32 dwTimeLeft //byStatus为0:距离开始的剩余时间;byStatus为1:距离结束的剩余时间;byStatus为2:距离下一次开始的剩余时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << byStatus << dwTimeLeft;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 66, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CShushanBattleProtSvr::SendClt_BattleStartInfo(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byStatus, //状态=>0:准备 1:开始 2:结束
	UINT32 dwTimeLeft //byStatus为0:距离开始的剩余时间;byStatus为1:距离结束的剩余时间;byStatus为2:距离下一次开始的剩余时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << byStatus << dwTimeLeft;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 66, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CShushanBattleProtSvr::BuildPkg_BattleStartInfo(
	UINT8 byStatus, //状态=>0:准备 1:开始 2:结束
	UINT32 dwTimeLeft //byStatus为0:距离开始的剩余时间;byStatus为1:距离结束的剩余时间;byStatus为2:距离下一次开始的剩余时间
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << byStatus << dwTimeLeft;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 66, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：蜀山论剑玩家的配对信息
bool CShushanBattleProtSvr::Send_PlayerPairInfo(
	const SSSBattlePairInfo& stPairInfo //玩家的配对信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << stPairInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 66, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CShushanBattleProtSvr::SendClt_PlayerPairInfo(const UINT64* pUsrID_, UINT16 wCnt_,
	const SSSBattlePairInfo& stPairInfo //玩家的配对信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << stPairInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 66, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CShushanBattleProtSvr::BuildPkg_PlayerPairInfo(
	const SSSBattlePairInfo& stPairInfo //玩家的配对信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << stPairInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 66, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：广播连杀王玩家信息
bool CShushanBattleProtSvr::Send_TopKiller(
	const std::string& strName, //玩家名字
	UINT8 byTopStreak //最高连杀数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << strName << byTopStreak;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 66, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CShushanBattleProtSvr::SendClt_TopKiller(const UINT64* pUsrID_, UINT16 wCnt_,
	const std::string& strName, //玩家名字
	UINT8 byTopStreak //最高连杀数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << strName << byTopStreak;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 66, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CShushanBattleProtSvr::BuildPkg_TopKiller(
	const std::string& strName, //玩家名字
	UINT8 byTopStreak //最高连杀数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << strName << byTopStreak;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 66, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：广播荣誉王玩家信息
bool CShushanBattleProtSvr::Send_HonorKinger(
	const std::string& strName, //玩家名字
	UINT16 wMaxHonor //最高荣誉值
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << strName << wMaxHonor;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 66, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CShushanBattleProtSvr::SendClt_HonorKinger(const UINT64* pUsrID_, UINT16 wCnt_,
	const std::string& strName, //玩家名字
	UINT16 wMaxHonor //最高荣誉值
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << strName << wMaxHonor;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 66, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CShushanBattleProtSvr::BuildPkg_HonorKinger(
	const std::string& strName, //玩家名字
	UINT16 wMaxHonor //最高荣誉值
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << strName << wMaxHonor;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 66, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：蜀山论剑玩家的战报信息
bool CShushanBattleProtSvr::Send_BattleReportInfo(
	UINT8 byType, //0表示个人战报 1表示全部
	const TVecSSBattleReport& vecReport //玩家的战斗信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << byType << vecReport;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 66, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CShushanBattleProtSvr::SendClt_BattleReportInfo(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byType, //0表示个人战报 1表示全部
	const TVecSSBattleReport& vecReport //玩家的战斗信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << byType << vecReport;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 66, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CShushanBattleProtSvr::BuildPkg_BattleReportInfo(
	UINT8 byType, //0表示个人战报 1表示全部
	const TVecSSBattleReport& vecReport //玩家的战斗信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << byType << vecReport;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 66, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：蜀山论剑玩家使用技能信息
bool CShushanBattleProtSvr::Send_UseSkillInfo(
	const SSSBattleUseSkill& stUseSkill //使用技能信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << stUseSkill;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 66, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CShushanBattleProtSvr::SendClt_UseSkillInfo(const UINT64* pUsrID_, UINT16 wCnt_,
	const SSSBattleUseSkill& stUseSkill //使用技能信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << stUseSkill;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 66, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CShushanBattleProtSvr::BuildPkg_UseSkillInfo(
	const SSSBattleUseSkill& stUseSkill //使用技能信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << stUseSkill;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 66, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CShushanBattleProtSvr::_DoRecv_GetBattleStartInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetBattleStartInfo();
	return true;
}

bool CShushanBattleProtSvr::_DoRecv_GetPlayerPairInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetPlayerPairInfo();
	return true;
}

bool CShushanBattleProtSvr::_DoRecv_GetFirstPlayer(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetFirstPlayer();
	return true;
}

CShushanBattleProtSvr::SPlayerEnterAck::SPlayerEnterAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ESSBattleResult)0) { }

void CShushanBattleProtSvr::SPlayerEnterAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 66, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CShushanBattleProtSvr::_DoRecv_PlayerEnter(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 66, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SPlayerEnterAck> fnAck_(new SPlayerEnterAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_PlayerEnter(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CShushanBattleProtSvr::SPlayerLeaveAck::SPlayerLeaveAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ESSBattleResult)0) { }

void CShushanBattleProtSvr::SPlayerLeaveAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 66, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CShushanBattleProtSvr::_DoRecv_PlayerLeave(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 66, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SPlayerLeaveAck> fnAck_(new SPlayerLeaveAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_PlayerLeave(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CShushanBattleProtSvr::SUseSkillAck::SUseSkillAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			bySkillID(0), eResult((ESSBattleResult)0) { }

void CShushanBattleProtSvr::SUseSkillAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << bySkillID << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 66, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CShushanBattleProtSvr::_DoRecv_UseSkill(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 bySkillID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bySkillID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 66, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SUseSkillAck> fnAck_(new SUseSkillAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_UseSkill(bySkillID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CShushanBattleProtSvr::SBuySkillAck::SBuySkillAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byFlag(0), eResult((ESSBattleResult)0) { }

void CShushanBattleProtSvr::SBuySkillAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byFlag << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 66, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CShushanBattleProtSvr::_DoRecv_BuySkill(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byFlag = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byFlag;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 66, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBuySkillAck> fnAck_(new SBuySkillAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BuySkill(byFlag, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NShushanBattleProt
