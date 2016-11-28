/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Horse.h
//  Purpose:      坐骑
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

namespace NHorse
{

/////////////////////以下为类型定义/////////////////////
//骑乘状态
enum EHorseStatus
{
	eHorseStatusUnMount, //下马
	eHorseStatusMounted //上马
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EHorseStatus);
bool EnumStrToVal(const char*, EHorseStatus&);
#endif //PROT_USE_XML

//坐骑信息更新类型
enum EHorseOpType
{
	eHorseOpType_Add, //添加坐骑
	eHorseOpType_Update //更新坐骑信息
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EHorseOpType);
bool EnumStrToVal(const char*, EHorseOpType&);
#endif //PROT_USE_XML

//坐骑数据库数据
struct SHorseDB
{
	UINT64 qwRoleID; //角色id
	UINT64 qwUserID; //账号
	UINT32 dwHorseID; //坐骑id
	UINT32 dwHorseLevel; //坐骑等级
	UINT32 dwPos; //坐骑位置1表示骑乘
	UINT32 dwModelID; //坐骑模型id
	UINT32 dwExp; //坐骑当前经验
	UINT32 dwLock; //坐骑技能锁定
	std::string strModel; //坐骑外观列表

	SHorseDB();
	SHorseDB(UINT64 qwRoleID_, UINT64 qwUserID_, UINT32 dwHorseID_, UINT32 dwHorseLevel_, UINT32 dwPos_, 
		UINT32 dwModelID_, UINT32 dwExp_, UINT32 dwLock_, const std::string& strModel_);
#ifdef __GNUG__
	SHorseDB(const SHorseDB& src) = default; //默认拷贝构造函数
	SHorseDB& operator=(const SHorseDB& rhs) = default; //默认赋值操作符
#endif
	SHorseDB(SHorseDB&& src); //转移构造函数
	SHorseDB& operator=(SHorseDB&& rhs); //转移赋值操作符
};

typedef std::vector<SHorseDB> TVecHorseDB;

//坐骑信息
struct SHorseInfo
{
	UINT32 dwHorseID; //坐骑id
	UINT32 dwHorseLevel; //坐骑等阶
	UINT32 dwExp; //坐骑当前经验
	UINT32 dwPos; //骑乘状态
	TVecUINT32 vecHorseID; //坐骑外观列表

	SHorseInfo();
	SHorseInfo(UINT32 dwHorseID_, UINT32 dwHorseLevel_, UINT32 dwExp_, UINT32 dwPos_, const TVecUINT32& vecHorseID_);
};

typedef std::vector<SHorseInfo> TVecHorseInfo;

//属性信息表
struct SAttrInfo
{
	UINT32 dwAttrType; //属性类型id
	float fAttrValue; //属性值

	SAttrInfo();
	SAttrInfo(UINT32 dwAttrType_, float fAttrValue_);
};

typedef std::vector<SAttrInfo> TVecAttrInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SHorseDB&);
COutArchive& operator<<(COutArchive&, const SHorseDB&);

CInArchive& operator>>(CInArchive&, SHorseInfo&);
COutArchive& operator<<(COutArchive&, const SHorseInfo&);

CInArchive& operator>>(CInArchive&, SAttrInfo&);
COutArchive& operator<<(COutArchive&, const SAttrInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SHorseDB&);
bool ToXML(const SHorseDB&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecHorseDB&);
bool VectorToXML(const TVecHorseDB&, TiXmlElement&);

bool FromXML(TiXmlElement&, SHorseInfo&);
bool ToXML(const SHorseInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecHorseInfo&);
bool VectorToXML(const TVecHorseInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SAttrInfo&);
bool ToXML(const SAttrInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecAttrInfo&);
bool VectorToXML(const TVecAttrInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NHorse
