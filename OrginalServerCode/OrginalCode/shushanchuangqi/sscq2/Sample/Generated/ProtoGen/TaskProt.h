/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    TaskProt.h
//  Purpose:      任务协议
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

namespace NTaskProt
{

/////////////////////以下为类型定义/////////////////////
//任务的结果
enum ETaskResult
{
	eTaskSucceed, //成功
	eTaskNotExist, //任务不存在
	eTaskAlreadyAccept, //任务已经接取
	eTaskErrFinish, //任务不能完成
	eTaskErrGiveUp, //任务不能取消
	eTaskErrAccept, //接取任务失败
	eTaskErrPackFull, //背包已满错误
	eTaskErrRepeat, //不能接取重复任务
	eTaskErrFull, //已接任务数已满
	eTaskErrSex, //性别错误
	eTaskErrPrepTask, //前置任务
	eTaskErrLevel, //等级不符
	eTaskErrNoSelOptAward, //未选取奖励
	eTaskErrMap, //所在地图不符
	eTaskNoDiamond, //钻石不足
	eTaskNoGiftCoin, //礼金不足
	eTaskNoFamily, //无家族
	eTaskNoGuild, //无公会
	eTaskErrCamp, //阵营不对
	eTaskNoRepution, //声望不够
	eTaskNoJob, //职业限制
	eTaskNoRace, //种族限制
	eTaskNoGold, //仙石不足
	eTaskNoSliver, //银币不足
	eTaskGroupFull, //师门任务只能接一个
	eTaskYaMenFull, //衙门任务只能接一个
	eTaskCircleFull, //环任务只能接一个
	eTaskErrOther //其它错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETaskResult);
bool EnumStrToVal(const char*, ETaskResult&);
#endif //PROT_USE_XML

//任务的状态
enum ETaskState
{
	eTaskNone, //无
	eTaskAccept, //任务已接取
	eTaskFail, //任务失败
	eTaskFinish //任务完成
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETaskState);
bool EnumStrToVal(const char*, ETaskState&);
#endif //PROT_USE_XML

//任务NPC的状态
enum ENpcTaskState
{
	eNpcTaskNone, //无
	eNpcTaskAccept, //任务可接取
	eNpcTaskUnfinish, //任务未完成
	eNpcTaskSubmit, //任务可交付
	eNpcTaskFuture //将来可接取
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENpcTaskState);
bool EnumStrToVal(const char*, ENpcTaskState&);
#endif //PROT_USE_XML

//结构体：STaskInfo的继承体系类型
enum EType_STaskInfo
{
	eType_STaskInfo, //类型：STaskInfo
	eType_STaskCollectInfo, //类型：STaskCollectInfo
	eType_STaskGatherInfo, //类型：STaskGatherInfo
	eType_STaskMonsterInfo, //类型：STaskMonsterInfo
	eType_STaskTalkInfo, //类型：STaskTalkInfo
	eType_STaskProbeInfo, //类型：STaskProbeInfo
	eType_STaskBuildInfo, //类型：STaskBuildInfo
	eType_STaskScienceInfo, //类型：STaskScienceInfo
	eType_STaskActionInfo, //类型：STaskActionInfo
	eType_STaskGrowInfo //类型：STaskGrowInfo
};

//任务信息
struct STaskInfo
{
	STaskInfo();
	virtual ~STaskInfo() { }
	DEF_NEW_DELETE(STaskInfo); //使用对象池
	virtual EType_STaskInfo GetClassType() const { return eType_STaskInfo; }
};

typedef std::shared_ptr<STaskInfo> STaskInfoPtr;
typedef std::weak_ptr<STaskInfo> STaskInfoWtr;
typedef std::vector<STaskInfoPtr> TVecTaskInfo;

//父类：STaskInfo的辅助结构体
struct STaskInfo_Wrapper
{
	STaskInfoPtr ptr;
	STaskInfo_Wrapper(const STaskInfoPtr& ptr_ = NULL) : ptr(ptr_) { }
};

//收集道具的信息
struct STaskCollectInfo : public STaskInfo
{
	UINT16 wItemID; //道具的ID
	UINT16 wItemCount; //已搜集道具的数量

	STaskCollectInfo();
	DEF_NEW_DELETE(STaskCollectInfo); //使用对象池
	virtual EType_STaskInfo GetClassType() const { return eType_STaskCollectInfo; }
};

typedef std::shared_ptr<STaskCollectInfo> STaskCollectInfoPtr;
typedef std::weak_ptr<STaskCollectInfo> STaskCollectInfoWtr;

//采集的信息
struct STaskGatherInfo : public STaskInfo
{
	UINT16 wGatherID; //采集的ID
	UINT16 wCount; //已采集的次数

	STaskGatherInfo();
	DEF_NEW_DELETE(STaskGatherInfo); //使用对象池
	virtual EType_STaskInfo GetClassType() const { return eType_STaskGatherInfo; }
};

typedef std::shared_ptr<STaskGatherInfo> STaskGatherInfoPtr;
typedef std::weak_ptr<STaskGatherInfo> STaskGatherInfoWtr;

//杀死怪物的信息
struct STaskMonsterInfo : public STaskInfo
{
	UINT16 wMonsterID; //怪物的ID
	UINT16 wMonsterCount; //已杀怪物的数量

	STaskMonsterInfo();
	DEF_NEW_DELETE(STaskMonsterInfo); //使用对象池
	virtual EType_STaskInfo GetClassType() const { return eType_STaskMonsterInfo; }
};

typedef std::shared_ptr<STaskMonsterInfo> STaskMonsterInfoPtr;
typedef std::weak_ptr<STaskMonsterInfo> STaskMonsterInfoWtr;

//NPC的对话信息
struct STaskTalkInfo : public STaskInfo
{
	UINT16 wNpcID; //NPC的ID
	UINT16 wTalkCount; //0:未完成1:已完成

	STaskTalkInfo();
	DEF_NEW_DELETE(STaskTalkInfo); //使用对象池
	virtual EType_STaskInfo GetClassType() const { return eType_STaskTalkInfo; }
};

typedef std::shared_ptr<STaskTalkInfo> STaskTalkInfoPtr;
typedef std::weak_ptr<STaskTalkInfo> STaskTalkInfoWtr;

//探索区域信息
struct STaskProbeInfo : public STaskInfo
{
	UINT8 byIndex; //探索区域索引
	bool bProbed; //是否已探索

	STaskProbeInfo();
	DEF_NEW_DELETE(STaskProbeInfo); //使用对象池
	virtual EType_STaskInfo GetClassType() const { return eType_STaskProbeInfo; }
};

typedef std::shared_ptr<STaskProbeInfo> STaskProbeInfoPtr;
typedef std::weak_ptr<STaskProbeInfo> STaskProbeInfoWtr;

//建筑的信息
struct STaskBuildInfo : public STaskInfo
{
	UINT16 wBuildID; //建筑ID
	UINT16 wLevel; //等级

	STaskBuildInfo();
	DEF_NEW_DELETE(STaskBuildInfo); //使用对象池
	virtual EType_STaskInfo GetClassType() const { return eType_STaskBuildInfo; }
};

typedef std::shared_ptr<STaskBuildInfo> STaskBuildInfoPtr;
typedef std::weak_ptr<STaskBuildInfo> STaskBuildInfoWtr;

//科技的信息
struct STaskScienceInfo : public STaskInfo
{
	UINT16 wScienceID; //科技ID
	UINT16 wLevel; //等级

	STaskScienceInfo();
	DEF_NEW_DELETE(STaskScienceInfo); //使用对象池
	virtual EType_STaskInfo GetClassType() const { return eType_STaskScienceInfo; }
};

typedef std::shared_ptr<STaskScienceInfo> STaskScienceInfoPtr;
typedef std::weak_ptr<STaskScienceInfo> STaskScienceInfoWtr;

//行为的信息
struct STaskActionInfo : public STaskInfo
{
	UINT16 wAction; //行为类型
	UINT16 wCount; //次数

	STaskActionInfo();
	DEF_NEW_DELETE(STaskActionInfo); //使用对象池
	virtual EType_STaskInfo GetClassType() const { return eType_STaskActionInfo; }
};

typedef std::shared_ptr<STaskActionInfo> STaskActionInfoPtr;
typedef std::weak_ptr<STaskActionInfo> STaskActionInfoWtr;

//成长的信息
struct STaskGrowInfo : public STaskInfo
{
	UINT16 wType; //成长类型
	UINT16 wLevel; //等级

	STaskGrowInfo();
	DEF_NEW_DELETE(STaskGrowInfo); //使用对象池
	virtual EType_STaskInfo GetClassType() const { return eType_STaskGrowInfo; }
};

typedef std::shared_ptr<STaskGrowInfo> STaskGrowInfoPtr;
typedef std::weak_ptr<STaskGrowInfo> STaskGrowInfoWtr;

//任务的属性
struct STask
{
	UINT16 wTaskID; //任务的ID
	ETaskState eTaskState; //任务的状态
	UINT32 dwAcceptTime; //接取时间
	UINT8 byRepeat; //同时接取数
	TVecTaskInfo vecTaskInfo; //任务信息列表

	STask();
#ifdef __GNUG__
	STask(const STask& src) = default; //默认拷贝构造函数
	STask& operator=(const STask& rhs) = default; //默认赋值操作符
#endif
	STask(STask&& src); //转移构造函数
	STask& operator=(STask&& rhs); //转移赋值操作符
};

typedef std::vector<STask> TVecTask;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, STaskInfo&);
COutArchive& operator<<(COutArchive&, const STaskInfo&);
CInArchive& operator>>(CInArchive&, STaskInfo_Wrapper&);
COutArchive& operator<<(COutArchive&, const STaskInfo_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecTaskInfo&);
COutArchive& operator<<(COutArchive&, const TVecTaskInfo&);

CInArchive& operator>>(CInArchive&, STaskCollectInfo&);
COutArchive& operator<<(COutArchive&, const STaskCollectInfo&);

CInArchive& operator>>(CInArchive&, STaskGatherInfo&);
COutArchive& operator<<(COutArchive&, const STaskGatherInfo&);

CInArchive& operator>>(CInArchive&, STaskMonsterInfo&);
COutArchive& operator<<(COutArchive&, const STaskMonsterInfo&);

CInArchive& operator>>(CInArchive&, STaskTalkInfo&);
COutArchive& operator<<(COutArchive&, const STaskTalkInfo&);

CInArchive& operator>>(CInArchive&, STaskProbeInfo&);
COutArchive& operator<<(COutArchive&, const STaskProbeInfo&);

CInArchive& operator>>(CInArchive&, STaskBuildInfo&);
COutArchive& operator<<(COutArchive&, const STaskBuildInfo&);

CInArchive& operator>>(CInArchive&, STaskScienceInfo&);
COutArchive& operator<<(COutArchive&, const STaskScienceInfo&);

CInArchive& operator>>(CInArchive&, STaskActionInfo&);
COutArchive& operator<<(COutArchive&, const STaskActionInfo&);

CInArchive& operator>>(CInArchive&, STaskGrowInfo&);
COutArchive& operator<<(COutArchive&, const STaskGrowInfo&);

CInArchive& operator>>(CInArchive&, STask&);
COutArchive& operator<<(COutArchive&, const STask&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, STaskInfo&);
bool ToXML(const STaskInfo&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, STaskInfoPtr&);
bool SuperToXML(const STaskInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTaskInfo&);
bool VectorToXML(const TVecTaskInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STaskCollectInfo&);
bool ToXML(const STaskCollectInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STaskGatherInfo&);
bool ToXML(const STaskGatherInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STaskMonsterInfo&);
bool ToXML(const STaskMonsterInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STaskTalkInfo&);
bool ToXML(const STaskTalkInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STaskProbeInfo&);
bool ToXML(const STaskProbeInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STaskBuildInfo&);
bool ToXML(const STaskBuildInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STaskScienceInfo&);
bool ToXML(const STaskScienceInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STaskActionInfo&);
bool ToXML(const STaskActionInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STaskGrowInfo&);
bool ToXML(const STaskGrowInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STask&);
bool ToXML(const STask&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTask&);
bool VectorToXML(const TVecTask&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NTaskProt
