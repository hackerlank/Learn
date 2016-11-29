/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    CompareBattlePoint.h
//  Purpose:      变强(战力对比)相关协议
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

namespace NCompareBattlePoint
{

/////////////////////以下为类型定义/////////////////////
//对比的数据结构
struct SCompareData
{
	UINT64 qwRoleID; //玩家ID
	std::string strName; //玩家名字
	UINT8 byLevel; //玩家等级
	NProtoCommon::ECareerType eCareer; //玩家主将职业
	NProtoCommon::ESexType eSex; //玩家主将性别
	UINT32 dwBattlePoint; //玩家总战斗力
	UINT32 dwHeroBP; //散仙的战斗力(渡劫和心法除外)
	UINT32 dwBeautyBP; //美女系统战斗力
	UINT32 dwTrumpBP; //法宝战斗力
	UINT32 dwHorseBP; //坐骑战斗力
	UINT32 dwDujieBP; //渡劫战斗力
	UINT32 dwXinfaBP; //心法战斗力
	UINT32 dwClanBP; //帮派战斗力

	SCompareData();
#ifdef __GNUG__
	SCompareData(const SCompareData& src) = default; //默认拷贝构造函数
	SCompareData& operator=(const SCompareData& rhs) = default; //默认赋值操作符
#endif
	SCompareData(SCompareData&& src); //转移构造函数
	SCompareData& operator=(SCompareData&& rhs); //转移赋值操作符
};

typedef std::vector<SCompareData> TVecCompareData;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SCompareData&);
COutArchive& operator<<(COutArchive&, const SCompareData&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SCompareData&);
bool ToXML(const SCompareData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCompareData&);
bool VectorToXML(const TVecCompareData&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NCompareBattlePoint
