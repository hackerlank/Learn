/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterRank.cpp
//  Purpose:      排行榜相关内部协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterRankSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterRank
{

CGame2CenterRankSvr::THandleFunc CGame2CenterRankSvr::_ReturnFuncs[] =
{
	&CGame2CenterRankSvr::_DoReturn_GetFeature, //FuncID: -1
};

CGame2CenterRankSvr::THandleFunc CGame2CenterRankSvr::_HandleFuncs[] =
{
	&CGame2CenterRankSvr::_DoRecv_UpdateRankInfo, //FuncID: 1
	&CGame2CenterRankSvr::_DoRecv_UpdateAllLevelInfo, //FuncID: 2
};

CGame2CenterRankSvr::TTimeOutFunc CGame2CenterRankSvr::_TimeoutFuncs[] =
{
	&CGame2CenterRankSvr::_OnTimeOut_GetFeature, //FuncID: 1
};

bool CGame2CenterRankSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

void CGame2CenterRankSvr::OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID)
{
	if(byFuncID == 0 || byFuncID > (UINT8)ARRAYSIZE(_TimeoutFuncs))
		return;
	(this->*_TimeoutFuncs[byFuncID - 1])(dwSessionID);
}

//发送：获取玩家的外观信息
bool CGame2CenterRankSvr::Send_GetFeature(
	UINT64 qwRoleID, //玩家唯一ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 其他错误
		const std::string& strName, //(返回值)玩家姓名
		UINT16 wLevel, //(返回值)玩家等级
		const NBattleGS::SFeatureBasePtr& pFeature //(返回值)外观信息
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
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 81, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterRankSvr::SendSvr_GetFeature(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家唯一ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 其他错误
		const std::string& strName, //(返回值)玩家姓名
		UINT16 wLevel, //(返回值)玩家等级
		const NBattleGS::SFeatureBasePtr& pFeature //(返回值)外观信息
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
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 81, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

bool CGame2CenterRankSvr::_DoRecv_UpdateRankInfo(const char* pBuf_, UINT32 dwLen_)
{
	NRankProt::ERankType eType = (NRankProt::ERankType)0;
	UINT64 qwInstID = 0;
	NRankProt::TVecRankInfo vecRankInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eType >> qwInstID >> vecRankInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 81, Function: 1";
		return false;
	}
	OnRecv_UpdateRankInfo(eType, qwInstID, vecRankInfo);
	return true;
}

bool CGame2CenterRankSvr::_DoRecv_UpdateAllLevelInfo(const char* pBuf_, UINT32 dwLen_)
{
	TVecUINT64 vecRoleID;
	NRankProt::TVecRankInfo vecRankInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecRoleID >> vecRankInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 81, Function: 2";
		return false;
	}
	OnRecv_UpdateAllLevelInfo(vecRoleID, vecRankInfo);
	return true;
}

bool CGame2CenterRankSvr::_DoReturn_GetFeature(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byError = 0;
	std::string strName;
	UINT16 wLevel = 0;
	NBattleGS::SFeatureBase_Wrapper pFeature;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byError >> strName >> wLevel >> pFeature;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 81, Function: 1";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 其他错误
		const std::string& strName, //(返回值)玩家姓名
		UINT16 wLevel, //(返回值)玩家等级
		const NBattleGS::SFeatureBasePtr& pFeature //(返回值)外观信息
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byError, strName, wLevel, pFeature.ptr);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterRankSvr::_OnTimeOut_GetFeature(UINT32 dwSessionID)
{
	UINT8 byError = 0;
	std::string strName;
	UINT16 wLevel = 0;
	NBattleGS::SFeatureBase_Wrapper pFeature;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 其他错误
		const std::string& strName, //(返回值)玩家姓名
		UINT16 wLevel, //(返回值)玩家等级
		const NBattleGS::SFeatureBasePtr& pFeature //(返回值)外观信息
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byError, strName, wLevel, pFeature.ptr);
}

} //namespace NGame2CenterRank
