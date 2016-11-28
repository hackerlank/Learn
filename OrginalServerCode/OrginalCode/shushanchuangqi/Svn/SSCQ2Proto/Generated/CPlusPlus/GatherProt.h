/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GatherProt.h
//  Purpose:      采集协议
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
#include "ItemProt.h"

namespace NGatherProt
{

/////////////////////以下为类型定义/////////////////////
//副本结果
enum EGatherResult
{
	eGatherSuccess, //成功
	eGatherIn, //正在采集中
	eGatherOut, //没有采集中
	eGatherItemLimit, //采集所需物品不足
	eGatherBusy, //玩家忙
	eGatherPackEmptyMin, //采集空格子不足
	eGatherVIP, //御剑等级不足
	eGatherLevel, //等级不足
	eGatherNotExist, //采集物不存在
	eGatherTooFar, //采集物太远
	eGatherNumLimit, //采集物数量不足
	eGatherTask, //需要接相关任务才可以采集
	eGatherCancel, //采集中断
	eGatherFinish, //采集完成
	eGatherLuaErr, //Lua脚本拒绝
	eGatherOtherErr //未知错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGatherResult);
bool EnumStrToVal(const char*, EGatherResult&);
#endif //PROT_USE_XML
const char* GetDescription(EGatherResult);

//采集条件
enum EGatherConType
{
	eGCT_None, //无定义
	eGCT_Level, //等级
	eGCT_Item, //道具，包括仙石等
	eGCT_VIP, //VIP宝箱
	eGCT_End //定义完毕
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGatherConType);
bool EnumStrToVal(const char*, EGatherConType&);
#endif //PROT_USE_XML
const char* GetDescription(EGatherConType);


} //namespace NGatherProt
