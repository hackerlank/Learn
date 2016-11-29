/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    RoleInfoDefine.cpp
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "RoleInfoDefine.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NRoleInfoDefine
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EBattleReportType e)
{
	switch(e)
	{
	case eTypeLadder:
		return "eTypeLadder";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBattleReportType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBattleReportType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTypeLadder", eTypeLadder));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(EBattleReportType e)
{
	switch(e)
	{
	case eTypeLadder:
		return "天梯";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EBattleActionType e)
{
	switch(e)
	{
	case eTypeAttack:
		return "eTypeAttack";
	case eTypeDefense:
		return "eTypeDefense";
	case eTypeALL:
		return "eTypeALL";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBattleActionType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBattleActionType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTypeAttack", eTypeAttack));
		mapStr2Val.insert(make_pair("eTypeDefense", eTypeDefense));
		mapStr2Val.insert(make_pair("eTypeALL", eTypeALL));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(EBattleActionType e)
{
	switch(e)
	{
	case eTypeAttack:
		return "玩家进攻";
	case eTypeDefense:
		return "玩家防守";
	case eTypeALL:
		return "防守和进攻";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EBeastSoulType e)
{
	switch(e)
	{
	case eBeastSoulNone:
		return "eBeastSoulNone";
	case eBeastSoulAtttack:
		return "eBeastSoulAtttack";
	case eBeastSoulHP:
		return "eBeastSoulHP";
	case eBeastSoulCritical:
		return "eBeastSoulCritical";
	case eBeastSoulCounter:
		return "eBeastSoulCounter";
	case eBeastSoulSpeed:
		return "eBeastSoulSpeed";
	case eBeastSoulDefence:
		return "eBeastSoulDefence";
	case eBeastSoulHit:
		return "eBeastSoulHit";
	case eBeastSoulDodge:
		return "eBeastSoulDodge";
	case eBeastSoulMax:
		return "eBeastSoulMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBeastSoulType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBeastSoulType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBeastSoulNone", eBeastSoulNone));
		mapStr2Val.insert(make_pair("eBeastSoulAtttack", eBeastSoulAtttack));
		mapStr2Val.insert(make_pair("eBeastSoulHP", eBeastSoulHP));
		mapStr2Val.insert(make_pair("eBeastSoulCritical", eBeastSoulCritical));
		mapStr2Val.insert(make_pair("eBeastSoulCounter", eBeastSoulCounter));
		mapStr2Val.insert(make_pair("eBeastSoulSpeed", eBeastSoulSpeed));
		mapStr2Val.insert(make_pair("eBeastSoulDefence", eBeastSoulDefence));
		mapStr2Val.insert(make_pair("eBeastSoulHit", eBeastSoulHit));
		mapStr2Val.insert(make_pair("eBeastSoulDodge", eBeastSoulDodge));
		mapStr2Val.insert(make_pair("eBeastSoulMax", eBeastSoulMax));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

#ifdef PROT_USE_XML

const char* EnumValToStr(EDataType e)
{
	switch(e)
	{
	case eTypeRoleBaseInfo:
		return "eTypeRoleBaseInfo";
	case eTypeItemInfo:
		return "eTypeItemInfo";
	case eTypePlayerDgn:
		return "eTypePlayerDgn";
	case eTypeFighterInfo:
		return "eTypeFighterInfo";
	case eTypeTaskInfo:
		return "eTypeTaskInfo";
	case eTypeSkillInfo:
		return "eTypeSkillInfo";
	case eTypePassiveSkillInfo:
		return "eTypePassiveSkillInfo";
	case eTypeFriendInfo:
		return "eTypeFriendInfo";
	case eTypeVarInfo:
		return "eTypeVarInfo";
	case eTypeCittaInfo:
		return "eTypeCittaInfo";
	case eTypeSlotsInfo:
		return "eTypeSlotsInfo";
	case eTypeTrumpInfo:
		return "eTypeTrumpInfo";
	case eTypeEquipTrumpInfo:
		return "eTypeEquipTrumpInfo";
	case eTypeEquipTrumpShuffleInfo:
		return "eTypeEquipTrumpShuffleInfo";
	case eTypeFormationInfo:
		return "eTypeFormationInfo";
	case eTypePetDataInfo:
		return "eTypePetDataInfo";
	case eTypeRolePetInfo:
		return "eTypeRolePetInfo";
	case eTypeBeastSoulInfo:
		return "eTypeBeastSoulInfo";
	case eTypeTripodFireInfo:
		return "eTypeTripodFireInfo";
	case eTypeArena:
		return "eTypeArena";
	case eTypeBuffInfo:
		return "eTypeBuffInfo";
	case eTypeFashionInfo:
		return "eTypeFashionInfo";
	case eTypeSoulSpaceInfo:
		return "eTypeSoulSpaceInfo";
	case eTypeBubbleInfo:
		return "eTypeBubbleInfo";
	case eTypeHorseDBInfo:
		return "eTypeHorseDBInfo";
	case eTypeGroupTask:
		return "eTypeGroupTask";
	case eTypeYaMenTask:
		return "eTypeYaMenTask";
	case eTypeActivityTask:
		return "eTypeActivityTask";
	case eTypeTitle:
		return "eTypeTitle";
	case eTypeAchievementInfo:
		return "eTypeAchievementInfo";
	case eTypeCollectionInfo:
		return "eTypeCollectionInfo";
	case eTypeAttacked:
		return "eTypeAttacked";
	case eTypeExchangedItem:
		return "eTypeExchangedItem";
	case eTypeSweep:
		return "eTypeSweep";
	case eTypePendRes:
		return "eTypePendRes";
	case eTypeXinFaInfo:
		return "eTypeXinFaInfo";
	case eTypeLevelPrize:
		return "eTypeLevelPrize";
	case eTypeYelloDiamond:
		return "eTypeYelloDiamond";
	case eTypeEventInfo:
		return "eTypeEventInfo";
	case eTypeBuyItemLimit:
		return "eTypeBuyItemLimit";
	case eTypeDayTarget:
		return "eTypeDayTarget";
	case eTypeFighterComination:
		return "eTypeFighterComination";
	case eTypeBattleArray:
		return "eTypeBattleArray";
	case eTypeAutoStore:
		return "eTypeAutoStore";
	case eTypeTH:
		return "eTypeTH";
	case eTypeBeauty:
		return "eTypeBeauty";
	case eTypeFightFormation:
		return "eTypeFightFormation";
	case eTypeFightHero:
		return "eTypeFightHero";
	case eTypeShip:
		return "eTypeShip";
	case eTypeGuardEMei:
		return "eTypeGuardEMei";
	case eTypeGemstone:
		return "eTypeGemstone";
	case eTypeShengLing:
		return "eTypeShengLing";
	case eTypeShengLingPrize:
		return "eTypeShengLingPrize";
	case eTypeMax:
		return "eTypeMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDataType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDataType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTypeRoleBaseInfo", eTypeRoleBaseInfo));
		mapStr2Val.insert(make_pair("eTypeItemInfo", eTypeItemInfo));
		mapStr2Val.insert(make_pair("eTypePlayerDgn", eTypePlayerDgn));
		mapStr2Val.insert(make_pair("eTypeFighterInfo", eTypeFighterInfo));
		mapStr2Val.insert(make_pair("eTypeTaskInfo", eTypeTaskInfo));
		mapStr2Val.insert(make_pair("eTypeSkillInfo", eTypeSkillInfo));
		mapStr2Val.insert(make_pair("eTypePassiveSkillInfo", eTypePassiveSkillInfo));
		mapStr2Val.insert(make_pair("eTypeFriendInfo", eTypeFriendInfo));
		mapStr2Val.insert(make_pair("eTypeVarInfo", eTypeVarInfo));
		mapStr2Val.insert(make_pair("eTypeCittaInfo", eTypeCittaInfo));
		mapStr2Val.insert(make_pair("eTypeSlotsInfo", eTypeSlotsInfo));
		mapStr2Val.insert(make_pair("eTypeTrumpInfo", eTypeTrumpInfo));
		mapStr2Val.insert(make_pair("eTypeEquipTrumpInfo", eTypeEquipTrumpInfo));
		mapStr2Val.insert(make_pair("eTypeEquipTrumpShuffleInfo", eTypeEquipTrumpShuffleInfo));
		mapStr2Val.insert(make_pair("eTypeFormationInfo", eTypeFormationInfo));
		mapStr2Val.insert(make_pair("eTypePetDataInfo", eTypePetDataInfo));
		mapStr2Val.insert(make_pair("eTypeRolePetInfo", eTypeRolePetInfo));
		mapStr2Val.insert(make_pair("eTypeBeastSoulInfo", eTypeBeastSoulInfo));
		mapStr2Val.insert(make_pair("eTypeTripodFireInfo", eTypeTripodFireInfo));
		mapStr2Val.insert(make_pair("eTypeArena", eTypeArena));
		mapStr2Val.insert(make_pair("eTypeBuffInfo", eTypeBuffInfo));
		mapStr2Val.insert(make_pair("eTypeFashionInfo", eTypeFashionInfo));
		mapStr2Val.insert(make_pair("eTypeSoulSpaceInfo", eTypeSoulSpaceInfo));
		mapStr2Val.insert(make_pair("eTypeBubbleInfo", eTypeBubbleInfo));
		mapStr2Val.insert(make_pair("eTypeHorseDBInfo", eTypeHorseDBInfo));
		mapStr2Val.insert(make_pair("eTypeGroupTask", eTypeGroupTask));
		mapStr2Val.insert(make_pair("eTypeYaMenTask", eTypeYaMenTask));
		mapStr2Val.insert(make_pair("eTypeActivityTask", eTypeActivityTask));
		mapStr2Val.insert(make_pair("eTypeTitle", eTypeTitle));
		mapStr2Val.insert(make_pair("eTypeAchievementInfo", eTypeAchievementInfo));
		mapStr2Val.insert(make_pair("eTypeCollectionInfo", eTypeCollectionInfo));
		mapStr2Val.insert(make_pair("eTypeAttacked", eTypeAttacked));
		mapStr2Val.insert(make_pair("eTypeExchangedItem", eTypeExchangedItem));
		mapStr2Val.insert(make_pair("eTypeSweep", eTypeSweep));
		mapStr2Val.insert(make_pair("eTypePendRes", eTypePendRes));
		mapStr2Val.insert(make_pair("eTypeXinFaInfo", eTypeXinFaInfo));
		mapStr2Val.insert(make_pair("eTypeLevelPrize", eTypeLevelPrize));
		mapStr2Val.insert(make_pair("eTypeYelloDiamond", eTypeYelloDiamond));
		mapStr2Val.insert(make_pair("eTypeEventInfo", eTypeEventInfo));
		mapStr2Val.insert(make_pair("eTypeBuyItemLimit", eTypeBuyItemLimit));
		mapStr2Val.insert(make_pair("eTypeDayTarget", eTypeDayTarget));
		mapStr2Val.insert(make_pair("eTypeFighterComination", eTypeFighterComination));
		mapStr2Val.insert(make_pair("eTypeBattleArray", eTypeBattleArray));
		mapStr2Val.insert(make_pair("eTypeAutoStore", eTypeAutoStore));
		mapStr2Val.insert(make_pair("eTypeTH", eTypeTH));
		mapStr2Val.insert(make_pair("eTypeBeauty", eTypeBeauty));
		mapStr2Val.insert(make_pair("eTypeFightFormation", eTypeFightFormation));
		mapStr2Val.insert(make_pair("eTypeFightHero", eTypeFightHero));
		mapStr2Val.insert(make_pair("eTypeShip", eTypeShip));
		mapStr2Val.insert(make_pair("eTypeGuardEMei", eTypeGuardEMei));
		mapStr2Val.insert(make_pair("eTypeGemstone", eTypeGemstone));
		mapStr2Val.insert(make_pair("eTypeShengLing", eTypeShengLing));
		mapStr2Val.insert(make_pair("eTypeShengLingPrize", eTypeShengLingPrize));
		mapStr2Val.insert(make_pair("eTypeMax", eTypeMax));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(EDataType e)
{
	switch(e)
	{
	case eTypeRoleBaseInfo:
		return "玩家基本数据";
	case eTypeItemInfo:
		return "玩家物品数据";
	case eTypePlayerDgn:
		return "玩家副本数据";
	case eTypeFighterInfo:
		return "玩家将信息";
	case eTypeTaskInfo:
		return "玩家任务信息";
	case eTypeSkillInfo:
		return "技能信息";
	case eTypePassiveSkillInfo:
		return "被动技能信息";
	case eTypeFriendInfo:
		return "关系信息";
	case eTypeVarInfo:
		return "关系信息";
	case eTypeCittaInfo:
		return "玩家心法数据";
	case eTypeSlotsInfo:
		return "玩家/其他槽心法数据";
	case eTypeTrumpInfo:
		return "法宝信息";
	case eTypeEquipTrumpInfo:
		return "装备法宝信息";
	case eTypeEquipTrumpShuffleInfo:
		return "装备法宝洗炼信息";
	case eTypeFormationInfo:
		return "阵形信息";
	case eTypePetDataInfo:
		return "阵灵信息";
	case eTypeRolePetInfo:
		return "阵灵全局信息";
	case eTypeBeastSoulInfo:
		return "兽魂信息";
	case eTypeTripodFireInfo:
		return "九疑鼎的火种信息";
	case eTypeArena:
		return "斗剑信息";
	case eTypeBuffInfo:
		return "Buff信息";
	case eTypeFashionInfo:
		return "时装信息";
	case eTypeSoulSpaceInfo:
		return "魄空间信息";
	case eTypeBubbleInfo:
		return "气泡信息";
	case eTypeHorseDBInfo:
		return "坐骑信息";
	case eTypeGroupTask:
		return "师门任务";
	case eTypeYaMenTask:
		return "衙门任务";
	case eTypeActivityTask:
		return "活跃度任务";
	case eTypeTitle:
		return "称号";
	case eTypeAchievementInfo:
		return "成就";
	case eTypeCollectionInfo:
		return "收藏";
	case eTypeAttacked:
		return "玩家被攻击信息";
	case eTypeExchangedItem:
		return "玩家兑换商品信息";
	case eTypeSweep:
		return "玩家扫荡信息";
	case eTypePendRes:
		return "玩家暂存信息";
	case eTypeXinFaInfo:
		return "心法信息";
	case eTypeLevelPrize:
		return "心法信息";
	case eTypeYelloDiamond:
		return "黄钻信息";
	case eTypeEventInfo:
		return "事件信息";
	case eTypeBuyItemLimit:
		return "商品数量限购信息";
	case eTypeDayTarget:
		return "七日目标活动";
	case eTypeFighterComination:
		return "玩家的散仙组合信息";
	case eTypeBattleArray:
		return "破阵信息";
	case eTypeAutoStore:
		return "动态存储信息";
	case eTypeTH:
		return "寻宝信息";
	case eTypeBeauty:
		return "美女系统";
	case eTypeFightFormation:
		return "新阵型系统";
	case eTypeFightHero:
		return "散仙数据";
	case eTypeShip:
		return "金船";
	case eTypeGuardEMei:
		return "守卫峨眉";
	case eTypeGemstone:
		return "宝石";
	case eTypeShengLing:
		return "圣陵信息";
	case eTypeShengLingPrize:
		return "圣陵奖励信息";
	case eTypeMax:
		return "最大值";
	default:
		return "未知错误";
	}
}

RoleBaseInfo::RoleBaseInfo() : eCareer((NProtoCommon::ECareerType)0), eSex((NProtoCommon::ESexType)0), wMapID(0), fX(0), fY(0), 
			qwDgnId(0), dwDgnTypeID(0), wDgnMapId(0), fDgnfX(0), fDgnfY(0), 
			wBagMax(0), wDepotMax(0), dwPendSilver(0), dwPendCoupon(0), dwPendExp(0), 
			dwPendGold(0), dwDemonTowerFloorID(0), dwDemonTowerPrizeFloorID(0), dwPackNextUnlockTime(0), dwActivity(0), 
			qwSittingPlayer(0), dwLuckyCoupon(0), byLevel(0), qwExp(0), byNation(0), 
			byGMLvl(0), dwTotalRecharge(0), dwLoginTime(0), dwOfflineTime(0), dwLockExpireTime(0), 
			dwForbExpireTime(0), dwGold(0), dwFreeGold(0), dwSilver(0), dwCoupon(0), 
			dwSoul(0), dwPrestige(0), dwHonor(0), dwPExp(0), dwAction(0), 
			dwPoten(0), dwReiki(0), dwDemonSoul(0), dwSoulAttack(0), dwSoulHp(0), 
			dwSoulCritical(0), dwSoulCounter(0), dwSoulSpeed(0), dwSoulDefence(0), dwSoulHit(0), 
			dwSoulDodge(0), dwStampHuang(0), dwStampXuan(0), dwStampDi(0), dwStampTian(0), 
			dwStampXing(0), dwStampYue(0), dwStampDi2(0), dwStampXian(0), dwStampSheng(0), 
			dwStampFo(0), dwLoveHeart(0), dwBlueFairyFate(0), dwPurpleFairyFate(0), dwOrangeFairyFate(0), 
			dwDuJieFu(0), dwBTPoint(0), byDomain(0), byDomainLvl(0), byDisplayLvl(0), 
			byDomainYear(0), wMood(0), wAchievementLevel(0), dwAchievementAP(0), wCollectLevel(0), 
			dwCollectAP(0), qwInvitedID(0), byWallow(0), dwIndulgeKickTime(0), byYDLevel(0), 
			dwCreateTime(0), wLastSaveMapID(0), fLastSaveX(0), fLastSaveY(0) { }

RoleBaseInfo::RoleBaseInfo(RoleBaseInfo&& src) : strName(move(src.strName)), eCareer(src.eCareer), eSex(src.eSex), wMapID(src.wMapID), fX(src.fX), 
			fY(src.fY), qwDgnId(src.qwDgnId), dwDgnTypeID(src.dwDgnTypeID), wDgnMapId(src.wDgnMapId), fDgnfX(src.fDgnfX), 
			fDgnfY(src.fDgnfY), wBagMax(src.wBagMax), wDepotMax(src.wDepotMax), dwPendSilver(src.dwPendSilver), dwPendCoupon(src.dwPendCoupon), 
			dwPendExp(src.dwPendExp), dwPendGold(src.dwPendGold), dwDemonTowerFloorID(src.dwDemonTowerFloorID), dwDemonTowerPrizeFloorID(src.dwDemonTowerPrizeFloorID), strGuide(move(src.strGuide)), 
			szIcon(move(src.szIcon)), szIconDel(move(src.szIconDel)), szIconActive(move(src.szIconActive)), dwPackNextUnlockTime(src.dwPackNextUnlockTime), dwActivity(src.dwActivity), 
			qwSittingPlayer(src.qwSittingPlayer), szDgnStarAward(move(src.szDgnStarAward)), strCreateIP(move(src.strCreateIP)), strLoginIP(move(src.strLoginIP)), dwLuckyCoupon(src.dwLuckyCoupon), 
			byLevel(src.byLevel), qwExp(src.qwExp), byNation(src.byNation), byGMLvl(src.byGMLvl), dwTotalRecharge(src.dwTotalRecharge), 
			dwLoginTime(src.dwLoginTime), dwOfflineTime(src.dwOfflineTime), dwLockExpireTime(src.dwLockExpireTime), dwForbExpireTime(src.dwForbExpireTime), dwGold(src.dwGold), 
			dwFreeGold(src.dwFreeGold), dwSilver(src.dwSilver), dwCoupon(src.dwCoupon), dwSoul(src.dwSoul), dwPrestige(src.dwPrestige), 
			dwHonor(src.dwHonor), dwPExp(src.dwPExp), dwAction(src.dwAction), dwPoten(src.dwPoten), dwReiki(src.dwReiki), 
			dwDemonSoul(src.dwDemonSoul), dwSoulAttack(src.dwSoulAttack), dwSoulHp(src.dwSoulHp), dwSoulCritical(src.dwSoulCritical), dwSoulCounter(src.dwSoulCounter), 
			dwSoulSpeed(src.dwSoulSpeed), dwSoulDefence(src.dwSoulDefence), dwSoulHit(src.dwSoulHit), dwSoulDodge(src.dwSoulDodge), dwStampHuang(src.dwStampHuang), 
			dwStampXuan(src.dwStampXuan), dwStampDi(src.dwStampDi), dwStampTian(src.dwStampTian), dwStampXing(src.dwStampXing), dwStampYue(src.dwStampYue), 
			dwStampDi2(src.dwStampDi2), dwStampXian(src.dwStampXian), dwStampSheng(src.dwStampSheng), dwStampFo(src.dwStampFo), dwLoveHeart(src.dwLoveHeart), 
			dwBlueFairyFate(src.dwBlueFairyFate), dwPurpleFairyFate(src.dwPurpleFairyFate), dwOrangeFairyFate(src.dwOrangeFairyFate), dwDuJieFu(src.dwDuJieFu), dwBTPoint(src.dwBTPoint), 
			szOwnTitle(move(src.szOwnTitle)), szEquipTitle(move(src.szEquipTitle)), byDomain(src.byDomain), byDomainLvl(src.byDomainLvl), byDisplayLvl(src.byDisplayLvl), 
			byDomainYear(src.byDomainYear), szOpenId(move(src.szOpenId)), szOpenKey(move(src.szOpenKey)), strSign(move(src.strSign)), wMood(src.wMood), 
			wAchievementLevel(src.wAchievementLevel), dwAchievementAP(src.dwAchievementAP), wCollectLevel(src.wCollectLevel), dwCollectAP(src.dwCollectAP), qwInvitedID(src.qwInvitedID), 
			byWallow(src.byWallow), dwIndulgeKickTime(src.dwIndulgeKickTime), byYDLevel(src.byYDLevel), dwCreateTime(src.dwCreateTime), wLastSaveMapID(src.wLastSaveMapID), 
			fLastSaveX(src.fLastSaveX), fLastSaveY(src.fLastSaveY) { }

RoleBaseInfo& RoleBaseInfo::operator=(RoleBaseInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~RoleBaseInfo();
		new (this) RoleBaseInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, RoleBaseInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.strName;
	src >> (UINT8&)s.eCareer;
	src >> (UINT8&)s.eSex;
	src >> s.wMapID;
	src >> s.fX;
	src >> s.fY;
	src >> s.qwDgnId;
	src >> s.dwDgnTypeID;
	src >> s.wDgnMapId;
	src >> s.fDgnfX;
	src >> s.fDgnfY;
	src >> s.wBagMax;
	src >> s.wDepotMax;
	src >> s.dwPendSilver;
	src >> s.dwPendCoupon;
	src >> s.dwPendExp;
	src >> s.dwPendGold;
	src >> s.dwDemonTowerFloorID;
	src >> s.dwDemonTowerPrizeFloorID;
	src >> s.strGuide;
	src >> s.szIcon;
	src >> s.szIconDel;
	src >> s.szIconActive;
	src >> s.dwPackNextUnlockTime;
	src >> s.dwActivity;
	src >> s.qwSittingPlayer;
	src >> s.szDgnStarAward;
	src >> s.strCreateIP;
	src >> s.strLoginIP;
	src >> s.dwLuckyCoupon;
	src >> s.byLevel;
	src >> s.qwExp;
	src >> s.byNation;
	src >> s.byGMLvl;
	src >> s.dwTotalRecharge;
	src >> s.dwLoginTime;
	src >> s.dwOfflineTime;
	src >> s.dwLockExpireTime;
	src >> s.dwForbExpireTime;
	src >> s.dwGold;
	src >> s.dwFreeGold;
	src >> s.dwSilver;
	src >> s.dwCoupon;
	src >> s.dwSoul;
	src >> s.dwPrestige;
	src >> s.dwHonor;
	src >> s.dwPExp;
	src >> s.dwAction;
	src >> s.dwPoten;
	src >> s.dwReiki;
	src >> s.dwDemonSoul;
	src >> s.dwSoulAttack;
	src >> s.dwSoulHp;
	src >> s.dwSoulCritical;
	src >> s.dwSoulCounter;
	src >> s.dwSoulSpeed;
	src >> s.dwSoulDefence;
	src >> s.dwSoulHit;
	src >> s.dwSoulDodge;
	src >> s.dwStampHuang;
	src >> s.dwStampXuan;
	src >> s.dwStampDi;
	src >> s.dwStampTian;
	src >> s.dwStampXing;
	src >> s.dwStampYue;
	src >> s.dwStampDi2;
	src >> s.dwStampXian;
	src >> s.dwStampSheng;
	src >> s.dwStampFo;
	src >> s.dwLoveHeart;
	src >> s.dwBlueFairyFate;
	src >> s.dwPurpleFairyFate;
	src >> s.dwOrangeFairyFate;
	src >> s.dwDuJieFu;
	src >> s.dwBTPoint;
	src >> s.szOwnTitle;
	src >> s.szEquipTitle;
	src >> s.byDomain;
	src >> s.byDomainLvl;
	src >> s.byDisplayLvl;
	src >> s.byDomainYear;
	src >> s.szOpenId;
	src >> s.szOpenKey;
	src >> s.strSign;
	src >> s.wMood;
	src >> s.wAchievementLevel;
	src >> s.dwAchievementAP;
	src >> s.wCollectLevel;
	src >> s.dwCollectAP;
	src >> s.qwInvitedID;
	src >> s.byWallow;
	src >> s.dwIndulgeKickTime;
	src >> s.byYDLevel;
	src >> s.dwCreateTime;
	src >> s.wLastSaveMapID;
	src >> s.fLastSaveX;
	src >> s.fLastSaveY;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const RoleBaseInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.strName;
	src << (UINT8&)s.eCareer;
	src << (UINT8&)s.eSex;
	src << s.wMapID;
	src << s.fX;
	src << s.fY;
	src << s.qwDgnId;
	src << s.dwDgnTypeID;
	src << s.wDgnMapId;
	src << s.fDgnfX;
	src << s.fDgnfY;
	src << s.wBagMax;
	src << s.wDepotMax;
	src << s.dwPendSilver;
	src << s.dwPendCoupon;
	src << s.dwPendExp;
	src << s.dwPendGold;
	src << s.dwDemonTowerFloorID;
	src << s.dwDemonTowerPrizeFloorID;
	src << s.strGuide;
	src << s.szIcon;
	src << s.szIconDel;
	src << s.szIconActive;
	src << s.dwPackNextUnlockTime;
	src << s.dwActivity;
	src << s.qwSittingPlayer;
	src << s.szDgnStarAward;
	src << s.strCreateIP;
	src << s.strLoginIP;
	src << s.dwLuckyCoupon;
	src << s.byLevel;
	src << s.qwExp;
	src << s.byNation;
	src << s.byGMLvl;
	src << s.dwTotalRecharge;
	src << s.dwLoginTime;
	src << s.dwOfflineTime;
	src << s.dwLockExpireTime;
	src << s.dwForbExpireTime;
	src << s.dwGold;
	src << s.dwFreeGold;
	src << s.dwSilver;
	src << s.dwCoupon;
	src << s.dwSoul;
	src << s.dwPrestige;
	src << s.dwHonor;
	src << s.dwPExp;
	src << s.dwAction;
	src << s.dwPoten;
	src << s.dwReiki;
	src << s.dwDemonSoul;
	src << s.dwSoulAttack;
	src << s.dwSoulHp;
	src << s.dwSoulCritical;
	src << s.dwSoulCounter;
	src << s.dwSoulSpeed;
	src << s.dwSoulDefence;
	src << s.dwSoulHit;
	src << s.dwSoulDodge;
	src << s.dwStampHuang;
	src << s.dwStampXuan;
	src << s.dwStampDi;
	src << s.dwStampTian;
	src << s.dwStampXing;
	src << s.dwStampYue;
	src << s.dwStampDi2;
	src << s.dwStampXian;
	src << s.dwStampSheng;
	src << s.dwStampFo;
	src << s.dwLoveHeart;
	src << s.dwBlueFairyFate;
	src << s.dwPurpleFairyFate;
	src << s.dwOrangeFairyFate;
	src << s.dwDuJieFu;
	src << s.dwBTPoint;
	src << s.szOwnTitle;
	src << s.szEquipTitle;
	src << s.byDomain;
	src << s.byDomainLvl;
	src << s.byDisplayLvl;
	src << s.byDomainYear;
	src << s.szOpenId;
	src << s.szOpenKey;
	src << s.strSign;
	src << s.wMood;
	src << s.wAchievementLevel;
	src << s.dwAchievementAP;
	src << s.wCollectLevel;
	src << s.dwCollectAP;
	src << s.qwInvitedID;
	src << s.byWallow;
	src << s.dwIndulgeKickTime;
	src << s.byYDLevel;
	src << s.dwCreateTime;
	src << s.wLastSaveMapID;
	src << s.fLastSaveX;
	src << s.fLastSaveY;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, RoleBaseInfo& s)
{
	if(strcmp(rElement.Value(), "RoleBaseInfo") != 0)
	{
		LOG_CRI << "rElement is not RoleBaseInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strName") != 0)
	{
		LOG_CRI << "Attribute: name is not strName!";
		return false;
	}
	const char* pszVal_strName = pElemChild->Attribute("value");
	if(pszVal_strName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strName = pszVal_strName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eCareer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::ECareerType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::ECareerType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eCareer") != 0)
	{
		LOG_CRI << "Attribute: name is not eCareer!";
		return false;
	}
	const char* pszVal_eCareer = pElemChild->Attribute("value");
	if(pszVal_eCareer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_eCareer, s.eCareer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::ESexType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::ESexType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSex") != 0)
	{
		LOG_CRI << "Attribute: name is not eSex!";
		return false;
	}
	const char* pszVal_eSex = pElemChild->Attribute("value");
	if(pszVal_eSex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_eSex, s.eSex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMapID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMapID") != 0)
	{
		LOG_CRI << "Attribute: name is not wMapID!";
		return false;
	}
	const char* pszVal_wMapID = pElemChild->Attribute("value");
	if(pszVal_wMapID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMapID, s.wMapID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fX is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fX") != 0)
	{
		LOG_CRI << "Attribute: name is not fX!";
		return false;
	}
	const char* pszVal_fX = pElemChild->Attribute("value");
	if(pszVal_fX == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fX, s.fX))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fY is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fY") != 0)
	{
		LOG_CRI << "Attribute: name is not fY!";
		return false;
	}
	const char* pszVal_fY = pElemChild->Attribute("value");
	if(pszVal_fY == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fY, s.fY))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwDgnId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwDgnId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwDgnId!";
		return false;
	}
	const char* pszVal_qwDgnId = pElemChild->Attribute("value");
	if(pszVal_qwDgnId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwDgnId, s.qwDgnId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDgnTypeID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDgnTypeID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDgnTypeID!";
		return false;
	}
	const char* pszVal_dwDgnTypeID = pElemChild->Attribute("value");
	if(pszVal_dwDgnTypeID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDgnTypeID, s.dwDgnTypeID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wDgnMapId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wDgnMapId") != 0)
	{
		LOG_CRI << "Attribute: name is not wDgnMapId!";
		return false;
	}
	const char* pszVal_wDgnMapId = pElemChild->Attribute("value");
	if(pszVal_wDgnMapId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wDgnMapId, s.wDgnMapId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fDgnfX is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fDgnfX") != 0)
	{
		LOG_CRI << "Attribute: name is not fDgnfX!";
		return false;
	}
	const char* pszVal_fDgnfX = pElemChild->Attribute("value");
	if(pszVal_fDgnfX == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fDgnfX, s.fDgnfX))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fDgnfY is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fDgnfY") != 0)
	{
		LOG_CRI << "Attribute: name is not fDgnfY!";
		return false;
	}
	const char* pszVal_fDgnfY = pElemChild->Attribute("value");
	if(pszVal_fDgnfY == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fDgnfY, s.fDgnfY))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBagMax is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBagMax") != 0)
	{
		LOG_CRI << "Attribute: name is not wBagMax!";
		return false;
	}
	const char* pszVal_wBagMax = pElemChild->Attribute("value");
	if(pszVal_wBagMax == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBagMax, s.wBagMax))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wDepotMax is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wDepotMax") != 0)
	{
		LOG_CRI << "Attribute: name is not wDepotMax!";
		return false;
	}
	const char* pszVal_wDepotMax = pElemChild->Attribute("value");
	if(pszVal_wDepotMax == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wDepotMax, s.wDepotMax))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPendSilver is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPendSilver") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPendSilver!";
		return false;
	}
	const char* pszVal_dwPendSilver = pElemChild->Attribute("value");
	if(pszVal_dwPendSilver == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPendSilver, s.dwPendSilver))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPendCoupon is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPendCoupon") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPendCoupon!";
		return false;
	}
	const char* pszVal_dwPendCoupon = pElemChild->Attribute("value");
	if(pszVal_dwPendCoupon == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPendCoupon, s.dwPendCoupon))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPendExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPendExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPendExp!";
		return false;
	}
	const char* pszVal_dwPendExp = pElemChild->Attribute("value");
	if(pszVal_dwPendExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPendExp, s.dwPendExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPendGold is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPendGold") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPendGold!";
		return false;
	}
	const char* pszVal_dwPendGold = pElemChild->Attribute("value");
	if(pszVal_dwPendGold == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPendGold, s.dwPendGold))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDemonTowerFloorID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDemonTowerFloorID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDemonTowerFloorID!";
		return false;
	}
	const char* pszVal_dwDemonTowerFloorID = pElemChild->Attribute("value");
	if(pszVal_dwDemonTowerFloorID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDemonTowerFloorID, s.dwDemonTowerFloorID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDemonTowerPrizeFloorID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDemonTowerPrizeFloorID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDemonTowerPrizeFloorID!";
		return false;
	}
	const char* pszVal_dwDemonTowerPrizeFloorID = pElemChild->Attribute("value");
	if(pszVal_dwDemonTowerPrizeFloorID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDemonTowerPrizeFloorID, s.dwDemonTowerPrizeFloorID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuide is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuide") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuide!";
		return false;
	}
	const char* pszVal_strGuide = pElemChild->Attribute("value");
	if(pszVal_strGuide == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuide = pszVal_strGuide;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for szIcon is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "szIcon") != 0)
	{
		LOG_CRI << "Attribute: name is not szIcon!";
		return false;
	}
	const char* pszVal_szIcon = pElemChild->Attribute("value");
	if(pszVal_szIcon == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.szIcon = pszVal_szIcon;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for szIconDel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "szIconDel") != 0)
	{
		LOG_CRI << "Attribute: name is not szIconDel!";
		return false;
	}
	const char* pszVal_szIconDel = pElemChild->Attribute("value");
	if(pszVal_szIconDel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.szIconDel = pszVal_szIconDel;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for szIconActive is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "szIconActive") != 0)
	{
		LOG_CRI << "Attribute: name is not szIconActive!";
		return false;
	}
	const char* pszVal_szIconActive = pElemChild->Attribute("value");
	if(pszVal_szIconActive == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.szIconActive = pszVal_szIconActive;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPackNextUnlockTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPackNextUnlockTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPackNextUnlockTime!";
		return false;
	}
	const char* pszVal_dwPackNextUnlockTime = pElemChild->Attribute("value");
	if(pszVal_dwPackNextUnlockTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPackNextUnlockTime, s.dwPackNextUnlockTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwActivity is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwActivity") != 0)
	{
		LOG_CRI << "Attribute: name is not dwActivity!";
		return false;
	}
	const char* pszVal_dwActivity = pElemChild->Attribute("value");
	if(pszVal_dwActivity == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwActivity, s.dwActivity))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwSittingPlayer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwSittingPlayer") != 0)
	{
		LOG_CRI << "Attribute: name is not qwSittingPlayer!";
		return false;
	}
	const char* pszVal_qwSittingPlayer = pElemChild->Attribute("value");
	if(pszVal_qwSittingPlayer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwSittingPlayer, s.qwSittingPlayer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for szDgnStarAward is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "szDgnStarAward") != 0)
	{
		LOG_CRI << "Attribute: name is not szDgnStarAward!";
		return false;
	}
	const char* pszVal_szDgnStarAward = pElemChild->Attribute("value");
	if(pszVal_szDgnStarAward == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.szDgnStarAward = pszVal_szDgnStarAward;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strCreateIP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strCreateIP") != 0)
	{
		LOG_CRI << "Attribute: name is not strCreateIP!";
		return false;
	}
	const char* pszVal_strCreateIP = pElemChild->Attribute("value");
	if(pszVal_strCreateIP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strCreateIP = pszVal_strCreateIP;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strLoginIP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strLoginIP") != 0)
	{
		LOG_CRI << "Attribute: name is not strLoginIP!";
		return false;
	}
	const char* pszVal_strLoginIP = pElemChild->Attribute("value");
	if(pszVal_strLoginIP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strLoginIP = pszVal_strLoginIP;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLuckyCoupon is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLuckyCoupon") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLuckyCoupon!";
		return false;
	}
	const char* pszVal_dwLuckyCoupon = pElemChild->Attribute("value");
	if(pszVal_dwLuckyCoupon == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLuckyCoupon, s.dwLuckyCoupon))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byLevel!";
		return false;
	}
	const char* pszVal_byLevel = pElemChild->Attribute("value");
	if(pszVal_byLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLevel, s.byLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwExp") != 0)
	{
		LOG_CRI << "Attribute: name is not qwExp!";
		return false;
	}
	const char* pszVal_qwExp = pElemChild->Attribute("value");
	if(pszVal_qwExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwExp, s.qwExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byNation is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byNation") != 0)
	{
		LOG_CRI << "Attribute: name is not byNation!";
		return false;
	}
	const char* pszVal_byNation = pElemChild->Attribute("value");
	if(pszVal_byNation == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byNation, s.byNation))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byGMLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byGMLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byGMLvl!";
		return false;
	}
	const char* pszVal_byGMLvl = pElemChild->Attribute("value");
	if(pszVal_byGMLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byGMLvl, s.byGMLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTotalRecharge is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTotalRecharge") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTotalRecharge!";
		return false;
	}
	const char* pszVal_dwTotalRecharge = pElemChild->Attribute("value");
	if(pszVal_dwTotalRecharge == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTotalRecharge, s.dwTotalRecharge))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLoginTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLoginTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLoginTime!";
		return false;
	}
	const char* pszVal_dwLoginTime = pElemChild->Attribute("value");
	if(pszVal_dwLoginTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLoginTime, s.dwLoginTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOfflineTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOfflineTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOfflineTime!";
		return false;
	}
	const char* pszVal_dwOfflineTime = pElemChild->Attribute("value");
	if(pszVal_dwOfflineTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOfflineTime, s.dwOfflineTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLockExpireTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLockExpireTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLockExpireTime!";
		return false;
	}
	const char* pszVal_dwLockExpireTime = pElemChild->Attribute("value");
	if(pszVal_dwLockExpireTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLockExpireTime, s.dwLockExpireTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwForbExpireTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwForbExpireTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwForbExpireTime!";
		return false;
	}
	const char* pszVal_dwForbExpireTime = pElemChild->Attribute("value");
	if(pszVal_dwForbExpireTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwForbExpireTime, s.dwForbExpireTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGold is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGold") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGold!";
		return false;
	}
	const char* pszVal_dwGold = pElemChild->Attribute("value");
	if(pszVal_dwGold == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGold, s.dwGold))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFreeGold is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFreeGold") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFreeGold!";
		return false;
	}
	const char* pszVal_dwFreeGold = pElemChild->Attribute("value");
	if(pszVal_dwFreeGold == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFreeGold, s.dwFreeGold))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSilver is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSilver") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSilver!";
		return false;
	}
	const char* pszVal_dwSilver = pElemChild->Attribute("value");
	if(pszVal_dwSilver == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSilver, s.dwSilver))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCoupon is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCoupon") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCoupon!";
		return false;
	}
	const char* pszVal_dwCoupon = pElemChild->Attribute("value");
	if(pszVal_dwCoupon == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCoupon, s.dwCoupon))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoul is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoul") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoul!";
		return false;
	}
	const char* pszVal_dwSoul = pElemChild->Attribute("value");
	if(pszVal_dwSoul == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoul, s.dwSoul))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPrestige is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPrestige") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPrestige!";
		return false;
	}
	const char* pszVal_dwPrestige = pElemChild->Attribute("value");
	if(pszVal_dwPrestige == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPrestige, s.dwPrestige))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHonor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHonor") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHonor!";
		return false;
	}
	const char* pszVal_dwHonor = pElemChild->Attribute("value");
	if(pszVal_dwHonor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHonor, s.dwHonor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPExp!";
		return false;
	}
	const char* pszVal_dwPExp = pElemChild->Attribute("value");
	if(pszVal_dwPExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPExp, s.dwPExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAction is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAction") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAction!";
		return false;
	}
	const char* pszVal_dwAction = pElemChild->Attribute("value");
	if(pszVal_dwAction == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAction, s.dwAction))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPoten is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPoten") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPoten!";
		return false;
	}
	const char* pszVal_dwPoten = pElemChild->Attribute("value");
	if(pszVal_dwPoten == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPoten, s.dwPoten))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwReiki is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwReiki") != 0)
	{
		LOG_CRI << "Attribute: name is not dwReiki!";
		return false;
	}
	const char* pszVal_dwReiki = pElemChild->Attribute("value");
	if(pszVal_dwReiki == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwReiki, s.dwReiki))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDemonSoul is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDemonSoul") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDemonSoul!";
		return false;
	}
	const char* pszVal_dwDemonSoul = pElemChild->Attribute("value");
	if(pszVal_dwDemonSoul == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDemonSoul, s.dwDemonSoul))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulAttack is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulAttack") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulAttack!";
		return false;
	}
	const char* pszVal_dwSoulAttack = pElemChild->Attribute("value");
	if(pszVal_dwSoulAttack == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulAttack, s.dwSoulAttack))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulHp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulHp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulHp!";
		return false;
	}
	const char* pszVal_dwSoulHp = pElemChild->Attribute("value");
	if(pszVal_dwSoulHp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulHp, s.dwSoulHp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulCritical is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulCritical") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulCritical!";
		return false;
	}
	const char* pszVal_dwSoulCritical = pElemChild->Attribute("value");
	if(pszVal_dwSoulCritical == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulCritical, s.dwSoulCritical))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulCounter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulCounter") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulCounter!";
		return false;
	}
	const char* pszVal_dwSoulCounter = pElemChild->Attribute("value");
	if(pszVal_dwSoulCounter == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulCounter, s.dwSoulCounter))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulSpeed is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulSpeed") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulSpeed!";
		return false;
	}
	const char* pszVal_dwSoulSpeed = pElemChild->Attribute("value");
	if(pszVal_dwSoulSpeed == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulSpeed, s.dwSoulSpeed))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulDefence is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulDefence") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulDefence!";
		return false;
	}
	const char* pszVal_dwSoulDefence = pElemChild->Attribute("value");
	if(pszVal_dwSoulDefence == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulDefence, s.dwSoulDefence))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulHit is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulHit") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulHit!";
		return false;
	}
	const char* pszVal_dwSoulHit = pElemChild->Attribute("value");
	if(pszVal_dwSoulHit == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulHit, s.dwSoulHit))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulDodge is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulDodge") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulDodge!";
		return false;
	}
	const char* pszVal_dwSoulDodge = pElemChild->Attribute("value");
	if(pszVal_dwSoulDodge == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulDodge, s.dwSoulDodge))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampHuang is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampHuang") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampHuang!";
		return false;
	}
	const char* pszVal_dwStampHuang = pElemChild->Attribute("value");
	if(pszVal_dwStampHuang == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampHuang, s.dwStampHuang))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampXuan is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampXuan") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampXuan!";
		return false;
	}
	const char* pszVal_dwStampXuan = pElemChild->Attribute("value");
	if(pszVal_dwStampXuan == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampXuan, s.dwStampXuan))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampDi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampDi") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampDi!";
		return false;
	}
	const char* pszVal_dwStampDi = pElemChild->Attribute("value");
	if(pszVal_dwStampDi == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampDi, s.dwStampDi))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampTian is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampTian") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampTian!";
		return false;
	}
	const char* pszVal_dwStampTian = pElemChild->Attribute("value");
	if(pszVal_dwStampTian == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampTian, s.dwStampTian))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampXing is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampXing") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampXing!";
		return false;
	}
	const char* pszVal_dwStampXing = pElemChild->Attribute("value");
	if(pszVal_dwStampXing == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampXing, s.dwStampXing))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampYue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampYue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampYue!";
		return false;
	}
	const char* pszVal_dwStampYue = pElemChild->Attribute("value");
	if(pszVal_dwStampYue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampYue, s.dwStampYue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampDi2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampDi2") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampDi2!";
		return false;
	}
	const char* pszVal_dwStampDi2 = pElemChild->Attribute("value");
	if(pszVal_dwStampDi2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampDi2, s.dwStampDi2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampXian is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampXian") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampXian!";
		return false;
	}
	const char* pszVal_dwStampXian = pElemChild->Attribute("value");
	if(pszVal_dwStampXian == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampXian, s.dwStampXian))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampSheng is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampSheng") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampSheng!";
		return false;
	}
	const char* pszVal_dwStampSheng = pElemChild->Attribute("value");
	if(pszVal_dwStampSheng == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampSheng, s.dwStampSheng))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampFo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampFo") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampFo!";
		return false;
	}
	const char* pszVal_dwStampFo = pElemChild->Attribute("value");
	if(pszVal_dwStampFo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampFo, s.dwStampFo))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLoveHeart is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLoveHeart") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLoveHeart!";
		return false;
	}
	const char* pszVal_dwLoveHeart = pElemChild->Attribute("value");
	if(pszVal_dwLoveHeart == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLoveHeart, s.dwLoveHeart))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBlueFairyFate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBlueFairyFate") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBlueFairyFate!";
		return false;
	}
	const char* pszVal_dwBlueFairyFate = pElemChild->Attribute("value");
	if(pszVal_dwBlueFairyFate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBlueFairyFate, s.dwBlueFairyFate))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPurpleFairyFate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPurpleFairyFate") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPurpleFairyFate!";
		return false;
	}
	const char* pszVal_dwPurpleFairyFate = pElemChild->Attribute("value");
	if(pszVal_dwPurpleFairyFate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPurpleFairyFate, s.dwPurpleFairyFate))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOrangeFairyFate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOrangeFairyFate") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOrangeFairyFate!";
		return false;
	}
	const char* pszVal_dwOrangeFairyFate = pElemChild->Attribute("value");
	if(pszVal_dwOrangeFairyFate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOrangeFairyFate, s.dwOrangeFairyFate))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDuJieFu is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDuJieFu") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDuJieFu!";
		return false;
	}
	const char* pszVal_dwDuJieFu = pElemChild->Attribute("value");
	if(pszVal_dwDuJieFu == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDuJieFu, s.dwDuJieFu))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBTPoint is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBTPoint") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBTPoint!";
		return false;
	}
	const char* pszVal_dwBTPoint = pElemChild->Attribute("value");
	if(pszVal_dwBTPoint == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBTPoint, s.dwBTPoint))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for szOwnTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "szOwnTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not szOwnTitle!";
		return false;
	}
	const char* pszVal_szOwnTitle = pElemChild->Attribute("value");
	if(pszVal_szOwnTitle == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.szOwnTitle = pszVal_szOwnTitle;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for szEquipTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "szEquipTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not szEquipTitle!";
		return false;
	}
	const char* pszVal_szEquipTitle = pElemChild->Attribute("value");
	if(pszVal_szEquipTitle == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.szEquipTitle = pszVal_szEquipTitle;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDomain is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDomain") != 0)
	{
		LOG_CRI << "Attribute: name is not byDomain!";
		return false;
	}
	const char* pszVal_byDomain = pElemChild->Attribute("value");
	if(pszVal_byDomain == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDomain, s.byDomain))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDomainLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDomainLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byDomainLvl!";
		return false;
	}
	const char* pszVal_byDomainLvl = pElemChild->Attribute("value");
	if(pszVal_byDomainLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDomainLvl, s.byDomainLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDisplayLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDisplayLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byDisplayLvl!";
		return false;
	}
	const char* pszVal_byDisplayLvl = pElemChild->Attribute("value");
	if(pszVal_byDisplayLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDisplayLvl, s.byDisplayLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDomainYear is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDomainYear") != 0)
	{
		LOG_CRI << "Attribute: name is not byDomainYear!";
		return false;
	}
	const char* pszVal_byDomainYear = pElemChild->Attribute("value");
	if(pszVal_byDomainYear == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDomainYear, s.byDomainYear))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for szOpenId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "szOpenId") != 0)
	{
		LOG_CRI << "Attribute: name is not szOpenId!";
		return false;
	}
	const char* pszVal_szOpenId = pElemChild->Attribute("value");
	if(pszVal_szOpenId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.szOpenId = pszVal_szOpenId;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for szOpenKey is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "szOpenKey") != 0)
	{
		LOG_CRI << "Attribute: name is not szOpenKey!";
		return false;
	}
	const char* pszVal_szOpenKey = pElemChild->Attribute("value");
	if(pszVal_szOpenKey == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.szOpenKey = pszVal_szOpenKey;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSign is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSign") != 0)
	{
		LOG_CRI << "Attribute: name is not strSign!";
		return false;
	}
	const char* pszVal_strSign = pElemChild->Attribute("value");
	if(pszVal_strSign == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSign = pszVal_strSign;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMood is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMood") != 0)
	{
		LOG_CRI << "Attribute: name is not wMood!";
		return false;
	}
	const char* pszVal_wMood = pElemChild->Attribute("value");
	if(pszVal_wMood == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMood, s.wMood))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wAchievementLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wAchievementLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not wAchievementLevel!";
		return false;
	}
	const char* pszVal_wAchievementLevel = pElemChild->Attribute("value");
	if(pszVal_wAchievementLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wAchievementLevel, s.wAchievementLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAchievementAP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAchievementAP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAchievementAP!";
		return false;
	}
	const char* pszVal_dwAchievementAP = pElemChild->Attribute("value");
	if(pszVal_dwAchievementAP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAchievementAP, s.dwAchievementAP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCollectLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCollectLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not wCollectLevel!";
		return false;
	}
	const char* pszVal_wCollectLevel = pElemChild->Attribute("value");
	if(pszVal_wCollectLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCollectLevel, s.wCollectLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCollectAP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCollectAP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCollectAP!";
		return false;
	}
	const char* pszVal_dwCollectAP = pElemChild->Attribute("value");
	if(pszVal_dwCollectAP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCollectAP, s.dwCollectAP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInvitedID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInvitedID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInvitedID!";
		return false;
	}
	const char* pszVal_qwInvitedID = pElemChild->Attribute("value");
	if(pszVal_qwInvitedID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInvitedID, s.qwInvitedID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byWallow is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byWallow") != 0)
	{
		LOG_CRI << "Attribute: name is not byWallow!";
		return false;
	}
	const char* pszVal_byWallow = pElemChild->Attribute("value");
	if(pszVal_byWallow == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byWallow, s.byWallow))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwIndulgeKickTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwIndulgeKickTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwIndulgeKickTime!";
		return false;
	}
	const char* pszVal_dwIndulgeKickTime = pElemChild->Attribute("value");
	if(pszVal_dwIndulgeKickTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwIndulgeKickTime, s.dwIndulgeKickTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byYDLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byYDLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byYDLevel!";
		return false;
	}
	const char* pszVal_byYDLevel = pElemChild->Attribute("value");
	if(pszVal_byYDLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byYDLevel, s.byYDLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCreateTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCreateTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCreateTime!";
		return false;
	}
	const char* pszVal_dwCreateTime = pElemChild->Attribute("value");
	if(pszVal_dwCreateTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCreateTime, s.dwCreateTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wLastSaveMapID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wLastSaveMapID") != 0)
	{
		LOG_CRI << "Attribute: name is not wLastSaveMapID!";
		return false;
	}
	const char* pszVal_wLastSaveMapID = pElemChild->Attribute("value");
	if(pszVal_wLastSaveMapID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wLastSaveMapID, s.wLastSaveMapID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fLastSaveX is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fLastSaveX") != 0)
	{
		LOG_CRI << "Attribute: name is not fLastSaveX!";
		return false;
	}
	const char* pszVal_fLastSaveX = pElemChild->Attribute("value");
	if(pszVal_fLastSaveX == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fLastSaveX, s.fLastSaveX))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fLastSaveY is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fLastSaveY") != 0)
	{
		LOG_CRI << "Attribute: name is not fLastSaveY!";
		return false;
	}
	const char* pszVal_fLastSaveY = pElemChild->Attribute("value");
	if(pszVal_fLastSaveY == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fLastSaveY, s.fLastSaveY))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const RoleBaseInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("RoleBaseInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("EDataType:eRoleBaseInfo"));
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("玩家名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_eCareer(new TiXmlElement("ProtoCommon::ECareerType"));
	if(pElem_eCareer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eCareer->SetAttribute("name", "eCareer");
	const char* pszEnum_eCareer = NProtoCommon::EnumValToStr(s.eCareer);
	if(pszEnum_eCareer == NULL)
	{
		LOG_CRI << "EnumValToStr for eCareer fails!";
		return false;
	}
	pElem_eCareer->SetAttribute("value", pszEnum_eCareer);
	pElem_eCareer->SetAttribute("comment", ToUTF8Ptr("职业"));
	if(rElement.LinkEndChild(pElem_eCareer.get()) != NULL)
		pElem_eCareer.release();
	unique_ptr<TiXmlElement> pElem_eSex(new TiXmlElement("ProtoCommon::ESexType"));
	if(pElem_eSex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSex->SetAttribute("name", "eSex");
	const char* pszEnum_eSex = NProtoCommon::EnumValToStr(s.eSex);
	if(pszEnum_eSex == NULL)
	{
		LOG_CRI << "EnumValToStr for eSex fails!";
		return false;
	}
	pElem_eSex->SetAttribute("value", pszEnum_eSex);
	pElem_eSex->SetAttribute("comment", ToUTF8Ptr("性别"));
	if(rElement.LinkEndChild(pElem_eSex.get()) != NULL)
		pElem_eSex.release();
	unique_ptr<TiXmlElement> pElem_wMapID(new TiXmlElement("UINT16"));
	if(pElem_wMapID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMapID->SetAttribute("name", "wMapID");
	pElem_wMapID->SetAttribute("value", NumberToString(s.wMapID).c_str());
	pElem_wMapID->SetAttribute("comment", ToUTF8Ptr("地图ID"));
	if(rElement.LinkEndChild(pElem_wMapID.get()) != NULL)
		pElem_wMapID.release();
	unique_ptr<TiXmlElement> pElem_fX(new TiXmlElement("float"));
	if(pElem_fX == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fX->SetAttribute("name", "fX");
	pElem_fX->SetAttribute("value", NumberToString(s.fX).c_str());
	pElem_fX->SetAttribute("comment", ToUTF8Ptr("X坐标"));
	if(rElement.LinkEndChild(pElem_fX.get()) != NULL)
		pElem_fX.release();
	unique_ptr<TiXmlElement> pElem_fY(new TiXmlElement("float"));
	if(pElem_fY == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fY->SetAttribute("name", "fY");
	pElem_fY->SetAttribute("value", NumberToString(s.fY).c_str());
	pElem_fY->SetAttribute("comment", ToUTF8Ptr("Y坐标"));
	if(rElement.LinkEndChild(pElem_fY.get()) != NULL)
		pElem_fY.release();
	unique_ptr<TiXmlElement> pElem_qwDgnId(new TiXmlElement("UINT64"));
	if(pElem_qwDgnId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwDgnId->SetAttribute("name", "qwDgnId");
	pElem_qwDgnId->SetAttribute("value", NumberToString(s.qwDgnId).c_str());
	pElem_qwDgnId->SetAttribute("comment", ToUTF8Ptr("副本实例ID"));
	if(rElement.LinkEndChild(pElem_qwDgnId.get()) != NULL)
		pElem_qwDgnId.release();
	unique_ptr<TiXmlElement> pElem_dwDgnTypeID(new TiXmlElement("UINT16"));
	if(pElem_dwDgnTypeID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDgnTypeID->SetAttribute("name", "dwDgnTypeID");
	pElem_dwDgnTypeID->SetAttribute("value", NumberToString(s.dwDgnTypeID).c_str());
	pElem_dwDgnTypeID->SetAttribute("comment", ToUTF8Ptr("副本模版ID"));
	if(rElement.LinkEndChild(pElem_dwDgnTypeID.get()) != NULL)
		pElem_dwDgnTypeID.release();
	unique_ptr<TiXmlElement> pElem_wDgnMapId(new TiXmlElement("UINT16"));
	if(pElem_wDgnMapId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wDgnMapId->SetAttribute("name", "wDgnMapId");
	pElem_wDgnMapId->SetAttribute("value", NumberToString(s.wDgnMapId).c_str());
	pElem_wDgnMapId->SetAttribute("comment", ToUTF8Ptr("副本地图ID"));
	if(rElement.LinkEndChild(pElem_wDgnMapId.get()) != NULL)
		pElem_wDgnMapId.release();
	unique_ptr<TiXmlElement> pElem_fDgnfX(new TiXmlElement("float"));
	if(pElem_fDgnfX == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fDgnfX->SetAttribute("name", "fDgnfX");
	pElem_fDgnfX->SetAttribute("value", NumberToString(s.fDgnfX).c_str());
	pElem_fDgnfX->SetAttribute("comment", ToUTF8Ptr("副本X坐标"));
	if(rElement.LinkEndChild(pElem_fDgnfX.get()) != NULL)
		pElem_fDgnfX.release();
	unique_ptr<TiXmlElement> pElem_fDgnfY(new TiXmlElement("float"));
	if(pElem_fDgnfY == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fDgnfY->SetAttribute("name", "fDgnfY");
	pElem_fDgnfY->SetAttribute("value", NumberToString(s.fDgnfY).c_str());
	pElem_fDgnfY->SetAttribute("comment", ToUTF8Ptr("副本Y坐标"));
	if(rElement.LinkEndChild(pElem_fDgnfY.get()) != NULL)
		pElem_fDgnfY.release();
	unique_ptr<TiXmlElement> pElem_wBagMax(new TiXmlElement("UINT16"));
	if(pElem_wBagMax == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBagMax->SetAttribute("name", "wBagMax");
	pElem_wBagMax->SetAttribute("value", NumberToString(s.wBagMax).c_str());
	pElem_wBagMax->SetAttribute("comment", ToUTF8Ptr("背包容量"));
	if(rElement.LinkEndChild(pElem_wBagMax.get()) != NULL)
		pElem_wBagMax.release();
	unique_ptr<TiXmlElement> pElem_wDepotMax(new TiXmlElement("UINT16"));
	if(pElem_wDepotMax == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wDepotMax->SetAttribute("name", "wDepotMax");
	pElem_wDepotMax->SetAttribute("value", NumberToString(s.wDepotMax).c_str());
	pElem_wDepotMax->SetAttribute("comment", ToUTF8Ptr("仓库容量"));
	if(rElement.LinkEndChild(pElem_wDepotMax.get()) != NULL)
		pElem_wDepotMax.release();
	unique_ptr<TiXmlElement> pElem_dwPendSilver(new TiXmlElement("UINT32"));
	if(pElem_dwPendSilver == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPendSilver->SetAttribute("name", "dwPendSilver");
	pElem_dwPendSilver->SetAttribute("value", NumberToString(s.dwPendSilver).c_str());
	pElem_dwPendSilver->SetAttribute("comment", ToUTF8Ptr("延迟发放的银币"));
	if(rElement.LinkEndChild(pElem_dwPendSilver.get()) != NULL)
		pElem_dwPendSilver.release();
	unique_ptr<TiXmlElement> pElem_dwPendCoupon(new TiXmlElement("UINT32"));
	if(pElem_dwPendCoupon == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPendCoupon->SetAttribute("name", "dwPendCoupon");
	pElem_dwPendCoupon->SetAttribute("value", NumberToString(s.dwPendCoupon).c_str());
	pElem_dwPendCoupon->SetAttribute("comment", ToUTF8Ptr("延迟发放的礼券"));
	if(rElement.LinkEndChild(pElem_dwPendCoupon.get()) != NULL)
		pElem_dwPendCoupon.release();
	unique_ptr<TiXmlElement> pElem_dwPendExp(new TiXmlElement("UINT32"));
	if(pElem_dwPendExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPendExp->SetAttribute("name", "dwPendExp");
	pElem_dwPendExp->SetAttribute("value", NumberToString(s.dwPendExp).c_str());
	pElem_dwPendExp->SetAttribute("comment", ToUTF8Ptr("延迟发放的经验"));
	if(rElement.LinkEndChild(pElem_dwPendExp.get()) != NULL)
		pElem_dwPendExp.release();
	unique_ptr<TiXmlElement> pElem_dwPendGold(new TiXmlElement("UINT32"));
	if(pElem_dwPendGold == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPendGold->SetAttribute("name", "dwPendGold");
	pElem_dwPendGold->SetAttribute("value", NumberToString(s.dwPendGold).c_str());
	pElem_dwPendGold->SetAttribute("comment", ToUTF8Ptr("延迟发放的仙石"));
	if(rElement.LinkEndChild(pElem_dwPendGold.get()) != NULL)
		pElem_dwPendGold.release();
	unique_ptr<TiXmlElement> pElem_dwDemonTowerFloorID(new TiXmlElement("UINT32"));
	if(pElem_dwDemonTowerFloorID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDemonTowerFloorID->SetAttribute("name", "dwDemonTowerFloorID");
	pElem_dwDemonTowerFloorID->SetAttribute("value", NumberToString(s.dwDemonTowerFloorID).c_str());
	pElem_dwDemonTowerFloorID->SetAttribute("comment", ToUTF8Ptr("通关镇妖塔层数"));
	if(rElement.LinkEndChild(pElem_dwDemonTowerFloorID.get()) != NULL)
		pElem_dwDemonTowerFloorID.release();
	unique_ptr<TiXmlElement> pElem_dwDemonTowerPrizeFloorID(new TiXmlElement("UINT32"));
	if(pElem_dwDemonTowerPrizeFloorID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDemonTowerPrizeFloorID->SetAttribute("name", "dwDemonTowerPrizeFloorID");
	pElem_dwDemonTowerPrizeFloorID->SetAttribute("value", NumberToString(s.dwDemonTowerPrizeFloorID).c_str());
	pElem_dwDemonTowerPrizeFloorID->SetAttribute("comment", ToUTF8Ptr("镇妖塔层数"));
	if(rElement.LinkEndChild(pElem_dwDemonTowerPrizeFloorID.get()) != NULL)
		pElem_dwDemonTowerPrizeFloorID.release();
	unique_ptr<TiXmlElement> pElem_strGuide(new TiXmlElement("string"));
	if(pElem_strGuide == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuide->SetAttribute("name", "strGuide");
	pElem_strGuide->SetAttribute("value", s.strGuide.c_str());
	pElem_strGuide->SetAttribute("comment", ToUTF8Ptr("新手引导内容"));
	if(rElement.LinkEndChild(pElem_strGuide.get()) != NULL)
		pElem_strGuide.release();
	unique_ptr<TiXmlElement> pElem_szIcon(new TiXmlElement("string"));
	if(pElem_szIcon == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_szIcon->SetAttribute("name", "szIcon");
	pElem_szIcon->SetAttribute("value", s.szIcon.c_str());
	pElem_szIcon->SetAttribute("comment", ToUTF8Ptr("功能开放标签"));
	if(rElement.LinkEndChild(pElem_szIcon.get()) != NULL)
		pElem_szIcon.release();
	unique_ptr<TiXmlElement> pElem_szIconDel(new TiXmlElement("string"));
	if(pElem_szIconDel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_szIconDel->SetAttribute("name", "szIconDel");
	pElem_szIconDel->SetAttribute("value", s.szIconDel.c_str());
	pElem_szIconDel->SetAttribute("comment", ToUTF8Ptr("功能关闭标签"));
	if(rElement.LinkEndChild(pElem_szIconDel.get()) != NULL)
		pElem_szIconDel.release();
	unique_ptr<TiXmlElement> pElem_szIconActive(new TiXmlElement("string"));
	if(pElem_szIconActive == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_szIconActive->SetAttribute("name", "szIconActive");
	pElem_szIconActive->SetAttribute("value", s.szIconActive.c_str());
	pElem_szIconActive->SetAttribute("comment", ToUTF8Ptr("功能关闭标签"));
	if(rElement.LinkEndChild(pElem_szIconActive.get()) != NULL)
		pElem_szIconActive.release();
	unique_ptr<TiXmlElement> pElem_dwPackNextUnlockTime(new TiXmlElement("UINT32"));
	if(pElem_dwPackNextUnlockTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPackNextUnlockTime->SetAttribute("name", "dwPackNextUnlockTime");
	pElem_dwPackNextUnlockTime->SetAttribute("value", NumberToString(s.dwPackNextUnlockTime).c_str());
	pElem_dwPackNextUnlockTime->SetAttribute("comment", ToUTF8Ptr("背包下次解锁时间"));
	if(rElement.LinkEndChild(pElem_dwPackNextUnlockTime.get()) != NULL)
		pElem_dwPackNextUnlockTime.release();
	unique_ptr<TiXmlElement> pElem_dwActivity(new TiXmlElement("UINT32"));
	if(pElem_dwActivity == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwActivity->SetAttribute("name", "dwActivity");
	pElem_dwActivity->SetAttribute("value", NumberToString(s.dwActivity).c_str());
	pElem_dwActivity->SetAttribute("comment", ToUTF8Ptr("活跃值"));
	if(rElement.LinkEndChild(pElem_dwActivity.get()) != NULL)
		pElem_dwActivity.release();
	unique_ptr<TiXmlElement> pElem_qwSittingPlayer(new TiXmlElement("UINT64"));
	if(pElem_qwSittingPlayer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwSittingPlayer->SetAttribute("name", "qwSittingPlayer");
	pElem_qwSittingPlayer->SetAttribute("value", NumberToString(s.qwSittingPlayer).c_str());
	pElem_qwSittingPlayer->SetAttribute("comment", ToUTF8Ptr("一起双修的人"));
	if(rElement.LinkEndChild(pElem_qwSittingPlayer.get()) != NULL)
		pElem_qwSittingPlayer.release();
	unique_ptr<TiXmlElement> pElem_szDgnStarAward(new TiXmlElement("string"));
	if(pElem_szDgnStarAward == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_szDgnStarAward->SetAttribute("name", "szDgnStarAward");
	pElem_szDgnStarAward->SetAttribute("value", s.szDgnStarAward.c_str());
	pElem_szDgnStarAward->SetAttribute("comment", ToUTF8Ptr("副本星级领奖"));
	if(rElement.LinkEndChild(pElem_szDgnStarAward.get()) != NULL)
		pElem_szDgnStarAward.release();
	unique_ptr<TiXmlElement> pElem_strCreateIP(new TiXmlElement("string"));
	if(pElem_strCreateIP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strCreateIP->SetAttribute("name", "strCreateIP");
	pElem_strCreateIP->SetAttribute("value", s.strCreateIP.c_str());
	pElem_strCreateIP->SetAttribute("comment", ToUTF8Ptr("玩家创角时IP"));
	if(rElement.LinkEndChild(pElem_strCreateIP.get()) != NULL)
		pElem_strCreateIP.release();
	unique_ptr<TiXmlElement> pElem_strLoginIP(new TiXmlElement("string"));
	if(pElem_strLoginIP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strLoginIP->SetAttribute("name", "strLoginIP");
	pElem_strLoginIP->SetAttribute("value", s.strLoginIP.c_str());
	pElem_strLoginIP->SetAttribute("comment", ToUTF8Ptr("玩家登录时IP"));
	if(rElement.LinkEndChild(pElem_strLoginIP.get()) != NULL)
		pElem_strLoginIP.release();
	unique_ptr<TiXmlElement> pElem_dwLuckyCoupon(new TiXmlElement("UINT32"));
	if(pElem_dwLuckyCoupon == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLuckyCoupon->SetAttribute("name", "dwLuckyCoupon");
	pElem_dwLuckyCoupon->SetAttribute("value", NumberToString(s.dwLuckyCoupon).c_str());
	pElem_dwLuckyCoupon->SetAttribute("comment", ToUTF8Ptr("幸运券"));
	if(rElement.LinkEndChild(pElem_dwLuckyCoupon.get()) != NULL)
		pElem_dwLuckyCoupon.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("玩家等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_qwExp(new TiXmlElement("UINT64"));
	if(pElem_qwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwExp->SetAttribute("name", "qwExp");
	pElem_qwExp->SetAttribute("value", NumberToString(s.qwExp).c_str());
	pElem_qwExp->SetAttribute("comment", ToUTF8Ptr("玩家经验值"));
	if(rElement.LinkEndChild(pElem_qwExp.get()) != NULL)
		pElem_qwExp.release();
	unique_ptr<TiXmlElement> pElem_byNation(new TiXmlElement("UINT8"));
	if(pElem_byNation == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byNation->SetAttribute("name", "byNation");
	pElem_byNation->SetAttribute("value", NumberToString(s.byNation).c_str());
	pElem_byNation->SetAttribute("comment", ToUTF8Ptr("国家"));
	if(rElement.LinkEndChild(pElem_byNation.get()) != NULL)
		pElem_byNation.release();
	unique_ptr<TiXmlElement> pElem_byGMLvl(new TiXmlElement("UINT8"));
	if(pElem_byGMLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGMLvl->SetAttribute("name", "byGMLvl");
	pElem_byGMLvl->SetAttribute("value", NumberToString(s.byGMLvl).c_str());
	pElem_byGMLvl->SetAttribute("comment", ToUTF8Ptr("GM权限"));
	if(rElement.LinkEndChild(pElem_byGMLvl.get()) != NULL)
		pElem_byGMLvl.release();
	unique_ptr<TiXmlElement> pElem_dwTotalRecharge(new TiXmlElement("UINT32"));
	if(pElem_dwTotalRecharge == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTotalRecharge->SetAttribute("name", "dwTotalRecharge");
	pElem_dwTotalRecharge->SetAttribute("value", NumberToString(s.dwTotalRecharge).c_str());
	pElem_dwTotalRecharge->SetAttribute("comment", ToUTF8Ptr("充值金额"));
	if(rElement.LinkEndChild(pElem_dwTotalRecharge.get()) != NULL)
		pElem_dwTotalRecharge.release();
	unique_ptr<TiXmlElement> pElem_dwLoginTime(new TiXmlElement("UINT32"));
	if(pElem_dwLoginTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLoginTime->SetAttribute("name", "dwLoginTime");
	pElem_dwLoginTime->SetAttribute("value", NumberToString(s.dwLoginTime).c_str());
	pElem_dwLoginTime->SetAttribute("comment", ToUTF8Ptr("上次登陆时间"));
	if(rElement.LinkEndChild(pElem_dwLoginTime.get()) != NULL)
		pElem_dwLoginTime.release();
	unique_ptr<TiXmlElement> pElem_dwOfflineTime(new TiXmlElement("UINT32"));
	if(pElem_dwOfflineTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOfflineTime->SetAttribute("name", "dwOfflineTime");
	pElem_dwOfflineTime->SetAttribute("value", NumberToString(s.dwOfflineTime).c_str());
	pElem_dwOfflineTime->SetAttribute("comment", ToUTF8Ptr("上次下线时间"));
	if(rElement.LinkEndChild(pElem_dwOfflineTime.get()) != NULL)
		pElem_dwOfflineTime.release();
	unique_ptr<TiXmlElement> pElem_dwLockExpireTime(new TiXmlElement("UINT32"));
	if(pElem_dwLockExpireTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLockExpireTime->SetAttribute("name", "dwLockExpireTime");
	pElem_dwLockExpireTime->SetAttribute("value", NumberToString(s.dwLockExpireTime).c_str());
	pElem_dwLockExpireTime->SetAttribute("comment", ToUTF8Ptr("被封禁结束时间"));
	if(rElement.LinkEndChild(pElem_dwLockExpireTime.get()) != NULL)
		pElem_dwLockExpireTime.release();
	unique_ptr<TiXmlElement> pElem_dwForbExpireTime(new TiXmlElement("UINT32"));
	if(pElem_dwForbExpireTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwForbExpireTime->SetAttribute("name", "dwForbExpireTime");
	pElem_dwForbExpireTime->SetAttribute("value", NumberToString(s.dwForbExpireTime).c_str());
	pElem_dwForbExpireTime->SetAttribute("comment", ToUTF8Ptr("被禁言结束时间"));
	if(rElement.LinkEndChild(pElem_dwForbExpireTime.get()) != NULL)
		pElem_dwForbExpireTime.release();
	unique_ptr<TiXmlElement> pElem_dwGold(new TiXmlElement("UINT32"));
	if(pElem_dwGold == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGold->SetAttribute("name", "dwGold");
	pElem_dwGold->SetAttribute("value", NumberToString(s.dwGold).c_str());
	pElem_dwGold->SetAttribute("comment", ToUTF8Ptr("充值仙石"));
	if(rElement.LinkEndChild(pElem_dwGold.get()) != NULL)
		pElem_dwGold.release();
	unique_ptr<TiXmlElement> pElem_dwFreeGold(new TiXmlElement("UINT32"));
	if(pElem_dwFreeGold == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFreeGold->SetAttribute("name", "dwFreeGold");
	pElem_dwFreeGold->SetAttribute("value", NumberToString(s.dwFreeGold).c_str());
	pElem_dwFreeGold->SetAttribute("comment", ToUTF8Ptr("免费仙石"));
	if(rElement.LinkEndChild(pElem_dwFreeGold.get()) != NULL)
		pElem_dwFreeGold.release();
	unique_ptr<TiXmlElement> pElem_dwSilver(new TiXmlElement("UINT32"));
	if(pElem_dwSilver == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSilver->SetAttribute("name", "dwSilver");
	pElem_dwSilver->SetAttribute("value", NumberToString(s.dwSilver).c_str());
	pElem_dwSilver->SetAttribute("comment", ToUTF8Ptr("银币"));
	if(rElement.LinkEndChild(pElem_dwSilver.get()) != NULL)
		pElem_dwSilver.release();
	unique_ptr<TiXmlElement> pElem_dwCoupon(new TiXmlElement("UINT32"));
	if(pElem_dwCoupon == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCoupon->SetAttribute("name", "dwCoupon");
	pElem_dwCoupon->SetAttribute("value", NumberToString(s.dwCoupon).c_str());
	pElem_dwCoupon->SetAttribute("comment", ToUTF8Ptr("礼券"));
	if(rElement.LinkEndChild(pElem_dwCoupon.get()) != NULL)
		pElem_dwCoupon.release();
	unique_ptr<TiXmlElement> pElem_dwSoul(new TiXmlElement("UINT32"));
	if(pElem_dwSoul == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoul->SetAttribute("name", "dwSoul");
	pElem_dwSoul->SetAttribute("value", NumberToString(s.dwSoul).c_str());
	pElem_dwSoul->SetAttribute("comment", ToUTF8Ptr("魂魄"));
	if(rElement.LinkEndChild(pElem_dwSoul.get()) != NULL)
		pElem_dwSoul.release();
	unique_ptr<TiXmlElement> pElem_dwPrestige(new TiXmlElement("UINT32"));
	if(pElem_dwPrestige == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPrestige->SetAttribute("name", "dwPrestige");
	pElem_dwPrestige->SetAttribute("value", NumberToString(s.dwPrestige).c_str());
	pElem_dwPrestige->SetAttribute("comment", ToUTF8Ptr("声望"));
	if(rElement.LinkEndChild(pElem_dwPrestige.get()) != NULL)
		pElem_dwPrestige.release();
	unique_ptr<TiXmlElement> pElem_dwHonor(new TiXmlElement("UINT32"));
	if(pElem_dwHonor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHonor->SetAttribute("name", "dwHonor");
	pElem_dwHonor->SetAttribute("value", NumberToString(s.dwHonor).c_str());
	pElem_dwHonor->SetAttribute("comment", ToUTF8Ptr("荣誉"));
	if(rElement.LinkEndChild(pElem_dwHonor.get()) != NULL)
		pElem_dwHonor.release();
	unique_ptr<TiXmlElement> pElem_dwPExp(new TiXmlElement("UINT32"));
	if(pElem_dwPExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPExp->SetAttribute("name", "dwPExp");
	pElem_dwPExp->SetAttribute("value", NumberToString(s.dwPExp).c_str());
	pElem_dwPExp->SetAttribute("comment", ToUTF8Ptr("修为"));
	if(rElement.LinkEndChild(pElem_dwPExp.get()) != NULL)
		pElem_dwPExp.release();
	unique_ptr<TiXmlElement> pElem_dwAction(new TiXmlElement("UINT32"));
	if(pElem_dwAction == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAction->SetAttribute("name", "dwAction");
	pElem_dwAction->SetAttribute("value", NumberToString(s.dwAction).c_str());
	pElem_dwAction->SetAttribute("comment", ToUTF8Ptr("体力"));
	if(rElement.LinkEndChild(pElem_dwAction.get()) != NULL)
		pElem_dwAction.release();
	unique_ptr<TiXmlElement> pElem_dwPoten(new TiXmlElement("UINT32"));
	if(pElem_dwPoten == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPoten->SetAttribute("name", "dwPoten");
	pElem_dwPoten->SetAttribute("value", NumberToString(s.dwPoten).c_str());
	pElem_dwPoten->SetAttribute("comment", ToUTF8Ptr("渡劫点数"));
	if(rElement.LinkEndChild(pElem_dwPoten.get()) != NULL)
		pElem_dwPoten.release();
	unique_ptr<TiXmlElement> pElem_dwReiki(new TiXmlElement("UINT32"));
	if(pElem_dwReiki == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwReiki->SetAttribute("name", "dwReiki");
	pElem_dwReiki->SetAttribute("value", NumberToString(s.dwReiki).c_str());
	pElem_dwReiki->SetAttribute("comment", ToUTF8Ptr("副本星级"));
	if(rElement.LinkEndChild(pElem_dwReiki.get()) != NULL)
		pElem_dwReiki.release();
	unique_ptr<TiXmlElement> pElem_dwDemonSoul(new TiXmlElement("UINT32"));
	if(pElem_dwDemonSoul == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDemonSoul->SetAttribute("name", "dwDemonSoul");
	pElem_dwDemonSoul->SetAttribute("value", NumberToString(s.dwDemonSoul).c_str());
	pElem_dwDemonSoul->SetAttribute("comment", ToUTF8Ptr("锁妖塔魂值"));
	if(rElement.LinkEndChild(pElem_dwDemonSoul.get()) != NULL)
		pElem_dwDemonSoul.release();
	unique_ptr<TiXmlElement> pElem_dwSoulAttack(new TiXmlElement("UINT32"));
	if(pElem_dwSoulAttack == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulAttack->SetAttribute("name", "dwSoulAttack");
	pElem_dwSoulAttack->SetAttribute("value", NumberToString(s.dwSoulAttack).c_str());
	pElem_dwSoulAttack->SetAttribute("comment", ToUTF8Ptr("攻击之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulAttack.get()) != NULL)
		pElem_dwSoulAttack.release();
	unique_ptr<TiXmlElement> pElem_dwSoulHp(new TiXmlElement("UINT32"));
	if(pElem_dwSoulHp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulHp->SetAttribute("name", "dwSoulHp");
	pElem_dwSoulHp->SetAttribute("value", NumberToString(s.dwSoulHp).c_str());
	pElem_dwSoulHp->SetAttribute("comment", ToUTF8Ptr("生命之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulHp.get()) != NULL)
		pElem_dwSoulHp.release();
	unique_ptr<TiXmlElement> pElem_dwSoulCritical(new TiXmlElement("UINT32"));
	if(pElem_dwSoulCritical == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulCritical->SetAttribute("name", "dwSoulCritical");
	pElem_dwSoulCritical->SetAttribute("value", NumberToString(s.dwSoulCritical).c_str());
	pElem_dwSoulCritical->SetAttribute("comment", ToUTF8Ptr("暴击之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulCritical.get()) != NULL)
		pElem_dwSoulCritical.release();
	unique_ptr<TiXmlElement> pElem_dwSoulCounter(new TiXmlElement("UINT32"));
	if(pElem_dwSoulCounter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulCounter->SetAttribute("name", "dwSoulCounter");
	pElem_dwSoulCounter->SetAttribute("value", NumberToString(s.dwSoulCounter).c_str());
	pElem_dwSoulCounter->SetAttribute("comment", ToUTF8Ptr("破击之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulCounter.get()) != NULL)
		pElem_dwSoulCounter.release();
	unique_ptr<TiXmlElement> pElem_dwSoulSpeed(new TiXmlElement("UINT32"));
	if(pElem_dwSoulSpeed == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulSpeed->SetAttribute("name", "dwSoulSpeed");
	pElem_dwSoulSpeed->SetAttribute("value", NumberToString(s.dwSoulSpeed).c_str());
	pElem_dwSoulSpeed->SetAttribute("comment", ToUTF8Ptr("身法之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulSpeed.get()) != NULL)
		pElem_dwSoulSpeed.release();
	unique_ptr<TiXmlElement> pElem_dwSoulDefence(new TiXmlElement("UINT32"));
	if(pElem_dwSoulDefence == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulDefence->SetAttribute("name", "dwSoulDefence");
	pElem_dwSoulDefence->SetAttribute("value", NumberToString(s.dwSoulDefence).c_str());
	pElem_dwSoulDefence->SetAttribute("comment", ToUTF8Ptr("防御之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulDefence.get()) != NULL)
		pElem_dwSoulDefence.release();
	unique_ptr<TiXmlElement> pElem_dwSoulHit(new TiXmlElement("UINT32"));
	if(pElem_dwSoulHit == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulHit->SetAttribute("name", "dwSoulHit");
	pElem_dwSoulHit->SetAttribute("value", NumberToString(s.dwSoulHit).c_str());
	pElem_dwSoulHit->SetAttribute("comment", ToUTF8Ptr("命中之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulHit.get()) != NULL)
		pElem_dwSoulHit.release();
	unique_ptr<TiXmlElement> pElem_dwSoulDodge(new TiXmlElement("UINT32"));
	if(pElem_dwSoulDodge == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulDodge->SetAttribute("name", "dwSoulDodge");
	pElem_dwSoulDodge->SetAttribute("value", NumberToString(s.dwSoulDodge).c_str());
	pElem_dwSoulDodge->SetAttribute("comment", ToUTF8Ptr("闪避之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulDodge.get()) != NULL)
		pElem_dwSoulDodge.release();
	unique_ptr<TiXmlElement> pElem_dwStampHuang(new TiXmlElement("UINT32"));
	if(pElem_dwStampHuang == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampHuang->SetAttribute("name", "dwStampHuang");
	pElem_dwStampHuang->SetAttribute("value", NumberToString(s.dwStampHuang).c_str());
	pElem_dwStampHuang->SetAttribute("comment", ToUTF8Ptr("黄阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampHuang.get()) != NULL)
		pElem_dwStampHuang.release();
	unique_ptr<TiXmlElement> pElem_dwStampXuan(new TiXmlElement("UINT32"));
	if(pElem_dwStampXuan == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampXuan->SetAttribute("name", "dwStampXuan");
	pElem_dwStampXuan->SetAttribute("value", NumberToString(s.dwStampXuan).c_str());
	pElem_dwStampXuan->SetAttribute("comment", ToUTF8Ptr("玄阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampXuan.get()) != NULL)
		pElem_dwStampXuan.release();
	unique_ptr<TiXmlElement> pElem_dwStampDi(new TiXmlElement("UINT32"));
	if(pElem_dwStampDi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampDi->SetAttribute("name", "dwStampDi");
	pElem_dwStampDi->SetAttribute("value", NumberToString(s.dwStampDi).c_str());
	pElem_dwStampDi->SetAttribute("comment", ToUTF8Ptr("地阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampDi.get()) != NULL)
		pElem_dwStampDi.release();
	unique_ptr<TiXmlElement> pElem_dwStampTian(new TiXmlElement("UINT32"));
	if(pElem_dwStampTian == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampTian->SetAttribute("name", "dwStampTian");
	pElem_dwStampTian->SetAttribute("value", NumberToString(s.dwStampTian).c_str());
	pElem_dwStampTian->SetAttribute("comment", ToUTF8Ptr("天阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampTian.get()) != NULL)
		pElem_dwStampTian.release();
	unique_ptr<TiXmlElement> pElem_dwStampXing(new TiXmlElement("UINT32"));
	if(pElem_dwStampXing == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampXing->SetAttribute("name", "dwStampXing");
	pElem_dwStampXing->SetAttribute("value", NumberToString(s.dwStampXing).c_str());
	pElem_dwStampXing->SetAttribute("comment", ToUTF8Ptr("星阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampXing.get()) != NULL)
		pElem_dwStampXing.release();
	unique_ptr<TiXmlElement> pElem_dwStampYue(new TiXmlElement("UINT32"));
	if(pElem_dwStampYue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampYue->SetAttribute("name", "dwStampYue");
	pElem_dwStampYue->SetAttribute("value", NumberToString(s.dwStampYue).c_str());
	pElem_dwStampYue->SetAttribute("comment", ToUTF8Ptr("月阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampYue.get()) != NULL)
		pElem_dwStampYue.release();
	unique_ptr<TiXmlElement> pElem_dwStampDi2(new TiXmlElement("UINT32"));
	if(pElem_dwStampDi2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampDi2->SetAttribute("name", "dwStampDi2");
	pElem_dwStampDi2->SetAttribute("value", NumberToString(s.dwStampDi2).c_str());
	pElem_dwStampDi2->SetAttribute("comment", ToUTF8Ptr("帝阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampDi2.get()) != NULL)
		pElem_dwStampDi2.release();
	unique_ptr<TiXmlElement> pElem_dwStampXian(new TiXmlElement("UINT32"));
	if(pElem_dwStampXian == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampXian->SetAttribute("name", "dwStampXian");
	pElem_dwStampXian->SetAttribute("value", NumberToString(s.dwStampXian).c_str());
	pElem_dwStampXian->SetAttribute("comment", ToUTF8Ptr("仙阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampXian.get()) != NULL)
		pElem_dwStampXian.release();
	unique_ptr<TiXmlElement> pElem_dwStampSheng(new TiXmlElement("UINT32"));
	if(pElem_dwStampSheng == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampSheng->SetAttribute("name", "dwStampSheng");
	pElem_dwStampSheng->SetAttribute("value", NumberToString(s.dwStampSheng).c_str());
	pElem_dwStampSheng->SetAttribute("comment", ToUTF8Ptr("圣阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampSheng.get()) != NULL)
		pElem_dwStampSheng.release();
	unique_ptr<TiXmlElement> pElem_dwStampFo(new TiXmlElement("UINT32"));
	if(pElem_dwStampFo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampFo->SetAttribute("name", "dwStampFo");
	pElem_dwStampFo->SetAttribute("value", NumberToString(s.dwStampFo).c_str());
	pElem_dwStampFo->SetAttribute("comment", ToUTF8Ptr("佛阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampFo.get()) != NULL)
		pElem_dwStampFo.release();
	unique_ptr<TiXmlElement> pElem_dwLoveHeart(new TiXmlElement("UINT32"));
	if(pElem_dwLoveHeart == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLoveHeart->SetAttribute("name", "dwLoveHeart");
	pElem_dwLoveHeart->SetAttribute("value", NumberToString(s.dwLoveHeart).c_str());
	pElem_dwLoveHeart->SetAttribute("comment", ToUTF8Ptr("爱心"));
	if(rElement.LinkEndChild(pElem_dwLoveHeart.get()) != NULL)
		pElem_dwLoveHeart.release();
	unique_ptr<TiXmlElement> pElem_dwBlueFairyFate(new TiXmlElement("UINT32"));
	if(pElem_dwBlueFairyFate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBlueFairyFate->SetAttribute("name", "dwBlueFairyFate");
	pElem_dwBlueFairyFate->SetAttribute("value", NumberToString(s.dwBlueFairyFate).c_str());
	pElem_dwBlueFairyFate->SetAttribute("comment", ToUTF8Ptr("蓝色仙缘"));
	if(rElement.LinkEndChild(pElem_dwBlueFairyFate.get()) != NULL)
		pElem_dwBlueFairyFate.release();
	unique_ptr<TiXmlElement> pElem_dwPurpleFairyFate(new TiXmlElement("UINT32"));
	if(pElem_dwPurpleFairyFate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPurpleFairyFate->SetAttribute("name", "dwPurpleFairyFate");
	pElem_dwPurpleFairyFate->SetAttribute("value", NumberToString(s.dwPurpleFairyFate).c_str());
	pElem_dwPurpleFairyFate->SetAttribute("comment", ToUTF8Ptr("紫色仙缘"));
	if(rElement.LinkEndChild(pElem_dwPurpleFairyFate.get()) != NULL)
		pElem_dwPurpleFairyFate.release();
	unique_ptr<TiXmlElement> pElem_dwOrangeFairyFate(new TiXmlElement("UINT32"));
	if(pElem_dwOrangeFairyFate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOrangeFairyFate->SetAttribute("name", "dwOrangeFairyFate");
	pElem_dwOrangeFairyFate->SetAttribute("value", NumberToString(s.dwOrangeFairyFate).c_str());
	pElem_dwOrangeFairyFate->SetAttribute("comment", ToUTF8Ptr("橙色仙缘"));
	if(rElement.LinkEndChild(pElem_dwOrangeFairyFate.get()) != NULL)
		pElem_dwOrangeFairyFate.release();
	unique_ptr<TiXmlElement> pElem_dwDuJieFu(new TiXmlElement("UINT32"));
	if(pElem_dwDuJieFu == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDuJieFu->SetAttribute("name", "dwDuJieFu");
	pElem_dwDuJieFu->SetAttribute("value", NumberToString(s.dwDuJieFu).c_str());
	pElem_dwDuJieFu->SetAttribute("comment", ToUTF8Ptr("散仙渡劫符数量"));
	if(rElement.LinkEndChild(pElem_dwDuJieFu.get()) != NULL)
		pElem_dwDuJieFu.release();
	unique_ptr<TiXmlElement> pElem_dwBTPoint(new TiXmlElement("UINT32"));
	if(pElem_dwBTPoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBTPoint->SetAttribute("name", "dwBTPoint");
	pElem_dwBTPoint->SetAttribute("value", NumberToString(s.dwBTPoint).c_str());
	pElem_dwBTPoint->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwBTPoint.get()) != NULL)
		pElem_dwBTPoint.release();
	unique_ptr<TiXmlElement> pElem_szOwnTitle(new TiXmlElement("string"));
	if(pElem_szOwnTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_szOwnTitle->SetAttribute("name", "szOwnTitle");
	pElem_szOwnTitle->SetAttribute("value", s.szOwnTitle.c_str());
	pElem_szOwnTitle->SetAttribute("comment", ToUTF8Ptr("拥有的称号"));
	if(rElement.LinkEndChild(pElem_szOwnTitle.get()) != NULL)
		pElem_szOwnTitle.release();
	unique_ptr<TiXmlElement> pElem_szEquipTitle(new TiXmlElement("string"));
	if(pElem_szEquipTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_szEquipTitle->SetAttribute("name", "szEquipTitle");
	pElem_szEquipTitle->SetAttribute("value", s.szEquipTitle.c_str());
	pElem_szEquipTitle->SetAttribute("comment", ToUTF8Ptr("装备的称号"));
	if(rElement.LinkEndChild(pElem_szEquipTitle.get()) != NULL)
		pElem_szEquipTitle.release();
	unique_ptr<TiXmlElement> pElem_byDomain(new TiXmlElement("UINT8"));
	if(pElem_byDomain == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDomain->SetAttribute("name", "byDomain");
	pElem_byDomain->SetAttribute("value", NumberToString(s.byDomain).c_str());
	pElem_byDomain->SetAttribute("comment", ToUTF8Ptr("渠道"));
	if(rElement.LinkEndChild(pElem_byDomain.get()) != NULL)
		pElem_byDomain.release();
	unique_ptr<TiXmlElement> pElem_byDomainLvl(new TiXmlElement("UINT8"));
	if(pElem_byDomainLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDomainLvl->SetAttribute("name", "byDomainLvl");
	pElem_byDomainLvl->SetAttribute("value", NumberToString(s.byDomainLvl).c_str());
	pElem_byDomainLvl->SetAttribute("comment", ToUTF8Ptr("渠道等级"));
	if(rElement.LinkEndChild(pElem_byDomainLvl.get()) != NULL)
		pElem_byDomainLvl.release();
	unique_ptr<TiXmlElement> pElem_byDisplayLvl(new TiXmlElement("UINT8"));
	if(pElem_byDisplayLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDisplayLvl->SetAttribute("name", "byDisplayLvl");
	pElem_byDisplayLvl->SetAttribute("value", NumberToString(s.byDisplayLvl).c_str());
	pElem_byDisplayLvl->SetAttribute("comment", ToUTF8Ptr("显示等级"));
	if(rElement.LinkEndChild(pElem_byDisplayLvl.get()) != NULL)
		pElem_byDisplayLvl.release();
	unique_ptr<TiXmlElement> pElem_byDomainYear(new TiXmlElement("UINT8"));
	if(pElem_byDomainYear == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDomainYear->SetAttribute("name", "byDomainYear");
	pElem_byDomainYear->SetAttribute("value", NumberToString(s.byDomainYear).c_str());
	pElem_byDomainYear->SetAttribute("comment", ToUTF8Ptr("年费"));
	if(rElement.LinkEndChild(pElem_byDomainYear.get()) != NULL)
		pElem_byDomainYear.release();
	unique_ptr<TiXmlElement> pElem_szOpenId(new TiXmlElement("string"));
	if(pElem_szOpenId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_szOpenId->SetAttribute("name", "szOpenId");
	pElem_szOpenId->SetAttribute("value", s.szOpenId.c_str());
	pElem_szOpenId->SetAttribute("comment", ToUTF8Ptr("szOpenId"));
	if(rElement.LinkEndChild(pElem_szOpenId.get()) != NULL)
		pElem_szOpenId.release();
	unique_ptr<TiXmlElement> pElem_szOpenKey(new TiXmlElement("string"));
	if(pElem_szOpenKey == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_szOpenKey->SetAttribute("name", "szOpenKey");
	pElem_szOpenKey->SetAttribute("value", s.szOpenKey.c_str());
	pElem_szOpenKey->SetAttribute("comment", ToUTF8Ptr("szOpenKey"));
	if(rElement.LinkEndChild(pElem_szOpenKey.get()) != NULL)
		pElem_szOpenKey.release();
	unique_ptr<TiXmlElement> pElem_strSign(new TiXmlElement("string"));
	if(pElem_strSign == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSign->SetAttribute("name", "strSign");
	pElem_strSign->SetAttribute("value", s.strSign.c_str());
	pElem_strSign->SetAttribute("comment", ToUTF8Ptr("签名"));
	if(rElement.LinkEndChild(pElem_strSign.get()) != NULL)
		pElem_strSign.release();
	unique_ptr<TiXmlElement> pElem_wMood(new TiXmlElement("UINT16"));
	if(pElem_wMood == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMood->SetAttribute("name", "wMood");
	pElem_wMood->SetAttribute("value", NumberToString(s.wMood).c_str());
	pElem_wMood->SetAttribute("comment", ToUTF8Ptr("心情表情"));
	if(rElement.LinkEndChild(pElem_wMood.get()) != NULL)
		pElem_wMood.release();
	unique_ptr<TiXmlElement> pElem_wAchievementLevel(new TiXmlElement("UINT16"));
	if(pElem_wAchievementLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wAchievementLevel->SetAttribute("name", "wAchievementLevel");
	pElem_wAchievementLevel->SetAttribute("value", NumberToString(s.wAchievementLevel).c_str());
	pElem_wAchievementLevel->SetAttribute("comment", ToUTF8Ptr("成就等级"));
	if(rElement.LinkEndChild(pElem_wAchievementLevel.get()) != NULL)
		pElem_wAchievementLevel.release();
	unique_ptr<TiXmlElement> pElem_dwAchievementAP(new TiXmlElement("UINT32"));
	if(pElem_dwAchievementAP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAchievementAP->SetAttribute("name", "dwAchievementAP");
	pElem_dwAchievementAP->SetAttribute("value", NumberToString(s.dwAchievementAP).c_str());
	pElem_dwAchievementAP->SetAttribute("comment", ToUTF8Ptr("成就点"));
	if(rElement.LinkEndChild(pElem_dwAchievementAP.get()) != NULL)
		pElem_dwAchievementAP.release();
	unique_ptr<TiXmlElement> pElem_wCollectLevel(new TiXmlElement("UINT16"));
	if(pElem_wCollectLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCollectLevel->SetAttribute("name", "wCollectLevel");
	pElem_wCollectLevel->SetAttribute("value", NumberToString(s.wCollectLevel).c_str());
	pElem_wCollectLevel->SetAttribute("comment", ToUTF8Ptr("收藏等级"));
	if(rElement.LinkEndChild(pElem_wCollectLevel.get()) != NULL)
		pElem_wCollectLevel.release();
	unique_ptr<TiXmlElement> pElem_dwCollectAP(new TiXmlElement("UINT32"));
	if(pElem_dwCollectAP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCollectAP->SetAttribute("name", "dwCollectAP");
	pElem_dwCollectAP->SetAttribute("value", NumberToString(s.dwCollectAP).c_str());
	pElem_dwCollectAP->SetAttribute("comment", ToUTF8Ptr("收藏点"));
	if(rElement.LinkEndChild(pElem_dwCollectAP.get()) != NULL)
		pElem_dwCollectAP.release();
	unique_ptr<TiXmlElement> pElem_qwInvitedID(new TiXmlElement("UINT64"));
	if(pElem_qwInvitedID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInvitedID->SetAttribute("name", "qwInvitedID");
	pElem_qwInvitedID->SetAttribute("value", NumberToString(s.qwInvitedID).c_str());
	pElem_qwInvitedID->SetAttribute("comment", ToUTF8Ptr("邀请"));
	if(rElement.LinkEndChild(pElem_qwInvitedID.get()) != NULL)
		pElem_qwInvitedID.release();
	unique_ptr<TiXmlElement> pElem_byWallow(new TiXmlElement("UINT8"));
	if(pElem_byWallow == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byWallow->SetAttribute("name", "byWallow");
	pElem_byWallow->SetAttribute("value", NumberToString(s.byWallow).c_str());
	pElem_byWallow->SetAttribute("comment", ToUTF8Ptr("防沉迷"));
	if(rElement.LinkEndChild(pElem_byWallow.get()) != NULL)
		pElem_byWallow.release();
	unique_ptr<TiXmlElement> pElem_dwIndulgeKickTime(new TiXmlElement("UINT32"));
	if(pElem_dwIndulgeKickTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwIndulgeKickTime->SetAttribute("name", "dwIndulgeKickTime");
	pElem_dwIndulgeKickTime->SetAttribute("value", NumberToString(s.dwIndulgeKickTime).c_str());
	pElem_dwIndulgeKickTime->SetAttribute("comment", ToUTF8Ptr("防沉迷t人时间"));
	if(rElement.LinkEndChild(pElem_dwIndulgeKickTime.get()) != NULL)
		pElem_dwIndulgeKickTime.release();
	unique_ptr<TiXmlElement> pElem_byYDLevel(new TiXmlElement("UINT8"));
	if(pElem_byYDLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byYDLevel->SetAttribute("name", "byYDLevel");
	pElem_byYDLevel->SetAttribute("value", NumberToString(s.byYDLevel).c_str());
	pElem_byYDLevel->SetAttribute("comment", ToUTF8Ptr("玩家QQ黄钻等级"));
	if(rElement.LinkEndChild(pElem_byYDLevel.get()) != NULL)
		pElem_byYDLevel.release();
	unique_ptr<TiXmlElement> pElem_dwCreateTime(new TiXmlElement("UINT32"));
	if(pElem_dwCreateTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCreateTime->SetAttribute("name", "dwCreateTime");
	pElem_dwCreateTime->SetAttribute("value", NumberToString(s.dwCreateTime).c_str());
	pElem_dwCreateTime->SetAttribute("comment", ToUTF8Ptr("创角时间"));
	if(rElement.LinkEndChild(pElem_dwCreateTime.get()) != NULL)
		pElem_dwCreateTime.release();
	unique_ptr<TiXmlElement> pElem_wLastSaveMapID(new TiXmlElement("UINT16"));
	if(pElem_wLastSaveMapID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLastSaveMapID->SetAttribute("name", "wLastSaveMapID");
	pElem_wLastSaveMapID->SetAttribute("value", NumberToString(s.wLastSaveMapID).c_str());
	pElem_wLastSaveMapID->SetAttribute("comment", ToUTF8Ptr("保存地图ID"));
	if(rElement.LinkEndChild(pElem_wLastSaveMapID.get()) != NULL)
		pElem_wLastSaveMapID.release();
	unique_ptr<TiXmlElement> pElem_fLastSaveX(new TiXmlElement("float"));
	if(pElem_fLastSaveX == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fLastSaveX->SetAttribute("name", "fLastSaveX");
	pElem_fLastSaveX->SetAttribute("value", NumberToString(s.fLastSaveX).c_str());
	pElem_fLastSaveX->SetAttribute("comment", ToUTF8Ptr("保存X坐标"));
	if(rElement.LinkEndChild(pElem_fLastSaveX.get()) != NULL)
		pElem_fLastSaveX.release();
	unique_ptr<TiXmlElement> pElem_fLastSaveY(new TiXmlElement("float"));
	if(pElem_fLastSaveY == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fLastSaveY->SetAttribute("name", "fLastSaveY");
	pElem_fLastSaveY->SetAttribute("value", NumberToString(s.fLastSaveY).c_str());
	pElem_fLastSaveY->SetAttribute("comment", ToUTF8Ptr("保存Y坐标"));
	if(rElement.LinkEndChild(pElem_fLastSaveY.get()) != NULL)
		pElem_fLastSaveY.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoleBaseInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		RoleBaseInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRoleBaseInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("RoleBaseInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

RoleDgnInfo::RoleDgnInfo() : dwDgnType(0), dwLastEnterTimer(0), byCost(0), dwEnterTimesAppend(0), dwAppendEndTimer(0), 
			dwEnterTimes(0), dwLastCompleteTimer(0), dwCompleteTimes(0), wMinTurns(0), dwBuyTimer(0), 
			dwBuyTimesToday(0), dwFinishTimesToday(0) { }

CInArchive& operator>>(CInArchive& src, RoleDgnInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwDgnType;
	src >> s.dwLastEnterTimer;
	src >> s.byCost;
	src >> s.dwEnterTimesAppend;
	src >> s.dwAppendEndTimer;
	src >> s.dwEnterTimes;
	src >> s.dwLastCompleteTimer;
	src >> s.dwCompleteTimes;
	src >> s.wMinTurns;
	src >> s.dwBuyTimer;
	src >> s.dwBuyTimesToday;
	src >> s.dwFinishTimesToday;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const RoleDgnInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwDgnType;
	src << s.dwLastEnterTimer;
	src << s.byCost;
	src << s.dwEnterTimesAppend;
	src << s.dwAppendEndTimer;
	src << s.dwEnterTimes;
	src << s.dwLastCompleteTimer;
	src << s.dwCompleteTimes;
	src << s.wMinTurns;
	src << s.dwBuyTimer;
	src << s.dwBuyTimesToday;
	src << s.dwFinishTimesToday;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, RoleDgnInfo& s)
{
	if(strcmp(rElement.Value(), "RoleDgnInfo") != 0)
	{
		LOG_CRI << "rElement is not RoleDgnInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDgnType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDgnType") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDgnType!";
		return false;
	}
	const char* pszVal_dwDgnType = pElemChild->Attribute("value");
	if(pszVal_dwDgnType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDgnType, s.dwDgnType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLastEnterTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastEnterTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastEnterTimer!";
		return false;
	}
	const char* pszVal_dwLastEnterTimer = pElemChild->Attribute("value");
	if(pszVal_dwLastEnterTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastEnterTimer, s.dwLastEnterTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCost is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCost") != 0)
	{
		LOG_CRI << "Attribute: name is not byCost!";
		return false;
	}
	const char* pszVal_byCost = pElemChild->Attribute("value");
	if(pszVal_byCost == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCost, s.byCost))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEnterTimesAppend is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEnterTimesAppend") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEnterTimesAppend!";
		return false;
	}
	const char* pszVal_dwEnterTimesAppend = pElemChild->Attribute("value");
	if(pszVal_dwEnterTimesAppend == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEnterTimesAppend, s.dwEnterTimesAppend))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAppendEndTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAppendEndTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAppendEndTimer!";
		return false;
	}
	const char* pszVal_dwAppendEndTimer = pElemChild->Attribute("value");
	if(pszVal_dwAppendEndTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAppendEndTimer, s.dwAppendEndTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEnterTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEnterTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEnterTimes!";
		return false;
	}
	const char* pszVal_dwEnterTimes = pElemChild->Attribute("value");
	if(pszVal_dwEnterTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEnterTimes, s.dwEnterTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLastCompleteTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastCompleteTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastCompleteTimer!";
		return false;
	}
	const char* pszVal_dwLastCompleteTimer = pElemChild->Attribute("value");
	if(pszVal_dwLastCompleteTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastCompleteTimer, s.dwLastCompleteTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCompleteTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCompleteTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCompleteTimes!";
		return false;
	}
	const char* pszVal_dwCompleteTimes = pElemChild->Attribute("value");
	if(pszVal_dwCompleteTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCompleteTimes, s.dwCompleteTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMinTurns is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMinTurns") != 0)
	{
		LOG_CRI << "Attribute: name is not wMinTurns!";
		return false;
	}
	const char* pszVal_wMinTurns = pElemChild->Attribute("value");
	if(pszVal_wMinTurns == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMinTurns, s.wMinTurns))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuyTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyTimer!";
		return false;
	}
	const char* pszVal_dwBuyTimer = pElemChild->Attribute("value");
	if(pszVal_dwBuyTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyTimer, s.dwBuyTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuyTimesToday is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyTimesToday") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyTimesToday!";
		return false;
	}
	const char* pszVal_dwBuyTimesToday = pElemChild->Attribute("value");
	if(pszVal_dwBuyTimesToday == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyTimesToday, s.dwBuyTimesToday))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFinishTimesToday is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFinishTimesToday") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFinishTimesToday!";
		return false;
	}
	const char* pszVal_dwFinishTimesToday = pElemChild->Attribute("value");
	if(pszVal_dwFinishTimesToday == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFinishTimesToday, s.dwFinishTimesToday))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const RoleDgnInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("RoleDgnInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("EDataType:eTypePlayerDgn：剧情副本，特定日期副本可以考虑删除"));
	unique_ptr<TiXmlElement> pElem_dwDgnType(new TiXmlElement("UINT32"));
	if(pElem_dwDgnType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDgnType->SetAttribute("name", "dwDgnType");
	pElem_dwDgnType->SetAttribute("value", NumberToString(s.dwDgnType).c_str());
	pElem_dwDgnType->SetAttribute("comment", ToUTF8Ptr("副本类型"));
	if(rElement.LinkEndChild(pElem_dwDgnType.get()) != NULL)
		pElem_dwDgnType.release();
	unique_ptr<TiXmlElement> pElem_dwLastEnterTimer(new TiXmlElement("UINT32"));
	if(pElem_dwLastEnterTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastEnterTimer->SetAttribute("name", "dwLastEnterTimer");
	pElem_dwLastEnterTimer->SetAttribute("value", NumberToString(s.dwLastEnterTimer).c_str());
	pElem_dwLastEnterTimer->SetAttribute("comment", ToUTF8Ptr("最近副本支付代价时间"));
	if(rElement.LinkEndChild(pElem_dwLastEnterTimer.get()) != NULL)
		pElem_dwLastEnterTimer.release();
	unique_ptr<TiXmlElement> pElem_byCost(new TiXmlElement("UINT8"));
	if(pElem_byCost == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCost->SetAttribute("name", "byCost");
	pElem_byCost->SetAttribute("value", NumberToString(s.byCost).c_str());
	pElem_byCost->SetAttribute("comment", ToUTF8Ptr("副本支付代价,是否没有消费,0表示已经消费"));
	if(rElement.LinkEndChild(pElem_byCost.get()) != NULL)
		pElem_byCost.release();
	unique_ptr<TiXmlElement> pElem_dwEnterTimesAppend(new TiXmlElement("UINT32"));
	if(pElem_dwEnterTimesAppend == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEnterTimesAppend->SetAttribute("name", "dwEnterTimesAppend");
	pElem_dwEnterTimesAppend->SetAttribute("value", NumberToString(s.dwEnterTimesAppend).c_str());
	pElem_dwEnterTimesAppend->SetAttribute("comment", ToUTF8Ptr("额外增加的副本进入次数"));
	if(rElement.LinkEndChild(pElem_dwEnterTimesAppend.get()) != NULL)
		pElem_dwEnterTimesAppend.release();
	unique_ptr<TiXmlElement> pElem_dwAppendEndTimer(new TiXmlElement("UINT32"));
	if(pElem_dwAppendEndTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAppendEndTimer->SetAttribute("name", "dwAppendEndTimer");
	pElem_dwAppendEndTimer->SetAttribute("value", NumberToString(s.dwAppendEndTimer).c_str());
	pElem_dwAppendEndTimer->SetAttribute("comment", ToUTF8Ptr("额外增加的副本进入次数的到期时间"));
	if(rElement.LinkEndChild(pElem_dwAppendEndTimer.get()) != NULL)
		pElem_dwAppendEndTimer.release();
	unique_ptr<TiXmlElement> pElem_dwEnterTimes(new TiXmlElement("UINT32"));
	if(pElem_dwEnterTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEnterTimes->SetAttribute("name", "dwEnterTimes");
	pElem_dwEnterTimes->SetAttribute("value", NumberToString(s.dwEnterTimes).c_str());
	pElem_dwEnterTimes->SetAttribute("comment", ToUTF8Ptr("当前副本进入次数"));
	if(rElement.LinkEndChild(pElem_dwEnterTimes.get()) != NULL)
		pElem_dwEnterTimes.release();
	unique_ptr<TiXmlElement> pElem_dwLastCompleteTimer(new TiXmlElement("UINT32"));
	if(pElem_dwLastCompleteTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastCompleteTimer->SetAttribute("name", "dwLastCompleteTimer");
	pElem_dwLastCompleteTimer->SetAttribute("value", NumberToString(s.dwLastCompleteTimer).c_str());
	pElem_dwLastCompleteTimer->SetAttribute("comment", ToUTF8Ptr("最近副本通过时间"));
	if(rElement.LinkEndChild(pElem_dwLastCompleteTimer.get()) != NULL)
		pElem_dwLastCompleteTimer.release();
	unique_ptr<TiXmlElement> pElem_dwCompleteTimes(new TiXmlElement("UINT32"));
	if(pElem_dwCompleteTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCompleteTimes->SetAttribute("name", "dwCompleteTimes");
	pElem_dwCompleteTimes->SetAttribute("value", NumberToString(s.dwCompleteTimes).c_str());
	pElem_dwCompleteTimes->SetAttribute("comment", ToUTF8Ptr("副本通过次数，通过就记录下"));
	if(rElement.LinkEndChild(pElem_dwCompleteTimes.get()) != NULL)
		pElem_dwCompleteTimes.release();
	unique_ptr<TiXmlElement> pElem_wMinTurns(new TiXmlElement("UINT16"));
	if(pElem_wMinTurns == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMinTurns->SetAttribute("name", "wMinTurns");
	pElem_wMinTurns->SetAttribute("value", NumberToString(s.wMinTurns).c_str());
	pElem_wMinTurns->SetAttribute("comment", ToUTF8Ptr("通过的最少回合数"));
	if(rElement.LinkEndChild(pElem_wMinTurns.get()) != NULL)
		pElem_wMinTurns.release();
	unique_ptr<TiXmlElement> pElem_dwBuyTimer(new TiXmlElement("UINT32"));
	if(pElem_dwBuyTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyTimer->SetAttribute("name", "dwBuyTimer");
	pElem_dwBuyTimer->SetAttribute("value", NumberToString(s.dwBuyTimer).c_str());
	pElem_dwBuyTimer->SetAttribute("comment", ToUTF8Ptr("最近购买的时间"));
	if(rElement.LinkEndChild(pElem_dwBuyTimer.get()) != NULL)
		pElem_dwBuyTimer.release();
	unique_ptr<TiXmlElement> pElem_dwBuyTimesToday(new TiXmlElement("UINT32"));
	if(pElem_dwBuyTimesToday == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyTimesToday->SetAttribute("name", "dwBuyTimesToday");
	pElem_dwBuyTimesToday->SetAttribute("value", NumberToString(s.dwBuyTimesToday).c_str());
	pElem_dwBuyTimesToday->SetAttribute("comment", ToUTF8Ptr("当天购买的次数"));
	if(rElement.LinkEndChild(pElem_dwBuyTimesToday.get()) != NULL)
		pElem_dwBuyTimesToday.release();
	unique_ptr<TiXmlElement> pElem_dwFinishTimesToday(new TiXmlElement("UINT32"));
	if(pElem_dwFinishTimesToday == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFinishTimesToday->SetAttribute("name", "dwFinishTimesToday");
	pElem_dwFinishTimesToday->SetAttribute("value", NumberToString(s.dwFinishTimesToday).c_str());
	pElem_dwFinishTimesToday->SetAttribute("comment", ToUTF8Ptr("今日完成副本次数"));
	if(rElement.LinkEndChild(pElem_dwFinishTimesToday.get()) != NULL)
		pElem_dwFinishTimesToday.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoleDgnInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		RoleDgnInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRoleDgnInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("RoleDgnInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

RoleTaskInfo::RoleTaskInfo() : dwTaskId(0), eTaskState((NTaskProt::ETaskState)0), dwAcceptTimes(0), dwLastAcceptTimer(0), dwFinishTimes(0), 
			dwLastFinishTimer(0), byProcessType1(0), dwProcessParam11(0), dwProcessParam12(0), byProcessType2(0), 
			dwProcessParam21(0), dwProcessParam22(0), byProcessType3(0), dwProcessParam31(0), dwProcessParam32(0), 
			dwRepeatAcceptTimes(0) { }

CInArchive& operator>>(CInArchive& src, RoleTaskInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwTaskId;
	src >> (UINT8&)s.eTaskState;
	src >> s.dwAcceptTimes;
	src >> s.dwLastAcceptTimer;
	src >> s.dwFinishTimes;
	src >> s.dwLastFinishTimer;
	src >> s.byProcessType1;
	src >> s.dwProcessParam11;
	src >> s.dwProcessParam12;
	src >> s.byProcessType2;
	src >> s.dwProcessParam21;
	src >> s.dwProcessParam22;
	src >> s.byProcessType3;
	src >> s.dwProcessParam31;
	src >> s.dwProcessParam32;
	src >> s.dwRepeatAcceptTimes;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const RoleTaskInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwTaskId;
	src << (UINT8&)s.eTaskState;
	src << s.dwAcceptTimes;
	src << s.dwLastAcceptTimer;
	src << s.dwFinishTimes;
	src << s.dwLastFinishTimer;
	src << s.byProcessType1;
	src << s.dwProcessParam11;
	src << s.dwProcessParam12;
	src << s.byProcessType2;
	src << s.dwProcessParam21;
	src << s.dwProcessParam22;
	src << s.byProcessType3;
	src << s.dwProcessParam31;
	src << s.dwProcessParam32;
	src << s.dwRepeatAcceptTimes;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, RoleTaskInfo& s)
{
	if(strcmp(rElement.Value(), "RoleTaskInfo") != 0)
	{
		LOG_CRI << "rElement is not RoleTaskInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTaskId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTaskId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTaskId!";
		return false;
	}
	const char* pszVal_dwTaskId = pElemChild->Attribute("value");
	if(pszVal_dwTaskId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTaskId, s.dwTaskId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eTaskState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TaskProt::ETaskState") != 0)
	{
		LOG_CRI << "pElemChild is not TaskProt::ETaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eTaskState") != 0)
	{
		LOG_CRI << "Attribute: name is not eTaskState!";
		return false;
	}
	const char* pszVal_eTaskState = pElemChild->Attribute("value");
	if(pszVal_eTaskState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NTaskProt::EnumStrToVal(pszVal_eTaskState, s.eTaskState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAcceptTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAcceptTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAcceptTimes!";
		return false;
	}
	const char* pszVal_dwAcceptTimes = pElemChild->Attribute("value");
	if(pszVal_dwAcceptTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAcceptTimes, s.dwAcceptTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLastAcceptTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastAcceptTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastAcceptTimer!";
		return false;
	}
	const char* pszVal_dwLastAcceptTimer = pElemChild->Attribute("value");
	if(pszVal_dwLastAcceptTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastAcceptTimer, s.dwLastAcceptTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFinishTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFinishTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFinishTimes!";
		return false;
	}
	const char* pszVal_dwFinishTimes = pElemChild->Attribute("value");
	if(pszVal_dwFinishTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFinishTimes, s.dwFinishTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLastFinishTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastFinishTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastFinishTimer!";
		return false;
	}
	const char* pszVal_dwLastFinishTimer = pElemChild->Attribute("value");
	if(pszVal_dwLastFinishTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastFinishTimer, s.dwLastFinishTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byProcessType1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byProcessType1") != 0)
	{
		LOG_CRI << "Attribute: name is not byProcessType1!";
		return false;
	}
	const char* pszVal_byProcessType1 = pElemChild->Attribute("value");
	if(pszVal_byProcessType1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byProcessType1, s.byProcessType1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwProcessParam11 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwProcessParam11") != 0)
	{
		LOG_CRI << "Attribute: name is not dwProcessParam11!";
		return false;
	}
	const char* pszVal_dwProcessParam11 = pElemChild->Attribute("value");
	if(pszVal_dwProcessParam11 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwProcessParam11, s.dwProcessParam11))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwProcessParam12 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwProcessParam12") != 0)
	{
		LOG_CRI << "Attribute: name is not dwProcessParam12!";
		return false;
	}
	const char* pszVal_dwProcessParam12 = pElemChild->Attribute("value");
	if(pszVal_dwProcessParam12 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwProcessParam12, s.dwProcessParam12))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byProcessType2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byProcessType2") != 0)
	{
		LOG_CRI << "Attribute: name is not byProcessType2!";
		return false;
	}
	const char* pszVal_byProcessType2 = pElemChild->Attribute("value");
	if(pszVal_byProcessType2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byProcessType2, s.byProcessType2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwProcessParam21 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwProcessParam21") != 0)
	{
		LOG_CRI << "Attribute: name is not dwProcessParam21!";
		return false;
	}
	const char* pszVal_dwProcessParam21 = pElemChild->Attribute("value");
	if(pszVal_dwProcessParam21 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwProcessParam21, s.dwProcessParam21))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwProcessParam22 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwProcessParam22") != 0)
	{
		LOG_CRI << "Attribute: name is not dwProcessParam22!";
		return false;
	}
	const char* pszVal_dwProcessParam22 = pElemChild->Attribute("value");
	if(pszVal_dwProcessParam22 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwProcessParam22, s.dwProcessParam22))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byProcessType3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byProcessType3") != 0)
	{
		LOG_CRI << "Attribute: name is not byProcessType3!";
		return false;
	}
	const char* pszVal_byProcessType3 = pElemChild->Attribute("value");
	if(pszVal_byProcessType3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byProcessType3, s.byProcessType3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwProcessParam31 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwProcessParam31") != 0)
	{
		LOG_CRI << "Attribute: name is not dwProcessParam31!";
		return false;
	}
	const char* pszVal_dwProcessParam31 = pElemChild->Attribute("value");
	if(pszVal_dwProcessParam31 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwProcessParam31, s.dwProcessParam31))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwProcessParam32 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwProcessParam32") != 0)
	{
		LOG_CRI << "Attribute: name is not dwProcessParam32!";
		return false;
	}
	const char* pszVal_dwProcessParam32 = pElemChild->Attribute("value");
	if(pszVal_dwProcessParam32 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwProcessParam32, s.dwProcessParam32))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRepeatAcceptTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRepeatAcceptTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRepeatAcceptTimes!";
		return false;
	}
	const char* pszVal_dwRepeatAcceptTimes = pElemChild->Attribute("value");
	if(pszVal_dwRepeatAcceptTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRepeatAcceptTimes, s.dwRepeatAcceptTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const RoleTaskInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("RoleTaskInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("任务存储结构"));
	unique_ptr<TiXmlElement> pElem_dwTaskId(new TiXmlElement("UINT32"));
	if(pElem_dwTaskId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTaskId->SetAttribute("name", "dwTaskId");
	pElem_dwTaskId->SetAttribute("value", NumberToString(s.dwTaskId).c_str());
	pElem_dwTaskId->SetAttribute("comment", ToUTF8Ptr("任务Id"));
	if(rElement.LinkEndChild(pElem_dwTaskId.get()) != NULL)
		pElem_dwTaskId.release();
	unique_ptr<TiXmlElement> pElem_eTaskState(new TiXmlElement("TaskProt::ETaskState"));
	if(pElem_eTaskState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eTaskState->SetAttribute("name", "eTaskState");
	const char* pszEnum_eTaskState = NTaskProt::EnumValToStr(s.eTaskState);
	if(pszEnum_eTaskState == NULL)
	{
		LOG_CRI << "EnumValToStr for eTaskState fails!";
		return false;
	}
	pElem_eTaskState->SetAttribute("value", pszEnum_eTaskState);
	pElem_eTaskState->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eTaskState.get()) != NULL)
		pElem_eTaskState.release();
	unique_ptr<TiXmlElement> pElem_dwAcceptTimes(new TiXmlElement("UINT32"));
	if(pElem_dwAcceptTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAcceptTimes->SetAttribute("name", "dwAcceptTimes");
	pElem_dwAcceptTimes->SetAttribute("value", NumberToString(s.dwAcceptTimes).c_str());
	pElem_dwAcceptTimes->SetAttribute("comment", ToUTF8Ptr("接受任务次数"));
	if(rElement.LinkEndChild(pElem_dwAcceptTimes.get()) != NULL)
		pElem_dwAcceptTimes.release();
	unique_ptr<TiXmlElement> pElem_dwLastAcceptTimer(new TiXmlElement("UINT32"));
	if(pElem_dwLastAcceptTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastAcceptTimer->SetAttribute("name", "dwLastAcceptTimer");
	pElem_dwLastAcceptTimer->SetAttribute("value", NumberToString(s.dwLastAcceptTimer).c_str());
	pElem_dwLastAcceptTimer->SetAttribute("comment", ToUTF8Ptr("最近任务接受时间"));
	if(rElement.LinkEndChild(pElem_dwLastAcceptTimer.get()) != NULL)
		pElem_dwLastAcceptTimer.release();
	unique_ptr<TiXmlElement> pElem_dwFinishTimes(new TiXmlElement("UINT32"));
	if(pElem_dwFinishTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFinishTimes->SetAttribute("name", "dwFinishTimes");
	pElem_dwFinishTimes->SetAttribute("value", NumberToString(s.dwFinishTimes).c_str());
	pElem_dwFinishTimes->SetAttribute("comment", ToUTF8Ptr("完成任务次数"));
	if(rElement.LinkEndChild(pElem_dwFinishTimes.get()) != NULL)
		pElem_dwFinishTimes.release();
	unique_ptr<TiXmlElement> pElem_dwLastFinishTimer(new TiXmlElement("UINT32"));
	if(pElem_dwLastFinishTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastFinishTimer->SetAttribute("name", "dwLastFinishTimer");
	pElem_dwLastFinishTimer->SetAttribute("value", NumberToString(s.dwLastFinishTimer).c_str());
	pElem_dwLastFinishTimer->SetAttribute("comment", ToUTF8Ptr("最近完成任务时间"));
	if(rElement.LinkEndChild(pElem_dwLastFinishTimer.get()) != NULL)
		pElem_dwLastFinishTimer.release();
	unique_ptr<TiXmlElement> pElem_byProcessType1(new TiXmlElement("UINT8"));
	if(pElem_byProcessType1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byProcessType1->SetAttribute("name", "byProcessType1");
	pElem_byProcessType1->SetAttribute("value", NumberToString(s.byProcessType1).c_str());
	pElem_byProcessType1->SetAttribute("comment", ToUTF8Ptr("进度1的类型"));
	if(rElement.LinkEndChild(pElem_byProcessType1.get()) != NULL)
		pElem_byProcessType1.release();
	unique_ptr<TiXmlElement> pElem_dwProcessParam11(new TiXmlElement("UINT32"));
	if(pElem_dwProcessParam11 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwProcessParam11->SetAttribute("name", "dwProcessParam11");
	pElem_dwProcessParam11->SetAttribute("value", NumberToString(s.dwProcessParam11).c_str());
	pElem_dwProcessParam11->SetAttribute("comment", ToUTF8Ptr("进度1的第1个参数"));
	if(rElement.LinkEndChild(pElem_dwProcessParam11.get()) != NULL)
		pElem_dwProcessParam11.release();
	unique_ptr<TiXmlElement> pElem_dwProcessParam12(new TiXmlElement("UINT32"));
	if(pElem_dwProcessParam12 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwProcessParam12->SetAttribute("name", "dwProcessParam12");
	pElem_dwProcessParam12->SetAttribute("value", NumberToString(s.dwProcessParam12).c_str());
	pElem_dwProcessParam12->SetAttribute("comment", ToUTF8Ptr("进度1的第2个参数"));
	if(rElement.LinkEndChild(pElem_dwProcessParam12.get()) != NULL)
		pElem_dwProcessParam12.release();
	unique_ptr<TiXmlElement> pElem_byProcessType2(new TiXmlElement("UINT8"));
	if(pElem_byProcessType2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byProcessType2->SetAttribute("name", "byProcessType2");
	pElem_byProcessType2->SetAttribute("value", NumberToString(s.byProcessType2).c_str());
	pElem_byProcessType2->SetAttribute("comment", ToUTF8Ptr("进度2的类型"));
	if(rElement.LinkEndChild(pElem_byProcessType2.get()) != NULL)
		pElem_byProcessType2.release();
	unique_ptr<TiXmlElement> pElem_dwProcessParam21(new TiXmlElement("UINT32"));
	if(pElem_dwProcessParam21 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwProcessParam21->SetAttribute("name", "dwProcessParam21");
	pElem_dwProcessParam21->SetAttribute("value", NumberToString(s.dwProcessParam21).c_str());
	pElem_dwProcessParam21->SetAttribute("comment", ToUTF8Ptr("进度2的第1个参数"));
	if(rElement.LinkEndChild(pElem_dwProcessParam21.get()) != NULL)
		pElem_dwProcessParam21.release();
	unique_ptr<TiXmlElement> pElem_dwProcessParam22(new TiXmlElement("UINT32"));
	if(pElem_dwProcessParam22 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwProcessParam22->SetAttribute("name", "dwProcessParam22");
	pElem_dwProcessParam22->SetAttribute("value", NumberToString(s.dwProcessParam22).c_str());
	pElem_dwProcessParam22->SetAttribute("comment", ToUTF8Ptr("进度2的第2个参数"));
	if(rElement.LinkEndChild(pElem_dwProcessParam22.get()) != NULL)
		pElem_dwProcessParam22.release();
	unique_ptr<TiXmlElement> pElem_byProcessType3(new TiXmlElement("UINT8"));
	if(pElem_byProcessType3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byProcessType3->SetAttribute("name", "byProcessType3");
	pElem_byProcessType3->SetAttribute("value", NumberToString(s.byProcessType3).c_str());
	pElem_byProcessType3->SetAttribute("comment", ToUTF8Ptr("进度3的类型"));
	if(rElement.LinkEndChild(pElem_byProcessType3.get()) != NULL)
		pElem_byProcessType3.release();
	unique_ptr<TiXmlElement> pElem_dwProcessParam31(new TiXmlElement("UINT32"));
	if(pElem_dwProcessParam31 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwProcessParam31->SetAttribute("name", "dwProcessParam31");
	pElem_dwProcessParam31->SetAttribute("value", NumberToString(s.dwProcessParam31).c_str());
	pElem_dwProcessParam31->SetAttribute("comment", ToUTF8Ptr("进度3的第1个参数"));
	if(rElement.LinkEndChild(pElem_dwProcessParam31.get()) != NULL)
		pElem_dwProcessParam31.release();
	unique_ptr<TiXmlElement> pElem_dwProcessParam32(new TiXmlElement("UINT32"));
	if(pElem_dwProcessParam32 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwProcessParam32->SetAttribute("name", "dwProcessParam32");
	pElem_dwProcessParam32->SetAttribute("value", NumberToString(s.dwProcessParam32).c_str());
	pElem_dwProcessParam32->SetAttribute("comment", ToUTF8Ptr("进度3的第2个参数"));
	if(rElement.LinkEndChild(pElem_dwProcessParam32.get()) != NULL)
		pElem_dwProcessParam32.release();
	unique_ptr<TiXmlElement> pElem_dwRepeatAcceptTimes(new TiXmlElement("UINT32"));
	if(pElem_dwRepeatAcceptTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRepeatAcceptTimes->SetAttribute("name", "dwRepeatAcceptTimes");
	pElem_dwRepeatAcceptTimes->SetAttribute("value", NumberToString(s.dwRepeatAcceptTimes).c_str());
	pElem_dwRepeatAcceptTimes->SetAttribute("comment", ToUTF8Ptr("当前有效接任务次数"));
	if(rElement.LinkEndChild(pElem_dwRepeatAcceptTimes.get()) != NULL)
		pElem_dwRepeatAcceptTimes.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoleTaskInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		RoleTaskInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRoleTaskInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("RoleTaskInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SVarsDBInfo::SVarsDBInfo() : qwRoleID(0), byServerType(0), wVar(0), qwValue(0), dwExpired(0) { }

SVarsDBInfo::SVarsDBInfo(UINT64 qwRoleID_, UINT8 byServerType_, UINT16 wVar_, UINT64 qwValue_, UINT32 dwExpired_)
			: qwRoleID(qwRoleID_), byServerType(byServerType_), wVar(wVar_), qwValue(qwValue_), dwExpired(dwExpired_) { }

CInArchive& operator>>(CInArchive& src, SVarsDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.byServerType;
	src >> s.wVar;
	src >> s.qwValue;
	src >> s.dwExpired;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SVarsDBInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.byServerType;
	src << s.wVar;
	src << s.qwValue;
	src << s.dwExpired;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SVarsDBInfo& s)
{
	if(strcmp(rElement.Value(), "SVarsDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SVarsDBInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byServerType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byServerType") != 0)
	{
		LOG_CRI << "Attribute: name is not byServerType!";
		return false;
	}
	const char* pszVal_byServerType = pElemChild->Attribute("value");
	if(pszVal_byServerType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byServerType, s.byServerType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wVar is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wVar") != 0)
	{
		LOG_CRI << "Attribute: name is not wVar!";
		return false;
	}
	const char* pszVal_wVar = pElemChild->Attribute("value");
	if(pszVal_wVar == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wVar, s.wVar))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwValue") != 0)
	{
		LOG_CRI << "Attribute: name is not qwValue!";
		return false;
	}
	const char* pszVal_qwValue = pElemChild->Attribute("value");
	if(pszVal_qwValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwValue, s.qwValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwExpired is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwExpired") != 0)
	{
		LOG_CRI << "Attribute: name is not dwExpired!";
		return false;
	}
	const char* pszVal_dwExpired = pElemChild->Attribute("value");
	if(pszVal_dwExpired == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwExpired, s.dwExpired))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SVarsDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SVarsDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家变量数据"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家RoleId"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_byServerType(new TiXmlElement("UINT8"));
	if(pElem_byServerType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byServerType->SetAttribute("name", "byServerType");
	pElem_byServerType->SetAttribute("value", NumberToString(s.byServerType).c_str());
	pElem_byServerType->SetAttribute("comment", ToUTF8Ptr("服务器类型"));
	if(rElement.LinkEndChild(pElem_byServerType.get()) != NULL)
		pElem_byServerType.release();
	unique_ptr<TiXmlElement> pElem_wVar(new TiXmlElement("UINT16"));
	if(pElem_wVar == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wVar->SetAttribute("name", "wVar");
	pElem_wVar->SetAttribute("value", NumberToString(s.wVar).c_str());
	pElem_wVar->SetAttribute("comment", ToUTF8Ptr("变量ID"));
	if(rElement.LinkEndChild(pElem_wVar.get()) != NULL)
		pElem_wVar.release();
	unique_ptr<TiXmlElement> pElem_qwValue(new TiXmlElement("UINT64"));
	if(pElem_qwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwValue->SetAttribute("name", "qwValue");
	pElem_qwValue->SetAttribute("value", NumberToString(s.qwValue).c_str());
	pElem_qwValue->SetAttribute("comment", ToUTF8Ptr("变量值"));
	if(rElement.LinkEndChild(pElem_qwValue.get()) != NULL)
		pElem_qwValue.release();
	unique_ptr<TiXmlElement> pElem_dwExpired(new TiXmlElement("UINT32"));
	if(pElem_dwExpired == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExpired->SetAttribute("name", "dwExpired");
	pElem_dwExpired->SetAttribute("value", NumberToString(s.dwExpired).c_str());
	pElem_dwExpired->SetAttribute("comment", ToUTF8Ptr("过期时间"));
	if(rElement.LinkEndChild(pElem_dwExpired.get()) != NULL)
		pElem_dwExpired.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecVarsDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SVarsDBInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecVarsDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SVarsDBInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SGameVarsDBInfo::SGameVarsDBInfo() : byServerType(0), wVar(0), qwValue(0), dwExpired(0) { }

SGameVarsDBInfo::SGameVarsDBInfo(UINT8 byServerType_, UINT16 wVar_, UINT64 qwValue_, UINT32 dwExpired_) : byServerType(byServerType_), wVar(wVar_), qwValue(qwValue_), dwExpired(dwExpired_) { }

CInArchive& operator>>(CInArchive& src, SGameVarsDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byServerType;
	src >> s.wVar;
	src >> s.qwValue;
	src >> s.dwExpired;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGameVarsDBInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byServerType;
	src << s.wVar;
	src << s.qwValue;
	src << s.dwExpired;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGameVarsDBInfo& s)
{
	if(strcmp(rElement.Value(), "SGameVarsDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SGameVarsDBInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byServerType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byServerType") != 0)
	{
		LOG_CRI << "Attribute: name is not byServerType!";
		return false;
	}
	const char* pszVal_byServerType = pElemChild->Attribute("value");
	if(pszVal_byServerType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byServerType, s.byServerType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wVar is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wVar") != 0)
	{
		LOG_CRI << "Attribute: name is not wVar!";
		return false;
	}
	const char* pszVal_wVar = pElemChild->Attribute("value");
	if(pszVal_wVar == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wVar, s.wVar))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwValue") != 0)
	{
		LOG_CRI << "Attribute: name is not qwValue!";
		return false;
	}
	const char* pszVal_qwValue = pElemChild->Attribute("value");
	if(pszVal_qwValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwValue, s.qwValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwExpired is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwExpired") != 0)
	{
		LOG_CRI << "Attribute: name is not dwExpired!";
		return false;
	}
	const char* pszVal_dwExpired = pElemChild->Attribute("value");
	if(pszVal_dwExpired == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwExpired, s.dwExpired))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGameVarsDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGameVarsDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("系统变量数据"));
	unique_ptr<TiXmlElement> pElem_byServerType(new TiXmlElement("UINT8"));
	if(pElem_byServerType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byServerType->SetAttribute("name", "byServerType");
	pElem_byServerType->SetAttribute("value", NumberToString(s.byServerType).c_str());
	pElem_byServerType->SetAttribute("comment", ToUTF8Ptr("服务器类型"));
	if(rElement.LinkEndChild(pElem_byServerType.get()) != NULL)
		pElem_byServerType.release();
	unique_ptr<TiXmlElement> pElem_wVar(new TiXmlElement("UINT16"));
	if(pElem_wVar == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wVar->SetAttribute("name", "wVar");
	pElem_wVar->SetAttribute("value", NumberToString(s.wVar).c_str());
	pElem_wVar->SetAttribute("comment", ToUTF8Ptr("变量ID"));
	if(rElement.LinkEndChild(pElem_wVar.get()) != NULL)
		pElem_wVar.release();
	unique_ptr<TiXmlElement> pElem_qwValue(new TiXmlElement("UINT64"));
	if(pElem_qwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwValue->SetAttribute("name", "qwValue");
	pElem_qwValue->SetAttribute("value", NumberToString(s.qwValue).c_str());
	pElem_qwValue->SetAttribute("comment", ToUTF8Ptr("变量值"));
	if(rElement.LinkEndChild(pElem_qwValue.get()) != NULL)
		pElem_qwValue.release();
	unique_ptr<TiXmlElement> pElem_dwExpired(new TiXmlElement("UINT32"));
	if(pElem_dwExpired == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExpired->SetAttribute("name", "dwExpired");
	pElem_dwExpired->SetAttribute("value", NumberToString(s.dwExpired).c_str());
	pElem_dwExpired->SetAttribute("comment", ToUTF8Ptr("过期时间"));
	if(rElement.LinkEndChild(pElem_dwExpired.get()) != NULL)
		pElem_dwExpired.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGameVarsDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGameVarsDBInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecGameVarsDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGameVarsDBInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SRoleSlotsInfo::SRoleSlotsInfo() : qwRoleID(0), qwOwnerID(0), eStoreType((NItemProt::EStoreType)0), wMaxSlot(0), wMaxAvaliableSlot(0) { }

SRoleSlotsInfo::SRoleSlotsInfo(UINT64 qwRoleID_, UINT64 qwOwnerID_, NItemProt::EStoreType eStoreType_, UINT16 wMaxSlot_, UINT16 wMaxAvaliableSlot_)
			: qwRoleID(qwRoleID_), qwOwnerID(qwOwnerID_), eStoreType(eStoreType_), wMaxSlot(wMaxSlot_), wMaxAvaliableSlot(wMaxAvaliableSlot_) { }

CInArchive& operator>>(CInArchive& src, SRoleSlotsInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.qwOwnerID;
	src >> (UINT8&)s.eStoreType;
	src >> s.wMaxSlot;
	src >> s.wMaxAvaliableSlot;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoleSlotsInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.qwOwnerID;
	src << (UINT8&)s.eStoreType;
	src << s.wMaxSlot;
	src << s.wMaxAvaliableSlot;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoleSlotsInfo& s)
{
	if(strcmp(rElement.Value(), "SRoleSlotsInfo") != 0)
	{
		LOG_CRI << "rElement is not SRoleSlotsInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwOwnerID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwOwnerID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwOwnerID!";
		return false;
	}
	const char* pszVal_qwOwnerID = pElemChild->Attribute("value");
	if(pszVal_qwOwnerID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwOwnerID, s.qwOwnerID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eStoreType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::EStoreType") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::EStoreType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eStoreType") != 0)
	{
		LOG_CRI << "Attribute: name is not eStoreType!";
		return false;
	}
	const char* pszVal_eStoreType = pElemChild->Attribute("value");
	if(pszVal_eStoreType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NItemProt::EnumStrToVal(pszVal_eStoreType, s.eStoreType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMaxSlot is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMaxSlot") != 0)
	{
		LOG_CRI << "Attribute: name is not wMaxSlot!";
		return false;
	}
	const char* pszVal_wMaxSlot = pElemChild->Attribute("value");
	if(pszVal_wMaxSlot == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMaxSlot, s.wMaxSlot))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMaxAvaliableSlot is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMaxAvaliableSlot") != 0)
	{
		LOG_CRI << "Attribute: name is not wMaxAvaliableSlot!";
		return false;
	}
	const char* pszVal_wMaxAvaliableSlot = pElemChild->Attribute("value");
	if(pszVal_wMaxAvaliableSlot == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMaxAvaliableSlot, s.wMaxAvaliableSlot))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRoleSlotsInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoleSlotsInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("EDataType:eTypeSlotsInfo:玩家各种槽数据"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家RoleID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_qwOwnerID(new TiXmlElement("UINT64"));
	if(pElem_qwOwnerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwnerID->SetAttribute("name", "qwOwnerID");
	pElem_qwOwnerID->SetAttribute("value", NumberToString(s.qwOwnerID).c_str());
	pElem_qwOwnerID->SetAttribute("comment", ToUTF8Ptr("槽拥有者ID"));
	if(rElement.LinkEndChild(pElem_qwOwnerID.get()) != NULL)
		pElem_qwOwnerID.release();
	unique_ptr<TiXmlElement> pElem_eStoreType(new TiXmlElement("ItemProt::EStoreType"));
	if(pElem_eStoreType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eStoreType->SetAttribute("name", "eStoreType");
	const char* pszEnum_eStoreType = NItemProt::EnumValToStr(s.eStoreType);
	if(pszEnum_eStoreType == NULL)
	{
		LOG_CRI << "EnumValToStr for eStoreType fails!";
		return false;
	}
	pElem_eStoreType->SetAttribute("value", pszEnum_eStoreType);
	pElem_eStoreType->SetAttribute("comment", ToUTF8Ptr("槽类型"));
	if(rElement.LinkEndChild(pElem_eStoreType.get()) != NULL)
		pElem_eStoreType.release();
	unique_ptr<TiXmlElement> pElem_wMaxSlot(new TiXmlElement("UINT16"));
	if(pElem_wMaxSlot == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMaxSlot->SetAttribute("name", "wMaxSlot");
	pElem_wMaxSlot->SetAttribute("value", NumberToString(s.wMaxSlot).c_str());
	pElem_wMaxSlot->SetAttribute("comment", ToUTF8Ptr("槽允许的最大数量"));
	if(rElement.LinkEndChild(pElem_wMaxSlot.get()) != NULL)
		pElem_wMaxSlot.release();
	unique_ptr<TiXmlElement> pElem_wMaxAvaliableSlot(new TiXmlElement("UINT16"));
	if(pElem_wMaxAvaliableSlot == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMaxAvaliableSlot->SetAttribute("name", "wMaxAvaliableSlot");
	pElem_wMaxAvaliableSlot->SetAttribute("value", NumberToString(s.wMaxAvaliableSlot).c_str());
	pElem_wMaxAvaliableSlot->SetAttribute("comment", ToUTF8Ptr("槽当前的最大数量"));
	if(rElement.LinkEndChild(pElem_wMaxAvaliableSlot.get()) != NULL)
		pElem_wMaxAvaliableSlot.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoleSlotsInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRoleSlotsInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRoleSlotsInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRoleSlotsInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SFormationInfo::SFormationInfo() : wFormationID(0), bySelected(0) { }

SFormationInfo::SFormationInfo(UINT16 wFormationID_, UINT8 bySelected_) : wFormationID(wFormationID_), bySelected(bySelected_) { }

CInArchive& operator>>(CInArchive& src, SFormationInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wFormationID;
	src >> s.bySelected;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFormationInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wFormationID;
	src << s.bySelected;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFormationInfo& s)
{
	if(strcmp(rElement.Value(), "SFormationInfo") != 0)
	{
		LOG_CRI << "rElement is not SFormationInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wFormationID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFormationID") != 0)
	{
		LOG_CRI << "Attribute: name is not wFormationID!";
		return false;
	}
	const char* pszVal_wFormationID = pElemChild->Attribute("value");
	if(pszVal_wFormationID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFormationID, s.wFormationID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySelected is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySelected") != 0)
	{
		LOG_CRI << "Attribute: name is not bySelected!";
		return false;
	}
	const char* pszVal_bySelected = pElemChild->Attribute("value");
	if(pszVal_bySelected == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySelected, s.bySelected))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFormationInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFormationInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("阵型信息"));
	unique_ptr<TiXmlElement> pElem_wFormationID(new TiXmlElement("UINT16"));
	if(pElem_wFormationID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFormationID->SetAttribute("name", "wFormationID");
	pElem_wFormationID->SetAttribute("value", NumberToString(s.wFormationID).c_str());
	pElem_wFormationID->SetAttribute("comment", ToUTF8Ptr("阵型ID"));
	if(rElement.LinkEndChild(pElem_wFormationID.get()) != NULL)
		pElem_wFormationID.release();
	unique_ptr<TiXmlElement> pElem_bySelected(new TiXmlElement("UINT8"));
	if(pElem_bySelected == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySelected->SetAttribute("name", "bySelected");
	pElem_bySelected->SetAttribute("value", NumberToString(s.bySelected).c_str());
	pElem_bySelected->SetAttribute("comment", ToUTF8Ptr("是否启用"));
	if(rElement.LinkEndChild(pElem_bySelected.get()) != NULL)
		pElem_bySelected.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFormationInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFormationInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecFormationInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFormationInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SPetDataInfo::SPetDataInfo() : wPetID(0), bySelected(0), byLevel(0), dwExp(0) { }

SPetDataInfo::SPetDataInfo(UINT16 wPetID_, UINT8 bySelected_, UINT8 byLevel_, UINT32 dwExp_) : wPetID(wPetID_), bySelected(bySelected_), byLevel(byLevel_), dwExp(dwExp_) { }

CInArchive& operator>>(CInArchive& src, SPetDataInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wPetID;
	src >> s.bySelected;
	src >> s.byLevel;
	src >> s.dwExp;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPetDataInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wPetID;
	src << s.bySelected;
	src << s.byLevel;
	src << s.dwExp;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPetDataInfo& s)
{
	if(strcmp(rElement.Value(), "SPetDataInfo") != 0)
	{
		LOG_CRI << "rElement is not SPetDataInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPetID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPetID") != 0)
	{
		LOG_CRI << "Attribute: name is not wPetID!";
		return false;
	}
	const char* pszVal_wPetID = pElemChild->Attribute("value");
	if(pszVal_wPetID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPetID, s.wPetID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySelected is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySelected") != 0)
	{
		LOG_CRI << "Attribute: name is not bySelected!";
		return false;
	}
	const char* pszVal_bySelected = pElemChild->Attribute("value");
	if(pszVal_bySelected == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySelected, s.bySelected))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byLevel!";
		return false;
	}
	const char* pszVal_byLevel = pElemChild->Attribute("value");
	if(pszVal_byLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLevel, s.byLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwExp!";
		return false;
	}
	const char* pszVal_dwExp = pElemChild->Attribute("value");
	if(pszVal_dwExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwExp, s.dwExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPetDataInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPetDataInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("阵灵信息"));
	unique_ptr<TiXmlElement> pElem_wPetID(new TiXmlElement("UINT16"));
	if(pElem_wPetID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPetID->SetAttribute("name", "wPetID");
	pElem_wPetID->SetAttribute("value", NumberToString(s.wPetID).c_str());
	pElem_wPetID->SetAttribute("comment", ToUTF8Ptr("阵灵ID"));
	if(rElement.LinkEndChild(pElem_wPetID.get()) != NULL)
		pElem_wPetID.release();
	unique_ptr<TiXmlElement> pElem_bySelected(new TiXmlElement("UINT8"));
	if(pElem_bySelected == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySelected->SetAttribute("name", "bySelected");
	pElem_bySelected->SetAttribute("value", NumberToString(s.bySelected).c_str());
	pElem_bySelected->SetAttribute("comment", ToUTF8Ptr("是否启用: 0-未启用 1-出战跟随 2-出战不跟随"));
	if(rElement.LinkEndChild(pElem_bySelected.get()) != NULL)
		pElem_bySelected.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("阵灵等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_dwExp(new TiXmlElement("UINT32"));
	if(pElem_dwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExp->SetAttribute("name", "dwExp");
	pElem_dwExp->SetAttribute("value", NumberToString(s.dwExp).c_str());
	pElem_dwExp->SetAttribute("comment", ToUTF8Ptr("阵灵经验"));
	if(rElement.LinkEndChild(pElem_dwExp.get()) != NULL)
		pElem_dwExp.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPetDataInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPetDataInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecPetDataInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPetDataInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SRolePetInfo::SRolePetInfo() : dwExp(0), byLevel(0), dwSpirit(0) { }

SRolePetInfo::SRolePetInfo(UINT32 dwExp_, UINT8 byLevel_, UINT32 dwSpirit_) : dwExp(dwExp_), byLevel(byLevel_), dwSpirit(dwSpirit_) { }

CInArchive& operator>>(CInArchive& src, SRolePetInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwExp;
	src >> s.byLevel;
	src >> s.dwSpirit;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRolePetInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwExp;
	src << s.byLevel;
	src << s.dwSpirit;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRolePetInfo& s)
{
	if(strcmp(rElement.Value(), "SRolePetInfo") != 0)
	{
		LOG_CRI << "rElement is not SRolePetInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwExp!";
		return false;
	}
	const char* pszVal_dwExp = pElemChild->Attribute("value");
	if(pszVal_dwExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwExp, s.dwExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byLevel!";
		return false;
	}
	const char* pszVal_byLevel = pElemChild->Attribute("value");
	if(pszVal_byLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLevel, s.byLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSpirit is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSpirit") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSpirit!";
		return false;
	}
	const char* pszVal_dwSpirit = pElemChild->Attribute("value");
	if(pszVal_dwSpirit == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSpirit, s.dwSpirit))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRolePetInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRolePetInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("阵灵全局信息"));
	unique_ptr<TiXmlElement> pElem_dwExp(new TiXmlElement("UINT32"));
	if(pElem_dwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExp->SetAttribute("name", "dwExp");
	pElem_dwExp->SetAttribute("value", NumberToString(s.dwExp).c_str());
	pElem_dwExp->SetAttribute("comment", ToUTF8Ptr("阵灵经验"));
	if(rElement.LinkEndChild(pElem_dwExp.get()) != NULL)
		pElem_dwExp.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("阵灵等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_dwSpirit(new TiXmlElement("UINT32"));
	if(pElem_dwSpirit == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSpirit->SetAttribute("name", "dwSpirit");
	pElem_dwSpirit->SetAttribute("value", NumberToString(s.dwSpirit).c_str());
	pElem_dwSpirit->SetAttribute("comment", ToUTF8Ptr("阵灵灵力值"));
	if(rElement.LinkEndChild(pElem_dwSpirit.get()) != NULL)
		pElem_dwSpirit.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRolePetInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRolePetInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRolePetInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRolePetInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SBeastSoulInfo::SBeastSoulInfo() : eType((EBeastSoulType)0), byRank(0), byLevel(0) { }

SBeastSoulInfo::SBeastSoulInfo(EBeastSoulType eType_, UINT8 byRank_, UINT8 byLevel_) : eType(eType_), byRank(byRank_), byLevel(byLevel_) { }

CInArchive& operator>>(CInArchive& src, SBeastSoulInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eType;
	src >> s.byRank;
	src >> s.byLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBeastSoulInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eType;
	src << s.byRank;
	src << s.byLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBeastSoulInfo& s)
{
	if(strcmp(rElement.Value(), "SBeastSoulInfo") != 0)
	{
		LOG_CRI << "rElement is not SBeastSoulInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBeastSoulType") != 0)
	{
		LOG_CRI << "pElemChild is not EBeastSoulType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eType") != 0)
	{
		LOG_CRI << "Attribute: name is not eType!";
		return false;
	}
	const char* pszVal_eType = pElemChild->Attribute("value");
	if(pszVal_eType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eType, s.eType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRank") != 0)
	{
		LOG_CRI << "Attribute: name is not byRank!";
		return false;
	}
	const char* pszVal_byRank = pElemChild->Attribute("value");
	if(pszVal_byRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRank, s.byRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byLevel!";
		return false;
	}
	const char* pszVal_byLevel = pElemChild->Attribute("value");
	if(pszVal_byLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLevel, s.byLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBeastSoulInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBeastSoulInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("兽魂信息"));
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("EBeastSoulType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBeastSoulType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("兽魂类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_byRank(new TiXmlElement("UINT8"));
	if(pElem_byRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRank->SetAttribute("name", "byRank");
	pElem_byRank->SetAttribute("value", NumberToString(s.byRank).c_str());
	pElem_byRank->SetAttribute("comment", ToUTF8Ptr("兽魂星图等级"));
	if(rElement.LinkEndChild(pElem_byRank.get()) != NULL)
		pElem_byRank.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("兽魂星魂等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBeastSoulInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBeastSoulInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecBeastSoulInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBeastSoulInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SSoulSpaceInfo::SSoulSpaceInfo() : qwRoleID(0), dwSoulSpaceID(0), dwSoulSpaceLevel(0) { }

SSoulSpaceInfo::SSoulSpaceInfo(UINT64 qwRoleID_, UINT64 dwSoulSpaceID_, UINT64 dwSoulSpaceLevel_) : qwRoleID(qwRoleID_), dwSoulSpaceID(dwSoulSpaceID_), dwSoulSpaceLevel(dwSoulSpaceLevel_) { }

CInArchive& operator>>(CInArchive& src, SSoulSpaceInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.dwSoulSpaceID;
	src >> s.dwSoulSpaceLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSoulSpaceInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.dwSoulSpaceID;
	src << s.dwSoulSpaceLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSoulSpaceInfo& s)
{
	if(strcmp(rElement.Value(), "SSoulSpaceInfo") != 0)
	{
		LOG_CRI << "rElement is not SSoulSpaceInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulSpaceID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulSpaceID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulSpaceID!";
		return false;
	}
	const char* pszVal_dwSoulSpaceID = pElemChild->Attribute("value");
	if(pszVal_dwSoulSpaceID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulSpaceID, s.dwSoulSpaceID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulSpaceLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulSpaceLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulSpaceLevel!";
		return false;
	}
	const char* pszVal_dwSoulSpaceLevel = pElemChild->Attribute("value");
	if(pszVal_dwSoulSpaceLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulSpaceLevel, s.dwSoulSpaceLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSoulSpaceInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSoulSpaceInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家魄空间信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("角色ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_dwSoulSpaceID(new TiXmlElement("UINT64"));
	if(pElem_dwSoulSpaceID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulSpaceID->SetAttribute("name", "dwSoulSpaceID");
	pElem_dwSoulSpaceID->SetAttribute("value", NumberToString(s.dwSoulSpaceID).c_str());
	pElem_dwSoulSpaceID->SetAttribute("comment", ToUTF8Ptr("魄空间ID"));
	if(rElement.LinkEndChild(pElem_dwSoulSpaceID.get()) != NULL)
		pElem_dwSoulSpaceID.release();
	unique_ptr<TiXmlElement> pElem_dwSoulSpaceLevel(new TiXmlElement("UINT64"));
	if(pElem_dwSoulSpaceLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulSpaceLevel->SetAttribute("name", "dwSoulSpaceLevel");
	pElem_dwSoulSpaceLevel->SetAttribute("value", NumberToString(s.dwSoulSpaceLevel).c_str());
	pElem_dwSoulSpaceLevel->SetAttribute("comment", ToUTF8Ptr("魄空间等级"));
	if(rElement.LinkEndChild(pElem_dwSoulSpaceLevel.get()) != NULL)
		pElem_dwSoulSpaceLevel.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSoulSpaceInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSoulSpaceInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecSoulSpaceInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSoulSpaceInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SRoleArenaInfo::SRoleArenaInfo() : dwLastAwardTimer(0), dwCDTime(0), dwLadderCDTime(0) { }

SRoleArenaInfo::SRoleArenaInfo(UINT32 dwLastAwardTimer_, const NArenaGS::TVecArenaAward& vecAwards_, UINT32 dwCDTime_, UINT32 dwLadderCDTime_, const NArenaGS::TVecFlushFither& vecFlushFigter_)
			: dwLastAwardTimer(dwLastAwardTimer_), vecAwards(vecAwards_), dwCDTime(dwCDTime_), dwLadderCDTime(dwLadderCDTime_), vecFlushFigter(vecFlushFigter_) { }

SRoleArenaInfo::SRoleArenaInfo(SRoleArenaInfo&& src) : dwLastAwardTimer(src.dwLastAwardTimer), vecAwards(move(src.vecAwards)), dwCDTime(src.dwCDTime), dwLadderCDTime(src.dwLadderCDTime), vecFlushFigter(move(src.vecFlushFigter)) { }

SRoleArenaInfo& SRoleArenaInfo::operator=(SRoleArenaInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SRoleArenaInfo();
		new (this) SRoleArenaInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRoleArenaInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwLastAwardTimer;
	src >> s.vecAwards;
	src >> s.dwCDTime;
	src >> s.dwLadderCDTime;
	src >> s.vecFlushFigter;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoleArenaInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwLastAwardTimer;
	src << s.vecAwards;
	src << s.dwCDTime;
	src << s.dwLadderCDTime;
	src << s.vecFlushFigter;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoleArenaInfo& s)
{
	if(strcmp(rElement.Value(), "SRoleArenaInfo") != 0)
	{
		LOG_CRI << "rElement is not SRoleArenaInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLastAwardTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastAwardTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastAwardTimer!";
		return false;
	}
	const char* pszVal_dwLastAwardTimer = pElemChild->Attribute("value");
	if(pszVal_dwLastAwardTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastAwardTimer, s.dwLastAwardTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecAwards is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ArenaGS::TVecArenaAward") != 0)
	{
		LOG_CRI << "pElemChild is not ArenaGS::TVecArenaAward!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecAwards") != 0)
	{
		LOG_CRI << "Attribute: name is not vecAwards!";
		return false;
	}
	if(!NArenaGS::VectorFromXML(*pElemChild, s.vecAwards))
	{
		LOG_CRI << "VectorFromXML for vecAwards fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCDTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCDTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCDTime!";
		return false;
	}
	const char* pszVal_dwCDTime = pElemChild->Attribute("value");
	if(pszVal_dwCDTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCDTime, s.dwCDTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLadderCDTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLadderCDTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLadderCDTime!";
		return false;
	}
	const char* pszVal_dwLadderCDTime = pElemChild->Attribute("value");
	if(pszVal_dwLadderCDTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLadderCDTime, s.dwLadderCDTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFlushFigter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ArenaGS::TVecFlushFither") != 0)
	{
		LOG_CRI << "pElemChild is not ArenaGS::TVecFlushFither!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFlushFigter") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFlushFigter!";
		return false;
	}
	if(!NArenaGS::VectorFromXML(*pElemChild, s.vecFlushFigter))
	{
		LOG_CRI << "VectorFromXML for vecFlushFigter fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRoleArenaInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoleArenaInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("EDataType:eTypeArena:玩家斗剑信息"));
	unique_ptr<TiXmlElement> pElem_dwLastAwardTimer(new TiXmlElement("UINT32"));
	if(pElem_dwLastAwardTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastAwardTimer->SetAttribute("name", "dwLastAwardTimer");
	pElem_dwLastAwardTimer->SetAttribute("value", NumberToString(s.dwLastAwardTimer).c_str());
	pElem_dwLastAwardTimer->SetAttribute("comment", ToUTF8Ptr("上次刷的那次奖励，记录系统计算时间"));
	if(rElement.LinkEndChild(pElem_dwLastAwardTimer.get()) != NULL)
		pElem_dwLastAwardTimer.release();
	unique_ptr<TiXmlElement> pElem_vecAwards(new TiXmlElement("ArenaGS::TVecArenaAward"));
	if(pElem_vecAwards == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecAwards->SetAttribute("name", "vecAwards");
	if(!NArenaGS::VectorToXML(s.vecAwards, *pElem_vecAwards))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecAwards->SetAttribute("comment", ToUTF8Ptr("奖励包状态"));
	if(rElement.LinkEndChild(pElem_vecAwards.get()) != NULL)
		pElem_vecAwards.release();
	unique_ptr<TiXmlElement> pElem_dwCDTime(new TiXmlElement("UINT32"));
	if(pElem_dwCDTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCDTime->SetAttribute("name", "dwCDTime");
	pElem_dwCDTime->SetAttribute("value", NumberToString(s.dwCDTime).c_str());
	pElem_dwCDTime->SetAttribute("comment", ToUTF8Ptr("战斗冷却到期时间戳"));
	if(rElement.LinkEndChild(pElem_dwCDTime.get()) != NULL)
		pElem_dwCDTime.release();
	unique_ptr<TiXmlElement> pElem_dwLadderCDTime(new TiXmlElement("UINT32"));
	if(pElem_dwLadderCDTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLadderCDTime->SetAttribute("name", "dwLadderCDTime");
	pElem_dwLadderCDTime->SetAttribute("value", NumberToString(s.dwLadderCDTime).c_str());
	pElem_dwLadderCDTime->SetAttribute("comment", ToUTF8Ptr("天梯战斗冷却到期时间戳"));
	if(rElement.LinkEndChild(pElem_dwLadderCDTime.get()) != NULL)
		pElem_dwLadderCDTime.release();
	unique_ptr<TiXmlElement> pElem_vecFlushFigter(new TiXmlElement("ArenaGS::TVecFlushFither"));
	if(pElem_vecFlushFigter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFlushFigter->SetAttribute("name", "vecFlushFigter");
	if(!NArenaGS::VectorToXML(s.vecFlushFigter, *pElem_vecFlushFigter))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFlushFigter->SetAttribute("comment", ToUTF8Ptr("最近刷的对手"));
	if(rElement.LinkEndChild(pElem_vecFlushFigter.get()) != NULL)
		pElem_vecFlushFigter.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoleArenaInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRoleArenaInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRoleArenaInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRoleArenaInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SBattleRePort::SBattleRePort() : qwRoleID(0), qwBattleID(0), qwAttackID(0), eActionType((EBattleActionType)0), eType((EBattleReportType)0), 
			eSuc((EBattleActionType)0), dwTime(0), dwParam1(0), dwParam2(0), dwParam3(0), 
			dwIndex(0) { }

SBattleRePort::SBattleRePort(SBattleRePort&& src) : qwRoleID(src.qwRoleID), qwBattleID(src.qwBattleID), qwAttackID(src.qwAttackID), strAttackID(move(src.strAttackID)), eActionType(src.eActionType), 
			eType(src.eType), eSuc(src.eSuc), dwTime(src.dwTime), dwParam1(src.dwParam1), dwParam2(src.dwParam2), 
			dwParam3(src.dwParam3), dwIndex(src.dwIndex) { }

SBattleRePort& SBattleRePort::operator=(SBattleRePort&& rhs)
{
	if(this != &rhs)
	{
		this->~SBattleRePort();
		new (this) SBattleRePort(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBattleRePort& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.qwBattleID;
	src >> s.qwAttackID;
	src >> s.strAttackID;
	src >> (UINT8&)s.eActionType;
	src >> (UINT8&)s.eType;
	src >> (UINT8&)s.eSuc;
	src >> s.dwTime;
	src >> s.dwParam1;
	src >> s.dwParam2;
	src >> s.dwParam3;
	src >> s.dwIndex;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleRePort& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.qwBattleID;
	src << s.qwAttackID;
	src << s.strAttackID;
	src << (UINT8&)s.eActionType;
	src << (UINT8&)s.eType;
	src << (UINT8&)s.eSuc;
	src << s.dwTime;
	src << s.dwParam1;
	src << s.dwParam2;
	src << s.dwParam3;
	src << s.dwIndex;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleRePort& s)
{
	if(strcmp(rElement.Value(), "SBattleRePort") != 0)
	{
		LOG_CRI << "rElement is not SBattleRePort!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwBattleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwBattleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwBattleID!";
		return false;
	}
	const char* pszVal_qwBattleID = pElemChild->Attribute("value");
	if(pszVal_qwBattleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwBattleID, s.qwBattleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwAttackID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwAttackID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwAttackID!";
		return false;
	}
	const char* pszVal_qwAttackID = pElemChild->Attribute("value");
	if(pszVal_qwAttackID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwAttackID, s.qwAttackID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strAttackID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strAttackID") != 0)
	{
		LOG_CRI << "Attribute: name is not strAttackID!";
		return false;
	}
	const char* pszVal_strAttackID = pElemChild->Attribute("value");
	if(pszVal_strAttackID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strAttackID = pszVal_strAttackID;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eActionType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBattleActionType") != 0)
	{
		LOG_CRI << "pElemChild is not EBattleActionType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eActionType") != 0)
	{
		LOG_CRI << "Attribute: name is not eActionType!";
		return false;
	}
	const char* pszVal_eActionType = pElemChild->Attribute("value");
	if(pszVal_eActionType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eActionType, s.eActionType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBattleReportType") != 0)
	{
		LOG_CRI << "pElemChild is not EBattleReportType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eType") != 0)
	{
		LOG_CRI << "Attribute: name is not eType!";
		return false;
	}
	const char* pszVal_eType = pElemChild->Attribute("value");
	if(pszVal_eType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eType, s.eType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSuc is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBattleActionType") != 0)
	{
		LOG_CRI << "pElemChild is not EBattleActionType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSuc") != 0)
	{
		LOG_CRI << "Attribute: name is not eSuc!";
		return false;
	}
	const char* pszVal_eSuc = pElemChild->Attribute("value");
	if(pszVal_eSuc == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eSuc, s.eSuc))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTime!";
		return false;
	}
	const char* pszVal_dwTime = pElemChild->Attribute("value");
	if(pszVal_dwTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTime, s.dwTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwParam1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwParam1") != 0)
	{
		LOG_CRI << "Attribute: name is not dwParam1!";
		return false;
	}
	const char* pszVal_dwParam1 = pElemChild->Attribute("value");
	if(pszVal_dwParam1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwParam1, s.dwParam1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwParam2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwParam2") != 0)
	{
		LOG_CRI << "Attribute: name is not dwParam2!";
		return false;
	}
	const char* pszVal_dwParam2 = pElemChild->Attribute("value");
	if(pszVal_dwParam2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwParam2, s.dwParam2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwParam3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwParam3") != 0)
	{
		LOG_CRI << "Attribute: name is not dwParam3!";
		return false;
	}
	const char* pszVal_dwParam3 = pElemChild->Attribute("value");
	if(pszVal_dwParam3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwParam3, s.dwParam3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwIndex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwIndex") != 0)
	{
		LOG_CRI << "Attribute: name is not dwIndex!";
		return false;
	}
	const char* pszVal_dwIndex = pElemChild->Attribute("value");
	if(pszVal_dwIndex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwIndex, s.dwIndex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleRePort& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleRePort");
	rElement.SetAttribute("type", ToUTF8Ptr("战报保存"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_qwBattleID(new TiXmlElement("UINT64"));
	if(pElem_qwBattleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwBattleID->SetAttribute("name", "qwBattleID");
	pElem_qwBattleID->SetAttribute("value", NumberToString(s.qwBattleID).c_str());
	pElem_qwBattleID->SetAttribute("comment", ToUTF8Ptr("战报Id"));
	if(rElement.LinkEndChild(pElem_qwBattleID.get()) != NULL)
		pElem_qwBattleID.release();
	unique_ptr<TiXmlElement> pElem_qwAttackID(new TiXmlElement("UINT64"));
	if(pElem_qwAttackID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwAttackID->SetAttribute("name", "qwAttackID");
	pElem_qwAttackID->SetAttribute("value", NumberToString(s.qwAttackID).c_str());
	pElem_qwAttackID->SetAttribute("comment", ToUTF8Ptr("对方ID"));
	if(rElement.LinkEndChild(pElem_qwAttackID.get()) != NULL)
		pElem_qwAttackID.release();
	unique_ptr<TiXmlElement> pElem_strAttackID(new TiXmlElement("string"));
	if(pElem_strAttackID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strAttackID->SetAttribute("name", "strAttackID");
	pElem_strAttackID->SetAttribute("value", s.strAttackID.c_str());
	pElem_strAttackID->SetAttribute("comment", ToUTF8Ptr("对方名字"));
	if(rElement.LinkEndChild(pElem_strAttackID.get()) != NULL)
		pElem_strAttackID.release();
	unique_ptr<TiXmlElement> pElem_eActionType(new TiXmlElement("EBattleActionType"));
	if(pElem_eActionType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eActionType->SetAttribute("name", "eActionType");
	const char* pszEnum_eActionType = EnumValToStr(s.eActionType);
	if(pszEnum_eActionType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBattleActionType fails!";
		return false;
	}
	pElem_eActionType->SetAttribute("value", pszEnum_eActionType);
	pElem_eActionType->SetAttribute("comment", ToUTF8Ptr("玩家战斗方式"));
	if(rElement.LinkEndChild(pElem_eActionType.get()) != NULL)
		pElem_eActionType.release();
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("EBattleReportType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBattleReportType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("战报类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_eSuc(new TiXmlElement("EBattleActionType"));
	if(pElem_eSuc == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSuc->SetAttribute("name", "eSuc");
	const char* pszEnum_eSuc = EnumValToStr(s.eSuc);
	if(pszEnum_eSuc == NULL)
	{
		LOG_CRI << "EnumValToStr for EBattleActionType fails!";
		return false;
	}
	pElem_eSuc->SetAttribute("value", pszEnum_eSuc);
	pElem_eSuc->SetAttribute("comment", ToUTF8Ptr("胜利方"));
	if(rElement.LinkEndChild(pElem_eSuc.get()) != NULL)
		pElem_eSuc.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("战报时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	unique_ptr<TiXmlElement> pElem_dwParam1(new TiXmlElement("UINT32"));
	if(pElem_dwParam1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwParam1->SetAttribute("name", "dwParam1");
	pElem_dwParam1->SetAttribute("value", NumberToString(s.dwParam1).c_str());
	pElem_dwParam1->SetAttribute("comment", ToUTF8Ptr("参数1"));
	if(rElement.LinkEndChild(pElem_dwParam1.get()) != NULL)
		pElem_dwParam1.release();
	unique_ptr<TiXmlElement> pElem_dwParam2(new TiXmlElement("UINT32"));
	if(pElem_dwParam2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwParam2->SetAttribute("name", "dwParam2");
	pElem_dwParam2->SetAttribute("value", NumberToString(s.dwParam2).c_str());
	pElem_dwParam2->SetAttribute("comment", ToUTF8Ptr("参数2"));
	if(rElement.LinkEndChild(pElem_dwParam2.get()) != NULL)
		pElem_dwParam2.release();
	unique_ptr<TiXmlElement> pElem_dwParam3(new TiXmlElement("UINT32"));
	if(pElem_dwParam3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwParam3->SetAttribute("name", "dwParam3");
	pElem_dwParam3->SetAttribute("value", NumberToString(s.dwParam3).c_str());
	pElem_dwParam3->SetAttribute("comment", ToUTF8Ptr("参数3"));
	if(rElement.LinkEndChild(pElem_dwParam3.get()) != NULL)
		pElem_dwParam3.release();
	unique_ptr<TiXmlElement> pElem_dwIndex(new TiXmlElement("UINT32"));
	if(pElem_dwIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwIndex->SetAttribute("name", "dwIndex");
	pElem_dwIndex->SetAttribute("value", NumberToString(s.dwIndex).c_str());
	pElem_dwIndex->SetAttribute("comment", ToUTF8Ptr("类型流水"));
	if(rElement.LinkEndChild(pElem_dwIndex.get()) != NULL)
		pElem_dwIndex.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleRePort& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleRePort s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecBattleRePort& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleRePort"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SDBBubbleInfo::SDBBubbleInfo() : qwRoleID(0), qwTransID(0), wMsgID(0), dwTime(0) { }

SDBBubbleInfo::SDBBubbleInfo(UINT64 qwRoleID_, UINT64 qwTransID_, UINT16 wMsgID_, UINT32 dwTime_, const TVecINT64& vecParam_, 
			const TVecString& vecString_)
			: qwRoleID(qwRoleID_), qwTransID(qwTransID_), wMsgID(wMsgID_), dwTime(dwTime_), vecParam(vecParam_), 
			vecString(vecString_) { }

CInArchive& operator>>(CInArchive& src, SDBBubbleInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.qwTransID;
	src >> s.wMsgID;
	src >> s.dwTime;
	src >> s.vecParam;
	src >> s.vecString;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDBBubbleInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.qwTransID;
	src << s.wMsgID;
	src << s.dwTime;
	src << s.vecParam;
	src << s.vecString;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDBBubbleInfo& s)
{
	if(strcmp(rElement.Value(), "SDBBubbleInfo") != 0)
	{
		LOG_CRI << "rElement is not SDBBubbleInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwTransID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwTransID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwTransID!";
		return false;
	}
	const char* pszVal_qwTransID = pElemChild->Attribute("value");
	if(pszVal_qwTransID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwTransID, s.qwTransID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMsgID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMsgID") != 0)
	{
		LOG_CRI << "Attribute: name is not wMsgID!";
		return false;
	}
	const char* pszVal_wMsgID = pElemChild->Attribute("value");
	if(pszVal_wMsgID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMsgID, s.wMsgID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTime!";
		return false;
	}
	const char* pszVal_dwTime = pElemChild->Attribute("value");
	if(pszVal_dwTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTime, s.dwTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecINT64") != 0)
	{
		LOG_CRI << "pElemChild is not TVecINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecParam") != 0)
	{
		LOG_CRI << "Attribute: name is not vecParam!";
		return false;
	}
	const char* pszText_vecParam = pElemChild->GetText();
	if(pszText_vecParam != NULL)
		SplitToNumber(pszText_vecParam, ",", s.vecParam);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecString is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecString") != 0)
	{
		LOG_CRI << "pElemChild is not TVecString!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecString") != 0)
	{
		LOG_CRI << "Attribute: name is not vecString!";
		return false;
	}
	const char* pszText_vecString = pElemChild->GetText();
	if(pszText_vecString != NULL)
		SplitToText(pszText_vecString, ",", s.vecString);
	return true;
}

bool ToXML(const SDBBubbleInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDBBubbleInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("气泡信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("角色ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_qwTransID(new TiXmlElement("UINT64"));
	if(pElem_qwTransID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwTransID->SetAttribute("name", "qwTransID");
	pElem_qwTransID->SetAttribute("value", NumberToString(s.qwTransID).c_str());
	pElem_qwTransID->SetAttribute("comment", ToUTF8Ptr("唯一流水ID"));
	if(rElement.LinkEndChild(pElem_qwTransID.get()) != NULL)
		pElem_qwTransID.release();
	unique_ptr<TiXmlElement> pElem_wMsgID(new TiXmlElement("UINT16"));
	if(pElem_wMsgID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMsgID->SetAttribute("name", "wMsgID");
	pElem_wMsgID->SetAttribute("value", NumberToString(s.wMsgID).c_str());
	pElem_wMsgID->SetAttribute("comment", ToUTF8Ptr("气泡ID"));
	if(rElement.LinkEndChild(pElem_wMsgID.get()) != NULL)
		pElem_wMsgID.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("气泡时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	unique_ptr<TiXmlElement> pElem_vecParam(new TiXmlElement("TVecINT64"));
	if(pElem_vecParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecParam->SetAttribute("name", "vecParam");
	string strText_vecParam;
	for(size_t i = 0; i < s.vecParam.size(); ++i)
	{
		if(i > 0)
			strText_vecParam += ", ";
		strText_vecParam += NumberToString(s.vecParam[i]);
	}
	unique_ptr<TiXmlText> pText_vecParam(new TiXmlText(strText_vecParam.c_str()));
	if(pText_vecParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecParam->LinkEndChild(pText_vecParam.get()) != NULL)
		pText_vecParam.release();
	pElem_vecParam->SetAttribute("comment", ToUTF8Ptr("整型变量"));
	if(rElement.LinkEndChild(pElem_vecParam.get()) != NULL)
		pElem_vecParam.release();
	unique_ptr<TiXmlElement> pElem_vecString(new TiXmlElement("TVecString"));
	if(pElem_vecString == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecString->SetAttribute("name", "vecString");
	string strText_vecString;
	for(size_t i = 0; i < s.vecString.size(); ++i)
	{
		if(i > 0)
			strText_vecString += ", ";
		strText_vecString += s.vecString[i];
	}
	unique_ptr<TiXmlText> pText_vecString(new TiXmlText(strText_vecString.c_str()));
	if(pText_vecString == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecString->LinkEndChild(pText_vecString.get()) != NULL)
		pText_vecString.release();
	pElem_vecString->SetAttribute("comment", ToUTF8Ptr("字符串型变量"));
	if(rElement.LinkEndChild(pElem_vecString.get()) != NULL)
		pElem_vecString.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDBBubbleInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDBBubbleInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecDBBubbleInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDBBubbleInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SBubbleInfo::SBubbleInfo() : wMsgID(0), wMessageID(0), byIndex(0), dwTime(0) { }

SBubbleInfo::SBubbleInfo(UINT16 wMsgID_, UINT16 wMessageID_, UINT8 byIndex_, UINT32 dwTime_, const TVecINT64& vecParam_, 
			const TVecString& vecString_)
			: wMsgID(wMsgID_), wMessageID(wMessageID_), byIndex(byIndex_), dwTime(dwTime_), vecParam(vecParam_), 
			vecString(vecString_) { }

CInArchive& operator>>(CInArchive& src, SBubbleInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wMsgID;
	src >> s.wMessageID;
	src >> s.byIndex;
	src >> s.dwTime;
	src >> s.vecParam;
	src >> s.vecString;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBubbleInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wMsgID;
	src << s.wMessageID;
	src << s.byIndex;
	src << s.dwTime;
	src << s.vecParam;
	src << s.vecString;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBubbleInfo& s)
{
	if(strcmp(rElement.Value(), "SBubbleInfo") != 0)
	{
		LOG_CRI << "rElement is not SBubbleInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMsgID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMsgID") != 0)
	{
		LOG_CRI << "Attribute: name is not wMsgID!";
		return false;
	}
	const char* pszVal_wMsgID = pElemChild->Attribute("value");
	if(pszVal_wMsgID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMsgID, s.wMsgID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMessageID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMessageID") != 0)
	{
		LOG_CRI << "Attribute: name is not wMessageID!";
		return false;
	}
	const char* pszVal_wMessageID = pElemChild->Attribute("value");
	if(pszVal_wMessageID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMessageID, s.wMessageID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byIndex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byIndex") != 0)
	{
		LOG_CRI << "Attribute: name is not byIndex!";
		return false;
	}
	const char* pszVal_byIndex = pElemChild->Attribute("value");
	if(pszVal_byIndex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byIndex, s.byIndex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTime!";
		return false;
	}
	const char* pszVal_dwTime = pElemChild->Attribute("value");
	if(pszVal_dwTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTime, s.dwTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecINT64") != 0)
	{
		LOG_CRI << "pElemChild is not TVecINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecParam") != 0)
	{
		LOG_CRI << "Attribute: name is not vecParam!";
		return false;
	}
	const char* pszText_vecParam = pElemChild->GetText();
	if(pszText_vecParam != NULL)
		SplitToNumber(pszText_vecParam, ",", s.vecParam);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecString is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecString") != 0)
	{
		LOG_CRI << "pElemChild is not TVecString!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecString") != 0)
	{
		LOG_CRI << "Attribute: name is not vecString!";
		return false;
	}
	const char* pszText_vecString = pElemChild->GetText();
	if(pszText_vecString != NULL)
		SplitToText(pszText_vecString, ",", s.vecString);
	return true;
}

bool ToXML(const SBubbleInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBubbleInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("气泡信息"));
	unique_ptr<TiXmlElement> pElem_wMsgID(new TiXmlElement("UINT16"));
	if(pElem_wMsgID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMsgID->SetAttribute("name", "wMsgID");
	pElem_wMsgID->SetAttribute("value", NumberToString(s.wMsgID).c_str());
	pElem_wMsgID->SetAttribute("comment", ToUTF8Ptr("气泡ID"));
	if(rElement.LinkEndChild(pElem_wMsgID.get()) != NULL)
		pElem_wMsgID.release();
	unique_ptr<TiXmlElement> pElem_wMessageID(new TiXmlElement("UINT16"));
	if(pElem_wMessageID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMessageID->SetAttribute("name", "wMessageID");
	pElem_wMessageID->SetAttribute("value", NumberToString(s.wMessageID).c_str());
	pElem_wMessageID->SetAttribute("comment", ToUTF8Ptr("消息ID"));
	if(rElement.LinkEndChild(pElem_wMessageID.get()) != NULL)
		pElem_wMessageID.release();
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("气泡位置"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("气泡时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	unique_ptr<TiXmlElement> pElem_vecParam(new TiXmlElement("TVecINT64"));
	if(pElem_vecParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecParam->SetAttribute("name", "vecParam");
	string strText_vecParam;
	for(size_t i = 0; i < s.vecParam.size(); ++i)
	{
		if(i > 0)
			strText_vecParam += ", ";
		strText_vecParam += NumberToString(s.vecParam[i]);
	}
	unique_ptr<TiXmlText> pText_vecParam(new TiXmlText(strText_vecParam.c_str()));
	if(pText_vecParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecParam->LinkEndChild(pText_vecParam.get()) != NULL)
		pText_vecParam.release();
	pElem_vecParam->SetAttribute("comment", ToUTF8Ptr("整型变量"));
	if(rElement.LinkEndChild(pElem_vecParam.get()) != NULL)
		pElem_vecParam.release();
	unique_ptr<TiXmlElement> pElem_vecString(new TiXmlElement("TVecString"));
	if(pElem_vecString == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecString->SetAttribute("name", "vecString");
	string strText_vecString;
	for(size_t i = 0; i < s.vecString.size(); ++i)
	{
		if(i > 0)
			strText_vecString += ", ";
		strText_vecString += s.vecString[i];
	}
	unique_ptr<TiXmlText> pText_vecString(new TiXmlText(strText_vecString.c_str()));
	if(pText_vecString == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecString->LinkEndChild(pText_vecString.get()) != NULL)
		pText_vecString.release();
	pElem_vecString->SetAttribute("comment", ToUTF8Ptr("字符串型变量"));
	if(rElement.LinkEndChild(pElem_vecString.get()) != NULL)
		pElem_vecString.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBubbleInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBubbleInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecBubbleInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBubbleInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SGroupTaskInfo::SGroupTaskInfo() : dwRepute(0), byReputeLevel(0), byBuyTimes(0), dwFlushTask1(0), eState1((NGroupTaskProt::EGroupTaskState)0), 
			dwFlushTask2(0), eState2((NGroupTaskProt::EGroupTaskState)0), dwFlushTask3(0), eState3((NGroupTaskProt::EGroupTaskState)0), dwFlushTask4(0), 
			eState4((NGroupTaskProt::EGroupTaskState)0), dwFlushTask5(0), eState5((NGroupTaskProt::EGroupTaskState)0) { }

CInArchive& operator>>(CInArchive& src, SGroupTaskInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwRepute;
	src >> s.byReputeLevel;
	src >> s.byBuyTimes;
	src >> s.dwFlushTask1;
	src >> (UINT8&)s.eState1;
	src >> s.dwFlushTask2;
	src >> (UINT8&)s.eState2;
	src >> s.dwFlushTask3;
	src >> (UINT8&)s.eState3;
	src >> s.dwFlushTask4;
	src >> (UINT8&)s.eState4;
	src >> s.dwFlushTask5;
	src >> (UINT8&)s.eState5;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGroupTaskInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwRepute;
	src << s.byReputeLevel;
	src << s.byBuyTimes;
	src << s.dwFlushTask1;
	src << (UINT8&)s.eState1;
	src << s.dwFlushTask2;
	src << (UINT8&)s.eState2;
	src << s.dwFlushTask3;
	src << (UINT8&)s.eState3;
	src << s.dwFlushTask4;
	src << (UINT8&)s.eState4;
	src << s.dwFlushTask5;
	src << (UINT8&)s.eState5;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGroupTaskInfo& s)
{
	if(strcmp(rElement.Value(), "SGroupTaskInfo") != 0)
	{
		LOG_CRI << "rElement is not SGroupTaskInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRepute is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRepute") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRepute!";
		return false;
	}
	const char* pszVal_dwRepute = pElemChild->Attribute("value");
	if(pszVal_dwRepute == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRepute, s.dwRepute))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byReputeLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byReputeLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byReputeLevel!";
		return false;
	}
	const char* pszVal_byReputeLevel = pElemChild->Attribute("value");
	if(pszVal_byReputeLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byReputeLevel, s.byReputeLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBuyTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBuyTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not byBuyTimes!";
		return false;
	}
	const char* pszVal_byBuyTimes = pElemChild->Attribute("value");
	if(pszVal_byBuyTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBuyTimes, s.byBuyTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFlushTask1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFlushTask1") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFlushTask1!";
		return false;
	}
	const char* pszVal_dwFlushTask1 = pElemChild->Attribute("value");
	if(pszVal_dwFlushTask1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFlushTask1, s.dwFlushTask1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eState1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "GroupTaskProt::EGroupTaskState") != 0)
	{
		LOG_CRI << "pElemChild is not GroupTaskProt::EGroupTaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eState1") != 0)
	{
		LOG_CRI << "Attribute: name is not eState1!";
		return false;
	}
	const char* pszVal_eState1 = pElemChild->Attribute("value");
	if(pszVal_eState1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NGroupTaskProt::EnumStrToVal(pszVal_eState1, s.eState1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFlushTask2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFlushTask2") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFlushTask2!";
		return false;
	}
	const char* pszVal_dwFlushTask2 = pElemChild->Attribute("value");
	if(pszVal_dwFlushTask2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFlushTask2, s.dwFlushTask2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eState2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "GroupTaskProt::EGroupTaskState") != 0)
	{
		LOG_CRI << "pElemChild is not GroupTaskProt::EGroupTaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eState2") != 0)
	{
		LOG_CRI << "Attribute: name is not eState2!";
		return false;
	}
	const char* pszVal_eState2 = pElemChild->Attribute("value");
	if(pszVal_eState2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NGroupTaskProt::EnumStrToVal(pszVal_eState2, s.eState2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFlushTask3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFlushTask3") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFlushTask3!";
		return false;
	}
	const char* pszVal_dwFlushTask3 = pElemChild->Attribute("value");
	if(pszVal_dwFlushTask3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFlushTask3, s.dwFlushTask3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eState3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "GroupTaskProt::EGroupTaskState") != 0)
	{
		LOG_CRI << "pElemChild is not GroupTaskProt::EGroupTaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eState3") != 0)
	{
		LOG_CRI << "Attribute: name is not eState3!";
		return false;
	}
	const char* pszVal_eState3 = pElemChild->Attribute("value");
	if(pszVal_eState3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NGroupTaskProt::EnumStrToVal(pszVal_eState3, s.eState3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFlushTask4 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFlushTask4") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFlushTask4!";
		return false;
	}
	const char* pszVal_dwFlushTask4 = pElemChild->Attribute("value");
	if(pszVal_dwFlushTask4 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFlushTask4, s.dwFlushTask4))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eState4 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "GroupTaskProt::EGroupTaskState") != 0)
	{
		LOG_CRI << "pElemChild is not GroupTaskProt::EGroupTaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eState4") != 0)
	{
		LOG_CRI << "Attribute: name is not eState4!";
		return false;
	}
	const char* pszVal_eState4 = pElemChild->Attribute("value");
	if(pszVal_eState4 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NGroupTaskProt::EnumStrToVal(pszVal_eState4, s.eState4))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFlushTask5 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFlushTask5") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFlushTask5!";
		return false;
	}
	const char* pszVal_dwFlushTask5 = pElemChild->Attribute("value");
	if(pszVal_dwFlushTask5 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFlushTask5, s.dwFlushTask5))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eState5 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "GroupTaskProt::EGroupTaskState") != 0)
	{
		LOG_CRI << "pElemChild is not GroupTaskProt::EGroupTaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eState5") != 0)
	{
		LOG_CRI << "Attribute: name is not eState5!";
		return false;
	}
	const char* pszVal_eState5 = pElemChild->Attribute("value");
	if(pszVal_eState5 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NGroupTaskProt::EnumStrToVal(pszVal_eState5, s.eState5))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGroupTaskInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGroupTaskInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("师门任务"));
	unique_ptr<TiXmlElement> pElem_dwRepute(new TiXmlElement("UINT32"));
	if(pElem_dwRepute == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRepute->SetAttribute("name", "dwRepute");
	pElem_dwRepute->SetAttribute("value", NumberToString(s.dwRepute).c_str());
	pElem_dwRepute->SetAttribute("comment", ToUTF8Ptr("声望"));
	if(rElement.LinkEndChild(pElem_dwRepute.get()) != NULL)
		pElem_dwRepute.release();
	unique_ptr<TiXmlElement> pElem_byReputeLevel(new TiXmlElement("UINT8"));
	if(pElem_byReputeLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byReputeLevel->SetAttribute("name", "byReputeLevel");
	pElem_byReputeLevel->SetAttribute("value", NumberToString(s.byReputeLevel).c_str());
	pElem_byReputeLevel->SetAttribute("comment", ToUTF8Ptr("声望等级"));
	if(rElement.LinkEndChild(pElem_byReputeLevel.get()) != NULL)
		pElem_byReputeLevel.release();
	unique_ptr<TiXmlElement> pElem_byBuyTimes(new TiXmlElement("UINT8"));
	if(pElem_byBuyTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBuyTimes->SetAttribute("name", "byBuyTimes");
	pElem_byBuyTimes->SetAttribute("value", NumberToString(s.byBuyTimes).c_str());
	pElem_byBuyTimes->SetAttribute("comment", ToUTF8Ptr("购买的师门任务数"));
	if(rElement.LinkEndChild(pElem_byBuyTimes.get()) != NULL)
		pElem_byBuyTimes.release();
	unique_ptr<TiXmlElement> pElem_dwFlushTask1(new TiXmlElement("UINT32"));
	if(pElem_dwFlushTask1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFlushTask1->SetAttribute("name", "dwFlushTask1");
	pElem_dwFlushTask1->SetAttribute("value", NumberToString(s.dwFlushTask1).c_str());
	pElem_dwFlushTask1->SetAttribute("comment", ToUTF8Ptr("刷的任务"));
	if(rElement.LinkEndChild(pElem_dwFlushTask1.get()) != NULL)
		pElem_dwFlushTask1.release();
	unique_ptr<TiXmlElement> pElem_eState1(new TiXmlElement("GroupTaskProt::EGroupTaskState"));
	if(pElem_eState1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState1->SetAttribute("name", "eState1");
	const char* pszEnum_eState1 = NGroupTaskProt::EnumValToStr(s.eState1);
	if(pszEnum_eState1 == NULL)
	{
		LOG_CRI << "EnumValToStr for eState1 fails!";
		return false;
	}
	pElem_eState1->SetAttribute("value", pszEnum_eState1);
	pElem_eState1->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eState1.get()) != NULL)
		pElem_eState1.release();
	unique_ptr<TiXmlElement> pElem_dwFlushTask2(new TiXmlElement("UINT32"));
	if(pElem_dwFlushTask2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFlushTask2->SetAttribute("name", "dwFlushTask2");
	pElem_dwFlushTask2->SetAttribute("value", NumberToString(s.dwFlushTask2).c_str());
	pElem_dwFlushTask2->SetAttribute("comment", ToUTF8Ptr("刷的任务"));
	if(rElement.LinkEndChild(pElem_dwFlushTask2.get()) != NULL)
		pElem_dwFlushTask2.release();
	unique_ptr<TiXmlElement> pElem_eState2(new TiXmlElement("GroupTaskProt::EGroupTaskState"));
	if(pElem_eState2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState2->SetAttribute("name", "eState2");
	const char* pszEnum_eState2 = NGroupTaskProt::EnumValToStr(s.eState2);
	if(pszEnum_eState2 == NULL)
	{
		LOG_CRI << "EnumValToStr for eState2 fails!";
		return false;
	}
	pElem_eState2->SetAttribute("value", pszEnum_eState2);
	pElem_eState2->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eState2.get()) != NULL)
		pElem_eState2.release();
	unique_ptr<TiXmlElement> pElem_dwFlushTask3(new TiXmlElement("UINT32"));
	if(pElem_dwFlushTask3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFlushTask3->SetAttribute("name", "dwFlushTask3");
	pElem_dwFlushTask3->SetAttribute("value", NumberToString(s.dwFlushTask3).c_str());
	pElem_dwFlushTask3->SetAttribute("comment", ToUTF8Ptr("刷的任务"));
	if(rElement.LinkEndChild(pElem_dwFlushTask3.get()) != NULL)
		pElem_dwFlushTask3.release();
	unique_ptr<TiXmlElement> pElem_eState3(new TiXmlElement("GroupTaskProt::EGroupTaskState"));
	if(pElem_eState3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState3->SetAttribute("name", "eState3");
	const char* pszEnum_eState3 = NGroupTaskProt::EnumValToStr(s.eState3);
	if(pszEnum_eState3 == NULL)
	{
		LOG_CRI << "EnumValToStr for eState3 fails!";
		return false;
	}
	pElem_eState3->SetAttribute("value", pszEnum_eState3);
	pElem_eState3->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eState3.get()) != NULL)
		pElem_eState3.release();
	unique_ptr<TiXmlElement> pElem_dwFlushTask4(new TiXmlElement("UINT32"));
	if(pElem_dwFlushTask4 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFlushTask4->SetAttribute("name", "dwFlushTask4");
	pElem_dwFlushTask4->SetAttribute("value", NumberToString(s.dwFlushTask4).c_str());
	pElem_dwFlushTask4->SetAttribute("comment", ToUTF8Ptr("刷的任务"));
	if(rElement.LinkEndChild(pElem_dwFlushTask4.get()) != NULL)
		pElem_dwFlushTask4.release();
	unique_ptr<TiXmlElement> pElem_eState4(new TiXmlElement("GroupTaskProt::EGroupTaskState"));
	if(pElem_eState4 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState4->SetAttribute("name", "eState4");
	const char* pszEnum_eState4 = NGroupTaskProt::EnumValToStr(s.eState4);
	if(pszEnum_eState4 == NULL)
	{
		LOG_CRI << "EnumValToStr for eState4 fails!";
		return false;
	}
	pElem_eState4->SetAttribute("value", pszEnum_eState4);
	pElem_eState4->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eState4.get()) != NULL)
		pElem_eState4.release();
	unique_ptr<TiXmlElement> pElem_dwFlushTask5(new TiXmlElement("UINT32"));
	if(pElem_dwFlushTask5 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFlushTask5->SetAttribute("name", "dwFlushTask5");
	pElem_dwFlushTask5->SetAttribute("value", NumberToString(s.dwFlushTask5).c_str());
	pElem_dwFlushTask5->SetAttribute("comment", ToUTF8Ptr("刷的任务"));
	if(rElement.LinkEndChild(pElem_dwFlushTask5.get()) != NULL)
		pElem_dwFlushTask5.release();
	unique_ptr<TiXmlElement> pElem_eState5(new TiXmlElement("GroupTaskProt::EGroupTaskState"));
	if(pElem_eState5 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState5->SetAttribute("name", "eState5");
	const char* pszEnum_eState5 = NGroupTaskProt::EnumValToStr(s.eState5);
	if(pszEnum_eState5 == NULL)
	{
		LOG_CRI << "EnumValToStr for eState5 fails!";
		return false;
	}
	pElem_eState5->SetAttribute("value", pszEnum_eState5);
	pElem_eState5->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eState5.get()) != NULL)
		pElem_eState5.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGroupTaskInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGroupTaskInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecGroupTaskInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGroupTaskInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SYaMenTaskInfo::SYaMenTaskInfo() : dwHoly(0), byHolyLevel(0), byBuyTimes(0), dwFlushTask1(0), eState1((NYaMenTaskProt::EYaMenTaskState)0), 
			dwFlushTask2(0), eState2((NYaMenTaskProt::EYaMenTaskState)0), dwFlushTask3(0), eState3((NYaMenTaskProt::EYaMenTaskState)0), dwFlushTask4(0), 
			eState4((NYaMenTaskProt::EYaMenTaskState)0), dwFlushTask5(0), eState5((NYaMenTaskProt::EYaMenTaskState)0) { }

CInArchive& operator>>(CInArchive& src, SYaMenTaskInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwHoly;
	src >> s.byHolyLevel;
	src >> s.byBuyTimes;
	src >> s.dwFlushTask1;
	src >> (UINT8&)s.eState1;
	src >> s.dwFlushTask2;
	src >> (UINT8&)s.eState2;
	src >> s.dwFlushTask3;
	src >> (UINT8&)s.eState3;
	src >> s.dwFlushTask4;
	src >> (UINT8&)s.eState4;
	src >> s.dwFlushTask5;
	src >> (UINT8&)s.eState5;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SYaMenTaskInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwHoly;
	src << s.byHolyLevel;
	src << s.byBuyTimes;
	src << s.dwFlushTask1;
	src << (UINT8&)s.eState1;
	src << s.dwFlushTask2;
	src << (UINT8&)s.eState2;
	src << s.dwFlushTask3;
	src << (UINT8&)s.eState3;
	src << s.dwFlushTask4;
	src << (UINT8&)s.eState4;
	src << s.dwFlushTask5;
	src << (UINT8&)s.eState5;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SYaMenTaskInfo& s)
{
	if(strcmp(rElement.Value(), "SYaMenTaskInfo") != 0)
	{
		LOG_CRI << "rElement is not SYaMenTaskInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHoly is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHoly") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHoly!";
		return false;
	}
	const char* pszVal_dwHoly = pElemChild->Attribute("value");
	if(pszVal_dwHoly == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHoly, s.dwHoly))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byHolyLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byHolyLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byHolyLevel!";
		return false;
	}
	const char* pszVal_byHolyLevel = pElemChild->Attribute("value");
	if(pszVal_byHolyLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byHolyLevel, s.byHolyLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBuyTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBuyTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not byBuyTimes!";
		return false;
	}
	const char* pszVal_byBuyTimes = pElemChild->Attribute("value");
	if(pszVal_byBuyTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBuyTimes, s.byBuyTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFlushTask1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFlushTask1") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFlushTask1!";
		return false;
	}
	const char* pszVal_dwFlushTask1 = pElemChild->Attribute("value");
	if(pszVal_dwFlushTask1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFlushTask1, s.dwFlushTask1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eState1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "YaMenTaskProt::EYaMenTaskState") != 0)
	{
		LOG_CRI << "pElemChild is not YaMenTaskProt::EYaMenTaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eState1") != 0)
	{
		LOG_CRI << "Attribute: name is not eState1!";
		return false;
	}
	const char* pszVal_eState1 = pElemChild->Attribute("value");
	if(pszVal_eState1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NYaMenTaskProt::EnumStrToVal(pszVal_eState1, s.eState1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFlushTask2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFlushTask2") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFlushTask2!";
		return false;
	}
	const char* pszVal_dwFlushTask2 = pElemChild->Attribute("value");
	if(pszVal_dwFlushTask2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFlushTask2, s.dwFlushTask2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eState2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "YaMenTaskProt::EYaMenTaskState") != 0)
	{
		LOG_CRI << "pElemChild is not YaMenTaskProt::EYaMenTaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eState2") != 0)
	{
		LOG_CRI << "Attribute: name is not eState2!";
		return false;
	}
	const char* pszVal_eState2 = pElemChild->Attribute("value");
	if(pszVal_eState2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NYaMenTaskProt::EnumStrToVal(pszVal_eState2, s.eState2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFlushTask3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFlushTask3") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFlushTask3!";
		return false;
	}
	const char* pszVal_dwFlushTask3 = pElemChild->Attribute("value");
	if(pszVal_dwFlushTask3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFlushTask3, s.dwFlushTask3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eState3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "YaMenTaskProt::EYaMenTaskState") != 0)
	{
		LOG_CRI << "pElemChild is not YaMenTaskProt::EYaMenTaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eState3") != 0)
	{
		LOG_CRI << "Attribute: name is not eState3!";
		return false;
	}
	const char* pszVal_eState3 = pElemChild->Attribute("value");
	if(pszVal_eState3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NYaMenTaskProt::EnumStrToVal(pszVal_eState3, s.eState3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFlushTask4 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFlushTask4") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFlushTask4!";
		return false;
	}
	const char* pszVal_dwFlushTask4 = pElemChild->Attribute("value");
	if(pszVal_dwFlushTask4 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFlushTask4, s.dwFlushTask4))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eState4 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "YaMenTaskProt::EYaMenTaskState") != 0)
	{
		LOG_CRI << "pElemChild is not YaMenTaskProt::EYaMenTaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eState4") != 0)
	{
		LOG_CRI << "Attribute: name is not eState4!";
		return false;
	}
	const char* pszVal_eState4 = pElemChild->Attribute("value");
	if(pszVal_eState4 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NYaMenTaskProt::EnumStrToVal(pszVal_eState4, s.eState4))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFlushTask5 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFlushTask5") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFlushTask5!";
		return false;
	}
	const char* pszVal_dwFlushTask5 = pElemChild->Attribute("value");
	if(pszVal_dwFlushTask5 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFlushTask5, s.dwFlushTask5))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eState5 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "YaMenTaskProt::EYaMenTaskState") != 0)
	{
		LOG_CRI << "pElemChild is not YaMenTaskProt::EYaMenTaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eState5") != 0)
	{
		LOG_CRI << "Attribute: name is not eState5!";
		return false;
	}
	const char* pszVal_eState5 = pElemChild->Attribute("value");
	if(pszVal_eState5 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NYaMenTaskProt::EnumStrToVal(pszVal_eState5, s.eState5))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SYaMenTaskInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SYaMenTaskInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("衙门任务"));
	unique_ptr<TiXmlElement> pElem_dwHoly(new TiXmlElement("UINT32"));
	if(pElem_dwHoly == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHoly->SetAttribute("name", "dwHoly");
	pElem_dwHoly->SetAttribute("value", NumberToString(s.dwHoly).c_str());
	pElem_dwHoly->SetAttribute("comment", ToUTF8Ptr("圣义值"));
	if(rElement.LinkEndChild(pElem_dwHoly.get()) != NULL)
		pElem_dwHoly.release();
	unique_ptr<TiXmlElement> pElem_byHolyLevel(new TiXmlElement("UINT8"));
	if(pElem_byHolyLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byHolyLevel->SetAttribute("name", "byHolyLevel");
	pElem_byHolyLevel->SetAttribute("value", NumberToString(s.byHolyLevel).c_str());
	pElem_byHolyLevel->SetAttribute("comment", ToUTF8Ptr("圣义等级"));
	if(rElement.LinkEndChild(pElem_byHolyLevel.get()) != NULL)
		pElem_byHolyLevel.release();
	unique_ptr<TiXmlElement> pElem_byBuyTimes(new TiXmlElement("UINT8"));
	if(pElem_byBuyTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBuyTimes->SetAttribute("name", "byBuyTimes");
	pElem_byBuyTimes->SetAttribute("value", NumberToString(s.byBuyTimes).c_str());
	pElem_byBuyTimes->SetAttribute("comment", ToUTF8Ptr("购买的衙门任务数"));
	if(rElement.LinkEndChild(pElem_byBuyTimes.get()) != NULL)
		pElem_byBuyTimes.release();
	unique_ptr<TiXmlElement> pElem_dwFlushTask1(new TiXmlElement("UINT32"));
	if(pElem_dwFlushTask1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFlushTask1->SetAttribute("name", "dwFlushTask1");
	pElem_dwFlushTask1->SetAttribute("value", NumberToString(s.dwFlushTask1).c_str());
	pElem_dwFlushTask1->SetAttribute("comment", ToUTF8Ptr("刷的任务"));
	if(rElement.LinkEndChild(pElem_dwFlushTask1.get()) != NULL)
		pElem_dwFlushTask1.release();
	unique_ptr<TiXmlElement> pElem_eState1(new TiXmlElement("YaMenTaskProt::EYaMenTaskState"));
	if(pElem_eState1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState1->SetAttribute("name", "eState1");
	const char* pszEnum_eState1 = NYaMenTaskProt::EnumValToStr(s.eState1);
	if(pszEnum_eState1 == NULL)
	{
		LOG_CRI << "EnumValToStr for eState1 fails!";
		return false;
	}
	pElem_eState1->SetAttribute("value", pszEnum_eState1);
	pElem_eState1->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eState1.get()) != NULL)
		pElem_eState1.release();
	unique_ptr<TiXmlElement> pElem_dwFlushTask2(new TiXmlElement("UINT32"));
	if(pElem_dwFlushTask2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFlushTask2->SetAttribute("name", "dwFlushTask2");
	pElem_dwFlushTask2->SetAttribute("value", NumberToString(s.dwFlushTask2).c_str());
	pElem_dwFlushTask2->SetAttribute("comment", ToUTF8Ptr("刷的任务"));
	if(rElement.LinkEndChild(pElem_dwFlushTask2.get()) != NULL)
		pElem_dwFlushTask2.release();
	unique_ptr<TiXmlElement> pElem_eState2(new TiXmlElement("YaMenTaskProt::EYaMenTaskState"));
	if(pElem_eState2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState2->SetAttribute("name", "eState2");
	const char* pszEnum_eState2 = NYaMenTaskProt::EnumValToStr(s.eState2);
	if(pszEnum_eState2 == NULL)
	{
		LOG_CRI << "EnumValToStr for eState2 fails!";
		return false;
	}
	pElem_eState2->SetAttribute("value", pszEnum_eState2);
	pElem_eState2->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eState2.get()) != NULL)
		pElem_eState2.release();
	unique_ptr<TiXmlElement> pElem_dwFlushTask3(new TiXmlElement("UINT32"));
	if(pElem_dwFlushTask3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFlushTask3->SetAttribute("name", "dwFlushTask3");
	pElem_dwFlushTask3->SetAttribute("value", NumberToString(s.dwFlushTask3).c_str());
	pElem_dwFlushTask3->SetAttribute("comment", ToUTF8Ptr("刷的任务"));
	if(rElement.LinkEndChild(pElem_dwFlushTask3.get()) != NULL)
		pElem_dwFlushTask3.release();
	unique_ptr<TiXmlElement> pElem_eState3(new TiXmlElement("YaMenTaskProt::EYaMenTaskState"));
	if(pElem_eState3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState3->SetAttribute("name", "eState3");
	const char* pszEnum_eState3 = NYaMenTaskProt::EnumValToStr(s.eState3);
	if(pszEnum_eState3 == NULL)
	{
		LOG_CRI << "EnumValToStr for eState3 fails!";
		return false;
	}
	pElem_eState3->SetAttribute("value", pszEnum_eState3);
	pElem_eState3->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eState3.get()) != NULL)
		pElem_eState3.release();
	unique_ptr<TiXmlElement> pElem_dwFlushTask4(new TiXmlElement("UINT32"));
	if(pElem_dwFlushTask4 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFlushTask4->SetAttribute("name", "dwFlushTask4");
	pElem_dwFlushTask4->SetAttribute("value", NumberToString(s.dwFlushTask4).c_str());
	pElem_dwFlushTask4->SetAttribute("comment", ToUTF8Ptr("刷的任务"));
	if(rElement.LinkEndChild(pElem_dwFlushTask4.get()) != NULL)
		pElem_dwFlushTask4.release();
	unique_ptr<TiXmlElement> pElem_eState4(new TiXmlElement("YaMenTaskProt::EYaMenTaskState"));
	if(pElem_eState4 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState4->SetAttribute("name", "eState4");
	const char* pszEnum_eState4 = NYaMenTaskProt::EnumValToStr(s.eState4);
	if(pszEnum_eState4 == NULL)
	{
		LOG_CRI << "EnumValToStr for eState4 fails!";
		return false;
	}
	pElem_eState4->SetAttribute("value", pszEnum_eState4);
	pElem_eState4->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eState4.get()) != NULL)
		pElem_eState4.release();
	unique_ptr<TiXmlElement> pElem_dwFlushTask5(new TiXmlElement("UINT32"));
	if(pElem_dwFlushTask5 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFlushTask5->SetAttribute("name", "dwFlushTask5");
	pElem_dwFlushTask5->SetAttribute("value", NumberToString(s.dwFlushTask5).c_str());
	pElem_dwFlushTask5->SetAttribute("comment", ToUTF8Ptr("刷的任务"));
	if(rElement.LinkEndChild(pElem_dwFlushTask5.get()) != NULL)
		pElem_dwFlushTask5.release();
	unique_ptr<TiXmlElement> pElem_eState5(new TiXmlElement("YaMenTaskProt::EYaMenTaskState"));
	if(pElem_eState5 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState5->SetAttribute("name", "eState5");
	const char* pszEnum_eState5 = NYaMenTaskProt::EnumValToStr(s.eState5);
	if(pszEnum_eState5 == NULL)
	{
		LOG_CRI << "EnumValToStr for eState5 fails!";
		return false;
	}
	pElem_eState5->SetAttribute("value", pszEnum_eState5);
	pElem_eState5->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eState5.get()) != NULL)
		pElem_eState5.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecYaMenTaskInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SYaMenTaskInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecYaMenTaskInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SYaMenTaskInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SActivityTaskInfo::SActivityTaskInfo() : wId(0), byTimes(0), byIsSpecial(0) { }

SActivityTaskInfo::SActivityTaskInfo(UINT16 wId_, UINT8 byTimes_, UINT8 byIsSpecial_) : wId(wId_), byTimes(byTimes_), byIsSpecial(byIsSpecial_) { }

CInArchive& operator>>(CInArchive& src, SActivityTaskInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wId;
	src >> s.byTimes;
	src >> s.byIsSpecial;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SActivityTaskInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wId;
	src << s.byTimes;
	src << s.byIsSpecial;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SActivityTaskInfo& s)
{
	if(strcmp(rElement.Value(), "SActivityTaskInfo") != 0)
	{
		LOG_CRI << "rElement is not SActivityTaskInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wId") != 0)
	{
		LOG_CRI << "Attribute: name is not wId!";
		return false;
	}
	const char* pszVal_wId = pElemChild->Attribute("value");
	if(pszVal_wId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wId, s.wId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not byTimes!";
		return false;
	}
	const char* pszVal_byTimes = pElemChild->Attribute("value");
	if(pszVal_byTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTimes, s.byTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byIsSpecial is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byIsSpecial") != 0)
	{
		LOG_CRI << "Attribute: name is not byIsSpecial!";
		return false;
	}
	const char* pszVal_byIsSpecial = pElemChild->Attribute("value");
	if(pszVal_byIsSpecial == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byIsSpecial, s.byIsSpecial))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SActivityTaskInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SActivityTaskInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("活跃任务"));
	unique_ptr<TiXmlElement> pElem_wId(new TiXmlElement("UINT16"));
	if(pElem_wId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wId->SetAttribute("name", "wId");
	pElem_wId->SetAttribute("value", NumberToString(s.wId).c_str());
	pElem_wId->SetAttribute("comment", ToUTF8Ptr("活跃触发点ID"));
	if(rElement.LinkEndChild(pElem_wId.get()) != NULL)
		pElem_wId.release();
	unique_ptr<TiXmlElement> pElem_byTimes(new TiXmlElement("UINT8"));
	if(pElem_byTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTimes->SetAttribute("name", "byTimes");
	pElem_byTimes->SetAttribute("value", NumberToString(s.byTimes).c_str());
	pElem_byTimes->SetAttribute("comment", ToUTF8Ptr("完成次数"));
	if(rElement.LinkEndChild(pElem_byTimes.get()) != NULL)
		pElem_byTimes.release();
	unique_ptr<TiXmlElement> pElem_byIsSpecial(new TiXmlElement("UINT8"));
	if(pElem_byIsSpecial == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIsSpecial->SetAttribute("name", "byIsSpecial");
	pElem_byIsSpecial->SetAttribute("value", NumberToString(s.byIsSpecial).c_str());
	pElem_byIsSpecial->SetAttribute("comment", ToUTF8Ptr("是否特别任务"));
	if(rElement.LinkEndChild(pElem_byIsSpecial.get()) != NULL)
		pElem_byIsSpecial.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecActivityTaskInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SActivityTaskInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecActivityTaskInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SActivityTaskInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

STitle::STitle() : wId(0), byEquipPos(0), dwValidTime(0) { }

STitle::STitle(UINT16 wId_, UINT8 byEquipPos_, UINT32 dwValidTime_) : wId(wId_), byEquipPos(byEquipPos_), dwValidTime(dwValidTime_) { }

CInArchive& operator>>(CInArchive& src, STitle& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wId;
	src >> s.byEquipPos;
	src >> s.dwValidTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STitle& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wId;
	src << s.byEquipPos;
	src << s.dwValidTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STitle& s)
{
	if(strcmp(rElement.Value(), "STitle") != 0)
	{
		LOG_CRI << "rElement is not STitle!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wId") != 0)
	{
		LOG_CRI << "Attribute: name is not wId!";
		return false;
	}
	const char* pszVal_wId = pElemChild->Attribute("value");
	if(pszVal_wId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wId, s.wId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byEquipPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byEquipPos") != 0)
	{
		LOG_CRI << "Attribute: name is not byEquipPos!";
		return false;
	}
	const char* pszVal_byEquipPos = pElemChild->Attribute("value");
	if(pszVal_byEquipPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byEquipPos, s.byEquipPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwValidTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwValidTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwValidTime!";
		return false;
	}
	const char* pszVal_dwValidTime = pElemChild->Attribute("value");
	if(pszVal_dwValidTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwValidTime, s.dwValidTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STitle& s, TiXmlElement& rElement)
{
	rElement.SetValue("STitle");
	rElement.SetAttribute("type", ToUTF8Ptr("头衔"));
	unique_ptr<TiXmlElement> pElem_wId(new TiXmlElement("UINT16"));
	if(pElem_wId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wId->SetAttribute("name", "wId");
	pElem_wId->SetAttribute("value", NumberToString(s.wId).c_str());
	pElem_wId->SetAttribute("comment", ToUTF8Ptr("头衔ID"));
	if(rElement.LinkEndChild(pElem_wId.get()) != NULL)
		pElem_wId.release();
	unique_ptr<TiXmlElement> pElem_byEquipPos(new TiXmlElement("UINT8"));
	if(pElem_byEquipPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byEquipPos->SetAttribute("name", "byEquipPos");
	pElem_byEquipPos->SetAttribute("value", NumberToString(s.byEquipPos).c_str());
	pElem_byEquipPos->SetAttribute("comment", ToUTF8Ptr("装备位,从1开始，0表示未装备"));
	if(rElement.LinkEndChild(pElem_byEquipPos.get()) != NULL)
		pElem_byEquipPos.release();
	unique_ptr<TiXmlElement> pElem_dwValidTime(new TiXmlElement("UINT32"));
	if(pElem_dwValidTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValidTime->SetAttribute("name", "dwValidTime");
	pElem_dwValidTime->SetAttribute("value", NumberToString(s.dwValidTime).c_str());
	pElem_dwValidTime->SetAttribute("comment", ToUTF8Ptr("有效截止时间,0表示永久"));
	if(rElement.LinkEndChild(pElem_dwValidTime.get()) != NULL)
		pElem_dwValidTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTitle& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STitle s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecTitle& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STitle"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SPendRes::SPendRes() : byResType(0), dwValue(0), bySource(0), dwParam(0) { }

SPendRes::SPendRes(UINT8 byResType_, UINT32 dwValue_, UINT8 bySource_, UINT32 dwParam_) : byResType(byResType_), dwValue(dwValue_), bySource(bySource_), dwParam(dwParam_) { }

CInArchive& operator>>(CInArchive& src, SPendRes& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byResType;
	src >> s.dwValue;
	src >> s.bySource;
	src >> s.dwParam;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPendRes& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byResType;
	src << s.dwValue;
	src << s.bySource;
	src << s.dwParam;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPendRes& s)
{
	if(strcmp(rElement.Value(), "SPendRes") != 0)
	{
		LOG_CRI << "rElement is not SPendRes!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byResType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byResType") != 0)
	{
		LOG_CRI << "Attribute: name is not byResType!";
		return false;
	}
	const char* pszVal_byResType = pElemChild->Attribute("value");
	if(pszVal_byResType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byResType, s.byResType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwValue!";
		return false;
	}
	const char* pszVal_dwValue = pElemChild->Attribute("value");
	if(pszVal_dwValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwValue, s.dwValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySource is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySource") != 0)
	{
		LOG_CRI << "Attribute: name is not bySource!";
		return false;
	}
	const char* pszVal_bySource = pElemChild->Attribute("value");
	if(pszVal_bySource == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySource, s.bySource))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwParam") != 0)
	{
		LOG_CRI << "Attribute: name is not dwParam!";
		return false;
	}
	const char* pszVal_dwParam = pElemChild->Attribute("value");
	if(pszVal_dwParam == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwParam, s.dwParam))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPendRes& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPendRes");
	rElement.SetAttribute("type", ToUTF8Ptr("暂存信息"));
	unique_ptr<TiXmlElement> pElem_byResType(new TiXmlElement("UINT8"));
	if(pElem_byResType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byResType->SetAttribute("name", "byResType");
	pElem_byResType->SetAttribute("value", NumberToString(s.byResType).c_str());
	pElem_byResType->SetAttribute("comment", ToUTF8Ptr("类型"));
	if(rElement.LinkEndChild(pElem_byResType.get()) != NULL)
		pElem_byResType.release();
	unique_ptr<TiXmlElement> pElem_dwValue(new TiXmlElement("UINT32"));
	if(pElem_dwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValue->SetAttribute("name", "dwValue");
	pElem_dwValue->SetAttribute("value", NumberToString(s.dwValue).c_str());
	pElem_dwValue->SetAttribute("comment", ToUTF8Ptr("数据"));
	if(rElement.LinkEndChild(pElem_dwValue.get()) != NULL)
		pElem_dwValue.release();
	unique_ptr<TiXmlElement> pElem_bySource(new TiXmlElement("UINT8"));
	if(pElem_bySource == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySource->SetAttribute("name", "bySource");
	pElem_bySource->SetAttribute("value", NumberToString(s.bySource).c_str());
	pElem_bySource->SetAttribute("comment", ToUTF8Ptr("暂存原因0,战斗，1副本"));
	if(rElement.LinkEndChild(pElem_bySource.get()) != NULL)
		pElem_bySource.release();
	unique_ptr<TiXmlElement> pElem_dwParam(new TiXmlElement("UINT32"));
	if(pElem_dwParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwParam->SetAttribute("name", "dwParam");
	pElem_dwParam->SetAttribute("value", NumberToString(s.dwParam).c_str());
	pElem_dwParam->SetAttribute("comment", ToUTF8Ptr("参数"));
	if(rElement.LinkEndChild(pElem_dwParam.get()) != NULL)
		pElem_dwParam.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPendRes& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPendRes s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecPendRes& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPendRes"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SEventInfo::SEventInfo() : qwRoleID(0), byActClassID(0), dwEventInstID(0), dwApplyID(0), wEventStatus(0), 
			bySave(0), dwParam1(0), dwParam2(0), dwStartTime(0), dwEndTime(0) { }

SEventInfo::SEventInfo(UINT64 qwRoleID_, UINT8 byActClassID_, UINT32 dwEventInstID_, UINT32 dwApplyID_, UINT16 wEventStatus_, 
			UINT8 bySave_, UINT32 dwParam1_, INT32 dwParam2_, UINT32 dwStartTime_, UINT32 dwEndTime_)
			: qwRoleID(qwRoleID_), byActClassID(byActClassID_), dwEventInstID(dwEventInstID_), dwApplyID(dwApplyID_), wEventStatus(wEventStatus_), 
			bySave(bySave_), dwParam1(dwParam1_), dwParam2(dwParam2_), dwStartTime(dwStartTime_), dwEndTime(dwEndTime_) { }

CInArchive& operator>>(CInArchive& src, SEventInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.byActClassID;
	src >> s.dwEventInstID;
	src >> s.dwApplyID;
	src >> s.wEventStatus;
	src >> s.bySave;
	src >> s.dwParam1;
	src >> s.dwParam2;
	src >> s.dwStartTime;
	src >> s.dwEndTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEventInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.byActClassID;
	src << s.dwEventInstID;
	src << s.dwApplyID;
	src << s.wEventStatus;
	src << s.bySave;
	src << s.dwParam1;
	src << s.dwParam2;
	src << s.dwStartTime;
	src << s.dwEndTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SEventInfo& s)
{
	if(strcmp(rElement.Value(), "SEventInfo") != 0)
	{
		LOG_CRI << "rElement is not SEventInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byActClassID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byActClassID") != 0)
	{
		LOG_CRI << "Attribute: name is not byActClassID!";
		return false;
	}
	const char* pszVal_byActClassID = pElemChild->Attribute("value");
	if(pszVal_byActClassID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byActClassID, s.byActClassID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEventInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEventInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEventInstID!";
		return false;
	}
	const char* pszVal_dwEventInstID = pElemChild->Attribute("value");
	if(pszVal_dwEventInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEventInstID, s.dwEventInstID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwApplyID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwApplyID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwApplyID!";
		return false;
	}
	const char* pszVal_dwApplyID = pElemChild->Attribute("value");
	if(pszVal_dwApplyID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwApplyID, s.dwApplyID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wEventStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wEventStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not wEventStatus!";
		return false;
	}
	const char* pszVal_wEventStatus = pElemChild->Attribute("value");
	if(pszVal_wEventStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wEventStatus, s.wEventStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySave is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySave") != 0)
	{
		LOG_CRI << "Attribute: name is not bySave!";
		return false;
	}
	const char* pszVal_bySave = pElemChild->Attribute("value");
	if(pszVal_bySave == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySave, s.bySave))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwParam1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwParam1") != 0)
	{
		LOG_CRI << "Attribute: name is not dwParam1!";
		return false;
	}
	const char* pszVal_dwParam1 = pElemChild->Attribute("value");
	if(pszVal_dwParam1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwParam1, s.dwParam1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwParam2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwParam2") != 0)
	{
		LOG_CRI << "Attribute: name is not dwParam2!";
		return false;
	}
	const char* pszVal_dwParam2 = pElemChild->Attribute("value");
	if(pszVal_dwParam2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwParam2, s.dwParam2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStartTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStartTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStartTime!";
		return false;
	}
	const char* pszVal_dwStartTime = pElemChild->Attribute("value");
	if(pszVal_dwStartTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStartTime, s.dwStartTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEndTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEndTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEndTime!";
		return false;
	}
	const char* pszVal_dwEndTime = pElemChild->Attribute("value");
	if(pszVal_dwEndTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEndTime, s.dwEndTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEventInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEventInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("事件信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("角色ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_byActClassID(new TiXmlElement("UINT8"));
	if(pElem_byActClassID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byActClassID->SetAttribute("name", "byActClassID");
	pElem_byActClassID->SetAttribute("value", NumberToString(s.byActClassID).c_str());
	pElem_byActClassID->SetAttribute("comment", ToUTF8Ptr("活动类型ID"));
	if(rElement.LinkEndChild(pElem_byActClassID.get()) != NULL)
		pElem_byActClassID.release();
	unique_ptr<TiXmlElement> pElem_dwEventInstID(new TiXmlElement("UINT32"));
	if(pElem_dwEventInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEventInstID->SetAttribute("name", "dwEventInstID");
	pElem_dwEventInstID->SetAttribute("value", NumberToString(s.dwEventInstID).c_str());
	pElem_dwEventInstID->SetAttribute("comment", ToUTF8Ptr("事件实例ID"));
	if(rElement.LinkEndChild(pElem_dwEventInstID.get()) != NULL)
		pElem_dwEventInstID.release();
	unique_ptr<TiXmlElement> pElem_dwApplyID(new TiXmlElement("UINT32"));
	if(pElem_dwApplyID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwApplyID->SetAttribute("name", "dwApplyID");
	pElem_dwApplyID->SetAttribute("value", NumberToString(s.dwApplyID).c_str());
	pElem_dwApplyID->SetAttribute("comment", ToUTF8Ptr("具体活动ID"));
	if(rElement.LinkEndChild(pElem_dwApplyID.get()) != NULL)
		pElem_dwApplyID.release();
	unique_ptr<TiXmlElement> pElem_wEventStatus(new TiXmlElement("UINT16"));
	if(pElem_wEventStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wEventStatus->SetAttribute("name", "wEventStatus");
	pElem_wEventStatus->SetAttribute("value", NumberToString(s.wEventStatus).c_str());
	pElem_wEventStatus->SetAttribute("comment", ToUTF8Ptr("事件状态"));
	if(rElement.LinkEndChild(pElem_wEventStatus.get()) != NULL)
		pElem_wEventStatus.release();
	unique_ptr<TiXmlElement> pElem_bySave(new TiXmlElement("UINT8"));
	if(pElem_bySave == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySave->SetAttribute("name", "bySave");
	pElem_bySave->SetAttribute("value", NumberToString(s.bySave).c_str());
	pElem_bySave->SetAttribute("comment", ToUTF8Ptr("是否存数据库"));
	if(rElement.LinkEndChild(pElem_bySave.get()) != NULL)
		pElem_bySave.release();
	unique_ptr<TiXmlElement> pElem_dwParam1(new TiXmlElement("UINT32"));
	if(pElem_dwParam1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwParam1->SetAttribute("name", "dwParam1");
	pElem_dwParam1->SetAttribute("value", NumberToString(s.dwParam1).c_str());
	pElem_dwParam1->SetAttribute("comment", ToUTF8Ptr("统计参数1"));
	if(rElement.LinkEndChild(pElem_dwParam1.get()) != NULL)
		pElem_dwParam1.release();
	unique_ptr<TiXmlElement> pElem_dwParam2(new TiXmlElement("INT32"));
	if(pElem_dwParam2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwParam2->SetAttribute("name", "dwParam2");
	pElem_dwParam2->SetAttribute("value", NumberToString(s.dwParam2).c_str());
	pElem_dwParam2->SetAttribute("comment", ToUTF8Ptr("统计参数2"));
	if(rElement.LinkEndChild(pElem_dwParam2.get()) != NULL)
		pElem_dwParam2.release();
	unique_ptr<TiXmlElement> pElem_dwStartTime(new TiXmlElement("UINT32"));
	if(pElem_dwStartTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStartTime->SetAttribute("name", "dwStartTime");
	pElem_dwStartTime->SetAttribute("value", NumberToString(s.dwStartTime).c_str());
	pElem_dwStartTime->SetAttribute("comment", ToUTF8Ptr("开始时间"));
	if(rElement.LinkEndChild(pElem_dwStartTime.get()) != NULL)
		pElem_dwStartTime.release();
	unique_ptr<TiXmlElement> pElem_dwEndTime(new TiXmlElement("UINT32"));
	if(pElem_dwEndTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEndTime->SetAttribute("name", "dwEndTime");
	pElem_dwEndTime->SetAttribute("value", NumberToString(s.dwEndTime).c_str());
	pElem_dwEndTime->SetAttribute("comment", ToUTF8Ptr("结束时间"));
	if(rElement.LinkEndChild(pElem_dwEndTime.get()) != NULL)
		pElem_dwEndTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecEventInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEventInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecEventInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEventInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SEventOffLine::SEventOffLine() : byServerType(0), dwEventType(0), dwTime(0) { }

SEventOffLine::SEventOffLine(UINT8 byServerType_, UINT32 dwEventType_, UINT32 dwTime_, const std::string& strParam1_, const std::string& strParam2_)
			: byServerType(byServerType_), dwEventType(dwEventType_), dwTime(dwTime_), strParam1(strParam1_), strParam2(strParam2_) { }

SEventOffLine::SEventOffLine(SEventOffLine&& src) : byServerType(src.byServerType), dwEventType(src.dwEventType), dwTime(src.dwTime), strParam1(move(src.strParam1)), strParam2(move(src.strParam2)) { }

SEventOffLine& SEventOffLine::operator=(SEventOffLine&& rhs)
{
	if(this != &rhs)
	{
		this->~SEventOffLine();
		new (this) SEventOffLine(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SEventOffLine& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byServerType;
	src >> s.dwEventType;
	src >> s.dwTime;
	src >> s.strParam1;
	src >> s.strParam2;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEventOffLine& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byServerType;
	src << s.dwEventType;
	src << s.dwTime;
	src << s.strParam1;
	src << s.strParam2;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SEventOffLine& s)
{
	if(strcmp(rElement.Value(), "SEventOffLine") != 0)
	{
		LOG_CRI << "rElement is not SEventOffLine!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byServerType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byServerType") != 0)
	{
		LOG_CRI << "Attribute: name is not byServerType!";
		return false;
	}
	const char* pszVal_byServerType = pElemChild->Attribute("value");
	if(pszVal_byServerType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byServerType, s.byServerType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEventType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEventType") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEventType!";
		return false;
	}
	const char* pszVal_dwEventType = pElemChild->Attribute("value");
	if(pszVal_dwEventType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEventType, s.dwEventType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTime!";
		return false;
	}
	const char* pszVal_dwTime = pElemChild->Attribute("value");
	if(pszVal_dwTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTime, s.dwTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strParam1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strParam1") != 0)
	{
		LOG_CRI << "Attribute: name is not strParam1!";
		return false;
	}
	const char* pszVal_strParam1 = pElemChild->Attribute("value");
	if(pszVal_strParam1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strParam1 = pszVal_strParam1;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strParam2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strParam2") != 0)
	{
		LOG_CRI << "Attribute: name is not strParam2!";
		return false;
	}
	const char* pszVal_strParam2 = pElemChild->Attribute("value");
	if(pszVal_strParam2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strParam2 = pszVal_strParam2;
	return true;
}

bool ToXML(const SEventOffLine& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEventOffLine");
	rElement.SetAttribute("type", ToUTF8Ptr("离线事件"));
	unique_ptr<TiXmlElement> pElem_byServerType(new TiXmlElement("UINT8"));
	if(pElem_byServerType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byServerType->SetAttribute("name", "byServerType");
	pElem_byServerType->SetAttribute("value", NumberToString(s.byServerType).c_str());
	pElem_byServerType->SetAttribute("comment", ToUTF8Ptr("服务器类型"));
	if(rElement.LinkEndChild(pElem_byServerType.get()) != NULL)
		pElem_byServerType.release();
	unique_ptr<TiXmlElement> pElem_dwEventType(new TiXmlElement("UINT32"));
	if(pElem_dwEventType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEventType->SetAttribute("name", "dwEventType");
	pElem_dwEventType->SetAttribute("value", NumberToString(s.dwEventType).c_str());
	pElem_dwEventType->SetAttribute("comment", ToUTF8Ptr("事件类型"));
	if(rElement.LinkEndChild(pElem_dwEventType.get()) != NULL)
		pElem_dwEventType.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("发生时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	unique_ptr<TiXmlElement> pElem_strParam1(new TiXmlElement("string"));
	if(pElem_strParam1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strParam1->SetAttribute("name", "strParam1");
	pElem_strParam1->SetAttribute("value", s.strParam1.c_str());
	pElem_strParam1->SetAttribute("comment", ToUTF8Ptr("TVecUINT32"));
	if(rElement.LinkEndChild(pElem_strParam1.get()) != NULL)
		pElem_strParam1.release();
	unique_ptr<TiXmlElement> pElem_strParam2(new TiXmlElement("string"));
	if(pElem_strParam2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strParam2->SetAttribute("name", "strParam2");
	pElem_strParam2->SetAttribute("value", s.strParam2.c_str());
	pElem_strParam2->SetAttribute("comment", ToUTF8Ptr("字符参数"));
	if(rElement.LinkEndChild(pElem_strParam2.get()) != NULL)
		pElem_strParam2.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecEventOffLine& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEventOffLine s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecEventOffLine& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEventOffLine"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SBuyItemDBInfo::SBuyItemDBInfo() : qwRoleID(0), dwInstID(0), dwCount(0) { }

SBuyItemDBInfo::SBuyItemDBInfo(UINT64 qwRoleID_, UINT32 dwInstID_, UINT32 dwCount_) : qwRoleID(qwRoleID_), dwInstID(dwInstID_), dwCount(dwCount_) { }

CInArchive& operator>>(CInArchive& src, SBuyItemDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.dwInstID;
	src >> s.dwCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBuyItemDBInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.dwInstID;
	src << s.dwCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBuyItemDBInfo& s)
{
	if(strcmp(rElement.Value(), "SBuyItemDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SBuyItemDBInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwInstID!";
		return false;
	}
	const char* pszVal_dwInstID = pElemChild->Attribute("value");
	if(pszVal_dwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwInstID, s.dwInstID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCount!";
		return false;
	}
	const char* pszVal_dwCount = pElemChild->Attribute("value");
	if(pszVal_dwCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCount, s.dwCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBuyItemDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBuyItemDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("物品购买数量db信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_dwInstID(new TiXmlElement("UINT32"));
	if(pElem_dwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwInstID->SetAttribute("name", "dwInstID");
	pElem_dwInstID->SetAttribute("value", NumberToString(s.dwInstID).c_str());
	pElem_dwInstID->SetAttribute("comment", ToUTF8Ptr("实例ID"));
	if(rElement.LinkEndChild(pElem_dwInstID.get()) != NULL)
		pElem_dwInstID.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("物品数量"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBuyItemDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBuyItemDBInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecBuyItemDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBuyItemDBInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SDayTargetDBInfo::SDayTargetDBInfo() : qwRoleID(0), wTaskID(0), byStatus(0), dwProcess(0) { }

SDayTargetDBInfo::SDayTargetDBInfo(UINT64 qwRoleID_, UINT16 wTaskID_, UINT8 byStatus_, UINT32 dwProcess_) : qwRoleID(qwRoleID_), wTaskID(wTaskID_), byStatus(byStatus_), dwProcess(dwProcess_) { }

CInArchive& operator>>(CInArchive& src, SDayTargetDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wTaskID;
	src >> s.byStatus;
	src >> s.dwProcess;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDayTargetDBInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.wTaskID;
	src << s.byStatus;
	src << s.dwProcess;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDayTargetDBInfo& s)
{
	if(strcmp(rElement.Value(), "SDayTargetDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SDayTargetDBInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wTaskID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wTaskID") != 0)
	{
		LOG_CRI << "Attribute: name is not wTaskID!";
		return false;
	}
	const char* pszVal_wTaskID = pElemChild->Attribute("value");
	if(pszVal_wTaskID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wTaskID, s.wTaskID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not byStatus!";
		return false;
	}
	const char* pszVal_byStatus = pElemChild->Attribute("value");
	if(pszVal_byStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStatus, s.byStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwProcess is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwProcess") != 0)
	{
		LOG_CRI << "Attribute: name is not dwProcess!";
		return false;
	}
	const char* pszVal_dwProcess = pElemChild->Attribute("value");
	if(pszVal_dwProcess == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwProcess, s.dwProcess))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDayTargetDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDayTargetDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("7日目标活动信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_wTaskID(new TiXmlElement("UINT16"));
	if(pElem_wTaskID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wTaskID->SetAttribute("name", "wTaskID");
	pElem_wTaskID->SetAttribute("value", NumberToString(s.wTaskID).c_str());
	pElem_wTaskID->SetAttribute("comment", ToUTF8Ptr("任务ID"));
	if(rElement.LinkEndChild(pElem_wTaskID.get()) != NULL)
		pElem_wTaskID.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwProcess(new TiXmlElement("UINT32"));
	if(pElem_dwProcess == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwProcess->SetAttribute("name", "dwProcess");
	pElem_dwProcess->SetAttribute("value", NumberToString(s.dwProcess).c_str());
	pElem_dwProcess->SetAttribute("comment", ToUTF8Ptr("任务进度"));
	if(rElement.LinkEndChild(pElem_dwProcess.get()) != NULL)
		pElem_dwProcess.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDayTargetDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDayTargetDBInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecDayTargetDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDayTargetDBInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SBattleArrayDBInfo::SBattleArrayDBInfo() : qwRoleID(0), wBattleArrayID(0), dwBattleArrayLevelID(0), byBattleArrayStatus(0) { }

SBattleArrayDBInfo::SBattleArrayDBInfo(UINT64 qwRoleID_, UINT16 wBattleArrayID_, UINT32 dwBattleArrayLevelID_, UINT8 byBattleArrayStatus_) : qwRoleID(qwRoleID_), wBattleArrayID(wBattleArrayID_), dwBattleArrayLevelID(dwBattleArrayLevelID_), byBattleArrayStatus(byBattleArrayStatus_) { }

CInArchive& operator>>(CInArchive& src, SBattleArrayDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wBattleArrayID;
	src >> s.dwBattleArrayLevelID;
	src >> s.byBattleArrayStatus;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleArrayDBInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.wBattleArrayID;
	src << s.dwBattleArrayLevelID;
	src << s.byBattleArrayStatus;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleArrayDBInfo& s)
{
	if(strcmp(rElement.Value(), "SBattleArrayDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SBattleArrayDBInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBattleArrayID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBattleArrayID") != 0)
	{
		LOG_CRI << "Attribute: name is not wBattleArrayID!";
		return false;
	}
	const char* pszVal_wBattleArrayID = pElemChild->Attribute("value");
	if(pszVal_wBattleArrayID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBattleArrayID, s.wBattleArrayID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBattleArrayLevelID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBattleArrayLevelID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBattleArrayLevelID!";
		return false;
	}
	const char* pszVal_dwBattleArrayLevelID = pElemChild->Attribute("value");
	if(pszVal_dwBattleArrayLevelID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBattleArrayLevelID, s.dwBattleArrayLevelID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBattleArrayStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBattleArrayStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not byBattleArrayStatus!";
		return false;
	}
	const char* pszVal_byBattleArrayStatus = pElemChild->Attribute("value");
	if(pszVal_byBattleArrayStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBattleArrayStatus, s.byBattleArrayStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleArrayDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleArrayDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("破阵信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_wBattleArrayID(new TiXmlElement("UINT16"));
	if(pElem_wBattleArrayID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBattleArrayID->SetAttribute("name", "wBattleArrayID");
	pElem_wBattleArrayID->SetAttribute("value", NumberToString(s.wBattleArrayID).c_str());
	pElem_wBattleArrayID->SetAttribute("comment", ToUTF8Ptr("阵id"));
	if(rElement.LinkEndChild(pElem_wBattleArrayID.get()) != NULL)
		pElem_wBattleArrayID.release();
	unique_ptr<TiXmlElement> pElem_dwBattleArrayLevelID(new TiXmlElement("UINT32"));
	if(pElem_dwBattleArrayLevelID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattleArrayLevelID->SetAttribute("name", "dwBattleArrayLevelID");
	pElem_dwBattleArrayLevelID->SetAttribute("value", NumberToString(s.dwBattleArrayLevelID).c_str());
	pElem_dwBattleArrayLevelID->SetAttribute("comment", ToUTF8Ptr("进度(阵图id)"));
	if(rElement.LinkEndChild(pElem_dwBattleArrayLevelID.get()) != NULL)
		pElem_dwBattleArrayLevelID.release();
	unique_ptr<TiXmlElement> pElem_byBattleArrayStatus(new TiXmlElement("UINT8"));
	if(pElem_byBattleArrayStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBattleArrayStatus->SetAttribute("name", "byBattleArrayStatus");
	pElem_byBattleArrayStatus->SetAttribute("value", NumberToString(s.byBattleArrayStatus).c_str());
	pElem_byBattleArrayStatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byBattleArrayStatus.get()) != NULL)
		pElem_byBattleArrayStatus.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleArrayDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleArrayDBInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecBattleArrayDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleArrayDBInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SAutoStoreDBInfo::SAutoStoreDBInfo() : qwRoleID(0), wType(0), dwClassID(0), dwValue(0) { }

SAutoStoreDBInfo::SAutoStoreDBInfo(UINT64 qwRoleID_, UINT16 wType_, UINT32 dwClassID_, UINT32 dwValue_) : qwRoleID(qwRoleID_), wType(wType_), dwClassID(dwClassID_), dwValue(dwValue_) { }

CInArchive& operator>>(CInArchive& src, SAutoStoreDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wType;
	src >> s.dwClassID;
	src >> s.dwValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SAutoStoreDBInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.wType;
	src << s.dwClassID;
	src << s.dwValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SAutoStoreDBInfo& s)
{
	if(strcmp(rElement.Value(), "SAutoStoreDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SAutoStoreDBInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wType") != 0)
	{
		LOG_CRI << "Attribute: name is not wType!";
		return false;
	}
	const char* pszVal_wType = pElemChild->Attribute("value");
	if(pszVal_wType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wType, s.wType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwClassID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwClassID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwClassID!";
		return false;
	}
	const char* pszVal_dwClassID = pElemChild->Attribute("value");
	if(pszVal_dwClassID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwClassID, s.dwClassID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwValue!";
		return false;
	}
	const char* pszVal_dwValue = pElemChild->Attribute("value");
	if(pszVal_dwValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwValue, s.dwValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SAutoStoreDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SAutoStoreDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("动态存储信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_wType(new TiXmlElement("UINT16"));
	if(pElem_wType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wType->SetAttribute("name", "wType");
	pElem_wType->SetAttribute("value", NumberToString(s.wType).c_str());
	pElem_wType->SetAttribute("comment", ToUTF8Ptr("大类"));
	if(rElement.LinkEndChild(pElem_wType.get()) != NULL)
		pElem_wType.release();
	unique_ptr<TiXmlElement> pElem_dwClassID(new TiXmlElement("UINT32"));
	if(pElem_dwClassID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwClassID->SetAttribute("name", "dwClassID");
	pElem_dwClassID->SetAttribute("value", NumberToString(s.dwClassID).c_str());
	pElem_dwClassID->SetAttribute("comment", ToUTF8Ptr("小类"));
	if(rElement.LinkEndChild(pElem_dwClassID.get()) != NULL)
		pElem_dwClassID.release();
	unique_ptr<TiXmlElement> pElem_dwValue(new TiXmlElement("UINT32"));
	if(pElem_dwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValue->SetAttribute("name", "dwValue");
	pElem_dwValue->SetAttribute("value", NumberToString(s.dwValue).c_str());
	pElem_dwValue->SetAttribute("comment", ToUTF8Ptr("数值"));
	if(rElement.LinkEndChild(pElem_dwValue.get()) != NULL)
		pElem_dwValue.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecAutoStoreDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SAutoStoreDBInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecAutoStoreDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SAutoStoreDBInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SFightFormationDBInfo::SFightFormationDBInfo() : qwRoleID(0), wBattleType(0), wFormationID(0) { }

SFightFormationDBInfo::SFightFormationDBInfo(UINT64 qwRoleID_, UINT16 wBattleType_, UINT16 wFormationID_, const std::string& strBattlePosInfo_) : qwRoleID(qwRoleID_), wBattleType(wBattleType_), wFormationID(wFormationID_), strBattlePosInfo(strBattlePosInfo_) { }

SFightFormationDBInfo::SFightFormationDBInfo(SFightFormationDBInfo&& src) : qwRoleID(src.qwRoleID), wBattleType(src.wBattleType), wFormationID(src.wFormationID), strBattlePosInfo(move(src.strBattlePosInfo)) { }

SFightFormationDBInfo& SFightFormationDBInfo::operator=(SFightFormationDBInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SFightFormationDBInfo();
		new (this) SFightFormationDBInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SFightFormationDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wBattleType;
	src >> s.wFormationID;
	src >> s.strBattlePosInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFightFormationDBInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.wBattleType;
	src << s.wFormationID;
	src << s.strBattlePosInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFightFormationDBInfo& s)
{
	if(strcmp(rElement.Value(), "SFightFormationDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SFightFormationDBInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBattleType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBattleType") != 0)
	{
		LOG_CRI << "Attribute: name is not wBattleType!";
		return false;
	}
	const char* pszVal_wBattleType = pElemChild->Attribute("value");
	if(pszVal_wBattleType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBattleType, s.wBattleType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wFormationID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFormationID") != 0)
	{
		LOG_CRI << "Attribute: name is not wFormationID!";
		return false;
	}
	const char* pszVal_wFormationID = pElemChild->Attribute("value");
	if(pszVal_wFormationID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFormationID, s.wFormationID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strBattlePosInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strBattlePosInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not strBattlePosInfo!";
		return false;
	}
	const char* pszVal_strBattlePosInfo = pElemChild->Attribute("value");
	if(pszVal_strBattlePosInfo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strBattlePosInfo = pszVal_strBattlePosInfo;
	return true;
}

bool ToXML(const SFightFormationDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFightFormationDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("新阵型信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_wBattleType(new TiXmlElement("UINT16"));
	if(pElem_wBattleType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBattleType->SetAttribute("name", "wBattleType");
	pElem_wBattleType->SetAttribute("value", NumberToString(s.wBattleType).c_str());
	pElem_wBattleType->SetAttribute("comment", ToUTF8Ptr("战斗类型"));
	if(rElement.LinkEndChild(pElem_wBattleType.get()) != NULL)
		pElem_wBattleType.release();
	unique_ptr<TiXmlElement> pElem_wFormationID(new TiXmlElement("UINT16"));
	if(pElem_wFormationID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFormationID->SetAttribute("name", "wFormationID");
	pElem_wFormationID->SetAttribute("value", NumberToString(s.wFormationID).c_str());
	pElem_wFormationID->SetAttribute("comment", ToUTF8Ptr("当前阵形ID"));
	if(rElement.LinkEndChild(pElem_wFormationID.get()) != NULL)
		pElem_wFormationID.release();
	unique_ptr<TiXmlElement> pElem_strBattlePosInfo(new TiXmlElement("string"));
	if(pElem_strBattlePosInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strBattlePosInfo->SetAttribute("name", "strBattlePosInfo");
	pElem_strBattlePosInfo->SetAttribute("value", s.strBattlePosInfo.c_str());
	pElem_strBattlePosInfo->SetAttribute("comment", ToUTF8Ptr("阵型信息"));
	if(rElement.LinkEndChild(pElem_strBattlePosInfo.get()) != NULL)
		pElem_strBattlePosInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFightFormationDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFightFormationDBInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecFightFormationDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFightFormationDBInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SFightHeroDBInfo::SFightHeroDBInfo() : qwRoleID(0), wBattleType(0), qwInstID(0), dwHP(0), dwMaxHP(0), 
			dwAura(0), dwMaxAura(0) { }

SFightHeroDBInfo::SFightHeroDBInfo(UINT64 qwRoleID_, UINT16 wBattleType_, UINT64 qwInstID_, UINT32 dwHP_, UINT32 dwMaxHP_, 
			UINT32 dwAura_, UINT32 dwMaxAura_)
			: qwRoleID(qwRoleID_), wBattleType(wBattleType_), qwInstID(qwInstID_), dwHP(dwHP_), dwMaxHP(dwMaxHP_), 
			dwAura(dwAura_), dwMaxAura(dwMaxAura_) { }

CInArchive& operator>>(CInArchive& src, SFightHeroDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wBattleType;
	src >> s.qwInstID;
	src >> s.dwHP;
	src >> s.dwMaxHP;
	src >> s.dwAura;
	src >> s.dwMaxAura;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFightHeroDBInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.wBattleType;
	src << s.qwInstID;
	src << s.dwHP;
	src << s.dwMaxHP;
	src << s.dwAura;
	src << s.dwMaxAura;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFightHeroDBInfo& s)
{
	if(strcmp(rElement.Value(), "SFightHeroDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SFightHeroDBInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBattleType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBattleType") != 0)
	{
		LOG_CRI << "Attribute: name is not wBattleType!";
		return false;
	}
	const char* pszVal_wBattleType = pElemChild->Attribute("value");
	if(pszVal_wBattleType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBattleType, s.wBattleType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID!";
		return false;
	}
	const char* pszVal_qwInstID = pElemChild->Attribute("value");
	if(pszVal_qwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID, s.qwInstID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHP!";
		return false;
	}
	const char* pszVal_dwHP = pElemChild->Attribute("value");
	if(pszVal_dwHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHP, s.dwHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMaxHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMaxHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMaxHP!";
		return false;
	}
	const char* pszVal_dwMaxHP = pElemChild->Attribute("value");
	if(pszVal_dwMaxHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMaxHP, s.dwMaxHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAura is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAura") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAura!";
		return false;
	}
	const char* pszVal_dwAura = pElemChild->Attribute("value");
	if(pszVal_dwAura == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAura, s.dwAura))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMaxAura is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMaxAura") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMaxAura!";
		return false;
	}
	const char* pszVal_dwMaxAura = pElemChild->Attribute("value");
	if(pszVal_dwMaxAura == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMaxAura, s.dwMaxAura))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFightHeroDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFightHeroDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗散仙数据"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_wBattleType(new TiXmlElement("UINT16"));
	if(pElem_wBattleType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBattleType->SetAttribute("name", "wBattleType");
	pElem_wBattleType->SetAttribute("value", NumberToString(s.wBattleType).c_str());
	pElem_wBattleType->SetAttribute("comment", ToUTF8Ptr("战斗类型"));
	if(rElement.LinkEndChild(pElem_wBattleType.get()) != NULL)
		pElem_wBattleType.release();
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("散仙instID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_dwHP(new TiXmlElement("UINT32"));
	if(pElem_dwHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHP->SetAttribute("name", "dwHP");
	pElem_dwHP->SetAttribute("value", NumberToString(s.dwHP).c_str());
	pElem_dwHP->SetAttribute("comment", ToUTF8Ptr("当前生命值"));
	if(rElement.LinkEndChild(pElem_dwHP.get()) != NULL)
		pElem_dwHP.release();
	unique_ptr<TiXmlElement> pElem_dwMaxHP(new TiXmlElement("UINT32"));
	if(pElem_dwMaxHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxHP->SetAttribute("name", "dwMaxHP");
	pElem_dwMaxHP->SetAttribute("value", NumberToString(s.dwMaxHP).c_str());
	pElem_dwMaxHP->SetAttribute("comment", ToUTF8Ptr("最大生命值（可能用到）"));
	if(rElement.LinkEndChild(pElem_dwMaxHP.get()) != NULL)
		pElem_dwMaxHP.release();
	unique_ptr<TiXmlElement> pElem_dwAura(new TiXmlElement("UINT32"));
	if(pElem_dwAura == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAura->SetAttribute("name", "dwAura");
	pElem_dwAura->SetAttribute("value", NumberToString(s.dwAura).c_str());
	pElem_dwAura->SetAttribute("comment", ToUTF8Ptr("灵气值"));
	if(rElement.LinkEndChild(pElem_dwAura.get()) != NULL)
		pElem_dwAura.release();
	unique_ptr<TiXmlElement> pElem_dwMaxAura(new TiXmlElement("UINT32"));
	if(pElem_dwMaxAura == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxAura->SetAttribute("name", "dwMaxAura");
	pElem_dwMaxAura->SetAttribute("value", NumberToString(s.dwMaxAura).c_str());
	pElem_dwMaxAura->SetAttribute("comment", ToUTF8Ptr("灵气值"));
	if(rElement.LinkEndChild(pElem_dwMaxAura.get()) != NULL)
		pElem_dwMaxAura.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFightHeroDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFightHeroDBInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecFightHeroDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFightHeroDBInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

RoleDataInfo::RoleDataInfo() : qwRoleId(0) { }

RoleDataInfo::RoleDataInfo(RoleDataInfo&& src) : qwRoleId(src.qwRoleId), stBaseInfo(move(src.stBaseInfo)), vecFighterInfo(move(src.vecFighterInfo)), vecSkillInfo(move(src.vecSkillInfo)), vecPassiveSkillInfo(move(src.vecPassiveSkillInfo)), 
			vecFighterCombination(move(src.vecFighterCombination)), vecRoleItemInfo(move(src.vecRoleItemInfo)), vecFriendsInfo(move(src.vecFriendsInfo)), vecRoleDgnInfo(move(src.vecRoleDgnInfo)), vecRoleTaskInfo(move(src.vecRoleTaskInfo)), 
			vecGameVars(move(src.vecGameVars)), vecRoleSlotsInfo(move(src.vecRoleSlotsInfo)), vecFormationInfo(move(src.vecFormationInfo)), vecPetDataInfo(move(src.vecPetDataInfo)), oRolePetInfo(src.oRolePetInfo), 
			vecBeastSoulInfo(move(src.vecBeastSoulInfo)), vecFireInfo(move(src.vecFireInfo)), vecArenaInfo(move(src.vecArenaInfo)), vecDBBuffInfo(move(src.vecDBBuffInfo)), vecSoulSpaceInfo(move(src.vecSoulSpaceInfo)), 
			vecBubbleInfo(move(src.vecBubbleInfo)), vecHorseDB(move(src.vecHorseDB)), sGroupInfo(src.sGroupInfo), sYaMenInfo(src.sYaMenInfo), vecActivityTask(move(src.vecActivityTask)), 
			vecTitle(move(src.vecTitle)), vecAchievementInfo(move(src.vecAchievementInfo)), vecCollectionInfo(move(src.vecCollectionInfo)), vecRoleAttaked(move(src.vecRoleAttaked)), vecExchangeInfo(move(src.vecExchangeInfo)), 
			vecSweepInfo(move(src.vecSweepInfo)), vecPendRes(move(src.vecPendRes)), vecXinFaDBInfo(move(src.vecXinFaDBInfo)), vecLevelPrize(move(src.vecLevelPrize)), vecPlatformParam(move(src.vecPlatformParam)), 
			vecEventInfo(move(src.vecEventInfo)), vecEventOffLine(move(src.vecEventOffLine)), vecBuyItemDBInfo(move(src.vecBuyItemDBInfo)), vecDayTargetDBInfo(move(src.vecDayTargetDBInfo)), vecBattleArrayDBInfo(move(src.vecBattleArrayDBInfo)), 
			vecAutoStoreDBInfo(move(src.vecAutoStoreDBInfo)), vecTHDBInfo(move(src.vecTHDBInfo)), vecBeauty(move(src.vecBeauty)), vecFightFormationDBInfo(move(src.vecFightFormationDBInfo)), vecFightHeroDBInfo(move(src.vecFightHeroDBInfo)), 
			sShipData(src.sShipData), vecShipReport(move(src.vecShipReport)), vecGEMDBInfo(move(src.vecGEMDBInfo)), vecShengLing(move(src.vecShengLing)), vecShengLingPrize(move(src.vecShengLingPrize)) { }

RoleDataInfo& RoleDataInfo::operator=(RoleDataInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~RoleDataInfo();
		new (this) RoleDataInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, RoleDataInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleId;
	src >> s.stBaseInfo;
	src >> s.vecFighterInfo;
	src >> s.vecSkillInfo;
	src >> s.vecPassiveSkillInfo;
	src >> s.vecFighterCombination;
	src >> s.vecRoleItemInfo;
	src >> s.vecFriendsInfo;
	src >> s.vecRoleDgnInfo;
	src >> s.vecRoleTaskInfo;
	src >> s.vecGameVars;
	src >> s.vecRoleSlotsInfo;
	src >> s.vecFormationInfo;
	src >> s.vecPetDataInfo;
	src >> s.oRolePetInfo;
	src >> s.vecBeastSoulInfo;
	src >> s.vecFireInfo;
	src >> s.vecArenaInfo;
	src >> s.vecDBBuffInfo;
	src >> s.vecSoulSpaceInfo;
	src >> s.vecBubbleInfo;
	src >> s.vecHorseDB;
	src >> s.sGroupInfo;
	src >> s.sYaMenInfo;
	src >> s.vecActivityTask;
	src >> s.vecTitle;
	src >> s.vecAchievementInfo;
	src >> s.vecCollectionInfo;
	src >> s.vecRoleAttaked;
	src >> s.vecExchangeInfo;
	src >> s.vecSweepInfo;
	src >> s.vecPendRes;
	src >> s.vecXinFaDBInfo;
	src >> s.vecLevelPrize;
	src >> s.vecPlatformParam;
	src >> s.vecEventInfo;
	src >> s.vecEventOffLine;
	src >> s.vecBuyItemDBInfo;
	src >> s.vecDayTargetDBInfo;
	src >> s.vecBattleArrayDBInfo;
	src >> s.vecAutoStoreDBInfo;
	src >> s.vecTHDBInfo;
	src >> s.vecBeauty;
	src >> s.vecFightFormationDBInfo;
	src >> s.vecFightHeroDBInfo;
	src >> s.sShipData;
	src >> s.vecShipReport;
	src >> s.vecGEMDBInfo;
	src >> s.vecShengLing;
	src >> s.vecShengLingPrize;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const RoleDataInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleId;
	src << s.stBaseInfo;
	src << s.vecFighterInfo;
	src << s.vecSkillInfo;
	src << s.vecPassiveSkillInfo;
	src << s.vecFighterCombination;
	src << s.vecRoleItemInfo;
	src << s.vecFriendsInfo;
	src << s.vecRoleDgnInfo;
	src << s.vecRoleTaskInfo;
	src << s.vecGameVars;
	src << s.vecRoleSlotsInfo;
	src << s.vecFormationInfo;
	src << s.vecPetDataInfo;
	src << s.oRolePetInfo;
	src << s.vecBeastSoulInfo;
	src << s.vecFireInfo;
	src << s.vecArenaInfo;
	src << s.vecDBBuffInfo;
	src << s.vecSoulSpaceInfo;
	src << s.vecBubbleInfo;
	src << s.vecHorseDB;
	src << s.sGroupInfo;
	src << s.sYaMenInfo;
	src << s.vecActivityTask;
	src << s.vecTitle;
	src << s.vecAchievementInfo;
	src << s.vecCollectionInfo;
	src << s.vecRoleAttaked;
	src << s.vecExchangeInfo;
	src << s.vecSweepInfo;
	src << s.vecPendRes;
	src << s.vecXinFaDBInfo;
	src << s.vecLevelPrize;
	src << s.vecPlatformParam;
	src << s.vecEventInfo;
	src << s.vecEventOffLine;
	src << s.vecBuyItemDBInfo;
	src << s.vecDayTargetDBInfo;
	src << s.vecBattleArrayDBInfo;
	src << s.vecAutoStoreDBInfo;
	src << s.vecTHDBInfo;
	src << s.vecBeauty;
	src << s.vecFightFormationDBInfo;
	src << s.vecFightHeroDBInfo;
	src << s.sShipData;
	src << s.vecShipReport;
	src << s.vecGEMDBInfo;
	src << s.vecShengLing;
	src << s.vecShengLingPrize;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, RoleDataInfo& s)
{
	if(strcmp(rElement.Value(), "RoleDataInfo") != 0)
	{
		LOG_CRI << "rElement is not RoleDataInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleId!";
		return false;
	}
	const char* pszVal_qwRoleId = pElemChild->Attribute("value");
	if(pszVal_qwRoleId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleId, s.qwRoleId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for stBaseInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "RoleBaseInfo") != 0)
	{
		LOG_CRI << "pElemChild is not RoleBaseInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stBaseInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not stBaseInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stBaseInfo))
	{
		LOG_CRI << "FromXML for: stBaseInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFighterInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "FighterProt::TVecFighterDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not FighterProt::TVecFighterDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFighterInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFighterInfo!";
		return false;
	}
	if(!NFighterProt::VectorFromXML(*pElemChild, s.vecFighterInfo))
	{
		LOG_CRI << "VectorFromXML for vecFighterInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecSkillInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "FighterProt::TVecSkillDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not FighterProt::TVecSkillDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecSkillInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecSkillInfo!";
		return false;
	}
	if(!NFighterProt::VectorFromXML(*pElemChild, s.vecSkillInfo))
	{
		LOG_CRI << "VectorFromXML for vecSkillInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPassiveSkillInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "FighterProt::TVecPassiveSkillDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not FighterProt::TVecPassiveSkillDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPassiveSkillInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPassiveSkillInfo!";
		return false;
	}
	if(!NFighterProt::VectorFromXML(*pElemChild, s.vecPassiveSkillInfo))
	{
		LOG_CRI << "VectorFromXML for vecPassiveSkillInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFighterCombination is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "FighterProt::TVecFighterCombination") != 0)
	{
		LOG_CRI << "pElemChild is not FighterProt::TVecFighterCombination!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFighterCombination") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFighterCombination!";
		return false;
	}
	if(!NFighterProt::VectorFromXML(*pElemChild, s.vecFighterCombination))
	{
		LOG_CRI << "VectorFromXML for vecFighterCombination fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecRoleItemInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecItem") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecItem!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecRoleItemInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecRoleItemInfo!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.vecRoleItemInfo))
	{
		LOG_CRI << "VectorFromXML for vecRoleItemInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFriendsInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "FriendProt::TVecFriendDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not FriendProt::TVecFriendDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFriendsInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFriendsInfo!";
		return false;
	}
	if(!NFriendProt::VectorFromXML(*pElemChild, s.vecFriendsInfo))
	{
		LOG_CRI << "VectorFromXML for vecFriendsInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecRoleDgnInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecRoleDgnInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecRoleDgnInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecRoleDgnInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecRoleDgnInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecRoleDgnInfo))
	{
		LOG_CRI << "VectorFromXML for vecRoleDgnInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecRoleTaskInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecRoleTaskInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecRoleTaskInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecRoleTaskInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecRoleTaskInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecRoleTaskInfo))
	{
		LOG_CRI << "VectorFromXML for vecRoleTaskInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecGameVars is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecVarsDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecVarsDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecGameVars") != 0)
	{
		LOG_CRI << "Attribute: name is not vecGameVars!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecGameVars))
	{
		LOG_CRI << "VectorFromXML for vecGameVars fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecRoleSlotsInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecRoleSlotsInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecRoleSlotsInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecRoleSlotsInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecRoleSlotsInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecRoleSlotsInfo))
	{
		LOG_CRI << "VectorFromXML for vecRoleSlotsInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFormationInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecFormationInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecFormationInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFormationInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFormationInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecFormationInfo))
	{
		LOG_CRI << "VectorFromXML for vecFormationInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPetDataInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecPetDataInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecPetDataInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPetDataInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPetDataInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecPetDataInfo))
	{
		LOG_CRI << "VectorFromXML for vecPetDataInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for oRolePetInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SRolePetInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SRolePetInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oRolePetInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not oRolePetInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.oRolePetInfo))
	{
		LOG_CRI << "FromXML for: oRolePetInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBeastSoulInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBeastSoulInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBeastSoulInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBeastSoulInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBeastSoulInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecBeastSoulInfo))
	{
		LOG_CRI << "VectorFromXML for vecBeastSoulInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFireInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TripodProt::TVecFireInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TripodProt::TVecFireInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFireInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFireInfo!";
		return false;
	}
	if(!NTripodProt::VectorFromXML(*pElemChild, s.vecFireInfo))
	{
		LOG_CRI << "VectorFromXML for vecFireInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecArenaInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecRoleArenaInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecRoleArenaInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecArenaInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecArenaInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecArenaInfo))
	{
		LOG_CRI << "VectorFromXML for vecArenaInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecDBBuffInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::TVecDBBuffInfo") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::TVecDBBuffInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecDBBuffInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecDBBuffInfo!";
		return false;
	}
	if(!NProtoCommon::VectorFromXML(*pElemChild, s.vecDBBuffInfo))
	{
		LOG_CRI << "VectorFromXML for vecDBBuffInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecSoulSpaceInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecSoulSpaceInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecSoulSpaceInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecSoulSpaceInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecSoulSpaceInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecSoulSpaceInfo))
	{
		LOG_CRI << "VectorFromXML for vecSoulSpaceInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBubbleInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecDBBubbleInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecDBBubbleInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBubbleInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBubbleInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecBubbleInfo))
	{
		LOG_CRI << "VectorFromXML for vecBubbleInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecHorseDB is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "Horse::TVecHorseDB") != 0)
	{
		LOG_CRI << "pElemChild is not Horse::TVecHorseDB!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecHorseDB") != 0)
	{
		LOG_CRI << "Attribute: name is not vecHorseDB!";
		return false;
	}
	if(!NHorse::VectorFromXML(*pElemChild, s.vecHorseDB))
	{
		LOG_CRI << "VectorFromXML for vecHorseDB fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sGroupInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SGroupTaskInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SGroupTaskInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sGroupInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sGroupInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sGroupInfo))
	{
		LOG_CRI << "FromXML for: sGroupInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sYaMenInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SYaMenTaskInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SYaMenTaskInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sYaMenInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sYaMenInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sYaMenInfo))
	{
		LOG_CRI << "FromXML for: sYaMenInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecActivityTask is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecActivityTaskInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecActivityTaskInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecActivityTask") != 0)
	{
		LOG_CRI << "Attribute: name is not vecActivityTask!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecActivityTask))
	{
		LOG_CRI << "VectorFromXML for vecActivityTask fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecTitle") != 0)
	{
		LOG_CRI << "pElemChild is not TVecTitle!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTitle!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecTitle))
	{
		LOG_CRI << "VectorFromXML for vecTitle fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecAchievementInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "AchievementProt::TVecAchievementInfo") != 0)
	{
		LOG_CRI << "pElemChild is not AchievementProt::TVecAchievementInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecAchievementInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecAchievementInfo!";
		return false;
	}
	if(!NAchievementProt::VectorFromXML(*pElemChild, s.vecAchievementInfo))
	{
		LOG_CRI << "VectorFromXML for vecAchievementInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecCollectionInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "CollectionProt::TVecCollectionInfo") != 0)
	{
		LOG_CRI << "pElemChild is not CollectionProt::TVecCollectionInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecCollectionInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecCollectionInfo!";
		return false;
	}
	if(!NCollectionProt::VectorFromXML(*pElemChild, s.vecCollectionInfo))
	{
		LOG_CRI << "VectorFromXML for vecCollectionInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecRoleAttaked is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "DemonTower::TVecRoleAttaked") != 0)
	{
		LOG_CRI << "pElemChild is not DemonTower::TVecRoleAttaked!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecRoleAttaked") != 0)
	{
		LOG_CRI << "Attribute: name is not vecRoleAttaked!";
		return false;
	}
	if(!NDemonTower::VectorFromXML(*pElemChild, s.vecRoleAttaked))
	{
		LOG_CRI << "VectorFromXML for vecRoleAttaked fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecExchangeInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ExchangeShopProt::TVecExchangeInfo") != 0)
	{
		LOG_CRI << "pElemChild is not ExchangeShopProt::TVecExchangeInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecExchangeInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecExchangeInfo!";
		return false;
	}
	if(!NExchangeShopProt::VectorFromXML(*pElemChild, s.vecExchangeInfo))
	{
		LOG_CRI << "VectorFromXML for vecExchangeInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecSweepInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "DungeonProt::TVecSweepInfo") != 0)
	{
		LOG_CRI << "pElemChild is not DungeonProt::TVecSweepInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecSweepInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecSweepInfo!";
		return false;
	}
	if(!NDungeonProt::VectorFromXML(*pElemChild, s.vecSweepInfo))
	{
		LOG_CRI << "VectorFromXML for vecSweepInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPendRes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecPendRes") != 0)
	{
		LOG_CRI << "pElemChild is not TVecPendRes!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPendRes") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPendRes!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecPendRes))
	{
		LOG_CRI << "VectorFromXML for vecPendRes fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecXinFaDBInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "FighterProt::TVecXinFaDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not FighterProt::TVecXinFaDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecXinFaDBInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecXinFaDBInfo!";
		return false;
	}
	if(!NFighterProt::VectorFromXML(*pElemChild, s.vecXinFaDBInfo))
	{
		LOG_CRI << "VectorFromXML for vecXinFaDBInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecLevelPrize is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "LevelPrize::TVecPrize2DB") != 0)
	{
		LOG_CRI << "pElemChild is not LevelPrize::TVecPrize2DB!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecLevelPrize") != 0)
	{
		LOG_CRI << "Attribute: name is not vecLevelPrize!";
		return false;
	}
	if(!NLevelPrize::VectorFromXML(*pElemChild, s.vecLevelPrize))
	{
		LOG_CRI << "VectorFromXML for vecLevelPrize fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPlatformParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::TVecPlatformParam") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::TVecPlatformParam!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPlatformParam") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPlatformParam!";
		return false;
	}
	if(!NProtoCommon::VectorFromXML(*pElemChild, s.vecPlatformParam))
	{
		LOG_CRI << "VectorFromXML for vecPlatformParam fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecEventInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecEventInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecEventInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecEventInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecEventInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecEventInfo))
	{
		LOG_CRI << "VectorFromXML for vecEventInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecEventOffLine is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecEventOffLine") != 0)
	{
		LOG_CRI << "pElemChild is not TVecEventOffLine!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecEventOffLine") != 0)
	{
		LOG_CRI << "Attribute: name is not vecEventOffLine!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecEventOffLine))
	{
		LOG_CRI << "VectorFromXML for vecEventOffLine fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBuyItemDBInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBuyItemDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBuyItemDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBuyItemDBInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBuyItemDBInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecBuyItemDBInfo))
	{
		LOG_CRI << "VectorFromXML for vecBuyItemDBInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecDayTargetDBInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecDayTargetDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecDayTargetDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecDayTargetDBInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecDayTargetDBInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecDayTargetDBInfo))
	{
		LOG_CRI << "VectorFromXML for vecDayTargetDBInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBattleArrayDBInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleArrayDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleArrayDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBattleArrayDBInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBattleArrayDBInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecBattleArrayDBInfo))
	{
		LOG_CRI << "VectorFromXML for vecBattleArrayDBInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecAutoStoreDBInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecAutoStoreDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecAutoStoreDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecAutoStoreDBInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecAutoStoreDBInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecAutoStoreDBInfo))
	{
		LOG_CRI << "VectorFromXML for vecAutoStoreDBInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTHDBInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TreasureHuntProt::TVecTHDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TreasureHuntProt::TVecTHDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTHDBInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTHDBInfo!";
		return false;
	}
	if(!NTreasureHuntProt::VectorFromXML(*pElemChild, s.vecTHDBInfo))
	{
		LOG_CRI << "VectorFromXML for vecTHDBInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBeauty is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "Beauty::TVecBeauty") != 0)
	{
		LOG_CRI << "pElemChild is not Beauty::TVecBeauty!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBeauty") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBeauty!";
		return false;
	}
	if(!NBeauty::VectorFromXML(*pElemChild, s.vecBeauty))
	{
		LOG_CRI << "VectorFromXML for vecBeauty fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFightFormationDBInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecFightFormationDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecFightFormationDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFightFormationDBInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFightFormationDBInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecFightFormationDBInfo))
	{
		LOG_CRI << "VectorFromXML for vecFightFormationDBInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFightHeroDBInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecFightHeroDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecFightHeroDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFightHeroDBInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFightHeroDBInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecFightHeroDBInfo))
	{
		LOG_CRI << "VectorFromXML for vecFightHeroDBInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sShipData is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ShipProt::PlayerSelfShipData") != 0)
	{
		LOG_CRI << "pElemChild is not ShipProt::PlayerSelfShipData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sShipData") != 0)
	{
		LOG_CRI << "Attribute: name is not sShipData!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sShipData))
	{
		LOG_CRI << "FromXML for: sShipData fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecShipReport is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ShipProt::TVecShipReport") != 0)
	{
		LOG_CRI << "pElemChild is not ShipProt::TVecShipReport!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecShipReport") != 0)
	{
		LOG_CRI << "Attribute: name is not vecShipReport!";
		return false;
	}
	if(!NShipProt::VectorFromXML(*pElemChild, s.vecShipReport))
	{
		LOG_CRI << "VectorFromXML for vecShipReport fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecGEMDBInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "GuardEMeiProt::TVecGEMDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not GuardEMeiProt::TVecGEMDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecGEMDBInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecGEMDBInfo!";
		return false;
	}
	if(!NGuardEMeiProt::VectorFromXML(*pElemChild, s.vecGEMDBInfo))
	{
		LOG_CRI << "VectorFromXML for vecGEMDBInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecShengLing is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ShengLingProt::TVecShengLingInfo2DB") != 0)
	{
		LOG_CRI << "pElemChild is not ShengLingProt::TVecShengLingInfo2DB!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecShengLing") != 0)
	{
		LOG_CRI << "Attribute: name is not vecShengLing!";
		return false;
	}
	if(!NShengLingProt::VectorFromXML(*pElemChild, s.vecShengLing))
	{
		LOG_CRI << "VectorFromXML for vecShengLing fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecShengLingPrize is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ShengLingProt::TVecShengLingPrize2DB") != 0)
	{
		LOG_CRI << "pElemChild is not ShengLingProt::TVecShengLingPrize2DB!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecShengLingPrize") != 0)
	{
		LOG_CRI << "Attribute: name is not vecShengLingPrize!";
		return false;
	}
	if(!NShengLingProt::VectorFromXML(*pElemChild, s.vecShengLingPrize))
	{
		LOG_CRI << "VectorFromXML for vecShengLingPrize fails!";
		return false;
	}
	return true;
}

bool ToXML(const RoleDataInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("RoleDataInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家整体数据"));
	unique_ptr<TiXmlElement> pElem_qwRoleId(new TiXmlElement("UINT64"));
	if(pElem_qwRoleId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleId->SetAttribute("name", "qwRoleId");
	pElem_qwRoleId->SetAttribute("value", NumberToString(s.qwRoleId).c_str());
	pElem_qwRoleId->SetAttribute("comment", ToUTF8Ptr("玩家RoleId"));
	if(rElement.LinkEndChild(pElem_qwRoleId.get()) != NULL)
		pElem_qwRoleId.release();
	unique_ptr<TiXmlElement> pElem_stBaseInfo(new TiXmlElement("RoleBaseInfo"));
	if(pElem_stBaseInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stBaseInfo->SetAttribute("name", "stBaseInfo");
	if(!ToXML(s.stBaseInfo, *pElem_stBaseInfo))
	{
		LOG_CRI << "stBaseInfo ToXML fails!";
		return false;
	}
	pElem_stBaseInfo->SetAttribute("comment", ToUTF8Ptr("玩家基本数据成员"));
	if(rElement.LinkEndChild(pElem_stBaseInfo.get()) != NULL)
		pElem_stBaseInfo.release();
	unique_ptr<TiXmlElement> pElem_vecFighterInfo(new TiXmlElement("FighterProt::TVecFighterDBInfo"));
	if(pElem_vecFighterInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFighterInfo->SetAttribute("name", "vecFighterInfo");
	if(!NFighterProt::VectorToXML(s.vecFighterInfo, *pElem_vecFighterInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFighterInfo->SetAttribute("comment", ToUTF8Ptr("将信息"));
	if(rElement.LinkEndChild(pElem_vecFighterInfo.get()) != NULL)
		pElem_vecFighterInfo.release();
	unique_ptr<TiXmlElement> pElem_vecSkillInfo(new TiXmlElement("FighterProt::TVecSkillDBInfo"));
	if(pElem_vecSkillInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecSkillInfo->SetAttribute("name", "vecSkillInfo");
	if(!NFighterProt::VectorToXML(s.vecSkillInfo, *pElem_vecSkillInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecSkillInfo->SetAttribute("comment", ToUTF8Ptr("将技能信息"));
	if(rElement.LinkEndChild(pElem_vecSkillInfo.get()) != NULL)
		pElem_vecSkillInfo.release();
	unique_ptr<TiXmlElement> pElem_vecPassiveSkillInfo(new TiXmlElement("FighterProt::TVecPassiveSkillDBInfo"));
	if(pElem_vecPassiveSkillInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPassiveSkillInfo->SetAttribute("name", "vecPassiveSkillInfo");
	if(!NFighterProt::VectorToXML(s.vecPassiveSkillInfo, *pElem_vecPassiveSkillInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPassiveSkillInfo->SetAttribute("comment", ToUTF8Ptr("将技能信息"));
	if(rElement.LinkEndChild(pElem_vecPassiveSkillInfo.get()) != NULL)
		pElem_vecPassiveSkillInfo.release();
	unique_ptr<TiXmlElement> pElem_vecFighterCombination(new TiXmlElement("FighterProt::TVecFighterCombination"));
	if(pElem_vecFighterCombination == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFighterCombination->SetAttribute("name", "vecFighterCombination");
	if(!NFighterProt::VectorToXML(s.vecFighterCombination, *pElem_vecFighterCombination))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFighterCombination->SetAttribute("comment", ToUTF8Ptr("玩家的散仙组合信息"));
	if(rElement.LinkEndChild(pElem_vecFighterCombination.get()) != NULL)
		pElem_vecFighterCombination.release();
	unique_ptr<TiXmlElement> pElem_vecRoleItemInfo(new TiXmlElement("ItemProt::TVecItem"));
	if(pElem_vecRoleItemInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecRoleItemInfo->SetAttribute("name", "vecRoleItemInfo");
	if(!NItemProt::VectorToXML(s.vecRoleItemInfo, *pElem_vecRoleItemInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecRoleItemInfo->SetAttribute("comment", ToUTF8Ptr("玩家物品成员"));
	if(rElement.LinkEndChild(pElem_vecRoleItemInfo.get()) != NULL)
		pElem_vecRoleItemInfo.release();
	unique_ptr<TiXmlElement> pElem_vecFriendsInfo(new TiXmlElement("FriendProt::TVecFriendDBInfo"));
	if(pElem_vecFriendsInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFriendsInfo->SetAttribute("name", "vecFriendsInfo");
	if(!NFriendProt::VectorToXML(s.vecFriendsInfo, *pElem_vecFriendsInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFriendsInfo->SetAttribute("comment", ToUTF8Ptr("好友信息"));
	if(rElement.LinkEndChild(pElem_vecFriendsInfo.get()) != NULL)
		pElem_vecFriendsInfo.release();
	unique_ptr<TiXmlElement> pElem_vecRoleDgnInfo(new TiXmlElement("TVecRoleDgnInfo"));
	if(pElem_vecRoleDgnInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecRoleDgnInfo->SetAttribute("name", "vecRoleDgnInfo");
	if(!VectorToXML(s.vecRoleDgnInfo, *pElem_vecRoleDgnInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecRoleDgnInfo->SetAttribute("comment", ToUTF8Ptr("玩家副本信息"));
	if(rElement.LinkEndChild(pElem_vecRoleDgnInfo.get()) != NULL)
		pElem_vecRoleDgnInfo.release();
	unique_ptr<TiXmlElement> pElem_vecRoleTaskInfo(new TiXmlElement("TVecRoleTaskInfo"));
	if(pElem_vecRoleTaskInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecRoleTaskInfo->SetAttribute("name", "vecRoleTaskInfo");
	if(!VectorToXML(s.vecRoleTaskInfo, *pElem_vecRoleTaskInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecRoleTaskInfo->SetAttribute("comment", ToUTF8Ptr("玩家任务信息"));
	if(rElement.LinkEndChild(pElem_vecRoleTaskInfo.get()) != NULL)
		pElem_vecRoleTaskInfo.release();
	unique_ptr<TiXmlElement> pElem_vecGameVars(new TiXmlElement("TVecVarsDBInfo"));
	if(pElem_vecGameVars == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecGameVars->SetAttribute("name", "vecGameVars");
	if(!VectorToXML(s.vecGameVars, *pElem_vecGameVars))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecGameVars->SetAttribute("comment", ToUTF8Ptr("玩家身上Game上的变量任务信息"));
	if(rElement.LinkEndChild(pElem_vecGameVars.get()) != NULL)
		pElem_vecGameVars.release();
	unique_ptr<TiXmlElement> pElem_vecRoleSlotsInfo(new TiXmlElement("TVecRoleSlotsInfo"));
	if(pElem_vecRoleSlotsInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecRoleSlotsInfo->SetAttribute("name", "vecRoleSlotsInfo");
	if(!VectorToXML(s.vecRoleSlotsInfo, *pElem_vecRoleSlotsInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecRoleSlotsInfo->SetAttribute("comment", ToUTF8Ptr("玩家身上的槽的信息"));
	if(rElement.LinkEndChild(pElem_vecRoleSlotsInfo.get()) != NULL)
		pElem_vecRoleSlotsInfo.release();
	unique_ptr<TiXmlElement> pElem_vecFormationInfo(new TiXmlElement("TVecFormationInfo"));
	if(pElem_vecFormationInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFormationInfo->SetAttribute("name", "vecFormationInfo");
	if(!VectorToXML(s.vecFormationInfo, *pElem_vecFormationInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFormationInfo->SetAttribute("comment", ToUTF8Ptr("玩家的阵形信息"));
	if(rElement.LinkEndChild(pElem_vecFormationInfo.get()) != NULL)
		pElem_vecFormationInfo.release();
	unique_ptr<TiXmlElement> pElem_vecPetDataInfo(new TiXmlElement("TVecPetDataInfo"));
	if(pElem_vecPetDataInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPetDataInfo->SetAttribute("name", "vecPetDataInfo");
	if(!VectorToXML(s.vecPetDataInfo, *pElem_vecPetDataInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPetDataInfo->SetAttribute("comment", ToUTF8Ptr("玩家的阵灵信息"));
	if(rElement.LinkEndChild(pElem_vecPetDataInfo.get()) != NULL)
		pElem_vecPetDataInfo.release();
	unique_ptr<TiXmlElement> pElem_oRolePetInfo(new TiXmlElement("SRolePetInfo"));
	if(pElem_oRolePetInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oRolePetInfo->SetAttribute("name", "oRolePetInfo");
	if(!ToXML(s.oRolePetInfo, *pElem_oRolePetInfo))
	{
		LOG_CRI << "oRolePetInfo ToXML fails!";
		return false;
	}
	pElem_oRolePetInfo->SetAttribute("comment", ToUTF8Ptr("玩家的阵形全局信息"));
	if(rElement.LinkEndChild(pElem_oRolePetInfo.get()) != NULL)
		pElem_oRolePetInfo.release();
	unique_ptr<TiXmlElement> pElem_vecBeastSoulInfo(new TiXmlElement("TVecBeastSoulInfo"));
	if(pElem_vecBeastSoulInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBeastSoulInfo->SetAttribute("name", "vecBeastSoulInfo");
	if(!VectorToXML(s.vecBeastSoulInfo, *pElem_vecBeastSoulInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBeastSoulInfo->SetAttribute("comment", ToUTF8Ptr("玩家的兽魂信息"));
	if(rElement.LinkEndChild(pElem_vecBeastSoulInfo.get()) != NULL)
		pElem_vecBeastSoulInfo.release();
	unique_ptr<TiXmlElement> pElem_vecFireInfo(new TiXmlElement("TripodProt::TVecFireInfo"));
	if(pElem_vecFireInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFireInfo->SetAttribute("name", "vecFireInfo");
	if(!NTripodProt::VectorToXML(s.vecFireInfo, *pElem_vecFireInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFireInfo->SetAttribute("comment", ToUTF8Ptr("玩家九疑鼎的火种信息"));
	if(rElement.LinkEndChild(pElem_vecFireInfo.get()) != NULL)
		pElem_vecFireInfo.release();
	unique_ptr<TiXmlElement> pElem_vecArenaInfo(new TiXmlElement("TVecRoleArenaInfo"));
	if(pElem_vecArenaInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecArenaInfo->SetAttribute("name", "vecArenaInfo");
	if(!VectorToXML(s.vecArenaInfo, *pElem_vecArenaInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecArenaInfo->SetAttribute("comment", ToUTF8Ptr("玩家斗剑信息"));
	if(rElement.LinkEndChild(pElem_vecArenaInfo.get()) != NULL)
		pElem_vecArenaInfo.release();
	unique_ptr<TiXmlElement> pElem_vecDBBuffInfo(new TiXmlElement("ProtoCommon::TVecDBBuffInfo"));
	if(pElem_vecDBBuffInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecDBBuffInfo->SetAttribute("name", "vecDBBuffInfo");
	if(!NProtoCommon::VectorToXML(s.vecDBBuffInfo, *pElem_vecDBBuffInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecDBBuffInfo->SetAttribute("comment", ToUTF8Ptr("玩家Buff信息"));
	if(rElement.LinkEndChild(pElem_vecDBBuffInfo.get()) != NULL)
		pElem_vecDBBuffInfo.release();
	unique_ptr<TiXmlElement> pElem_vecSoulSpaceInfo(new TiXmlElement("TVecSoulSpaceInfo"));
	if(pElem_vecSoulSpaceInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecSoulSpaceInfo->SetAttribute("name", "vecSoulSpaceInfo");
	if(!VectorToXML(s.vecSoulSpaceInfo, *pElem_vecSoulSpaceInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecSoulSpaceInfo->SetAttribute("comment", ToUTF8Ptr("玩家魄空间信息"));
	if(rElement.LinkEndChild(pElem_vecSoulSpaceInfo.get()) != NULL)
		pElem_vecSoulSpaceInfo.release();
	unique_ptr<TiXmlElement> pElem_vecBubbleInfo(new TiXmlElement("TVecDBBubbleInfo"));
	if(pElem_vecBubbleInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBubbleInfo->SetAttribute("name", "vecBubbleInfo");
	if(!VectorToXML(s.vecBubbleInfo, *pElem_vecBubbleInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBubbleInfo->SetAttribute("comment", ToUTF8Ptr("玩家气泡信息"));
	if(rElement.LinkEndChild(pElem_vecBubbleInfo.get()) != NULL)
		pElem_vecBubbleInfo.release();
	unique_ptr<TiXmlElement> pElem_vecHorseDB(new TiXmlElement("Horse::TVecHorseDB"));
	if(pElem_vecHorseDB == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecHorseDB->SetAttribute("name", "vecHorseDB");
	if(!NHorse::VectorToXML(s.vecHorseDB, *pElem_vecHorseDB))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecHorseDB->SetAttribute("comment", ToUTF8Ptr("玩家魄坐骑信息"));
	if(rElement.LinkEndChild(pElem_vecHorseDB.get()) != NULL)
		pElem_vecHorseDB.release();
	unique_ptr<TiXmlElement> pElem_sGroupInfo(new TiXmlElement("SGroupTaskInfo"));
	if(pElem_sGroupInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sGroupInfo->SetAttribute("name", "sGroupInfo");
	if(!ToXML(s.sGroupInfo, *pElem_sGroupInfo))
	{
		LOG_CRI << "sGroupInfo ToXML fails!";
		return false;
	}
	pElem_sGroupInfo->SetAttribute("comment", ToUTF8Ptr("师门任务信息"));
	if(rElement.LinkEndChild(pElem_sGroupInfo.get()) != NULL)
		pElem_sGroupInfo.release();
	unique_ptr<TiXmlElement> pElem_sYaMenInfo(new TiXmlElement("SYaMenTaskInfo"));
	if(pElem_sYaMenInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sYaMenInfo->SetAttribute("name", "sYaMenInfo");
	if(!ToXML(s.sYaMenInfo, *pElem_sYaMenInfo))
	{
		LOG_CRI << "sYaMenInfo ToXML fails!";
		return false;
	}
	pElem_sYaMenInfo->SetAttribute("comment", ToUTF8Ptr("衙门任务信息"));
	if(rElement.LinkEndChild(pElem_sYaMenInfo.get()) != NULL)
		pElem_sYaMenInfo.release();
	unique_ptr<TiXmlElement> pElem_vecActivityTask(new TiXmlElement("TVecActivityTaskInfo"));
	if(pElem_vecActivityTask == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecActivityTask->SetAttribute("name", "vecActivityTask");
	if(!VectorToXML(s.vecActivityTask, *pElem_vecActivityTask))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecActivityTask->SetAttribute("comment", ToUTF8Ptr("活跃度任务信息"));
	if(rElement.LinkEndChild(pElem_vecActivityTask.get()) != NULL)
		pElem_vecActivityTask.release();
	unique_ptr<TiXmlElement> pElem_vecTitle(new TiXmlElement("TVecTitle"));
	if(pElem_vecTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTitle->SetAttribute("name", "vecTitle");
	if(!VectorToXML(s.vecTitle, *pElem_vecTitle))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTitle->SetAttribute("comment", ToUTF8Ptr("称号信息"));
	if(rElement.LinkEndChild(pElem_vecTitle.get()) != NULL)
		pElem_vecTitle.release();
	unique_ptr<TiXmlElement> pElem_vecAchievementInfo(new TiXmlElement("AchievementProt::TVecAchievementInfo"));
	if(pElem_vecAchievementInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecAchievementInfo->SetAttribute("name", "vecAchievementInfo");
	if(!NAchievementProt::VectorToXML(s.vecAchievementInfo, *pElem_vecAchievementInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecAchievementInfo->SetAttribute("comment", ToUTF8Ptr("成就信息"));
	if(rElement.LinkEndChild(pElem_vecAchievementInfo.get()) != NULL)
		pElem_vecAchievementInfo.release();
	unique_ptr<TiXmlElement> pElem_vecCollectionInfo(new TiXmlElement("CollectionProt::TVecCollectionInfo"));
	if(pElem_vecCollectionInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecCollectionInfo->SetAttribute("name", "vecCollectionInfo");
	if(!NCollectionProt::VectorToXML(s.vecCollectionInfo, *pElem_vecCollectionInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecCollectionInfo->SetAttribute("comment", ToUTF8Ptr("收藏信息"));
	if(rElement.LinkEndChild(pElem_vecCollectionInfo.get()) != NULL)
		pElem_vecCollectionInfo.release();
	unique_ptr<TiXmlElement> pElem_vecRoleAttaked(new TiXmlElement("DemonTower::TVecRoleAttaked"));
	if(pElem_vecRoleAttaked == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecRoleAttaked->SetAttribute("name", "vecRoleAttaked");
	if(!NDemonTower::VectorToXML(s.vecRoleAttaked, *pElem_vecRoleAttaked))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecRoleAttaked->SetAttribute("comment", ToUTF8Ptr("玩家被攻击信息列表"));
	if(rElement.LinkEndChild(pElem_vecRoleAttaked.get()) != NULL)
		pElem_vecRoleAttaked.release();
	unique_ptr<TiXmlElement> pElem_vecExchangeInfo(new TiXmlElement("ExchangeShopProt::TVecExchangeInfo"));
	if(pElem_vecExchangeInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecExchangeInfo->SetAttribute("name", "vecExchangeInfo");
	if(!NExchangeShopProt::VectorToXML(s.vecExchangeInfo, *pElem_vecExchangeInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecExchangeInfo->SetAttribute("comment", ToUTF8Ptr("玩家兑换信息列表"));
	if(rElement.LinkEndChild(pElem_vecExchangeInfo.get()) != NULL)
		pElem_vecExchangeInfo.release();
	unique_ptr<TiXmlElement> pElem_vecSweepInfo(new TiXmlElement("DungeonProt::TVecSweepInfo"));
	if(pElem_vecSweepInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecSweepInfo->SetAttribute("name", "vecSweepInfo");
	if(!NDungeonProt::VectorToXML(s.vecSweepInfo, *pElem_vecSweepInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecSweepInfo->SetAttribute("comment", ToUTF8Ptr("玩家兑换信息列表"));
	if(rElement.LinkEndChild(pElem_vecSweepInfo.get()) != NULL)
		pElem_vecSweepInfo.release();
	unique_ptr<TiXmlElement> pElem_vecPendRes(new TiXmlElement("TVecPendRes"));
	if(pElem_vecPendRes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPendRes->SetAttribute("name", "vecPendRes");
	if(!VectorToXML(s.vecPendRes, *pElem_vecPendRes))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPendRes->SetAttribute("comment", ToUTF8Ptr("玩家暂存资源列表"));
	if(rElement.LinkEndChild(pElem_vecPendRes.get()) != NULL)
		pElem_vecPendRes.release();
	unique_ptr<TiXmlElement> pElem_vecXinFaDBInfo(new TiXmlElement("FighterProt::TVecXinFaDBInfo"));
	if(pElem_vecXinFaDBInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecXinFaDBInfo->SetAttribute("name", "vecXinFaDBInfo");
	if(!NFighterProt::VectorToXML(s.vecXinFaDBInfo, *pElem_vecXinFaDBInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecXinFaDBInfo->SetAttribute("comment", ToUTF8Ptr("玩家心法信息"));
	if(rElement.LinkEndChild(pElem_vecXinFaDBInfo.get()) != NULL)
		pElem_vecXinFaDBInfo.release();
	unique_ptr<TiXmlElement> pElem_vecLevelPrize(new TiXmlElement("LevelPrize::TVecPrize2DB"));
	if(pElem_vecLevelPrize == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecLevelPrize->SetAttribute("name", "vecLevelPrize");
	if(!NLevelPrize::VectorToXML(s.vecLevelPrize, *pElem_vecLevelPrize))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecLevelPrize->SetAttribute("comment", ToUTF8Ptr("玩家条件奖励信息"));
	if(rElement.LinkEndChild(pElem_vecLevelPrize.get()) != NULL)
		pElem_vecLevelPrize.release();
	unique_ptr<TiXmlElement> pElem_vecPlatformParam(new TiXmlElement("ProtoCommon::TVecPlatformParam"));
	if(pElem_vecPlatformParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPlatformParam->SetAttribute("name", "vecPlatformParam");
	if(!NProtoCommon::VectorToXML(s.vecPlatformParam, *pElem_vecPlatformParam))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPlatformParam->SetAttribute("comment", ToUTF8Ptr("玩家平台信息"));
	if(rElement.LinkEndChild(pElem_vecPlatformParam.get()) != NULL)
		pElem_vecPlatformParam.release();
	unique_ptr<TiXmlElement> pElem_vecEventInfo(new TiXmlElement("TVecEventInfo"));
	if(pElem_vecEventInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecEventInfo->SetAttribute("name", "vecEventInfo");
	if(!VectorToXML(s.vecEventInfo, *pElem_vecEventInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecEventInfo->SetAttribute("comment", ToUTF8Ptr("事件信息"));
	if(rElement.LinkEndChild(pElem_vecEventInfo.get()) != NULL)
		pElem_vecEventInfo.release();
	unique_ptr<TiXmlElement> pElem_vecEventOffLine(new TiXmlElement("TVecEventOffLine"));
	if(pElem_vecEventOffLine == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecEventOffLine->SetAttribute("name", "vecEventOffLine");
	if(!VectorToXML(s.vecEventOffLine, *pElem_vecEventOffLine))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecEventOffLine->SetAttribute("comment", ToUTF8Ptr("离线事件"));
	if(rElement.LinkEndChild(pElem_vecEventOffLine.get()) != NULL)
		pElem_vecEventOffLine.release();
	unique_ptr<TiXmlElement> pElem_vecBuyItemDBInfo(new TiXmlElement("TVecBuyItemDBInfo"));
	if(pElem_vecBuyItemDBInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBuyItemDBInfo->SetAttribute("name", "vecBuyItemDBInfo");
	if(!VectorToXML(s.vecBuyItemDBInfo, *pElem_vecBuyItemDBInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBuyItemDBInfo->SetAttribute("comment", ToUTF8Ptr("商品购买数量"));
	if(rElement.LinkEndChild(pElem_vecBuyItemDBInfo.get()) != NULL)
		pElem_vecBuyItemDBInfo.release();
	unique_ptr<TiXmlElement> pElem_vecDayTargetDBInfo(new TiXmlElement("TVecDayTargetDBInfo"));
	if(pElem_vecDayTargetDBInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecDayTargetDBInfo->SetAttribute("name", "vecDayTargetDBInfo");
	if(!VectorToXML(s.vecDayTargetDBInfo, *pElem_vecDayTargetDBInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecDayTargetDBInfo->SetAttribute("comment", ToUTF8Ptr("7日目标活动信息"));
	if(rElement.LinkEndChild(pElem_vecDayTargetDBInfo.get()) != NULL)
		pElem_vecDayTargetDBInfo.release();
	unique_ptr<TiXmlElement> pElem_vecBattleArrayDBInfo(new TiXmlElement("TVecBattleArrayDBInfo"));
	if(pElem_vecBattleArrayDBInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBattleArrayDBInfo->SetAttribute("name", "vecBattleArrayDBInfo");
	if(!VectorToXML(s.vecBattleArrayDBInfo, *pElem_vecBattleArrayDBInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBattleArrayDBInfo->SetAttribute("comment", ToUTF8Ptr("破阵信息"));
	if(rElement.LinkEndChild(pElem_vecBattleArrayDBInfo.get()) != NULL)
		pElem_vecBattleArrayDBInfo.release();
	unique_ptr<TiXmlElement> pElem_vecAutoStoreDBInfo(new TiXmlElement("TVecAutoStoreDBInfo"));
	if(pElem_vecAutoStoreDBInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecAutoStoreDBInfo->SetAttribute("name", "vecAutoStoreDBInfo");
	if(!VectorToXML(s.vecAutoStoreDBInfo, *pElem_vecAutoStoreDBInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecAutoStoreDBInfo->SetAttribute("comment", ToUTF8Ptr("动态存储信息"));
	if(rElement.LinkEndChild(pElem_vecAutoStoreDBInfo.get()) != NULL)
		pElem_vecAutoStoreDBInfo.release();
	unique_ptr<TiXmlElement> pElem_vecTHDBInfo(new TiXmlElement("TreasureHuntProt::TVecTHDBInfo"));
	if(pElem_vecTHDBInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTHDBInfo->SetAttribute("name", "vecTHDBInfo");
	if(!NTreasureHuntProt::VectorToXML(s.vecTHDBInfo, *pElem_vecTHDBInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTHDBInfo->SetAttribute("comment", ToUTF8Ptr("玩家寻宝信息"));
	if(rElement.LinkEndChild(pElem_vecTHDBInfo.get()) != NULL)
		pElem_vecTHDBInfo.release();
	unique_ptr<TiXmlElement> pElem_vecBeauty(new TiXmlElement("Beauty::TVecBeauty"));
	if(pElem_vecBeauty == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBeauty->SetAttribute("name", "vecBeauty");
	if(!NBeauty::VectorToXML(s.vecBeauty, *pElem_vecBeauty))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBeauty->SetAttribute("comment", ToUTF8Ptr("美女信息"));
	if(rElement.LinkEndChild(pElem_vecBeauty.get()) != NULL)
		pElem_vecBeauty.release();
	unique_ptr<TiXmlElement> pElem_vecFightFormationDBInfo(new TiXmlElement("TVecFightFormationDBInfo"));
	if(pElem_vecFightFormationDBInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFightFormationDBInfo->SetAttribute("name", "vecFightFormationDBInfo");
	if(!VectorToXML(s.vecFightFormationDBInfo, *pElem_vecFightFormationDBInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFightFormationDBInfo->SetAttribute("comment", ToUTF8Ptr("新阵型信息"));
	if(rElement.LinkEndChild(pElem_vecFightFormationDBInfo.get()) != NULL)
		pElem_vecFightFormationDBInfo.release();
	unique_ptr<TiXmlElement> pElem_vecFightHeroDBInfo(new TiXmlElement("TVecFightHeroDBInfo"));
	if(pElem_vecFightHeroDBInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFightHeroDBInfo->SetAttribute("name", "vecFightHeroDBInfo");
	if(!VectorToXML(s.vecFightHeroDBInfo, *pElem_vecFightHeroDBInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFightHeroDBInfo->SetAttribute("comment", ToUTF8Ptr("战斗散仙数据"));
	if(rElement.LinkEndChild(pElem_vecFightHeroDBInfo.get()) != NULL)
		pElem_vecFightHeroDBInfo.release();
	unique_ptr<TiXmlElement> pElem_sShipData(new TiXmlElement("ShipProt::PlayerSelfShipData"));
	if(pElem_sShipData == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sShipData->SetAttribute("name", "sShipData");
	if(!ToXML(s.sShipData, *pElem_sShipData))
	{
		LOG_CRI << "sShipData ToXML fails!";
		return false;
	}
	pElem_sShipData->SetAttribute("comment", ToUTF8Ptr("自己运船信息"));
	if(rElement.LinkEndChild(pElem_sShipData.get()) != NULL)
		pElem_sShipData.release();
	unique_ptr<TiXmlElement> pElem_vecShipReport(new TiXmlElement("ShipProt::TVecShipReport"));
	if(pElem_vecShipReport == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecShipReport->SetAttribute("name", "vecShipReport");
	if(!NShipProt::VectorToXML(s.vecShipReport, *pElem_vecShipReport))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecShipReport->SetAttribute("comment", ToUTF8Ptr("战报信息"));
	if(rElement.LinkEndChild(pElem_vecShipReport.get()) != NULL)
		pElem_vecShipReport.release();
	unique_ptr<TiXmlElement> pElem_vecGEMDBInfo(new TiXmlElement("GuardEMeiProt::TVecGEMDBInfo"));
	if(pElem_vecGEMDBInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecGEMDBInfo->SetAttribute("name", "vecGEMDBInfo");
	if(!NGuardEMeiProt::VectorToXML(s.vecGEMDBInfo, *pElem_vecGEMDBInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecGEMDBInfo->SetAttribute("comment", ToUTF8Ptr("玩家守卫峨眉信息"));
	if(rElement.LinkEndChild(pElem_vecGEMDBInfo.get()) != NULL)
		pElem_vecGEMDBInfo.release();
	unique_ptr<TiXmlElement> pElem_vecShengLing(new TiXmlElement("ShengLingProt::TVecShengLingInfo2DB"));
	if(pElem_vecShengLing == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecShengLing->SetAttribute("name", "vecShengLing");
	if(!NShengLingProt::VectorToXML(s.vecShengLing, *pElem_vecShengLing))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecShengLing->SetAttribute("comment", ToUTF8Ptr("玩家圣陵信息"));
	if(rElement.LinkEndChild(pElem_vecShengLing.get()) != NULL)
		pElem_vecShengLing.release();
	unique_ptr<TiXmlElement> pElem_vecShengLingPrize(new TiXmlElement("ShengLingProt::TVecShengLingPrize2DB"));
	if(pElem_vecShengLingPrize == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecShengLingPrize->SetAttribute("name", "vecShengLingPrize");
	if(!NShengLingProt::VectorToXML(s.vecShengLingPrize, *pElem_vecShengLingPrize))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecShengLingPrize->SetAttribute("comment", ToUTF8Ptr("玩家圣陵奖励"));
	if(rElement.LinkEndChild(pElem_vecShengLingPrize.get()) != NULL)
		pElem_vecShengLingPrize.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoleDataInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		RoleDataInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRoleDataInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("RoleDataInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SRecharge::SRecharge() : qwRoleID(0), wGoldID(0), dwCount(0), dwGold(0), byStatus(0), 
			dwHappenedTime(0) { }

SRecharge::SRecharge(const std::string& strNo_, UINT64 qwRoleID_, UINT16 wGoldID_, UINT32 dwCount_, UINT32 dwGold_, 
			UINT8 byStatus_, UINT32 dwHappenedTime_)
			: strNo(strNo_), qwRoleID(qwRoleID_), wGoldID(wGoldID_), dwCount(dwCount_), dwGold(dwGold_), 
			byStatus(byStatus_), dwHappenedTime(dwHappenedTime_) { }

SRecharge::SRecharge(SRecharge&& src) : strNo(move(src.strNo)), qwRoleID(src.qwRoleID), wGoldID(src.wGoldID), dwCount(src.dwCount), dwGold(src.dwGold), 
			byStatus(src.byStatus), dwHappenedTime(src.dwHappenedTime) { }

SRecharge& SRecharge::operator=(SRecharge&& rhs)
{
	if(this != &rhs)
	{
		this->~SRecharge();
		new (this) SRecharge(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRecharge& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.strNo;
	src >> s.qwRoleID;
	src >> s.wGoldID;
	src >> s.dwCount;
	src >> s.dwGold;
	src >> s.byStatus;
	src >> s.dwHappenedTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRecharge& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.strNo;
	src << s.qwRoleID;
	src << s.wGoldID;
	src << s.dwCount;
	src << s.dwGold;
	src << s.byStatus;
	src << s.dwHappenedTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRecharge& s)
{
	if(strcmp(rElement.Value(), "SRecharge") != 0)
	{
		LOG_CRI << "rElement is not SRecharge!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strNo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strNo") != 0)
	{
		LOG_CRI << "Attribute: name is not strNo!";
		return false;
	}
	const char* pszVal_strNo = pElemChild->Attribute("value");
	if(pszVal_strNo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strNo = pszVal_strNo;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wGoldID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wGoldID") != 0)
	{
		LOG_CRI << "Attribute: name is not wGoldID!";
		return false;
	}
	const char* pszVal_wGoldID = pElemChild->Attribute("value");
	if(pszVal_wGoldID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wGoldID, s.wGoldID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCount!";
		return false;
	}
	const char* pszVal_dwCount = pElemChild->Attribute("value");
	if(pszVal_dwCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCount, s.dwCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGold is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGold") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGold!";
		return false;
	}
	const char* pszVal_dwGold = pElemChild->Attribute("value");
	if(pszVal_dwGold == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGold, s.dwGold))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not byStatus!";
		return false;
	}
	const char* pszVal_byStatus = pElemChild->Attribute("value");
	if(pszVal_byStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStatus, s.byStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHappenedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHappenedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHappenedTime!";
		return false;
	}
	const char* pszVal_dwHappenedTime = pElemChild->Attribute("value");
	if(pszVal_dwHappenedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHappenedTime, s.dwHappenedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRecharge& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRecharge");
	rElement.SetAttribute("type", ToUTF8Ptr("DB存储玩家充值仙石的结构体"));
	unique_ptr<TiXmlElement> pElem_strNo(new TiXmlElement("string"));
	if(pElem_strNo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strNo->SetAttribute("name", "strNo");
	pElem_strNo->SetAttribute("value", s.strNo.c_str());
	pElem_strNo->SetAttribute("comment", ToUTF8Ptr("充值流水号"));
	if(rElement.LinkEndChild(pElem_strNo.get()) != NULL)
		pElem_strNo.release();
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("用户ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_wGoldID(new TiXmlElement("UINT16"));
	if(pElem_wGoldID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wGoldID->SetAttribute("name", "wGoldID");
	pElem_wGoldID->SetAttribute("value", NumberToString(s.wGoldID).c_str());
	pElem_wGoldID->SetAttribute("comment", ToUTF8Ptr("仙石包ID(41[10仙石],42[100仙石],43[300仙石],44[500仙石],45[1000仙石],46[3000仙石])"));
	if(rElement.LinkEndChild(pElem_wGoldID.get()) != NULL)
		pElem_wGoldID.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("充值的仙石包数量"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	unique_ptr<TiXmlElement> pElem_dwGold(new TiXmlElement("UINT32"));
	if(pElem_dwGold == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGold->SetAttribute("name", "dwGold");
	pElem_dwGold->SetAttribute("value", NumberToString(s.dwGold).c_str());
	pElem_dwGold->SetAttribute("comment", ToUTF8Ptr("充值的仙石总数"));
	if(rElement.LinkEndChild(pElem_dwGold.get()) != NULL)
		pElem_dwGold.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("仙石是否到账(0-准备/不成功 1-成功,2-补单成功)"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwHappenedTime(new TiXmlElement("UINT32"));
	if(pElem_dwHappenedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHappenedTime->SetAttribute("name", "dwHappenedTime");
	pElem_dwHappenedTime->SetAttribute("value", NumberToString(s.dwHappenedTime).c_str());
	pElem_dwHappenedTime->SetAttribute("comment", ToUTF8Ptr("充值时间"));
	if(rElement.LinkEndChild(pElem_dwHappenedTime.get()) != NULL)
		pElem_dwHappenedTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRecharge& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRecharge s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRecharge& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRecharge"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SPrepaid::SPrepaid() : qwRoleID(0), dwGold(0) { }

SPrepaid::SPrepaid(UINT64 qwRoleID_, UINT32 dwGold_) : qwRoleID(qwRoleID_), dwGold(dwGold_) { }

CInArchive& operator>>(CInArchive& src, SPrepaid& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.dwGold;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPrepaid& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.dwGold;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPrepaid& s)
{
	if(strcmp(rElement.Value(), "SPrepaid") != 0)
	{
		LOG_CRI << "rElement is not SPrepaid!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGold is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGold") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGold!";
		return false;
	}
	const char* pszVal_dwGold = pElemChild->Attribute("value");
	if(pszVal_dwGold == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGold, s.dwGold))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPrepaid& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPrepaid");
	rElement.SetAttribute("type", ToUTF8Ptr("DB存储玩家未创角预先充值仙石的结构体"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("用户ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_dwGold(new TiXmlElement("UINT32"));
	if(pElem_dwGold == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGold->SetAttribute("name", "dwGold");
	pElem_dwGold->SetAttribute("value", NumberToString(s.dwGold).c_str());
	pElem_dwGold->SetAttribute("comment", ToUTF8Ptr("预先充值的仙石总数量"));
	if(rElement.LinkEndChild(pElem_dwGold.get()) != NULL)
		pElem_dwGold.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPrepaid& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPrepaid s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecPrepaid& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPrepaid"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

} //namespace NRoleInfoDefine
