/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Center2DBComm.h
//  Purpose:      CenterServer到DBServer的通信协议
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
#include "ArenaGS.h"
#include "DemonTowerGS.h"
#include "GlobalChatProt.h"
#include "GodMonsterProt.h"
#include "MailProt.h"
#include "PHPProt.h"
#include "ProtoCommon.h"
#include "RankProt.h"
#include "RoleInfoDefine.h"
#include "ServerCommon.h"
#include "ShipProt.h"
#include "TripodProt.h"
#include "WonderActivityProt.h"

namespace NCenter2DBComm
{

/////////////////////以下为类型定义/////////////////////
//中心服数据类型
enum ECenterData
{
	eCenterDate_BeautyLog = 1, //美女log
	eCenterDate_InviteFriend = 2, //邀请好友数据
	eCenterDate_InviteTask = 3, //邀请好友任务数据
	eCenterDate_DemonTower_MinRonds = 4, //镇妖塔最小回数
	eCenterDate_DemonTower_MinBattlePoint = 5 //镇妖塔最小战斗力
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECenterData);
bool EnumStrToVal(const char*, ECenterData&);
#endif //PROT_USE_XML

//中心服存储数据
struct SCenterData
{
	UINT16 wType; //类型 ECenterData
	UINT64 qwInstID; //keyid1
	UINT64 qwInstID2; //keyid2
	UINT64 qwParam; //64位参数
	std::string strParam; //整形参数
	UINT32 dwParam1; //32位参数1
	UINT32 dwParam2; //32位参数2
	UINT32 dwParam3; //32位参数3
	UINT64 qwParam4; //64位参数4

	SCenterData();
	SCenterData(UINT16 wType_, UINT64 qwInstID_, UINT64 qwInstID2_, UINT64 qwParam_, const std::string& strParam_, 
		UINT32 dwParam1_, UINT32 dwParam2_, UINT32 dwParam3_, UINT64 qwParam4_);
#ifdef __GNUG__
	SCenterData(const SCenterData& src) = default; //默认拷贝构造函数
	SCenterData& operator=(const SCenterData& rhs) = default; //默认赋值操作符
#endif
	SCenterData(SCenterData&& src); //转移构造函数
	SCenterData& operator=(SCenterData&& rhs); //转移赋值操作符
};

typedef std::vector<SCenterData> TVecCenterData;

//系统邮件信息
struct SSystemMailTargetInfo
{
	UINT64 qwMailID; //邮件ID
	UINT64 qwReceiveID; //接受者ID

	SSystemMailTargetInfo();
	SSystemMailTargetInfo(UINT64 qwMailID_, UINT64 qwReceiveID_);
};

typedef std::vector<SSystemMailTargetInfo> TVecSystemMailTargetInfo;

//邮件删除提示结构
struct MailDelData
{
	UINT64 qwMailID; //邮件ID
	UINT8 byGet; //邮件的附件状态

	MailDelData();
	MailDelData(UINT64 qwMailID_, UINT8 byGet_);
};

typedef std::vector<MailDelData> TVecMailDelData;

//系统邮件信息
struct SSystemMailInfo
{
	NMailProt::EMailType eMailType; //邮件类型
	NMailProt::EMailState eMailState; //邮件状态
	UINT32 dwSendTime; //发送时间
	std::string strTitle; //标题
	std::string strSender; //发送者
	std::string strMsg; //邮件内容
	UINT8 byGet; //附件状态
	NMailProt::TVecMailAttachment vecMailAttachment; //附件

	SSystemMailInfo();
#ifdef __GNUG__
	SSystemMailInfo(const SSystemMailInfo& src) = default; //默认拷贝构造函数
	SSystemMailInfo& operator=(const SSystemMailInfo& rhs) = default; //默认赋值操作符
#endif
	SSystemMailInfo(SSystemMailInfo&& src); //转移构造函数
	SSystemMailInfo& operator=(SSystemMailInfo&& rhs); //转移赋值操作符
};

//数据库查询基本条件
struct SBaseCond
{
	UINT8 byLevel; //等级

	SBaseCond();
	SBaseCond(UINT8 byLevel_);
};

typedef std::vector<SBaseCond> TVecBaseCond;

//数据库查询返回
struct SBaseResult
{
	TVecUINT64 vecPlayerID; //玩家ID
	UINT32 dwResult; //查询结果

	SBaseResult();
	SBaseResult(const TVecUINT64& vecPlayerID_, UINT32 dwResult_);
};

typedef std::vector<SBaseResult> TVecBaseResult;

//玩家等级
struct SRoleLevel
{
	UINT32 dwID; //条件ID
	UINT32 dwCount; //数量
	TVecUINT64 vecRole; //玩家ID

	SRoleLevel();
	SRoleLevel(UINT32 dwID_, UINT32 dwCount_, const TVecUINT64& vecRole_);
};

typedef std::vector<SRoleLevel> TVecRoleLevel;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SCenterData&);
COutArchive& operator<<(COutArchive&, const SCenterData&);

CInArchive& operator>>(CInArchive&, SSystemMailTargetInfo&);
COutArchive& operator<<(COutArchive&, const SSystemMailTargetInfo&);

CInArchive& operator>>(CInArchive&, MailDelData&);
COutArchive& operator<<(COutArchive&, const MailDelData&);

CInArchive& operator>>(CInArchive&, SSystemMailInfo&);
COutArchive& operator<<(COutArchive&, const SSystemMailInfo&);

CInArchive& operator>>(CInArchive&, SBaseCond&);
COutArchive& operator<<(COutArchive&, const SBaseCond&);

CInArchive& operator>>(CInArchive&, SBaseResult&);
COutArchive& operator<<(COutArchive&, const SBaseResult&);

CInArchive& operator>>(CInArchive&, SRoleLevel&);
COutArchive& operator<<(COutArchive&, const SRoleLevel&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SCenterData&);
bool ToXML(const SCenterData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCenterData&);
bool VectorToXML(const TVecCenterData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSystemMailTargetInfo&);
bool ToXML(const SSystemMailTargetInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSystemMailTargetInfo&);
bool VectorToXML(const TVecSystemMailTargetInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, MailDelData&);
bool ToXML(const MailDelData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMailDelData&);
bool VectorToXML(const TVecMailDelData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSystemMailInfo&);
bool ToXML(const SSystemMailInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBaseCond&);
bool ToXML(const SBaseCond&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBaseCond&);
bool VectorToXML(const TVecBaseCond&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBaseResult&);
bool ToXML(const SBaseResult&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBaseResult&);
bool VectorToXML(const TVecBaseResult&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoleLevel&);
bool ToXML(const SRoleLevel&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoleLevel&);
bool VectorToXML(const TVecRoleLevel&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NCenter2DBComm
