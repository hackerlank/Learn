/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    FightFormation.h
//  Purpose:      新阵型相关协议
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

namespace NFightFormation
{

/////////////////////以下为类型定义/////////////////////
//新阵型相关协议
enum EFightFormationResult
{
	eFightFormationResult_Succes = 0, //操作成功
	eFightFormationResult_Fail = 1 //设置错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EFightFormationResult);
bool EnumStrToVal(const char*, EFightFormationResult&);
#endif //PROT_USE_XML

//阵型信息
struct SBattlePosInfo
{
	UINT64 qwInstID; //散仙唯一ID
	INT8 byPos; //位置

	SBattlePosInfo();
	SBattlePosInfo(UINT64 qwInstID_, INT8 byPos_);
};

typedef std::vector<SBattlePosInfo> TVecBattlePosInfo;

//战斗阵型信息
struct FightFormationInfo
{
	UINT16 wFormationID; //当前阵形ID
	TVecBattlePosInfo vecBattlePosInfo; //位置

	FightFormationInfo();
	FightFormationInfo(UINT16 wFormationID_, const TVecBattlePosInfo& vecBattlePosInfo_);
#ifdef __GNUG__
	FightFormationInfo(const FightFormationInfo& src) = default; //默认拷贝构造函数
	FightFormationInfo& operator=(const FightFormationInfo& rhs) = default; //默认赋值操作符
#endif
	FightFormationInfo(FightFormationInfo&& src); //转移构造函数
	FightFormationInfo& operator=(FightFormationInfo&& rhs); //转移赋值操作符
};

typedef std::vector<FightFormationInfo> TVecFightFormationInfo;

//战斗散仙信息
struct FightHeroInfo
{
	UINT64 qwInstID; //散仙InstID
	UINT32 dwHP; //当前生命值
	UINT32 dwMaxHP; //最大生命值（可能用到）
	UINT32 dwAura; //灵气值
	UINT32 dwMaxAura; //最大灵气值

	FightHeroInfo();
	FightHeroInfo(UINT64 qwInstID_, UINT32 dwHP_, UINT32 dwMaxHP_, UINT32 dwAura_, UINT32 dwMaxAura_);
};

typedef std::vector<FightHeroInfo> TVecFightHeroInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SBattlePosInfo&);
COutArchive& operator<<(COutArchive&, const SBattlePosInfo&);

CInArchive& operator>>(CInArchive&, FightFormationInfo&);
COutArchive& operator<<(COutArchive&, const FightFormationInfo&);

CInArchive& operator>>(CInArchive&, FightHeroInfo&);
COutArchive& operator<<(COutArchive&, const FightHeroInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SBattlePosInfo&);
bool ToXML(const SBattlePosInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattlePosInfo&);
bool VectorToXML(const TVecBattlePosInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, FightFormationInfo&);
bool ToXML(const FightFormationInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFightFormationInfo&);
bool VectorToXML(const TVecFightFormationInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, FightHeroInfo&);
bool ToXML(const FightHeroInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFightHeroInfo&);
bool VectorToXML(const TVecFightHeroInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NFightFormation
