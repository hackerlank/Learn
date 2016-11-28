/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DemonTower.h
//  Purpose:      锁妖塔
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

namespace NDemonTower
{

/////////////////////以下为类型定义/////////////////////
//被攻击类型
enum EAttackedType
{
	eAttackedType_DemonTower = 1 //锁妖塔
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EAttackedType);
bool EnumStrToVal(const char*, EAttackedType&);
#endif //PROT_USE_XML
const char* GetDescription(EAttackedType);

//魄空间列表
struct SSpaceInfo
{
	UINT32 dwSoulSpaceID; //魄空间id
	UINT32 dwSoulSpaceLevel; //魄空间等级

	SSpaceInfo();
	SSpaceInfo(UINT32 dwSoulSpaceID_, UINT32 dwSoulSpaceLevel_);
};

typedef std::vector<SSpaceInfo> TVecSpaceInfo;

//被攻击列表
struct SRoleAttaked
{
	UINT64 qwRoleID; //角色ID
	UINT32 dwPos; //存储位置
	UINT64 qwAtkRoleID; //攻击角色ID
	std::string strRoleName; //角色名
	UINT8 byLevel; //等级
	UINT32 dwAttackedTime; //攻击时间
	UINT32 dwFighterType; //战斗类型

	SRoleAttaked();
	SRoleAttaked(UINT64 qwRoleID_, UINT32 dwPos_, UINT64 qwAtkRoleID_, const std::string& strRoleName_, UINT8 byLevel_, 
		UINT32 dwAttackedTime_, UINT32 dwFighterType_);
#ifdef __GNUG__
	SRoleAttaked(const SRoleAttaked& src) = default; //默认拷贝构造函数
	SRoleAttaked& operator=(const SRoleAttaked& rhs) = default; //默认赋值操作符
#endif
	SRoleAttaked(SRoleAttaked&& src); //转移构造函数
	SRoleAttaked& operator=(SRoleAttaked&& rhs); //转移赋值操作符
};

typedef std::vector<SRoleAttaked> TVecRoleAttaked;

//锁妖塔被攻击列表
struct SDemonToweAttackedInfo
{
	UINT64 qwAtkRoleID; //攻击角色ID
	std::string strRoleName; //角色名
	UINT32 dwLayerID; //层数
	UINT8 byLevel; //等级
	UINT32 dwAttackedTime; //攻击时间

	SDemonToweAttackedInfo();
	SDemonToweAttackedInfo(UINT64 qwAtkRoleID_, const std::string& strRoleName_, UINT32 dwLayerID_, UINT8 byLevel_, UINT32 dwAttackedTime_);
#ifdef __GNUG__
	SDemonToweAttackedInfo(const SDemonToweAttackedInfo& src) = default; //默认拷贝构造函数
	SDemonToweAttackedInfo& operator=(const SDemonToweAttackedInfo& rhs) = default; //默认赋值操作符
#endif
	SDemonToweAttackedInfo(SDemonToweAttackedInfo&& src); //转移构造函数
	SDemonToweAttackedInfo& operator=(SDemonToweAttackedInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SDemonToweAttackedInfo> TVecDemonToweAttackedInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SSpaceInfo&);
COutArchive& operator<<(COutArchive&, const SSpaceInfo&);

CInArchive& operator>>(CInArchive&, SRoleAttaked&);
COutArchive& operator<<(COutArchive&, const SRoleAttaked&);

CInArchive& operator>>(CInArchive&, SDemonToweAttackedInfo&);
COutArchive& operator<<(COutArchive&, const SDemonToweAttackedInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SSpaceInfo&);
bool ToXML(const SSpaceInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSpaceInfo&);
bool VectorToXML(const TVecSpaceInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoleAttaked&);
bool ToXML(const SRoleAttaked&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoleAttaked&);
bool VectorToXML(const TVecRoleAttaked&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDemonToweAttackedInfo&);
bool ToXML(const SDemonToweAttackedInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDemonToweAttackedInfo&);
bool VectorToXML(const TVecDemonToweAttackedInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NDemonTower
