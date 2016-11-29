/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    InviteGS.h
//  Purpose:      邀请好友相关协议
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

namespace NInviteGS
{

/////////////////////以下为类型定义/////////////////////
//好友相关的结果
enum EInviteResult
{
	eInvite_Success, //成功
	eInvite_Failed, //失败
	eInvite_ErrorUserID, //玩家id错误
	eInvite_ErrorCFGID, //配置id错误
	eInvite_TaskInit, //任务未完成
	eInvite_TaskTakedPrize, //任务奖励已领取
	eInvite_ServerBusy //任务奖励已领取
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EInviteResult);
bool EnumStrToVal(const char*, EInviteResult&);
#endif //PROT_USE_XML

//邀请任务状态
enum EInvitedTask
{
	eInvitedTask_Init, //未完成
	eInvitedTask_Finish, //已完成
	eInvitedTask_TakePrized //已领奖
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EInvitedTask);
bool EnumStrToVal(const char*, EInvitedTask&);
#endif //PROT_USE_XML

//被邀请好友db信息
struct SInvitedFriendDB
{
	UINT64 qwUserID; //帐号ID
	UINT64 qwInviteID; //邀请账号ID
	std::string strName; //名字
	UINT8 byColor; //职业
	UINT8 byJob; //职业
	UINT8 bySex; //性别
	UINT8 byLevel; //等级
	UINT8 byVIPLevel; //VIP等级
	UINT32 dwTotalRecharge; //总充值

	SInvitedFriendDB();
	SInvitedFriendDB(UINT64 qwUserID_, UINT64 qwInviteID_, const std::string& strName_, UINT8 byColor_, UINT8 byJob_, 
		UINT8 bySex_, UINT8 byLevel_, UINT8 byVIPLevel_, UINT32 dwTotalRecharge_);
#ifdef __GNUG__
	SInvitedFriendDB(const SInvitedFriendDB& src) = default; //默认拷贝构造函数
	SInvitedFriendDB& operator=(const SInvitedFriendDB& rhs) = default; //默认赋值操作符
#endif
	SInvitedFriendDB(SInvitedFriendDB&& src); //转移构造函数
	SInvitedFriendDB& operator=(SInvitedFriendDB&& rhs); //转移赋值操作符
};

typedef std::vector<SInvitedFriendDB> TVecInvitedFriendDB;

//被邀请好友信息
struct SInvitedFriend
{
	UINT64 qwUserID; //帐号ID
	std::string strName; //名字
	UINT8 byJob; //职业
	UINT8 bySex; //性别
	UINT8 byLevel; //等级
	UINT8 byVIPLevel; //VIP等级
	UINT32 dwTotalRecharge; //总充值
	NProtoCommon::TVecPlatformParam vecPlatforms; //平台信息

	SInvitedFriend();
	SInvitedFriend(UINT64 qwUserID_, const std::string& strName_, UINT8 byJob_, UINT8 bySex_, UINT8 byLevel_, 
		UINT8 byVIPLevel_, UINT32 dwTotalRecharge_, const NProtoCommon::TVecPlatformParam& vecPlatforms_);
#ifdef __GNUG__
	SInvitedFriend(const SInvitedFriend& src) = default; //默认拷贝构造函数
	SInvitedFriend& operator=(const SInvitedFriend& rhs) = default; //默认赋值操作符
#endif
	SInvitedFriend(SInvitedFriend&& src); //转移构造函数
	SInvitedFriend& operator=(SInvitedFriend&& rhs); //转移赋值操作符
};

typedef std::vector<SInvitedFriend> TVecInvitedFriend;

//邀请任务状态
struct SInvitedTask
{
	UINT32 dwInviteTaskID; //任务id
	UINT16 wTaskType; //任务类型
	EInvitedTask eInvitedTask; //任务状态

	SInvitedTask();
	SInvitedTask(UINT32 dwInviteTaskID_, UINT16 wTaskType_, EInvitedTask eInvitedTask_);
};

typedef std::vector<SInvitedTask> TVecInvitedTask;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SInvitedFriendDB&);
COutArchive& operator<<(COutArchive&, const SInvitedFriendDB&);

CInArchive& operator>>(CInArchive&, SInvitedFriend&);
COutArchive& operator<<(COutArchive&, const SInvitedFriend&);

CInArchive& operator>>(CInArchive&, SInvitedTask&);
COutArchive& operator<<(COutArchive&, const SInvitedTask&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SInvitedFriendDB&);
bool ToXML(const SInvitedFriendDB&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecInvitedFriendDB&);
bool VectorToXML(const TVecInvitedFriendDB&, TiXmlElement&);

bool FromXML(TiXmlElement&, SInvitedFriend&);
bool ToXML(const SInvitedFriend&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecInvitedFriend&);
bool VectorToXML(const TVecInvitedFriend&, TiXmlElement&);

bool FromXML(TiXmlElement&, SInvitedTask&);
bool ToXML(const SInvitedTask&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecInvitedTask&);
bool VectorToXML(const TVecInvitedTask&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NInviteGS
