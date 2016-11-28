/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Game2CenterComm.h
//  Purpose:      GameServer到CenterServer的通信协议
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
#include "BattleGS.h"
#include "BeautyLogGS.h"
#include "EventCenter.h"
#include "FriendProt.h"
#include "GuildProt.h"
#include "ItemProt.h"
#include "LogDataDefine.h"
#include "MailProt.h"
#include "MallProt.h"
#include "PHPProt.h"
#include "ProtoCommon.h"
#include "RoleInfoDefine.h"
#include "ShipProt.h"
#include "TripodProt.h"

namespace NGame2CenterComm
{

/////////////////////以下为类型定义/////////////////////
//数据同步键
enum ESyncKey
{
	eSyncNone, //无
	eSyncGameSvrC2S, //GameServer之间的C2S通信协议
	eSyncGameSvrS2C //GameServer之间的S2C通信协议
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESyncKey);
bool EnumStrToVal(const char*, ESyncKey&);
#endif //PROT_USE_XML

//角色同步属性字段
enum EUserSyncPropField
{
	eSyncPropLevel, //等级
	eSyncPropNation, //阵营
	eSyncPropYellowDiamond, //QQ黄钻
	eSyncPropGold, //仙石
	eSyncPropSilver, //银币
	eSyncPropCoupon, //礼券
	eSyncPropbyTitle, //称号
	eSyncPropbyWallow, //防沉迷
	eSyncPropVIPLevel, //vip等级
	eSyncPropQuality, //主将品质
	eSyncPropPlayerFighterID, //主将ID
	eSyncPropTotalRecharge //玩家每次仙石充值数
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EUserSyncPropField);
bool EnumStrToVal(const char*, EUserSyncPropField&);
#endif //PROT_USE_XML

//操作原因
enum EOpSource
{
	eOpAreaAward, //斗剑奖励
	eOpAreaFlush, //斗剑刷将
	eOpClearAreaCd, //清除斗剑CD
	eOpArenaWirship, //斗剑膜拜
	eOpGuildDonate, //帮派捐献
	eOpGuildWorship, //帮派供奉
	eOpBuyAreaTimes, //购买挑战次数
	eOpLadderAward, //天梯奖励
	eOpAreaAwardDays, //斗剑挑战奖励
	eOpClearLadderCd, //天梯cd清除
	eOpAdoreAward, //崇拜奖励
	eOpTripodAward //九疑鼎扇火、协助奖励
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EOpSource);
bool EnumStrToVal(const char*, EOpSource&);
#endif //PROT_USE_XML

//更新/查询用户数据
enum EUpdateError
{
	eUpdateErrorNoUser, //无用户
	eUpdateErrorItemCount, //物品不足
	eUpdateErrorMoneyCount, //钱币不足
	eUpdateErrorUnKown //未知错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EUpdateError);
bool EnumStrToVal(const char*, EUpdateError&);
#endif //PROT_USE_XML

//玩家整形属性字段
enum EPlayerUINTProp
{
	ePropTopDemonFloorID, //镇妖塔最高层
	ePropPrizeDemonFloorID //镇妖塔奖励层数
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EPlayerUINTProp);
bool EnumStrToVal(const char*, EPlayerUINTProp&);
#endif //PROT_USE_XML

//全服活动类型信息
enum EWonderActType
{
	eActTrump = 1, //法宝
	eActLevel, //等级
	eActFighter, //散仙
	eActFormation, //阵灵
	eActDungon, //副本
	eActBeauty, //美女
	eActHorse, //坐骑
	eActEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EWonderActType);
bool EnumStrToVal(const char*, EWonderActType&);
#endif //PROT_USE_XML

//活动消息同步
enum ActiveParam
{
	eShip //运船金船
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ActiveParam);
bool EnumStrToVal(const char*, ActiveParam&);
#endif //PROT_USE_XML

//物品信息
struct SUserItem
{
	UINT32 dwTypeID; //物品ID/钱币类型
	UINT32 dwCount; //数量

	SUserItem();
	SUserItem(UINT32 dwTypeID_, UINT32 dwCount_);
};

typedef std::vector<SUserItem> TVecUserItem;

//角色进入游戏信息
struct SUserEnterInfo
{
	UINT16 wHeroID; //主将ID
	NProtoCommon::ESexType eSex; //性别
	NProtoCommon::ECareerType eCareer; //职业
	std::string strName; //玩家名字
	UINT8 byLevel; //玩家等级
	UINT8 byNation; //国家
	UINT8 byGMLvl; //GM权限
	UINT32 dwTotalRecharge; //充值金额
	UINT32 dwCreateTime; //创角时间
	UINT32 dwLoginTime; //上次登陆时间
	UINT32 dwOfflineTime; //上次下线时间
	UINT32 dwLockExpireTime; //被封禁结束时间
	UINT32 dwForbExpireTime; //被禁言结束时间
	UINT32 dwGold; //仙石
	UINT32 dwSilver; //银币
	UINT32 dwCoupon; //礼券
	UINT32 dwSoul; //魂魄
	UINT32 dwPrestige; //声望
	UINT32 dwHonor; //荣誉
	UINT32 dwPExp; //修为
	UINT32 dwSigil; //符印
	UINT32 dwCentsY; //仙元
	UINT32 dwAction; //体力
	UINT32 dwSop; //阅历
	UINT32 dwBTPoint; //战斗力
	TVecUINT16 vecOwnTitle; //拥有称号
	TVecUINT16 vecEquipTitle; //装备称号
	UINT8 byDomain; //渠道
	UINT8 byDomainLvl; //渠道等级
	UINT8 byDisplayLvl; //显示等级
	UINT8 byDomainYear; //年费
	std::string szOpenId; //szOpenId
	std::string szOpenKey; //szOpenKey
	UINT64 qwInvitedID; //邀请
	UINT8 byWallow; //防沉迷
	UINT8 byVIPLvl; //VIP等级
	UINT8 byYDLvl; //黄钻等级
	std::string strSign; //签名
	UINT16 wMood; //心情表情
	UINT32 dwFighterPower; //战斗力
	UINT8 byQuality; //主将品质
	UINT16 wPlayerFighterID; //主将ID
	NFriendProt::TVecFriendDBInfo vecFriendsInfo; //关系信息
	NRoleInfoDefine::TVecVarsDBInfo vecGameVars; //传到center的Var数据
	NRoleInfoDefine::TVecRoleArenaInfo vecArenaInfo; //玩家斗剑信息
	NTripodProt::TVecFireInfo vecFireInfo; //玩家九疑鼎的火种信息
	std::string szIconAppear; //开启的功能
	NProtoCommon::TVecPlatformParam vecPlatform; //平台参数列表
	NShipProt::TVecShipReport vecShipReport; //金船战报
	NShipProt::PlayerSelfShipData sShipData; //自己金船相关信息

	SUserEnterInfo();
};

//灵山商店数据
struct SLingShanShopData
{
	UINT64 qwGuildID; //帮派ID
	TVecUINT8 vecLingShanType; //灵山类型

	SLingShanShopData();
	SLingShanShopData(UINT64 qwGuildID_, const TVecUINT8& vecLingShanType_);
};

typedef std::vector<SLingShanShopData> TVecLingShanShopData;

//活动状态数据
struct SActivityState
{
	UINT32 dwActID; //活动ID
	bool bOpen; //状态

	SActivityState();
	SActivityState(UINT32 dwActID_, bool bOpen_);
};

typedef std::vector<SActivityState> TVecActivityState;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SUserItem&);
COutArchive& operator<<(COutArchive&, const SUserItem&);

CInArchive& operator>>(CInArchive&, SUserEnterInfo&);
COutArchive& operator<<(COutArchive&, const SUserEnterInfo&);

CInArchive& operator>>(CInArchive&, SLingShanShopData&);
COutArchive& operator<<(COutArchive&, const SLingShanShopData&);

CInArchive& operator>>(CInArchive&, SActivityState&);
COutArchive& operator<<(COutArchive&, const SActivityState&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SUserItem&);
bool ToXML(const SUserItem&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecUserItem&);
bool VectorToXML(const TVecUserItem&, TiXmlElement&);

bool FromXML(TiXmlElement&, SUserEnterInfo&);
bool ToXML(const SUserEnterInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SLingShanShopData&);
bool ToXML(const SLingShanShopData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecLingShanShopData&);
bool VectorToXML(const TVecLingShanShopData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SActivityState&);
bool ToXML(const SActivityState&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecActivityState&);
bool VectorToXML(const TVecActivityState&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGame2CenterComm
