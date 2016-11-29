/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    PropInfo.h
//  Purpose:      属性相关协议
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

namespace NPropInfo
{

/////////////////////以下为类型定义/////////////////////
//变更对象类型
enum EPropClass
{
	eClassRole, //角色
	eClassFighter, //将
	eClassEquip, //装备
	eClassORole //其他角色
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EPropClass);
bool EnumStrToVal(const char*, EPropClass&);
#endif //PROT_USE_XML

//属性的类型
enum EPropType
{
	ePropNone = 0, //无
	ePropGold = 1, //仙石
	ePropSilver = 2, //银币
	ePropCoupon = 3, //礼券
	eProppGiftCoin = 4, //金券
	ePropExpTemp = 5, //经验(占位)
	ePropPrestige = 6, //声望
	ePropSoul = 7, //魂魄
	ePropHonor = 8, //荣誉
	ePropPExp = 9, //修为
	ePropSigil = 10, //符印
	ePropCentsY = 11, //仙元
	ePropAction = 12, //体力
	ePropSop = 13, //阅历
	ePropTaoism = 14, //道术
	ePropPoten = 15, //渡劫点数
	ePropReiki = 16, //副本星级
	ePropHFP = 17, //寻仙积分
	ePropDemonSoul = 18, //锁妖塔魂值
	ePropSoulAttack = 19, //攻击之魂
	ePropSoulHp = 20, //生命之魂
	ePropSoulCritical = 21, //暴击之魂
	ePropSoulCounter = 22, //反击之魂
	ePropSoulSpeed = 23, //身法之魂
	ePropSoulDefence = 24, //防御之魂
	ePropSoulHit = 25, //命中之魂
	ePropSoulDodge = 26, //闪避之魂
	ePropAchievementAP = 27, //成就点
	ePropCollectAP = 28, //收藏点
	ePropGuildContrib = 29, //帮派贡献
	ePropStampHuang = 30, //黄阶除魔印
	ePropStampXuan = 31, //玄阶除魔印
	ePropStampDi = 32, //地阶除魔印
	ePropStampTian = 33, //天阶除魔印
	ePropStampXing = 34, //星阶除魔印
	ePropStampYue = 35, //月阶除魔印
	ePropStampDi2 = 36, //帝阶除魔印
	ePropStampXian = 37, //仙阶除魔印
	ePropStampSheng = 38, //圣阶除魔印
	ePropStampFo = 39, //佛阶除魔印
	ePropLoveHeart = 40, //爱心
	ePropBlueFairyFate = 51, //蓝色仙缘
	ePropPurpleFairyFate = 52, //紫色仙缘
	ePropOrangeFairyFate = 53, //橙色仙缘
	ePropDuJieFu = 56, //渡劫符
	ePropLuckyCoupon = 57, //抽奖券
	ePropMoneyEnd = 100, //钱币属性结束标志
	ePropCommon = 200, //普通定义
	ePropTotalRecharge = 201, //总充值数
	ePropBTPoint = 202, //战斗力
	ePropHero = 300, //将定义
	ePropPos = 301, //将在阵型中的位置
	ePropTroopPos = 302, //将在队伍中的位置
	ePropPotential = 303, //潜力
	ePropCapacity = 304, //资质
	ePropLevel = 305, //等级
	ePropLucky = 306, //机缘值
	ePropExp = 307, //经验 -- UINT64
	ePropLianPi = 308, //炼皮
	ePropTongJin = 309, //通筋
	ePropQiangJi = 310, //强肌
	ePropDuanGu = 311, //锻骨
	ePropMax //属性枚举最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EPropType);
bool EnumStrToVal(const char*, EPropType&);
#endif //PROT_USE_XML

//属性操作的结果
enum EPropResult
{
	ePropSucceed, //无
	ePropGoldErr, //仙石不够
	ePropSilverErr, //银币不够
	ePropCouponErr, //礼券不够
	ePropOtherErr //其它错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EPropResult);
bool EnumStrToVal(const char*, EPropResult&);
#endif //PROT_USE_XML

//兑换结果
enum EExchangeResult
{
	eExchangeResultSuccess = 0, //兑换成功
	eExchangeResultFailed, //兑换失败
	eExchangeResultLack, //兑换数量不足
	eExchangeResultLimit, //兑换已达上限
	eExchangeResultMax //兑换结果最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EExchangeResult);
bool EnumStrToVal(const char*, EExchangeResult&);
#endif //PROT_USE_XML

//属性信息
struct SPropValue
{
	EPropType ePropType; //属性类型
	UINT32 value; //属性值，需要根据类型来转换

	SPropValue();
	SPropValue(EPropType ePropType_, UINT32 value_);
};

typedef std::vector<SPropValue> TVecPropValue;

//属性信息
struct SPropQWValue
{
	EPropType ePropType; //属性类型
	UINT64 value; //属性值，需要根据类型来转换

	SPropQWValue();
	SPropQWValue(EPropType ePropType_, UINT64 value_);
};

typedef std::vector<SPropQWValue> TVecPropQWValue;

//扩展属性信息
struct SPropValExt
{
	EPropType ePropType; //属性类型
	float value; //属性值，需要根据类型来转换
	INT32 ext; //扩展值，不同用途作不同的解释

	SPropValExt();
	SPropValExt(EPropType ePropType_, float value_, INT32 ext_);
};

typedef std::vector<SPropValExt> TVecPropValExt;

//扩展属性信息
struct SPropQWValExt
{
	EPropType ePropType; //属性类型
	UINT64 value; //属性值，需要根据类型来转换
	INT32 ext; //扩展值，不同用途作不同的解释

	SPropQWValExt();
	SPropQWValExt(EPropType ePropType_, UINT64 value_, INT32 ext_);
};

typedef std::vector<SPropQWValExt> TVecPropQWValExt;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SPropValue&);
COutArchive& operator<<(COutArchive&, const SPropValue&);

CInArchive& operator>>(CInArchive&, SPropQWValue&);
COutArchive& operator<<(COutArchive&, const SPropQWValue&);

CInArchive& operator>>(CInArchive&, SPropValExt&);
COutArchive& operator<<(COutArchive&, const SPropValExt&);

CInArchive& operator>>(CInArchive&, SPropQWValExt&);
COutArchive& operator<<(COutArchive&, const SPropQWValExt&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SPropValue&);
bool ToXML(const SPropValue&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPropValue&);
bool VectorToXML(const TVecPropValue&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPropQWValue&);
bool ToXML(const SPropQWValue&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPropQWValue&);
bool VectorToXML(const TVecPropQWValue&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPropValExt&);
bool ToXML(const SPropValExt&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPropValExt&);
bool VectorToXML(const TVecPropValExt&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPropQWValExt&);
bool ToXML(const SPropQWValExt&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPropQWValExt&);
bool VectorToXML(const TVecPropQWValExt&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NPropInfo
