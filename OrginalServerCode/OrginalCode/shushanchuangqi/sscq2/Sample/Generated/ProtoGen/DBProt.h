/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DBProt.h
//  Purpose:      数据库查询协议
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

namespace NDBProt
{

/////////////////////以下为类型定义/////////////////////
//查询参数的类型
enum EParamType
{
	eTypeINT8 = 1, //INT8类型
	eTypeUINT8, //UINT8类型
	eTypeINT16, //INT16类型
	eTypeUINT16, //UINT16类型
	eTypeINT32, //INT32类型
	eTypeUINT32, //UINT32类型
	eTypeINT64, //INT64类型
	eTypeUINT64, //UINT64类型
	eTypeFloat, //float类型
	eTypeDouble, //double类型
	eTypeString, //string类型
	eTypeBlob, //Blob类型
	eTypeDateTime, //DateTime类型
	eTypeDate, //Date类型
	eTypeTime //Time类型
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EParamType);
bool EnumStrToVal(const char*, EParamType&);
#endif //PROT_USE_XML

//查询的类型
enum EQueryType
{
	eQueryNormal, //普通的查询
	eQuerySave0, //保存玩家数据的查询
	eQuerySave1, //保存玩家数据的查询
	eQuerySave2, //保存玩家数据的查询
	eQuerySave3, //保存玩家数据的查询
	eQuerySaveMax, //保存玩家数据的查询最大
	eQueryMail, //邮件相关的查询
	eQueryArena, //斗剑相关查询
	eQueryGuild, //帮派相关查询
	eQueryRank, //排行榜相关查询
	eQueryRecharge, //充值相关查询
	eQueryEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EQueryType);
bool EnumStrToVal(const char*, EQueryType&);
#endif //PROT_USE_XML

//查询的参数
struct SParam
{
	EParamType eType; //类型
	std::string strVal; //序列化后的值

	SParam();
	SParam(EParamType eType_, const std::string& strVal_);
#ifdef __GNUG__
	SParam(const SParam& src) = default; //默认拷贝构造函数
	SParam& operator=(const SParam& rhs) = default; //默认赋值操作符
#endif
	SParam(SParam&& src); //转移构造函数
	SParam& operator=(SParam&& rhs); //转移赋值操作符
};

typedef std::vector<SParam> TVecParam;

//查询
struct SQuery
{
	std::string strQuery; //查询字符串
	TVecParam vecParam; //参数列表
	bool bHasResult; //是否有结果集

	SQuery();
	SQuery(const std::string& strQuery_, const TVecParam& vecParam_, bool bHasResult_);
#ifdef __GNUG__
	SQuery(const SQuery& src) = default; //默认拷贝构造函数
	SQuery& operator=(const SQuery& rhs) = default; //默认赋值操作符
#endif
	SQuery(SQuery&& src); //转移构造函数
	SQuery& operator=(SQuery&& rhs); //转移赋值操作符
};

//查询的一个属性的结果
struct SRes
{
	std::string strVal; //序列化后的值

	SRes();
	SRes(const std::string& strVal_);
#ifdef __GNUG__
	SRes(const SRes& src) = default; //默认拷贝构造函数
	SRes& operator=(const SRes& rhs) = default; //默认赋值操作符
#endif
	SRes(SRes&& src); //转移构造函数
	SRes& operator=(SRes&& rhs); //转移赋值操作符
};

typedef std::vector<SRes> TVecRes;

//查询的一行结果集
struct SRow
{
	TVecRes vecRes; //属性结果的列表

	SRes& operator[](size_t index);
	const SRes& operator[](size_t index) const;
	bool Empty() const;
	size_t Size() const;

	SRow();
	SRow(const TVecRes& vecRes_);
#ifdef __GNUG__
	SRow(const SRow& src) = default; //默认拷贝构造函数
	SRow& operator=(const SRow& rhs) = default; //默认赋值操作符
#endif
	SRow(SRow&& src); //转移构造函数
	SRow& operator=(SRow&& rhs); //转移赋值操作符
};

typedef std::vector<SRow> TVecRow;

//查询的多行结果组成的一张表
struct STable
{
	UINT8 byIndex; //结果表对应查询中SQL语句的索引(从0开始)
	bool bMore; //是否有更多的结果
	TVecRow vecRow; //所有行结果的列表

	SRow& operator[](size_t index);
	const SRow& operator[](size_t index) const;
	bool Empty() const;
	size_t Size() const;

	STable();
	STable(UINT8 byIndex_, bool bMore_, const TVecRow& vecRow_);
#ifdef __GNUG__
	STable(const STable& src) = default; //默认拷贝构造函数
	STable& operator=(const STable& rhs) = default; //默认赋值操作符
#endif
	STable(STable&& src); //转移构造函数
	STable& operator=(STable&& rhs); //转移赋值操作符
};

typedef std::vector<STable> TVecTable;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SParam&);
COutArchive& operator<<(COutArchive&, const SParam&);

CInArchive& operator>>(CInArchive&, SQuery&);
COutArchive& operator<<(COutArchive&, const SQuery&);

CInArchive& operator>>(CInArchive&, SRes&);
COutArchive& operator<<(COutArchive&, const SRes&);

CInArchive& operator>>(CInArchive&, SRow&);
COutArchive& operator<<(COutArchive&, const SRow&);

CInArchive& operator>>(CInArchive&, STable&);
COutArchive& operator<<(COutArchive&, const STable&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SParam&);
bool ToXML(const SParam&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecParam&);
bool VectorToXML(const TVecParam&, TiXmlElement&);

bool FromXML(TiXmlElement&, SQuery&);
bool ToXML(const SQuery&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRes&);
bool ToXML(const SRes&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRes&);
bool VectorToXML(const TVecRes&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRow&);
bool ToXML(const SRow&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRow&);
bool VectorToXML(const TVecRow&, TiXmlElement&);

bool FromXML(TiXmlElement&, STable&);
bool ToXML(const STable&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTable&);
bool VectorToXML(const TVecTable&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NDBProt
