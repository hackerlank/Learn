/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    NewGuildBattleProt.cpp
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "NewGuildBattleProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NNewGuildBattleProt
{

CNewGuildBattleProtSvr::THandleFunc CNewGuildBattleProtSvr::_HandleFuncs[] =
{
	&CNewGuildBattleProtSvr::_DoRecv_GetState, //FuncID: 1
	&CNewGuildBattleProtSvr::_DoRecv_GetOwnerHistory, //FuncID: 2
	&CNewGuildBattleProtSvr::_DoRecv_Enter, //FuncID: 3
	&CNewGuildBattleProtSvr::_DoRecv_GateAttackPlayer, //FuncID: 4
	&CNewGuildBattleProtSvr::_DoRecv_BuyPuppet, //FuncID: 5
	&CNewGuildBattleProtSvr::_DoRecv_GetGateInfo, //FuncID: 6
	&CNewGuildBattleProtSvr::_DoRecv_CaveCapture, //FuncID: 7
	&CNewGuildBattleProtSvr::_DoRecv_CaveAttack, //FuncID: 8
	&CNewGuildBattleProtSvr::_DoRecv_CaveRest, //FuncID: 9
	&CNewGuildBattleProtSvr::_DoRecv_GetCaveInfo, //FuncID: 10
	&CNewGuildBattleProtSvr::_DoRecv_ClearDeadCD, //FuncID: 11
	&CNewGuildBattleProtSvr::_DoRecv_Quit, //FuncID: 12
	&CNewGuildBattleProtSvr::_DoRecv_GetGuildRankInfo, //FuncID: 13
	&CNewGuildBattleProtSvr::_DoRecv_GetGuildMemberRankInfo, //FuncID: 14
	&CNewGuildBattleProtSvr::_DoRecv_GetPlayerRankInfo, //FuncID: 15
	&CNewGuildBattleProtSvr::_DoRecv_CallMember, //FuncID: 16
};

bool CNewGuildBattleProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：状态变更广播
bool CNewGuildBattleProtSvr::Send_StateNotify(
	ENGBState eState, //当前帮派战状态
	UINT32 dwRemainTime, //新帮派战剩余时间
	const TVecMountainPanelInfo& vecInfo //各个灵山信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eState << dwRemainTime << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_StateNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	ENGBState eState, //当前帮派战状态
	UINT32 dwRemainTime, //新帮派战剩余时间
	const TVecMountainPanelInfo& vecInfo //各个灵山信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eState << dwRemainTime << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_StateNotify(
	ENGBState eState, //当前帮派战状态
	UINT32 dwRemainTime, //新帮派战剩余时间
	const TVecMountainPanelInfo& vecInfo //各个灵山信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eState << dwRemainTime << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：城门战广播
bool CNewGuildBattleProtSvr::Send_GateInfoNotify(
	const SMountainGateInfo& sInfo //城门信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << sInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_GateInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const SMountainGateInfo& sInfo //城门信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << sInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_GateInfoNotify(
	const SMountainGateInfo& sInfo //城门信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << sInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：城门战列表通知
bool CNewGuildBattleProtSvr::Send_GateListNotify(
	const TVecPlayerPanelInfo& vecInfo //城门玩家列表信息通知
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_GateListNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecPlayerPanelInfo& vecInfo //城门玩家列表信息通知
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_GateListNotify(
	const TVecPlayerPanelInfo& vecInfo //城门玩家列表信息通知
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：城门被攻破广播
bool CNewGuildBattleProtSvr::Send_GateBrokenNotify(
	ENGBMountain eMountainType, //灵山类型
	const TVecUINT64& vecAttackGuildID //（洞府战）攻击帮派ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eMountainType << vecAttackGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_GateBrokenNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	ENGBMountain eMountainType, //灵山类型
	const TVecUINT64& vecAttackGuildID //（洞府战）攻击帮派ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eMountainType << vecAttackGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_GateBrokenNotify(
	ENGBMountain eMountainType, //灵山类型
	const TVecUINT64& vecAttackGuildID //（洞府战）攻击帮派ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eMountainType << vecAttackGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：洞府战广播
bool CNewGuildBattleProtSvr::Send_CaveInfoNotify(
	const SCaveInfo& sInfo //洞府具体信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << sInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_CaveInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const SCaveInfo& sInfo //洞府具体信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << sInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_CaveInfoNotify(
	const SCaveInfo& sInfo //洞府具体信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << sInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：洞府战列表通知
bool CNewGuildBattleProtSvr::Send_CaveListNotify(
	const TVecPlayerPanelInfo& vecInfo //洞府玩家列表信息通知
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_CaveListNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecPlayerPanelInfo& vecInfo //洞府玩家列表信息通知
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_CaveListNotify(
	const TVecPlayerPanelInfo& vecInfo //洞府玩家列表信息通知
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：洞府战阵眼信息通知
bool CNewGuildBattleProtSvr::Send_CaveCoreNotify(
	const TVecCaveCoreInfo& vecCaveCoreInfo //阵眼信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << vecCaveCoreInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_CaveCoreNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecCaveCoreInfo& vecCaveCoreInfo //阵眼信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << vecCaveCoreInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_CaveCoreNotify(
	const TVecCaveCoreInfo& vecCaveCoreInfo //阵眼信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << vecCaveCoreInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：洞府战被占领通知
bool CNewGuildBattleProtSvr::Send_CaveCapture(
	ENGBMountain eMountainType, //灵山类型
	const std::string& strGuildName //当前占领帮派名称
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eMountainType << strGuildName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_CaveCapture(const UINT64* pUsrID_, UINT16 wCnt_,
	ENGBMountain eMountainType, //灵山类型
	const std::string& strGuildName //当前占领帮派名称
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eMountainType << strGuildName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_CaveCapture(
	ENGBMountain eMountainType, //灵山类型
	const std::string& strGuildName //当前占领帮派名称
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eMountainType << strGuildName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：战斗日志通知
bool CNewGuildBattleProtSvr::Send_BattleLogNotify(
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr //聊天信息参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID << vecStr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_BattleLogNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr //聊天信息参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID << vecStr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_BattleLogNotify(
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr //聊天信息参数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << wMsgID << vecStr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：战斗日志通知
bool CNewGuildBattleProtSvr::Send_PuppetAttackNotify(
	UINT8 byIndex //所属站位(0,1,2; 0为系统战争傀儡)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << byIndex;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_PuppetAttackNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byIndex //所属站位(0,1,2; 0为系统战争傀儡)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << byIndex;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_PuppetAttackNotify(
	UINT8 byIndex //所属站位(0,1,2; 0为系统战争傀儡)
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << byIndex;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：战功榜帮派排名信息广播
bool CNewGuildBattleProtSvr::Send_GuildRankInfoNotify(
	UINT32 dwMaxCount, //最大排名数量
	UINT32 dwCurIndex, //当前排名索引
	const TVecGuildRankInfo& vecInfo //排名信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwMaxCount << dwCurIndex << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_GuildRankInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwMaxCount, //最大排名数量
	UINT32 dwCurIndex, //当前排名索引
	const TVecGuildRankInfo& vecInfo //排名信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwMaxCount << dwCurIndex << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_GuildRankInfoNotify(
	UINT32 dwMaxCount, //最大排名数量
	UINT32 dwCurIndex, //当前排名索引
	const TVecGuildRankInfo& vecInfo //排名信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwMaxCount << dwCurIndex << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 11";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：战功榜帮派成员排名信息广播
bool CNewGuildBattleProtSvr::Send_GuildMemberRankInfoNotify(
	UINT32 dwMaxCount, //最大排名数量
	UINT32 dwCurIndex, //当前排名索引
	const TVecGuildMemberRankInfo& vecInfo //排名信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << dwMaxCount << dwCurIndex << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_GuildMemberRankInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwMaxCount, //最大排名数量
	UINT32 dwCurIndex, //当前排名索引
	const TVecGuildMemberRankInfo& vecInfo //排名信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << dwMaxCount << dwCurIndex << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_GuildMemberRankInfoNotify(
	UINT32 dwMaxCount, //最大排名数量
	UINT32 dwCurIndex, //当前排名索引
	const TVecGuildMemberRankInfo& vecInfo //排名信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << dwMaxCount << dwCurIndex << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 12";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：战功榜个人排名信息广播
bool CNewGuildBattleProtSvr::Send_PlayerRankInfoNotify(
	UINT32 dwMaxCount, //最大排名数量
	UINT32 dwCurIndex, //当前排名索引
	const TVecPlayerRankInfo& vecInfo //排名信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << dwMaxCount << dwCurIndex << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_PlayerRankInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwMaxCount, //最大排名数量
	UINT32 dwCurIndex, //当前排名索引
	const TVecPlayerRankInfo& vecInfo //排名信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << dwMaxCount << dwCurIndex << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_PlayerRankInfoNotify(
	UINT32 dwMaxCount, //最大排名数量
	UINT32 dwCurIndex, //当前排名索引
	const TVecPlayerRankInfo& vecInfo //排名信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << dwMaxCount << dwCurIndex << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 13";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：召集帮众广播
bool CNewGuildBattleProtSvr::Send_CallMemberNotify(
	UINT8 byQuality, //品质
	const std::string& strName //名字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << byQuality << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 68, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CNewGuildBattleProtSvr::SendClt_CallMemberNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byQuality, //品质
	const std::string& strName //名字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << byQuality << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 68, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CNewGuildBattleProtSvr::BuildPkg_CallMemberNotify(
	UINT8 byQuality, //品质
	const std::string& strName //名字
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << byQuality << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 68, Function: 14";
		_strPkg.clear();
	}
	return _strPkg;
}

CNewGuildBattleProtSvr::SGetStateAck::SGetStateAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eState((ENGBState)0), dwRemainTime(0), eMountainType((ENGBMountain)0) { }

void CNewGuildBattleProtSvr::SGetStateAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eState << dwRemainTime << vecInfo << (UINT8&)eMountainType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_GetState(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 1";
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

CNewGuildBattleProtSvr::SGetOwnerHistoryAck::SGetOwnerHistoryAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CNewGuildBattleProtSvr::SGetOwnerHistoryAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_GetOwnerHistory(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	ENGBMountain eMountainType = (ENGBMountain)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eMountainType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetOwnerHistoryAck> fnAck_(new SGetOwnerHistoryAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetOwnerHistory(eMountainType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CNewGuildBattleProtSvr::SEnterAck::SEnterAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBEnterResult)0), eState((ENGBMountainState)0) { }

void CNewGuildBattleProtSvr::SEnterAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << (UINT8&)eState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_Enter(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	ENGBMountain eMountainType = (ENGBMountain)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eMountainType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SEnterAck> fnAck_(new SEnterAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_Enter(eMountainType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CNewGuildBattleProtSvr::SGateAttackPlayerAck::SGateAttackPlayerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBGateAttackResult)0) { }

void CNewGuildBattleProtSvr::SGateAttackPlayerAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_GateAttackPlayer(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwTargetRoleID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwTargetRoleID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGateAttackPlayerAck> fnAck_(new SGateAttackPlayerAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GateAttackPlayer(qwTargetRoleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CNewGuildBattleProtSvr::SBuyPuppetAck::SBuyPuppetAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBBuyPuppetResult)0) { }

void CNewGuildBattleProtSvr::SBuyPuppetAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_BuyPuppet(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBuyPuppetAck> fnAck_(new SBuyPuppetAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BuyPuppet(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CNewGuildBattleProtSvr::SGetGateInfoAck::SGetGateInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBResult)0) { }

void CNewGuildBattleProtSvr::SGetGateInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << sInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_GetGateInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetGateInfoAck> fnAck_(new SGetGateInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetGateInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CNewGuildBattleProtSvr::SCaveCaptureAck::SCaveCaptureAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBCaveAttackResult)0) { }

void CNewGuildBattleProtSvr::SCaveCaptureAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_CaveCapture(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	ENGBCaveCore eCaveType = (ENGBCaveCore)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eCaveType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SCaveCaptureAck> fnAck_(new SCaveCaptureAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_CaveCapture(eCaveType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CNewGuildBattleProtSvr::SCaveAttackAck::SCaveAttackAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBCaveAttackResult)0) { }

void CNewGuildBattleProtSvr::SCaveAttackAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_CaveAttack(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwTargetRoleID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwTargetRoleID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SCaveAttackAck> fnAck_(new SCaveAttackAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_CaveAttack(qwTargetRoleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CNewGuildBattleProtSvr::SCaveRestAck::SCaveRestAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBCaveAttackResult)0) { }

void CNewGuildBattleProtSvr::SCaveRestAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 9";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_CaveRest(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 9";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SCaveRestAck> fnAck_(new SCaveRestAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_CaveRest(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CNewGuildBattleProtSvr::SGetCaveInfoAck::SGetCaveInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBResult)0) { }

void CNewGuildBattleProtSvr::SGetCaveInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -10;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << sInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_GetCaveInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 10";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetCaveInfoAck> fnAck_(new SGetCaveInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetCaveInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CNewGuildBattleProtSvr::SClearDeadCDAck::SClearDeadCDAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBClearDeadCDResult)0) { }

void CNewGuildBattleProtSvr::SClearDeadCDAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -11;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 11";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_ClearDeadCD(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 11";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SClearDeadCDAck> fnAck_(new SClearDeadCDAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ClearDeadCD(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CNewGuildBattleProtSvr::SQuitAck::SQuitAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBQuitResult)0) { }

void CNewGuildBattleProtSvr::SQuitAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 12";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_Quit(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 12";
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

CNewGuildBattleProtSvr::SGetGuildRankInfoAck::SGetGuildRankInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBResult)0), dwMaxCount(0), dwCurIndex(0) { }

void CNewGuildBattleProtSvr::SGetGuildRankInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -13;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << dwMaxCount << dwCurIndex << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 13";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_GetGuildRankInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwIndex = 0;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwIndex >> dwCount;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 13";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetGuildRankInfoAck> fnAck_(new SGetGuildRankInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetGuildRankInfo(dwIndex, dwCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CNewGuildBattleProtSvr::SGetGuildMemberRankInfoAck::SGetGuildMemberRankInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBResult)0), dwMaxCount(0), dwCurIndex(0) { }

void CNewGuildBattleProtSvr::SGetGuildMemberRankInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -14;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << dwMaxCount << dwCurIndex << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 14";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_GetGuildMemberRankInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwIndex = 0;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwIndex >> dwCount;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 14";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetGuildMemberRankInfoAck> fnAck_(new SGetGuildMemberRankInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetGuildMemberRankInfo(dwIndex, dwCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CNewGuildBattleProtSvr::SGetPlayerRankInfoAck::SGetPlayerRankInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBResult)0), dwMaxCount(0), dwCurIndex(0) { }

void CNewGuildBattleProtSvr::SGetPlayerRankInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -15;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << dwMaxCount << dwCurIndex << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 15";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_GetPlayerRankInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwIndex = 0;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwIndex >> dwCount;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 15";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetPlayerRankInfoAck> fnAck_(new SGetPlayerRankInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetPlayerRankInfo(dwIndex, dwCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CNewGuildBattleProtSvr::SCallMemberAck::SCallMemberAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ENGBResult)0) { }

void CNewGuildBattleProtSvr::SCallMemberAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -16;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 68, Function: 16";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CNewGuildBattleProtSvr::_DoRecv_CallMember(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 68, Function: 16";
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

} //namespace NNewGuildBattleProt
