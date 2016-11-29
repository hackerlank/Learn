/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    FighterProt.h
//  Purpose:      道具相关协议
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
#include "ItemProt.h"
#include "PropInfo.h"
#include "ProtoCommon.h"

namespace NFighterProt
{

/////////////////////以下为类型定义/////////////////////
//将类型
enum EFighterType
{
	eFighter, //将
	eFighterPlayer, //主将
	eFighterHero, //散仙
	eFighterMonster, //怪
	eFighterMax //将类型结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EFighterType);
bool EnumStrToVal(const char*, EFighterType&);
#endif //PROT_USE_XML

//技能操作结果
enum ESkillResult
{
	eSkillSucc, //成功
	eSkillFailed, //失败
	eSkillNotExist, //没有此技能
	eSkillLevelMax, //已达最高等级
	eSkillLevelErr, //玩家等级不足
	eSkillNotUp, //未装备此技能
	eSkillPExpErr, //修为不足
	eSkillSopErr, //阅历不足
	eSkillSigilErr, //符印不足
	eSkillCentsYErr, //仙元不足
	eSkillPotenErr, //潜力不足
	eRuneNotExist, //符文不存在
	eRuneLevelMax, //符文已达最高等级
	eRuneLevelErr, //玩家等级不足
	eAdvNotExist, //进阶不存在
	eAdvLevelGTSkillLevelErr, //进阶等级大于技能等级
	eItemNotEnough //物品不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESkillResult);
bool EnumStrToVal(const char*, ESkillResult&);
#endif //PROT_USE_XML

//求签类型
enum EDrawType
{
	eDrawTypeNone = 0, //无效类型
	eDrawTypeNormal, //普通求签(银币)
	eDrawTypeAdvance, //高级求签(仙石)
	eDrawTypeMax //最大类型
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDrawType);
bool EnumStrToVal(const char*, EDrawType&);
#endif //PROT_USE_XML

//求签类型
enum EDrawRewardType
{
	eDrawRewardTypeNone = 0, //无效类型
	eDrawRewardTypeBlue, //蓝色仙缘
	eDrawRewardTypePurple, //紫色仙缘
	eDrawRewardTypeOrange, //橙色仙缘
	eDrawRewardTypeMax //最大类型
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDrawRewardType);
bool EnumStrToVal(const char*, EDrawRewardType&);
#endif //PROT_USE_XML

//求签结果
enum EDrawResult
{
	eDrawResultSuccess = 0, //求签成功
	eDrawResultFailed, //求签失败
	eDrawResultLackOfCount, //次数不足
	eDrawResultLackOfMoney, //金钱不足
	eDrawResultMax //求签结果最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDrawResult);
bool EnumStrToVal(const char*, EDrawResult&);
#endif //PROT_USE_XML

//招募返回
enum ERecruitResult
{
	eRecruitSucc, //成功
	eRecruitFailed, //失败
	eRecruitAlready, //已招募
	eRecruitLackOfMoney, //货币不足
	eRecruitLevelLimited //等级不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ERecruitResult);
bool EnumStrToVal(const char*, ERecruitResult&);
#endif //PROT_USE_XML

//淬体
enum ECuiTiType
{
	eCuiTiLianPi, //炼皮-武器
	eCuiTiTongJin, //通筋-头盔
	eCuiTiQiangJi, //强肌-戒指
	eCuiTiDuanGu, //锻骨-衣服
	eCuiTiHuoLuo, //活络-鞋子
	eCuiTiXiSui, //洗髓-项链
	eCuiTiMax //淬体上限
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECuiTiType);
bool EnumStrToVal(const char*, ECuiTiType&);
#endif //PROT_USE_XML

//淬体
enum ECuiTiResult
{
	eCuiTiResultSucc, //成功
	eCuiTiResultFailed, //失败
	eCuiTiResultSilverErr, //银币不足
	eCuiTiResultLvlMaxErr, //已达最高等级
	eCuiTiResultPlayerLvlErr, //已达将最高等级
	eCuiTiResultUnlock //未解锁
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECuiTiResult);
bool EnumStrToVal(const char*, ECuiTiResult&);
#endif //PROT_USE_XML

//转移
enum EShiftResult
{
	eShiftSucc, //成功
	eShiftFailed, //失败
	eShiftGoldErr //仙石不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EShiftResult);
bool EnumStrToVal(const char*, EShiftResult&);
#endif //PROT_USE_XML

//散仙等级同步
enum ESyncLevelResult
{
	eSyncLevelSucc, //成功
	eSyncLevelFailed, //失败
	eSyncLevelAlready, //已是最高等级
	eSyncLevelMoney, //同步等级所需银币不足
	eSyncLevelMoneyMore //同步等级成功但所需银币不足无法继续升级
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESyncLevelResult);
bool EnumStrToVal(const char*, ESyncLevelResult&);
#endif //PROT_USE_XML

//散仙渡劫
enum EDujieResult
{
	eDujieSucc, //成功
	eDujieFailed, //失败
	eDujieItemErr, //渡劫符不足
	eDujieLevelMaxErr //渡劫等级已是最高级
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDujieResult);
bool EnumStrToVal(const char*, EDujieResult&);
#endif //PROT_USE_XML

//心法返回
enum EXinFaResult
{
	eXinFaSucc, //成功
	eXinFaFailed //失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EXinFaResult);
bool EnumStrToVal(const char*, EXinFaResult&);
#endif //PROT_USE_XML

//散仙组合返回
enum ECombinationResult
{
	eCombinationSucc, //成功
	eCombinationFailed, //失败
	eCombinationMaxLevel, //散仙组合已达最高等级
	eCombinationHaved, //该散仙组合已激活
	eCombinationNotHaved, //该散仙组合未激活
	eCombinationFighterErr, //散仙未招募满
	eCombinationItemErr, //道具不足
	eCombinationMainLevelErr //玩家主将等级不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECombinationResult);
bool EnumStrToVal(const char*, ECombinationResult&);
#endif //PROT_USE_XML

//散功返回
enum EDismissResult
{
	eDismissSucc, //成功
	eDismissFailed, //失败
	eNeedTakeOffStone //需要卸下宝石
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDismissResult);
bool EnumStrToVal(const char*, EDismissResult&);
#endif //PROT_USE_XML

//购买散仙返回
enum EFighterBuyResult
{
	eFighterBuySucc, //成功
	eFighterBuyFailed, //失败
	eFighterBuyAlready, //已购买
	eFighterBuyLackOfMoney //货币不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EFighterBuyResult);
bool EnumStrToVal(const char*, EFighterBuyResult&);
#endif //PROT_USE_XML

//玩家购买散仙信息
struct SFighterBuyInfo
{
	UINT16 wFighterID; //将类型ID
	UINT8 byFighterBuyStatus; //购买状态（0：未购买；1：已购买）

	SFighterBuyInfo();
	SFighterBuyInfo(UINT16 wFighterID_, UINT8 byFighterBuyStatus_);
};

typedef std::vector<SFighterBuyInfo> TVecFighterBuyInfo;

//玩家的散仙组合信息
struct SFighterCombination
{
	UINT8 byGroupID; //散仙组合ID
	UINT8 byGroupLvl; //散仙组合等级
	UINT32 dwGroupExp; //散仙组合当前经验值
	UINT8 byInLineUp; //是否出战在阵型(0未出战 1已出战)
	UINT8 byInEMei; //是否出战在守卫峨眉(0未出战 1已出战)

	SFighterCombination();
	SFighterCombination(UINT8 byGroupID_, UINT8 byGroupLvl_, UINT32 dwGroupExp_, UINT8 byInLineUp_, UINT8 byInEMei_);
};

typedef std::vector<SFighterCombination> TVecFighterCombination;

//数据库同步到游戏服务器的将信息
struct SFighterDBInfo
{
	UINT64 qwInstID; //将唯一ID
	UINT64 qwRoleID; //所属玩家ID
	UINT16 wFighterID; //将类型ID
	UINT8 byRecruited; //是否已招募
	UINT8 byStar; //当前星级
	INT32 iSlot; //将位置
	INT32 iPos; //阵型中的位置
	float fPotential; //潜力
	float fCapacity; //资质
	UINT8 byLevel; //等级
	UINT64 qwExp; //经验
	UINT8 byLianPi; //炼皮
	UINT8 byTongJin; //通筋
	UINT8 byQiangJi; //强肌
	UINT8 byDuanGu; //锻骨
	UINT8 byHuoLuo; //活络
	UINT8 byXiSui; //洗髓
	UINT32 dwDujieExp; //散仙渡劫经验
	UINT32 dwSpiritPower; //元神力

	SFighterDBInfo();
};

typedef std::vector<SFighterDBInfo> TVecFighterDBInfo;

//数据库同步到游戏服务器的技能信息
struct SSkillDBInfo
{
	UINT64 qwOwnerID; //将唯一ID
	UINT32 dwUpSkill1; //使用中的技能1
	UINT32 dwUpSkill2; //使用中的技能2
	UINT32 dwUpSkill3; //使用中的技能3
	UINT32 dwUpSkill4; //使用中的技能4
	UINT32 dwUpSkill5; //使用中的技能5
	UINT32 dwUpSkill6; //使用中的技能6
	UINT32 dwSkill1; //技能1
	UINT32 dwSkill2; //技能2
	UINT32 dwSkill3; //技能3
	UINT32 dwSkill4; //技能4
	UINT32 dwSkill5; //技能5
	UINT32 dwSkill6; //技能6
	UINT32 dwSkill7; //技能7
	UINT32 dwSkill8; //技能8
	UINT32 dwSkill9; //技能9
	UINT32 dwRune1; //符文1
	UINT32 dwRune2; //符文2
	UINT32 dwRune3; //符文3
	UINT32 dwRune4; //符文4
	UINT32 dwRune5; //符文5
	UINT32 dwRune6; //符文6
	UINT32 dwRune7; //符文7
	UINT32 dwRune8; //符文8
	UINT32 dwRune9; //符文9
	UINT32 dwSkillAdv1; //技能进阶1
	UINT32 dwSkillAdv2; //技能进阶2
	UINT32 dwSkillAdv3; //技能进阶3
	UINT32 dwSkillAdv4; //技能进阶4
	UINT32 dwSkillAdv5; //技能进阶5
	UINT32 dwSkillAdv6; //技能进阶6
	UINT32 dwSkillAdv7; //技能进阶7
	UINT32 dwSkillAdv8; //技能进阶8
	UINT32 dwSkillAdv9; //技能进阶9

	SSkillDBInfo();
};

typedef std::vector<SSkillDBInfo> TVecSkillDBInfo;

//数据库同步到游戏服务器的技能信息
struct SPassiveSkillDBInfo
{
	UINT64 qwOwnerID; //将唯一ID
	UINT64 qwRoleID; //玩家一ID
	UINT32 dwSkillID; //技能ID
	UINT32 dwSkillQuality; //技能品质
	UINT32 dwSkillLevel; //技能等级

	SPassiveSkillDBInfo();
	SPassiveSkillDBInfo(UINT64 qwOwnerID_, UINT64 qwRoleID_, UINT32 dwSkillID_, UINT32 dwSkillQuality_, UINT32 dwSkillLevel_);
};

typedef std::vector<SPassiveSkillDBInfo> TVecPassiveSkillDBInfo;

//客栈散仙信息
struct SHeroFighterInTavernInfo
{
	UINT16 wID; //散仙ID
	bool bHired; //是否已招募

	SHeroFighterInTavernInfo();
	SHeroFighterInTavernInfo(UINT16 wID_, bool bHired_);
};

typedef std::vector<SHeroFighterInTavernInfo> TVecHeroFighterInTavernInfo;

//客栈信息
struct STavernInfo
{
	UINT16 wID; //客栈ID
	TVecHeroFighterInTavernInfo vecFighterInfo; //客栈中散仙信息

	STavernInfo();
	STavernInfo(UINT16 wID_, const TVecHeroFighterInTavernInfo& vecFighterInfo_);
#ifdef __GNUG__
	STavernInfo(const STavernInfo& src) = default; //默认拷贝构造函数
	STavernInfo& operator=(const STavernInfo& rhs) = default; //默认赋值操作符
#endif
	STavernInfo(STavernInfo&& src); //转移构造函数
	STavernInfo& operator=(STavernInfo&& rhs); //转移赋值操作符
};

typedef std::vector<STavernInfo> TVecTavernInfo;

//战斗者除了外观之外的杂七杂八的基本信息
struct SFighterBaseInfo
{
	UINT64 qwInstID; //将唯一ID
	UINT16 wFighterID; //将类型ID
	UINT8 byRecruited; //是否已招募
	UINT8 byStar; //当前星级
	INT32 iSlot; //将位置
	INT32 iPos; //阵型中的位置
	UINT8 byLevel; //等级
	UINT64 qwExp; //总经验
	std::string strName; //将名字
	UINT32 dwHpMax; //最大血量
	UINT32 dwHp; //当前血量
	UINT32 dwAura; //当前灵气
	UINT32 dwAuraMax; //最大灵气
	UINT8 byLianPi; //炼皮
	UINT8 byTongJin; //通筋
	UINT8 byQiangJi; //强肌
	UINT8 byDuanGu; //锻骨
	UINT8 byHuoLuo; //活络
	UINT8 byXiSui; //洗髓
	UINT8 byDujieLevel; //散仙渡劫等级
	UINT32 dwDujieExp; //散仙渡劫经验
	UINT8 byQuality; //散仙品质(颜色)
	UINT32 dwSpiritPower; //元神力

	SFighterBaseInfo();
#ifdef __GNUG__
	SFighterBaseInfo(const SFighterBaseInfo& src) = default; //默认拷贝构造函数
	SFighterBaseInfo& operator=(const SFighterBaseInfo& rhs) = default; //默认赋值操作符
#endif
	SFighterBaseInfo(SFighterBaseInfo&& src); //转移构造函数
	SFighterBaseInfo& operator=(SFighterBaseInfo&& rhs); //转移赋值操作符
};

//参与战斗的技能信息
struct SFightSkillInfo
{
	UINT8 byIdx; //技能槽idx
	UINT32 dwSkillID; //技能ID

	SFightSkillInfo();
	SFightSkillInfo(UINT8 byIdx_, UINT32 dwSkillID_);
};

typedef std::vector<SFightSkillInfo> TVecFightSkillInfo;

//心法信息
struct SXinFaInfo
{
	UINT32 dwXinFaID; //心法ID
	UINT8 byXinFaLvl; //心法等级
	INT32 iSlot; //心法槽 -1表示心法没装备

	SXinFaInfo();
	SXinFaInfo(UINT32 dwXinFaID_, UINT8 byXinFaLvl_, INT32 iSlot_);
};

typedef std::vector<SXinFaInfo> TVecXinFaInfo;

//数据库同步到游戏服务器的心法信息
struct SXinFaDBInfo
{
	UINT64 qwRoleID; //所属角色唯一ID
	UINT64 qwOwnerID; //所属散仙ID
	UINT32 dwXinFaID; //心法ID
	UINT8 byXinFaLvl; //心法等级
	INT32 iSlot; //心法槽 -1表示心法没装备

	SXinFaDBInfo();
	SXinFaDBInfo(UINT64 qwRoleID_, UINT64 qwOwnerID_, UINT32 dwXinFaID_, UINT8 byXinFaLvl_, INT32 iSlot_);
};

typedef std::vector<SXinFaDBInfo> TVecXinFaDBInfo;

//战斗者信息
struct SFighterInfo
{
	SFighterBaseInfo oBaseInfo; //基本信息
	NProtoCommon::TVecFtAttrMod oAttrVec; //将属性
	TVecFightSkillInfo vActiveSkill; //装备的主动技能
	TVecFightSkillInfo vPassiveSkill; //被动技能
	SFightSkillInfo oPeerLees; //无双技能
	TVecXinFaInfo vecXinFa; //散仙已经学会的心法信息(注：供客户端计算属性百分比加成)
	NItemProt::TVecItem vecStoneItem; //宝石信息
	NItemProt::TVecEquipTrump vecEquipTrump; //装备法宝信息

	SFighterInfo();
#ifdef __GNUG__
	SFighterInfo(const SFighterInfo& src) = default; //默认拷贝构造函数
	SFighterInfo& operator=(const SFighterInfo& rhs) = default; //默认赋值操作符
#endif
	SFighterInfo(SFighterInfo&& src); //转移构造函数
	SFighterInfo& operator=(SFighterInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SFighterInfo> TVecFighterInfo;

//阵型位置信息
struct SFighterPos
{
	UINT64 qwInstID; //将唯一ID
	INT32 iPos; //将在阵型中的位置：-1表示下阵型

	SFighterPos();
	SFighterPos(UINT64 qwInstID_, INT32 iPos_);
};

typedef std::vector<SFighterPos> TVecFighterPos;

//散仙技能信息
struct SFighterSkill
{
	UINT32 dwSkillID; //技能ID

	SFighterSkill();
	SFighterSkill(UINT32 dwSkillID_);
};

typedef std::vector<SFighterSkill> TVecFighterSkill;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SFighterBuyInfo&);
COutArchive& operator<<(COutArchive&, const SFighterBuyInfo&);

CInArchive& operator>>(CInArchive&, SFighterCombination&);
COutArchive& operator<<(COutArchive&, const SFighterCombination&);

CInArchive& operator>>(CInArchive&, SFighterDBInfo&);
COutArchive& operator<<(COutArchive&, const SFighterDBInfo&);

CInArchive& operator>>(CInArchive&, SSkillDBInfo&);
COutArchive& operator<<(COutArchive&, const SSkillDBInfo&);

CInArchive& operator>>(CInArchive&, SPassiveSkillDBInfo&);
COutArchive& operator<<(COutArchive&, const SPassiveSkillDBInfo&);

CInArchive& operator>>(CInArchive&, SHeroFighterInTavernInfo&);
COutArchive& operator<<(COutArchive&, const SHeroFighterInTavernInfo&);

CInArchive& operator>>(CInArchive&, STavernInfo&);
COutArchive& operator<<(COutArchive&, const STavernInfo&);

CInArchive& operator>>(CInArchive&, SFighterBaseInfo&);
COutArchive& operator<<(COutArchive&, const SFighterBaseInfo&);

CInArchive& operator>>(CInArchive&, SFightSkillInfo&);
COutArchive& operator<<(COutArchive&, const SFightSkillInfo&);

CInArchive& operator>>(CInArchive&, SXinFaInfo&);
COutArchive& operator<<(COutArchive&, const SXinFaInfo&);

CInArchive& operator>>(CInArchive&, SXinFaDBInfo&);
COutArchive& operator<<(COutArchive&, const SXinFaDBInfo&);

CInArchive& operator>>(CInArchive&, SFighterInfo&);
COutArchive& operator<<(COutArchive&, const SFighterInfo&);

CInArchive& operator>>(CInArchive&, SFighterPos&);
COutArchive& operator<<(COutArchive&, const SFighterPos&);

CInArchive& operator>>(CInArchive&, SFighterSkill&);
COutArchive& operator<<(COutArchive&, const SFighterSkill&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SFighterBuyInfo&);
bool ToXML(const SFighterBuyInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFighterBuyInfo&);
bool VectorToXML(const TVecFighterBuyInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFighterCombination&);
bool ToXML(const SFighterCombination&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFighterCombination&);
bool VectorToXML(const TVecFighterCombination&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFighterDBInfo&);
bool ToXML(const SFighterDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFighterDBInfo&);
bool VectorToXML(const TVecFighterDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSkillDBInfo&);
bool ToXML(const SSkillDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSkillDBInfo&);
bool VectorToXML(const TVecSkillDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPassiveSkillDBInfo&);
bool ToXML(const SPassiveSkillDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPassiveSkillDBInfo&);
bool VectorToXML(const TVecPassiveSkillDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SHeroFighterInTavernInfo&);
bool ToXML(const SHeroFighterInTavernInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecHeroFighterInTavernInfo&);
bool VectorToXML(const TVecHeroFighterInTavernInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STavernInfo&);
bool ToXML(const STavernInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTavernInfo&);
bool VectorToXML(const TVecTavernInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFighterBaseInfo&);
bool ToXML(const SFighterBaseInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFightSkillInfo&);
bool ToXML(const SFightSkillInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFightSkillInfo&);
bool VectorToXML(const TVecFightSkillInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SXinFaInfo&);
bool ToXML(const SXinFaInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecXinFaInfo&);
bool VectorToXML(const TVecXinFaInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SXinFaDBInfo&);
bool ToXML(const SXinFaDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecXinFaDBInfo&);
bool VectorToXML(const TVecXinFaDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFighterInfo&);
bool ToXML(const SFighterInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFighterInfo&);
bool VectorToXML(const TVecFighterInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFighterPos&);
bool ToXML(const SFighterPos&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFighterPos&);
bool VectorToXML(const TVecFighterPos&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFighterSkill&);
bool ToXML(const SFighterSkill&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFighterSkill&);
bool VectorToXML(const TVecFighterSkill&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NFighterProt
