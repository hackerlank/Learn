/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    YaMenTaskProt.h
//  Purpose:      衙门任务协议
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

namespace NYaMenTaskProt
{

/////////////////////以下为类型定义/////////////////////
//任务的结果
enum EYaMenTaskResult
{
	eYaMenTaskSucceed, //成功
	eYaMenTaskLowMoney, //钱不足
	eBuyTimesUpLimit, //购买次数已达上限
	eYaMenSaveTimesUpLimit, //总次数已达上限
	eYaMenAwardPackFull, //包裹满
	eYaMenTaskErrOther //其它错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EYaMenTaskResult);
bool EnumStrToVal(const char*, EYaMenTaskResult&);
#endif //PROT_USE_XML

//清修的状态
enum EYaMenStudyState
{
	eCanStudy, //可清修
	eStudied, //已清修
	eCanChallenge, //可挑战
	eChallenging //正挑战
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EYaMenStudyState);
bool EnumStrToVal(const char*, EYaMenStudyState&);
#endif //PROT_USE_XML

//推任务的状态
enum EYaMenTaskState
{
	eNone, //未接
	eAccept, //已接
	eFinish, //已完成
	eFal //已失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EYaMenTaskState);
bool EnumStrToVal(const char*, EYaMenTaskState&);
#endif //PROT_USE_XML

//挑战的任务状态
struct SYaMenTask
{
	UINT32 dwTaskId; //任务的ID
	EYaMenTaskState eYaMenTaskState; //当前刷的任务信息

	SYaMenTask();
	SYaMenTask(UINT32 dwTaskId_, EYaMenTaskState eYaMenTaskState_);
};

typedef std::vector<SYaMenTask> TVecYaMenTask;

//衙门任务信息
struct SYaMenTaskInfoForClient
{
	EYaMenStudyState eStudyState; //清修状态
	UINT32 dwYaMenRepute; //声望
	UINT8 dwYaMenLevel; //声望等级
	UINT8 byFinishTask; //今日完成的衙门任务数
	UINT8 byAcceptTaskTimes; //剩余可接任务数
	UINT8 byBuyTimesToday; //今日购买的任务数
	UINT8 byVIPTaskTimes; //购买的可接任务数
	UINT8 byFlushTask; //今日刷新任务列表次数
	UINT8 byStudyAward; //今日领取的清修次数
	TVecYaMenTask vecTask; //推的任务列表

	SYaMenTaskInfoForClient();
	SYaMenTaskInfoForClient(EYaMenStudyState eStudyState_, UINT32 dwYaMenRepute_, UINT8 dwYaMenLevel_, UINT8 byFinishTask_, UINT8 byAcceptTaskTimes_, 
		UINT8 byBuyTimesToday_, UINT8 byVIPTaskTimes_, UINT8 byFlushTask_, UINT8 byStudyAward_, const TVecYaMenTask& vecTask_);
#ifdef __GNUG__
	SYaMenTaskInfoForClient(const SYaMenTaskInfoForClient& src) = default; //默认拷贝构造函数
	SYaMenTaskInfoForClient& operator=(const SYaMenTaskInfoForClient& rhs) = default; //默认赋值操作符
#endif
	SYaMenTaskInfoForClient(SYaMenTaskInfoForClient&& src); //转移构造函数
	SYaMenTaskInfoForClient& operator=(SYaMenTaskInfoForClient&& rhs); //转移赋值操作符
};

typedef std::vector<SYaMenTaskInfoForClient> TVecYaMenTaskInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SYaMenTask&);
COutArchive& operator<<(COutArchive&, const SYaMenTask&);

CInArchive& operator>>(CInArchive&, SYaMenTaskInfoForClient&);
COutArchive& operator<<(COutArchive&, const SYaMenTaskInfoForClient&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SYaMenTask&);
bool ToXML(const SYaMenTask&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecYaMenTask&);
bool VectorToXML(const TVecYaMenTask&, TiXmlElement&);

bool FromXML(TiXmlElement&, SYaMenTaskInfoForClient&);
bool ToXML(const SYaMenTaskInfoForClient&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecYaMenTaskInfo&);
bool VectorToXML(const TVecYaMenTaskInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NYaMenTaskProt
