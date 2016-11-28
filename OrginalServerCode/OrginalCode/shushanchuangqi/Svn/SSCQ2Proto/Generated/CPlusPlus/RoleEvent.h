/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    RoleEvent.h
//  Purpose:      玩家在GameServer的消息处理
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
#include "FighterProt.h"
#include "ItemProt.h"
#include "ProtoCommon.h"
#include "RoleInfoDefine.h"

namespace NRoleEvent
{

/////////////////////以下为类型定义/////////////////////
//暴击类型
enum ECritType
{
	ePetCrit, //阵灵暴击
	eHorseCrit, //坐骑暴击
	eFashionCrit, //时装暴击
	eTrumpCrit, //法宝暴击
	eDujieCrit, //渡劫暴击
	eMoneyTreeCrit //摇钱树暴击
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECritType);
bool EnumStrToVal(const char*, ECritType&);
#endif //PROT_USE_XML

//暴击倍数
enum ECritMultiple
{
	eTwoMultipleCrit, //2倍暴击
	eFiveMultipleCrit, //5倍暴击
	eTenMultipleCrit //10倍暴击
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECritMultiple);
bool EnumStrToVal(const char*, ECritMultiple&);
#endif //PROT_USE_XML

//面板散仙信息
struct SFighterSpecInfo
{
	NItemProt::TVecItem oEquips; //散仙所有装备信息
	NFighterProt::SFighterInfo oFighterInfo; //散仙基本信息

	SFighterSpecInfo();
#ifdef __GNUG__
	SFighterSpecInfo(const SFighterSpecInfo& src) = default; //默认拷贝构造函数
	SFighterSpecInfo& operator=(const SFighterSpecInfo& rhs) = default; //默认赋值操作符
#endif
	SFighterSpecInfo(SFighterSpecInfo&& src); //转移构造函数
	SFighterSpecInfo& operator=(SFighterSpecInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SFighterSpecInfo> TVecFighterSpecInfo;

//散仙信息
struct SRoleFighterStream
{
	SFighterSpecInfo oMainFighter; //主散仙的信息
	TVecFighterSpecInfo oFighters; //所有散仙的信息

	SRoleFighterStream();
	SRoleFighterStream(const SFighterSpecInfo& oMainFighter_, const TVecFighterSpecInfo& oFighters_);
#ifdef __GNUG__
	SRoleFighterStream(const SRoleFighterStream& src) = default; //默认拷贝构造函数
	SRoleFighterStream& operator=(const SRoleFighterStream& rhs) = default; //默认赋值操作符
#endif
	SRoleFighterStream(SRoleFighterStream&& src); //转移构造函数
	SRoleFighterStream& operator=(SRoleFighterStream&& rhs); //转移赋值操作符
};

//面板散仙信息
struct SRoleStream
{
	SFighterSpecInfo oMainFighter; //主散仙的信息

	SRoleStream();
	SRoleStream(const SFighterSpecInfo& oMainFighter_);
#ifdef __GNUG__
	SRoleStream(const SRoleStream& src) = default; //默认拷贝构造函数
	SRoleStream& operator=(const SRoleStream& rhs) = default; //默认赋值操作符
#endif
	SRoleStream(SRoleStream&& src); //转移构造函数
	SRoleStream& operator=(SRoleStream&& rhs); //转移赋值操作符
};

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SFighterSpecInfo&);
COutArchive& operator<<(COutArchive&, const SFighterSpecInfo&);

CInArchive& operator>>(CInArchive&, SRoleFighterStream&);
COutArchive& operator<<(COutArchive&, const SRoleFighterStream&);

CInArchive& operator>>(CInArchive&, SRoleStream&);
COutArchive& operator<<(COutArchive&, const SRoleStream&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SFighterSpecInfo&);
bool ToXML(const SFighterSpecInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFighterSpecInfo&);
bool VectorToXML(const TVecFighterSpecInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoleFighterStream&);
bool ToXML(const SRoleFighterStream&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoleStream&);
bool ToXML(const SRoleStream&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NRoleEvent
