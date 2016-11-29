/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterGuildBattle.cpp
//  Purpose:      帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterGuildBattleClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterGuildBattle
{

CGame2CenterGuildBattleClt::THandleFunc CGame2CenterGuildBattleClt::_ReturnFuncs[] =
{
	&CGame2CenterGuildBattleClt::_DoReturn_UserSignUp, //FuncID: -1
	&CGame2CenterGuildBattleClt::_DoReturn_GetAuthority, //FuncID: -2
	&CGame2CenterGuildBattleClt::_DoReturn_GetPanelInfo, //FuncID: -3
	&CGame2CenterGuildBattleClt::_DoReturn_NewGetGuildID, //FuncID: -4
};

CGame2CenterGuildBattleClt::THandleFunc CGame2CenterGuildBattleClt::_HandleFuncs[] =
{
	&CGame2CenterGuildBattleClt::_DoRecv_GuildLevelChanged, //FuncID: 1
	&CGame2CenterGuildBattleClt::_DoRecv_GuildOwnerChanged, //FuncID: 2
	&CGame2CenterGuildBattleClt::_DoRecv_GuildDisband, //FuncID: 3
	&CGame2CenterGuildBattleClt::_DoRecv_ReadyToSendNewGuildBattle, //FuncID: 4
};

CGame2CenterGuildBattleClt::TTimeOutFunc CGame2CenterGuildBattleClt::_TimeoutFuncs[] =
{
	&CGame2CenterGuildBattleClt::_OnTimeOut_UserSignUp, //FuncID: 1
	&CGame2CenterGuildBattleClt::_OnTimeOut_GetAuthority, //FuncID: 2
	&CGame2CenterGuildBattleClt::_OnTimeOut_GetPanelInfo, //FuncID: 3
	&CGame2CenterGuildBattleClt::_OnTimeOut_NewGetGuildID, //FuncID: 4
};

bool CGame2CenterGuildBattleClt::HandleMessage(const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return false;
	INT8 byFuncID = pBuf[0];
	if(byFuncID == 0 || byFuncID > (INT8)ARRAYSIZE(_HandleFuncs)
		 || byFuncID < -(INT8)ARRAYSIZE(_ReturnFuncs))
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
	else
	{
		byFuncID = -1 - byFuncID;
		if(_ReturnFuncs[static_cast<UINT8>(byFuncID)] != NULL)
			return (this->*_ReturnFuncs[static_cast<UINT8>(byFuncID)])(pBuf, dwLen);
	}
	return true;
}

void CGame2CenterGuildBattleClt::OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID)
{
	if(byFuncID == 0 || byFuncID > (UINT8)ARRAYSIZE(_TimeoutFuncs))
		return;
	(this->*_TimeoutFuncs[byFuncID - 1])(dwSessionID);
}

//发送：帮派战状态设定
bool CGame2CenterGuildBattleClt::Send_SetState(
	NGuildBattleProt::EGBState eState //当前帮派战状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleClt::SendSvr_SetState(const UINT32* pSvrID_, UINT8 byCnt_,
	NGuildBattleProt::EGBState eState //当前帮派战状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterGuildBattleClt::BuildPkg_SetState(
	NGuildBattleProt::EGBState eState //当前帮派战状态
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 77, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮派战用户报名
bool CGame2CenterGuildBattleClt::Send_UserSignUp(
	UINT64 qwRoleID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwGuildID, //(返回值)帮派ID
		UINT16 wLevel, //(返回值)帮派等级
		const std::string& strGuildName, //(返回值)帮派名称
		UINT32 dwScore, //(返回值)帮派战积分
		NGuildBattleProt::EGBSignUpResult eResult //(返回值)玩家报名结果
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 1);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleClt::SendSvr_UserSignUp(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwGuildID, //(返回值)帮派ID
		UINT16 wLevel, //(返回值)帮派等级
		const std::string& strGuildName, //(返回值)帮派名称
		UINT32 dwScore, //(返回值)帮派战积分
		NGuildBattleProt::EGBSignUpResult eResult //(返回值)玩家报名结果
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 1);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：帮派战相关广播
bool CGame2CenterGuildBattleClt::Send_InfoNotify(
	UINT64 qwGuildID, //帮派对应ID
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr //聊天信息参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << wMsgID << vecStr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleClt::SendSvr_InfoNotify(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwGuildID, //帮派对应ID
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr //聊天信息参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << wMsgID << vecStr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterGuildBattleClt::BuildPkg_InfoNotify(
	UINT64 qwGuildID, //帮派对应ID
	UINT16 wMsgID, //消息ID
	const TVecString& vecStr //聊天信息参数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << wMsgID << vecStr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 77, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：是否有帮派战操作权限
bool CGame2CenterGuildBattleClt::Send_GetAuthority(
	UINT64 qwRoleID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		bool bHasAuthority //(返回值)是否有帮派战操作权限
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 2);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleClt::SendSvr_GetAuthority(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		bool bHasAuthority //(返回值)是否有帮派战操作权限
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 2);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：增加帮派战积分
bool CGame2CenterGuildBattleClt::Send_AddScore(
	UINT64 qwGuildID, //帮派ID
	UINT32 dwScore, //帮派战积分
	const TVecMemberScore& vecMemberScore //玩家获得积分
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << dwScore << vecMemberScore;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleClt::SendSvr_AddScore(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwGuildID, //帮派ID
	UINT32 dwScore, //帮派战积分
	const TVecMemberScore& vecMemberScore //玩家获得积分
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << dwScore << vecMemberScore;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterGuildBattleClt::BuildPkg_AddScore(
	UINT64 qwGuildID, //帮派ID
	UINT32 dwScore, //帮派战积分
	const TVecMemberScore& vecMemberScore //玩家获得积分
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << dwScore << vecMemberScore;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 77, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加帮派战帮派积分
bool CGame2CenterGuildBattleClt::Send_AddGuildScore(
	UINT64 qwGuildID, //帮派ID
	UINT32 dwScore //帮派战积分
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << dwScore;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleClt::SendSvr_AddGuildScore(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwGuildID, //帮派ID
	UINT32 dwScore //帮派战积分
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << dwScore;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterGuildBattleClt::BuildPkg_AddGuildScore(
	UINT64 qwGuildID, //帮派ID
	UINT32 dwScore //帮派战积分
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << dwScore;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 77, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加帮派战成员积分
bool CGame2CenterGuildBattleClt::Send_AddMemberScore(
	UINT64 qwGuildID, //帮派ID
	const TVecMemberScore& vecMemberScore //玩家获得积分
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << vecMemberScore;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleClt::SendSvr_AddMemberScore(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwGuildID, //帮派ID
	const TVecMemberScore& vecMemberScore //玩家获得积分
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << vecMemberScore;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterGuildBattleClt::BuildPkg_AddMemberScore(
	UINT64 qwGuildID, //帮派ID
	const TVecMemberScore& vecMemberScore //玩家获得积分
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << vecMemberScore;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 77, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取帮派战相关面板信息
bool CGame2CenterGuildBattleClt::Send_GetPanelInfo(
	UINT64 qwRoleID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT32 dwSelfScore, //(返回值)我的积分
		UINT32 dwGuildScore, //(返回值)帮派积分
		UINT32 dwGuildRank //(返回值)帮派排名
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 3);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleClt::SendSvr_GetPanelInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT32 dwSelfScore, //(返回值)我的积分
		UINT32 dwGuildScore, //(返回值)帮派积分
		UINT32 dwGuildRank //(返回值)帮派排名
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 3);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：更新帮派战积分排名
bool CGame2CenterGuildBattleClt::Send_SyncGuildRank(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleClt::SendSvr_SyncGuildRank(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterGuildBattleClt::BuildPkg_SyncGuildRank(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 77, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮派战状态设定
bool CGame2CenterGuildBattleClt::Send_NewSetState(
	NNewGuildBattleProt::ENGBState eState //当前帮派战状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleClt::SendSvr_NewSetState(const UINT32* pSvrID_, UINT8 byCnt_,
	NNewGuildBattleProt::ENGBState eState //当前帮派战状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterGuildBattleClt::BuildPkg_NewSetState(
	NNewGuildBattleProt::ENGBState eState //当前帮派战状态
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 77, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取帮派ID
bool CGame2CenterGuildBattleClt::Send_NewGetGuildID(
	UINT64 qwRoleID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwGuildID, //(返回值)帮派ID
		const std::string& strGuildName, //(返回值)帮派名称
		UINT8 byGuildLvl //(返回值)帮派等级
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 4);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleClt::SendSvr_NewGetGuildID(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwGuildID, //(返回值)帮派ID
		const std::string& strGuildName, //(返回值)帮派名称
		UINT8 byGuildLvl //(返回值)帮派等级
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 4);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleClt::_DoRecv_GuildLevelChanged(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwGuildID = 0;
	UINT16 wLevel = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwGuildID >> wLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 77, Function: 1";
		return false;
	}
	OnRecv_GuildLevelChanged(qwGuildID, wLevel);
	return true;
}

bool CGame2CenterGuildBattleClt::_DoRecv_GuildOwnerChanged(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwGuildID = 0;
	std::string strGuildOwnerName;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwGuildID >> strGuildOwnerName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 77, Function: 2";
		return false;
	}
	OnRecv_GuildOwnerChanged(qwGuildID, strGuildOwnerName);
	return true;
}

bool CGame2CenterGuildBattleClt::_DoRecv_GuildDisband(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwGuildID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 77, Function: 3";
		return false;
	}
	OnRecv_GuildDisband(qwGuildID);
	return true;
}

bool CGame2CenterGuildBattleClt::_DoRecv_ReadyToSendNewGuildBattle(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_ReadyToSendNewGuildBattle();
	return true;
}

bool CGame2CenterGuildBattleClt::_DoReturn_UserSignUp(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT64 qwGuildID = 0;
	UINT16 wLevel = 0;
	std::string strGuildName;
	UINT32 dwScore = 0;
	NGuildBattleProt::EGBSignUpResult eResult = (NGuildBattleProt::EGBSignUpResult)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> qwGuildID >> wLevel >> strGuildName >> dwScore >> (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 77, Function: 2";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwGuildID, //(返回值)帮派ID
		UINT16 wLevel, //(返回值)帮派等级
		const std::string& strGuildName, //(返回值)帮派名称
		UINT32 dwScore, //(返回值)帮派战积分
		NGuildBattleProt::EGBSignUpResult eResult //(返回值)玩家报名结果
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, qwGuildID, wLevel, strGuildName, dwScore, eResult);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterGuildBattleClt::_OnTimeOut_UserSignUp(UINT32 dwSessionID)
{
	UINT64 qwGuildID = 0;
	UINT16 wLevel = 0;
	std::string strGuildName;
	UINT32 dwScore = 0;
	NGuildBattleProt::EGBSignUpResult eResult = (NGuildBattleProt::EGBSignUpResult)0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwGuildID, //(返回值)帮派ID
		UINT16 wLevel, //(返回值)帮派等级
		const std::string& strGuildName, //(返回值)帮派名称
		UINT32 dwScore, //(返回值)帮派战积分
		NGuildBattleProt::EGBSignUpResult eResult //(返回值)玩家报名结果
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, qwGuildID, wLevel, strGuildName, dwScore, eResult);
}

bool CGame2CenterGuildBattleClt::_DoReturn_GetAuthority(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	bool bHasAuthority = false;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> bHasAuthority;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 77, Function: 4";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		bool bHasAuthority //(返回值)是否有帮派战操作权限
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, bHasAuthority);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterGuildBattleClt::_OnTimeOut_GetAuthority(UINT32 dwSessionID)
{
	bool bHasAuthority = false;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		bool bHasAuthority //(返回值)是否有帮派战操作权限
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, bHasAuthority);
}

bool CGame2CenterGuildBattleClt::_DoReturn_GetPanelInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT32 dwSelfScore = 0;
	UINT32 dwGuildScore = 0;
	UINT32 dwGuildRank = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> dwSelfScore >> dwGuildScore >> dwGuildRank;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 77, Function: 8";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT32 dwSelfScore, //(返回值)我的积分
		UINT32 dwGuildScore, //(返回值)帮派积分
		UINT32 dwGuildRank //(返回值)帮派排名
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, dwSelfScore, dwGuildScore, dwGuildRank);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterGuildBattleClt::_OnTimeOut_GetPanelInfo(UINT32 dwSessionID)
{
	UINT32 dwSelfScore = 0;
	UINT32 dwGuildScore = 0;
	UINT32 dwGuildRank = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT32 dwSelfScore, //(返回值)我的积分
		UINT32 dwGuildScore, //(返回值)帮派积分
		UINT32 dwGuildRank //(返回值)帮派排名
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, dwSelfScore, dwGuildScore, dwGuildRank);
}

bool CGame2CenterGuildBattleClt::_DoReturn_NewGetGuildID(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT64 qwGuildID = 0;
	std::string strGuildName;
	UINT8 byGuildLvl = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> qwGuildID >> strGuildName >> byGuildLvl;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 77, Function: 11";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwGuildID, //(返回值)帮派ID
		const std::string& strGuildName, //(返回值)帮派名称
		UINT8 byGuildLvl //(返回值)帮派等级
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, qwGuildID, strGuildName, byGuildLvl);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterGuildBattleClt::_OnTimeOut_NewGetGuildID(UINT32 dwSessionID)
{
	UINT64 qwGuildID = 0;
	std::string strGuildName;
	UINT8 byGuildLvl = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwGuildID, //(返回值)帮派ID
		const std::string& strGuildName, //(返回值)帮派名称
		UINT8 byGuildLvl //(返回值)帮派等级
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, qwGuildID, strGuildName, byGuildLvl);
}

} //namespace NGame2CenterGuildBattle
