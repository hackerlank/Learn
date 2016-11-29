/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    AchievementProt.h
//  Purpose:      成就相关协议
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

namespace NAchievementProt
{

/////////////////////以下为类型定义/////////////////////
//成就完成进度
enum EAchievementRet
{
	eAchievementRet_Sucess = 0, //成功
	eAchievementRet_NotFinish, //未完成
	eAchievementRet_TakePrized, //已领奖
	eAchievementRet_ErrorCFG, //配置错误
	eAchievementRet_PackFull //包满
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EAchievementRet);
bool EnumStrToVal(const char*, EAchievementRet&);
#endif //PROT_USE_XML
const char* GetDescription(EAchievementRet);

//成就完成进度
enum EAchievementProcess
{
	eAchievementProcess_Init = 0, //未完成
	eAchievementProcess_Finish, //已完成
	eAchievementProcess_TakePrize //已领奖
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EAchievementProcess);
bool EnumStrToVal(const char*, EAchievementProcess&);
#endif //PROT_USE_XML
const char* GetDescription(EAchievementProcess);

//成就分享类型
enum EAchievementShareType
{
	eAchievementShareType_Invalid = 0, //无效类型
	eAchievementShareType_Friend, //qq好友分享
	eAchievementShareType_Game //游戏内炫耀
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EAchievementShareType);
bool EnumStrToVal(const char*, EAchievementShareType&);
#endif //PROT_USE_XML
const char* GetDescription(EAchievementShareType);

//EDataType:eTypeAchievementInfo
struct SAchievementInfo
{
	UINT64 qwRoleID; //角色ID
	UINT16 wAchievementID; //成就ID
	UINT32 dwCount; //EAchievementProcess类型成就完成进度
	UINT32 dwProcess; //当前进度(持续型事件记录数据)
	UINT32 dwFinishTime; //完成时间

	SAchievementInfo();
	SAchievementInfo(UINT64 qwRoleID_, UINT16 wAchievementID_, UINT32 dwCount_, UINT32 dwProcess_, UINT32 dwFinishTime_);
};

typedef std::vector<SAchievementInfo> TVecAchievementInfo;

//成就分享列表
struct SAchievementShare
{
	UINT16 wAchievementID; //成就ID
	EAchievementProcess eProcess; //分享状态

	SAchievementShare();
	SAchievementShare(UINT16 wAchievementID_, EAchievementProcess eProcess_);
};

typedef std::vector<SAchievementShare> TVecAchievementShare;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SAchievementInfo&);
COutArchive& operator<<(COutArchive&, const SAchievementInfo&);

CInArchive& operator>>(CInArchive&, SAchievementShare&);
COutArchive& operator<<(COutArchive&, const SAchievementShare&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SAchievementInfo&);
bool ToXML(const SAchievementInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecAchievementInfo&);
bool VectorToXML(const TVecAchievementInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SAchievementShare&);
bool ToXML(const SAchievementShare&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecAchievementShare&);
bool VectorToXML(const TVecAchievementShare&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NAchievementProt
