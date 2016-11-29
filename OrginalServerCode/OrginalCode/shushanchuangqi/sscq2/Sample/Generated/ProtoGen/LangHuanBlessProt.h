/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LangHuanBlessProt.h
//  Purpose:      中午挂机活动
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

namespace NLangHuanBlessProt
{

/////////////////////以下为类型定义/////////////////////
//操作结果
enum ELHBResult
{
	eLHBResult_none, //无此技能
	eLHBResult_empty, //次数用完
	eLHBResult_inCD, //技能CD中
	eLHBResult_hasBuff, //身上有Buff
	eLHBResult_success, //操作成功
	eLHBResult_CMapError, //创建地图失败
	eLHBResult_enterMapError, //进入地图失败
	eLHBResult_otherError, //其他错误
	eLHBResult_lowLevel, //玩家等级不够
	eLHBResult_notBegin, //活动未开始
	eLHBResult_end, //玩家已经结束
	eLHBResult_wait5min //玩家逃跑需要等待5分钟
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELHBResult);
bool EnumStrToVal(const char*, ELHBResult&);
#endif //PROT_USE_XML

//活动状态
enum ELHBState
{
	eLHBState_none, //无状态
	eLHBState_alarm, //警告
	eLHBState_ready, //报名开始
	eLHBState_begin, //活动开始
	eLHBState_end //活动结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELHBState);
bool EnumStrToVal(const char*, ELHBState&);
#endif //PROT_USE_XML

//技能类型
enum ELHBSkillType
{
	eLHBSkillType_eNone, //无技能
	eLHBSkillType_eAskTaoism, //问道技能
	eLHBSkillType_eTalkTaoism, //论道技能
	eLHBSkillType_eWander, //开小差技能
	eLHBSkillType_eSit, //打坐技能
	eLHBSkillType_max //技能最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELHBSkillType);
bool EnumStrToVal(const char*, ELHBSkillType&);
#endif //PROT_USE_XML

//技能信息
struct SLHBSkillInfo
{
	ELHBSkillType eLHBSkillType; //技能类型
	UINT8 byCD; //技能CD
	UINT32 wScore; //修为值
	UINT8 byTimes; //使用次数

	SLHBSkillInfo();
	SLHBSkillInfo(ELHBSkillType eLHBSkillType_, UINT8 byCD_, UINT32 wScore_, UINT8 byTimes_);
};

typedef std::vector<SLHBSkillInfo> TVecLHBSkillInfo;

//总的信息
struct SLHBTotalInfo
{
	ELHBState byState; //活动状态
	UINT32 dwTime; //玩家持续时间
	UINT32 dwXiuwei; //获得的修为值
	UINT32 dwExp; //获得的经验值
	TVecLHBSkillInfo vecLHBSkillInfo; //技能使用信息

	SLHBTotalInfo();
	SLHBTotalInfo(ELHBState byState_, UINT32 dwTime_, UINT32 dwXiuwei_, UINT32 dwExp_, const TVecLHBSkillInfo& vecLHBSkillInfo_);
#ifdef __GNUG__
	SLHBTotalInfo(const SLHBTotalInfo& src) = default; //默认拷贝构造函数
	SLHBTotalInfo& operator=(const SLHBTotalInfo& rhs) = default; //默认赋值操作符
#endif
	SLHBTotalInfo(SLHBTotalInfo&& src); //转移构造函数
	SLHBTotalInfo& operator=(SLHBTotalInfo&& rhs); //转移赋值操作符
};

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SLHBSkillInfo&);
COutArchive& operator<<(COutArchive&, const SLHBSkillInfo&);

CInArchive& operator>>(CInArchive&, SLHBTotalInfo&);
COutArchive& operator<<(COutArchive&, const SLHBTotalInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SLHBSkillInfo&);
bool ToXML(const SLHBSkillInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecLHBSkillInfo&);
bool VectorToXML(const TVecLHBSkillInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SLHBTotalInfo&);
bool ToXML(const SLHBTotalInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NLangHuanBlessProt
