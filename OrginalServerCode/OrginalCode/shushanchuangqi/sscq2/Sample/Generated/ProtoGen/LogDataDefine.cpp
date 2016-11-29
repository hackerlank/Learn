/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LogDataDefine.cpp
//  Purpose:      日志数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "LogDataDefine.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NLogDataDefine
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EDgnOpType e)
{
	switch(e)
	{
	case EDgnOpType_CREATE:
		return "EDgnOpType_CREATE";
	case EDgnOpType_PLAYERENTER:
		return "EDgnOpType_PLAYERENTER";
	case EDgnOpType_PLAYERLEAVE:
		return "EDgnOpType_PLAYERLEAVE";
	case EDgnOpType_FINISH:
		return "EDgnOpType_FINISH";
	case EDgnOpType_DESTROY:
		return "EDgnOpType_DESTROY";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDgnOpType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDgnOpType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EDgnOpType_CREATE", EDgnOpType_CREATE));
		mapStr2Val.insert(make_pair("EDgnOpType_PLAYERENTER", EDgnOpType_PLAYERENTER));
		mapStr2Val.insert(make_pair("EDgnOpType_PLAYERLEAVE", EDgnOpType_PLAYERLEAVE));
		mapStr2Val.insert(make_pair("EDgnOpType_FINISH", EDgnOpType_FINISH));
		mapStr2Val.insert(make_pair("EDgnOpType_DESTROY", EDgnOpType_DESTROY));
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

const char* EnumValToStr(ItemFrom e)
{
	switch(e)
	{
	case ItemFrom_GM:
		return "ItemFrom_GM";
	case ItemFrom_InLuaBox:
		return "ItemFrom_InLuaBox";
	case ItemFrom_System:
		return "ItemFrom_System";
	case ItemFrom_EDgn:
		return "ItemFrom_EDgn";
	case ItemFrom_DujieAward:
		return "ItemFrom_DujieAward";
	case ItemFrom_MonsterDrop:
		return "ItemFrom_MonsterDrop";
	case ItemFrom_YaMenAward:
		return "ItemFrom_YaMenAward";
	case ItemFrom_BeastSoul:
		return "ItemFrom_BeastSoul";
	case ItemFrom_Gather:
		return "ItemFrom_Gather";
	case ItemFrom_Task:
		return "ItemFrom_Task";
	case ItemFrom_Mail:
		return "ItemFrom_Mail";
	case ItemFrom_Mall:
		return "ItemFrom_Mall";
	case ItemFrom_DemonTower:
		return "ItemFrom_DemonTower";
	case ItemFrom_TripodAward:
		return "ItemFrom_TripodAward";
	case ItemFrom_ArenaAward:
		return "ItemFrom_ArenaAward";
	case ItemFrom_RankAdoreAward:
		return "ItemFrom_RankAdoreAward";
	case ItemFrom_VIPAward:
		return "ItemFrom_VIPAward";
	case ItemFrom_YelloDiamondAward:
		return "ItemFrom_YelloDiamondAward";
	case ItemFrom_FighterFind:
		return "ItemFrom_FighterFind";
	case ItemFrom_ExchangeItem:
		return "ItemFrom_ExchangeItem";
	case ItemFrom_LevelPrizeAct:
		return "ItemFrom_LevelPrizeAct";
	case ItemFrom_Activity:
		return "ItemFrom_Activity";
	case ItemFrom_CittaStore:
		return "ItemFrom_CittaStore";
	case ItemFrom_UserDeptORPack:
		return "ItemFrom_UserDeptORPack";
	case ItemFrom_ActiveTrump:
		return "ItemFrom_ActiveTrump";
	case ItemFrom_MergeCitta:
		return "ItemFrom_MergeCitta";
	case ItemFrom_BreakCitta:
		return "ItemFrom_BreakCitta";
	case ItemFrom_HeroXinFaDisperse:
		return "ItemFrom_HeroXinFaDisperse";
	case ItemFrom_PlayerXinFaDisperse:
		return "ItemFrom_PlayerXinFaDisperse";
	case ItemFrom_NewCollection:
		return "ItemFrom_NewCollection";
	case ItemFrom_NewAchieve:
		return "ItemFrom_NewAchieve";
	case ItemFrom_EnergyBuy:
		return "ItemFrom_EnergyBuy";
	case ItemFrom_EnergyBuff:
		return "ItemFrom_EnergyBuff";
	case ItemFrom_DemonTowerSeal:
		return "ItemFrom_DemonTowerSeal";
	case ItemFrom_DemonTowerPass:
		return "ItemFrom_DemonTowerPass";
	case ItemFrom_Pend:
		return "ItemFrom_Pend";
	case ItemFrom_Siting:
		return "ItemFrom_Siting";
	case ItemFrom_Recharge:
		return "ItemFrom_Recharge";
	case ItemFrom_LangHuanBless:
		return "ItemFrom_LangHuanBless";
	case ItemFrom_GroupTask:
		return "ItemFrom_GroupTask";
	case ItemFrom_SellItem:
		return "ItemFrom_SellItem";
	case ItemFrom_SignInAward:
		return "ItemFrom_SignInAward";
	case ItemFrom_ArenaBattle:
		return "ItemFrom_ArenaBattle";
	case ItemFrom_CharInit:
		return "ItemFrom_CharInit";
	case ItemFrom_LoginPkg:
		return "ItemFrom_LoginPkg";
	case ItemFrom_SevenDayTarget:
		return "ItemFrom_SevenDayTarget";
	case ItemFrom_WonderActivity:
		return "ItemFrom_WonderActivity";
	case ItemFrom_PHP:
		return "ItemFrom_PHP";
	case ItemFrom_BattleArrayItem:
		return "ItemFrom_BattleArrayItem";
	case ItemFrom_TreasureHunt:
		return "ItemFrom_TreasureHunt";
	case ItemFrom_Beauty:
		return "ItemFrom_Beauty";
	case ItemFrom_QQCoinExChange:
		return "ItemFrom_QQCoinExChange";
	case ItemFrom_Shushanweiwei:
		return "ItemFrom_Shushanweiwei";
	case ItemFrom_ShushanFound:
		return "ItemFrom_ShushanFound";
	case ItemFrom_CircleTask:
		return "ItemFrom_CircleTask";
	case ItemFrom_CircleTaskFinish:
		return "ItemFrom_CircleTaskFinish";
	case ItemFrom_MallChongZhi:
		return "ItemFrom_MallChongZhi";
	case ItemFrom_Answer:
		return "ItemFrom_Answer";
	case ItemFrom_GuardEMei:
		return "ItemFrom_GuardEMei";
	case ItemFrom_InviteFriend:
		return "ItemFrom_InviteFriend";
	case ItemFrom_QQAlarm:
		return "ItemFrom_QQAlarm";
	case ItemFrom_GuildXihe:
		return "ItemFrom_GuildXihe";
	case ItemFrom_Achievement:
		return "ItemFrom_Achievement";
	case ItemFrom_LadderBattle:
		return "ItemFrom_LadderBattle";
	case ItemFrom_ExchangeMoney:
		return "ItemFrom_ExchangeMoney";
	case ItemFrom_Draw:
		return "ItemFrom_Draw";
	case ItemFrom_StarAward:
		return "ItemFrom_StarAward";
	case ItemFrom_GodMonster:
		return "ItemFrom_GodMonster";
	case ItemFrom_LingShan:
		return "ItemFrom_LingShan";
	case ItemFrom_GuildExchangedItem:
		return "ItemFrom_GuildExchangedItem";
	case ItemFrom_MoneyTree:
		return "ItemFrom_MoneyTree";
	case ItemFrom_OffStone:
		return "ItemFrom_OffStone";
	case ItemFrom_MergeStone:
		return "ItemFrom_MergeStone";
	case ItemFrom_Lottery:
		return "ItemFrom_Lottery";
	case ItemFrom_RegisterSevenDaysDis:
		return "ItemFrom_RegisterSevenDaysDis";
	case ItemFrom_SecondRechargeAward:
		return "ItemFrom_SecondRechargeAward";
	case ItemFrom_Mall_NoGold:
		return "ItemFrom_Mall_NoGold";
	case ItemFrom_ETrumpStrength:
		return "ItemFrom_ETrumpStrength";
	case ItemFrom_ETrumpXiLian:
		return "ItemFrom_ETrumpXiLian";
	case ItemFrom_BreakEquipTrump:
		return "ItemFrom_BreakEquipTrump";
	case ItemFrom_MergeEquipTrump:
		return "ItemFrom_MergeEquipTrump";
	case ItemFrom_WearEquipTrump:
		return "ItemFrom_WearEquipTrump";
	case ItemFrom_TakeOffEquipTrump:
		return "ItemFrom_TakeOffEquipTrump";
	case ItemFrom_ShengLing:
		return "ItemFrom_ShengLing";
	case ItemFrom_Fenbaoyan:
		return "ItemFrom_Fenbaoyan";
	case ItemFrom_Feedback:
		return "ItemFrom_Feedback";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ItemFrom& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ItemFrom> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ItemFrom_GM", ItemFrom_GM));
		mapStr2Val.insert(make_pair("ItemFrom_InLuaBox", ItemFrom_InLuaBox));
		mapStr2Val.insert(make_pair("ItemFrom_System", ItemFrom_System));
		mapStr2Val.insert(make_pair("ItemFrom_EDgn", ItemFrom_EDgn));
		mapStr2Val.insert(make_pair("ItemFrom_DujieAward", ItemFrom_DujieAward));
		mapStr2Val.insert(make_pair("ItemFrom_MonsterDrop", ItemFrom_MonsterDrop));
		mapStr2Val.insert(make_pair("ItemFrom_YaMenAward", ItemFrom_YaMenAward));
		mapStr2Val.insert(make_pair("ItemFrom_BeastSoul", ItemFrom_BeastSoul));
		mapStr2Val.insert(make_pair("ItemFrom_Gather", ItemFrom_Gather));
		mapStr2Val.insert(make_pair("ItemFrom_Task", ItemFrom_Task));
		mapStr2Val.insert(make_pair("ItemFrom_Mail", ItemFrom_Mail));
		mapStr2Val.insert(make_pair("ItemFrom_Mall", ItemFrom_Mall));
		mapStr2Val.insert(make_pair("ItemFrom_DemonTower", ItemFrom_DemonTower));
		mapStr2Val.insert(make_pair("ItemFrom_TripodAward", ItemFrom_TripodAward));
		mapStr2Val.insert(make_pair("ItemFrom_ArenaAward", ItemFrom_ArenaAward));
		mapStr2Val.insert(make_pair("ItemFrom_RankAdoreAward", ItemFrom_RankAdoreAward));
		mapStr2Val.insert(make_pair("ItemFrom_VIPAward", ItemFrom_VIPAward));
		mapStr2Val.insert(make_pair("ItemFrom_YelloDiamondAward", ItemFrom_YelloDiamondAward));
		mapStr2Val.insert(make_pair("ItemFrom_FighterFind", ItemFrom_FighterFind));
		mapStr2Val.insert(make_pair("ItemFrom_ExchangeItem", ItemFrom_ExchangeItem));
		mapStr2Val.insert(make_pair("ItemFrom_LevelPrizeAct", ItemFrom_LevelPrizeAct));
		mapStr2Val.insert(make_pair("ItemFrom_Activity", ItemFrom_Activity));
		mapStr2Val.insert(make_pair("ItemFrom_CittaStore", ItemFrom_CittaStore));
		mapStr2Val.insert(make_pair("ItemFrom_UserDeptORPack", ItemFrom_UserDeptORPack));
		mapStr2Val.insert(make_pair("ItemFrom_ActiveTrump", ItemFrom_ActiveTrump));
		mapStr2Val.insert(make_pair("ItemFrom_MergeCitta", ItemFrom_MergeCitta));
		mapStr2Val.insert(make_pair("ItemFrom_BreakCitta", ItemFrom_BreakCitta));
		mapStr2Val.insert(make_pair("ItemFrom_HeroXinFaDisperse", ItemFrom_HeroXinFaDisperse));
		mapStr2Val.insert(make_pair("ItemFrom_PlayerXinFaDisperse", ItemFrom_PlayerXinFaDisperse));
		mapStr2Val.insert(make_pair("ItemFrom_NewCollection", ItemFrom_NewCollection));
		mapStr2Val.insert(make_pair("ItemFrom_NewAchieve", ItemFrom_NewAchieve));
		mapStr2Val.insert(make_pair("ItemFrom_EnergyBuy", ItemFrom_EnergyBuy));
		mapStr2Val.insert(make_pair("ItemFrom_EnergyBuff", ItemFrom_EnergyBuff));
		mapStr2Val.insert(make_pair("ItemFrom_DemonTowerSeal", ItemFrom_DemonTowerSeal));
		mapStr2Val.insert(make_pair("ItemFrom_DemonTowerPass", ItemFrom_DemonTowerPass));
		mapStr2Val.insert(make_pair("ItemFrom_Pend", ItemFrom_Pend));
		mapStr2Val.insert(make_pair("ItemFrom_Siting", ItemFrom_Siting));
		mapStr2Val.insert(make_pair("ItemFrom_Recharge", ItemFrom_Recharge));
		mapStr2Val.insert(make_pair("ItemFrom_LangHuanBless", ItemFrom_LangHuanBless));
		mapStr2Val.insert(make_pair("ItemFrom_GroupTask", ItemFrom_GroupTask));
		mapStr2Val.insert(make_pair("ItemFrom_SellItem", ItemFrom_SellItem));
		mapStr2Val.insert(make_pair("ItemFrom_SignInAward", ItemFrom_SignInAward));
		mapStr2Val.insert(make_pair("ItemFrom_ArenaBattle", ItemFrom_ArenaBattle));
		mapStr2Val.insert(make_pair("ItemFrom_CharInit", ItemFrom_CharInit));
		mapStr2Val.insert(make_pair("ItemFrom_LoginPkg", ItemFrom_LoginPkg));
		mapStr2Val.insert(make_pair("ItemFrom_SevenDayTarget", ItemFrom_SevenDayTarget));
		mapStr2Val.insert(make_pair("ItemFrom_WonderActivity", ItemFrom_WonderActivity));
		mapStr2Val.insert(make_pair("ItemFrom_PHP", ItemFrom_PHP));
		mapStr2Val.insert(make_pair("ItemFrom_BattleArrayItem", ItemFrom_BattleArrayItem));
		mapStr2Val.insert(make_pair("ItemFrom_TreasureHunt", ItemFrom_TreasureHunt));
		mapStr2Val.insert(make_pair("ItemFrom_Beauty", ItemFrom_Beauty));
		mapStr2Val.insert(make_pair("ItemFrom_QQCoinExChange", ItemFrom_QQCoinExChange));
		mapStr2Val.insert(make_pair("ItemFrom_Shushanweiwei", ItemFrom_Shushanweiwei));
		mapStr2Val.insert(make_pair("ItemFrom_ShushanFound", ItemFrom_ShushanFound));
		mapStr2Val.insert(make_pair("ItemFrom_CircleTask", ItemFrom_CircleTask));
		mapStr2Val.insert(make_pair("ItemFrom_CircleTaskFinish", ItemFrom_CircleTaskFinish));
		mapStr2Val.insert(make_pair("ItemFrom_MallChongZhi", ItemFrom_MallChongZhi));
		mapStr2Val.insert(make_pair("ItemFrom_Answer", ItemFrom_Answer));
		mapStr2Val.insert(make_pair("ItemFrom_GuardEMei", ItemFrom_GuardEMei));
		mapStr2Val.insert(make_pair("ItemFrom_InviteFriend", ItemFrom_InviteFriend));
		mapStr2Val.insert(make_pair("ItemFrom_QQAlarm", ItemFrom_QQAlarm));
		mapStr2Val.insert(make_pair("ItemFrom_GuildXihe", ItemFrom_GuildXihe));
		mapStr2Val.insert(make_pair("ItemFrom_Achievement", ItemFrom_Achievement));
		mapStr2Val.insert(make_pair("ItemFrom_LadderBattle", ItemFrom_LadderBattle));
		mapStr2Val.insert(make_pair("ItemFrom_ExchangeMoney", ItemFrom_ExchangeMoney));
		mapStr2Val.insert(make_pair("ItemFrom_Draw", ItemFrom_Draw));
		mapStr2Val.insert(make_pair("ItemFrom_StarAward", ItemFrom_StarAward));
		mapStr2Val.insert(make_pair("ItemFrom_GodMonster", ItemFrom_GodMonster));
		mapStr2Val.insert(make_pair("ItemFrom_LingShan", ItemFrom_LingShan));
		mapStr2Val.insert(make_pair("ItemFrom_GuildExchangedItem", ItemFrom_GuildExchangedItem));
		mapStr2Val.insert(make_pair("ItemFrom_MoneyTree", ItemFrom_MoneyTree));
		mapStr2Val.insert(make_pair("ItemFrom_OffStone", ItemFrom_OffStone));
		mapStr2Val.insert(make_pair("ItemFrom_MergeStone", ItemFrom_MergeStone));
		mapStr2Val.insert(make_pair("ItemFrom_Lottery", ItemFrom_Lottery));
		mapStr2Val.insert(make_pair("ItemFrom_RegisterSevenDaysDis", ItemFrom_RegisterSevenDaysDis));
		mapStr2Val.insert(make_pair("ItemFrom_SecondRechargeAward", ItemFrom_SecondRechargeAward));
		mapStr2Val.insert(make_pair("ItemFrom_Mall_NoGold", ItemFrom_Mall_NoGold));
		mapStr2Val.insert(make_pair("ItemFrom_ETrumpStrength", ItemFrom_ETrumpStrength));
		mapStr2Val.insert(make_pair("ItemFrom_ETrumpXiLian", ItemFrom_ETrumpXiLian));
		mapStr2Val.insert(make_pair("ItemFrom_BreakEquipTrump", ItemFrom_BreakEquipTrump));
		mapStr2Val.insert(make_pair("ItemFrom_MergeEquipTrump", ItemFrom_MergeEquipTrump));
		mapStr2Val.insert(make_pair("ItemFrom_WearEquipTrump", ItemFrom_WearEquipTrump));
		mapStr2Val.insert(make_pair("ItemFrom_TakeOffEquipTrump", ItemFrom_TakeOffEquipTrump));
		mapStr2Val.insert(make_pair("ItemFrom_ShengLing", ItemFrom_ShengLing));
		mapStr2Val.insert(make_pair("ItemFrom_Fenbaoyan", ItemFrom_Fenbaoyan));
		mapStr2Val.insert(make_pair("ItemFrom_Feedback", ItemFrom_Feedback));
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

const char* GetDescription(ItemFrom e)
{
	switch(e)
	{
	case ItemFrom_GM:
		return "GM指令里得到的物品";
	case ItemFrom_InLuaBox:
		return "lua脚本使用宝箱获得";
	case ItemFrom_System:
		return "系统奖励";
	case ItemFrom_EDgn:
		return "副本奖励";
	case ItemFrom_DujieAward:
		return "渡劫奖励";
	case ItemFrom_MonsterDrop:
		return "怪物掉落";
	case ItemFrom_YaMenAward:
		return "衙门每日奖励";
	case ItemFrom_BeastSoul:
		return "兽魂奖励";
	case ItemFrom_Gather:
		return "采集";
	case ItemFrom_Task:
		return "任务奖励";
	case ItemFrom_Mail:
		return "邮件";
	case ItemFrom_Mall:
		return "商城购买";
	case ItemFrom_DemonTower:
		return "锁妖塔";
	case ItemFrom_TripodAward:
		return "九疑鼎奖励";
	case ItemFrom_ArenaAward:
		return "斗剑奖励";
	case ItemFrom_RankAdoreAward:
		return "排行榜崇拜奖励";
	case ItemFrom_VIPAward:
		return "VIP礼包";
	case ItemFrom_YelloDiamondAward:
		return "黄钻礼包";
	case ItemFrom_FighterFind:
		return "刷将奖励";
	case ItemFrom_ExchangeItem:
		return "兑换物品";
	case ItemFrom_LevelPrizeAct:
		return "运营活动";
	case ItemFrom_Activity:
		return "活跃度";
	case ItemFrom_CittaStore:
		return "天书背包";
	case ItemFrom_UserDeptORPack:
		return "玩家仓库与背包道具交换、拆分、合并";
	case ItemFrom_ActiveTrump:
		return "法宝激活";
	case ItemFrom_MergeCitta:
		return "心法合成";
	case ItemFrom_BreakCitta:
		return "心法分解";
	case ItemFrom_HeroXinFaDisperse:
		return "散仙心法分解";
	case ItemFrom_PlayerXinFaDisperse:
		return "主将心法分解";
	case ItemFrom_NewCollection:
		return "收藏";
	case ItemFrom_NewAchieve:
		return "成就";
	case ItemFrom_EnergyBuy:
		return "购买精力";
	case ItemFrom_EnergyBuff:
		return "buffer增加精力";
	case ItemFrom_DemonTowerSeal:
		return "锁妖塔每日领取";
	case ItemFrom_DemonTowerPass:
		return "锁妖塔过关领取";
	case ItemFrom_Pend:
		return "延迟发放";
	case ItemFrom_Siting:
		return "双修";
	case ItemFrom_Recharge:
		return "充值";
	case ItemFrom_LangHuanBless:
		return "琅環福地";
	case ItemFrom_GroupTask:
		return "师门任务";
	case ItemFrom_SellItem:
		return "卖出物品";
	case ItemFrom_SignInAward:
		return "领取签到奖励礼包";
	case ItemFrom_ArenaBattle:
		return "斗剑历练奖励声望";
	case ItemFrom_CharInit:
		return "角色初始化获得";
	case ItemFrom_LoginPkg:
		return "累计登入获得";
	case ItemFrom_SevenDayTarget:
		return "7日目标活动";
	case ItemFrom_WonderActivity:
		return "精彩活动";
	case ItemFrom_PHP:
		return "客服后台操作";
	case ItemFrom_BattleArrayItem:
		return "破阵";
	case ItemFrom_TreasureHunt:
		return "寻宝";
	case ItemFrom_Beauty:
		return "美女系统";
	case ItemFrom_QQCoinExChange:
		return "QQ养成计划";
	case ItemFrom_Shushanweiwei:
		return "蜀山微微";
	case ItemFrom_ShushanFound:
		return "蜀山基金";
	case ItemFrom_CircleTask:
		return "环任务奖励";
	case ItemFrom_CircleTaskFinish:
		return "环任务全部完成奖励";
	case ItemFrom_MallChongZhi:
		return "商城充值活动奖励";
	case ItemFrom_Answer:
		return "答题活动";
	case ItemFrom_GuardEMei:
		return "守卫峨眉";
	case ItemFrom_InviteFriend:
		return "邀请好友";
	case ItemFrom_QQAlarm:
		return "QQAlarm奖励";
	case ItemFrom_GuildXihe:
		return "羲和神车奖励";
	case ItemFrom_Achievement:
		return "羲和神车奖励";
	case ItemFrom_LadderBattle:
		return "斗剑奖励资源";
	case ItemFrom_ExchangeMoney:
		return "货币兑换";
	case ItemFrom_Draw:
		return "求签";
	case ItemFrom_StarAward:
		return "副本星级领奖";
	case ItemFrom_GodMonster:
		return "天元神兽奖励";
	case ItemFrom_LingShan:
		return "秘境寻宝";
	case ItemFrom_GuildExchangedItem:
		return "帮派战物品兑换";
	case ItemFrom_MoneyTree:
		return "摇钱树";
	case ItemFrom_OffStone:
		return "取下宝石";
	case ItemFrom_MergeStone:
		return "宝石合成";
	case ItemFrom_Lottery:
		return "抽奖";
	case ItemFrom_RegisterSevenDaysDis:
		return "注册七天折扣豪礼大回馈";
	case ItemFrom_SecondRechargeAward:
		return "二次充值礼包";
	case ItemFrom_Mall_NoGold:
		return "商城购买非仙石";
	case ItemFrom_ETrumpStrength:
		return "装备法宝强化";
	case ItemFrom_ETrumpXiLian:
		return "装备法宝洗练";
	case ItemFrom_BreakEquipTrump:
		return "分解装备法宝";
	case ItemFrom_MergeEquipTrump:
		return "合成装备法宝";
	case ItemFrom_WearEquipTrump:
		return "穿戴装备法宝";
	case ItemFrom_TakeOffEquipTrump:
		return "卸下装备法宝";
	case ItemFrom_ShengLing:
		return "圣陵";
	case ItemFrom_Fenbaoyan:
		return "分宝岩";
	case ItemFrom_Feedback:
		return "消费回馈";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(ItemTo e)
{
	switch(e)
	{
	case ItemTo_Sell:
		return "ItemTo_Sell";
	case ItemTo_GM:
		return "ItemTo_GM";
	case ItemTo_UseItem:
		return "ItemTo_UseItem";
	case ItemTo_BeastSlots:
		return "ItemTo_BeastSlots";
	case ItemTo_CommitDujieTask:
		return "ItemTo_CommitDujieTask";
	case ItemTo_TripodMakeFire:
		return "ItemTo_TripodMakeFire";
	case ItemTo_TripodSpeed:
		return "ItemTo_TripodSpeed";
	case ItemTo_TripodActive:
		return "ItemTo_TripodActive";
	case ItemTo_TripodUpgrade:
		return "ItemTo_TripodUpgrade";
	case ItemTo_DemonTower:
		return "ItemTo_DemonTower";
	case ItemTo_ArenaFlush:
		return "ItemTo_ArenaFlush";
	case ItemTo_ArenaClearCD:
		return "ItemTo_ArenaClearCD";
	case ItemTo_ArenaWirship:
		return "ItemTo_ArenaWirship";
	case ItemTo_ArenaBuyTimes:
		return "ItemTo_ArenaBuyTimes";
	case ItemTo_ArenaClearLadderCD:
		return "ItemTo_ArenaClearLadderCD";
	case ItemTo_GuildDonate:
		return "ItemTo_GuildDonate";
	case ItemTo_GuildWorship:
		return "ItemTo_GuildWorship";
	case ItemTo_MergeCitta:
		return "ItemTo_MergeCitta";
	case ItemTo_UserDeptORPack:
		return "ItemTo_UserDeptORPack";
	case ItemTo_GatherCond:
		return "ItemTo_GatherCond";
	case ItemTo_Task:
		return "ItemTo_Task";
	case ItemTo_TrumpActive:
		return "ItemTo_TrumpActive";
	case ItemTo_TrumpUpgrade:
		return "ItemTo_TrumpUpgrade";
	case ItemTo_TrumpEvolve:
		return "ItemTo_TrumpEvolve";
	case ItemTo_LearnXinFa:
		return "ItemTo_LearnXinFa";
	case ItemTo_ZodTrumpUpgrade:
		return "ItemTo_ZodTrumpUpgrade";
	case ItemTo_EquipUpgrade:
		return "ItemTo_EquipUpgrade";
	case ItemTo_FashionUpgrade:
		return "ItemTo_FashionUpgrade";
	case ItemTo_FashionActive:
		return "ItemTo_FashionActive";
	case ItemTo_HorseActive:
		return "ItemTo_HorseActive";
	case ItemTo_HorseUpgrade:
		return "ItemTo_HorseUpgrade";
	case ItemTo_HeroInstinct:
		return "ItemTo_HeroInstinct";
	case ItemTo_TalentActive:
		return "ItemTo_TalentActive";
	case ItemTo_FormationActive:
		return "ItemTo_FormationActive";
	case ItemTo_PetActive:
		return "ItemTo_PetActive";
	case ItemTo_PetLvlUp:
		return "ItemTo_PetLvlUp";
	case ItemTo_Recruit:
		return "ItemTo_Recruit";
	case ItemTo_ExchangeItem:
		return "ItemTo_ExchangeItem";
	case ItemTo_FlushTask:
		return "ItemTo_FlushTask";
	case ItemTo_BuyTask:
		return "ItemTo_BuyTask";
	case ItemTo_YaMenFlushTask:
		return "ItemTo_YaMenFlushTask";
	case ItemTo_YaMenBuyTask:
		return "ItemTo_YaMenBuyTask";
	case ItemTo_HeroShift:
		return "ItemTo_HeroShift";
	case ItemTo_HeroCuiTiUpgrade:
		return "ItemTo_HeroCuiTiUpgrade";
	case ItemTo_FighterLuckyExchange:
		return "ItemTo_FighterLuckyExchange";
	case ItemTo_FighterSearch:
		return "ItemTo_FighterSearch";
	case ItemTo_FighterTaoismUpgrade:
		return "ItemTo_FighterTaoismUpgrade";
	case ItemTo_TaskForGroupAward:
		return "ItemTo_TaskForGroupAward";
	case ItemTo_TaskForYaMenAward:
		return "ItemTo_TaskForYaMenAward";
	case ItemTo_FigtherToOther:
		return "ItemTo_FigtherToOther";
	case ItemTo_ExpandStore:
		return "ItemTo_ExpandStore";
	case ItemTo_BuyGuildSkill:
		return "ItemTo_BuyGuildSkill";
	case ItemTo_SweepingSpeedUp:
		return "ItemTo_SweepingSpeedUp";
	case ItemTo_EquipIntensify:
		return "ItemTo_EquipIntensify";
	case ItemTo_AttachSpirit:
		return "ItemTo_AttachSpirit";
	case ItemTo_MallBuy:
		return "ItemTo_MallBuy";
	case ItemTo_HeroLevelUpgrade:
		return "ItemTo_HeroLevelUpgrade";
	case ItemTo_HeroSkillLevelUpgrade:
		return "ItemTo_HeroSkillLevelUpgrade";
	case ItemTo_HeroXinFaUpgrade:
		return "ItemTo_HeroXinFaUpgrade";
	case ItemTo_HeroSkillUpgrade:
		return "ItemTo_HeroSkillUpgrade";
	case ItemTo_PlayerXinFaUpgrade:
		return "ItemTo_PlayerXinFaUpgrade";
	case ItemTo_OpenVIP:
		return "ItemTo_OpenVIP";
	case ItemTo_OpenFriendVIP:
		return "ItemTo_OpenFriendVIP";
	case ItemTo_BuyAction:
		return "ItemTo_BuyAction";
	case ItemTo_ConsumeAction:
		return "ItemTo_ConsumeAction";
	case ItemTo_ZodTrump:
		return "ItemTo_ZodTrump";
	case ItemTo_BattleBuySkill:
		return "ItemTo_BattleBuySkill";
	case ItemTo_SoulSpaceUpgrade:
		return "ItemTo_SoulSpaceUpgrade";
	case ItemTo_WorldBossRelive:
		return "ItemTo_WorldBossRelive";
	case ItemTo_WorldBossBuyStrength:
		return "ItemTo_WorldBossBuyStrength";
	case ItemTo_WorldAttack:
		return "ItemTo_WorldAttack";
	case ItemTo_PlayerAdvanceUpgrade:
		return "ItemTo_PlayerAdvanceUpgrade";
	case ItemTo_PlayerSkillUpgrade:
		return "ItemTo_PlayerSkillUpgrade";
	case ItemTo_RuneUpgrade:
		return "ItemTo_RuneUpgrade";
	case ItemTo_UpgradeBeastSoul:
		return "ItemTo_UpgradeBeastSoul";
	case ItemTo_PHP:
		return "ItemTo_PHP";
	case ItemTo_FighterCombination:
		return "ItemTo_FighterCombination";
	case ItemTo_BattleArrayItem:
		return "ItemTo_BattleArrayItem";
	case ItemTo_TreasureHunt:
		return "ItemTo_TreasureHunt";
	case ItemTo_Beauty:
		return "ItemTo_Beauty";
	case ItemTo_ByOpenShipTimes:
		return "ItemTo_ByOpenShipTimes";
	case ItemTo_ByRobShipTimes:
		return "ItemTo_ByRobShipTimes";
	case ItemTo_ByReFlushShipTimes:
		return "ItemTo_ByReFlushShipTimes";
	case ItemTo_ShushanFound:
		return "ItemTo_ShushanFound";
	case ItemTo_CircleOneKey:
		return "ItemTo_CircleOneKey";
	case ItemTo_CircleOneKeyAll:
		return "ItemTo_CircleOneKeyAll";
	case ItemTo_GetShipOneKey:
		return "ItemTo_GetShipOneKey";
	case ItemTo_FinishShipOneKey:
		return "ItemTo_FinishShipOneKey";
	case ItemTo_CircleUpStar:
		return "ItemTo_CircleUpStar";
	case ItemTo_BuyHeroDgn:
		return "ItemTo_BuyHeroDgn";
	case ItemTo_BuyLiXianDgn:
		return "ItemTo_BuyLiXianDgn";
	case ItemTo_BuyEntryNum:
		return "ItemTo_BuyEntryNum";
	case ItemTo_GuildXihe:
		return "ItemTo_GuildXihe";
	case ItemTo_BuyLadderTimes:
		return "ItemTo_BuyLadderTimes";
	case ItemTo_ExchangeMoney:
		return "ItemTo_ExchangeMoney";
	case ItemTo_Draw:
		return "ItemTo_Draw";
	case ItemTo_FighterDismiss:
		return "ItemTo_FighterDismiss";
	case ItemTo_LingShan:
		return "ItemTo_LingShan";
	case ItemTo_GodMonster:
		return "ItemTo_GodMonster";
	case ItemTo_DujieConsume:
		return "ItemTo_DujieConsume";
	case ItemTo_MoneyTree:
		return "ItemTo_MoneyTree";
	case ItemTo_WareStone:
		return "ItemTo_WareStone";
	case ItemTo_MergeStone:
		return "ItemTo_MergeStone";
	case ItemTo_RegisterSevenDaysDis:
		return "ItemTo_RegisterSevenDaysDis";
	case ItemTo_MallBuy_NoGold:
		return "ItemTo_MallBuy_NoGold";
	case ItemTo_NewGuildBattleDead:
		return "ItemTo_NewGuildBattleDead";
	case ItemTo_NewGuildBattleBuyPuppet:
		return "ItemTo_NewGuildBattleBuyPuppet";
	case ItemTo_BreakCitta:
		return "ItemTo_BreakCitta";
	case ItemTo_FighterBuyLYQ:
		return "ItemTo_FighterBuyLYQ";
	case ItemTo_FighterBuyQLY:
		return "ItemTo_FighterBuyQLY";
	case ItemTo_ETrumpStrength:
		return "ItemTo_ETrumpStrength";
	case ItemTo_ETrumpXiLian:
		return "ItemTo_ETrumpXiLian";
	case ItemTo_BreakEquipTrump:
		return "ItemTo_BreakEquipTrump";
	case ItemTo_MergeEquipTrump:
		return "ItemTo_MergeEquipTrump";
	case ItemTo_WearEquipTrump:
		return "ItemTo_WearEquipTrump";
	case ItemTo_TakeOffEquipTrump:
		return "ItemTo_TakeOffEquipTrump";
	case ItemTo_ShengLing:
		return "ItemTo_ShengLing";
	case ItemTo_Fenbaoyan:
		return "ItemTo_Fenbaoyan";
	case ItemTo_Feedback:
		return "ItemTo_Feedback";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ItemTo& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ItemTo> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ItemTo_Sell", ItemTo_Sell));
		mapStr2Val.insert(make_pair("ItemTo_GM", ItemTo_GM));
		mapStr2Val.insert(make_pair("ItemTo_UseItem", ItemTo_UseItem));
		mapStr2Val.insert(make_pair("ItemTo_BeastSlots", ItemTo_BeastSlots));
		mapStr2Val.insert(make_pair("ItemTo_CommitDujieTask", ItemTo_CommitDujieTask));
		mapStr2Val.insert(make_pair("ItemTo_TripodMakeFire", ItemTo_TripodMakeFire));
		mapStr2Val.insert(make_pair("ItemTo_TripodSpeed", ItemTo_TripodSpeed));
		mapStr2Val.insert(make_pair("ItemTo_TripodActive", ItemTo_TripodActive));
		mapStr2Val.insert(make_pair("ItemTo_TripodUpgrade", ItemTo_TripodUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_DemonTower", ItemTo_DemonTower));
		mapStr2Val.insert(make_pair("ItemTo_ArenaFlush", ItemTo_ArenaFlush));
		mapStr2Val.insert(make_pair("ItemTo_ArenaClearCD", ItemTo_ArenaClearCD));
		mapStr2Val.insert(make_pair("ItemTo_ArenaWirship", ItemTo_ArenaWirship));
		mapStr2Val.insert(make_pair("ItemTo_ArenaBuyTimes", ItemTo_ArenaBuyTimes));
		mapStr2Val.insert(make_pair("ItemTo_ArenaClearLadderCD", ItemTo_ArenaClearLadderCD));
		mapStr2Val.insert(make_pair("ItemTo_GuildDonate", ItemTo_GuildDonate));
		mapStr2Val.insert(make_pair("ItemTo_GuildWorship", ItemTo_GuildWorship));
		mapStr2Val.insert(make_pair("ItemTo_MergeCitta", ItemTo_MergeCitta));
		mapStr2Val.insert(make_pair("ItemTo_UserDeptORPack", ItemTo_UserDeptORPack));
		mapStr2Val.insert(make_pair("ItemTo_GatherCond", ItemTo_GatherCond));
		mapStr2Val.insert(make_pair("ItemTo_Task", ItemTo_Task));
		mapStr2Val.insert(make_pair("ItemTo_TrumpActive", ItemTo_TrumpActive));
		mapStr2Val.insert(make_pair("ItemTo_TrumpUpgrade", ItemTo_TrumpUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_TrumpEvolve", ItemTo_TrumpEvolve));
		mapStr2Val.insert(make_pair("ItemTo_LearnXinFa", ItemTo_LearnXinFa));
		mapStr2Val.insert(make_pair("ItemTo_ZodTrumpUpgrade", ItemTo_ZodTrumpUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_EquipUpgrade", ItemTo_EquipUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_FashionUpgrade", ItemTo_FashionUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_FashionActive", ItemTo_FashionActive));
		mapStr2Val.insert(make_pair("ItemTo_HorseActive", ItemTo_HorseActive));
		mapStr2Val.insert(make_pair("ItemTo_HorseUpgrade", ItemTo_HorseUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_HeroInstinct", ItemTo_HeroInstinct));
		mapStr2Val.insert(make_pair("ItemTo_TalentActive", ItemTo_TalentActive));
		mapStr2Val.insert(make_pair("ItemTo_FormationActive", ItemTo_FormationActive));
		mapStr2Val.insert(make_pair("ItemTo_PetActive", ItemTo_PetActive));
		mapStr2Val.insert(make_pair("ItemTo_PetLvlUp", ItemTo_PetLvlUp));
		mapStr2Val.insert(make_pair("ItemTo_Recruit", ItemTo_Recruit));
		mapStr2Val.insert(make_pair("ItemTo_ExchangeItem", ItemTo_ExchangeItem));
		mapStr2Val.insert(make_pair("ItemTo_FlushTask", ItemTo_FlushTask));
		mapStr2Val.insert(make_pair("ItemTo_BuyTask", ItemTo_BuyTask));
		mapStr2Val.insert(make_pair("ItemTo_YaMenFlushTask", ItemTo_YaMenFlushTask));
		mapStr2Val.insert(make_pair("ItemTo_YaMenBuyTask", ItemTo_YaMenBuyTask));
		mapStr2Val.insert(make_pair("ItemTo_HeroShift", ItemTo_HeroShift));
		mapStr2Val.insert(make_pair("ItemTo_HeroCuiTiUpgrade", ItemTo_HeroCuiTiUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_FighterLuckyExchange", ItemTo_FighterLuckyExchange));
		mapStr2Val.insert(make_pair("ItemTo_FighterSearch", ItemTo_FighterSearch));
		mapStr2Val.insert(make_pair("ItemTo_FighterTaoismUpgrade", ItemTo_FighterTaoismUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_TaskForGroupAward", ItemTo_TaskForGroupAward));
		mapStr2Val.insert(make_pair("ItemTo_TaskForYaMenAward", ItemTo_TaskForYaMenAward));
		mapStr2Val.insert(make_pair("ItemTo_FigtherToOther", ItemTo_FigtherToOther));
		mapStr2Val.insert(make_pair("ItemTo_ExpandStore", ItemTo_ExpandStore));
		mapStr2Val.insert(make_pair("ItemTo_BuyGuildSkill", ItemTo_BuyGuildSkill));
		mapStr2Val.insert(make_pair("ItemTo_SweepingSpeedUp", ItemTo_SweepingSpeedUp));
		mapStr2Val.insert(make_pair("ItemTo_EquipIntensify", ItemTo_EquipIntensify));
		mapStr2Val.insert(make_pair("ItemTo_AttachSpirit", ItemTo_AttachSpirit));
		mapStr2Val.insert(make_pair("ItemTo_MallBuy", ItemTo_MallBuy));
		mapStr2Val.insert(make_pair("ItemTo_HeroLevelUpgrade", ItemTo_HeroLevelUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_HeroSkillLevelUpgrade", ItemTo_HeroSkillLevelUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_HeroXinFaUpgrade", ItemTo_HeroXinFaUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_HeroSkillUpgrade", ItemTo_HeroSkillUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_PlayerXinFaUpgrade", ItemTo_PlayerXinFaUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_OpenVIP", ItemTo_OpenVIP));
		mapStr2Val.insert(make_pair("ItemTo_OpenFriendVIP", ItemTo_OpenFriendVIP));
		mapStr2Val.insert(make_pair("ItemTo_BuyAction", ItemTo_BuyAction));
		mapStr2Val.insert(make_pair("ItemTo_ConsumeAction", ItemTo_ConsumeAction));
		mapStr2Val.insert(make_pair("ItemTo_ZodTrump", ItemTo_ZodTrump));
		mapStr2Val.insert(make_pair("ItemTo_BattleBuySkill", ItemTo_BattleBuySkill));
		mapStr2Val.insert(make_pair("ItemTo_SoulSpaceUpgrade", ItemTo_SoulSpaceUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_WorldBossRelive", ItemTo_WorldBossRelive));
		mapStr2Val.insert(make_pair("ItemTo_WorldBossBuyStrength", ItemTo_WorldBossBuyStrength));
		mapStr2Val.insert(make_pair("ItemTo_WorldAttack", ItemTo_WorldAttack));
		mapStr2Val.insert(make_pair("ItemTo_PlayerAdvanceUpgrade", ItemTo_PlayerAdvanceUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_PlayerSkillUpgrade", ItemTo_PlayerSkillUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_RuneUpgrade", ItemTo_RuneUpgrade));
		mapStr2Val.insert(make_pair("ItemTo_UpgradeBeastSoul", ItemTo_UpgradeBeastSoul));
		mapStr2Val.insert(make_pair("ItemTo_PHP", ItemTo_PHP));
		mapStr2Val.insert(make_pair("ItemTo_FighterCombination", ItemTo_FighterCombination));
		mapStr2Val.insert(make_pair("ItemTo_BattleArrayItem", ItemTo_BattleArrayItem));
		mapStr2Val.insert(make_pair("ItemTo_TreasureHunt", ItemTo_TreasureHunt));
		mapStr2Val.insert(make_pair("ItemTo_Beauty", ItemTo_Beauty));
		mapStr2Val.insert(make_pair("ItemTo_ByOpenShipTimes", ItemTo_ByOpenShipTimes));
		mapStr2Val.insert(make_pair("ItemTo_ByRobShipTimes", ItemTo_ByRobShipTimes));
		mapStr2Val.insert(make_pair("ItemTo_ByReFlushShipTimes", ItemTo_ByReFlushShipTimes));
		mapStr2Val.insert(make_pair("ItemTo_ShushanFound", ItemTo_ShushanFound));
		mapStr2Val.insert(make_pair("ItemTo_CircleOneKey", ItemTo_CircleOneKey));
		mapStr2Val.insert(make_pair("ItemTo_CircleOneKeyAll", ItemTo_CircleOneKeyAll));
		mapStr2Val.insert(make_pair("ItemTo_GetShipOneKey", ItemTo_GetShipOneKey));
		mapStr2Val.insert(make_pair("ItemTo_FinishShipOneKey", ItemTo_FinishShipOneKey));
		mapStr2Val.insert(make_pair("ItemTo_CircleUpStar", ItemTo_CircleUpStar));
		mapStr2Val.insert(make_pair("ItemTo_BuyHeroDgn", ItemTo_BuyHeroDgn));
		mapStr2Val.insert(make_pair("ItemTo_BuyLiXianDgn", ItemTo_BuyLiXianDgn));
		mapStr2Val.insert(make_pair("ItemTo_BuyEntryNum", ItemTo_BuyEntryNum));
		mapStr2Val.insert(make_pair("ItemTo_GuildXihe", ItemTo_GuildXihe));
		mapStr2Val.insert(make_pair("ItemTo_BuyLadderTimes", ItemTo_BuyLadderTimes));
		mapStr2Val.insert(make_pair("ItemTo_ExchangeMoney", ItemTo_ExchangeMoney));
		mapStr2Val.insert(make_pair("ItemTo_Draw", ItemTo_Draw));
		mapStr2Val.insert(make_pair("ItemTo_FighterDismiss", ItemTo_FighterDismiss));
		mapStr2Val.insert(make_pair("ItemTo_LingShan", ItemTo_LingShan));
		mapStr2Val.insert(make_pair("ItemTo_GodMonster", ItemTo_GodMonster));
		mapStr2Val.insert(make_pair("ItemTo_DujieConsume", ItemTo_DujieConsume));
		mapStr2Val.insert(make_pair("ItemTo_MoneyTree", ItemTo_MoneyTree));
		mapStr2Val.insert(make_pair("ItemTo_WareStone", ItemTo_WareStone));
		mapStr2Val.insert(make_pair("ItemTo_MergeStone", ItemTo_MergeStone));
		mapStr2Val.insert(make_pair("ItemTo_RegisterSevenDaysDis", ItemTo_RegisterSevenDaysDis));
		mapStr2Val.insert(make_pair("ItemTo_MallBuy_NoGold", ItemTo_MallBuy_NoGold));
		mapStr2Val.insert(make_pair("ItemTo_NewGuildBattleDead", ItemTo_NewGuildBattleDead));
		mapStr2Val.insert(make_pair("ItemTo_NewGuildBattleBuyPuppet", ItemTo_NewGuildBattleBuyPuppet));
		mapStr2Val.insert(make_pair("ItemTo_BreakCitta", ItemTo_BreakCitta));
		mapStr2Val.insert(make_pair("ItemTo_FighterBuyLYQ", ItemTo_FighterBuyLYQ));
		mapStr2Val.insert(make_pair("ItemTo_FighterBuyQLY", ItemTo_FighterBuyQLY));
		mapStr2Val.insert(make_pair("ItemTo_ETrumpStrength", ItemTo_ETrumpStrength));
		mapStr2Val.insert(make_pair("ItemTo_ETrumpXiLian", ItemTo_ETrumpXiLian));
		mapStr2Val.insert(make_pair("ItemTo_BreakEquipTrump", ItemTo_BreakEquipTrump));
		mapStr2Val.insert(make_pair("ItemTo_MergeEquipTrump", ItemTo_MergeEquipTrump));
		mapStr2Val.insert(make_pair("ItemTo_WearEquipTrump", ItemTo_WearEquipTrump));
		mapStr2Val.insert(make_pair("ItemTo_TakeOffEquipTrump", ItemTo_TakeOffEquipTrump));
		mapStr2Val.insert(make_pair("ItemTo_ShengLing", ItemTo_ShengLing));
		mapStr2Val.insert(make_pair("ItemTo_Fenbaoyan", ItemTo_Fenbaoyan));
		mapStr2Val.insert(make_pair("ItemTo_Feedback", ItemTo_Feedback));
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

const char* GetDescription(ItemTo e)
{
	switch(e)
	{
	case ItemTo_Sell:
		return "出售给系统";
	case ItemTo_GM:
		return "GM指令里删除物品";
	case ItemTo_UseItem:
		return "物品使用";
	case ItemTo_BeastSlots:
		return "激活兽魂";
	case ItemTo_CommitDujieTask:
		return "提交渡劫任务消耗";
	case ItemTo_TripodMakeFire:
		return "九疑鼎祈火";
	case ItemTo_TripodSpeed:
		return "九疑鼎道具入鼎";
	case ItemTo_TripodActive:
		return "九疑鼎激活消耗";
	case ItemTo_TripodUpgrade:
		return "九疑鼎升级消耗";
	case ItemTo_DemonTower:
		return "锁妖塔消耗";
	case ItemTo_ArenaFlush:
		return "斗剑刷将";
	case ItemTo_ArenaClearCD:
		return "清除斗剑CD";
	case ItemTo_ArenaWirship:
		return "斗剑膜拜";
	case ItemTo_ArenaBuyTimes:
		return "斗剑购买挑战次数";
	case ItemTo_ArenaClearLadderCD:
		return "斗剑天梯cd清除";
	case ItemTo_GuildDonate:
		return "帮派捐献";
	case ItemTo_GuildWorship:
		return "帮派供奉";
	case ItemTo_MergeCitta:
		return "天书使用、分解、穿戴";
	case ItemTo_UserDeptORPack:
		return "玩家仓库与背包道具交换、拆分、合并";
	case ItemTo_GatherCond:
		return "玩家收集消耗";
	case ItemTo_Task:
		return "任务消耗";
	case ItemTo_TrumpActive:
		return "主将法宝激活消耗";
	case ItemTo_TrumpUpgrade:
		return "主将法宝祭炼升级消耗";
	case ItemTo_TrumpEvolve:
		return "主将法宝升阶消耗";
	case ItemTo_LearnXinFa:
		return "学习心法消耗";
	case ItemTo_ZodTrumpUpgrade:
		return "散仙本命法宝祭炼升级消耗";
	case ItemTo_EquipUpgrade:
		return "装备升级消耗";
	case ItemTo_FashionUpgrade:
		return "时装升级消耗";
	case ItemTo_FashionActive:
		return "时装激活消耗";
	case ItemTo_HorseActive:
		return "坐骑激活消耗";
	case ItemTo_HorseUpgrade:
		return "坐骑升级消耗";
	case ItemTo_HeroInstinct:
		return "散仙血脉激活消耗";
	case ItemTo_TalentActive:
		return "天赋激活消耗";
	case ItemTo_FormationActive:
		return "阵型激活消耗";
	case ItemTo_PetActive:
		return "宠物激活消耗";
	case ItemTo_PetLvlUp:
		return "宠物升级消耗";
	case ItemTo_Recruit:
		return "将领招募消耗";
	case ItemTo_ExchangeItem:
		return "兑换物品消耗";
	case ItemTo_FlushTask:
		return "刷新师门任务";
	case ItemTo_BuyTask:
		return "购买师门任务";
	case ItemTo_YaMenFlushTask:
		return "刷新衙门任务";
	case ItemTo_YaMenBuyTask:
		return "购买衙门任务";
	case ItemTo_HeroShift:
		return "散仙转移";
	case ItemTo_HeroCuiTiUpgrade:
		return "散仙粹体升级";
	case ItemTo_FighterLuckyExchange:
		return "散仙兑换";
	case ItemTo_FighterSearch:
		return "散仙搜索";
	case ItemTo_FighterTaoismUpgrade:
		return "道术升级";
	case ItemTo_TaskForGroupAward:
		return "师门任务领奖";
	case ItemTo_TaskForYaMenAward:
		return "衙门任务领奖";
	case ItemTo_FigtherToOther:
		return "发起战斗";
	case ItemTo_ExpandStore:
		return "扩展背包";
	case ItemTo_BuyGuildSkill:
		return "购买工会战技能";
	case ItemTo_SweepingSpeedUp:
		return "扫荡加速";
	case ItemTo_EquipIntensify:
		return "装备强化";
	case ItemTo_AttachSpirit:
		return "装备注灵";
	case ItemTo_MallBuy:
		return "商城购买";
	case ItemTo_HeroLevelUpgrade:
		return "散仙升级";
	case ItemTo_HeroSkillLevelUpgrade:
		return "散仙天赋技能升级";
	case ItemTo_HeroXinFaUpgrade:
		return "散仙心法升级";
	case ItemTo_HeroSkillUpgrade:
		return "散仙技能升级";
	case ItemTo_PlayerXinFaUpgrade:
		return "玩家心法升级";
	case ItemTo_OpenVIP:
		return "开启vip";
	case ItemTo_OpenFriendVIP:
		return "给好友开启vip";
	case ItemTo_BuyAction:
		return "购买行动力";
	case ItemTo_ConsumeAction:
		return "副本或扫荡消耗";
	case ItemTo_ZodTrump:
		return "法宝升级";
	case ItemTo_BattleBuySkill:
		return "论剑购买技能";
	case ItemTo_SoulSpaceUpgrade:
		return "魄空间升级";
	case ItemTo_WorldBossRelive:
		return "世界boss复活";
	case ItemTo_WorldBossBuyStrength:
		return "世界boss购买buffer";
	case ItemTo_WorldAttack:
		return "世界boss购买立即攻击";
	case ItemTo_PlayerAdvanceUpgrade:
		return "主将技能进阶";
	case ItemTo_PlayerSkillUpgrade:
		return "主将技能升级";
	case ItemTo_RuneUpgrade:
		return "主将技能熔炼";
	case ItemTo_UpgradeBeastSoul:
		return "兽魂";
	case ItemTo_PHP:
		return "客服后台操作";
	case ItemTo_FighterCombination:
		return "散仙组合升级消耗";
	case ItemTo_BattleArrayItem:
		return "破阵";
	case ItemTo_TreasureHunt:
		return "一键寻宝";
	case ItemTo_Beauty:
		return "美女系统";
	case ItemTo_ByOpenShipTimes:
		return "购买运船次数";
	case ItemTo_ByRobShipTimes:
		return "购买抢船次数";
	case ItemTo_ByReFlushShipTimes:
		return "购买刷船次数";
	case ItemTo_ShushanFound:
		return "购买蜀山基金";
	case ItemTo_CircleOneKey:
		return "环任务立即完成当前";
	case ItemTo_CircleOneKeyAll:
		return "环任务立即完成所有";
	case ItemTo_GetShipOneKey:
		return "vip召唤船只";
	case ItemTo_FinishShipOneKey:
		return "一键完成运船";
	case ItemTo_CircleUpStar:
		return "环任务升星";
	case ItemTo_BuyHeroDgn:
		return "购买英雄副本次数";
	case ItemTo_BuyLiXianDgn:
		return "购买历险副本次数";
	case ItemTo_BuyEntryNum:
		return "购买守卫峨眉进入次数";
	case ItemTo_GuildXihe:
		return "羲和神车消耗";
	case ItemTo_BuyLadderTimes:
		return "购买天梯挑战次数";
	case ItemTo_ExchangeMoney:
		return "货币兑换";
	case ItemTo_Draw:
		return "求签";
	case ItemTo_FighterDismiss:
		return "散功消耗";
	case ItemTo_LingShan:
		return "秘境寻宝";
	case ItemTo_GodMonster:
		return "天元神兽消耗";
	case ItemTo_DujieConsume:
		return "散仙渡劫消耗";
	case ItemTo_MoneyTree:
		return "摇钱树消耗";
	case ItemTo_WareStone:
		return "装备宝石";
	case ItemTo_MergeStone:
		return "合成消耗";
	case ItemTo_RegisterSevenDaysDis:
		return "注册七天折扣豪礼大回馈消耗";
	case ItemTo_MallBuy_NoGold:
		return "商城购买_礼卷";
	case ItemTo_NewGuildBattleDead:
		return "灵山买活";
	case ItemTo_NewGuildBattleBuyPuppet:
		return "购买傀儡";
	case ItemTo_BreakCitta:
		return "心法分解";
	case ItemTo_FighterBuyLYQ:
		return "邀仙居——李英琼";
	case ItemTo_FighterBuyQLY:
		return "邀仙居——齐灵云";
	case ItemTo_ETrumpStrength:
		return "装备法宝强化";
	case ItemTo_ETrumpXiLian:
		return "装备法宝洗练";
	case ItemTo_BreakEquipTrump:
		return "分解装备法宝";
	case ItemTo_MergeEquipTrump:
		return "合成装备法宝";
	case ItemTo_WearEquipTrump:
		return "穿戴装备法宝";
	case ItemTo_TakeOffEquipTrump:
		return "卸下装备法宝";
	case ItemTo_ShengLing:
		return "圣陵";
	case ItemTo_Fenbaoyan:
		return "分宝岩";
	case ItemTo_Feedback:
		return "消费回馈";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EFighterOptType e)
{
	switch(e)
	{
	case eOptType_Recurit:
		return "eOptType_Recurit";
	case eOptType_Upgrade:
		return "eOptType_Upgrade";
	case eOptType_CuiTi:
		return "eOptType_CuiTi";
	case eOptType_FaBao:
		return "eOptType_FaBao";
	case eOptType_Skill:
		return "eOptType_Skill";
	case eOptType_Shift:
		return "eOptType_Shift";
	case eOptType_XinFa:
		return "eOptType_XinFa";
	case eOptType_PassiveSkill:
		return "eOptType_PassiveSkill";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EFighterOptType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EFighterOptType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eOptType_Recurit", eOptType_Recurit));
		mapStr2Val.insert(make_pair("eOptType_Upgrade", eOptType_Upgrade));
		mapStr2Val.insert(make_pair("eOptType_CuiTi", eOptType_CuiTi));
		mapStr2Val.insert(make_pair("eOptType_FaBao", eOptType_FaBao));
		mapStr2Val.insert(make_pair("eOptType_Skill", eOptType_Skill));
		mapStr2Val.insert(make_pair("eOptType_Shift", eOptType_Shift));
		mapStr2Val.insert(make_pair("eOptType_XinFa", eOptType_XinFa));
		mapStr2Val.insert(make_pair("eOptType_PassiveSkill", eOptType_PassiveSkill));
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

LogDataBase::LogDataBase() { }

CInArchive& operator>>(CInArchive& src, LogDataBase& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const LogDataBase& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, LogDataBase_Wrapper& rWrapper)
{
	EType_LogDataBase eType = eType_LogDataBase;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_LogDataBase:
		{
			rWrapper.ptr.reset(new LogDataBase);
			src >> (LogDataBase&)*rWrapper.ptr;
		}
		break;
	case eType_SDgnLog:
		{
			rWrapper.ptr.reset(new SDgnLog);
			src >> (SDgnLog&)*rWrapper.ptr;
		}
		break;
	case eType_SRegisterLog:
		{
			rWrapper.ptr.reset(new SRegisterLog);
			src >> (SRegisterLog&)*rWrapper.ptr;
		}
		break;
	case eType_SLoginLog:
		{
			rWrapper.ptr.reset(new SLoginLog);
			src >> (SLoginLog&)*rWrapper.ptr;
		}
		break;
	case eType_SItemCoursesLog:
		{
			rWrapper.ptr.reset(new SItemCoursesLog);
			src >> (SItemCoursesLog&)*rWrapper.ptr;
		}
		break;
	case eType_SMoneyCoursesLog:
		{
			rWrapper.ptr.reset(new SMoneyCoursesLog);
			src >> (SMoneyCoursesLog&)*rWrapper.ptr;
		}
		break;
	case eType_SMailLog:
		{
			rWrapper.ptr.reset(new SMailLog);
			src >> (SMailLog&)*rWrapper.ptr;
		}
		break;
	case eType_SPetLog:
		{
			rWrapper.ptr.reset(new SPetLog);
			src >> (SPetLog&)*rWrapper.ptr;
		}
		break;
	case eType_SDujieLog:
		{
			rWrapper.ptr.reset(new SDujieLog);
			src >> (SDujieLog&)*rWrapper.ptr;
		}
		break;
	case eType_SFashionLog:
		{
			rWrapper.ptr.reset(new SFashionLog);
			src >> (SFashionLog&)*rWrapper.ptr;
		}
		break;
	case eType_SFighterLog:
		{
			rWrapper.ptr.reset(new SFighterLog);
			src >> (SFighterLog&)*rWrapper.ptr;
		}
		break;
	case eType_SHorseLog:
		{
			rWrapper.ptr.reset(new SHorseLog);
			src >> (SHorseLog&)*rWrapper.ptr;
		}
		break;
	case eType_STrumpLog:
		{
			rWrapper.ptr.reset(new STrumpLog);
			src >> (STrumpLog&)*rWrapper.ptr;
		}
		break;
	case eType_SBeautyLog:
		{
			rWrapper.ptr.reset(new SBeautyLog);
			src >> (SBeautyLog&)*rWrapper.ptr;
		}
		break;
	case eType_SEquipLog:
		{
			rWrapper.ptr.reset(new SEquipLog);
			src >> (SEquipLog&)*rWrapper.ptr;
		}
		break;
	case eType_SGuildLog:
		{
			rWrapper.ptr.reset(new SGuildLog);
			src >> (SGuildLog&)*rWrapper.ptr;
		}
		break;
	case eType_SSendMoneyLog:
		{
			rWrapper.ptr.reset(new SSendMoneyLog);
			src >> (SSendMoneyLog&)*rWrapper.ptr;
		}
		break;
	case eType_SSendItemLog:
		{
			rWrapper.ptr.reset(new SSendItemLog);
			src >> (SSendItemLog&)*rWrapper.ptr;
		}
		break;
	case eType_SMailOpLog:
		{
			rWrapper.ptr.reset(new SMailOpLog);
			src >> (SMailOpLog&)*rWrapper.ptr;
		}
		break;
	case eType_SForbiddenLog:
		{
			rWrapper.ptr.reset(new SForbiddenLog);
			src >> (SForbiddenLog&)*rWrapper.ptr;
		}
		break;
	case eType_SForbiddenChatLog:
		{
			rWrapper.ptr.reset(new SForbiddenChatLog);
			src >> (SForbiddenChatLog&)*rWrapper.ptr;
		}
		break;
	case eType_SGlobalSendItemLog:
		{
			rWrapper.ptr.reset(new SGlobalSendItemLog);
			src >> (SGlobalSendItemLog&)*rWrapper.ptr;
		}
		break;
	case eType_SQuesOptLog:
		{
			rWrapper.ptr.reset(new SQuesOptLog);
			src >> (SQuesOptLog&)*rWrapper.ptr;
		}
		break;
	case eType_SSendMailLog:
		{
			rWrapper.ptr.reset(new SSendMailLog);
			src >> (SSendMailLog&)*rWrapper.ptr;
		}
		break;
	case eType_SVIPSendLog:
		{
			rWrapper.ptr.reset(new SVIPSendLog);
			src >> (SVIPSendLog&)*rWrapper.ptr;
		}
		break;
	case eType_SActivityOpenLog:
		{
			rWrapper.ptr.reset(new SActivityOpenLog);
			src >> (SActivityOpenLog&)*rWrapper.ptr;
		}
		break;
	case eType_SDiscountItemLog:
		{
			rWrapper.ptr.reset(new SDiscountItemLog);
			src >> (SDiscountItemLog&)*rWrapper.ptr;
		}
		break;
	case eType_SLevelChangeLog:
		{
			rWrapper.ptr.reset(new SLevelChangeLog);
			src >> (SLevelChangeLog&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_LogDataBase";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const LogDataBase_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_LogDataBase:
			src << (LogDataBase&)*rWrapper.ptr;
			break;
		case eType_SDgnLog:
			src << (SDgnLog&)*rWrapper.ptr;
			break;
		case eType_SRegisterLog:
			src << (SRegisterLog&)*rWrapper.ptr;
			break;
		case eType_SLoginLog:
			src << (SLoginLog&)*rWrapper.ptr;
			break;
		case eType_SItemCoursesLog:
			src << (SItemCoursesLog&)*rWrapper.ptr;
			break;
		case eType_SMoneyCoursesLog:
			src << (SMoneyCoursesLog&)*rWrapper.ptr;
			break;
		case eType_SMailLog:
			src << (SMailLog&)*rWrapper.ptr;
			break;
		case eType_SPetLog:
			src << (SPetLog&)*rWrapper.ptr;
			break;
		case eType_SDujieLog:
			src << (SDujieLog&)*rWrapper.ptr;
			break;
		case eType_SFashionLog:
			src << (SFashionLog&)*rWrapper.ptr;
			break;
		case eType_SFighterLog:
			src << (SFighterLog&)*rWrapper.ptr;
			break;
		case eType_SHorseLog:
			src << (SHorseLog&)*rWrapper.ptr;
			break;
		case eType_STrumpLog:
			src << (STrumpLog&)*rWrapper.ptr;
			break;
		case eType_SBeautyLog:
			src << (SBeautyLog&)*rWrapper.ptr;
			break;
		case eType_SEquipLog:
			src << (SEquipLog&)*rWrapper.ptr;
			break;
		case eType_SGuildLog:
			src << (SGuildLog&)*rWrapper.ptr;
			break;
		case eType_SSendMoneyLog:
			src << (SSendMoneyLog&)*rWrapper.ptr;
			break;
		case eType_SSendItemLog:
			src << (SSendItemLog&)*rWrapper.ptr;
			break;
		case eType_SMailOpLog:
			src << (SMailOpLog&)*rWrapper.ptr;
			break;
		case eType_SForbiddenLog:
			src << (SForbiddenLog&)*rWrapper.ptr;
			break;
		case eType_SForbiddenChatLog:
			src << (SForbiddenChatLog&)*rWrapper.ptr;
			break;
		case eType_SGlobalSendItemLog:
			src << (SGlobalSendItemLog&)*rWrapper.ptr;
			break;
		case eType_SQuesOptLog:
			src << (SQuesOptLog&)*rWrapper.ptr;
			break;
		case eType_SSendMailLog:
			src << (SSendMailLog&)*rWrapper.ptr;
			break;
		case eType_SVIPSendLog:
			src << (SVIPSendLog&)*rWrapper.ptr;
			break;
		case eType_SActivityOpenLog:
			src << (SActivityOpenLog&)*rWrapper.ptr;
			break;
		case eType_SDiscountItemLog:
			src << (SDiscountItemLog&)*rWrapper.ptr;
			break;
		case eType_SLevelChangeLog:
			src << (SLevelChangeLog&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_LogDataBase";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecLogDataBase& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		LogDataBase_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecLogDataBase& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		LogDataBase_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, LogDataBase& s)
{
	if(strcmp(rElement.Value(), "LogDataBase") != 0)
	{
		LOG_CRI << "rElement is not LogDataBase!";
		return false;
	}
	return true;
}

bool ToXML(const LogDataBase& s, TiXmlElement& rElement)
{
	rElement.SetValue("LogDataBase");
	rElement.SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, LogDataBasePtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "LogDataBase") == 0)
	{
		LogDataBasePtr pStruct(new LogDataBase);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for LogDataBase";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "LogDataBase FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SDgnLog") == 0)
	{
		SDgnLogPtr pStruct(new SDgnLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SDgnLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SDgnLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRegisterLog") == 0)
	{
		SRegisterLogPtr pStruct(new SRegisterLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRegisterLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRegisterLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SLoginLog") == 0)
	{
		SLoginLogPtr pStruct(new SLoginLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SLoginLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SLoginLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SItemCoursesLog") == 0)
	{
		SItemCoursesLogPtr pStruct(new SItemCoursesLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SItemCoursesLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SItemCoursesLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SMoneyCoursesLog") == 0)
	{
		SMoneyCoursesLogPtr pStruct(new SMoneyCoursesLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SMoneyCoursesLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SMoneyCoursesLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SMailLog") == 0)
	{
		SMailLogPtr pStruct(new SMailLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SMailLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SMailLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SPetLog") == 0)
	{
		SPetLogPtr pStruct(new SPetLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SPetLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SPetLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SDujieLog") == 0)
	{
		SDujieLogPtr pStruct(new SDujieLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SDujieLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SDujieLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SFashionLog") == 0)
	{
		SFashionLogPtr pStruct(new SFashionLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SFashionLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SFashionLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SFighterLog") == 0)
	{
		SFighterLogPtr pStruct(new SFighterLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SFighterLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SFighterLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SHorseLog") == 0)
	{
		SHorseLogPtr pStruct(new SHorseLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SHorseLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SHorseLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "STrumpLog") == 0)
	{
		STrumpLogPtr pStruct(new STrumpLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for STrumpLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "STrumpLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SBeautyLog") == 0)
	{
		SBeautyLogPtr pStruct(new SBeautyLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SBeautyLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SBeautyLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEquipLog") == 0)
	{
		SEquipLogPtr pStruct(new SEquipLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEquipLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEquipLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGuildLog") == 0)
	{
		SGuildLogPtr pStruct(new SGuildLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGuildLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGuildLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SSendMoneyLog") == 0)
	{
		SSendMoneyLogPtr pStruct(new SSendMoneyLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SSendMoneyLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SSendMoneyLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SSendItemLog") == 0)
	{
		SSendItemLogPtr pStruct(new SSendItemLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SSendItemLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SSendItemLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SMailOpLog") == 0)
	{
		SMailOpLogPtr pStruct(new SMailOpLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SMailOpLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SMailOpLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SForbiddenLog") == 0)
	{
		SForbiddenLogPtr pStruct(new SForbiddenLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SForbiddenLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SForbiddenLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SForbiddenChatLog") == 0)
	{
		SForbiddenChatLogPtr pStruct(new SForbiddenChatLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SForbiddenChatLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SForbiddenChatLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGlobalSendItemLog") == 0)
	{
		SGlobalSendItemLogPtr pStruct(new SGlobalSendItemLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGlobalSendItemLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGlobalSendItemLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SQuesOptLog") == 0)
	{
		SQuesOptLogPtr pStruct(new SQuesOptLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SQuesOptLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SQuesOptLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SSendMailLog") == 0)
	{
		SSendMailLogPtr pStruct(new SSendMailLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SSendMailLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SSendMailLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SVIPSendLog") == 0)
	{
		SVIPSendLogPtr pStruct(new SVIPSendLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SVIPSendLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SVIPSendLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SActivityOpenLog") == 0)
	{
		SActivityOpenLogPtr pStruct(new SActivityOpenLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SActivityOpenLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SActivityOpenLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SDiscountItemLog") == 0)
	{
		SDiscountItemLogPtr pStruct(new SDiscountItemLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SDiscountItemLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SDiscountItemLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SLevelChangeLog") == 0)
	{
		SLevelChangeLogPtr pStruct(new SLevelChangeLog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SLevelChangeLog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SLevelChangeLog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else
	{
		LOG_CRI << "Invalid name: " << pszName << "!";
		return false;
	}
	return true;
}

bool SuperToXML(const LogDataBase& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_LogDataBase:
		return ToXML((LogDataBase&)s, rElement);
	case eType_SDgnLog:
		return ToXML((SDgnLog&)s, rElement);
	case eType_SRegisterLog:
		return ToXML((SRegisterLog&)s, rElement);
	case eType_SLoginLog:
		return ToXML((SLoginLog&)s, rElement);
	case eType_SItemCoursesLog:
		return ToXML((SItemCoursesLog&)s, rElement);
	case eType_SMoneyCoursesLog:
		return ToXML((SMoneyCoursesLog&)s, rElement);
	case eType_SMailLog:
		return ToXML((SMailLog&)s, rElement);
	case eType_SPetLog:
		return ToXML((SPetLog&)s, rElement);
	case eType_SDujieLog:
		return ToXML((SDujieLog&)s, rElement);
	case eType_SFashionLog:
		return ToXML((SFashionLog&)s, rElement);
	case eType_SFighterLog:
		return ToXML((SFighterLog&)s, rElement);
	case eType_SHorseLog:
		return ToXML((SHorseLog&)s, rElement);
	case eType_STrumpLog:
		return ToXML((STrumpLog&)s, rElement);
	case eType_SBeautyLog:
		return ToXML((SBeautyLog&)s, rElement);
	case eType_SEquipLog:
		return ToXML((SEquipLog&)s, rElement);
	case eType_SGuildLog:
		return ToXML((SGuildLog&)s, rElement);
	case eType_SSendMoneyLog:
		return ToXML((SSendMoneyLog&)s, rElement);
	case eType_SSendItemLog:
		return ToXML((SSendItemLog&)s, rElement);
	case eType_SMailOpLog:
		return ToXML((SMailOpLog&)s, rElement);
	case eType_SForbiddenLog:
		return ToXML((SForbiddenLog&)s, rElement);
	case eType_SForbiddenChatLog:
		return ToXML((SForbiddenChatLog&)s, rElement);
	case eType_SGlobalSendItemLog:
		return ToXML((SGlobalSendItemLog&)s, rElement);
	case eType_SQuesOptLog:
		return ToXML((SQuesOptLog&)s, rElement);
	case eType_SSendMailLog:
		return ToXML((SSendMailLog&)s, rElement);
	case eType_SVIPSendLog:
		return ToXML((SVIPSendLog&)s, rElement);
	case eType_SActivityOpenLog:
		return ToXML((SActivityOpenLog&)s, rElement);
	case eType_SDiscountItemLog:
		return ToXML((SDiscountItemLog&)s, rElement);
	case eType_SLevelChangeLog:
		return ToXML((SLevelChangeLog&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecLogDataBase& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		LogDataBasePtr p;
		if(!SuperFromXML(*pElemMember, p))
		{
			LOG_CRI << "SuperFromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecLogDataBase& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("LogDataBase"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!SuperToXML(*vec[i], *pElemMember))
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

SDgnLog::SDgnLog() : eOpType((EDgnOpType)0), wDgnType(0), qwDgnInsID(0), qwUserID(0) { }

CInArchive& operator>>(CInArchive& src, SDgnLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> (UINT8&)s.eOpType;
	src >> s.wDgnType;
	src >> s.qwDgnInsID;
	src >> s.qwUserID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDgnLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << (UINT8&)s.eOpType;
	src << s.wDgnType;
	src << s.qwDgnInsID;
	src << s.qwUserID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecDgnLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SDgnLogPtr p(new SDgnLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecDgnLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDgnLog& s)
{
	if(strcmp(rElement.Value(), "SDgnLog") != 0)
	{
		LOG_CRI << "rElement is not SDgnLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eOpType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EDgnOpType") != 0)
	{
		LOG_CRI << "pElemChild is not EDgnOpType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eOpType") != 0)
	{
		LOG_CRI << "Attribute: name is not eOpType!";
		return false;
	}
	const char* pszVal_eOpType = pElemChild->Attribute("value");
	if(pszVal_eOpType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eOpType, s.eOpType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wDgnType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wDgnType") != 0)
	{
		LOG_CRI << "Attribute: name is not wDgnType!";
		return false;
	}
	const char* pszVal_wDgnType = pElemChild->Attribute("value");
	if(pszVal_wDgnType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wDgnType, s.wDgnType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwDgnInsID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwDgnInsID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwDgnInsID!";
		return false;
	}
	const char* pszVal_qwDgnInsID = pElemChild->Attribute("value");
	if(pszVal_qwDgnInsID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwDgnInsID, s.qwDgnInsID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserID!";
		return false;
	}
	const char* pszVal_qwUserID = pElemChild->Attribute("value");
	if(pszVal_qwUserID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserID, s.qwUserID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDgnLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDgnLog");
	rElement.SetAttribute("type", ToUTF8Ptr("副本日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_eOpType(new TiXmlElement("EDgnOpType"));
	if(pElem_eOpType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eOpType->SetAttribute("name", "eOpType");
	const char* pszEnum_eOpType = EnumValToStr(s.eOpType);
	if(pszEnum_eOpType == NULL)
	{
		LOG_CRI << "EnumValToStr for EDgnOpType fails!";
		return false;
	}
	pElem_eOpType->SetAttribute("value", pszEnum_eOpType);
	pElem_eOpType->SetAttribute("comment", ToUTF8Ptr("操作类型"));
	if(rElement.LinkEndChild(pElem_eOpType.get()) != NULL)
		pElem_eOpType.release();
	unique_ptr<TiXmlElement> pElem_wDgnType(new TiXmlElement("UINT16"));
	if(pElem_wDgnType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wDgnType->SetAttribute("name", "wDgnType");
	pElem_wDgnType->SetAttribute("value", NumberToString(s.wDgnType).c_str());
	pElem_wDgnType->SetAttribute("comment", ToUTF8Ptr("副本类型"));
	if(rElement.LinkEndChild(pElem_wDgnType.get()) != NULL)
		pElem_wDgnType.release();
	unique_ptr<TiXmlElement> pElem_qwDgnInsID(new TiXmlElement("UINT64"));
	if(pElem_qwDgnInsID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwDgnInsID->SetAttribute("name", "qwDgnInsID");
	pElem_qwDgnInsID->SetAttribute("value", NumberToString(s.qwDgnInsID).c_str());
	pElem_qwDgnInsID->SetAttribute("comment", ToUTF8Ptr("副本实例ID"));
	if(rElement.LinkEndChild(pElem_qwDgnInsID.get()) != NULL)
		pElem_qwDgnInsID.release();
	unique_ptr<TiXmlElement> pElem_qwUserID(new TiXmlElement("UINT64"));
	if(pElem_qwUserID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserID->SetAttribute("name", "qwUserID");
	pElem_qwUserID->SetAttribute("value", NumberToString(s.qwUserID).c_str());
	pElem_qwUserID->SetAttribute("comment", ToUTF8Ptr("操作者，0表示系统"));
	if(rElement.LinkEndChild(pElem_qwUserID.get()) != NULL)
		pElem_qwUserID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDgnLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDgnLogPtr p(new SDgnLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecDgnLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDgnLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SRegisterLog::SRegisterLog() : serverId(0), playerId(0) { }

SRegisterLog::SRegisterLog(SRegisterLog&& src) : LogDataBase(src), serverId(src.serverId), playerId(src.playerId), playerName(move(src.playerName)) { }

SRegisterLog& SRegisterLog::operator=(SRegisterLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SRegisterLog();
		new (this) SRegisterLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRegisterLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.serverId;
	src >> s.playerId;
	src >> s.playerName;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRegisterLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.serverId;
	src << s.playerId;
	src << s.playerName;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecRegisterLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SRegisterLogPtr p(new SRegisterLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecRegisterLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRegisterLog& s)
{
	if(strcmp(rElement.Value(), "SRegisterLog") != 0)
	{
		LOG_CRI << "rElement is not SRegisterLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for serverId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "serverId") != 0)
	{
		LOG_CRI << "Attribute: name is not serverId!";
		return false;
	}
	const char* pszVal_serverId = pElemChild->Attribute("value");
	if(pszVal_serverId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_serverId, s.serverId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for playerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "playerId") != 0)
	{
		LOG_CRI << "Attribute: name is not playerId!";
		return false;
	}
	const char* pszVal_playerId = pElemChild->Attribute("value");
	if(pszVal_playerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_playerId, s.playerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for playerName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "playerName") != 0)
	{
		LOG_CRI << "Attribute: name is not playerName!";
		return false;
	}
	const char* pszVal_playerName = pElemChild->Attribute("value");
	if(pszVal_playerName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.playerName = pszVal_playerName;
	return true;
}

bool ToXML(const SRegisterLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRegisterLog");
	rElement.SetAttribute("type", ToUTF8Ptr("注册日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_serverId(new TiXmlElement("UINT32"));
	if(pElem_serverId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_serverId->SetAttribute("name", "serverId");
	pElem_serverId->SetAttribute("value", NumberToString(s.serverId).c_str());
	pElem_serverId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_serverId.get()) != NULL)
		pElem_serverId.release();
	unique_ptr<TiXmlElement> pElem_playerId(new TiXmlElement("UINT64"));
	if(pElem_playerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_playerId->SetAttribute("name", "playerId");
	pElem_playerId->SetAttribute("value", NumberToString(s.playerId).c_str());
	pElem_playerId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_playerId.get()) != NULL)
		pElem_playerId.release();
	unique_ptr<TiXmlElement> pElem_playerName(new TiXmlElement("string"));
	if(pElem_playerName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_playerName->SetAttribute("name", "playerName");
	pElem_playerName->SetAttribute("value", s.playerName.c_str());
	pElem_playerName->SetAttribute("comment", ToUTF8Ptr("玩家名字"));
	if(rElement.LinkEndChild(pElem_playerName.get()) != NULL)
		pElem_playerName.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRegisterLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRegisterLogPtr p(new SRegisterLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRegisterLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRegisterLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SLoginLog::SLoginLog() : serverId(0), playerId(0), loginTime(0), logoutTime(0) { }

SLoginLog::SLoginLog(SLoginLog&& src) : LogDataBase(src), serverId(src.serverId), playerId(src.playerId), loginTime(src.loginTime), loginIp(move(src.loginIp)), logoutTime(src.logoutTime) { }

SLoginLog& SLoginLog::operator=(SLoginLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SLoginLog();
		new (this) SLoginLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SLoginLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.serverId;
	src >> s.playerId;
	src >> s.loginTime;
	src >> s.loginIp;
	src >> s.logoutTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SLoginLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.serverId;
	src << s.playerId;
	src << s.loginTime;
	src << s.loginIp;
	src << s.logoutTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecLoginLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SLoginLogPtr p(new SLoginLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecLoginLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SLoginLog& s)
{
	if(strcmp(rElement.Value(), "SLoginLog") != 0)
	{
		LOG_CRI << "rElement is not SLoginLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for serverId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "serverId") != 0)
	{
		LOG_CRI << "Attribute: name is not serverId!";
		return false;
	}
	const char* pszVal_serverId = pElemChild->Attribute("value");
	if(pszVal_serverId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_serverId, s.serverId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for playerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "playerId") != 0)
	{
		LOG_CRI << "Attribute: name is not playerId!";
		return false;
	}
	const char* pszVal_playerId = pElemChild->Attribute("value");
	if(pszVal_playerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_playerId, s.playerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for loginTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "loginTime") != 0)
	{
		LOG_CRI << "Attribute: name is not loginTime!";
		return false;
	}
	const char* pszVal_loginTime = pElemChild->Attribute("value");
	if(pszVal_loginTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_loginTime, s.loginTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for loginIp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "loginIp") != 0)
	{
		LOG_CRI << "Attribute: name is not loginIp!";
		return false;
	}
	const char* pszVal_loginIp = pElemChild->Attribute("value");
	if(pszVal_loginIp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.loginIp = pszVal_loginIp;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for logoutTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "logoutTime") != 0)
	{
		LOG_CRI << "Attribute: name is not logoutTime!";
		return false;
	}
	const char* pszVal_logoutTime = pElemChild->Attribute("value");
	if(pszVal_logoutTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_logoutTime, s.logoutTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SLoginLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SLoginLog");
	rElement.SetAttribute("type", ToUTF8Ptr("登录日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_serverId(new TiXmlElement("UINT32"));
	if(pElem_serverId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_serverId->SetAttribute("name", "serverId");
	pElem_serverId->SetAttribute("value", NumberToString(s.serverId).c_str());
	pElem_serverId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_serverId.get()) != NULL)
		pElem_serverId.release();
	unique_ptr<TiXmlElement> pElem_playerId(new TiXmlElement("UINT64"));
	if(pElem_playerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_playerId->SetAttribute("name", "playerId");
	pElem_playerId->SetAttribute("value", NumberToString(s.playerId).c_str());
	pElem_playerId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_playerId.get()) != NULL)
		pElem_playerId.release();
	unique_ptr<TiXmlElement> pElem_loginTime(new TiXmlElement("UINT32"));
	if(pElem_loginTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_loginTime->SetAttribute("name", "loginTime");
	pElem_loginTime->SetAttribute("value", NumberToString(s.loginTime).c_str());
	pElem_loginTime->SetAttribute("comment", ToUTF8Ptr("登录时间"));
	if(rElement.LinkEndChild(pElem_loginTime.get()) != NULL)
		pElem_loginTime.release();
	unique_ptr<TiXmlElement> pElem_loginIp(new TiXmlElement("string"));
	if(pElem_loginIp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_loginIp->SetAttribute("name", "loginIp");
	pElem_loginIp->SetAttribute("value", s.loginIp.c_str());
	pElem_loginIp->SetAttribute("comment", ToUTF8Ptr("登录IP"));
	if(rElement.LinkEndChild(pElem_loginIp.get()) != NULL)
		pElem_loginIp.release();
	unique_ptr<TiXmlElement> pElem_logoutTime(new TiXmlElement("UINT32"));
	if(pElem_logoutTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_logoutTime->SetAttribute("name", "logoutTime");
	pElem_logoutTime->SetAttribute("value", NumberToString(s.logoutTime).c_str());
	pElem_logoutTime->SetAttribute("comment", ToUTF8Ptr("离开时间"));
	if(rElement.LinkEndChild(pElem_logoutTime.get()) != NULL)
		pElem_logoutTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecLoginLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SLoginLogPtr p(new SLoginLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecLoginLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SLoginLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SItemCoursesLog::SItemCoursesLog() : serverId(0), playerId(0), qwInstId(0), itemId(0), itemNum(0), 
			fromto(0), happenedTime(0) { }

SItemCoursesLog::SItemCoursesLog(SItemCoursesLog&& src) : LogDataBase(src), serverId(src.serverId), playerId(src.playerId), strOpenId(move(src.strOpenId)), qwInstId(src.qwInstId), itemId(src.itemId), 
			itemNum(src.itemNum), fromto(src.fromto), fromtoStr(move(src.fromtoStr)), happenedTime(src.happenedTime) { }

SItemCoursesLog& SItemCoursesLog::operator=(SItemCoursesLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SItemCoursesLog();
		new (this) SItemCoursesLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SItemCoursesLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.serverId;
	src >> s.playerId;
	src >> s.strOpenId;
	src >> s.qwInstId;
	src >> s.itemId;
	src >> s.itemNum;
	src >> s.fromto;
	src >> s.fromtoStr;
	src >> s.happenedTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SItemCoursesLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.serverId;
	src << s.playerId;
	src << s.strOpenId;
	src << s.qwInstId;
	src << s.itemId;
	src << s.itemNum;
	src << s.fromto;
	src << s.fromtoStr;
	src << s.happenedTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecItemCoursesLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SItemCoursesLogPtr p(new SItemCoursesLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecItemCoursesLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SItemCoursesLog& s)
{
	if(strcmp(rElement.Value(), "SItemCoursesLog") != 0)
	{
		LOG_CRI << "rElement is not SItemCoursesLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for serverId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "serverId") != 0)
	{
		LOG_CRI << "Attribute: name is not serverId!";
		return false;
	}
	const char* pszVal_serverId = pElemChild->Attribute("value");
	if(pszVal_serverId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_serverId, s.serverId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for playerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "playerId") != 0)
	{
		LOG_CRI << "Attribute: name is not playerId!";
		return false;
	}
	const char* pszVal_playerId = pElemChild->Attribute("value");
	if(pszVal_playerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_playerId, s.playerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strOpenId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strOpenId") != 0)
	{
		LOG_CRI << "Attribute: name is not strOpenId!";
		return false;
	}
	const char* pszVal_strOpenId = pElemChild->Attribute("value");
	if(pszVal_strOpenId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strOpenId = pszVal_strOpenId;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstId!";
		return false;
	}
	const char* pszVal_qwInstId = pElemChild->Attribute("value");
	if(pszVal_qwInstId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstId, s.qwInstId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for itemId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "itemId") != 0)
	{
		LOG_CRI << "Attribute: name is not itemId!";
		return false;
	}
	const char* pszVal_itemId = pElemChild->Attribute("value");
	if(pszVal_itemId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_itemId, s.itemId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for itemNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "itemNum") != 0)
	{
		LOG_CRI << "Attribute: name is not itemNum!";
		return false;
	}
	const char* pszVal_itemNum = pElemChild->Attribute("value");
	if(pszVal_itemNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_itemNum, s.itemNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fromto is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fromto") != 0)
	{
		LOG_CRI << "Attribute: name is not fromto!";
		return false;
	}
	const char* pszVal_fromto = pElemChild->Attribute("value");
	if(pszVal_fromto == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fromto, s.fromto))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fromtoStr is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fromtoStr") != 0)
	{
		LOG_CRI << "Attribute: name is not fromtoStr!";
		return false;
	}
	const char* pszVal_fromtoStr = pElemChild->Attribute("value");
	if(pszVal_fromtoStr == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.fromtoStr = pszVal_fromtoStr;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for happenedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "happenedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not happenedTime!";
		return false;
	}
	const char* pszVal_happenedTime = pElemChild->Attribute("value");
	if(pszVal_happenedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_happenedTime, s.happenedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SItemCoursesLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SItemCoursesLog");
	rElement.SetAttribute("type", ToUTF8Ptr("道具流水日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_serverId(new TiXmlElement("UINT32"));
	if(pElem_serverId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_serverId->SetAttribute("name", "serverId");
	pElem_serverId->SetAttribute("value", NumberToString(s.serverId).c_str());
	pElem_serverId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_serverId.get()) != NULL)
		pElem_serverId.release();
	unique_ptr<TiXmlElement> pElem_playerId(new TiXmlElement("UINT64"));
	if(pElem_playerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_playerId->SetAttribute("name", "playerId");
	pElem_playerId->SetAttribute("value", NumberToString(s.playerId).c_str());
	pElem_playerId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_playerId.get()) != NULL)
		pElem_playerId.release();
	unique_ptr<TiXmlElement> pElem_strOpenId(new TiXmlElement("string"));
	if(pElem_strOpenId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strOpenId->SetAttribute("name", "strOpenId");
	pElem_strOpenId->SetAttribute("value", s.strOpenId.c_str());
	pElem_strOpenId->SetAttribute("comment", ToUTF8Ptr("玩家的openId"));
	if(rElement.LinkEndChild(pElem_strOpenId.get()) != NULL)
		pElem_strOpenId.release();
	unique_ptr<TiXmlElement> pElem_qwInstId(new TiXmlElement("UINT64"));
	if(pElem_qwInstId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstId->SetAttribute("name", "qwInstId");
	pElem_qwInstId->SetAttribute("value", NumberToString(s.qwInstId).c_str());
	pElem_qwInstId->SetAttribute("comment", ToUTF8Ptr("物品流水ID"));
	if(rElement.LinkEndChild(pElem_qwInstId.get()) != NULL)
		pElem_qwInstId.release();
	unique_ptr<TiXmlElement> pElem_itemId(new TiXmlElement("UINT32"));
	if(pElem_itemId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_itemId->SetAttribute("name", "itemId");
	pElem_itemId->SetAttribute("value", NumberToString(s.itemId).c_str());
	pElem_itemId->SetAttribute("comment", ToUTF8Ptr("物品ID"));
	if(rElement.LinkEndChild(pElem_itemId.get()) != NULL)
		pElem_itemId.release();
	unique_ptr<TiXmlElement> pElem_itemNum(new TiXmlElement("UINT32"));
	if(pElem_itemNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_itemNum->SetAttribute("name", "itemNum");
	pElem_itemNum->SetAttribute("value", NumberToString(s.itemNum).c_str());
	pElem_itemNum->SetAttribute("comment", ToUTF8Ptr("物品使用or增加数量"));
	if(rElement.LinkEndChild(pElem_itemNum.get()) != NULL)
		pElem_itemNum.release();
	unique_ptr<TiXmlElement> pElem_fromto(new TiXmlElement("UINT16"));
	if(pElem_fromto == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fromto->SetAttribute("name", "fromto");
	pElem_fromto->SetAttribute("value", NumberToString(s.fromto).c_str());
	pElem_fromto->SetAttribute("comment", ToUTF8Ptr("物品出处id"));
	if(rElement.LinkEndChild(pElem_fromto.get()) != NULL)
		pElem_fromto.release();
	unique_ptr<TiXmlElement> pElem_fromtoStr(new TiXmlElement("string"));
	if(pElem_fromtoStr == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fromtoStr->SetAttribute("name", "fromtoStr");
	pElem_fromtoStr->SetAttribute("value", s.fromtoStr.c_str());
	pElem_fromtoStr->SetAttribute("comment", ToUTF8Ptr("物品出处字符描述"));
	if(rElement.LinkEndChild(pElem_fromtoStr.get()) != NULL)
		pElem_fromtoStr.release();
	unique_ptr<TiXmlElement> pElem_happenedTime(new TiXmlElement("UINT32"));
	if(pElem_happenedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_happenedTime->SetAttribute("name", "happenedTime");
	pElem_happenedTime->SetAttribute("value", NumberToString(s.happenedTime).c_str());
	pElem_happenedTime->SetAttribute("comment", ToUTF8Ptr("时间"));
	if(rElement.LinkEndChild(pElem_happenedTime.get()) != NULL)
		pElem_happenedTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecItemCoursesLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SItemCoursesLogPtr p(new SItemCoursesLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecItemCoursesLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SItemCoursesLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SMoneyCoursesLog::SMoneyCoursesLog() : serverId(0), playerId(0), moneyType(0), moneyNum(0), totalNum(0), 
			fromto(0), happenedTime(0), bIsFreeGold(0) { }

SMoneyCoursesLog::SMoneyCoursesLog(SMoneyCoursesLog&& src) : LogDataBase(src), serverId(src.serverId), playerId(src.playerId), strOpenId(move(src.strOpenId)), moneyType(src.moneyType), moneyNum(src.moneyNum), 
			totalNum(src.totalNum), fromto(src.fromto), fromtoStr(move(src.fromtoStr)), happenedTime(src.happenedTime), bIsFreeGold(src.bIsFreeGold) { }

SMoneyCoursesLog& SMoneyCoursesLog::operator=(SMoneyCoursesLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SMoneyCoursesLog();
		new (this) SMoneyCoursesLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SMoneyCoursesLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.serverId;
	src >> s.playerId;
	src >> s.strOpenId;
	src >> s.moneyType;
	src >> s.moneyNum;
	src >> s.totalNum;
	src >> s.fromto;
	src >> s.fromtoStr;
	src >> s.happenedTime;
	src >> s.bIsFreeGold;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMoneyCoursesLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.serverId;
	src << s.playerId;
	src << s.strOpenId;
	src << s.moneyType;
	src << s.moneyNum;
	src << s.totalNum;
	src << s.fromto;
	src << s.fromtoStr;
	src << s.happenedTime;
	src << s.bIsFreeGold;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecMoneyCoursesLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SMoneyCoursesLogPtr p(new SMoneyCoursesLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecMoneyCoursesLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMoneyCoursesLog& s)
{
	if(strcmp(rElement.Value(), "SMoneyCoursesLog") != 0)
	{
		LOG_CRI << "rElement is not SMoneyCoursesLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for serverId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "serverId") != 0)
	{
		LOG_CRI << "Attribute: name is not serverId!";
		return false;
	}
	const char* pszVal_serverId = pElemChild->Attribute("value");
	if(pszVal_serverId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_serverId, s.serverId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for playerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "playerId") != 0)
	{
		LOG_CRI << "Attribute: name is not playerId!";
		return false;
	}
	const char* pszVal_playerId = pElemChild->Attribute("value");
	if(pszVal_playerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_playerId, s.playerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strOpenId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strOpenId") != 0)
	{
		LOG_CRI << "Attribute: name is not strOpenId!";
		return false;
	}
	const char* pszVal_strOpenId = pElemChild->Attribute("value");
	if(pszVal_strOpenId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strOpenId = pszVal_strOpenId;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for moneyType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "moneyType") != 0)
	{
		LOG_CRI << "Attribute: name is not moneyType!";
		return false;
	}
	const char* pszVal_moneyType = pElemChild->Attribute("value");
	if(pszVal_moneyType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_moneyType, s.moneyType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for moneyNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "moneyNum") != 0)
	{
		LOG_CRI << "Attribute: name is not moneyNum!";
		return false;
	}
	const char* pszVal_moneyNum = pElemChild->Attribute("value");
	if(pszVal_moneyNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_moneyNum, s.moneyNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for totalNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "totalNum") != 0)
	{
		LOG_CRI << "Attribute: name is not totalNum!";
		return false;
	}
	const char* pszVal_totalNum = pElemChild->Attribute("value");
	if(pszVal_totalNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_totalNum, s.totalNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fromto is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fromto") != 0)
	{
		LOG_CRI << "Attribute: name is not fromto!";
		return false;
	}
	const char* pszVal_fromto = pElemChild->Attribute("value");
	if(pszVal_fromto == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fromto, s.fromto))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fromtoStr is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fromtoStr") != 0)
	{
		LOG_CRI << "Attribute: name is not fromtoStr!";
		return false;
	}
	const char* pszVal_fromtoStr = pElemChild->Attribute("value");
	if(pszVal_fromtoStr == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.fromtoStr = pszVal_fromtoStr;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for happenedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "happenedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not happenedTime!";
		return false;
	}
	const char* pszVal_happenedTime = pElemChild->Attribute("value");
	if(pszVal_happenedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_happenedTime, s.happenedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bIsFreeGold is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bIsFreeGold") != 0)
	{
		LOG_CRI << "Attribute: name is not bIsFreeGold!";
		return false;
	}
	const char* pszVal_bIsFreeGold = pElemChild->Attribute("value");
	if(pszVal_bIsFreeGold == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bIsFreeGold, s.bIsFreeGold))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SMoneyCoursesLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMoneyCoursesLog");
	rElement.SetAttribute("type", ToUTF8Ptr("货币流水日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_serverId(new TiXmlElement("UINT32"));
	if(pElem_serverId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_serverId->SetAttribute("name", "serverId");
	pElem_serverId->SetAttribute("value", NumberToString(s.serverId).c_str());
	pElem_serverId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_serverId.get()) != NULL)
		pElem_serverId.release();
	unique_ptr<TiXmlElement> pElem_playerId(new TiXmlElement("UINT64"));
	if(pElem_playerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_playerId->SetAttribute("name", "playerId");
	pElem_playerId->SetAttribute("value", NumberToString(s.playerId).c_str());
	pElem_playerId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_playerId.get()) != NULL)
		pElem_playerId.release();
	unique_ptr<TiXmlElement> pElem_strOpenId(new TiXmlElement("string"));
	if(pElem_strOpenId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strOpenId->SetAttribute("name", "strOpenId");
	pElem_strOpenId->SetAttribute("value", s.strOpenId.c_str());
	pElem_strOpenId->SetAttribute("comment", ToUTF8Ptr("玩家的openId"));
	if(rElement.LinkEndChild(pElem_strOpenId.get()) != NULL)
		pElem_strOpenId.release();
	unique_ptr<TiXmlElement> pElem_moneyType(new TiXmlElement("UINT8"));
	if(pElem_moneyType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_moneyType->SetAttribute("name", "moneyType");
	pElem_moneyType->SetAttribute("value", NumberToString(s.moneyType).c_str());
	pElem_moneyType->SetAttribute("comment", ToUTF8Ptr("货币类型ID"));
	if(rElement.LinkEndChild(pElem_moneyType.get()) != NULL)
		pElem_moneyType.release();
	unique_ptr<TiXmlElement> pElem_moneyNum(new TiXmlElement("UINT32"));
	if(pElem_moneyNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_moneyNum->SetAttribute("name", "moneyNum");
	pElem_moneyNum->SetAttribute("value", NumberToString(s.moneyNum).c_str());
	pElem_moneyNum->SetAttribute("comment", ToUTF8Ptr("货币使用or增加数量"));
	if(rElement.LinkEndChild(pElem_moneyNum.get()) != NULL)
		pElem_moneyNum.release();
	unique_ptr<TiXmlElement> pElem_totalNum(new TiXmlElement("UINT32"));
	if(pElem_totalNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_totalNum->SetAttribute("name", "totalNum");
	pElem_totalNum->SetAttribute("value", NumberToString(s.totalNum).c_str());
	pElem_totalNum->SetAttribute("comment", ToUTF8Ptr("当前货币总数量"));
	if(rElement.LinkEndChild(pElem_totalNum.get()) != NULL)
		pElem_totalNum.release();
	unique_ptr<TiXmlElement> pElem_fromto(new TiXmlElement("UINT16"));
	if(pElem_fromto == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fromto->SetAttribute("name", "fromto");
	pElem_fromto->SetAttribute("value", NumberToString(s.fromto).c_str());
	pElem_fromto->SetAttribute("comment", ToUTF8Ptr("物品出处id"));
	if(rElement.LinkEndChild(pElem_fromto.get()) != NULL)
		pElem_fromto.release();
	unique_ptr<TiXmlElement> pElem_fromtoStr(new TiXmlElement("string"));
	if(pElem_fromtoStr == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fromtoStr->SetAttribute("name", "fromtoStr");
	pElem_fromtoStr->SetAttribute("value", s.fromtoStr.c_str());
	pElem_fromtoStr->SetAttribute("comment", ToUTF8Ptr("物品出处字符描述"));
	if(rElement.LinkEndChild(pElem_fromtoStr.get()) != NULL)
		pElem_fromtoStr.release();
	unique_ptr<TiXmlElement> pElem_happenedTime(new TiXmlElement("UINT32"));
	if(pElem_happenedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_happenedTime->SetAttribute("name", "happenedTime");
	pElem_happenedTime->SetAttribute("value", NumberToString(s.happenedTime).c_str());
	pElem_happenedTime->SetAttribute("comment", ToUTF8Ptr("时间"));
	if(rElement.LinkEndChild(pElem_happenedTime.get()) != NULL)
		pElem_happenedTime.release();
	unique_ptr<TiXmlElement> pElem_bIsFreeGold(new TiXmlElement("UINT8"));
	if(pElem_bIsFreeGold == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bIsFreeGold->SetAttribute("name", "bIsFreeGold");
	pElem_bIsFreeGold->SetAttribute("value", NumberToString(s.bIsFreeGold).c_str());
	pElem_bIsFreeGold->SetAttribute("comment", ToUTF8Ptr("是否使用免费仙石"));
	if(rElement.LinkEndChild(pElem_bIsFreeGold.get()) != NULL)
		pElem_bIsFreeGold.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMoneyCoursesLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMoneyCoursesLogPtr p(new SMoneyCoursesLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecMoneyCoursesLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMoneyCoursesLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SMailLog::SMailLog() : dwServerId(0), qwPlayerId(0), qwMailId(0), byType(0), byState(0), 
			dwRevTime(0), dwDelTime(0) { }

SMailLog::SMailLog(SMailLog&& src) : LogDataBase(src), dwServerId(src.dwServerId), qwPlayerId(src.qwPlayerId), qwMailId(src.qwMailId), byType(src.byType), strTitle(move(src.strTitle)), 
			strText(move(src.strText)), strAttach(move(src.strAttach)), byState(src.byState), dwRevTime(src.dwRevTime), dwDelTime(src.dwDelTime) { }

SMailLog& SMailLog::operator=(SMailLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SMailLog();
		new (this) SMailLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SMailLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.dwServerId;
	src >> s.qwPlayerId;
	src >> s.qwMailId;
	src >> s.byType;
	src >> s.strTitle;
	src >> s.strText;
	src >> s.strAttach;
	src >> s.byState;
	src >> s.dwRevTime;
	src >> s.dwDelTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMailLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.dwServerId;
	src << s.qwPlayerId;
	src << s.qwMailId;
	src << s.byType;
	src << s.strTitle;
	src << s.strText;
	src << s.strAttach;
	src << s.byState;
	src << s.dwRevTime;
	src << s.dwDelTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecMailLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SMailLogPtr p(new SMailLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecMailLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMailLog& s)
{
	if(strcmp(rElement.Value(), "SMailLog") != 0)
	{
		LOG_CRI << "rElement is not SMailLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwPlayerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwPlayerId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwPlayerId!";
		return false;
	}
	const char* pszVal_qwPlayerId = pElemChild->Attribute("value");
	if(pszVal_qwPlayerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwPlayerId, s.qwPlayerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwMailId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwMailId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwMailId!";
		return false;
	}
	const char* pszVal_qwMailId = pElemChild->Attribute("value");
	if(pszVal_qwMailId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwMailId, s.qwMailId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byType") != 0)
	{
		LOG_CRI << "Attribute: name is not byType!";
		return false;
	}
	const char* pszVal_byType = pElemChild->Attribute("value");
	if(pszVal_byType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byType, s.byType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not strTitle!";
		return false;
	}
	const char* pszVal_strTitle = pElemChild->Attribute("value");
	if(pszVal_strTitle == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strTitle = pszVal_strTitle;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strText is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strText") != 0)
	{
		LOG_CRI << "Attribute: name is not strText!";
		return false;
	}
	const char* pszVal_strText = pElemChild->Attribute("value");
	if(pszVal_strText == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strText = pszVal_strText;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strAttach is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strAttach") != 0)
	{
		LOG_CRI << "Attribute: name is not strAttach!";
		return false;
	}
	const char* pszVal_strAttach = pElemChild->Attribute("value");
	if(pszVal_strAttach == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strAttach = pszVal_strAttach;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byState") != 0)
	{
		LOG_CRI << "Attribute: name is not byState!";
		return false;
	}
	const char* pszVal_byState = pElemChild->Attribute("value");
	if(pszVal_byState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byState, s.byState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRevTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRevTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRevTime!";
		return false;
	}
	const char* pszVal_dwRevTime = pElemChild->Attribute("value");
	if(pszVal_dwRevTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRevTime, s.dwRevTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDelTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDelTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDelTime!";
		return false;
	}
	const char* pszVal_dwDelTime = pElemChild->Attribute("value");
	if(pszVal_dwDelTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDelTime, s.dwDelTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SMailLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMailLog");
	rElement.SetAttribute("type", ToUTF8Ptr("邮件流水日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwPlayerId(new TiXmlElement("UINT64"));
	if(pElem_qwPlayerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwPlayerId->SetAttribute("name", "qwPlayerId");
	pElem_qwPlayerId->SetAttribute("value", NumberToString(s.qwPlayerId).c_str());
	pElem_qwPlayerId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwPlayerId.get()) != NULL)
		pElem_qwPlayerId.release();
	unique_ptr<TiXmlElement> pElem_qwMailId(new TiXmlElement("UINT64"));
	if(pElem_qwMailId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwMailId->SetAttribute("name", "qwMailId");
	pElem_qwMailId->SetAttribute("value", NumberToString(s.qwMailId).c_str());
	pElem_qwMailId->SetAttribute("comment", ToUTF8Ptr("邮件ID"));
	if(rElement.LinkEndChild(pElem_qwMailId.get()) != NULL)
		pElem_qwMailId.release();
	unique_ptr<TiXmlElement> pElem_byType(new TiXmlElement("UINT8"));
	if(pElem_byType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byType->SetAttribute("name", "byType");
	pElem_byType->SetAttribute("value", NumberToString(s.byType).c_str());
	pElem_byType->SetAttribute("comment", ToUTF8Ptr("邮件类型"));
	if(rElement.LinkEndChild(pElem_byType.get()) != NULL)
		pElem_byType.release();
	unique_ptr<TiXmlElement> pElem_strTitle(new TiXmlElement("string"));
	if(pElem_strTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strTitle->SetAttribute("name", "strTitle");
	pElem_strTitle->SetAttribute("value", s.strTitle.c_str());
	pElem_strTitle->SetAttribute("comment", ToUTF8Ptr("邮件标题"));
	if(rElement.LinkEndChild(pElem_strTitle.get()) != NULL)
		pElem_strTitle.release();
	unique_ptr<TiXmlElement> pElem_strText(new TiXmlElement("string"));
	if(pElem_strText == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strText->SetAttribute("name", "strText");
	pElem_strText->SetAttribute("value", s.strText.c_str());
	pElem_strText->SetAttribute("comment", ToUTF8Ptr("邮件正文"));
	if(rElement.LinkEndChild(pElem_strText.get()) != NULL)
		pElem_strText.release();
	unique_ptr<TiXmlElement> pElem_strAttach(new TiXmlElement("string"));
	if(pElem_strAttach == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strAttach->SetAttribute("name", "strAttach");
	pElem_strAttach->SetAttribute("value", s.strAttach.c_str());
	pElem_strAttach->SetAttribute("comment", ToUTF8Ptr("邮件附件"));
	if(rElement.LinkEndChild(pElem_strAttach.get()) != NULL)
		pElem_strAttach.release();
	unique_ptr<TiXmlElement> pElem_byState(new TiXmlElement("UINT8"));
	if(pElem_byState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byState->SetAttribute("name", "byState");
	pElem_byState->SetAttribute("value", NumberToString(s.byState).c_str());
	pElem_byState->SetAttribute("comment", ToUTF8Ptr("邮件状态"));
	if(rElement.LinkEndChild(pElem_byState.get()) != NULL)
		pElem_byState.release();
	unique_ptr<TiXmlElement> pElem_dwRevTime(new TiXmlElement("UINT32"));
	if(pElem_dwRevTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRevTime->SetAttribute("name", "dwRevTime");
	pElem_dwRevTime->SetAttribute("value", NumberToString(s.dwRevTime).c_str());
	pElem_dwRevTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwRevTime.get()) != NULL)
		pElem_dwRevTime.release();
	unique_ptr<TiXmlElement> pElem_dwDelTime(new TiXmlElement("UINT32"));
	if(pElem_dwDelTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDelTime->SetAttribute("name", "dwDelTime");
	pElem_dwDelTime->SetAttribute("value", NumberToString(s.dwDelTime).c_str());
	pElem_dwDelTime->SetAttribute("comment", ToUTF8Ptr("删除时间"));
	if(rElement.LinkEndChild(pElem_dwDelTime.get()) != NULL)
		pElem_dwDelTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMailLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMailLogPtr p(new SMailLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecMailLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMailLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SPetLog::SPetLog() : dwServerId(0), qwPlayerId(0), byOpType(0), wLevel(0), happenedTime(0) { }

SPetLog::SPetLog(SPetLog&& src) : LogDataBase(src), dwServerId(src.dwServerId), qwPlayerId(src.qwPlayerId), sName(move(src.sName)), byOpType(src.byOpType), wLevel(src.wLevel), 
			happenedTime(src.happenedTime) { }

SPetLog& SPetLog::operator=(SPetLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SPetLog();
		new (this) SPetLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPetLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.dwServerId;
	src >> s.qwPlayerId;
	src >> s.sName;
	src >> s.byOpType;
	src >> s.wLevel;
	src >> s.happenedTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPetLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.dwServerId;
	src << s.qwPlayerId;
	src << s.sName;
	src << s.byOpType;
	src << s.wLevel;
	src << s.happenedTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecPetLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SPetLogPtr p(new SPetLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecPetLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPetLog& s)
{
	if(strcmp(rElement.Value(), "SPetLog") != 0)
	{
		LOG_CRI << "rElement is not SPetLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwPlayerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwPlayerId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwPlayerId!";
		return false;
	}
	const char* pszVal_qwPlayerId = pElemChild->Attribute("value");
	if(pszVal_qwPlayerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwPlayerId, s.qwPlayerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sName") != 0)
	{
		LOG_CRI << "Attribute: name is not sName!";
		return false;
	}
	const char* pszVal_sName = pElemChild->Attribute("value");
	if(pszVal_sName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.sName = pszVal_sName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byOpType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byOpType") != 0)
	{
		LOG_CRI << "Attribute: name is not byOpType!";
		return false;
	}
	const char* pszVal_byOpType = pElemChild->Attribute("value");
	if(pszVal_byOpType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byOpType, s.byOpType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not wLevel!";
		return false;
	}
	const char* pszVal_wLevel = pElemChild->Attribute("value");
	if(pszVal_wLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wLevel, s.wLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for happenedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "happenedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not happenedTime!";
		return false;
	}
	const char* pszVal_happenedTime = pElemChild->Attribute("value");
	if(pszVal_happenedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_happenedTime, s.happenedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPetLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPetLog");
	rElement.SetAttribute("type", ToUTF8Ptr("阵灵日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwPlayerId(new TiXmlElement("UINT64"));
	if(pElem_qwPlayerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwPlayerId->SetAttribute("name", "qwPlayerId");
	pElem_qwPlayerId->SetAttribute("value", NumberToString(s.qwPlayerId).c_str());
	pElem_qwPlayerId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwPlayerId.get()) != NULL)
		pElem_qwPlayerId.release();
	unique_ptr<TiXmlElement> pElem_sName(new TiXmlElement("string"));
	if(pElem_sName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sName->SetAttribute("name", "sName");
	pElem_sName->SetAttribute("value", s.sName.c_str());
	pElem_sName->SetAttribute("comment", ToUTF8Ptr("阵灵名字"));
	if(rElement.LinkEndChild(pElem_sName.get()) != NULL)
		pElem_sName.release();
	unique_ptr<TiXmlElement> pElem_byOpType(new TiXmlElement("UINT8"));
	if(pElem_byOpType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byOpType->SetAttribute("name", "byOpType");
	pElem_byOpType->SetAttribute("value", NumberToString(s.byOpType).c_str());
	pElem_byOpType->SetAttribute("comment", ToUTF8Ptr("操作类型"));
	if(rElement.LinkEndChild(pElem_byOpType.get()) != NULL)
		pElem_byOpType.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("阵灵等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	unique_ptr<TiXmlElement> pElem_happenedTime(new TiXmlElement("UINT32"));
	if(pElem_happenedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_happenedTime->SetAttribute("name", "happenedTime");
	pElem_happenedTime->SetAttribute("value", NumberToString(s.happenedTime).c_str());
	pElem_happenedTime->SetAttribute("comment", ToUTF8Ptr("时间"));
	if(rElement.LinkEndChild(pElem_happenedTime.get()) != NULL)
		pElem_happenedTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPetLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPetLogPtr p(new SPetLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecPetLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPetLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SDujieLog::SDujieLog() : dwServerId(0), qwPlayerId(0), wFighterId(0), dwExp(0), happenedTime(0) { }

SDujieLog::SDujieLog(SDujieLog&& src) : LogDataBase(src), dwServerId(src.dwServerId), qwPlayerId(src.qwPlayerId), wFighterId(src.wFighterId), sFighterName(move(src.sFighterName)), sPeriodName(move(src.sPeriodName)), 
			dwExp(src.dwExp), happenedTime(src.happenedTime) { }

SDujieLog& SDujieLog::operator=(SDujieLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SDujieLog();
		new (this) SDujieLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SDujieLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.dwServerId;
	src >> s.qwPlayerId;
	src >> s.wFighterId;
	src >> s.sFighterName;
	src >> s.sPeriodName;
	src >> s.dwExp;
	src >> s.happenedTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDujieLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.dwServerId;
	src << s.qwPlayerId;
	src << s.wFighterId;
	src << s.sFighterName;
	src << s.sPeriodName;
	src << s.dwExp;
	src << s.happenedTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecDujieLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SDujieLogPtr p(new SDujieLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecDujieLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDujieLog& s)
{
	if(strcmp(rElement.Value(), "SDujieLog") != 0)
	{
		LOG_CRI << "rElement is not SDujieLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwPlayerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwPlayerId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwPlayerId!";
		return false;
	}
	const char* pszVal_qwPlayerId = pElemChild->Attribute("value");
	if(pszVal_qwPlayerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwPlayerId, s.qwPlayerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wFighterId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFighterId") != 0)
	{
		LOG_CRI << "Attribute: name is not wFighterId!";
		return false;
	}
	const char* pszVal_wFighterId = pElemChild->Attribute("value");
	if(pszVal_wFighterId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFighterId, s.wFighterId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sFighterName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sFighterName") != 0)
	{
		LOG_CRI << "Attribute: name is not sFighterName!";
		return false;
	}
	const char* pszVal_sFighterName = pElemChild->Attribute("value");
	if(pszVal_sFighterName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.sFighterName = pszVal_sFighterName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sPeriodName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sPeriodName") != 0)
	{
		LOG_CRI << "Attribute: name is not sPeriodName!";
		return false;
	}
	const char* pszVal_sPeriodName = pElemChild->Attribute("value");
	if(pszVal_sPeriodName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.sPeriodName = pszVal_sPeriodName;
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for happenedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "happenedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not happenedTime!";
		return false;
	}
	const char* pszVal_happenedTime = pElemChild->Attribute("value");
	if(pszVal_happenedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_happenedTime, s.happenedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDujieLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDujieLog");
	rElement.SetAttribute("type", ToUTF8Ptr("渡劫日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwPlayerId(new TiXmlElement("UINT64"));
	if(pElem_qwPlayerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwPlayerId->SetAttribute("name", "qwPlayerId");
	pElem_qwPlayerId->SetAttribute("value", NumberToString(s.qwPlayerId).c_str());
	pElem_qwPlayerId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwPlayerId.get()) != NULL)
		pElem_qwPlayerId.release();
	unique_ptr<TiXmlElement> pElem_wFighterId(new TiXmlElement("UINT16"));
	if(pElem_wFighterId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterId->SetAttribute("name", "wFighterId");
	pElem_wFighterId->SetAttribute("value", NumberToString(s.wFighterId).c_str());
	pElem_wFighterId->SetAttribute("comment", ToUTF8Ptr("散仙ID"));
	if(rElement.LinkEndChild(pElem_wFighterId.get()) != NULL)
		pElem_wFighterId.release();
	unique_ptr<TiXmlElement> pElem_sFighterName(new TiXmlElement("string"));
	if(pElem_sFighterName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sFighterName->SetAttribute("name", "sFighterName");
	pElem_sFighterName->SetAttribute("value", s.sFighterName.c_str());
	pElem_sFighterName->SetAttribute("comment", ToUTF8Ptr("散仙名字"));
	if(rElement.LinkEndChild(pElem_sFighterName.get()) != NULL)
		pElem_sFighterName.release();
	unique_ptr<TiXmlElement> pElem_sPeriodName(new TiXmlElement("string"));
	if(pElem_sPeriodName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sPeriodName->SetAttribute("name", "sPeriodName");
	pElem_sPeriodName->SetAttribute("value", s.sPeriodName.c_str());
	pElem_sPeriodName->SetAttribute("comment", ToUTF8Ptr("渡劫阶段"));
	if(rElement.LinkEndChild(pElem_sPeriodName.get()) != NULL)
		pElem_sPeriodName.release();
	unique_ptr<TiXmlElement> pElem_dwExp(new TiXmlElement("UINT32"));
	if(pElem_dwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExp->SetAttribute("name", "dwExp");
	pElem_dwExp->SetAttribute("value", NumberToString(s.dwExp).c_str());
	pElem_dwExp->SetAttribute("comment", ToUTF8Ptr("当前渡劫经验值"));
	if(rElement.LinkEndChild(pElem_dwExp.get()) != NULL)
		pElem_dwExp.release();
	unique_ptr<TiXmlElement> pElem_happenedTime(new TiXmlElement("UINT32"));
	if(pElem_happenedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_happenedTime->SetAttribute("name", "happenedTime");
	pElem_happenedTime->SetAttribute("value", NumberToString(s.happenedTime).c_str());
	pElem_happenedTime->SetAttribute("comment", ToUTF8Ptr("时间"));
	if(rElement.LinkEndChild(pElem_happenedTime.get()) != NULL)
		pElem_happenedTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDujieLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDujieLogPtr p(new SDujieLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecDujieLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDujieLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SFashionLog::SFashionLog() : dwServerId(0), qwUserId(0), wId(0), dwLevel(0), happenedTime(0) { }

SFashionLog::SFashionLog(SFashionLog&& src) : LogDataBase(src), dwServerId(src.dwServerId), qwUserId(src.qwUserId), wId(src.wId), sName(move(src.sName)), dwLevel(src.dwLevel), 
			happenedTime(src.happenedTime) { }

SFashionLog& SFashionLog::operator=(SFashionLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SFashionLog();
		new (this) SFashionLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SFashionLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.wId;
	src >> s.sName;
	src >> s.dwLevel;
	src >> s.happenedTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFashionLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.wId;
	src << s.sName;
	src << s.dwLevel;
	src << s.happenedTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecFashionLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SFashionLogPtr p(new SFashionLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecFashionLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFashionLog& s)
{
	if(strcmp(rElement.Value(), "SFashionLog") != 0)
	{
		LOG_CRI << "rElement is not SFashionLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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
		LOG_CRI << "pElemChild for sName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sName") != 0)
	{
		LOG_CRI << "Attribute: name is not sName!";
		return false;
	}
	const char* pszVal_sName = pElemChild->Attribute("value");
	if(pszVal_sName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.sName = pszVal_sName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLevel!";
		return false;
	}
	const char* pszVal_dwLevel = pElemChild->Attribute("value");
	if(pszVal_dwLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLevel, s.dwLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for happenedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "happenedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not happenedTime!";
		return false;
	}
	const char* pszVal_happenedTime = pElemChild->Attribute("value");
	if(pszVal_happenedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_happenedTime, s.happenedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFashionLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFashionLog");
	rElement.SetAttribute("type", ToUTF8Ptr("时装日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_wId(new TiXmlElement("UINT16"));
	if(pElem_wId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wId->SetAttribute("name", "wId");
	pElem_wId->SetAttribute("value", NumberToString(s.wId).c_str());
	pElem_wId->SetAttribute("comment", ToUTF8Ptr("时装ID"));
	if(rElement.LinkEndChild(pElem_wId.get()) != NULL)
		pElem_wId.release();
	unique_ptr<TiXmlElement> pElem_sName(new TiXmlElement("string"));
	if(pElem_sName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sName->SetAttribute("name", "sName");
	pElem_sName->SetAttribute("value", s.sName.c_str());
	pElem_sName->SetAttribute("comment", ToUTF8Ptr("时装名字"));
	if(rElement.LinkEndChild(pElem_sName.get()) != NULL)
		pElem_sName.release();
	unique_ptr<TiXmlElement> pElem_dwLevel(new TiXmlElement("UINT32"));
	if(pElem_dwLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLevel->SetAttribute("name", "dwLevel");
	pElem_dwLevel->SetAttribute("value", NumberToString(s.dwLevel).c_str());
	pElem_dwLevel->SetAttribute("comment", ToUTF8Ptr("时装等级"));
	if(rElement.LinkEndChild(pElem_dwLevel.get()) != NULL)
		pElem_dwLevel.release();
	unique_ptr<TiXmlElement> pElem_happenedTime(new TiXmlElement("UINT32"));
	if(pElem_happenedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_happenedTime->SetAttribute("name", "happenedTime");
	pElem_happenedTime->SetAttribute("value", NumberToString(s.happenedTime).c_str());
	pElem_happenedTime->SetAttribute("comment", ToUTF8Ptr("时间"));
	if(rElement.LinkEndChild(pElem_happenedTime.get()) != NULL)
		pElem_happenedTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFashionLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFashionLogPtr p(new SFashionLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecFashionLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFashionLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SFighterLog::SFighterLog() : dwServerId(0), qwUserId(0), wFighterId(0), wLevel(0), byQuality(0), 
			eOptType((EFighterOptType)0), dwType(0), qwResult(0), happenedTime(0) { }

SFighterLog::SFighterLog(SFighterLog&& src) : LogDataBase(src), dwServerId(src.dwServerId), qwUserId(src.qwUserId), wFighterId(src.wFighterId), sName(move(src.sName)), wLevel(src.wLevel), 
			byQuality(src.byQuality), eOptType(src.eOptType), dwType(src.dwType), qwResult(src.qwResult), happenedTime(src.happenedTime) { }

SFighterLog& SFighterLog::operator=(SFighterLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SFighterLog();
		new (this) SFighterLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SFighterLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.wFighterId;
	src >> s.sName;
	src >> s.wLevel;
	src >> s.byQuality;
	src >> (UINT8&)s.eOptType;
	src >> s.dwType;
	src >> s.qwResult;
	src >> s.happenedTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFighterLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.wFighterId;
	src << s.sName;
	src << s.wLevel;
	src << s.byQuality;
	src << (UINT8&)s.eOptType;
	src << s.dwType;
	src << s.qwResult;
	src << s.happenedTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecFighterLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SFighterLogPtr p(new SFighterLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecFighterLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFighterLog& s)
{
	if(strcmp(rElement.Value(), "SFighterLog") != 0)
	{
		LOG_CRI << "rElement is not SFighterLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wFighterId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFighterId") != 0)
	{
		LOG_CRI << "Attribute: name is not wFighterId!";
		return false;
	}
	const char* pszVal_wFighterId = pElemChild->Attribute("value");
	if(pszVal_wFighterId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFighterId, s.wFighterId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sName") != 0)
	{
		LOG_CRI << "Attribute: name is not sName!";
		return false;
	}
	const char* pszVal_sName = pElemChild->Attribute("value");
	if(pszVal_sName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.sName = pszVal_sName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not wLevel!";
		return false;
	}
	const char* pszVal_wLevel = pElemChild->Attribute("value");
	if(pszVal_wLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wLevel, s.wLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQuality is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQuality") != 0)
	{
		LOG_CRI << "Attribute: name is not byQuality!";
		return false;
	}
	const char* pszVal_byQuality = pElemChild->Attribute("value");
	if(pszVal_byQuality == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQuality, s.byQuality))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eOptType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EFighterOptType") != 0)
	{
		LOG_CRI << "pElemChild is not EFighterOptType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eOptType") != 0)
	{
		LOG_CRI << "Attribute: name is not eOptType!";
		return false;
	}
	const char* pszVal_eOptType = pElemChild->Attribute("value");
	if(pszVal_eOptType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eOptType, s.eOptType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwType") != 0)
	{
		LOG_CRI << "Attribute: name is not dwType!";
		return false;
	}
	const char* pszVal_dwType = pElemChild->Attribute("value");
	if(pszVal_dwType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwType, s.dwType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwResult is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwResult") != 0)
	{
		LOG_CRI << "Attribute: name is not qwResult!";
		return false;
	}
	const char* pszVal_qwResult = pElemChild->Attribute("value");
	if(pszVal_qwResult == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwResult, s.qwResult))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for happenedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "happenedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not happenedTime!";
		return false;
	}
	const char* pszVal_happenedTime = pElemChild->Attribute("value");
	if(pszVal_happenedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_happenedTime, s.happenedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFighterLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFighterLog");
	rElement.SetAttribute("type", ToUTF8Ptr("散仙日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_wFighterId(new TiXmlElement("UINT16"));
	if(pElem_wFighterId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterId->SetAttribute("name", "wFighterId");
	pElem_wFighterId->SetAttribute("value", NumberToString(s.wFighterId).c_str());
	pElem_wFighterId->SetAttribute("comment", ToUTF8Ptr("散仙ID"));
	if(rElement.LinkEndChild(pElem_wFighterId.get()) != NULL)
		pElem_wFighterId.release();
	unique_ptr<TiXmlElement> pElem_sName(new TiXmlElement("string"));
	if(pElem_sName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sName->SetAttribute("name", "sName");
	pElem_sName->SetAttribute("value", s.sName.c_str());
	pElem_sName->SetAttribute("comment", ToUTF8Ptr("散仙名字"));
	if(rElement.LinkEndChild(pElem_sName.get()) != NULL)
		pElem_sName.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("散仙等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("散仙品质"));
	if(rElement.LinkEndChild(pElem_byQuality.get()) != NULL)
		pElem_byQuality.release();
	unique_ptr<TiXmlElement> pElem_eOptType(new TiXmlElement("EFighterOptType"));
	if(pElem_eOptType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eOptType->SetAttribute("name", "eOptType");
	const char* pszEnum_eOptType = EnumValToStr(s.eOptType);
	if(pszEnum_eOptType == NULL)
	{
		LOG_CRI << "EnumValToStr for EFighterOptType fails!";
		return false;
	}
	pElem_eOptType->SetAttribute("value", pszEnum_eOptType);
	pElem_eOptType->SetAttribute("comment", ToUTF8Ptr("操作类型1"));
	if(rElement.LinkEndChild(pElem_eOptType.get()) != NULL)
		pElem_eOptType.release();
	unique_ptr<TiXmlElement> pElem_dwType(new TiXmlElement("UINT32"));
	if(pElem_dwType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwType->SetAttribute("name", "dwType");
	pElem_dwType->SetAttribute("value", NumberToString(s.dwType).c_str());
	pElem_dwType->SetAttribute("comment", ToUTF8Ptr("操作类型2(本命法宝时，0表示法宝，1表示法宝技能)"));
	if(rElement.LinkEndChild(pElem_dwType.get()) != NULL)
		pElem_dwType.release();
	unique_ptr<TiXmlElement> pElem_qwResult(new TiXmlElement("UINT64"));
	if(pElem_qwResult == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwResult->SetAttribute("name", "qwResult");
	pElem_qwResult->SetAttribute("value", NumberToString(s.qwResult).c_str());
	pElem_qwResult->SetAttribute("comment", ToUTF8Ptr("操作结果(本命法宝时：前32位表示ID，后32为表示等级"));
	if(rElement.LinkEndChild(pElem_qwResult.get()) != NULL)
		pElem_qwResult.release();
	unique_ptr<TiXmlElement> pElem_happenedTime(new TiXmlElement("UINT32"));
	if(pElem_happenedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_happenedTime->SetAttribute("name", "happenedTime");
	pElem_happenedTime->SetAttribute("value", NumberToString(s.happenedTime).c_str());
	pElem_happenedTime->SetAttribute("comment", ToUTF8Ptr("时间"));
	if(rElement.LinkEndChild(pElem_happenedTime.get()) != NULL)
		pElem_happenedTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFighterLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFighterLogPtr p(new SFighterLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecFighterLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFighterLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SHorseLog::SHorseLog() : dwServerId(0), qwUserId(0), dwID(0), dwLevel(0), happenedTime(0) { }

SHorseLog::SHorseLog(SHorseLog&& src) : LogDataBase(src), dwServerId(src.dwServerId), qwUserId(src.qwUserId), dwID(src.dwID), sName(move(src.sName)), dwLevel(src.dwLevel), 
			happenedTime(src.happenedTime) { }

SHorseLog& SHorseLog::operator=(SHorseLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SHorseLog();
		new (this) SHorseLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SHorseLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.dwID;
	src >> s.sName;
	src >> s.dwLevel;
	src >> s.happenedTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SHorseLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.dwID;
	src << s.sName;
	src << s.dwLevel;
	src << s.happenedTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecHorseLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SHorseLogPtr p(new SHorseLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecHorseLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SHorseLog& s)
{
	if(strcmp(rElement.Value(), "SHorseLog") != 0)
	{
		LOG_CRI << "rElement is not SHorseLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwID!";
		return false;
	}
	const char* pszVal_dwID = pElemChild->Attribute("value");
	if(pszVal_dwID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwID, s.dwID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sName") != 0)
	{
		LOG_CRI << "Attribute: name is not sName!";
		return false;
	}
	const char* pszVal_sName = pElemChild->Attribute("value");
	if(pszVal_sName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.sName = pszVal_sName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLevel!";
		return false;
	}
	const char* pszVal_dwLevel = pElemChild->Attribute("value");
	if(pszVal_dwLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLevel, s.dwLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for happenedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "happenedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not happenedTime!";
		return false;
	}
	const char* pszVal_happenedTime = pElemChild->Attribute("value");
	if(pszVal_happenedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_happenedTime, s.happenedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SHorseLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SHorseLog");
	rElement.SetAttribute("type", ToUTF8Ptr("坐骑日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_dwID(new TiXmlElement("UINT32"));
	if(pElem_dwID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwID->SetAttribute("name", "dwID");
	pElem_dwID->SetAttribute("value", NumberToString(s.dwID).c_str());
	pElem_dwID->SetAttribute("comment", ToUTF8Ptr("坐骑ID"));
	if(rElement.LinkEndChild(pElem_dwID.get()) != NULL)
		pElem_dwID.release();
	unique_ptr<TiXmlElement> pElem_sName(new TiXmlElement("string"));
	if(pElem_sName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sName->SetAttribute("name", "sName");
	pElem_sName->SetAttribute("value", s.sName.c_str());
	pElem_sName->SetAttribute("comment", ToUTF8Ptr("坐骑名字"));
	if(rElement.LinkEndChild(pElem_sName.get()) != NULL)
		pElem_sName.release();
	unique_ptr<TiXmlElement> pElem_dwLevel(new TiXmlElement("UINT32"));
	if(pElem_dwLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLevel->SetAttribute("name", "dwLevel");
	pElem_dwLevel->SetAttribute("value", NumberToString(s.dwLevel).c_str());
	pElem_dwLevel->SetAttribute("comment", ToUTF8Ptr("坐骑等级"));
	if(rElement.LinkEndChild(pElem_dwLevel.get()) != NULL)
		pElem_dwLevel.release();
	unique_ptr<TiXmlElement> pElem_happenedTime(new TiXmlElement("UINT32"));
	if(pElem_happenedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_happenedTime->SetAttribute("name", "happenedTime");
	pElem_happenedTime->SetAttribute("value", NumberToString(s.happenedTime).c_str());
	pElem_happenedTime->SetAttribute("comment", ToUTF8Ptr("时间"));
	if(rElement.LinkEndChild(pElem_happenedTime.get()) != NULL)
		pElem_happenedTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecHorseLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SHorseLogPtr p(new SHorseLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecHorseLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SHorseLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

STrumpLog::STrumpLog() : dwServerId(0), qwUserId(0), wID(0), dwSkillId(0), dwLevel(0), 
			dwExp(0), happenedTime(0) { }

STrumpLog::STrumpLog(STrumpLog&& src) : LogDataBase(src), dwServerId(src.dwServerId), qwUserId(src.qwUserId), wID(src.wID), sName(move(src.sName)), dwSkillId(src.dwSkillId), 
			dwLevel(src.dwLevel), dwExp(src.dwExp), happenedTime(src.happenedTime) { }

STrumpLog& STrumpLog::operator=(STrumpLog&& rhs)
{
	if(this != &rhs)
	{
		this->~STrumpLog();
		new (this) STrumpLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, STrumpLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.wID;
	src >> s.sName;
	src >> s.dwSkillId;
	src >> s.dwLevel;
	src >> s.dwExp;
	src >> s.happenedTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STrumpLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.wID;
	src << s.sName;
	src << s.dwSkillId;
	src << s.dwLevel;
	src << s.dwExp;
	src << s.happenedTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecTrumpLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		STrumpLogPtr p(new STrumpLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecTrumpLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STrumpLog& s)
{
	if(strcmp(rElement.Value(), "STrumpLog") != 0)
	{
		LOG_CRI << "rElement is not STrumpLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wID") != 0)
	{
		LOG_CRI << "Attribute: name is not wID!";
		return false;
	}
	const char* pszVal_wID = pElemChild->Attribute("value");
	if(pszVal_wID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wID, s.wID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sName") != 0)
	{
		LOG_CRI << "Attribute: name is not sName!";
		return false;
	}
	const char* pszVal_sName = pElemChild->Attribute("value");
	if(pszVal_sName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.sName = pszVal_sName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillId!";
		return false;
	}
	const char* pszVal_dwSkillId = pElemChild->Attribute("value");
	if(pszVal_dwSkillId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillId, s.dwSkillId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLevel!";
		return false;
	}
	const char* pszVal_dwLevel = pElemChild->Attribute("value");
	if(pszVal_dwLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLevel, s.dwLevel))
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for happenedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "happenedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not happenedTime!";
		return false;
	}
	const char* pszVal_happenedTime = pElemChild->Attribute("value");
	if(pszVal_happenedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_happenedTime, s.happenedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STrumpLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("STrumpLog");
	rElement.SetAttribute("type", ToUTF8Ptr("法宝日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_wID(new TiXmlElement("UINT16"));
	if(pElem_wID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wID->SetAttribute("name", "wID");
	pElem_wID->SetAttribute("value", NumberToString(s.wID).c_str());
	pElem_wID->SetAttribute("comment", ToUTF8Ptr("法宝ID"));
	if(rElement.LinkEndChild(pElem_wID.get()) != NULL)
		pElem_wID.release();
	unique_ptr<TiXmlElement> pElem_sName(new TiXmlElement("string"));
	if(pElem_sName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sName->SetAttribute("name", "sName");
	pElem_sName->SetAttribute("value", s.sName.c_str());
	pElem_sName->SetAttribute("comment", ToUTF8Ptr("法宝名字"));
	if(rElement.LinkEndChild(pElem_sName.get()) != NULL)
		pElem_sName.release();
	unique_ptr<TiXmlElement> pElem_dwSkillId(new TiXmlElement("UINT32"));
	if(pElem_dwSkillId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillId->SetAttribute("name", "dwSkillId");
	pElem_dwSkillId->SetAttribute("value", NumberToString(s.dwSkillId).c_str());
	pElem_dwSkillId->SetAttribute("comment", ToUTF8Ptr("法宝技能等级"));
	if(rElement.LinkEndChild(pElem_dwSkillId.get()) != NULL)
		pElem_dwSkillId.release();
	unique_ptr<TiXmlElement> pElem_dwLevel(new TiXmlElement("UINT32"));
	if(pElem_dwLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLevel->SetAttribute("name", "dwLevel");
	pElem_dwLevel->SetAttribute("value", NumberToString(s.dwLevel).c_str());
	pElem_dwLevel->SetAttribute("comment", ToUTF8Ptr("法宝品节"));
	if(rElement.LinkEndChild(pElem_dwLevel.get()) != NULL)
		pElem_dwLevel.release();
	unique_ptr<TiXmlElement> pElem_dwExp(new TiXmlElement("UINT32"));
	if(pElem_dwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExp->SetAttribute("name", "dwExp");
	pElem_dwExp->SetAttribute("value", NumberToString(s.dwExp).c_str());
	pElem_dwExp->SetAttribute("comment", ToUTF8Ptr("法宝当前祭炼值"));
	if(rElement.LinkEndChild(pElem_dwExp.get()) != NULL)
		pElem_dwExp.release();
	unique_ptr<TiXmlElement> pElem_happenedTime(new TiXmlElement("UINT32"));
	if(pElem_happenedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_happenedTime->SetAttribute("name", "happenedTime");
	pElem_happenedTime->SetAttribute("value", NumberToString(s.happenedTime).c_str());
	pElem_happenedTime->SetAttribute("comment", ToUTF8Ptr("时间"));
	if(rElement.LinkEndChild(pElem_happenedTime.get()) != NULL)
		pElem_happenedTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTrumpLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STrumpLogPtr p(new STrumpLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecTrumpLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STrumpLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SBeautyLog::SBeautyLog() : dwServerId(0), qwUserId(0), wID(0), wLevel(0), dwExp(0), 
			happenedTime(0) { }

SBeautyLog::SBeautyLog(SBeautyLog&& src) : LogDataBase(src), dwServerId(src.dwServerId), qwUserId(src.qwUserId), wID(src.wID), sName(move(src.sName)), wLevel(src.wLevel), 
			dwExp(src.dwExp), happenedTime(src.happenedTime) { }

SBeautyLog& SBeautyLog::operator=(SBeautyLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SBeautyLog();
		new (this) SBeautyLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBeautyLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.wID;
	src >> s.sName;
	src >> s.wLevel;
	src >> s.dwExp;
	src >> s.happenedTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBeautyLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.wID;
	src << s.sName;
	src << s.wLevel;
	src << s.dwExp;
	src << s.happenedTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecBeautyLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SBeautyLogPtr p(new SBeautyLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecBeautyLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBeautyLog& s)
{
	if(strcmp(rElement.Value(), "SBeautyLog") != 0)
	{
		LOG_CRI << "rElement is not SBeautyLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wID") != 0)
	{
		LOG_CRI << "Attribute: name is not wID!";
		return false;
	}
	const char* pszVal_wID = pElemChild->Attribute("value");
	if(pszVal_wID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wID, s.wID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sName") != 0)
	{
		LOG_CRI << "Attribute: name is not sName!";
		return false;
	}
	const char* pszVal_sName = pElemChild->Attribute("value");
	if(pszVal_sName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.sName = pszVal_sName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not wLevel!";
		return false;
	}
	const char* pszVal_wLevel = pElemChild->Attribute("value");
	if(pszVal_wLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wLevel, s.wLevel))
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for happenedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "happenedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not happenedTime!";
		return false;
	}
	const char* pszVal_happenedTime = pElemChild->Attribute("value");
	if(pszVal_happenedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_happenedTime, s.happenedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBeautyLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBeautyLog");
	rElement.SetAttribute("type", ToUTF8Ptr("美女日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_wID(new TiXmlElement("UINT16"));
	if(pElem_wID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wID->SetAttribute("name", "wID");
	pElem_wID->SetAttribute("value", NumberToString(s.wID).c_str());
	pElem_wID->SetAttribute("comment", ToUTF8Ptr("美女ID"));
	if(rElement.LinkEndChild(pElem_wID.get()) != NULL)
		pElem_wID.release();
	unique_ptr<TiXmlElement> pElem_sName(new TiXmlElement("string"));
	if(pElem_sName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sName->SetAttribute("name", "sName");
	pElem_sName->SetAttribute("value", s.sName.c_str());
	pElem_sName->SetAttribute("comment", ToUTF8Ptr("美女名字"));
	if(rElement.LinkEndChild(pElem_sName.get()) != NULL)
		pElem_sName.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("亲密等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	unique_ptr<TiXmlElement> pElem_dwExp(new TiXmlElement("UINT32"));
	if(pElem_dwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExp->SetAttribute("name", "dwExp");
	pElem_dwExp->SetAttribute("value", NumberToString(s.dwExp).c_str());
	pElem_dwExp->SetAttribute("comment", ToUTF8Ptr("亲密度"));
	if(rElement.LinkEndChild(pElem_dwExp.get()) != NULL)
		pElem_dwExp.release();
	unique_ptr<TiXmlElement> pElem_happenedTime(new TiXmlElement("UINT32"));
	if(pElem_happenedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_happenedTime->SetAttribute("name", "happenedTime");
	pElem_happenedTime->SetAttribute("value", NumberToString(s.happenedTime).c_str());
	pElem_happenedTime->SetAttribute("comment", ToUTF8Ptr("时间"));
	if(rElement.LinkEndChild(pElem_happenedTime.get()) != NULL)
		pElem_happenedTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBeautyLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBeautyLogPtr p(new SBeautyLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecBeautyLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBeautyLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SEquipLog::SEquipLog() : dwServerId(0), qwUserId(0), dwID(0), dwLevel(0), happenedTime(0) { }

SEquipLog::SEquipLog(SEquipLog&& src) : LogDataBase(src), dwServerId(src.dwServerId), qwUserId(src.qwUserId), dwID(src.dwID), sName(move(src.sName)), dwLevel(src.dwLevel), 
			happenedTime(src.happenedTime) { }

SEquipLog& SEquipLog::operator=(SEquipLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SEquipLog();
		new (this) SEquipLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SEquipLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.dwID;
	src >> s.sName;
	src >> s.dwLevel;
	src >> s.happenedTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEquipLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.dwID;
	src << s.sName;
	src << s.dwLevel;
	src << s.happenedTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecEquipLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEquipLogPtr p(new SEquipLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecEquipLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SEquipLog& s)
{
	if(strcmp(rElement.Value(), "SEquipLog") != 0)
	{
		LOG_CRI << "rElement is not SEquipLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwID!";
		return false;
	}
	const char* pszVal_dwID = pElemChild->Attribute("value");
	if(pszVal_dwID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwID, s.dwID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sName") != 0)
	{
		LOG_CRI << "Attribute: name is not sName!";
		return false;
	}
	const char* pszVal_sName = pElemChild->Attribute("value");
	if(pszVal_sName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.sName = pszVal_sName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLevel!";
		return false;
	}
	const char* pszVal_dwLevel = pElemChild->Attribute("value");
	if(pszVal_dwLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLevel, s.dwLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for happenedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "happenedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not happenedTime!";
		return false;
	}
	const char* pszVal_happenedTime = pElemChild->Attribute("value");
	if(pszVal_happenedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_happenedTime, s.happenedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEquipLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEquipLog");
	rElement.SetAttribute("type", ToUTF8Ptr("装备日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_dwID(new TiXmlElement("UINT32"));
	if(pElem_dwID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwID->SetAttribute("name", "dwID");
	pElem_dwID->SetAttribute("value", NumberToString(s.dwID).c_str());
	pElem_dwID->SetAttribute("comment", ToUTF8Ptr("装备ID"));
	if(rElement.LinkEndChild(pElem_dwID.get()) != NULL)
		pElem_dwID.release();
	unique_ptr<TiXmlElement> pElem_sName(new TiXmlElement("string"));
	if(pElem_sName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sName->SetAttribute("name", "sName");
	pElem_sName->SetAttribute("value", s.sName.c_str());
	pElem_sName->SetAttribute("comment", ToUTF8Ptr("装备名字"));
	if(rElement.LinkEndChild(pElem_sName.get()) != NULL)
		pElem_sName.release();
	unique_ptr<TiXmlElement> pElem_dwLevel(new TiXmlElement("UINT32"));
	if(pElem_dwLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLevel->SetAttribute("name", "dwLevel");
	pElem_dwLevel->SetAttribute("value", NumberToString(s.dwLevel).c_str());
	pElem_dwLevel->SetAttribute("comment", ToUTF8Ptr("装备等级"));
	if(rElement.LinkEndChild(pElem_dwLevel.get()) != NULL)
		pElem_dwLevel.release();
	unique_ptr<TiXmlElement> pElem_happenedTime(new TiXmlElement("UINT32"));
	if(pElem_happenedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_happenedTime->SetAttribute("name", "happenedTime");
	pElem_happenedTime->SetAttribute("value", NumberToString(s.happenedTime).c_str());
	pElem_happenedTime->SetAttribute("comment", ToUTF8Ptr("时间"));
	if(rElement.LinkEndChild(pElem_happenedTime.get()) != NULL)
		pElem_happenedTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecEquipLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEquipLogPtr p(new SEquipLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecEquipLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEquipLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SGuildLog::SGuildLog() : dwServerId(0), qwGuildId(0), byLevel(0), dwCount(0), byTowerLvl(0), 
			byStoreLvl(0), byHourseLvl(0), dwScore(0), dwMoney(0), happenedTime(0), 
			byOptType(0), byOptParam(0) { }

SGuildLog::SGuildLog(SGuildLog&& src) : LogDataBase(src), dwServerId(src.dwServerId), qwGuildId(src.qwGuildId), sName(move(src.sName)), byLevel(src.byLevel), dwCount(src.dwCount), 
			byTowerLvl(src.byTowerLvl), byStoreLvl(src.byStoreLvl), byHourseLvl(src.byHourseLvl), dwScore(src.dwScore), dwMoney(src.dwMoney), 
			happenedTime(src.happenedTime), byOptType(src.byOptType), byOptParam(src.byOptParam) { }

SGuildLog& SGuildLog::operator=(SGuildLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SGuildLog();
		new (this) SGuildLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGuildLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.dwServerId;
	src >> s.qwGuildId;
	src >> s.sName;
	src >> s.byLevel;
	src >> s.dwCount;
	src >> s.byTowerLvl;
	src >> s.byStoreLvl;
	src >> s.byHourseLvl;
	src >> s.dwScore;
	src >> s.dwMoney;
	src >> s.happenedTime;
	src >> s.byOptType;
	src >> s.byOptParam;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.dwServerId;
	src << s.qwGuildId;
	src << s.sName;
	src << s.byLevel;
	src << s.dwCount;
	src << s.byTowerLvl;
	src << s.byStoreLvl;
	src << s.byHourseLvl;
	src << s.dwScore;
	src << s.dwMoney;
	src << s.happenedTime;
	src << s.byOptType;
	src << s.byOptParam;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecGuildLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGuildLogPtr p(new SGuildLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecGuildLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGuildLog& s)
{
	if(strcmp(rElement.Value(), "SGuildLog") != 0)
	{
		LOG_CRI << "rElement is not SGuildLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwGuildId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwGuildId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwGuildId!";
		return false;
	}
	const char* pszVal_qwGuildId = pElemChild->Attribute("value");
	if(pszVal_qwGuildId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwGuildId, s.qwGuildId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sName") != 0)
	{
		LOG_CRI << "Attribute: name is not sName!";
		return false;
	}
	const char* pszVal_sName = pElemChild->Attribute("value");
	if(pszVal_sName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.sName = pszVal_sName;
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
		LOG_CRI << "pElemChild for byTowerLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTowerLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byTowerLvl!";
		return false;
	}
	const char* pszVal_byTowerLvl = pElemChild->Attribute("value");
	if(pszVal_byTowerLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTowerLvl, s.byTowerLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStoreLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStoreLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byStoreLvl!";
		return false;
	}
	const char* pszVal_byStoreLvl = pElemChild->Attribute("value");
	if(pszVal_byStoreLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStoreLvl, s.byStoreLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byHourseLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byHourseLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byHourseLvl!";
		return false;
	}
	const char* pszVal_byHourseLvl = pElemChild->Attribute("value");
	if(pszVal_byHourseLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byHourseLvl, s.byHourseLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwScore!";
		return false;
	}
	const char* pszVal_dwScore = pElemChild->Attribute("value");
	if(pszVal_dwScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwScore, s.dwScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMoney is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMoney") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMoney!";
		return false;
	}
	const char* pszVal_dwMoney = pElemChild->Attribute("value");
	if(pszVal_dwMoney == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMoney, s.dwMoney))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for happenedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "happenedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not happenedTime!";
		return false;
	}
	const char* pszVal_happenedTime = pElemChild->Attribute("value");
	if(pszVal_happenedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_happenedTime, s.happenedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byOptType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byOptType") != 0)
	{
		LOG_CRI << "Attribute: name is not byOptType!";
		return false;
	}
	const char* pszVal_byOptType = pElemChild->Attribute("value");
	if(pszVal_byOptType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byOptType, s.byOptType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byOptParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byOptParam") != 0)
	{
		LOG_CRI << "Attribute: name is not byOptParam!";
		return false;
	}
	const char* pszVal_byOptParam = pElemChild->Attribute("value");
	if(pszVal_byOptParam == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byOptParam, s.byOptParam))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildLog");
	rElement.SetAttribute("type", ToUTF8Ptr("帮会日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("服务器ID"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwGuildId(new TiXmlElement("UINT64"));
	if(pElem_qwGuildId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildId->SetAttribute("name", "qwGuildId");
	pElem_qwGuildId->SetAttribute("value", NumberToString(s.qwGuildId).c_str());
	pElem_qwGuildId->SetAttribute("comment", ToUTF8Ptr("帮派ID"));
	if(rElement.LinkEndChild(pElem_qwGuildId.get()) != NULL)
		pElem_qwGuildId.release();
	unique_ptr<TiXmlElement> pElem_sName(new TiXmlElement("string"));
	if(pElem_sName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sName->SetAttribute("name", "sName");
	pElem_sName->SetAttribute("value", s.sName.c_str());
	pElem_sName->SetAttribute("comment", ToUTF8Ptr("帮派名字"));
	if(rElement.LinkEndChild(pElem_sName.get()) != NULL)
		pElem_sName.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("帮派等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("帮派人员"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	unique_ptr<TiXmlElement> pElem_byTowerLvl(new TiXmlElement("UINT8"));
	if(pElem_byTowerLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTowerLvl->SetAttribute("name", "byTowerLvl");
	pElem_byTowerLvl->SetAttribute("value", NumberToString(s.byTowerLvl).c_str());
	pElem_byTowerLvl->SetAttribute("comment", ToUTF8Ptr("神谕塔等级"));
	if(rElement.LinkEndChild(pElem_byTowerLvl.get()) != NULL)
		pElem_byTowerLvl.release();
	unique_ptr<TiXmlElement> pElem_byStoreLvl(new TiXmlElement("UINT8"));
	if(pElem_byStoreLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStoreLvl->SetAttribute("name", "byStoreLvl");
	pElem_byStoreLvl->SetAttribute("value", NumberToString(s.byStoreLvl).c_str());
	pElem_byStoreLvl->SetAttribute("comment", ToUTF8Ptr("仓库等级"));
	if(rElement.LinkEndChild(pElem_byStoreLvl.get()) != NULL)
		pElem_byStoreLvl.release();
	unique_ptr<TiXmlElement> pElem_byHourseLvl(new TiXmlElement("UINT8"));
	if(pElem_byHourseLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byHourseLvl->SetAttribute("name", "byHourseLvl");
	pElem_byHourseLvl->SetAttribute("value", NumberToString(s.byHourseLvl).c_str());
	pElem_byHourseLvl->SetAttribute("comment", ToUTF8Ptr("剑阁等级"));
	if(rElement.LinkEndChild(pElem_byHourseLvl.get()) != NULL)
		pElem_byHourseLvl.release();
	unique_ptr<TiXmlElement> pElem_dwScore(new TiXmlElement("UINT32"));
	if(pElem_dwScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwScore->SetAttribute("name", "dwScore");
	pElem_dwScore->SetAttribute("value", NumberToString(s.dwScore).c_str());
	pElem_dwScore->SetAttribute("comment", ToUTF8Ptr("帮派积分"));
	if(rElement.LinkEndChild(pElem_dwScore.get()) != NULL)
		pElem_dwScore.release();
	unique_ptr<TiXmlElement> pElem_dwMoney(new TiXmlElement("UINT32"));
	if(pElem_dwMoney == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMoney->SetAttribute("name", "dwMoney");
	pElem_dwMoney->SetAttribute("value", NumberToString(s.dwMoney).c_str());
	pElem_dwMoney->SetAttribute("comment", ToUTF8Ptr("帮派金钱"));
	if(rElement.LinkEndChild(pElem_dwMoney.get()) != NULL)
		pElem_dwMoney.release();
	unique_ptr<TiXmlElement> pElem_happenedTime(new TiXmlElement("UINT32"));
	if(pElem_happenedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_happenedTime->SetAttribute("name", "happenedTime");
	pElem_happenedTime->SetAttribute("value", NumberToString(s.happenedTime).c_str());
	pElem_happenedTime->SetAttribute("comment", ToUTF8Ptr("创建时间"));
	if(rElement.LinkEndChild(pElem_happenedTime.get()) != NULL)
		pElem_happenedTime.release();
	unique_ptr<TiXmlElement> pElem_byOptType(new TiXmlElement("UINT8"));
	if(pElem_byOptType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byOptType->SetAttribute("name", "byOptType");
	pElem_byOptType->SetAttribute("value", NumberToString(s.byOptType).c_str());
	pElem_byOptType->SetAttribute("comment", ToUTF8Ptr("数据库操作 (1创建，其他Update)"));
	if(rElement.LinkEndChild(pElem_byOptType.get()) != NULL)
		pElem_byOptType.release();
	unique_ptr<TiXmlElement> pElem_byOptParam(new TiXmlElement("UINT8"));
	if(pElem_byOptParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byOptParam->SetAttribute("name", "byOptParam");
	pElem_byOptParam->SetAttribute("value", NumberToString(s.byOptParam).c_str());
	pElem_byOptParam->SetAttribute("comment", ToUTF8Ptr("附加参数(1加入2加钱3加积分4神谕塔升级5仓库升级6剑阁升级)"));
	if(rElement.LinkEndChild(pElem_byOptParam.get()) != NULL)
		pElem_byOptParam.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildLogPtr p(new SGuildLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecGuildLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SSendMoneyLog::SSendMoneyLog() : byStatus(0), dwServerId(0), qwUserId(0), byMoneyType(0), dwMoneyValue(0), 
			dwOpTime(0) { }

SSendMoneyLog::SSendMoneyLog(SSendMoneyLog&& src) : LogDataBase(src), strSendName(move(src.strSendName)), byStatus(src.byStatus), dwServerId(src.dwServerId), qwUserId(src.qwUserId), byMoneyType(src.byMoneyType), 
			dwMoneyValue(src.dwMoneyValue), strReason(move(src.strReason)), dwOpTime(src.dwOpTime) { }

SSendMoneyLog& SSendMoneyLog::operator=(SSendMoneyLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SSendMoneyLog();
		new (this) SSendMoneyLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SSendMoneyLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.strSendName;
	src >> s.byStatus;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.byMoneyType;
	src >> s.dwMoneyValue;
	src >> s.strReason;
	src >> s.dwOpTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSendMoneyLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.strSendName;
	src << s.byStatus;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.byMoneyType;
	src << s.dwMoneyValue;
	src << s.strReason;
	src << s.dwOpTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSendMoneyLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SSendMoneyLogPtr p(new SSendMoneyLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSendMoneyLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSendMoneyLog& s)
{
	if(strcmp(rElement.Value(), "SSendMoneyLog") != 0)
	{
		LOG_CRI << "rElement is not SSendMoneyLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
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
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byMoneyType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byMoneyType") != 0)
	{
		LOG_CRI << "Attribute: name is not byMoneyType!";
		return false;
	}
	const char* pszVal_byMoneyType = pElemChild->Attribute("value");
	if(pszVal_byMoneyType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byMoneyType, s.byMoneyType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMoneyValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMoneyValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMoneyValue!";
		return false;
	}
	const char* pszVal_dwMoneyValue = pElemChild->Attribute("value");
	if(pszVal_dwMoneyValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMoneyValue, s.dwMoneyValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strReason is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strReason") != 0)
	{
		LOG_CRI << "Attribute: name is not strReason!";
		return false;
	}
	const char* pszVal_strReason = pElemChild->Attribute("value");
	if(pszVal_strReason == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strReason = pszVal_strReason;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOpTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOpTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOpTime!";
		return false;
	}
	const char* pszVal_dwOpTime = pElemChild->Attribute("value");
	if(pszVal_dwOpTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOpTime, s.dwOpTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSendMoneyLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSendMoneyLog");
	rElement.SetAttribute("type", ToUTF8Ptr("发送货币日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("发送人"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("大区"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_byMoneyType(new TiXmlElement("UINT8"));
	if(pElem_byMoneyType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byMoneyType->SetAttribute("name", "byMoneyType");
	pElem_byMoneyType->SetAttribute("value", NumberToString(s.byMoneyType).c_str());
	pElem_byMoneyType->SetAttribute("comment", ToUTF8Ptr("货币类型"));
	if(rElement.LinkEndChild(pElem_byMoneyType.get()) != NULL)
		pElem_byMoneyType.release();
	unique_ptr<TiXmlElement> pElem_dwMoneyValue(new TiXmlElement("UINT32"));
	if(pElem_dwMoneyValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMoneyValue->SetAttribute("name", "dwMoneyValue");
	pElem_dwMoneyValue->SetAttribute("value", NumberToString(s.dwMoneyValue).c_str());
	pElem_dwMoneyValue->SetAttribute("comment", ToUTF8Ptr("发送数量"));
	if(rElement.LinkEndChild(pElem_dwMoneyValue.get()) != NULL)
		pElem_dwMoneyValue.release();
	unique_ptr<TiXmlElement> pElem_strReason(new TiXmlElement("string"));
	if(pElem_strReason == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strReason->SetAttribute("name", "strReason");
	pElem_strReason->SetAttribute("value", s.strReason.c_str());
	pElem_strReason->SetAttribute("comment", ToUTF8Ptr("发送理由"));
	if(rElement.LinkEndChild(pElem_strReason.get()) != NULL)
		pElem_strReason.release();
	unique_ptr<TiXmlElement> pElem_dwOpTime(new TiXmlElement("UINT32"));
	if(pElem_dwOpTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOpTime->SetAttribute("name", "dwOpTime");
	pElem_dwOpTime->SetAttribute("value", NumberToString(s.dwOpTime).c_str());
	pElem_dwOpTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwOpTime.get()) != NULL)
		pElem_dwOpTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSendMoneyLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSendMoneyLogPtr p(new SSendMoneyLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecSendMoneyLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSendMoneyLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SSendItemLog::SSendItemLog() : byStatus(0), dwServerId(0), qwUserId(0), dwOpTime(0) { }

SSendItemLog::SSendItemLog(SSendItemLog&& src) : LogDataBase(src), strSendName(move(src.strSendName)), byStatus(src.byStatus), dwServerId(src.dwServerId), qwUserId(src.qwUserId), strTitle(move(src.strTitle)), 
			strBody(move(src.strBody)), strItemList(move(src.strItemList)), strReason(move(src.strReason)), dwOpTime(src.dwOpTime) { }

SSendItemLog& SSendItemLog::operator=(SSendItemLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SSendItemLog();
		new (this) SSendItemLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SSendItemLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.strSendName;
	src >> s.byStatus;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.strTitle;
	src >> s.strBody;
	src >> s.strItemList;
	src >> s.strReason;
	src >> s.dwOpTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSendItemLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.strSendName;
	src << s.byStatus;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.strTitle;
	src << s.strBody;
	src << s.strItemList;
	src << s.strReason;
	src << s.dwOpTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSendItemLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SSendItemLogPtr p(new SSendItemLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSendItemLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSendItemLog& s)
{
	if(strcmp(rElement.Value(), "SSendItemLog") != 0)
	{
		LOG_CRI << "rElement is not SSendItemLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
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
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not strTitle!";
		return false;
	}
	const char* pszVal_strTitle = pElemChild->Attribute("value");
	if(pszVal_strTitle == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strTitle = pszVal_strTitle;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strBody is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strBody") != 0)
	{
		LOG_CRI << "Attribute: name is not strBody!";
		return false;
	}
	const char* pszVal_strBody = pElemChild->Attribute("value");
	if(pszVal_strBody == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strBody = pszVal_strBody;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strItemList is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strItemList") != 0)
	{
		LOG_CRI << "Attribute: name is not strItemList!";
		return false;
	}
	const char* pszVal_strItemList = pElemChild->Attribute("value");
	if(pszVal_strItemList == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strItemList = pszVal_strItemList;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strReason is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strReason") != 0)
	{
		LOG_CRI << "Attribute: name is not strReason!";
		return false;
	}
	const char* pszVal_strReason = pElemChild->Attribute("value");
	if(pszVal_strReason == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strReason = pszVal_strReason;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOpTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOpTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOpTime!";
		return false;
	}
	const char* pszVal_dwOpTime = pElemChild->Attribute("value");
	if(pszVal_dwOpTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOpTime, s.dwOpTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSendItemLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSendItemLog");
	rElement.SetAttribute("type", ToUTF8Ptr("发送物品日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("发送人"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("大区"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_strTitle(new TiXmlElement("string"));
	if(pElem_strTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strTitle->SetAttribute("name", "strTitle");
	pElem_strTitle->SetAttribute("value", s.strTitle.c_str());
	pElem_strTitle->SetAttribute("comment", ToUTF8Ptr("标题"));
	if(rElement.LinkEndChild(pElem_strTitle.get()) != NULL)
		pElem_strTitle.release();
	unique_ptr<TiXmlElement> pElem_strBody(new TiXmlElement("string"));
	if(pElem_strBody == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strBody->SetAttribute("name", "strBody");
	pElem_strBody->SetAttribute("value", s.strBody.c_str());
	pElem_strBody->SetAttribute("comment", ToUTF8Ptr("内容"));
	if(rElement.LinkEndChild(pElem_strBody.get()) != NULL)
		pElem_strBody.release();
	unique_ptr<TiXmlElement> pElem_strItemList(new TiXmlElement("string"));
	if(pElem_strItemList == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strItemList->SetAttribute("name", "strItemList");
	pElem_strItemList->SetAttribute("value", s.strItemList.c_str());
	pElem_strItemList->SetAttribute("comment", ToUTF8Ptr("物品列表"));
	if(rElement.LinkEndChild(pElem_strItemList.get()) != NULL)
		pElem_strItemList.release();
	unique_ptr<TiXmlElement> pElem_strReason(new TiXmlElement("string"));
	if(pElem_strReason == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strReason->SetAttribute("name", "strReason");
	pElem_strReason->SetAttribute("value", s.strReason.c_str());
	pElem_strReason->SetAttribute("comment", ToUTF8Ptr("发送理由"));
	if(rElement.LinkEndChild(pElem_strReason.get()) != NULL)
		pElem_strReason.release();
	unique_ptr<TiXmlElement> pElem_dwOpTime(new TiXmlElement("UINT32"));
	if(pElem_dwOpTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOpTime->SetAttribute("name", "dwOpTime");
	pElem_dwOpTime->SetAttribute("value", NumberToString(s.dwOpTime).c_str());
	pElem_dwOpTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwOpTime.get()) != NULL)
		pElem_dwOpTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSendItemLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSendItemLogPtr p(new SSendItemLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecSendItemLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSendItemLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SMailOpLog::SMailOpLog() : byStatus(0), dwServerId(0), qwUserId(0), byMailOpType(0), dwOpTime(0) { }

SMailOpLog::SMailOpLog(SMailOpLog&& src) : LogDataBase(src), strSendName(move(src.strSendName)), byStatus(src.byStatus), dwServerId(src.dwServerId), qwUserId(src.qwUserId), byMailOpType(src.byMailOpType), 
			dwOpTime(src.dwOpTime) { }

SMailOpLog& SMailOpLog::operator=(SMailOpLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SMailOpLog();
		new (this) SMailOpLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SMailOpLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.strSendName;
	src >> s.byStatus;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.byMailOpType;
	src >> s.dwOpTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMailOpLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.strSendName;
	src << s.byStatus;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.byMailOpType;
	src << s.dwOpTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecMailOpLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SMailOpLogPtr p(new SMailOpLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecMailOpLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMailOpLog& s)
{
	if(strcmp(rElement.Value(), "SMailOpLog") != 0)
	{
		LOG_CRI << "rElement is not SMailOpLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
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
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byMailOpType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byMailOpType") != 0)
	{
		LOG_CRI << "Attribute: name is not byMailOpType!";
		return false;
	}
	const char* pszVal_byMailOpType = pElemChild->Attribute("value");
	if(pszVal_byMailOpType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byMailOpType, s.byMailOpType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOpTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOpTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOpTime!";
		return false;
	}
	const char* pszVal_dwOpTime = pElemChild->Attribute("value");
	if(pszVal_dwOpTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOpTime, s.dwOpTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SMailOpLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMailOpLog");
	rElement.SetAttribute("type", ToUTF8Ptr("邮件操作日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("操作人"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("大区"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_byMailOpType(new TiXmlElement("UINT8"));
	if(pElem_byMailOpType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byMailOpType->SetAttribute("name", "byMailOpType");
	pElem_byMailOpType->SetAttribute("value", NumberToString(s.byMailOpType).c_str());
	pElem_byMailOpType->SetAttribute("comment", ToUTF8Ptr("邮件操作类型"));
	if(rElement.LinkEndChild(pElem_byMailOpType.get()) != NULL)
		pElem_byMailOpType.release();
	unique_ptr<TiXmlElement> pElem_dwOpTime(new TiXmlElement("UINT32"));
	if(pElem_dwOpTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOpTime->SetAttribute("name", "dwOpTime");
	pElem_dwOpTime->SetAttribute("value", NumberToString(s.dwOpTime).c_str());
	pElem_dwOpTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwOpTime.get()) != NULL)
		pElem_dwOpTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMailOpLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMailOpLogPtr p(new SMailOpLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecMailOpLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMailOpLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SForbiddenLog::SForbiddenLog() : byStatus(0), dwServerId(0), qwUserId(0), byOpType(0), dwForbidTime(0), 
			dwOpTime(0) { }

SForbiddenLog::SForbiddenLog(SForbiddenLog&& src) : LogDataBase(src), strSendName(move(src.strSendName)), byStatus(src.byStatus), dwServerId(src.dwServerId), qwUserId(src.qwUserId), byOpType(src.byOpType), 
			dwForbidTime(src.dwForbidTime), strReason(move(src.strReason)), dwOpTime(src.dwOpTime) { }

SForbiddenLog& SForbiddenLog::operator=(SForbiddenLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SForbiddenLog();
		new (this) SForbiddenLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SForbiddenLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.strSendName;
	src >> s.byStatus;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.byOpType;
	src >> s.dwForbidTime;
	src >> s.strReason;
	src >> s.dwOpTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SForbiddenLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.strSendName;
	src << s.byStatus;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.byOpType;
	src << s.dwForbidTime;
	src << s.strReason;
	src << s.dwOpTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecForbiddenLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SForbiddenLogPtr p(new SForbiddenLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecForbiddenLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SForbiddenLog& s)
{
	if(strcmp(rElement.Value(), "SForbiddenLog") != 0)
	{
		LOG_CRI << "rElement is not SForbiddenLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
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
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byOpType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byOpType") != 0)
	{
		LOG_CRI << "Attribute: name is not byOpType!";
		return false;
	}
	const char* pszVal_byOpType = pElemChild->Attribute("value");
	if(pszVal_byOpType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byOpType, s.byOpType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwForbidTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwForbidTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwForbidTime!";
		return false;
	}
	const char* pszVal_dwForbidTime = pElemChild->Attribute("value");
	if(pszVal_dwForbidTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwForbidTime, s.dwForbidTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strReason is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strReason") != 0)
	{
		LOG_CRI << "Attribute: name is not strReason!";
		return false;
	}
	const char* pszVal_strReason = pElemChild->Attribute("value");
	if(pszVal_strReason == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strReason = pszVal_strReason;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOpTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOpTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOpTime!";
		return false;
	}
	const char* pszVal_dwOpTime = pElemChild->Attribute("value");
	if(pszVal_dwOpTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOpTime, s.dwOpTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SForbiddenLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SForbiddenLog");
	rElement.SetAttribute("type", ToUTF8Ptr("封号*解封记录"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("操作人"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("大区"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_byOpType(new TiXmlElement("UINT8"));
	if(pElem_byOpType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byOpType->SetAttribute("name", "byOpType");
	pElem_byOpType->SetAttribute("value", NumberToString(s.byOpType).c_str());
	pElem_byOpType->SetAttribute("comment", ToUTF8Ptr("操作类型"));
	if(rElement.LinkEndChild(pElem_byOpType.get()) != NULL)
		pElem_byOpType.release();
	unique_ptr<TiXmlElement> pElem_dwForbidTime(new TiXmlElement("UINT32"));
	if(pElem_dwForbidTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwForbidTime->SetAttribute("name", "dwForbidTime");
	pElem_dwForbidTime->SetAttribute("value", NumberToString(s.dwForbidTime).c_str());
	pElem_dwForbidTime->SetAttribute("comment", ToUTF8Ptr("封禁时间"));
	if(rElement.LinkEndChild(pElem_dwForbidTime.get()) != NULL)
		pElem_dwForbidTime.release();
	unique_ptr<TiXmlElement> pElem_strReason(new TiXmlElement("string"));
	if(pElem_strReason == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strReason->SetAttribute("name", "strReason");
	pElem_strReason->SetAttribute("value", s.strReason.c_str());
	pElem_strReason->SetAttribute("comment", ToUTF8Ptr("理由"));
	if(rElement.LinkEndChild(pElem_strReason.get()) != NULL)
		pElem_strReason.release();
	unique_ptr<TiXmlElement> pElem_dwOpTime(new TiXmlElement("UINT32"));
	if(pElem_dwOpTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOpTime->SetAttribute("name", "dwOpTime");
	pElem_dwOpTime->SetAttribute("value", NumberToString(s.dwOpTime).c_str());
	pElem_dwOpTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwOpTime.get()) != NULL)
		pElem_dwOpTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecForbiddenLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SForbiddenLogPtr p(new SForbiddenLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecForbiddenLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SForbiddenLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SForbiddenChatLog::SForbiddenChatLog() : byStatus(0), dwServerId(0), qwUserId(0), byOpType(0), dwForbidTime(0), 
			dwOpTime(0) { }

SForbiddenChatLog::SForbiddenChatLog(SForbiddenChatLog&& src) : LogDataBase(src), strSendName(move(src.strSendName)), byStatus(src.byStatus), dwServerId(src.dwServerId), qwUserId(src.qwUserId), byOpType(src.byOpType), 
			dwForbidTime(src.dwForbidTime), strReason(move(src.strReason)), dwOpTime(src.dwOpTime) { }

SForbiddenChatLog& SForbiddenChatLog::operator=(SForbiddenChatLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SForbiddenChatLog();
		new (this) SForbiddenChatLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SForbiddenChatLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.strSendName;
	src >> s.byStatus;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.byOpType;
	src >> s.dwForbidTime;
	src >> s.strReason;
	src >> s.dwOpTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SForbiddenChatLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.strSendName;
	src << s.byStatus;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.byOpType;
	src << s.dwForbidTime;
	src << s.strReason;
	src << s.dwOpTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecForbiddenChatLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SForbiddenChatLogPtr p(new SForbiddenChatLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecForbiddenChatLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SForbiddenChatLog& s)
{
	if(strcmp(rElement.Value(), "SForbiddenChatLog") != 0)
	{
		LOG_CRI << "rElement is not SForbiddenChatLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
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
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byOpType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byOpType") != 0)
	{
		LOG_CRI << "Attribute: name is not byOpType!";
		return false;
	}
	const char* pszVal_byOpType = pElemChild->Attribute("value");
	if(pszVal_byOpType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byOpType, s.byOpType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwForbidTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwForbidTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwForbidTime!";
		return false;
	}
	const char* pszVal_dwForbidTime = pElemChild->Attribute("value");
	if(pszVal_dwForbidTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwForbidTime, s.dwForbidTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strReason is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strReason") != 0)
	{
		LOG_CRI << "Attribute: name is not strReason!";
		return false;
	}
	const char* pszVal_strReason = pElemChild->Attribute("value");
	if(pszVal_strReason == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strReason = pszVal_strReason;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOpTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOpTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOpTime!";
		return false;
	}
	const char* pszVal_dwOpTime = pElemChild->Attribute("value");
	if(pszVal_dwOpTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOpTime, s.dwOpTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SForbiddenChatLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SForbiddenChatLog");
	rElement.SetAttribute("type", ToUTF8Ptr("禁言*解禁记录"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("操作人"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("大区"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_byOpType(new TiXmlElement("UINT8"));
	if(pElem_byOpType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byOpType->SetAttribute("name", "byOpType");
	pElem_byOpType->SetAttribute("value", NumberToString(s.byOpType).c_str());
	pElem_byOpType->SetAttribute("comment", ToUTF8Ptr("操作类型"));
	if(rElement.LinkEndChild(pElem_byOpType.get()) != NULL)
		pElem_byOpType.release();
	unique_ptr<TiXmlElement> pElem_dwForbidTime(new TiXmlElement("UINT32"));
	if(pElem_dwForbidTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwForbidTime->SetAttribute("name", "dwForbidTime");
	pElem_dwForbidTime->SetAttribute("value", NumberToString(s.dwForbidTime).c_str());
	pElem_dwForbidTime->SetAttribute("comment", ToUTF8Ptr("封禁时间"));
	if(rElement.LinkEndChild(pElem_dwForbidTime.get()) != NULL)
		pElem_dwForbidTime.release();
	unique_ptr<TiXmlElement> pElem_strReason(new TiXmlElement("string"));
	if(pElem_strReason == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strReason->SetAttribute("name", "strReason");
	pElem_strReason->SetAttribute("value", s.strReason.c_str());
	pElem_strReason->SetAttribute("comment", ToUTF8Ptr("理由"));
	if(rElement.LinkEndChild(pElem_strReason.get()) != NULL)
		pElem_strReason.release();
	unique_ptr<TiXmlElement> pElem_dwOpTime(new TiXmlElement("UINT32"));
	if(pElem_dwOpTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOpTime->SetAttribute("name", "dwOpTime");
	pElem_dwOpTime->SetAttribute("value", NumberToString(s.dwOpTime).c_str());
	pElem_dwOpTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwOpTime.get()) != NULL)
		pElem_dwOpTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecForbiddenChatLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SForbiddenChatLogPtr p(new SForbiddenChatLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecForbiddenChatLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SForbiddenChatLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SGlobalSendItemLog::SGlobalSendItemLog() : byStatus(0), dwServerId(0), qwUserId(0), dwGold(0), dwCoupon(0), 
			dwSliver(0), dwHonor(0), dwOpTime(0) { }

SGlobalSendItemLog::SGlobalSendItemLog(SGlobalSendItemLog&& src) : LogDataBase(src), strSendName(move(src.strSendName)), byStatus(src.byStatus), dwServerId(src.dwServerId), qwUserId(src.qwUserId), dwGold(src.dwGold), 
			dwCoupon(src.dwCoupon), dwSliver(src.dwSliver), dwHonor(src.dwHonor), strItemList(move(src.strItemList)), strReason(move(src.strReason)), 
			dwOpTime(src.dwOpTime) { }

SGlobalSendItemLog& SGlobalSendItemLog::operator=(SGlobalSendItemLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SGlobalSendItemLog();
		new (this) SGlobalSendItemLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGlobalSendItemLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.strSendName;
	src >> s.byStatus;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.dwGold;
	src >> s.dwCoupon;
	src >> s.dwSliver;
	src >> s.dwHonor;
	src >> s.strItemList;
	src >> s.strReason;
	src >> s.dwOpTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGlobalSendItemLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.strSendName;
	src << s.byStatus;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.dwGold;
	src << s.dwCoupon;
	src << s.dwSliver;
	src << s.dwHonor;
	src << s.strItemList;
	src << s.strReason;
	src << s.dwOpTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecGlobalSendItemLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGlobalSendItemLogPtr p(new SGlobalSendItemLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecGlobalSendItemLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGlobalSendItemLog& s)
{
	if(strcmp(rElement.Value(), "SGlobalSendItemLog") != 0)
	{
		LOG_CRI << "rElement is not SGlobalSendItemLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
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
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
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
		LOG_CRI << "pElemChild for dwSliver is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSliver") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSliver!";
		return false;
	}
	const char* pszVal_dwSliver = pElemChild->Attribute("value");
	if(pszVal_dwSliver == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSliver, s.dwSliver))
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
		LOG_CRI << "pElemChild for strItemList is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strItemList") != 0)
	{
		LOG_CRI << "Attribute: name is not strItemList!";
		return false;
	}
	const char* pszVal_strItemList = pElemChild->Attribute("value");
	if(pszVal_strItemList == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strItemList = pszVal_strItemList;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strReason is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strReason") != 0)
	{
		LOG_CRI << "Attribute: name is not strReason!";
		return false;
	}
	const char* pszVal_strReason = pElemChild->Attribute("value");
	if(pszVal_strReason == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strReason = pszVal_strReason;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOpTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOpTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOpTime!";
		return false;
	}
	const char* pszVal_dwOpTime = pElemChild->Attribute("value");
	if(pszVal_dwOpTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOpTime, s.dwOpTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGlobalSendItemLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGlobalSendItemLog");
	rElement.SetAttribute("type", ToUTF8Ptr("发送物品日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("发送人"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("大区"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_dwGold(new TiXmlElement("UINT32"));
	if(pElem_dwGold == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGold->SetAttribute("name", "dwGold");
	pElem_dwGold->SetAttribute("value", NumberToString(s.dwGold).c_str());
	pElem_dwGold->SetAttribute("comment", ToUTF8Ptr("仙石"));
	if(rElement.LinkEndChild(pElem_dwGold.get()) != NULL)
		pElem_dwGold.release();
	unique_ptr<TiXmlElement> pElem_dwCoupon(new TiXmlElement("UINT32"));
	if(pElem_dwCoupon == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCoupon->SetAttribute("name", "dwCoupon");
	pElem_dwCoupon->SetAttribute("value", NumberToString(s.dwCoupon).c_str());
	pElem_dwCoupon->SetAttribute("comment", ToUTF8Ptr("礼卷"));
	if(rElement.LinkEndChild(pElem_dwCoupon.get()) != NULL)
		pElem_dwCoupon.release();
	unique_ptr<TiXmlElement> pElem_dwSliver(new TiXmlElement("UINT32"));
	if(pElem_dwSliver == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSliver->SetAttribute("name", "dwSliver");
	pElem_dwSliver->SetAttribute("value", NumberToString(s.dwSliver).c_str());
	pElem_dwSliver->SetAttribute("comment", ToUTF8Ptr("银币"));
	if(rElement.LinkEndChild(pElem_dwSliver.get()) != NULL)
		pElem_dwSliver.release();
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
	unique_ptr<TiXmlElement> pElem_strItemList(new TiXmlElement("string"));
	if(pElem_strItemList == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strItemList->SetAttribute("name", "strItemList");
	pElem_strItemList->SetAttribute("value", s.strItemList.c_str());
	pElem_strItemList->SetAttribute("comment", ToUTF8Ptr("物品列表"));
	if(rElement.LinkEndChild(pElem_strItemList.get()) != NULL)
		pElem_strItemList.release();
	unique_ptr<TiXmlElement> pElem_strReason(new TiXmlElement("string"));
	if(pElem_strReason == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strReason->SetAttribute("name", "strReason");
	pElem_strReason->SetAttribute("value", s.strReason.c_str());
	pElem_strReason->SetAttribute("comment", ToUTF8Ptr("理由"));
	if(rElement.LinkEndChild(pElem_strReason.get()) != NULL)
		pElem_strReason.release();
	unique_ptr<TiXmlElement> pElem_dwOpTime(new TiXmlElement("UINT32"));
	if(pElem_dwOpTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOpTime->SetAttribute("name", "dwOpTime");
	pElem_dwOpTime->SetAttribute("value", NumberToString(s.dwOpTime).c_str());
	pElem_dwOpTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwOpTime.get()) != NULL)
		pElem_dwOpTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGlobalSendItemLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGlobalSendItemLogPtr p(new SGlobalSendItemLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecGlobalSendItemLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGlobalSendItemLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SQuesOptLog::SQuesOptLog() : byStatus(0), dwServerId(0), qwUserId(0), byOpType(0), wQuestType(0), 
			dwOpTime(0) { }

SQuesOptLog::SQuesOptLog(SQuesOptLog&& src) : LogDataBase(src), strSendName(move(src.strSendName)), byStatus(src.byStatus), dwServerId(src.dwServerId), qwUserId(src.qwUserId), byOpType(src.byOpType), 
			wQuestType(src.wQuestType), strQuestName(move(src.strQuestName)), dwOpTime(src.dwOpTime) { }

SQuesOptLog& SQuesOptLog::operator=(SQuesOptLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SQuesOptLog();
		new (this) SQuesOptLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SQuesOptLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.strSendName;
	src >> s.byStatus;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.byOpType;
	src >> s.wQuestType;
	src >> s.strQuestName;
	src >> s.dwOpTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SQuesOptLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.strSendName;
	src << s.byStatus;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.byOpType;
	src << s.wQuestType;
	src << s.strQuestName;
	src << s.dwOpTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecQuesOptLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SQuesOptLogPtr p(new SQuesOptLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecQuesOptLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SQuesOptLog& s)
{
	if(strcmp(rElement.Value(), "SQuesOptLog") != 0)
	{
		LOG_CRI << "rElement is not SQuesOptLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
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
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byOpType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byOpType") != 0)
	{
		LOG_CRI << "Attribute: name is not byOpType!";
		return false;
	}
	const char* pszVal_byOpType = pElemChild->Attribute("value");
	if(pszVal_byOpType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byOpType, s.byOpType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wQuestType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wQuestType") != 0)
	{
		LOG_CRI << "Attribute: name is not wQuestType!";
		return false;
	}
	const char* pszVal_wQuestType = pElemChild->Attribute("value");
	if(pszVal_wQuestType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wQuestType, s.wQuestType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strQuestName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strQuestName") != 0)
	{
		LOG_CRI << "Attribute: name is not strQuestName!";
		return false;
	}
	const char* pszVal_strQuestName = pElemChild->Attribute("value");
	if(pszVal_strQuestName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strQuestName = pszVal_strQuestName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOpTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOpTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOpTime!";
		return false;
	}
	const char* pszVal_dwOpTime = pElemChild->Attribute("value");
	if(pszVal_dwOpTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOpTime, s.dwOpTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SQuesOptLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SQuesOptLog");
	rElement.SetAttribute("type", ToUTF8Ptr("任务管理记录"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("操作人"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("大区"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_byOpType(new TiXmlElement("UINT8"));
	if(pElem_byOpType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byOpType->SetAttribute("name", "byOpType");
	pElem_byOpType->SetAttribute("value", NumberToString(s.byOpType).c_str());
	pElem_byOpType->SetAttribute("comment", ToUTF8Ptr("操作类型"));
	if(rElement.LinkEndChild(pElem_byOpType.get()) != NULL)
		pElem_byOpType.release();
	unique_ptr<TiXmlElement> pElem_wQuestType(new TiXmlElement("UINT16"));
	if(pElem_wQuestType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wQuestType->SetAttribute("name", "wQuestType");
	pElem_wQuestType->SetAttribute("value", NumberToString(s.wQuestType).c_str());
	pElem_wQuestType->SetAttribute("comment", ToUTF8Ptr("任务类型"));
	if(rElement.LinkEndChild(pElem_wQuestType.get()) != NULL)
		pElem_wQuestType.release();
	unique_ptr<TiXmlElement> pElem_strQuestName(new TiXmlElement("string"));
	if(pElem_strQuestName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strQuestName->SetAttribute("name", "strQuestName");
	pElem_strQuestName->SetAttribute("value", s.strQuestName.c_str());
	pElem_strQuestName->SetAttribute("comment", ToUTF8Ptr("任务名字"));
	if(rElement.LinkEndChild(pElem_strQuestName.get()) != NULL)
		pElem_strQuestName.release();
	unique_ptr<TiXmlElement> pElem_dwOpTime(new TiXmlElement("UINT32"));
	if(pElem_dwOpTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOpTime->SetAttribute("name", "dwOpTime");
	pElem_dwOpTime->SetAttribute("value", NumberToString(s.dwOpTime).c_str());
	pElem_dwOpTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwOpTime.get()) != NULL)
		pElem_dwOpTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecQuesOptLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SQuesOptLogPtr p(new SQuesOptLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecQuesOptLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SQuesOptLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SSendMailLog::SSendMailLog() : byStatus(0), dwServerId(0), qwUserId(0), dwOpTime(0) { }

SSendMailLog::SSendMailLog(SSendMailLog&& src) : LogDataBase(src), strSendName(move(src.strSendName)), byStatus(src.byStatus), dwServerId(src.dwServerId), qwUserId(src.qwUserId), strTitel(move(src.strTitel)), 
			strBody(move(src.strBody)), dwOpTime(src.dwOpTime) { }

SSendMailLog& SSendMailLog::operator=(SSendMailLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SSendMailLog();
		new (this) SSendMailLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SSendMailLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.strSendName;
	src >> s.byStatus;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.strTitel;
	src >> s.strBody;
	src >> s.dwOpTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSendMailLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.strSendName;
	src << s.byStatus;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.strTitel;
	src << s.strBody;
	src << s.dwOpTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSendMailLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SSendMailLogPtr p(new SSendMailLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSendMailLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSendMailLog& s)
{
	if(strcmp(rElement.Value(), "SSendMailLog") != 0)
	{
		LOG_CRI << "rElement is not SSendMailLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
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
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strTitel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strTitel") != 0)
	{
		LOG_CRI << "Attribute: name is not strTitel!";
		return false;
	}
	const char* pszVal_strTitel = pElemChild->Attribute("value");
	if(pszVal_strTitel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strTitel = pszVal_strTitel;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strBody is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strBody") != 0)
	{
		LOG_CRI << "Attribute: name is not strBody!";
		return false;
	}
	const char* pszVal_strBody = pElemChild->Attribute("value");
	if(pszVal_strBody == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strBody = pszVal_strBody;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOpTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOpTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOpTime!";
		return false;
	}
	const char* pszVal_dwOpTime = pElemChild->Attribute("value");
	if(pszVal_dwOpTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOpTime, s.dwOpTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSendMailLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSendMailLog");
	rElement.SetAttribute("type", ToUTF8Ptr("邮件发送日志"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("发送人"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("大区"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_strTitel(new TiXmlElement("string"));
	if(pElem_strTitel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strTitel->SetAttribute("name", "strTitel");
	pElem_strTitel->SetAttribute("value", s.strTitel.c_str());
	pElem_strTitel->SetAttribute("comment", ToUTF8Ptr("标题"));
	if(rElement.LinkEndChild(pElem_strTitel.get()) != NULL)
		pElem_strTitel.release();
	unique_ptr<TiXmlElement> pElem_strBody(new TiXmlElement("string"));
	if(pElem_strBody == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strBody->SetAttribute("name", "strBody");
	pElem_strBody->SetAttribute("value", s.strBody.c_str());
	pElem_strBody->SetAttribute("comment", ToUTF8Ptr("内容"));
	if(rElement.LinkEndChild(pElem_strBody.get()) != NULL)
		pElem_strBody.release();
	unique_ptr<TiXmlElement> pElem_dwOpTime(new TiXmlElement("UINT32"));
	if(pElem_dwOpTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOpTime->SetAttribute("name", "dwOpTime");
	pElem_dwOpTime->SetAttribute("value", NumberToString(s.dwOpTime).c_str());
	pElem_dwOpTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwOpTime.get()) != NULL)
		pElem_dwOpTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSendMailLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSendMailLogPtr p(new SSendMailLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecSendMailLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSendMailLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SVIPSendLog::SVIPSendLog() : byStatus(0), dwServerId(0), qwUserId(0), dwVIPLevel(0), dwOpTime(0) { }

SVIPSendLog::SVIPSendLog(SVIPSendLog&& src) : LogDataBase(src), strSendName(move(src.strSendName)), byStatus(src.byStatus), dwServerId(src.dwServerId), qwUserId(src.qwUserId), dwVIPLevel(src.dwVIPLevel), 
			strBody(move(src.strBody)), dwOpTime(src.dwOpTime) { }

SVIPSendLog& SVIPSendLog::operator=(SVIPSendLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SVIPSendLog();
		new (this) SVIPSendLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SVIPSendLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.strSendName;
	src >> s.byStatus;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.dwVIPLevel;
	src >> s.strBody;
	src >> s.dwOpTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SVIPSendLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.strSendName;
	src << s.byStatus;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.dwVIPLevel;
	src << s.strBody;
	src << s.dwOpTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecVIPSendLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SVIPSendLogPtr p(new SVIPSendLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecVIPSendLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SVIPSendLog& s)
{
	if(strcmp(rElement.Value(), "SVIPSendLog") != 0)
	{
		LOG_CRI << "rElement is not SVIPSendLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
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
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwVIPLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwVIPLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not dwVIPLevel!";
		return false;
	}
	const char* pszVal_dwVIPLevel = pElemChild->Attribute("value");
	if(pszVal_dwVIPLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwVIPLevel, s.dwVIPLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strBody is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strBody") != 0)
	{
		LOG_CRI << "Attribute: name is not strBody!";
		return false;
	}
	const char* pszVal_strBody = pElemChild->Attribute("value");
	if(pszVal_strBody == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strBody = pszVal_strBody;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOpTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOpTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOpTime!";
		return false;
	}
	const char* pszVal_dwOpTime = pElemChild->Attribute("value");
	if(pszVal_dwOpTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOpTime, s.dwOpTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SVIPSendLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SVIPSendLog");
	rElement.SetAttribute("type", ToUTF8Ptr("VIP物品发放记录"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("发送人"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("大区"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_dwVIPLevel(new TiXmlElement("UINT32"));
	if(pElem_dwVIPLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwVIPLevel->SetAttribute("name", "dwVIPLevel");
	pElem_dwVIPLevel->SetAttribute("value", NumberToString(s.dwVIPLevel).c_str());
	pElem_dwVIPLevel->SetAttribute("comment", ToUTF8Ptr("vip等级"));
	if(rElement.LinkEndChild(pElem_dwVIPLevel.get()) != NULL)
		pElem_dwVIPLevel.release();
	unique_ptr<TiXmlElement> pElem_strBody(new TiXmlElement("string"));
	if(pElem_strBody == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strBody->SetAttribute("name", "strBody");
	pElem_strBody->SetAttribute("value", s.strBody.c_str());
	pElem_strBody->SetAttribute("comment", ToUTF8Ptr("内容"));
	if(rElement.LinkEndChild(pElem_strBody.get()) != NULL)
		pElem_strBody.release();
	unique_ptr<TiXmlElement> pElem_dwOpTime(new TiXmlElement("UINT32"));
	if(pElem_dwOpTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOpTime->SetAttribute("name", "dwOpTime");
	pElem_dwOpTime->SetAttribute("value", NumberToString(s.dwOpTime).c_str());
	pElem_dwOpTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwOpTime.get()) != NULL)
		pElem_dwOpTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecVIPSendLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SVIPSendLogPtr p(new SVIPSendLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecVIPSendLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SVIPSendLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SActivityOpenLog::SActivityOpenLog() : byStatus(0), dwServerId(0), qwUserId(0), dwBeginTime(0), dwEndTime(0), 
			dwOpTime(0) { }

SActivityOpenLog::SActivityOpenLog(SActivityOpenLog&& src) : LogDataBase(src), strSendName(move(src.strSendName)), byStatus(src.byStatus), dwServerId(src.dwServerId), qwUserId(src.qwUserId), strActivityName(move(src.strActivityName)), 
			dwBeginTime(src.dwBeginTime), dwEndTime(src.dwEndTime), dwOpTime(src.dwOpTime) { }

SActivityOpenLog& SActivityOpenLog::operator=(SActivityOpenLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SActivityOpenLog();
		new (this) SActivityOpenLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SActivityOpenLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.strSendName;
	src >> s.byStatus;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.strActivityName;
	src >> s.dwBeginTime;
	src >> s.dwEndTime;
	src >> s.dwOpTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SActivityOpenLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.strSendName;
	src << s.byStatus;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.strActivityName;
	src << s.dwBeginTime;
	src << s.dwEndTime;
	src << s.dwOpTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecActivityOpenLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SActivityOpenLogPtr p(new SActivityOpenLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecActivityOpenLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SActivityOpenLog& s)
{
	if(strcmp(rElement.Value(), "SActivityOpenLog") != 0)
	{
		LOG_CRI << "rElement is not SActivityOpenLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
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
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strActivityName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strActivityName") != 0)
	{
		LOG_CRI << "Attribute: name is not strActivityName!";
		return false;
	}
	const char* pszVal_strActivityName = pElemChild->Attribute("value");
	if(pszVal_strActivityName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strActivityName = pszVal_strActivityName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBeginTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBeginTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBeginTime!";
		return false;
	}
	const char* pszVal_dwBeginTime = pElemChild->Attribute("value");
	if(pszVal_dwBeginTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBeginTime, s.dwBeginTime))
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOpTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOpTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOpTime!";
		return false;
	}
	const char* pszVal_dwOpTime = pElemChild->Attribute("value");
	if(pszVal_dwOpTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOpTime, s.dwOpTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SActivityOpenLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SActivityOpenLog");
	rElement.SetAttribute("type", ToUTF8Ptr("活动开启记录"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("发送人"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("大区"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_strActivityName(new TiXmlElement("string"));
	if(pElem_strActivityName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strActivityName->SetAttribute("name", "strActivityName");
	pElem_strActivityName->SetAttribute("value", s.strActivityName.c_str());
	pElem_strActivityName->SetAttribute("comment", ToUTF8Ptr("活动名称"));
	if(rElement.LinkEndChild(pElem_strActivityName.get()) != NULL)
		pElem_strActivityName.release();
	unique_ptr<TiXmlElement> pElem_dwBeginTime(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTime->SetAttribute("name", "dwBeginTime");
	pElem_dwBeginTime->SetAttribute("value", NumberToString(s.dwBeginTime).c_str());
	pElem_dwBeginTime->SetAttribute("comment", ToUTF8Ptr("开始时间"));
	if(rElement.LinkEndChild(pElem_dwBeginTime.get()) != NULL)
		pElem_dwBeginTime.release();
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
	unique_ptr<TiXmlElement> pElem_dwOpTime(new TiXmlElement("UINT32"));
	if(pElem_dwOpTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOpTime->SetAttribute("name", "dwOpTime");
	pElem_dwOpTime->SetAttribute("value", NumberToString(s.dwOpTime).c_str());
	pElem_dwOpTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwOpTime.get()) != NULL)
		pElem_dwOpTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecActivityOpenLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SActivityOpenLogPtr p(new SActivityOpenLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecActivityOpenLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SActivityOpenLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SDiscountItemLog::SDiscountItemLog() : byStatus(0), dwServerId(0), qwUserId(0), byType(0), dwBeginTime(0), 
			dwEndTime(0), dwOpTime(0) { }

SDiscountItemLog::SDiscountItemLog(SDiscountItemLog&& src) : LogDataBase(src), strSendName(move(src.strSendName)), byStatus(src.byStatus), dwServerId(src.dwServerId), qwUserId(src.qwUserId), byType(src.byType), 
			dwBeginTime(src.dwBeginTime), dwEndTime(src.dwEndTime), strItemList(move(src.strItemList)), dwOpTime(src.dwOpTime) { }

SDiscountItemLog& SDiscountItemLog::operator=(SDiscountItemLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SDiscountItemLog();
		new (this) SDiscountItemLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SDiscountItemLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.strSendName;
	src >> s.byStatus;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.byType;
	src >> s.dwBeginTime;
	src >> s.dwEndTime;
	src >> s.strItemList;
	src >> s.dwOpTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDiscountItemLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.strSendName;
	src << s.byStatus;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.byType;
	src << s.dwBeginTime;
	src << s.dwEndTime;
	src << s.strItemList;
	src << s.dwOpTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecDiscountItemLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SDiscountItemLogPtr p(new SDiscountItemLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecDiscountItemLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDiscountItemLog& s)
{
	if(strcmp(rElement.Value(), "SDiscountItemLog") != 0)
	{
		LOG_CRI << "rElement is not SDiscountItemLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
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
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byType") != 0)
	{
		LOG_CRI << "Attribute: name is not byType!";
		return false;
	}
	const char* pszVal_byType = pElemChild->Attribute("value");
	if(pszVal_byType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byType, s.byType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBeginTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBeginTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBeginTime!";
		return false;
	}
	const char* pszVal_dwBeginTime = pElemChild->Attribute("value");
	if(pszVal_dwBeginTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBeginTime, s.dwBeginTime))
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strItemList is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strItemList") != 0)
	{
		LOG_CRI << "Attribute: name is not strItemList!";
		return false;
	}
	const char* pszVal_strItemList = pElemChild->Attribute("value");
	if(pszVal_strItemList == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strItemList = pszVal_strItemList;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOpTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOpTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOpTime!";
		return false;
	}
	const char* pszVal_dwOpTime = pElemChild->Attribute("value");
	if(pszVal_dwOpTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOpTime, s.dwOpTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDiscountItemLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDiscountItemLog");
	rElement.SetAttribute("type", ToUTF8Ptr("限时限购配置记录"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("发送人"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("大区"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
	unique_ptr<TiXmlElement> pElem_byType(new TiXmlElement("UINT8"));
	if(pElem_byType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byType->SetAttribute("name", "byType");
	pElem_byType->SetAttribute("value", NumberToString(s.byType).c_str());
	pElem_byType->SetAttribute("comment", ToUTF8Ptr("类型"));
	if(rElement.LinkEndChild(pElem_byType.get()) != NULL)
		pElem_byType.release();
	unique_ptr<TiXmlElement> pElem_dwBeginTime(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTime->SetAttribute("name", "dwBeginTime");
	pElem_dwBeginTime->SetAttribute("value", NumberToString(s.dwBeginTime).c_str());
	pElem_dwBeginTime->SetAttribute("comment", ToUTF8Ptr("开始时间"));
	if(rElement.LinkEndChild(pElem_dwBeginTime.get()) != NULL)
		pElem_dwBeginTime.release();
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
	unique_ptr<TiXmlElement> pElem_strItemList(new TiXmlElement("string"));
	if(pElem_strItemList == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strItemList->SetAttribute("name", "strItemList");
	pElem_strItemList->SetAttribute("value", s.strItemList.c_str());
	pElem_strItemList->SetAttribute("comment", ToUTF8Ptr("物品列表"));
	if(rElement.LinkEndChild(pElem_strItemList.get()) != NULL)
		pElem_strItemList.release();
	unique_ptr<TiXmlElement> pElem_dwOpTime(new TiXmlElement("UINT32"));
	if(pElem_dwOpTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOpTime->SetAttribute("name", "dwOpTime");
	pElem_dwOpTime->SetAttribute("value", NumberToString(s.dwOpTime).c_str());
	pElem_dwOpTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwOpTime.get()) != NULL)
		pElem_dwOpTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDiscountItemLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDiscountItemLogPtr p(new SDiscountItemLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecDiscountItemLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDiscountItemLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SLevelChangeLog::SLevelChangeLog() : byStatus(0), dwServerId(0), qwUserId(0), byLevel(0), dwOpTime(0) { }

SLevelChangeLog::SLevelChangeLog(SLevelChangeLog&& src) : LogDataBase(src), strSendName(move(src.strSendName)), byStatus(src.byStatus), dwServerId(src.dwServerId), qwUserId(src.qwUserId), byLevel(src.byLevel), 
			dwOpTime(src.dwOpTime) { }

SLevelChangeLog& SLevelChangeLog::operator=(SLevelChangeLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SLevelChangeLog();
		new (this) SLevelChangeLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SLevelChangeLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (LogDataBase&)s;
	src >> s.strSendName;
	src >> s.byStatus;
	src >> s.dwServerId;
	src >> s.qwUserId;
	src >> s.byLevel;
	src >> s.dwOpTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SLevelChangeLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const LogDataBase&)s;
	src << s.strSendName;
	src << s.byStatus;
	src << s.dwServerId;
	src << s.qwUserId;
	src << s.byLevel;
	src << s.dwOpTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecLevelChangeLog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SLevelChangeLogPtr p(new SLevelChangeLog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecLevelChangeLog& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SLevelChangeLog& s)
{
	if(strcmp(rElement.Value(), "SLevelChangeLog") != 0)
	{
		LOG_CRI << "rElement is not SLevelChangeLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for LogDataBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (LogDataBase&)s))
	{
		LOG_CRI << "FromXML for: LogDataBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
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
		LOG_CRI << "pElemChild for dwServerId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwServerId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwServerId!";
		return false;
	}
	const char* pszVal_dwServerId = pElemChild->Attribute("value");
	if(pszVal_dwServerId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwServerId, s.dwServerId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserId!";
		return false;
	}
	const char* pszVal_qwUserId = pElemChild->Attribute("value");
	if(pszVal_qwUserId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserId, s.qwUserId))
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
		LOG_CRI << "pElemChild for dwOpTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOpTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOpTime!";
		return false;
	}
	const char* pszVal_dwOpTime = pElemChild->Attribute("value");
	if(pszVal_dwOpTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOpTime, s.dwOpTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SLevelChangeLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SLevelChangeLog");
	rElement.SetAttribute("type", ToUTF8Ptr("等级修改记录"));
	unique_ptr<TiXmlElement> pElem_LogDataBase(new TiXmlElement("LogDataBase"));
	if(pElem_LogDataBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const LogDataBase&)s, *pElem_LogDataBase))
	{
		LOG_CRI << "LogDataBase ToXML fails!";
		return false;
	}
	pElem_LogDataBase->SetAttribute("type", ToUTF8Ptr("日志数据基类"));
	pElem_LogDataBase->SetAttribute("comment", ToUTF8Ptr("父类LogDataBase部分"));
	if(rElement.LinkEndChild(pElem_LogDataBase.get()) != NULL)
		pElem_LogDataBase.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("发送人"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwServerId(new TiXmlElement("UINT32"));
	if(pElem_dwServerId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwServerId->SetAttribute("name", "dwServerId");
	pElem_dwServerId->SetAttribute("value", NumberToString(s.dwServerId).c_str());
	pElem_dwServerId->SetAttribute("comment", ToUTF8Ptr("大区"));
	if(rElement.LinkEndChild(pElem_dwServerId.get()) != NULL)
		pElem_dwServerId.release();
	unique_ptr<TiXmlElement> pElem_qwUserId(new TiXmlElement("UINT64"));
	if(pElem_qwUserId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserId->SetAttribute("name", "qwUserId");
	pElem_qwUserId->SetAttribute("value", NumberToString(s.qwUserId).c_str());
	pElem_qwUserId->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwUserId.get()) != NULL)
		pElem_qwUserId.release();
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
	unique_ptr<TiXmlElement> pElem_dwOpTime(new TiXmlElement("UINT32"));
	if(pElem_dwOpTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOpTime->SetAttribute("name", "dwOpTime");
	pElem_dwOpTime->SetAttribute("value", NumberToString(s.dwOpTime).c_str());
	pElem_dwOpTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwOpTime.get()) != NULL)
		pElem_dwOpTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecLevelChangeLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SLevelChangeLogPtr p(new SLevelChangeLog);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecLevelChangeLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SLevelChangeLog"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

} //namespace NLogDataDefine
