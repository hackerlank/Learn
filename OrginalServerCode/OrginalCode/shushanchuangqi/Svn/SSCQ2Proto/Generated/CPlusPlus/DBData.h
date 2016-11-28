/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DBData.h
//  Purpose:      数据库序列化结构
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

namespace NDBData
{

/////////////////////以下为类型定义/////////////////////
//帐号基本数据
struct SUserPropStream
{
	UINT32 dwGoldCoin; //仙石
	UINT32 dwHonour; //荣誉
	UINT8 byCamp; //阵营
	UINT32 dwLastLeaveTime; //最后一次下线时间

	SUserPropStream();
	SUserPropStream(UINT32 dwGoldCoin_, UINT32 dwHonour_, UINT8 byCamp_, UINT32 dwLastLeaveTime_);
};

//角色基本数据(战斗相关)
struct SBasePropStream
{
	UINT32 dwCurHP; //当前HP
	UINT32 dwCurMP; //当前MP
	UINT8 byElement; //元素属性
	UINT16 wUseTitleID; //当前使用称号
	UINT16 wUseHorseID; //当前骑乘坐骑

	SBasePropStream();
	SBasePropStream(UINT32 dwCurHP_, UINT32 dwCurMP_, UINT8 byElement_, UINT16 wUseTitleID_, UINT16 wUseHorseID_);
};

//角色附加数据
struct SExtPropStream
{
	UINT32 dwExp; //经验
	UINT32 dwDgnInstID; //副本实例ID
	UINT32 dwDgnCreateTime; //副本创建时间
	UINT16 wPreDgnMapID; //进入副本之前的地图ID
	float fPreDgnX; //进入副本之前的X坐标
	float fPreDgnY; //进入副本之前的Y坐标

	SExtPropStream();
	SExtPropStream(UINT32 dwExp_, UINT32 dwDgnInstID_, UINT32 dwDgnCreateTime_, UINT16 wPreDgnMapID_, float fPreDgnX_, 
		float fPreDgnY_);
};

//各种槽（物品槽，心法槽）
struct SSlotPropStream
{
	UINT64 dwRoleID; //角色ID
	UINT64 dwOwnerID; //拥有者实例ID
	UINT8 byStoreType; //槽类型
	UINT16 wSlotCount; //当前槽的数量

	SSlotPropStream();
	SSlotPropStream(UINT64 dwRoleID_, UINT64 dwOwnerID_, UINT8 byStoreType_, UINT16 wSlotCount_);
};

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SUserPropStream&);
COutArchive& operator<<(COutArchive&, const SUserPropStream&);

CInArchive& operator>>(CInArchive&, SBasePropStream&);
COutArchive& operator<<(COutArchive&, const SBasePropStream&);

CInArchive& operator>>(CInArchive&, SExtPropStream&);
COutArchive& operator<<(COutArchive&, const SExtPropStream&);

CInArchive& operator>>(CInArchive&, SSlotPropStream&);
COutArchive& operator<<(COutArchive&, const SSlotPropStream&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SUserPropStream&);
bool ToXML(const SUserPropStream&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBasePropStream&);
bool ToXML(const SBasePropStream&, TiXmlElement&);

bool FromXML(TiXmlElement&, SExtPropStream&);
bool ToXML(const SExtPropStream&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSlotPropStream&);
bool ToXML(const SSlotPropStream&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NDBData
