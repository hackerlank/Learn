/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    FighterProt.cpp
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "FighterProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NFighterProt
{

CFighterProtSvr::THandleFunc CFighterProtSvr::_HandleFuncs[] =
{
	&CFighterProtSvr::_DoRecv_FighterSkillEquipTo, //FuncID: 1
	&CFighterProtSvr::_DoRecv_FighterSkillLevelUp, //FuncID: 2
	&CFighterProtSvr::_DoRecv_FighterPassiveSkillLevelUp, //FuncID: 3
	&CFighterProtSvr::_DoRecv_GetTavernInfo, //FuncID: 4
	&CFighterProtSvr::_DoRecv_Draw, //FuncID: 5
	&CFighterProtSvr::_DoRecv_FighterRecruit, //FuncID: 6
	&CFighterProtSvr::_DoRecv_CuiTiUpgrade, //FuncID: 7
	&CFighterProtSvr::_DoRecv_CuiTiAllUpgrade, //FuncID: 8
	&CFighterProtSvr::_DoRecv_FighterShift, //FuncID: 9
	&CFighterProtSvr::_DoRecv_FighterSyncLevel, //FuncID: 10
	&CFighterProtSvr::_DoRecv_UpgradeDujie, //FuncID: 11
	&CFighterProtSvr::_DoRecv_ReqFighterXinFaInfo, //FuncID: 12
	&CFighterProtSvr::_DoRecv_FighterActiveXinFa, //FuncID: 13
	&CFighterProtSvr::_DoRecv_FighterXinFaLevelUp, //FuncID: 14
	&CFighterProtSvr::_DoRecv_FighterXinFaDisperse, //FuncID: 15
	&CFighterProtSvr::_DoRecv_GetAllFighterCombination, //FuncID: 16
	&CFighterProtSvr::_DoRecv_ActiveCombination, //FuncID: 17
	&CFighterProtSvr::_DoRecv_UpgradeCombination, //FuncID: 18
	&CFighterProtSvr::_DoRecv_EquipToCombinationSkill, //FuncID: 19
	&CFighterProtSvr::_DoRecv_FighterDismiss, //FuncID: 20
	&CFighterProtSvr::_DoRecv_GetFighterBuyInfo, //FuncID: 21
	&CFighterProtSvr::_DoRecv_FighterBuy, //FuncID: 22
};

bool CFighterProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：装备技能返回
bool CFighterProtSvr::Send_SkillUpNotify(
	UINT32 dwSkillID, //技能ID
	INT32 iSlot //技能槽 -1表示卸下技能
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSkillID << iSlot;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 20, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFighterProtSvr::SendClt_SkillUpNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwSkillID, //技能ID
	INT32 iSlot //技能槽 -1表示卸下技能
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSkillID << iSlot;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 20, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFighterProtSvr::BuildPkg_SkillUpNotify(
	UINT32 dwSkillID, //技能ID
	INT32 iSlot //技能槽 -1表示卸下技能
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSkillID << iSlot;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 20, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加新技能
bool CFighterProtSvr::Send_SkillAddNotify(
	UINT32 dwSkillID //技能ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSkillID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 20, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFighterProtSvr::SendClt_SkillAddNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwSkillID //技能ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSkillID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 20, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFighterProtSvr::BuildPkg_SkillAddNotify(
	UINT32 dwSkillID //技能ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSkillID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 20, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：散仙血脉激活
bool CFighterProtSvr::Send_InstinctActiveNotify(
	UINT64 qwInstID, //散仙唯一ID
	const TVecUINT16& vecInstinctIDRandom, //血脉随机结果
	const TVecUINT16& vecInstinctIDRet //血脉最终结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << vecInstinctIDRandom << vecInstinctIDRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 20, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFighterProtSvr::SendClt_InstinctActiveNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwInstID, //散仙唯一ID
	const TVecUINT16& vecInstinctIDRandom, //血脉随机结果
	const TVecUINT16& vecInstinctIDRet //血脉最终结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << vecInstinctIDRandom << vecInstinctIDRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 20, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFighterProtSvr::BuildPkg_InstinctActiveNotify(
	UINT64 qwInstID, //散仙唯一ID
	const TVecUINT16& vecInstinctIDRandom, //血脉随机结果
	const TVecUINT16& vecInstinctIDRet //血脉最终结果
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << vecInstinctIDRandom << vecInstinctIDRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 20, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：招募散仙成功的弹框通知
bool CFighterProtSvr::Send_RecruitSuccNotify(
	UINT16 wFighterID //散仙ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << wFighterID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 20, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFighterProtSvr::SendClt_RecruitSuccNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wFighterID //散仙ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << wFighterID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 20, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFighterProtSvr::BuildPkg_RecruitSuccNotify(
	UINT16 wFighterID //散仙ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << wFighterID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 20, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：阵型位置变更
bool CFighterProtSvr::Send_FighterPosNotify(
	const TVecFighterPos& vecPos //阵型位置
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecPos;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 20, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFighterProtSvr::SendClt_FighterPosNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecFighterPos& vecPos //阵型位置
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecPos;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 20, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFighterProtSvr::BuildPkg_FighterPosNotify(
	const TVecFighterPos& vecPos //阵型位置
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecPos;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 20, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新散仙的渡劫数据
bool CFighterProtSvr::Send_UpdateDujieValue(
	UINT64 qwInstID, //将唯一ID
	UINT8 byDujieLevel, //当前渡劫等级
	UINT32 dwDujieExp, //当前渡劫经验
	UINT32 dwSpiritPower //元神力
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << byDujieLevel << dwDujieExp << dwSpiritPower;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 20, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFighterProtSvr::SendClt_UpdateDujieValue(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwInstID, //将唯一ID
	UINT8 byDujieLevel, //当前渡劫等级
	UINT32 dwDujieExp, //当前渡劫经验
	UINT32 dwSpiritPower //元神力
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << byDujieLevel << dwDujieExp << dwSpiritPower;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 20, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFighterProtSvr::BuildPkg_UpdateDujieValue(
	UINT64 qwInstID, //将唯一ID
	UINT8 byDujieLevel, //当前渡劫等级
	UINT32 dwDujieExp, //当前渡劫经验
	UINT32 dwSpiritPower //元神力
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << byDujieLevel << dwDujieExp << dwSpiritPower;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 20, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：心法数据更新通知
bool CFighterProtSvr::Send_XinFaNotify(
	UINT64 qwInstID, //将唯一ID
	UINT32 dwXinFaID, //心法ID
	UINT8 byXinFaLvl, //心法等级
	INT32 iSlot //心法槽 -1表示心法没装备
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << dwXinFaID << byXinFaLvl << iSlot;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 20, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFighterProtSvr::SendClt_XinFaNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwInstID, //将唯一ID
	UINT32 dwXinFaID, //心法ID
	UINT8 byXinFaLvl, //心法等级
	INT32 iSlot //心法槽 -1表示心法没装备
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << dwXinFaID << byXinFaLvl << iSlot;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 20, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFighterProtSvr::BuildPkg_XinFaNotify(
	UINT64 qwInstID, //将唯一ID
	UINT32 dwXinFaID, //心法ID
	UINT8 byXinFaLvl, //心法等级
	INT32 iSlot //心法槽 -1表示心法没装备
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << dwXinFaID << byXinFaLvl << iSlot;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 20, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：散仙心法主卷等级满了添加一个天赋技能更新通知
bool CFighterProtSvr::Send_AddTalentSkillNotify(
	UINT64 qwInstID, //将唯一ID
	UINT8 byIdx, //技能槽idx
	UINT32 dwSkillID //技能ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << byIdx << dwSkillID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 20, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFighterProtSvr::SendClt_AddTalentSkillNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwInstID, //将唯一ID
	UINT8 byIdx, //技能槽idx
	UINT32 dwSkillID //技能ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << byIdx << dwSkillID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 20, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFighterProtSvr::BuildPkg_AddTalentSkillNotify(
	UINT64 qwInstID, //将唯一ID
	UINT8 byIdx, //技能槽idx
	UINT32 dwSkillID //技能ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << byIdx << dwSkillID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 20, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：散仙技能列表返回
bool CFighterProtSvr::Send_SkillListNotify(
	UINT64 qwInstID, //将唯一ID
	const TVecFighterSkill& VecFighterSkill //技能ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << VecFighterSkill;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 20, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFighterProtSvr::SendClt_SkillListNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwInstID, //将唯一ID
	const TVecFighterSkill& VecFighterSkill //技能ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << VecFighterSkill;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 20, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFighterProtSvr::BuildPkg_SkillListNotify(
	UINT64 qwInstID, //将唯一ID
	const TVecFighterSkill& VecFighterSkill //技能ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << VecFighterSkill;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 20, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家的散仙组合列表返回
bool CFighterProtSvr::Send_FighterCombinationNotify(
	const TVecFighterCombination& VecCombination //散仙组合列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << VecCombination;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 20, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CFighterProtSvr::SendClt_FighterCombinationNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecFighterCombination& VecCombination //散仙组合列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << VecCombination;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 20, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CFighterProtSvr::BuildPkg_FighterCombinationNotify(
	const TVecFighterCombination& VecCombination //散仙组合列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << VecCombination;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 20, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

CFighterProtSvr::SFighterSkillEquipToAck::SFighterSkillEquipToAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ESkillResult)0) { }

void CFighterProtSvr::SFighterSkillEquipToAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vActiveSkill;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_FighterSkillEquipTo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	UINT32 dwSkillID = 0;
	INT32 iSlot = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> dwSkillID >> iSlot;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFighterSkillEquipToAck> fnAck_(new SFighterSkillEquipToAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FighterSkillEquipTo(qwInstID, dwSkillID, iSlot, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SFighterSkillLevelUpAck::SFighterSkillLevelUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ESkillResult)0) { }

void CFighterProtSvr::SFighterSkillLevelUpAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_FighterSkillLevelUp(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	UINT32 dwSkillID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> dwSkillID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFighterSkillLevelUpAck> fnAck_(new SFighterSkillLevelUpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FighterSkillLevelUp(qwInstID, dwSkillID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SFighterPassiveSkillLevelUpAck::SFighterPassiveSkillLevelUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ESkillResult)0) { }

void CFighterProtSvr::SFighterPassiveSkillLevelUpAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_FighterPassiveSkillLevelUp(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	UINT32 dwSkillID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> dwSkillID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFighterPassiveSkillLevelUpAck> fnAck_(new SFighterPassiveSkillLevelUpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FighterPassiveSkillLevelUp(qwInstID, dwSkillID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SGetTavernInfoAck::SGetTavernInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwDrawCount(0) { }

void CFighterProtSvr::SGetTavernInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwDrawCount << vecTavernInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_GetTavernInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetTavernInfoAck> fnAck_(new SGetTavernInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetTavernInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SDrawAck::SDrawAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EDrawResult)0) { }

void CFighterProtSvr::SDrawAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecItemGet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_Draw(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EDrawType eType = (EDrawType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SDrawAck> fnAck_(new SDrawAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_Draw(eType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SFighterRecruitAck::SFighterRecruitAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ERecruitResult)0) { }

void CFighterProtSvr::SFighterRecruitAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_FighterRecruit(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wFighterID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wFighterID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFighterRecruitAck> fnAck_(new SFighterRecruitAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FighterRecruit(wFighterID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SCuiTiUpgradeAck::SCuiTiUpgradeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ECuiTiResult)0), byLevel(0) { }

void CFighterProtSvr::SCuiTiUpgradeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << byLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_CuiTiUpgrade(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	ECuiTiType eCuiTiType = (ECuiTiType)0;
	UINT8 byTimes = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> (UINT8&)eCuiTiType >> byTimes;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SCuiTiUpgradeAck> fnAck_(new SCuiTiUpgradeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_CuiTiUpgrade(qwInstID, eCuiTiType, byTimes, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SCuiTiAllUpgradeAck::SCuiTiAllUpgradeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ECuiTiResult)0) { }

void CFighterProtSvr::SCuiTiAllUpgradeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_CuiTiAllUpgrade(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SCuiTiAllUpgradeAck> fnAck_(new SCuiTiAllUpgradeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_CuiTiAllUpgrade(qwInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SFighterShiftAck::SFighterShiftAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EShiftResult)0) { }

void CFighterProtSvr::SFighterShiftAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 9";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_FighterShift(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstIDSrc = 0;
	UINT64 qwInstIDDst = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstIDSrc >> qwInstIDDst;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 9";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFighterShiftAck> fnAck_(new SFighterShiftAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FighterShift(qwInstIDSrc, qwInstIDDst, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SFighterSyncLevelAck::SFighterSyncLevelAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ESyncLevelResult)0) { }

void CFighterProtSvr::SFighterSyncLevelAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_FighterSyncLevel(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	UINT8 byGoalLvl = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> byGoalLvl;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 10";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFighterSyncLevelAck> fnAck_(new SFighterSyncLevelAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FighterSyncLevel(qwInstID, byGoalLvl, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SUpgradeDujieAck::SUpgradeDujieAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EDujieResult)0), qwInstID(0) { }

void CFighterProtSvr::SUpgradeDujieAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -11;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << qwInstID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 11";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_UpgradeDujie(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 11";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SUpgradeDujieAck> fnAck_(new SUpgradeDujieAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_UpgradeDujie(qwInstID, byOneKey, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SReqFighterXinFaInfoAck::SReqFighterXinFaInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CFighterProtSvr::SReqFighterXinFaInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -12;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecFighterXinFa;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 12";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_ReqFighterXinFaInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 12";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SReqFighterXinFaInfoAck> fnAck_(new SReqFighterXinFaInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReqFighterXinFaInfo(qwInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SFighterActiveXinFaAck::SFighterActiveXinFaAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EXinFaResult)0) { }

void CFighterProtSvr::SFighterActiveXinFaAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 13";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_FighterActiveXinFa(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	UINT32 dwXinFaID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> dwXinFaID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 13";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFighterActiveXinFaAck> fnAck_(new SFighterActiveXinFaAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FighterActiveXinFa(qwInstID, dwXinFaID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SFighterXinFaLevelUpAck::SFighterXinFaLevelUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EXinFaResult)0) { }

void CFighterProtSvr::SFighterXinFaLevelUpAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 14";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_FighterXinFaLevelUp(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	UINT32 dwXinFaID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> dwXinFaID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 14";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFighterXinFaLevelUpAck> fnAck_(new SFighterXinFaLevelUpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FighterXinFaLevelUp(qwInstID, dwXinFaID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SFighterXinFaDisperseAck::SFighterXinFaDisperseAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EXinFaResult)0) { }

void CFighterProtSvr::SFighterXinFaDisperseAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 15";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_FighterXinFaDisperse(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	UINT32 dwXinFaID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> dwXinFaID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 15";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFighterXinFaDisperseAck> fnAck_(new SFighterXinFaDisperseAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FighterXinFaDisperse(qwInstID, dwXinFaID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SGetAllFighterCombinationAck::SGetAllFighterCombinationAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CFighterProtSvr::SGetAllFighterCombinationAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -16;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecCombinationInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 16";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_GetAllFighterCombination(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 16";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetAllFighterCombinationAck> fnAck_(new SGetAllFighterCombinationAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAllFighterCombination(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SActiveCombinationAck::SActiveCombinationAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ECombinationResult)0) { }

void CFighterProtSvr::SActiveCombinationAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -17;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 17";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_ActiveCombination(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byGroupID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byGroupID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 17";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SActiveCombinationAck> fnAck_(new SActiveCombinationAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ActiveCombination(byGroupID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SUpgradeCombinationAck::SUpgradeCombinationAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ECombinationResult)0) { }

void CFighterProtSvr::SUpgradeCombinationAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -18;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << oCombinationInfo << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 18";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_UpgradeCombination(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byGroupID = 0;
	UINT8 byOneKey = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byGroupID >> byOneKey;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 18";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SUpgradeCombinationAck> fnAck_(new SUpgradeCombinationAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_UpgradeCombination(byGroupID, byOneKey, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SEquipToCombinationSkillAck::SEquipToCombinationSkillAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ECombinationResult)0) { }

void CFighterProtSvr::SEquipToCombinationSkillAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -19;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 19";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_EquipToCombinationSkill(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byGroupID = 0;
	UINT8 byType = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byGroupID >> byType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 19";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SEquipToCombinationSkillAck> fnAck_(new SEquipToCombinationSkillAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_EquipToCombinationSkill(byGroupID, byType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SFighterDismissAck::SFighterDismissAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EDismissResult)0) { }

void CFighterProtSvr::SFighterDismissAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -20;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 20";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_FighterDismiss(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 20";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFighterDismissAck> fnAck_(new SFighterDismissAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FighterDismiss(qwInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SGetFighterBuyInfoAck::SGetFighterBuyInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CFighterProtSvr::SGetFighterBuyInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -21;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecFighterBuyInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 21";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_GetFighterBuyInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 21";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetFighterBuyInfoAck> fnAck_(new SGetFighterBuyInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetFighterBuyInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CFighterProtSvr::SFighterBuyAck::SFighterBuyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EFighterBuyResult)0) { }

void CFighterProtSvr::SFighterBuyAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -22;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 20, Function: 22";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CFighterProtSvr::_DoRecv_FighterBuy(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wFighterID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wFighterID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 20, Function: 22";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFighterBuyAck> fnAck_(new SFighterBuyAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FighterBuy(wFighterID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NFighterProt
