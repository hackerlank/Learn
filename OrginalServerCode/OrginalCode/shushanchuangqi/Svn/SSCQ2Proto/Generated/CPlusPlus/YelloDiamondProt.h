/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    YelloDiamondProt.h
//  Purpose:      QQ黄钻协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include <string>
#include <memory>
#include "ServerDefine.h"
#include "Archive.h"
#ifdef PROT_USE_XML
#include "tinyxml.h"
#endif

namespace NYelloDiamondProt
{

/////////////////////以下为类型定义/////////////////////
//操作结果
enum EOpResult
{
	eOtherError, //其他错误
	eShortLevel, //等级不够
	eNotActive, //未开通QQ黄钻
	eNotYear, //未开通年费黄钻贵族
	eNotLuxury, //未开通QQ豪华黄钻
	eAreadyGain, //已经领取
	eBagFull, //背包空间不足
	eSuccess //操作成功
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EOpResult);
bool EnumStrToVal(const char*, EOpResult&);
#endif //PROT_USE_XML

//礼包类型
enum EBagType
{
	EBagType_eNone = 0, //无礼包可领取
	EBagType_eDayBag = 1, //黄钻日常礼包
	EBagType_eYearBag = 2, //年黄钻礼包
	EBagType_eLuxuryBag = 3, //豪华QQ黄钻礼包
	EBagType_eNewBag = 4, //新手礼包
	EBagType_eGrowBag = 5, //成长礼包
	EBagType_eHorseBag = 6, //座机礼包
	EBagType_eMax //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBagType);
bool EnumStrToVal(const char*, EBagType&);
#endif //PROT_USE_XML

//QQ黄钻类型
enum EYDType
{
	EYDType_eNone, //未开通QQ黄钻
	EYDType_eDayType, //普通QQ黄钻
	EYDType_eYearType, //年QQ黄钻
	EYDType_eLuxuryType //豪华QQ黄钻
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EYDType);
bool EnumStrToVal(const char*, EYDType&);
#endif //PROT_USE_XML

//QQ黄钻信息
struct SYDInfo
{
	bool bGainDayBag; //是否领取每日礼包
	bool bGainYearBag; //是否领取年费礼包
	bool bGainLuxuryBag; //是否领取豪华礼包
	bool bGainHorseBag; //是否领取座机礼包
	UINT16 dGrowBag; //已领取成长礼包等级 从低位开始向高位 1表示领取，0表示未领取
	bool bGainNewBag; //是否领取新手礼包

	SYDInfo();
	SYDInfo(bool bGainDayBag_, bool bGainYearBag_, bool bGainLuxuryBag_, bool bGainHorseBag_, UINT16 dGrowBag_, 
		bool bGainNewBag_);
};

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SYDInfo&);
COutArchive& operator<<(COutArchive&, const SYDInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SYDInfo&);
bool ToXML(const SYDInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NYelloDiamondProt
