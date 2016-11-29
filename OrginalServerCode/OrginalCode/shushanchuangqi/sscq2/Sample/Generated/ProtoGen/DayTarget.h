/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DayTarget.h
//  Purpose:      七日目标活动
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

namespace NDayTarget
{

/////////////////////以下为类型定义/////////////////////
//错误码
enum EDayTargetRet
{
	eDayTargetRet_Sucess = 0, //成功
	eDayTargetRet_NotFinish, //任务未完成
	eDayTargetRet_DayLimit, //未到领奖天数
	eDayTargetRet_TakePrized, //已经领过奖励
	eDayTargetRet_CFGError, //基础配置错误
	eDayTargetRet_PackFull //背包空间不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDayTargetRet);
bool EnumStrToVal(const char*, EDayTargetRet&);
#endif //PROT_USE_XML

//任务状态
enum EDayTargeTasktStatus
{
	eDayTargetTaskStatus_Init = 0, //任务未完成
	eDayTargetTaskStatus_Finish, //任务完成
	eDayTargetTaskStatus_TakePrized //任务已领奖
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDayTargeTasktStatus);
bool EnumStrToVal(const char*, EDayTargeTasktStatus&);
#endif //PROT_USE_XML

//任务信息列表
struct SDayTargetTask
{
	UINT16 wTaskID; //任务ID
	EDayTargeTasktStatus eTaskStatus; //任务状态
	UINT32 dwParam; //进度

	SDayTargetTask();
	SDayTargetTask(UINT16 wTaskID_, EDayTargeTasktStatus eTaskStatus_, UINT32 dwParam_);
};

typedef std::vector<SDayTargetTask> TVecDayTargetTask;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SDayTargetTask&);
COutArchive& operator<<(COutArchive&, const SDayTargetTask&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SDayTargetTask&);
bool ToXML(const SDayTargetTask&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDayTargetTask&);
bool VectorToXML(const TVecDayTargetTask&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NDayTarget
