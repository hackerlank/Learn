/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    GuildBattleProt.cpp
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GuildBattleProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGuildBattleProt
{

CGuildBattleProtSvr::THandleFunc CGuildBattleProtSvr::_HandleFuncs[] =
{
	&CGuildBattleProtSvr::_DoRecv_SignUp, //FuncID: 1
	&CGuildBattleProtSvr::_DoRecv_Enter, //FuncID: 2
	&CGuildBattleProtSvr::_DoRecv_Quit, //FuncID: 3
	&CGuildBattleProtSvr::_DoRecv_AdjustMember, //FuncID: 4
	&CGuildBattleProtSvr::_DoRecv_GetState, //FuncID: 5
	&CGuildBattleProtSvr::_DoRecv_GetFieldInfo, //FuncID: 6
	&CGuildBattleProtSvr::_DoRecv_GetSpotInfo, //FuncID: 7
	&CGuildBattleProtSvr::_DoRecv_GetSpotBattle, //FuncID: 8
	&CGuildBattleProtSvr::_DoRecv_GetSkillInfo, //FuncID: 9
	&CGuildBattleProtSvr::_DoRecv_BuySkill, //FuncID: 10
	&CGuildBattleProtSvr::_DoRecv_GetPanelInfo, //FuncID: 11
	&CGuildBattleProtSvr::_DoRecv_CallMember, //FuncID: 12
};

bool CGuildBattleProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：帮派战状态通知
bool CGuildBattleProtSvr::Send_StateNotify(
	EGBState eState, //当前帮派战状态
	UINT8 byBattleCount, //当前已经战斗的数量
	UINT32 dwRemainTime, //当前状态剩余时间
	EGBSpot eSpotType, //自己所在据点(报名的据点或者目前被调整到的据点)
	EGBSide eSelfSide //自己所在帮派方向
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eState << byBattleCount << dwRemainTime << (UINT8&)eSpotType << (UINT8&)eSelfSide;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 76, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGuildBattleProtSvr::SendClt_StateNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	EGBState eState, //当前帮派战状态
	UINT8 byBattleCount, //当前已经战斗的数量
	UINT32 dwRemainTime, //当前状态剩余时间
	EGBSpot eSpotType, //自己所在据点(报名的据点或者目前被调整到的据点)
	EGBSide eSelfSide //自己所在帮派方向
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eState << byBattleCount << dwRemainTime << (UINT8&)eSpotType << (UINT8&)eSelfSide;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 76, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGuildBattleProtSvr::BuildPkg_StateNotify(
	EGBState eState, //当前帮派战状态
	UINT8 byBattleCount, //当前已经战斗的数量
	UINT32 dwRemainTime, //当前状态剩余时间
	EGBSpot eSpotType, //自己所在据点(报名的据点或者目前被调整到的据点)
	EGBSide eSelfSide //自己所在帮派方向
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eState << byBattleCount << dwRemainTime << (UINT8&)eSpotType << (UINT8&)eSelfSide;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 76, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮派战信息通知
bool CGuildBattleProtSvr::Send_FieldInfoNotify(
	const SFieldInfo& sFieldInfo //战场信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << sFieldInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 76, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGuildBattleProtSvr::SendClt_FieldInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const SFieldInfo& sFieldInfo //战场信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << sFieldInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 76, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGuildBattleProtSvr::BuildPkg_FieldInfoNotify(
	const SFieldInfo& sFieldInfo //战场信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << sFieldInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 76, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮派战据点信息通知
bool CGuildBattleProtSvr::Send_SpotInfoNotify(
	const TVecSpotInfo& vecSpotInfo //据点详细信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecSpotInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 76, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGuildBattleProtSvr::SendClt_SpotInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecSpotInfo& vecSpotInfo //据点详细信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecSpotInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 76, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGuildBattleProtSvr::BuildPkg_SpotInfoNotify(
	const TVecSpotInfo& vecSpotInfo //据点详细信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecSpotInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 76, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：据点战斗通知
bool CGuildBattleProtSvr::Send_SpotBattleNotify(
	EGBSpot eType, //据点类型
	const TVecBattleData& vecBattleData //战报信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eType << vecBattleData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 76, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGuildBattleProtSvr::SendClt_SpotBattleNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	EGBSpot eType, //据点类型
	const TVecBattleData& vecBattleData //战报信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eType << vecBattleData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 76, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGuildBattleProtSvr::BuildPkg_SpotBattleNotify(
	EGBSpot eType, //据点类型
	const TVecBattleData& vecBattleData //战报信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eType << vecBattleData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 76, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮派战技能信息通知
bool CGuildBattleProtSvr::Send_SkillInfoNotify(
	const TVecSkillInfo& vecSkillInfo //具体已购买技能
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecSkillInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 76, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGuildBattleProtSvr::SendClt_SkillInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecSkillInfo& vecSkillInfo //具体已购买技能
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecSkillInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 76, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGuildBattleProtSvr::BuildPkg_SkillInfoNotify(
	const TVecSkillInfo& vecSkillInfo //具体已购买技能
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecSkillInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 76, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新帮派战小面板信息
bool CGuildBattleProtSvr::Send_PanelInfoNotify(
	UINT32 dwSelfScore, //我的积分
	UINT32 dwGuildScore, //帮派积分
	UINT32 dwGuildRank //帮派排名
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSelfScore << dwGuildScore << dwGuildRank;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 76, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGuildBattleProtSvr::SendClt_PanelInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwSelfScore, //我的积分
	UINT32 dwGuildScore, //帮派积分
	UINT32 dwGuildRank //帮派排名
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSelfScore << dwGuildScore << dwGuildRank;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 76, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGuildBattleProtSvr::BuildPkg_PanelInfoNotify(
	UINT32 dwSelfScore, //我的积分
	UINT32 dwGuildScore, //帮派积分
	UINT32 dwGuildRank //帮派排名
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSelfScore << dwGuildScore << dwGuildRank;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 76, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：报名还没进入的通知进入
bool CGuildBattleProtSvr::Send_SignupEnterNotify(
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
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 76, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGuildBattleProtSvr::SendClt_SignupEnterNotify(const UINT64* pUsrID_, UINT16 wCnt_
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
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 76, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGuildBattleProtSvr::BuildPkg_SignupEnterNotify(
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
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 76, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：召集帮众广播
bool CGuildBattleProtSvr::Send_CallMemberNotify(
	UINT8 byQuality, //品质
	const std::string& strName //名字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << byQuality << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 76, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGuildBattleProtSvr::SendClt_CallMemberNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byQuality, //品质
	const std::string& strName //名字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << byQuality << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 76, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGuildBattleProtSvr::BuildPkg_CallMemberNotify(
	UINT8 byQuality, //品质
	const std::string& strName //名字
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << byQuality << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 76, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

CGuildBattleProtSvr::SSignUpAck::SSignUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGBSignUpResult)0) { }

void CGuildBattleProtSvr::SSignUpAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 76, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGuildBattleProtSvr::_DoRecv_SignUp(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EGBSpot eSpotType = (EGBSpot)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eSpotType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 76, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSignUpAck> fnAck_(new SSignUpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_SignUp(eSpotType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGuildBattleProtSvr::SEnterAck::SEnterAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGBEnterResult)0) { }

void CGuildBattleProtSvr::SEnterAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 76, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGuildBattleProtSvr::_DoRecv_Enter(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 76, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SEnterAck> fnAck_(new SEnterAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_Enter(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGuildBattleProtSvr::SQuitAck::SQuitAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGBQuitResult)0) { }

void CGuildBattleProtSvr::SQuitAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 76, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGuildBattleProtSvr::_DoRecv_Quit(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 76, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SQuitAck> fnAck_(new SQuitAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_Quit(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGuildBattleProtSvr::SAdjustMemberAck::SAdjustMemberAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGBAdjustResult)0) { }

void CGuildBattleProtSvr::SAdjustMemberAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 76, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGuildBattleProtSvr::_DoRecv_AdjustMember(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwRoleID = 0;
	EGBSpot eSpotType = (EGBSpot)0;
	UINT8 byIndex = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwRoleID >> (UINT8&)eSpotType >> byIndex;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 76, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SAdjustMemberAck> fnAck_(new SAdjustMemberAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_AdjustMember(qwRoleID, eSpotType, byIndex, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGuildBattleProtSvr::SGetStateAck::SGetStateAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eState((EGBState)0), byBattleCount(0), dwRemainTime(0), eSpotType((EGBSpot)0), bGuildJoined(false), 
			eSelfSide((EGBSide)0) { }

void CGuildBattleProtSvr::SGetStateAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eState << byBattleCount << dwRemainTime << (UINT8&)eSpotType << bGuildJoined << (UINT8&)eSelfSide;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 76, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGuildBattleProtSvr::_DoRecv_GetState(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 76, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetStateAck> fnAck_(new SGetStateAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetState(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGuildBattleProtSvr::SGetFieldInfoAck::SGetFieldInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGBResult)0) { }

void CGuildBattleProtSvr::SGetFieldInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecFieldInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 76, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGuildBattleProtSvr::_DoRecv_GetFieldInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 76, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetFieldInfoAck> fnAck_(new SGetFieldInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetFieldInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGuildBattleProtSvr::SGetSpotInfoAck::SGetSpotInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGBResult)0) { }

void CGuildBattleProtSvr::SGetSpotInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecSpotInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 76, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGuildBattleProtSvr::_DoRecv_GetSpotInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EGBSpot eType = (EGBSpot)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 76, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetSpotInfoAck> fnAck_(new SGetSpotInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetSpotInfo(eType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGuildBattleProtSvr::SGetSpotBattleAck::SGetSpotBattleAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGBBattleResult)0) { }

void CGuildBattleProtSvr::SGetSpotBattleAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecBattleData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 76, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGuildBattleProtSvr::_DoRecv_GetSpotBattle(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EGBSpot eType = (EGBSpot)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 76, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetSpotBattleAck> fnAck_(new SGetSpotBattleAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetSpotBattle(eType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGuildBattleProtSvr::SGetSkillInfoAck::SGetSkillInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGBSkillResult)0) { }

void CGuildBattleProtSvr::SGetSkillInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecSkillInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 76, Function: 9";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGuildBattleProtSvr::_DoRecv_GetSkillInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 76, Function: 9";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetSkillInfoAck> fnAck_(new SGetSkillInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetSkillInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGuildBattleProtSvr::SBuySkillAck::SBuySkillAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGBSkillResult)0) { }

void CGuildBattleProtSvr::SBuySkillAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -10;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 76, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGuildBattleProtSvr::_DoRecv_BuySkill(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EGBSkill eType = (EGBSkill)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 76, Function: 10";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBuySkillAck> fnAck_(new SBuySkillAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BuySkill(eType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGuildBattleProtSvr::SGetPanelInfoAck::SGetPanelInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwSelfScore(0), dwGuildScore(0), dwGuildRank(0) { }

void CGuildBattleProtSvr::SGetPanelInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -11;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwSelfScore << dwGuildScore << dwGuildRank;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 76, Function: 11";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGuildBattleProtSvr::_DoRecv_GetPanelInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 76, Function: 11";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetPanelInfoAck> fnAck_(new SGetPanelInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetPanelInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGuildBattleProtSvr::SCallMemberAck::SCallMemberAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGBResult)0) { }

void CGuildBattleProtSvr::SCallMemberAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -12;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 76, Function: 12";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGuildBattleProtSvr::_DoRecv_CallMember(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 76, Function: 12";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SCallMemberAck> fnAck_(new SCallMemberAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_CallMember(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NGuildBattleProt
