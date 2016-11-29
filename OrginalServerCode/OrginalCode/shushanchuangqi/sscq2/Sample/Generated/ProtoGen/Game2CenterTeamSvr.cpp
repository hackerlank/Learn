/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterTeam.cpp
//  Purpose:      GameServer到CenterServer关于Team的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterTeamSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterTeam
{

CGame2CenterTeamSvr::THandleFunc CGame2CenterTeamSvr::_ReturnFuncs[] =
{
	&CGame2CenterTeamSvr::_DoReturn_CanEnterCreateTeam, //FuncID: -1
	&CGame2CenterTeamSvr::_DoReturn_GetFighterFeatureByInsID, //FuncID: -2
	&CGame2CenterTeamSvr::_DoReturn_GetPlayerBattleInfo, //FuncID: -3
	&CGame2CenterTeamSvr::_DoReturn_StartBattle, //FuncID: -4
};

CGame2CenterTeamSvr::THandleFunc CGame2CenterTeamSvr::_HandleFuncs[] =
{
	&CGame2CenterTeamSvr::_DoRecv_SynTeamFighter, //FuncID: 1
	&CGame2CenterTeamSvr::_DoRecv_SynTeamAddBeauty, //FuncID: 2
	&CGame2CenterTeamSvr::_DoRecv_SynTeamDelBeauty, //FuncID: 3
	&CGame2CenterTeamSvr::_DoRecv_SynRewardRate, //FuncID: 4
};

CGame2CenterTeamSvr::TTimeOutFunc CGame2CenterTeamSvr::_TimeoutFuncs[] =
{
	&CGame2CenterTeamSvr::_OnTimeOut_CanEnterCreateTeam, //FuncID: 1
	&CGame2CenterTeamSvr::_OnTimeOut_GetFighterFeatureByInsID, //FuncID: 2
	&CGame2CenterTeamSvr::_OnTimeOut_GetPlayerBattleInfo, //FuncID: 3
	&CGame2CenterTeamSvr::_OnTimeOut_StartBattle, //FuncID: 4
};

bool CGame2CenterTeamSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

void CGame2CenterTeamSvr::OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID)
{
	if(byFuncID == 0 || byFuncID > (UINT8)ARRAYSIZE(_TimeoutFuncs))
		return;
	(this->*_TimeoutFuncs[byFuncID - 1])(dwSessionID);
}

//发送：玩家请求加入，创建队伍
bool CGame2CenterTeamSvr::Send_CanEnterCreateTeam(
	UINT64 qwUsrID, //帐号ID
	UINT8 byHeroNum, //0,不需要将，>0，需要主将，散仙数量：byHeroNum，美女
	UINT16 wDgnType, //副本模板
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NTeamGS::ETEAMResult eResult, //(返回值)操作结果
		const NTeamGS::TVecTeamFighter& vecFighter //(返回值)获取战斗对象
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
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << byHeroNum << wDgnType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 57, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterTeamSvr::SendSvr_CanEnterCreateTeam(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT8 byHeroNum, //0,不需要将，>0，需要主将，散仙数量：byHeroNum，美女
	UINT16 wDgnType, //副本模板
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NTeamGS::ETEAMResult eResult, //(返回值)操作结果
		const NTeamGS::TVecTeamFighter& vecFighter //(返回值)获取战斗对象
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
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << byHeroNum << wDgnType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 57, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：玩家加入/离开队伍信息同步
bool CGame2CenterTeamSvr::Send_SynTeam(
	UINT64 qwUsrID, //帐号ID
	EPlayerTeam eStatus //玩家操作
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 57, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterTeamSvr::SendSvr_SynTeam(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	EPlayerTeam eStatus //玩家操作
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 57, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterTeamSvr::BuildPkg_SynTeam(
	UINT64 qwUsrID, //帐号ID
	EPlayerTeam eStatus //玩家操作
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 57, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：根据实例拉取将外观
bool CGame2CenterTeamSvr::Send_GetFighterFeatureByInsID(
	UINT64 qwUsrID, //帐号ID
	UINT64 qwFighterID, //将ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NTeamGS::CommonFighter& stFighter //(返回值)获取战斗对象
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
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << qwFighterID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 57, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterTeamSvr::SendSvr_GetFighterFeatureByInsID(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT64 qwFighterID, //将ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NTeamGS::CommonFighter& stFighter //(返回值)获取战斗对象
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
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << qwFighterID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 57, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：获取玩家战斗信息
bool CGame2CenterTeamSvr::Send_GetPlayerBattleInfo(
	UINT64 qwUsrID, //帐号ID
	UINT8 byPlayerPos, //玩家所在的队伍位置
	const TVecUINT64& vecFigther, //散仙唯一ID
	const TVecUINT8& vecPos, //玩家序列位置
	UINT8 byNeedBeauty, //0,不需要美女，1需要美女
	UINT16 wDgnType, //副本类型
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NTeamGS::ETEAMResult eResult, //(返回值)操作结果
		const NBattleGS::TVecBattleFighter& vecFighter //(返回值)战斗对象
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
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << byPlayerPos << vecFigther << vecPos << byNeedBeauty << wDgnType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 57, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterTeamSvr::SendSvr_GetPlayerBattleInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT8 byPlayerPos, //玩家所在的队伍位置
	const TVecUINT64& vecFigther, //散仙唯一ID
	const TVecUINT8& vecPos, //玩家序列位置
	UINT8 byNeedBeauty, //0,不需要美女，1需要美女
	UINT16 wDgnType, //副本类型
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NTeamGS::ETEAMResult eResult, //(返回值)操作结果
		const NBattleGS::TVecBattleFighter& vecFighter //(返回值)战斗对象
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
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << byPlayerPos << vecFigther << vecPos << byNeedBeauty << wDgnType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 57, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：请求发起战斗
bool CGame2CenterTeamSvr::Send_StartBattle(
	UINT64 qwUsrID, //队长ID
	UINT16 wDgnType, //副本类型
	const NBattleGS::TVecBattleFighter& vecFighter, //其他服战斗对象
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TeamReport& stTeamReport //(返回值)通告战斗结果
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
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << wDgnType << vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 57, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterTeamSvr::SendSvr_StartBattle(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //队长ID
	UINT16 wDgnType, //副本类型
	const NBattleGS::TVecBattleFighter& vecFighter, //其他服战斗对象
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TeamReport& stTeamReport //(返回值)通告战斗结果
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
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << wDgnType << vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 57, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：通告战斗结果
bool CGame2CenterTeamSvr::Send_NoticeTeamReport(
	UINT64 qwUsrID, //帐号ID
	UINT16 wDgnType, //副本类型
	const TeamReport& stTeamReport, //副本类型
	UINT32 dwRewardRate //奖励系数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << wDgnType << stTeamReport << dwRewardRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 57, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterTeamSvr::SendSvr_NoticeTeamReport(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT16 wDgnType, //副本类型
	const TeamReport& stTeamReport, //副本类型
	UINT32 dwRewardRate //奖励系数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << wDgnType << stTeamReport << dwRewardRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 57, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterTeamSvr::BuildPkg_NoticeTeamReport(
	UINT64 qwUsrID, //帐号ID
	UINT16 wDgnType, //副本类型
	const TeamReport& stTeamReport, //副本类型
	UINT32 dwRewardRate //奖励系数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << wDgnType << stTeamReport << dwRewardRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 57, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CGame2CenterTeamSvr::_DoRecv_SynTeamFighter(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	NTeamGS::TVecTeamFighter vecFighter;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 57, Function: 1";
		return false;
	}
	OnRecv_SynTeamFighter(qwUsrID, vecFighter);
	return true;
}

bool CGame2CenterTeamSvr::_DoRecv_SynTeamAddBeauty(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	NTeamGS::TVecTeamFighter vecFighter;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 57, Function: 2";
		return false;
	}
	OnRecv_SynTeamAddBeauty(qwUsrID, vecFighter);
	return true;
}

bool CGame2CenterTeamSvr::_DoRecv_SynTeamDelBeauty(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 57, Function: 3";
		return false;
	}
	OnRecv_SynTeamDelBeauty(qwUsrID);
	return true;
}

bool CGame2CenterTeamSvr::_DoRecv_SynRewardRate(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwRewardRate = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwRewardRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 57, Function: 4";
		return false;
	}
	OnRecv_SynRewardRate(dwRewardRate);
	return true;
}

bool CGame2CenterTeamSvr::_DoReturn_CanEnterCreateTeam(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NTeamGS::ETEAMResult eResult = (NTeamGS::ETEAMResult)0;
	NTeamGS::TVecTeamFighter vecFighter;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> (UINT8&)eResult >> vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 57, Function: 1";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NTeamGS::ETEAMResult eResult, //(返回值)操作结果
		const NTeamGS::TVecTeamFighter& vecFighter //(返回值)获取战斗对象
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, eResult, vecFighter);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterTeamSvr::_OnTimeOut_CanEnterCreateTeam(UINT32 dwSessionID)
{
	NTeamGS::ETEAMResult eResult = (NTeamGS::ETEAMResult)0;
	NTeamGS::TVecTeamFighter vecFighter;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NTeamGS::ETEAMResult eResult, //(返回值)操作结果
		const NTeamGS::TVecTeamFighter& vecFighter //(返回值)获取战斗对象
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, eResult, vecFighter);
}

bool CGame2CenterTeamSvr::_DoReturn_GetFighterFeatureByInsID(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NTeamGS::CommonFighter stFighter;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> stFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 57, Function: 3";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NTeamGS::CommonFighter& stFighter //(返回值)获取战斗对象
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, stFighter);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterTeamSvr::_OnTimeOut_GetFighterFeatureByInsID(UINT32 dwSessionID)
{
	NTeamGS::CommonFighter stFighter;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NTeamGS::CommonFighter& stFighter //(返回值)获取战斗对象
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, stFighter);
}

bool CGame2CenterTeamSvr::_DoReturn_GetPlayerBattleInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NTeamGS::ETEAMResult eResult = (NTeamGS::ETEAMResult)0;
	NBattleGS::TVecBattleFighter vecFighter;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> (UINT8&)eResult >> vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 57, Function: 4";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NTeamGS::ETEAMResult eResult, //(返回值)操作结果
		const NBattleGS::TVecBattleFighter& vecFighter //(返回值)战斗对象
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, eResult, vecFighter);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterTeamSvr::_OnTimeOut_GetPlayerBattleInfo(UINT32 dwSessionID)
{
	NTeamGS::ETEAMResult eResult = (NTeamGS::ETEAMResult)0;
	NBattleGS::TVecBattleFighter vecFighter;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NTeamGS::ETEAMResult eResult, //(返回值)操作结果
		const NBattleGS::TVecBattleFighter& vecFighter //(返回值)战斗对象
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, eResult, vecFighter);
}

bool CGame2CenterTeamSvr::_DoReturn_StartBattle(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	TeamReport stTeamReport;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> stTeamReport;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 57, Function: 5";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TeamReport& stTeamReport //(返回值)通告战斗结果
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, stTeamReport);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterTeamSvr::_OnTimeOut_StartBattle(UINT32 dwSessionID)
{
	TeamReport stTeamReport;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TeamReport& stTeamReport //(返回值)通告战斗结果
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, stTeamReport);
}

} //namespace NGame2CenterTeam
