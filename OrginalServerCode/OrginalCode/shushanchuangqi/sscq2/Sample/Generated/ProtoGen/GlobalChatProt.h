/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GlobalChatProt.h
//  Purpose:      全局聊天协议
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

namespace NGlobalChatProt
{

/////////////////////以下为类型定义/////////////////////
//获取展示道具结果
enum EChatShowResult
{
	eChatShowSucceed, //成功
	eChatShowNotExist, //展示道具不存在
	eChatShowErrOther //其他错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EChatShowResult);
bool EnumStrToVal(const char*, EChatShowResult&);
#endif //PROT_USE_XML

//通道类型
enum EChannelType
{
	eChannelNone = 0, //None
	eChannelAll = 1, //综合
	eChannelWorld = 2, //世界
	eChannelGuild = 3, //帮派
	eChannelSys = 4, //系统
	eChannelTeam = 5, //组队
	eChannelNoLabelSys //无字系统消息
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EChannelType);
bool EnumStrToVal(const char*, EChannelType&);
#endif //PROT_USE_XML

//消息额外类型
enum EChannelSubType
{
	eSubNone, //无
	eSubBulletin, //公告区域
	eSubBroadcast, //广播区域
	eSubHorn, //喇叭区域
	eSubSuspension, //悬浮区域
	eSubPrompt, //提示区域
	eSubEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EChannelSubType);
bool EnumStrToVal(const char*, EChannelSubType&);
#endif //PROT_USE_XML

//展示类型
enum EChatShowType
{
	eShowItem, //道具
	eShowRole, //角色
	eShowPet, //阵灵
	eShowHorse //坐骑
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EChatShowType);
bool EnumStrToVal(const char*, EChatShowType&);
#endif //PROT_USE_XML

//私聊错误类型
enum EWhisperErrorType
{
	eWhisperTooFastErr, //太快
	eWhisperOfflineErr, //目标不在线
	eWhisperLengthErr //信息长度不对
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EWhisperErrorType);
bool EnumStrToVal(const char*, EWhisperErrorType&);
#endif //PROT_USE_XML

//炫耀类型
enum ESShowInfoType
{
	eFlauntGood, //物品，使用SItem解析
	eFlauntHero, //散仙，使用SFlauntHero解析
	eFlauntPet, //阵灵，使用SFlauntPet解析
	eFlauntHorse, //坐骑，使用SFlauntHorse解析
	eShowAchievement, //成就
	eFlauntFashion //时装，使用SFlauntFashion解析
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESShowInfoType);
bool EnumStrToVal(const char*, ESShowInfoType&);
#endif //PROT_USE_XML

//发送者信息
struct SSenderInfo
{
	UINT8 byVIPType; //VIP特权类型
	UINT64 qwUsrID; //帐号ID
	std::string strName; //发送者名
	std::string strGuildName; //帮派名称
	UINT8 byQuality; //玩家品质（颜色）
	UINT8 byNation; //发送者国家
	NProtoCommon::TVecPlatformParam vecPlatforms; //平台相关参数

	SSenderInfo();
	SSenderInfo(UINT8 byVIPType_, UINT64 qwUsrID_, const std::string& strName_, const std::string& strGuildName_, UINT8 byQuality_, 
		UINT8 byNation_, const NProtoCommon::TVecPlatformParam& vecPlatforms_);
#ifdef __GNUG__
	SSenderInfo(const SSenderInfo& src) = default; //默认拷贝构造函数
	SSenderInfo& operator=(const SSenderInfo& rhs) = default; //默认赋值操作符
#endif
	SSenderInfo(SSenderInfo&& src); //转移构造函数
	SSenderInfo& operator=(SSenderInfo&& rhs); //转移赋值操作符
};

//炫耀信息
struct SShowInfo
{
	UINT64 qwInstID; //唯一ID
	std::string strShowInfo; //展示信息序列化

	SShowInfo();
	SShowInfo(UINT64 qwInstID_, const std::string& strShowInfo_);
#ifdef __GNUG__
	SShowInfo(const SShowInfo& src) = default; //默认拷贝构造函数
	SShowInfo& operator=(const SShowInfo& rhs) = default; //默认赋值操作符
#endif
	SShowInfo(SShowInfo&& src); //转移构造函数
	SShowInfo& operator=(SShowInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SShowInfo> TVecShowInfo;

//私聊对方信息
struct SWhisperInfo
{
	UINT64 qwUserID; //帐号ID
	std::string strName; //名字 XXX: 如果主将改名需要修改此处
	UINT8 byVIPType; //VIP特权类型
	std::string strGuildName; //帮派名称
	NProtoCommon::TVecPlatformParam vecPlatforms; //平台相关参数
	UINT16 wFighterID; //主将ID
	NProtoCommon::ESexType eSex; //性别
	UINT8 byLevel; //等级
	UINT16 wMood; //心情表情
	std::string strSign; //签名
	UINT8 byQuality; //品质

	SWhisperInfo();
#ifdef __GNUG__
	SWhisperInfo(const SWhisperInfo& src) = default; //默认拷贝构造函数
	SWhisperInfo& operator=(const SWhisperInfo& rhs) = default; //默认赋值操作符
#endif
	SWhisperInfo(SWhisperInfo&& src); //转移构造函数
	SWhisperInfo& operator=(SWhisperInfo&& rhs); //转移赋值操作符
};

//炫耀参与战斗的技能信息
struct SFlauntSkill
{
	UINT8 byIdx; //技能槽idx
	UINT32 dwSkillID; //技能ID

	SFlauntSkill();
	SFlauntSkill(UINT8 byIdx_, UINT32 dwSkillID_);
};

typedef std::vector<SFlauntSkill> TVecFlauntSkill;

//炫耀装备信息
struct SFlauntEquip
{
	UINT16 wEquipID; //装备TypeID
	UINT8 byStrengthenLevel; //强化等级
	UINT8 byPos; //装备位置

	SFlauntEquip();
	SFlauntEquip(UINT16 wEquipID_, UINT8 byStrengthenLevel_, UINT8 byPos_);
};

typedef std::vector<SFlauntEquip> TVecFlauntEquip;

//散仙炫耀信息
struct SFlauntHero
{
	std::string strName; //名字
	UINT64 qwInstID; //散仙唯一ID
	UINT16 wFighterID; //散仙ID
	UINT8 byLevel; //等级
	UINT8 byQuilty; //品质 0,1,2,3,4,5,6【黑白绿蓝紫黄橙】
	UINT32 dwPower; //散仙战斗力
	NProtoCommon::TVecFtAttrMod oAttrVec; //最终属性
	UINT8 byDujieLevel; //散仙渡劫等级
	TVecFlauntSkill vActiveSkill; //主动技能
	TVecFlauntSkill vPassiveSkill; //被动技能
	SFlauntSkill sPeerLessSkill; //无双技能
	TVecFlauntEquip vecFlauntEquip; //时装
	UINT8 byLianPi; //炼皮
	UINT8 byTongJin; //通筋
	UINT8 byQiangJi; //强肌
	UINT8 byDuanGu; //锻骨
	UINT8 byHuoLuo; //活络
	UINT8 byXiSui; //洗髓

	SFlauntHero();
#ifdef __GNUG__
	SFlauntHero(const SFlauntHero& src) = default; //默认拷贝构造函数
	SFlauntHero& operator=(const SFlauntHero& rhs) = default; //默认赋值操作符
#endif
	SFlauntHero(SFlauntHero&& src); //转移构造函数
	SFlauntHero& operator=(SFlauntHero&& rhs); //转移赋值操作符
};

//时装炫耀
struct SFlauntFashion
{
	UINT16 wFighterID; //主将ID
	UINT8 byLevel; //时装等级
	UINT8 byType; //类型(0武器,1衣服)
	UINT16 weaponID; //武器ID
	UINT16 armorID; //衣服ID

	SFlauntFashion();
	SFlauntFashion(UINT16 wFighterID_, UINT8 byLevel_, UINT8 byType_, UINT16 weaponID_, UINT16 armorID_);
};

//阵灵炫耀信息
struct SFlauntPet
{
	UINT64 qwInstID; //阵灵唯一ID
	UINT16 wFighterID; //阵灵ID
	UINT8 byLevel; //等级

	SFlauntPet();
	SFlauntPet(UINT64 qwInstID_, UINT16 wFighterID_, UINT8 byLevel_);
};

//坐骑炫耀信息
struct SFlauntHorse
{
	UINT64 qwInstID; //阵灵唯一ID
	UINT16 wFighterID; //坐骑ID
	UINT8 byLevel; //等级

	SFlauntHorse();
	SFlauntHorse(UINT64 qwInstID_, UINT16 wFighterID_, UINT8 byLevel_);
};

//成就炫耀信息
struct SFlauntAchievement
{
	UINT64 qwInstID; //成就唯一ID
	UINT16 wAchievementID; //成就ID

	SFlauntAchievement();
	SFlauntAchievement(UINT64 qwInstID_, UINT16 wAchievementID_);
};

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SSenderInfo&);
COutArchive& operator<<(COutArchive&, const SSenderInfo&);

CInArchive& operator>>(CInArchive&, SShowInfo&);
COutArchive& operator<<(COutArchive&, const SShowInfo&);

CInArchive& operator>>(CInArchive&, SWhisperInfo&);
COutArchive& operator<<(COutArchive&, const SWhisperInfo&);

CInArchive& operator>>(CInArchive&, SFlauntSkill&);
COutArchive& operator<<(COutArchive&, const SFlauntSkill&);

CInArchive& operator>>(CInArchive&, SFlauntEquip&);
COutArchive& operator<<(COutArchive&, const SFlauntEquip&);

CInArchive& operator>>(CInArchive&, SFlauntHero&);
COutArchive& operator<<(COutArchive&, const SFlauntHero&);

CInArchive& operator>>(CInArchive&, SFlauntFashion&);
COutArchive& operator<<(COutArchive&, const SFlauntFashion&);

CInArchive& operator>>(CInArchive&, SFlauntPet&);
COutArchive& operator<<(COutArchive&, const SFlauntPet&);

CInArchive& operator>>(CInArchive&, SFlauntHorse&);
COutArchive& operator<<(COutArchive&, const SFlauntHorse&);

CInArchive& operator>>(CInArchive&, SFlauntAchievement&);
COutArchive& operator<<(COutArchive&, const SFlauntAchievement&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SSenderInfo&);
bool ToXML(const SSenderInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SShowInfo&);
bool ToXML(const SShowInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecShowInfo&);
bool VectorToXML(const TVecShowInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SWhisperInfo&);
bool ToXML(const SWhisperInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFlauntSkill&);
bool ToXML(const SFlauntSkill&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFlauntSkill&);
bool VectorToXML(const TVecFlauntSkill&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFlauntEquip&);
bool ToXML(const SFlauntEquip&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFlauntEquip&);
bool VectorToXML(const TVecFlauntEquip&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFlauntHero&);
bool ToXML(const SFlauntHero&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFlauntFashion&);
bool ToXML(const SFlauntFashion&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFlauntPet&);
bool ToXML(const SFlauntPet&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFlauntHorse&);
bool ToXML(const SFlauntHorse&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFlauntAchievement&);
bool ToXML(const SFlauntAchievement&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGlobalChatProt
