/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    MallProt.h
//  Purpose:      商城相关协议
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
#include "ProtoCommon.h"

namespace NMallProt
{

/////////////////////以下为类型定义/////////////////////
//商城类型
enum EMallType
{
	eMallGold = 1, //奇珍商城
	eMallFashion, //时装商城
	eMallVIP, //VIP商城
	eMallPrestige, //声望商城
	eMallHonor, //荣誉商城
	eMallCoupon, //礼券商城
	eMallSilver, //银币商城
	eMallLimit, //限购商城
	eMallGem, //宝石商城
	eMallEnd //商城
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMallType);
bool EnumStrToVal(const char*, EMallType&);
#endif //PROT_USE_XML

//商城操作结果
enum EMallResult
{
	eMallResultSucc, //成功
	eMallResultFailed, //失败
	eMallResultStore, //背包空间不足
	eMallResultStoreAdd, //物品加入背包出错
	eMallResultMoney, //购买时相应货币不足
	eMallResultNoItem, //所购买的物品已下架
	eMallResultFashionErr, //所购买的时装不能加入背包
	eMallResultFashionAlready, //所购买的时装已存在
	eMallPresentSucc, //赠送成功
	eMallPresentNoTarget, //赠送的玩家不存在
	eMallResultDiscountOverTime, //限购活动已过期
	eMallResultDiscountFull, //超出限购数量限制
	eMallResultDiscountRechargeErr, //未达到限购充值仙石数量
	eMallResultDiscountConsumeErr, //未达到限购消耗仙石数量
	eMallResultItemCount //没有购买次数
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMallResult);
bool EnumStrToVal(const char*, EMallResult&);
#endif //PROT_USE_XML

//使用钱币标志
enum EUseMoneyMark
{
	eUseBindMoney, //使用绑定钱币
	eUseNoBindMoney //使用非绑定钱币
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EUseMoneyMark);
bool EnumStrToVal(const char*, EUseMoneyMark&);
#endif //PROT_USE_XML

//限购限制类型
enum EDiscountLimitType
{
	eDiscountLimitTypeNO = 0, //无条件
	eDiscountLimitTypeRecharge = 1, //充值限购
	eDiscountLimitTypeConsume = 2, //消费限购
	eDiscountLimitTypeEnd //限购类型
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDiscountLimitType);
bool EnumStrToVal(const char*, EDiscountLimitType&);
#endif //PROT_USE_XML

//商城信息
struct SMallInfo
{
	UINT32 dwInstID; //商品编号
	std::string strName; //商品名称
	UINT16 wItemID; //物品ID
	UINT32 dwItemCount; //物品数量
	NProtoCommon::EMoneyType eMoneyType; //所需货币类型
	UINT32 dwPrice; //价格
	UINT8 byVIP; //VIP等级限制
	UINT16 wIcon; //图标
	UINT32 dwDayCntLimit; //限购数量

	SMallInfo();
	SMallInfo(UINT32 dwInstID_, const std::string& strName_, UINT16 wItemID_, UINT32 dwItemCount_, NProtoCommon::EMoneyType eMoneyType_, 
		UINT32 dwPrice_, UINT8 byVIP_, UINT16 wIcon_, UINT32 dwDayCntLimit_);
#ifdef __GNUG__
	SMallInfo(const SMallInfo& src) = default; //默认拷贝构造函数
	SMallInfo& operator=(const SMallInfo& rhs) = default; //默认赋值操作符
#endif
	SMallInfo(SMallInfo&& src); //转移构造函数
	SMallInfo& operator=(SMallInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SMallInfo> TVecMallInfo;

//商城折扣物品
struct SDiscountItem
{
	UINT16 wItemID; //物品ID
	UINT16 wOriginalPrice; //原价
	UINT16 wDiscountPrice; //折扣价

	SDiscountItem();
	SDiscountItem(UINT16 wItemID_, UINT16 wOriginalPrice_, UINT16 wDiscountPrice_);
};

typedef std::vector<SDiscountItem> TVecDiscountItem;

//商城折扣物品信息
struct SDiscount
{
	UINT8 byPos; //限购位置(0,1,2表示)
	UINT64 qwMarkID; //栏位版本ID
	TVecDiscountItem vecDisItems; //限购道具
	UINT8 byLimitType; //类型限制(0无条件、1充值限购、2消费限购)
	UINT32 dwLimitValue; //达到的仙石数量限制(0无条件、1充值限购、2消费限购)
	UINT16 wLimitCount; //购买道具个数限制
	UINT32 dwBeginTime; //限购开始时间
	UINT32 dwEndTime; //限购结束时间

	SDiscount();
	SDiscount(UINT8 byPos_, UINT64 qwMarkID_, const TVecDiscountItem& vecDisItems_, UINT8 byLimitType_, UINT32 dwLimitValue_, 
		UINT16 wLimitCount_, UINT32 dwBeginTime_, UINT32 dwEndTime_);
#ifdef __GNUG__
	SDiscount(const SDiscount& src) = default; //默认拷贝构造函数
	SDiscount& operator=(const SDiscount& rhs) = default; //默认赋值操作符
#endif
	SDiscount(SDiscount&& src); //转移构造函数
	SDiscount& operator=(SDiscount&& rhs); //转移赋值操作符
};

typedef std::vector<SDiscount> TVecDiscount;

//物品购买信息
struct SBuyItemInfo
{
	UINT32 dwInstID; //实例ID
	UINT32 dwCount; //物品数量

	SBuyItemInfo();
	SBuyItemInfo(UINT32 dwInstID_, UINT32 dwCount_);
};

typedef std::vector<SBuyItemInfo> TVecBuyItemInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SMallInfo&);
COutArchive& operator<<(COutArchive&, const SMallInfo&);

CInArchive& operator>>(CInArchive&, SDiscountItem&);
COutArchive& operator<<(COutArchive&, const SDiscountItem&);

CInArchive& operator>>(CInArchive&, SDiscount&);
COutArchive& operator<<(COutArchive&, const SDiscount&);

CInArchive& operator>>(CInArchive&, SBuyItemInfo&);
COutArchive& operator<<(COutArchive&, const SBuyItemInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SMallInfo&);
bool ToXML(const SMallInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMallInfo&);
bool VectorToXML(const TVecMallInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDiscountItem&);
bool ToXML(const SDiscountItem&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDiscountItem&);
bool VectorToXML(const TVecDiscountItem&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDiscount&);
bool ToXML(const SDiscount&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDiscount&);
bool VectorToXML(const TVecDiscount&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBuyItemInfo&);
bool ToXML(const SBuyItemInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBuyItemInfo&);
bool VectorToXML(const TVecBuyItemInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NMallProt
