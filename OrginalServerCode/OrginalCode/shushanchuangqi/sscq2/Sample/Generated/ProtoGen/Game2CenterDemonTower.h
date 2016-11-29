/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Game2CenterDemonTower.h
//  Purpose:      GameServer到CenterServer关于镇妖塔的通信协议
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
#include "DemonTower.h"

namespace NGame2CenterDemonTower
{

/////////////////////以下为类型定义/////////////////////
//进入镇妖塔玩家信息
struct SDemonTowerEnterPlayer
{
	UINT64 qwUserID; //账号Id
	UINT64 qwRoleID; //角色Id
	std::string strName; //角色名
	UINT32 dwFloorID; //楼层
	UINT8 bySex; //性别
	UINT16 byLevel; //等级
	UINT32 dwCareer; //职业
	UINT32 dwPower; //战斗力

	SDemonTowerEnterPlayer();
	SDemonTowerEnterPlayer(UINT64 qwUserID_, UINT64 qwRoleID_, const std::string& strName_, UINT32 dwFloorID_, UINT8 bySex_, 
		UINT16 byLevel_, UINT32 dwCareer_, UINT32 dwPower_);
#ifdef __GNUG__
	SDemonTowerEnterPlayer(const SDemonTowerEnterPlayer& src) = default; //默认拷贝构造函数
	SDemonTowerEnterPlayer& operator=(const SDemonTowerEnterPlayer& rhs) = default; //默认赋值操作符
#endif
	SDemonTowerEnterPlayer(SDemonTowerEnterPlayer&& src); //转移构造函数
	SDemonTowerEnterPlayer& operator=(SDemonTowerEnterPlayer&& rhs); //转移赋值操作符
};

//镇妖塔玩家击败怪物信息
struct SDemonTowerPassPlayer
{
	UINT32 dwCurFloorID; //当前楼层
	UINT64 qwUserID; //账号Id
	UINT32 dwPower; //战斗力
	UINT16 wTurns; //回合数
	UINT64 qwReportID; //战报id

	SDemonTowerPassPlayer();
	SDemonTowerPassPlayer(UINT32 dwCurFloorID_, UINT64 qwUserID_, UINT32 dwPower_, UINT16 wTurns_, UINT64 qwReportID_);
};

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SDemonTowerEnterPlayer&);
COutArchive& operator<<(COutArchive&, const SDemonTowerEnterPlayer&);

CInArchive& operator>>(CInArchive&, SDemonTowerPassPlayer&);
COutArchive& operator<<(COutArchive&, const SDemonTowerPassPlayer&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SDemonTowerEnterPlayer&);
bool ToXML(const SDemonTowerEnterPlayer&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDemonTowerPassPlayer&);
bool ToXML(const SDemonTowerPassPlayer&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGame2CenterDemonTower
