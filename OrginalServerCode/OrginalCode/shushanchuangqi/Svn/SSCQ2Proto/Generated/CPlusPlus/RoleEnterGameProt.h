/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    RoleEnterGameProt.h
//  Purpose:      角色信息相关操作协议
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

namespace NRoleEnterGameProt
{

/////////////////////以下为类型定义/////////////////////
//登录结果
enum EEnterResult
{
	eEnterSucceed, //成功
	eRoleNoExist, //角色未创建
	eEnterAlready, //已经在游戏中
	eEnterDataErr, //角色数据错误
	eEnterStateErr, //状态错误
	eEnterFreezErr, //帐号被封
	eEnterOtherErr //其它错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EEnterResult);
bool EnumStrToVal(const char*, EEnterResult&);
#endif //PROT_USE_XML
const char* GetDescription(EEnterResult);

//角色操作的结果
enum ECreateRoleResult
{
	eRoleSucceed, //成功
	eRoleExist, //角色已存在
	eRoleNameExist, //角色名已存在
	eRoleNameInvalid, //角色名称有非法字符
	eRoleNameTooLong, //角色名过长
	eRoleNameTooShort, //角色名过短
	eRoleStateErr, //状态错误
	eRoleJobErr, //职业错误
	eRoleSexErr, //性别错误
	eRoleOtherErr //其它错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECreateRoleResult);
bool EnumStrToVal(const char*, ECreateRoleResult&);
#endif //PROT_USE_XML
const char* GetDescription(ECreateRoleResult);

//查询基础消息
struct PlayerBaseData
{
	std::string strName; //玩家名字
	NProtoCommon::ECareerType eCareer; //职业
	NProtoCommon::ESexType eSex; //性别
	UINT8 byLevel; //玩家等级
	UINT64 qwExp; //玩家经验值
	UINT16 wBagMax; //背包容量
	UINT16 wDepotMax; //仓库容量
	UINT8 byNation; //国家
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
	UINT32 dwPoten; //潜能
	UINT32 dwReiki; //灵力
	UINT32 dwDemonSoul; //锁妖塔魂值
	UINT32 dwSoulAttack; //攻击之魂
	UINT32 dwSoulHp; //生命之魂
	UINT32 dwSoulCritical; //暴击之魂
	UINT32 dwSoulCounter; //反击之魂
	UINT32 dwSoulSpeed; //身法之魂
	UINT32 dwSoulDefence; //防御之魂
	UINT32 dwSoulHit; //命中之魂
	UINT32 dwSoulDodge; //闪避之魂
	UINT32 dwStampHuang; //黄阶除魔印
	UINT32 dwStampXuan; //玄阶除魔印
	UINT32 dwStampDi; //地阶除魔印
	UINT32 dwStampTian; //天阶除魔印
	UINT32 dwStampXing; //星阶除魔印
	UINT32 dwStampYue; //月阶除魔印
	UINT32 dwStampDi2; //帝阶除魔印
	UINT32 dwStampXian; //仙阶除魔印
	UINT32 dwStampSheng; //圣阶除魔印
	UINT32 dwStampFo; //佛阶除魔印
	UINT32 dwBTPoint; //战斗力
	UINT32 dwBlueFairyFate; //蓝色仙缘
	UINT32 dwPurpleFairyFate; //紫色仙缘
	UINT32 dwOrangeFairyFate; //橙色仙缘
	UINT32 dwTotalRecharge; //总充值数
	TVecUINT16 vecOwnTitle; //拥有称号
	TVecUINT16 vecEquipTitle; //装备称号
	std::string strGuide; //新手引导信息
	UINT8 byWallow; //防沉迷
	TVecUINT16 vecIconAppear; //Icon开启
	TVecUINT16 vecIconDel; //Icon关闭
	UINT32 dwDemonTowerFloorID; //通关镇妖塔层数
	UINT32 dwDemonTowerPrizeFloorID; //镇妖塔领奖层数
	UINT32 dwCreateTime; //玩家创角时间

	PlayerBaseData();
#ifdef __GNUG__
	PlayerBaseData(const PlayerBaseData& src) = default; //默认拷贝构造函数
	PlayerBaseData& operator=(const PlayerBaseData& rhs) = default; //默认赋值操作符
#endif
	PlayerBaseData(PlayerBaseData&& src); //转移构造函数
	PlayerBaseData& operator=(PlayerBaseData&& rhs); //转移赋值操作符
};

//查询角色消息
struct RoleEnterGameData
{
	UINT8 byIsUser; //0表示不存在
	PlayerBaseData sBaseInfo; //基础信息

	RoleEnterGameData();
	RoleEnterGameData(UINT8 byIsUser_, const PlayerBaseData& sBaseInfo_);
#ifdef __GNUG__
	RoleEnterGameData(const RoleEnterGameData& src) = default; //默认拷贝构造函数
	RoleEnterGameData& operator=(const RoleEnterGameData& rhs) = default; //默认赋值操作符
#endif
	RoleEnterGameData(RoleEnterGameData&& src); //转移构造函数
	RoleEnterGameData& operator=(RoleEnterGameData&& rhs); //转移赋值操作符
};

//角色信息
struct SCreateRoleInfo
{
	std::string strName; //角色名
	NProtoCommon::ECareerType eCareer; //职业
	NProtoCommon::ESexType eSex; //性别
	std::string strInviteRoleID; //好友邀请id
	std::string strIP; //创角时ip

	SCreateRoleInfo();
	SCreateRoleInfo(const std::string& strName_, NProtoCommon::ECareerType eCareer_, NProtoCommon::ESexType eSex_, const std::string& strInviteRoleID_, const std::string& strIP_);
#ifdef __GNUG__
	SCreateRoleInfo(const SCreateRoleInfo& src) = default; //默认拷贝构造函数
	SCreateRoleInfo& operator=(const SCreateRoleInfo& rhs) = default; //默认赋值操作符
#endif
	SCreateRoleInfo(SCreateRoleInfo&& src); //转移构造函数
	SCreateRoleInfo& operator=(SCreateRoleInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SCreateRoleInfo> TVecCreateRoleInfo;

//角色信息
struct SEnterParam
{
	NProtoCommon::EPtType byPtType; //平台类型
	NProtoCommon::EQQPtType byQQPtType; //QQ平台类型
	UINT8 byQQPtLv; //QQ平台类型等级
	UINT8 byQQPtYearType; //是否年费
	UINT8 byQQPtLuxuryType; //是否豪华
	std::string customPar1; //广告主来源
	std::string customPar2; //广告次来源
	std::string strOpenId; //openID
	std::string strOpenKey; //openKey

	SEnterParam();
	SEnterParam(NProtoCommon::EPtType byPtType_, NProtoCommon::EQQPtType byQQPtType_, UINT8 byQQPtLv_, UINT8 byQQPtYearType_, UINT8 byQQPtLuxuryType_, 
		const std::string& customPar1_, const std::string& customPar2_, const std::string& strOpenId_, const std::string& strOpenKey_);
#ifdef __GNUG__
	SEnterParam(const SEnterParam& src) = default; //默认拷贝构造函数
	SEnterParam& operator=(const SEnterParam& rhs) = default; //默认赋值操作符
#endif
	SEnterParam(SEnterParam&& src); //转移构造函数
	SEnterParam& operator=(SEnterParam&& rhs); //转移赋值操作符
};

typedef std::vector<SEnterParam> TVecEnterParam;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, PlayerBaseData&);
COutArchive& operator<<(COutArchive&, const PlayerBaseData&);

CInArchive& operator>>(CInArchive&, RoleEnterGameData&);
COutArchive& operator<<(COutArchive&, const RoleEnterGameData&);

CInArchive& operator>>(CInArchive&, SCreateRoleInfo&);
COutArchive& operator<<(COutArchive&, const SCreateRoleInfo&);

CInArchive& operator>>(CInArchive&, SEnterParam&);
COutArchive& operator<<(COutArchive&, const SEnterParam&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, PlayerBaseData&);
bool ToXML(const PlayerBaseData&, TiXmlElement&);

bool FromXML(TiXmlElement&, RoleEnterGameData&);
bool ToXML(const RoleEnterGameData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SCreateRoleInfo&);
bool ToXML(const SCreateRoleInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCreateRoleInfo&);
bool VectorToXML(const TVecCreateRoleInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEnterParam&);
bool ToXML(const SEnterParam&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecEnterParam&);
bool VectorToXML(const TVecEnterParam&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NRoleEnterGameProt
