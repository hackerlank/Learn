/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Formation.h
//  Purpose:      阵灵相关协议
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
#include "RoleInfoDefine.h"

namespace NFormationProt
{

/////////////////////以下为类型定义/////////////////////
//阵型解锁属性
enum EFormationAttr
{
	eFormAttrNone, //无加成
	eFormAttrSpeed, //身法
	eFormAttrHit, //命中
	eFormAttrEva, //闪避
	eFormAttrCrit, //暴击
	eFormAttrAntiCrit, //抗暴
	eFormAttrCount, //反击
	eFormAttrAntiCount, //抵抗
	eFormAttrAp, //破击
	eFormAttrMax //最大
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EFormationAttr);
bool EnumStrToVal(const char*, EFormationAttr&);
#endif //PROT_USE_XML

//阵形、阵灵、兽魂操作结果
enum EFormPetType
{
	eFormPetSucc, //成功
	eFormPetFalied, //失败
	eFormPetMainFighterErr, //主将不能下阵
	eFormPetItemErr, //解锁道具不足
	eFormPetPetLevelItemErr //阵灵升级道具不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EFormPetType);
bool EnumStrToVal(const char*, EFormPetType&);
#endif //PROT_USE_XML

//兽魂操作返回结果
enum EBeastSoulResult
{
	eBeastSoulSucces = 0, //操作成功
	eBeastSoulFailed, //操作失败
	eBeastSoulLackOfMoney, //对应货币不足
	eBeastSoulRankMax, //已经是最大等级
	eBeastSoulLevelLimit //玩家等级不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBeastSoulResult);
bool EnumStrToVal(const char*, EBeastSoulResult&);
#endif //PROT_USE_XML

//阵型信息
struct SLineup
{
	UINT64 qwInstID; //散仙唯一ID
	INT32 iPos; //位置

	SLineup();
	SLineup(UINT64 qwInstID_, INT32 iPos_);
};

typedef std::vector<SLineup> TVecSLineup;

//兽魂奖励道具信息
struct SBeastSoulItem
{
	UINT16 wItemID; //模板ID
	UINT32 dwCount; //数量

	SBeastSoulItem();
	SBeastSoulItem(UINT16 wItemID_, UINT32 dwCount_);
};

typedef std::vector<SBeastSoulItem> TVecBeastSoulItem;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SLineup&);
COutArchive& operator<<(COutArchive&, const SLineup&);

CInArchive& operator>>(CInArchive&, SBeastSoulItem&);
COutArchive& operator<<(COutArchive&, const SBeastSoulItem&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SLineup&);
bool ToXML(const SLineup&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSLineup&);
bool VectorToXML(const TVecSLineup&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBeastSoulItem&);
bool ToXML(const SBeastSoulItem&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBeastSoulItem&);
bool VectorToXML(const TVecBeastSoulItem&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NFormationProt
