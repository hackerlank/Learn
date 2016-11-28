/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    NpcProt.h
//  Purpose:      NPC相关协议
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
#include "TaskProt.h"

namespace NNpcProt
{

/////////////////////以下为类型定义/////////////////////
//NPC对话结果
enum ETalkResult
{
	eTalkSucceed, //打开对话成功
	eTalkNotExist, //NPC不存在
	eTalkTooFar, //玩家距离NPC太远
	eTalkScriptFail, //NPC对话脚本执行失败
	eTalkOther //其它错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETalkResult);
bool EnumStrToVal(const char*, ETalkResult&);
#endif //PROT_USE_XML

//NPC的任务状态
struct SNpcTaskState
{
	UINT16 wNpcID; //NPC的ID
	NTaskProt::ENpcTaskState eNpcTaskState; //任务状态

	SNpcTaskState();
	SNpcTaskState(UINT16 wNpcID_, NTaskProt::ENpcTaskState eNpcTaskState_);
};

typedef std::vector<SNpcTaskState> TVecNpcTask;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SNpcTaskState&);
COutArchive& operator<<(COutArchive&, const SNpcTaskState&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SNpcTaskState&);
bool ToXML(const SNpcTaskState&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecNpcTask&);
bool VectorToXML(const TVecNpcTask&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NNpcProt
