/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    FeedBackProt.h
//  Purpose:      消费回馈
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

namespace NFeedBackProt
{

/////////////////////以下为类型定义/////////////////////
//消费回馈错误码
enum EFeedBackRet
{
	eFeedBackRet_Sucess = 0, //成功
	eFeedBackRet_MoneyLimit, //仙元不足
	eFeedBackRet_TakeCntLimit, //领取次数限制
	eFeedBackRet_IDError, //领奖id错误
	eFeedBackRet_TimeError, //不在限购时间
	eFeedBackRet_CFGError, //配置错误
	eFeedBackRet_ParamError, //参数错误
	eFeedBackRet_PackError, //背包空间不足
	eFeedBackRet_ActiveTimeError, //不在活动时间内
	eFeedBackRet_PrizeCntError //领奖次数限制
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EFeedBackRet);
bool EnumStrToVal(const char*, EFeedBackRet&);
#endif //PROT_USE_XML

//消费回馈类型
enum EFeedBackActType
{
	eFeedBackActType_Invalid = 0, //无效
	eFeedBackActType_EquipTrump, //法宝强化
	eFeedBackActType_Stone //宝石合成
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EFeedBackActType);
bool EnumStrToVal(const char*, EFeedBackActType&);
#endif //PROT_USE_XML

//回馈信息
struct SFeedBackInfo
{
	UINT32 dwActID; //活动id
	UINT32 dwBeginTime; //开始时间
	UINT32 dwEndTime; //结束时间
	UINT32 dwTakePrizeMax; //可领奖次数
	UINT32 dwTakePrizedCnt; //已领奖次数

	SFeedBackInfo();
	SFeedBackInfo(UINT32 dwActID_, UINT32 dwBeginTime_, UINT32 dwEndTime_, UINT32 dwTakePrizeMax_, UINT32 dwTakePrizedCnt_);
};

typedef std::vector<SFeedBackInfo> TVecFeedBackInfo;

//折扣限购信息
struct SBuyDiscountInfo
{
	EFeedBackActType eType; //消费回馈类型
	UINT32 dwBuyCount; //已领购买次数

	SBuyDiscountInfo();
	SBuyDiscountInfo(EFeedBackActType eType_, UINT32 dwBuyCount_);
};

typedef std::vector<SBuyDiscountInfo> TVecSBuyDiscountInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SFeedBackInfo&);
COutArchive& operator<<(COutArchive&, const SFeedBackInfo&);

CInArchive& operator>>(CInArchive&, SBuyDiscountInfo&);
COutArchive& operator<<(COutArchive&, const SBuyDiscountInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SFeedBackInfo&);
bool ToXML(const SFeedBackInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFeedBackInfo&);
bool VectorToXML(const TVecFeedBackInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBuyDiscountInfo&);
bool ToXML(const SBuyDiscountInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSBuyDiscountInfo&);
bool VectorToXML(const TVecSBuyDiscountInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NFeedBackProt
