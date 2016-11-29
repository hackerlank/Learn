/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    ItemProt.cpp
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ItemProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NItemProt
{

CItemProtSvr::THandleFunc CItemProtSvr::_HandleFuncs[] =
{
	&CItemProtSvr::_DoRecv_GetStore, //FuncID: 1
	&CItemProtSvr::_DoRecv_UseItem, //FuncID: 2
	&CItemProtSvr::_DoRecv_ExpandStore, //FuncID: 3
	&CItemProtSvr::_DoRecv_RelocateStoreItem, //FuncID: 4
	&CItemProtSvr::_DoRecv_TidyupStore, //FuncID: 5
	&CItemProtSvr::_DoRecv_SplitStackItem, //FuncID: 6
	&CItemProtSvr::_DoRecv_MergeStackItem, //FuncID: 7
	&CItemProtSvr::_DoRecv_DestroyStoreItem, //FuncID: 8
	&CItemProtSvr::_DoRecv_TransferItem, //FuncID: 9
	&CItemProtSvr::_DoRecv_SellItem, //FuncID: 10
	&CItemProtSvr::_DoRecv_SellItemWithCount, //FuncID: 11
	&CItemProtSvr::_DoRecv_UnlockPack, //FuncID: 12
	&CItemProtSvr::_DoRecv_OpenItemLogger, //FuncID: 13
	&CItemProtSvr::_DoRecv_RecordTransfPoint, //FuncID: 14
	&CItemProtSvr::_DoRecv_TransfMapPoint, //FuncID: 15
	&CItemProtSvr::_DoRecv_WearCitta, //FuncID: 16
	&CItemProtSvr::_DoRecv_TakeoffCitta, //FuncID: 17
	&CItemProtSvr::_DoRecv_MergeCitta, //FuncID: 18
	&CItemProtSvr::_DoRecv_BreakCitta, //FuncID: 19
	&CItemProtSvr::_DoRecv_ActiveTrump, //FuncID: 20
	&CItemProtSvr::_DoRecv_EquipTrump, //FuncID: 21
	&CItemProtSvr::_DoRecv_UnEquipTrump, //FuncID: 22
	&CItemProtSvr::_DoRecv_UpgradeTrump, //FuncID: 23
	&CItemProtSvr::_DoRecv_EvolveTrump, //FuncID: 24
	&CItemProtSvr::_DoRecv_FashionActive, //FuncID: 25
	&CItemProtSvr::_DoRecv_FashionHide, //FuncID: 26
	&CItemProtSvr::_DoRecv_FashionChange, //FuncID: 27
	&CItemProtSvr::_DoRecv_FashionUpgrade, //FuncID: 28
	&CItemProtSvr::_DoRecv_WareGemStone, //FuncID: 29
	&CItemProtSvr::_DoRecv_TakeOffGemStone, //FuncID: 30
	&CItemProtSvr::_DoRecv_ComposeGemStone, //FuncID: 31
	&CItemProtSvr::_DoRecv_ComposeGemStoneOneKey, //FuncID: 32
};

bool CItemProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：包裹或仓库道具通知
bool CItemProtSvr::Send_StoreNotify(
	EStoreType eStoreType, //存储类型
	UINT16 wStoreSize, //包裹或仓库的容量
	const TVecItem& vecStoreItem //包裹或仓库中道具的列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << wStoreSize << vecStoreItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_StoreNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	EStoreType eStoreType, //存储类型
	UINT16 wStoreSize, //包裹或仓库的容量
	const TVecItem& vecStoreItem //包裹或仓库中道具的列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << wStoreSize << vecStoreItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_StoreNotify(
	EStoreType eStoreType, //存储类型
	UINT16 wStoreSize, //包裹或仓库的容量
	const TVecItem& vecStoreItem //包裹或仓库中道具的列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << wStoreSize << vecStoreItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：解锁格子还需要多少时间
bool CItemProtSvr::Send_PackNextUnlockTime(
	UINT32 dwTime //时间，单位秒
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_PackNextUnlockTime(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwTime //时间，单位秒
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_PackNextUnlockTime(
	UINT32 dwTime //时间，单位秒
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：包裹或仓库容量改变通知
bool CItemProtSvr::Send_StoreSizeChangeNotify(
	EStoreType eStoreType, //存储类型
	UINT16 wStoreSize //包裹或仓库的容量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << wStoreSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_StoreSizeChangeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	EStoreType eStoreType, //存储类型
	UINT16 wStoreSize //包裹或仓库的容量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << wStoreSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_StoreSizeChangeNotify(
	EStoreType eStoreType, //存储类型
	UINT16 wStoreSize //包裹或仓库的容量
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << wStoreSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：当前玩家的包裹或仓库中道具增加通知
bool CItemProtSvr::Send_StoreItemAddNtf(
	EStoreType eStoreType, //存储类型
	const TVecItem& vecStoreItem, //包裹或仓库中道具的列表
	bool bNew //是否新获得道具
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << vecStoreItem << bNew;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_StoreItemAddNtf(const UINT64* pUsrID_, UINT16 wCnt_,
	EStoreType eStoreType, //存储类型
	const TVecItem& vecStoreItem, //包裹或仓库中道具的列表
	bool bNew //是否新获得道具
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << vecStoreItem << bNew;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_StoreItemAddNtf(
	EStoreType eStoreType, //存储类型
	const TVecItem& vecStoreItem, //包裹或仓库中道具的列表
	bool bNew //是否新获得道具
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << vecStoreItem << bNew;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：当前玩家的包裹或仓库中道具删除通知
bool CItemProtSvr::Send_StoreItemDelNtf(
	EStoreType eStoreType, //存储类型
	const TVecUINT64& vecInstID //道具的实例ID列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << vecInstID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_StoreItemDelNtf(const UINT64* pUsrID_, UINT16 wCnt_,
	EStoreType eStoreType, //存储类型
	const TVecUINT64& vecInstID //道具的实例ID列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << vecInstID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_StoreItemDelNtf(
	EStoreType eStoreType, //存储类型
	const TVecUINT64& vecInstID //道具的实例ID列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << vecInstID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：堆叠道具数量刷新通知
bool CItemProtSvr::Send_StackItemUpdate(
	EStoreType eStoreType, //存储类型
	UINT64 qwRoleID, //角色ID
	UINT64 qwInstID, //堆叠道具的实例ID
	UINT16 wStack //当前堆叠数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << qwRoleID << qwInstID << wStack;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_StackItemUpdate(const UINT64* pUsrID_, UINT16 wCnt_,
	EStoreType eStoreType, //存储类型
	UINT64 qwRoleID, //角色ID
	UINT64 qwInstID, //堆叠道具的实例ID
	UINT16 wStack //当前堆叠数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << qwRoleID << qwInstID << wStack;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_StackItemUpdate(
	EStoreType eStoreType, //存储类型
	UINT64 qwRoleID, //角色ID
	UINT64 qwInstID, //堆叠道具的实例ID
	UINT16 wStack //当前堆叠数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << qwRoleID << qwInstID << wStack;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：打开包裹或仓库
bool CItemProtSvr::Send_OpenDepot(
	EStoreType eStoreType //存储类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_OpenDepot(const UINT64* pUsrID_, UINT16 wCnt_,
	EStoreType eStoreType //存储类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_OpenDepot(
	EStoreType eStoreType //存储类型
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：道具绑定改变通知
bool CItemProtSvr::Send_ItemBindChangeNtf(
	EStoreType eStoreType, //存储类型
	UINT64 qwInstID, //道具的实例ID
	EBindType eBindType, //道具的绑定类型
	bool bBind //道具是否绑定
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << qwInstID << (UINT8&)eBindType << bBind;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_ItemBindChangeNtf(const UINT64* pUsrID_, UINT16 wCnt_,
	EStoreType eStoreType, //存储类型
	UINT64 qwInstID, //道具的实例ID
	EBindType eBindType, //道具的绑定类型
	bool bBind //道具是否绑定
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << qwInstID << (UINT8&)eBindType << bBind;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_ItemBindChangeNtf(
	EStoreType eStoreType, //存储类型
	UINT64 qwInstID, //道具的实例ID
	EBindType eBindType, //道具的绑定类型
	bool bBind //道具是否绑定
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << qwInstID << (UINT8&)eBindType << bBind;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：道具CD时间通知
bool CItemProtSvr::Send_ItemCDNtf(
	UINT8 byType, //冷却类型0:ItemID 1:GroupID
	const SItemColdTime& rItemCD //道具CD
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << byType << rItemCD;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_ItemCDNtf(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byType, //冷却类型0:ItemID 1:GroupID
	const SItemColdTime& rItemCD //道具CD
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << byType << rItemCD;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_ItemCDNtf(
	UINT8 byType, //冷却类型0:ItemID 1:GroupID
	const SItemColdTime& rItemCD //道具CD
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << byType << rItemCD;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：道具的到期时间通知
bool CItemProtSvr::Send_ItemExpireTimeNtf(
	UINT64 qwInstID, //道具的实例ID
	UINT32 dwExpireTime //到期时间(1970年1月1日0时开始的秒数)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << dwExpireTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_ItemExpireTimeNtf(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwInstID, //道具的实例ID
	UINT32 dwExpireTime //到期时间(1970年1月1日0时开始的秒数)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << dwExpireTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_ItemExpireTimeNtf(
	UINT64 qwInstID, //道具的实例ID
	UINT32 dwExpireTime //到期时间(1970年1月1日0时开始的秒数)
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << dwExpireTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：道具(装备)属性变化通知
bool CItemProtSvr::Send_ItemChangeNotify(
	EStoreType eStoreType, //存储类型
	UINT64 qwOwnerID, //所有者ID(可能是主将，副将，宠物...)
	const SItemPtr& rStoreItem //装备更新后信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	SItem_Wrapper rStoreItem_Wrapper(rStoreItem);
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << qwOwnerID << rStoreItem_Wrapper;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_ItemChangeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	EStoreType eStoreType, //存储类型
	UINT64 qwOwnerID, //所有者ID(可能是主将，副将，宠物...)
	const SItemPtr& rStoreItem //装备更新后信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	SItem_Wrapper rStoreItem_Wrapper(rStoreItem);
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << qwOwnerID << rStoreItem_Wrapper;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_ItemChangeNotify(
	EStoreType eStoreType, //存储类型
	UINT64 qwOwnerID, //所有者ID(可能是主将，副将，宠物...)
	const SItemPtr& rStoreItem //装备更新后信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	SItem_Wrapper rStoreItem_Wrapper(rStoreItem);
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << qwOwnerID << rStoreItem_Wrapper;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 11";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：清除道具使用冷却CD
bool CItemProtSvr::Send_ClearAllItemCDNtf(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_ClearAllItemCDNtf(const UINT64* pUsrID_, UINT16 wCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_ClearAllItemCDNtf(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 12";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：角色道具冷却通知
bool CItemProtSvr::Send_SlotItemCDNotify(
	const TVecItemColdTime& vecItemCold, //道具使用冷却时间
	const TVecItemColdTime& vecGroupCold //道具公共冷却时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << vecItemCold << vecGroupCold;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_SlotItemCDNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecItemColdTime& vecItemCold, //道具使用冷却时间
	const TVecItemColdTime& vecGroupCold //道具公共冷却时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << vecItemCold << vecGroupCold;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_SlotItemCDNotify(
	const TVecItemColdTime& vecItemCold, //道具使用冷却时间
	const TVecItemColdTime& vecGroupCold //道具公共冷却时间
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << vecItemCold << vecGroupCold;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 13";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：角色获得道具提示
bool CItemProtSvr::Send_AddItemSystemMsg(
	const TVecAddItemMsg& vecAddItemMsg //道具获得提示
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << vecAddItemMsg;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_AddItemSystemMsg(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecAddItemMsg& vecAddItemMsg //道具获得提示
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << vecAddItemMsg;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_AddItemSystemMsg(
	const TVecAddItemMsg& vecAddItemMsg //道具获得提示
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << vecAddItemMsg;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 14";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：错误提示
bool CItemProtSvr::Send_ItemErrNfg(
	EItemResult eResult //提示
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 15";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_ItemErrNfg(const UINT64* pUsrID_, UINT16 wCnt_,
	EItemResult eResult //提示
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 15";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_ItemErrNfg(
	EItemResult eResult //提示
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 15";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：再一次增加记录道具通知
bool CItemProtSvr::Send_AgainAddloggedItemNotify(
	const TVecLoggedItem& rVecLoggedItem //道具列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << rVecLoggedItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 16";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_AgainAddloggedItemNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecLoggedItem& rVecLoggedItem //道具列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << rVecLoggedItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 16";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_AgainAddloggedItemNotify(
	const TVecLoggedItem& rVecLoggedItem //道具列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << rVecLoggedItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 16";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加记录道具通知
bool CItemProtSvr::Send_AddLoggedItemNotify(
	const TVecLoggedItem& rVecLoggedItem //道具列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_ << rVecLoggedItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 17";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_AddLoggedItemNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecLoggedItem& rVecLoggedItem //道具列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_ << rVecLoggedItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 17";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_AddLoggedItemNotify(
	const TVecLoggedItem& rVecLoggedItem //道具列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_ << rVecLoggedItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 17";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新记录的堆叠道具通知
bool CItemProtSvr::Send_UpdateLoggedStackItemNotify(
	UINT16 wItemID, //ID
	UINT8 byQuality, //品质
	UINT32 dwCount //数目
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << wItemID << byQuality << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 18";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_UpdateLoggedStackItemNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wItemID, //ID
	UINT8 byQuality, //品质
	UINT32 dwCount //数目
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << wItemID << byQuality << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 18";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_UpdateLoggedStackItemNotify(
	UINT16 wItemID, //ID
	UINT8 byQuality, //品质
	UINT32 dwCount //数目
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << wItemID << byQuality << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 18";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：当前玩家制造或者分解心法，包裹或仓库中道具增加通知
bool CItemProtSvr::Send_CittaAddNtf(
	EStoreType eStoreType, //存储类型
	const TVecItem& vecStoreItem, //包裹或仓库中道具的列表
	bool bNew //是否新获得道具
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 19;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << vecStoreItem << bNew;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 19";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_CittaAddNtf(const UINT64* pUsrID_, UINT16 wCnt_,
	EStoreType eStoreType, //存储类型
	const TVecItem& vecStoreItem, //包裹或仓库中道具的列表
	bool bNew //是否新获得道具
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 19;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << vecStoreItem << bNew;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 19";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_CittaAddNtf(
	EStoreType eStoreType, //存储类型
	const TVecItem& vecStoreItem, //包裹或仓库中道具的列表
	bool bNew //是否新获得道具
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 19;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eStoreType << vecStoreItem << bNew;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 19";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新记录的堆叠道具通知
bool CItemProtSvr::Send_NoticeUseItemNotify(
	UINT16 wItemID, //ID
	UINT32 dwNum, //使用物品数量
	const TVecResource& vecRes, //资源
	const TVecItemGenInfo& vecItem //物品
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << wItemID << dwNum << vecRes << vecItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 18, Function: 20";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CItemProtSvr::SendClt_NoticeUseItemNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wItemID, //ID
	UINT32 dwNum, //使用物品数量
	const TVecResource& vecRes, //资源
	const TVecItemGenInfo& vecItem //物品
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << wItemID << dwNum << vecRes << vecItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 18, Function: 20";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CItemProtSvr::BuildPkg_NoticeUseItemNotify(
	UINT16 wItemID, //ID
	UINT32 dwNum, //使用物品数量
	const TVecResource& vecRes, //资源
	const TVecItemGenInfo& vecItem //物品
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << wItemID << dwNum << vecRes << vecItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 18, Function: 20";
		_strPkg.clear();
	}
	return _strPkg;
}

CItemProtSvr::SGetStoreAck::SGetStoreAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwNextUnlockTime(0) { }

void CItemProtSvr::SGetStoreAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << stStoreStream << dwNextUnlockTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_GetStore(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EStoreType eStoreType = (EStoreType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eStoreType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetStoreAck> fnAck_(new SGetStoreAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetStore(eStoreType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SUseItemAck::SUseItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EItemResult)0) { }

void CItemProtSvr::SUseItemAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_UseItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EStoreType eStoreType = (EStoreType)0;
	UINT64 qwRoleID = 0;
	UINT64 qwMercenID = 0;
	UINT64 qwInstID = 0;
	UINT16 wStack = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eStoreType >> qwRoleID >> qwMercenID >> qwInstID >> wStack;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SUseItemAck> fnAck_(new SUseItemAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_UseItem(eStoreType, qwRoleID, qwMercenID, qwInstID, wStack, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SExpandStoreAck::SExpandStoreAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EItemResult)0) { }

void CItemProtSvr::SExpandStoreAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_ExpandStore(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EStoreType eStoreType = (EStoreType)0;
	UINT8 byCount = 0;
	NProtoCommon::ECoinType eCoinType = (NProtoCommon::ECoinType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eStoreType >> byCount >> (UINT8&)eCoinType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SExpandStoreAck> fnAck_(new SExpandStoreAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ExpandStore(eStoreType, byCount, eCoinType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SRelocateStoreItemAck::SRelocateStoreItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EItemResult)0) { }

void CItemProtSvr::SRelocateStoreItemAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_RelocateStoreItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EStoreType eStoreType = (EStoreType)0;
	UINT64 qwInstID = 0;
	INT16 wNewIndex = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eStoreType >> qwInstID >> wNewIndex;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SRelocateStoreItemAck> fnAck_(new SRelocateStoreItemAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_RelocateStoreItem(eStoreType, qwInstID, wNewIndex, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::STidyupStoreAck::STidyupStoreAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EItemResult)0) { }

void CItemProtSvr::STidyupStoreAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_TidyupStore(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EStoreType eStoreType = (EStoreType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eStoreType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<STidyupStoreAck> fnAck_(new STidyupStoreAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_TidyupStore(eStoreType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SSplitStackItemAck::SSplitStackItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EItemResult)0) { }

void CItemProtSvr::SSplitStackItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_SplitStackItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EStoreType eStoreType = (EStoreType)0;
	UINT64 qwInstID = 0;
	UINT16 wStack = 0;
	INT16 wIndex = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eStoreType >> qwInstID >> wStack >> wIndex;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSplitStackItemAck> fnAck_(new SSplitStackItemAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_SplitStackItem(eStoreType, qwInstID, wStack, wIndex, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SMergeStackItemAck::SMergeStackItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EItemResult)0) { }

void CItemProtSvr::SMergeStackItemAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_MergeStackItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EStoreType eStoreType = (EStoreType)0;
	UINT64 qwFromInstID = 0;
	UINT64 qwToInstID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eStoreType >> qwFromInstID >> qwToInstID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SMergeStackItemAck> fnAck_(new SMergeStackItemAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_MergeStackItem(eStoreType, qwFromInstID, qwToInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SDestroyStoreItemAck::SDestroyStoreItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EItemResult)0) { }

void CItemProtSvr::SDestroyStoreItemAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_DestroyStoreItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EStoreType eStoreType = (EStoreType)0;
	UINT64 qwInstID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eStoreType >> qwInstID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SDestroyStoreItemAck> fnAck_(new SDestroyStoreItemAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_DestroyStoreItem(eStoreType, qwInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::STransferItemAck::STransferItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EItemResult)0) { }

void CItemProtSvr::STransferItemAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 9";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_TransferItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EStoreType eFromStoreType = (EStoreType)0;
	EStoreType eToStoreType = (EStoreType)0;
	UINT64 qwInstID = 0;
	INT16 wIndex = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eFromStoreType >> (UINT8&)eToStoreType >> qwInstID >> wIndex;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 9";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<STransferItemAck> fnAck_(new STransferItemAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_TransferItem(eFromStoreType, eToStoreType, qwInstID, wIndex, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SSellItemAck::SSellItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EItemResult)0) { }

void CItemProtSvr::SSellItemAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_SellItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	TVecUINT64 vecInstID;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> vecInstID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 10";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSellItemAck> fnAck_(new SSellItemAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_SellItem(vecInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SSellItemWithCountAck::SSellItemWithCountAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EItemResult)0) { }

void CItemProtSvr::SSellItemWithCountAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 11";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_SellItemWithCount(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EStoreType eStoreType = (EStoreType)0;
	UINT64 qwInstID = 0;
	UINT16 wStack = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eStoreType >> qwInstID >> wStack;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 11";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSellItemWithCountAck> fnAck_(new SSellItemWithCountAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_SellItemWithCount(eStoreType, qwInstID, wStack, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SUnlockPackAck::SUnlockPackAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EItemResult)0) { }

void CItemProtSvr::SUnlockPackAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 12";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_UnlockPack(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 12";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SUnlockPackAck> fnAck_(new SUnlockPackAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_UnlockPack(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CItemProtSvr::_DoRecv_OpenItemLogger(const char* pBuf_, UINT32 dwLen_)
{
	EItemLoggerType eType = (EItemLoggerType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 13";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_OpenItemLogger(eType);
	return true;
}

CItemProtSvr::SRecordTransfPointAck::SRecordTransfPointAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EItemResult)0) { }

void CItemProtSvr::SRecordTransfPointAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -13;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 14";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_RecordTransfPoint(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	UINT16 wIndex = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> wIndex;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 14";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SRecordTransfPointAck> fnAck_(new SRecordTransfPointAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_RecordTransfPoint(qwInstID, wIndex, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::STransfMapPointAck::STransfMapPointAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EItemResult)0) { }

void CItemProtSvr::STransfMapPointAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -14;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 15";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_TransfMapPoint(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	UINT16 wIndex = 0;
	UINT16 wMapID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> wIndex >> wMapID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 15";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<STransfMapPointAck> fnAck_(new STransfMapPointAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_TransfMapPoint(qwInstID, wIndex, wMapID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SWearCittaAck::SWearCittaAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ECittaResult)0) { }

void CItemProtSvr::SWearCittaAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -15;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 16";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_WearCitta(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	ECittaSlotType eSlotType = (ECittaSlotType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> (INT8&)eSlotType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 16";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SWearCittaAck> fnAck_(new SWearCittaAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_WearCitta(qwInstID, eSlotType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::STakeoffCittaAck::STakeoffCittaAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ECittaResult)0) { }

void CItemProtSvr::STakeoffCittaAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 17";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_TakeoffCitta(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	ECittaSlotType eSlotType = (ECittaSlotType)0;
	INT16 wIndex = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (INT8&)eSlotType >> wIndex;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 17";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<STakeoffCittaAck> fnAck_(new STakeoffCittaAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_TakeoffCitta(eSlotType, wIndex, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SMergeCittaAck::SMergeCittaAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ECittaResult)0) { }

void CItemProtSvr::SMergeCittaAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -17;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecItemCitta;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 18";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_MergeCitta(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EBindUseType eBindType = (EBindUseType)0;
	UINT16 wItemID = 0;
	UINT16 wCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eBindType >> wItemID >> wCount;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 18";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SMergeCittaAck> fnAck_(new SMergeCittaAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_MergeCitta(eBindType, wItemID, wCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SBreakCittaAck::SBreakCittaAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ECittaResult)0) { }

void CItemProtSvr::SBreakCittaAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -18;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecItemInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 19";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_BreakCitta(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	TVecUINT64 vecInstID;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> vecInstID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 19";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBreakCittaAck> fnAck_(new SBreakCittaAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BreakCitta(vecInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SActiveTrumpAck::SActiveTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ETrumpResult)0) { }

void CItemProtSvr::SActiveTrumpAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -19;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecTrump;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 20";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_ActiveTrump(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wItemID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wItemID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 20";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SActiveTrumpAck> fnAck_(new SActiveTrumpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ActiveTrump(wItemID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SEquipTrumpAck::SEquipTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ETrumpResult)0) { }

void CItemProtSvr::SEquipTrumpAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -20;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecTrump;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 21";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_EquipTrump(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 21";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SEquipTrumpAck> fnAck_(new SEquipTrumpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_EquipTrump(qwInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SUnEquipTrumpAck::SUnEquipTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ETrumpResult)0) { }

void CItemProtSvr::SUnEquipTrumpAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -21;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecTrump;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 22";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_UnEquipTrump(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 22";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SUnEquipTrumpAck> fnAck_(new SUnEquipTrumpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_UnEquipTrump(qwInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SUpgradeTrumpAck::SUpgradeTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ETrumpResult)0) { }

void CItemProtSvr::SUpgradeTrumpAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -22;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecTrump;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 23";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_UpgradeTrump(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	UINT8 byOneKey = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> byOneKey;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 23";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SUpgradeTrumpAck> fnAck_(new SUpgradeTrumpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_UpgradeTrump(qwInstID, byOneKey, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SEvolveTrumpAck::SEvolveTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ETrumpResult)0) { }

void CItemProtSvr::SEvolveTrumpAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -23;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecTrump;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 24";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_EvolveTrump(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 24";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SEvolveTrumpAck> fnAck_(new SEvolveTrumpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_EvolveTrump(qwInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SFashionActiveAck::SFashionActiveAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EFashionResult)0) { }

void CItemProtSvr::SFashionActiveAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -24;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 25";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_FashionActive(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wItemID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wItemID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 25";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFashionActiveAck> fnAck_(new SFashionActiveAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FashionActive(wItemID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SFashionHideAck::SFashionHideAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EFashionResult)0) { }

void CItemProtSvr::SFashionHideAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -25;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 26";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_FashionHide(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byType = 0;
	UINT8 byHide = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byType >> byHide;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 26";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFashionHideAck> fnAck_(new SFashionHideAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FashionHide(byType, byHide, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SFashionChangeAck::SFashionChangeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EFashionResult)0) { }

void CItemProtSvr::SFashionChangeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -26;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 27";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_FashionChange(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 27";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFashionChangeAck> fnAck_(new SFashionChangeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FashionChange(qwInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SFashionUpgradeAck::SFashionUpgradeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EFashionResult)0) { }

void CItemProtSvr::SFashionUpgradeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -27;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 28";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_FashionUpgrade(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	UINT8 byOneKey = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> byOneKey;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 28";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFashionUpgradeAck> fnAck_(new SFashionUpgradeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FashionUpgrade(qwInstID, byOneKey, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SWareGemStoneAck::SWareGemStoneAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGemstoneResult)0), qwFighterID(0), byPos(0) { }

void CItemProtSvr::SWareGemStoneAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -28;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << qwFighterID << byPos << Item;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 29";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_WareGemStone(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wItemID = 0;
	UINT64 qwFighterID = 0;
	UINT8 byPos = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wItemID >> qwFighterID >> byPos;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 29";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SWareGemStoneAck> fnAck_(new SWareGemStoneAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_WareGemStone(wItemID, qwFighterID, byPos, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::STakeOffGemStoneAck::STakeOffGemStoneAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGemstoneResult)0), qwFighterID(0), byPos(0) { }

void CItemProtSvr::STakeOffGemStoneAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -29;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << qwFighterID << byPos;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 30";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_TakeOffGemStone(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwFighterID = 0;
	UINT8 byPos = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwFighterID >> byPos;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 30";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<STakeOffGemStoneAck> fnAck_(new STakeOffGemStoneAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_TakeOffGemStone(qwFighterID, byPos, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SComposeGemStoneAck::SComposeGemStoneAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGemstoneResult)0) { }

void CItemProtSvr::SComposeGemStoneAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -30;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 31";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_ComposeGemStone(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wItemID = 0;
	UINT32 dwNum = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wItemID >> dwNum;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 31";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SComposeGemStoneAck> fnAck_(new SComposeGemStoneAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ComposeGemStone(wItemID, dwNum, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CItemProtSvr::SComposeGemStoneOneKeyAck::SComposeGemStoneOneKeyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGemstoneResult)0) { }

void CItemProtSvr::SComposeGemStoneOneKeyAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -31;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 18, Function: 32";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CItemProtSvr::_DoRecv_ComposeGemStoneOneKey(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	TVecGMMailItem vecStone;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> vecStone;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 18, Function: 32";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SComposeGemStoneOneKeyAck> fnAck_(new SComposeGemStoneOneKeyAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ComposeGemStoneOneKey(vecStone, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NItemProt
