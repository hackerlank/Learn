/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterLog.cpp
//  Purpose:      GameServer到CenterServer的数据中心log协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterLogClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterLog
{

CGame2CenterLogClt::THandleFunc CGame2CenterLogClt::_HandleFuncs[] =
{
	NULL
};

bool CGame2CenterLogClt::HandleMessage(const char* pBuf, UINT32 dwLen)
{
	return true;
}

//发送：log注册记录
bool CGame2CenterLogClt::Send_LogRegister(
	UINT64 qwUsrID, //帐号ID
	const TVecString& vecStrInfo //用户登陆平台信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecStrInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 61, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterLogClt::SendSvr_LogRegister(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	const TVecString& vecStrInfo //用户登陆平台信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecStrInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 61, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterLogClt::BuildPkg_LogRegister(
	UINT64 qwUsrID, //帐号ID
	const TVecString& vecStrInfo //用户登陆平台信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecStrInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 61, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：log登陆
bool CGame2CenterLogClt::Send_LogUserLogin(
	UINT64 qwUsrID, //帐号ID
	const TVecString& vecStrInfo //用户登陆平台信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecStrInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 61, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterLogClt::SendSvr_LogUserLogin(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	const TVecString& vecStrInfo //用户登陆平台信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecStrInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 61, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterLogClt::BuildPkg_LogUserLogin(
	UINT64 qwUsrID, //帐号ID
	const TVecString& vecStrInfo //用户登陆平台信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecStrInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 61, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：log登出
bool CGame2CenterLogClt::Send_LogPlayerLogout(
	UINT32 dwTime, //时间
	UINT64 qwUsrID //帐号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 61, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterLogClt::SendSvr_LogPlayerLogout(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwTime, //时间
	UINT64 qwUsrID //帐号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 61, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterLogClt::BuildPkg_LogPlayerLogout(
	UINT32 dwTime, //时间
	UINT64 qwUsrID //帐号ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 61, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：log玩家充值
bool CGame2CenterLogClt::Send_LogRecharge(
	UINT64 qwUsrID, //帐号ID
	const std::string& strUdp1, //udpLog参数1(平台传来的)
	const std::string& strUdp2, //udpLog参数2(平台传来的)
	UINT32 dwGold //仙石数量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strUdp1 << strUdp2 << dwGold;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 61, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterLogClt::SendSvr_LogRecharge(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	const std::string& strUdp1, //udpLog参数1(平台传来的)
	const std::string& strUdp2, //udpLog参数2(平台传来的)
	UINT32 dwGold //仙石数量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strUdp1 << strUdp2 << dwGold;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 61, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterLogClt::BuildPkg_LogRecharge(
	UINT64 qwUsrID, //帐号ID
	const std::string& strUdp1, //udpLog参数1(平台传来的)
	const std::string& strUdp2, //udpLog参数2(平台传来的)
	UINT32 dwGold //仙石数量
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strUdp1 << strUdp2 << dwGold;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 61, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：log金钱变化
bool CGame2CenterLogClt::Send_LogMoneyChange(
	UINT64 qwUsrID, //帐号ID
	EOpType eType, //类型
	const TVecUserMoneyChange& vecMoney //货币
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eType << vecMoney;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 61, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterLogClt::SendSvr_LogMoneyChange(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	EOpType eType, //类型
	const TVecUserMoneyChange& vecMoney //货币
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eType << vecMoney;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 61, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterLogClt::BuildPkg_LogMoneyChange(
	UINT64 qwUsrID, //帐号ID
	EOpType eType, //类型
	const TVecUserMoneyChange& vecMoney //货币
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eType << vecMoney;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 61, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：log道具变化
bool CGame2CenterLogClt::Send_LogItemChange(
	UINT64 qwUsrID, //帐号ID
	EOpType eType, //类型
	const TVecUserItemChange& vecItem //道具
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eType << vecItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 61, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterLogClt::SendSvr_LogItemChange(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	EOpType eType, //类型
	const TVecUserItemChange& vecItem //道具
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eType << vecItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 61, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterLogClt::BuildPkg_LogItemChange(
	UINT64 qwUsrID, //帐号ID
	EOpType eType, //类型
	const TVecUserItemChange& vecItem //道具
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eType << vecItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 61, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：log新手引导变化
bool CGame2CenterLogClt::Send_LogGuideChange(
	UINT64 qwUsrID, //帐号ID
	const std::string& strCategory, //引导类 load或guide
	const std::string& strStep //引导ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strCategory << strStep;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 61, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterLogClt::SendSvr_LogGuideChange(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	const std::string& strCategory, //引导类 load或guide
	const std::string& strStep //引导ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strCategory << strStep;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 61, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterLogClt::BuildPkg_LogGuideChange(
	UINT64 qwUsrID, //帐号ID
	const std::string& strCategory, //引导类 load或guide
	const std::string& strStep //引导ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strCategory << strStep;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 61, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：log自定义行为变化
bool CGame2CenterLogClt::Send_LogActiveChange(
	UINT64 qwUsrID, //帐号ID
	const std::string& strCategory, //行为分类
	const std::string& strAction, //用户行为
	UINT32 dwCount //
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strCategory << strAction << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 61, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterLogClt::SendSvr_LogActiveChange(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	const std::string& strCategory, //行为分类
	const std::string& strAction, //用户行为
	UINT32 dwCount //
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strCategory << strAction << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 61, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterLogClt::BuildPkg_LogActiveChange(
	UINT64 qwUsrID, //帐号ID
	const std::string& strCategory, //行为分类
	const std::string& strAction, //用户行为
	UINT32 dwCount //
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strCategory << strAction << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 61, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：log自定义行为变化
bool CGame2CenterLogClt::Send_LogAct(
	UINT64 qwUsrID, //帐号ID
	const std::string& strCategory, //行为分类
	const std::string& strAction, //用户行为
	const std::string& strParam3, //用户行为
	const std::string& strParam4, //用户行为
	const std::string& strParam5, //用户行为
	const std::string& strParam6, //用户行为
	UINT32 dwCount //
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strCategory << strAction << strParam3 << strParam4 << strParam5 << strParam6 << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 61, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterLogClt::SendSvr_LogAct(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	const std::string& strCategory, //行为分类
	const std::string& strAction, //用户行为
	const std::string& strParam3, //用户行为
	const std::string& strParam4, //用户行为
	const std::string& strParam5, //用户行为
	const std::string& strParam6, //用户行为
	UINT32 dwCount //
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strCategory << strAction << strParam3 << strParam4 << strParam5 << strParam6 << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 61, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterLogClt::BuildPkg_LogAct(
	UINT64 qwUsrID, //帐号ID
	const std::string& strCategory, //行为分类
	const std::string& strAction, //用户行为
	const std::string& strParam3, //用户行为
	const std::string& strParam4, //用户行为
	const std::string& strParam5, //用户行为
	const std::string& strParam6, //用户行为
	UINT32 dwCount //
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strCategory << strAction << strParam3 << strParam4 << strParam5 << strParam6 << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 61, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：log服务器变化
bool CGame2CenterLogClt::Send_LogServerInfo(
	UINT32 dwTime, //时间
	const std::string& strType, //记录类型
	const std::string& strSubType, //记录分类型
	UINT32 dwNum //记录数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime << strType << strSubType << dwNum;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 61, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterLogClt::SendSvr_LogServerInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwTime, //时间
	const std::string& strType, //记录类型
	const std::string& strSubType, //记录分类型
	UINT32 dwNum //记录数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime << strType << strSubType << dwNum;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 61, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterLogClt::BuildPkg_LogServerInfo(
	UINT32 dwTime, //时间
	const std::string& strType, //记录类型
	const std::string& strSubType, //记录分类型
	UINT32 dwNum //记录数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime << strType << strSubType << dwNum;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 61, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

} //namespace NGame2CenterLog
