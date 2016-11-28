/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    FriendProt.h
//  Purpose:      好友相关协议
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

namespace NFriendProt
{

/////////////////////以下为类型定义/////////////////////
//好友相关的结果
enum EFriendResult
{
	eFriendSuccess, //成功
	eFriendFailed, //失败
	eFriendDuplicateErr, //已经存在
	eFriendOtherDuplicateErr, //已存在于目标的好友列表
	eFriendMaxNumErr, //好友达到上限
	eFriendOtherMaxNumErr, //对方好友达到上限
	eFriendOfflineErr, //对方不在线
	eFriendRefuseErr, //对方拒绝
	eFriendNotExistErr, //目标不存在
	eFriendGroupIDErr, //分组ID错误
	eFriendOnBlackList, //对方已在你的黑名单中
	eFriendOnTarBlackList, //对方已把你拉入黑名单
	eFriendSign, //修改签名成功
	eFriendSignLenErr, //签名过长
	eFriendMood, //修改表情成功
	eFriendOtherErr //其他错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EFriendResult);
bool EnumStrToVal(const char*, EFriendResult&);
#endif //PROT_USE_XML

//好友组别
enum EFriendGroupType
{
	eGroupNone, //无
	eCloseFriend, //亲密好友
	eCommonFriend, //普通好友
	eBlackFriend, //黑名单
	eGroupEnd //结尾
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EFriendGroupType);
bool EnumStrToVal(const char*, EFriendGroupType&);
#endif //PROT_USE_XML
const char* GetDescription(EFriendGroupType);

//好友条目
struct SFriendDBInfo
{
	UINT8 byGroup; //分组ID
	UINT64 qwUserID; //帐号ID
	std::string strName; //名字 XXX: 如果主将改名需要修改此处
	UINT16 wFighterID; //主将ID
	UINT8 byLevel; //等级
	UINT16 wMood; //心情表情
	UINT8 byVIPLevel; //VIP等级
	std::string strSign; //签名
	UINT8 byColor; //好友颜色

	SFriendDBInfo();
	SFriendDBInfo(UINT8 byGroup_, UINT64 qwUserID_, const std::string& strName_, UINT16 wFighterID_, UINT8 byLevel_, 
		UINT16 wMood_, UINT8 byVIPLevel_, const std::string& strSign_, UINT8 byColor_);
#ifdef __GNUG__
	SFriendDBInfo(const SFriendDBInfo& src) = default; //默认拷贝构造函数
	SFriendDBInfo& operator=(const SFriendDBInfo& rhs) = default; //默认赋值操作符
#endif
	SFriendDBInfo(SFriendDBInfo&& src); //转移构造函数
	SFriendDBInfo& operator=(SFriendDBInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SFriendDBInfo> TVecFriendDBInfo;

//好友条目
struct SFriendEntry
{
	EFriendGroupType eGroupType; //分组ID
	UINT64 qwUserID; //帐号ID
	std::string strName; //名字 XXX: 如果主将改名需要修改此处
	UINT16 wFighterID; //主将ID
	NProtoCommon::ESexType eSex; //性别
	UINT8 byLevel; //等级
	UINT8 byVIPLevel; //VIP等级
	UINT8 byColor; //好友颜色
	UINT16 wMood; //心情表情
	std::string strSign; //签名
	UINT32 dwTotalRecharge; //总充值
	bool bOnlineStatus; //在线状态
	NProtoCommon::TVecPlatformParam vecPlatforms; //平台信息

	SFriendEntry();
#ifdef __GNUG__
	SFriendEntry(const SFriendEntry& src) = default; //默认拷贝构造函数
	SFriendEntry& operator=(const SFriendEntry& rhs) = default; //默认赋值操作符
#endif
	SFriendEntry(SFriendEntry&& src); //转移构造函数
	SFriendEntry& operator=(SFriendEntry&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SFriendEntry); //使用对象池
};

typedef std::shared_ptr<SFriendEntry> SFriendEntryPtr;
typedef std::weak_ptr<SFriendEntry> SFriendEntryWtr;
typedef std::vector<SFriendEntryPtr> TVecFriendEntry;

//好友
struct SFriend
{
	UINT16 wMood; //我的心情表情
	std::string strSign; //我的签名
	TVecFriendEntry vecFriendEntry; //好友列表

	SFriend();
	SFriend(UINT16 wMood_, const std::string& strSign_, const TVecFriendEntry& vecFriendEntry_);
#ifdef __GNUG__
	SFriend(const SFriend& src) = default; //默认拷贝构造函数
	SFriend& operator=(const SFriend& rhs) = default; //默认赋值操作符
#endif
	SFriend(SFriend&& src); //转移构造函数
	SFriend& operator=(SFriend&& rhs); //转移赋值操作符
};

//推荐好友
struct SreferFriend
{
	UINT64 qwUserID; //帐号ID
	UINT8 byLevel; //等级
	UINT16 wHeroID; //主将ID
	std::string strName; //用户名称

	SreferFriend();
	SreferFriend(UINT64 qwUserID_, UINT8 byLevel_, UINT16 wHeroID_, const std::string& strName_);
#ifdef __GNUG__
	SreferFriend(const SreferFriend& src) = default; //默认拷贝构造函数
	SreferFriend& operator=(const SreferFriend& rhs) = default; //默认赋值操作符
#endif
	SreferFriend(SreferFriend&& src); //转移构造函数
	SreferFriend& operator=(SreferFriend&& rhs); //转移赋值操作符
};

typedef std::vector<SreferFriend> TVecReferFriend;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SFriendDBInfo&);
COutArchive& operator<<(COutArchive&, const SFriendDBInfo&);

CInArchive& operator>>(CInArchive&, SFriendEntry&);
COutArchive& operator<<(COutArchive&, const SFriendEntry&);
CInArchive& operator>>(CInArchive&, TVecFriendEntry&);
COutArchive& operator<<(COutArchive&, const TVecFriendEntry&);

CInArchive& operator>>(CInArchive&, SFriend&);
COutArchive& operator<<(COutArchive&, const SFriend&);

CInArchive& operator>>(CInArchive&, SreferFriend&);
COutArchive& operator<<(COutArchive&, const SreferFriend&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SFriendDBInfo&);
bool ToXML(const SFriendDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFriendDBInfo&);
bool VectorToXML(const TVecFriendDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFriendEntry&);
bool ToXML(const SFriendEntry&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFriendEntry&);
bool VectorToXML(const TVecFriendEntry&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFriend&);
bool ToXML(const SFriend&, TiXmlElement&);

bool FromXML(TiXmlElement&, SreferFriend&);
bool ToXML(const SreferFriend&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecReferFriend&);
bool VectorToXML(const TVecReferFriend&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NFriendProt
