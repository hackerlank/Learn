/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Beauty.h
//  Purpose:      美女系统
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include <vector>
#include <string>
#include <memory>
#include "ServerDefine.h"
#include "Archive.h"
#ifdef PROT_USE_XML
#include "tinyxml.h"
#endif
#include "ItemProt.h"
#include "ProtoCommon.h"

namespace NBeauty
{

/////////////////////以下为类型定义/////////////////////
//美女系统操作结果
enum EBeautyRet
{
	eBeautyRet_Sucess, //成功
	eBeautyRet_LevelLimit, //等级不够
	eBeautyRet_ErrorCFG, //配置错误
	eBeautyRet_PackError, //背包格子不够
	eBeautyRet_MoneyError, //钱不够
	eBeautyRet_HeartError, //爱心不够
	eBeautyRet_ErrorID, //美女ID错误
	eBeautyRet_ChatCd, //聊天cd限制
	eBeautyRet_LackItem, //物品不够
	eBeautyRet_ExistBeauty, //已结识美女
	eBeautyRet_GondError, //激活条件不满足
	eBeautyRet_LotterTypeError //抽奖类型错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBeautyRet);
bool EnumStrToVal(const char*, EBeautyRet&);
#endif //PROT_USE_XML

//抽奖类型
enum ELotteryBeautyType
{
	eLotteryBeautyType_OneSilver = 1001, //单次银币抽奖
	eLotteryBeautyType_OneGold = 1002, //单次仙石抽奖
	eLotteryBeautyType_OneLoveHeart = 1003, //单次爱心抽奖
	eLotteryBeautyType_OneFreeGold = 1004, //单次仙石免费抽奖
	eLotteryBeautyType_TenSilver = 2001, //10次银币抽奖
	eLotteryBeautyType_TenGold = 2002, //10次仙石抽奖
	eLotteryBeautyType_TenLoveHeart = 2003 //10次爱心抽奖
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELotteryBeautyType);
bool EnumStrToVal(const char*, ELotteryBeautyType&);
#endif //PROT_USE_XML

//美女信息
struct SBeauty
{
	UINT64 qwRoleID; //玩家id
	UINT16 wBeautyID; //美女id
	UINT16 wBeautyLevel; //亲密等级
	UINT32 dwBeautyExp; //亲密度
	UINT16 wDayLoveType; //当天喜欢物品类型
	UINT32 dwChatTime; //美女聊天cd(目前是共用cd次字段不用)
	UINT32 dwPrizeExp; //已获得爱心的亲密度
	bool bFight; //是否出战

	SBeauty();
	SBeauty(UINT64 qwRoleID_, UINT16 wBeautyID_, UINT16 wBeautyLevel_, UINT32 dwBeautyExp_, UINT16 wDayLoveType_, 
		UINT32 dwChatTime_, UINT32 dwPrizeExp_, bool bFight_);
};

typedef std::vector<SBeauty> TVecBeauty;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SBeauty&);
COutArchive& operator<<(COutArchive&, const SBeauty&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SBeauty&);
bool ToXML(const SBeauty&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBeauty&);
bool VectorToXML(const TVecBeauty&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NBeauty
