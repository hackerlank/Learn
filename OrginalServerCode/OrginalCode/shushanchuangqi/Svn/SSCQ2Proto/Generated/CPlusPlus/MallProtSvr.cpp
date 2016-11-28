/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    MallProt.cpp
//  Purpose:      商城相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "MallProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NMallProt
{

CMallProtSvr::THandleFunc CMallProtSvr::_HandleFuncs[] =
{
	&CMallProtSvr::_DoRecv_MalGet, //FuncID: 1
	&CMallProtSvr::_DoRecv_MalBuy, //FuncID: 2
	&CMallProtSvr::_DoRecv_MallPresent, //FuncID: 3
	&CMallProtSvr::_DoRecv_GetMallDiscountInfo, //FuncID: 4
	&CMallProtSvr::_DoRecv_BuyDiscountItem, //FuncID: 5
	&CMallProtSvr::_DoRecv_GetBuyItemList, //FuncID: 6
	&CMallProtSvr::_DoRecv_GetChongZhiActInfo, //FuncID: 7
};

bool CMallProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：通知玩家商城限购信息
bool CMallProtSvr::Send_UpdateMallDiscountInfo(
	const TVecDiscount& vecDiscount, //限购信息列表
	UINT32 wCountPos1, //限购位置1购买道具数
	UINT32 wCountPos2, //限购位置2购买道具数
	UINT32 wCountPos3, //限购位置3购买道具数
	UINT32 wRechargePos1, //位置1充值限购期间充值仙石数
	UINT32 wRechargePos2, //位置2充值限购期间充值仙石数
	UINT32 wRechargePos3, //位置3充值限购期间充值仙石数
	UINT32 wConsumePos1, //位置1消费限购期间消费仙石数
	UINT32 wConsumePos2, //位置2消费限购期间消费仙石数
	UINT32 wConsumePos3 //位置3消费限购期间消费仙石数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << vecDiscount << wCountPos1 << wCountPos2 << wCountPos3 << wRechargePos1 << wRechargePos2 << wRechargePos3 << wConsumePos1 << wConsumePos2 << wConsumePos3;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 27, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMallProtSvr::SendClt_UpdateMallDiscountInfo(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecDiscount& vecDiscount, //限购信息列表
	UINT32 wCountPos1, //限购位置1购买道具数
	UINT32 wCountPos2, //限购位置2购买道具数
	UINT32 wCountPos3, //限购位置3购买道具数
	UINT32 wRechargePos1, //位置1充值限购期间充值仙石数
	UINT32 wRechargePos2, //位置2充值限购期间充值仙石数
	UINT32 wRechargePos3, //位置3充值限购期间充值仙石数
	UINT32 wConsumePos1, //位置1消费限购期间消费仙石数
	UINT32 wConsumePos2, //位置2消费限购期间消费仙石数
	UINT32 wConsumePos3 //位置3消费限购期间消费仙石数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << vecDiscount << wCountPos1 << wCountPos2 << wCountPos3 << wRechargePos1 << wRechargePos2 << wRechargePos3 << wConsumePos1 << wConsumePos2 << wConsumePos3;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 27, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMallProtSvr::BuildPkg_UpdateMallDiscountInfo(
	const TVecDiscount& vecDiscount, //限购信息列表
	UINT32 wCountPos1, //限购位置1购买道具数
	UINT32 wCountPos2, //限购位置2购买道具数
	UINT32 wCountPos3, //限购位置3购买道具数
	UINT32 wRechargePos1, //位置1充值限购期间充值仙石数
	UINT32 wRechargePos2, //位置2充值限购期间充值仙石数
	UINT32 wRechargePos3, //位置3充值限购期间充值仙石数
	UINT32 wConsumePos1, //位置1消费限购期间消费仙石数
	UINT32 wConsumePos2, //位置2消费限购期间消费仙石数
	UINT32 wConsumePos3 //位置3消费限购期间消费仙石数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << vecDiscount << wCountPos1 << wCountPos2 << wCountPos3 << wRechargePos1 << wRechargePos2 << wRechargePos3 << wConsumePos1 << wConsumePos2 << wConsumePos3;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 27, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通过栏位通知玩家商城限购信息
bool CMallProtSvr::Send_UpdateMallDiscountInfoByPos(
	const SDiscount& oDiscount //限购信息列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << oDiscount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 27, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMallProtSvr::SendClt_UpdateMallDiscountInfoByPos(const UINT64* pUsrID_, UINT16 wCnt_,
	const SDiscount& oDiscount //限购信息列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << oDiscount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 27, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMallProtSvr::BuildPkg_UpdateMallDiscountInfoByPos(
	const SDiscount& oDiscount //限购信息列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << oDiscount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 27, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：物品购买数量更新
bool CMallProtSvr::Send_BuyItemNotify(
	const SBuyItemInfo& oBuyItemInfo //更新信息 dwInstID=0 表示整个更新列表清空数量（0点刷新）
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << oBuyItemInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 27, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMallProtSvr::SendClt_BuyItemNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const SBuyItemInfo& oBuyItemInfo //更新信息 dwInstID=0 表示整个更新列表清空数量（0点刷新）
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << oBuyItemInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 27, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMallProtSvr::BuildPkg_BuyItemNotify(
	const SBuyItemInfo& oBuyItemInfo //更新信息 dwInstID=0 表示整个更新列表清空数量（0点刷新）
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << oBuyItemInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 27, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新玩家'首次充值'活动完成信息(在商城界面的奖励)
bool CMallProtSvr::Send_UpdateChongZhiActInfo(
	UINT8 byIdx, //当前充值完成的第几个
	UINT32 dwCount, //当前充值了几个仙石包
	UINT8 byInfo //按位取(低6位,每位为1表明已完成)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << byIdx << dwCount << byInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 27, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMallProtSvr::SendClt_UpdateChongZhiActInfo(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byIdx, //当前充值完成的第几个
	UINT32 dwCount, //当前充值了几个仙石包
	UINT8 byInfo //按位取(低6位,每位为1表明已完成)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << byIdx << dwCount << byInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 27, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMallProtSvr::BuildPkg_UpdateChongZhiActInfo(
	UINT8 byIdx, //当前充值完成的第几个
	UINT32 dwCount, //当前充值了几个仙石包
	UINT8 byInfo //按位取(低6位,每位为1表明已完成)
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << byIdx << dwCount << byInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 27, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

CMallProtSvr::SMalGetAck::SMalGetAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CMallProtSvr::SMalGetAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecMallInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 27, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMallProtSvr::_DoRecv_MalGet(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EMallType eType = (EMallType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (INT8&)eType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 27, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SMalGetAck> fnAck_(new SMalGetAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_MalGet(eType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CMallProtSvr::SMalBuyAck::SMalBuyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EMallResult)0) { }

void CMallProtSvr::SMalBuyAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 27, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMallProtSvr::_DoRecv_MalBuy(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EUseMoneyMark eMark = (EUseMoneyMark)0;
	EMallType eType = (EMallType)0;
	UINT32 wInstID = 0;
	UINT16 wCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (INT8&)eMark >> (INT8&)eType >> wInstID >> wCount;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 27, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SMalBuyAck> fnAck_(new SMalBuyAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_MalBuy(eMark, eType, wInstID, wCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CMallProtSvr::SMallPresentAck::SMallPresentAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EMallResult)0) { }

void CMallProtSvr::SMallPresentAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 27, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMallProtSvr::_DoRecv_MallPresent(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EUseMoneyMark eMark = (EUseMoneyMark)0;
	EMallType eType = (EMallType)0;
	UINT32 wInstID = 0;
	UINT16 wCount = 0;
	std::string strReceiveName;
	std::string strTitle;
	std::string strMsg;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (INT8&)eMark >> (INT8&)eType >> wInstID >> wCount >> strReceiveName >> strTitle >> strMsg;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 27, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SMallPresentAck> fnAck_(new SMallPresentAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_MallPresent(eMark, eType, wInstID, wCount, strReceiveName, strTitle, strMsg, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CMallProtSvr::_DoRecv_GetMallDiscountInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetMallDiscountInfo();
	return true;
}

CMallProtSvr::SBuyDiscountItemAck::SBuyDiscountItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EMallResult)0), byPos(0), wCount(0) { }

void CMallProtSvr::SBuyDiscountItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eResult << byPos << wCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 27, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMallProtSvr::_DoRecv_BuyDiscountItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byPos = 0;
	UINT16 wCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byPos >> wCount;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 27, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBuyDiscountItemAck> fnAck_(new SBuyDiscountItemAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BuyDiscountItem(byPos, wCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CMallProtSvr::SGetBuyItemListAck::SGetBuyItemListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CMallProtSvr::SGetBuyItemListAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecBuyItemInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 27, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMallProtSvr::_DoRecv_GetBuyItemList(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 27, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetBuyItemListAck> fnAck_(new SGetBuyItemListAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetBuyItemList(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CMallProtSvr::_DoRecv_GetChongZhiActInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetChongZhiActInfo();
	return true;
}

} //namespace NMallProt
