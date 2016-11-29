/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GroupTaskProt.h
//  Purpose:      师门任务协议
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

namespace NGroupTaskProt
{

/////////////////////以下为类型定义/////////////////////
//任务的结果
enum EGroupTaskResult
{
	eGroupTaskSucceed, //成功
	eGroupTaskLowMoney, //钱不足
	eBuyTimesUpLimit, //购买次数已达上限
	eGroupSaveTimesUpLimit, //总次数已达上限
	eGroupTaskErrOther //其它错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGroupTaskResult);
bool EnumStrToVal(const char*, EGroupTaskResult&);
#endif //PROT_USE_XML

//清修的状态
enum EGroupStudyState
{
	eCanStudy, //可清修
	eStudied, //已清修
	eCanChallenge, //可挑战
	eChallenging //正挑战
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGroupStudyState);
bool EnumStrToVal(const char*, EGroupStudyState&);
#endif //PROT_USE_XML

//推任务的状态
enum EGroupTaskState
{
	eNone, //未接
	eAccept, //已接
	eFinish, //已完成
	eFal //已失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGroupTaskState);
bool EnumStrToVal(const char*, EGroupTaskState&);
#endif //PROT_USE_XML

//挑战的任务状态
struct SGroupTask
{
	UINT32 dwTaskId; //任务的ID
	EGroupTaskState eGroupTaskState; //当前刷的任务信息

	SGroupTask();
	SGroupTask(UINT32 dwTaskId_, EGroupTaskState eGroupTaskState_);
};

typedef std::vector<SGroupTask> TVecGroupTask;

//师门任务信息
struct SGroupTaskInfoForClient
{
	EGroupStudyState eStudyState; //清修状态
	UINT32 dwGroupRepute; //声望
	UINT8 dwGroupLevel; //声望等级
	UINT8 byFinishTask; //今日完成的师门任务数
	UINT8 byAcceptTaskTimes; //剩余可接任务数
	UINT8 byBuyTimesToday; //今日购买的任务数
	UINT8 byVIPTaskTimes; //购买的可接任务数
	UINT8 byFlushTask; //今日刷新任务列表次数
	UINT8 byStudyAward; //今日领取的清修次数
	TVecGroupTask vecTask; //推的任务列表

	SGroupTaskInfoForClient();
	SGroupTaskInfoForClient(EGroupStudyState eStudyState_, UINT32 dwGroupRepute_, UINT8 dwGroupLevel_, UINT8 byFinishTask_, UINT8 byAcceptTaskTimes_, 
		UINT8 byBuyTimesToday_, UINT8 byVIPTaskTimes_, UINT8 byFlushTask_, UINT8 byStudyAward_, const TVecGroupTask& vecTask_);
#ifdef __GNUG__
	SGroupTaskInfoForClient(const SGroupTaskInfoForClient& src) = default; //默认拷贝构造函数
	SGroupTaskInfoForClient& operator=(const SGroupTaskInfoForClient& rhs) = default; //默认赋值操作符
#endif
	SGroupTaskInfoForClient(SGroupTaskInfoForClient&& src); //转移构造函数
	SGroupTaskInfoForClient& operator=(SGroupTaskInfoForClient&& rhs); //转移赋值操作符
};

typedef std::vector<SGroupTaskInfoForClient> TVecGroupTaskInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SGroupTask&);
COutArchive& operator<<(COutArchive&, const SGroupTask&);

CInArchive& operator>>(CInArchive&, SGroupTaskInfoForClient&);
COutArchive& operator<<(COutArchive&, const SGroupTaskInfoForClient&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SGroupTask&);
bool ToXML(const SGroupTask&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGroupTask&);
bool VectorToXML(const TVecGroupTask&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGroupTaskInfoForClient&);
bool ToXML(const SGroupTaskInfoForClient&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGroupTaskInfo&);
bool VectorToXML(const TVecGroupTaskInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGroupTaskProt
