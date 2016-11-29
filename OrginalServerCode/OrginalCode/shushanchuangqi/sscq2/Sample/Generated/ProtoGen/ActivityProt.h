/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Activity.h
//  Purpose:      活力任务协议
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

namespace NActivityProt
{

/////////////////////以下为类型定义/////////////////////
//任务的结果
enum EActivityResult
{
	eActivitySucceed, //成功
	eActivityMin, //活力度不足
	eActivityTotalMin, //累计活力值不足
	eActivityPackNoSpace, //背包不足
	eActivityHasGet, //奖励已领取
	eActivityVip, //御剑等级不足
	eActivityErrOther, //其它错误
	eActivityNotFinish //任务未完成
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EActivityResult);
bool EnumStrToVal(const char*, EActivityResult&);
#endif //PROT_USE_XML

//成就完成进度
enum EShareStatus
{
	eShareStatus_Init = 0, //未完成
	eShareStatus_Finish, //已完成
	eShareStatus_TakePrize //已领奖
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EShareStatus);
bool EnumStrToVal(const char*, EShareStatus&);
#endif //PROT_USE_XML
const char* GetDescription(EShareStatus);

//每日已领活力奖励
struct SActivityAward
{
	UINT8 byId; //奖励ID
	UINT8 byVIP; //是否VIP

	SActivityAward();
	SActivityAward(UINT8 byId_, UINT8 byVIP_);
};

typedef std::vector<SActivityAward> TVecActivityAward;

//活力任务信息
struct SActivityInfoForClient
{
	UINT32 dwTotolActivity; //累计活力值
	UINT16 wActivity; //当前活力
	NRoleInfoDefine::TVecActivityTaskInfo vecActivityTask; //活力监测点
	TVecActivityAward vecActivityAward; //已领活力

	SActivityInfoForClient();
	SActivityInfoForClient(UINT32 dwTotolActivity_, UINT16 wActivity_, const NRoleInfoDefine::TVecActivityTaskInfo& vecActivityTask_, const TVecActivityAward& vecActivityAward_);
#ifdef __GNUG__
	SActivityInfoForClient(const SActivityInfoForClient& src) = default; //默认拷贝构造函数
	SActivityInfoForClient& operator=(const SActivityInfoForClient& rhs) = default; //默认赋值操作符
#endif
	SActivityInfoForClient(SActivityInfoForClient&& src); //转移构造函数
	SActivityInfoForClient& operator=(SActivityInfoForClient&& rhs); //转移赋值操作符
};

typedef std::vector<SActivityInfoForClient> TVecActivityInfo;

//活力分享列表
struct SActivityShare
{
	UINT32 dwActivityID; //活跃度ID
	EShareStatus eStatus; //分享状态

	SActivityShare();
	SActivityShare(UINT32 dwActivityID_, EShareStatus eStatus_);
};

typedef std::vector<SActivityShare> TVecActivityShare;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SActivityAward&);
COutArchive& operator<<(COutArchive&, const SActivityAward&);

CInArchive& operator>>(CInArchive&, SActivityInfoForClient&);
COutArchive& operator<<(COutArchive&, const SActivityInfoForClient&);

CInArchive& operator>>(CInArchive&, SActivityShare&);
COutArchive& operator<<(COutArchive&, const SActivityShare&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SActivityAward&);
bool ToXML(const SActivityAward&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecActivityAward&);
bool VectorToXML(const TVecActivityAward&, TiXmlElement&);

bool FromXML(TiXmlElement&, SActivityInfoForClient&);
bool ToXML(const SActivityInfoForClient&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecActivityInfo&);
bool VectorToXML(const TVecActivityInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SActivityShare&);
bool ToXML(const SActivityShare&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecActivityShare&);
bool VectorToXML(const TVecActivityShare&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NActivityProt
