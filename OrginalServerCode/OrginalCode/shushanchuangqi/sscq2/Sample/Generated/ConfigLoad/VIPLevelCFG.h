// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SVIPLevelCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CVIPLEVELLOADER_H
#define _CVIPLEVELLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SVIPLevelCFG
{
	/**
	VIP等级
	**/
	UINT8	_Level;

	/**
	成长值
	**/
	UINT32	_Exp;

	/**
	每日礼包
	**/
	string	_DayPack;

	/**
	一次性奖励
	**/
	string	_Award;

	/**
	一次性奖励广告
描述
	**/
	string	_AssetDesc;

	/**
	登录提示气泡
	**/
	string	_Trailertxt;

	/**
	登录提示道具预览
	**/
	string	_TrailerItem;

	/**
	图片id
	**/
	string	_ImageId;

	/**
	仓库格数量
	**/
	UINT16	_StoreNum;

	/**
	好友上限增加
	**/
	UINT16	_FriendNum;

	/**
	世界boss自动战斗
	**/
	UINT16	_BossAuto;

	/**
	师门任务经验加成
	**/
	UINT16	_ShimenGet;

	/**
	衙门任务银币加成
	**/
	UINT16	_YamenGet;

	/**
	单日可购买师门次数
	**/
	UINT16	_ShimenTimes;

	/**
	单日可购买衙门次数
	**/
	UINT16	_YamenTimes;

	/**
	立刻完成师门衙门任务
	**/
	UINT16	_ShiyaLiKe;

	/**
	帮派篝火收益加成
	**/
	UINT16	_GuildFireGet;

	/**
	vip专属称号
	**/
	string	_Title;

	/**
	单日可购买体力次数
	**/
	UINT16	_DailyEnergyBoughtTimes;

	/**
	扫荡免费
	**/
	UINT16	_SaoDangFree;

	/**
	VIP经验副本
	**/
	string	_VipDundgnEXP;

	/**
	VIP修为副本
	**/
	string	_VipDundgnXiuwei;

	/**
	VIP材料副本
	**/
	string	_VipDundgnCailiao;

	/**
	副本通关奖励系数
	**/
	UINT16	_CopyFinishRewardC;

	/**
	历练额外购买挑战次数
	**/
	UINT16	_LilianBuy;

	/**
	历练挑战立刻冷却
	**/
	UINT16	_LilianCD;

	/**
	免费刷新挑战名单次数
	**/
	UINT16	_LilianFrush;

	/**
	斗剑挑战立刻冷却
	**/
	UINT16	_DoujianCD;

	/**
	打坐单次最大时间
	**/
	UINT16	_SitTimeMax;

	/**
	打坐收益加成
	**/
	UINT16	_SitAddition;

	/**
	VIP专属阵型
	**/
	string	_VIPFormation;

	/**
	VIP专属散仙
	**/
	string	_VIPHero;

	/**
	VIP专属阵灵
	**/
	string	_VIPPet;

	/**
	VIP专属时装
	**/
	string	_VIPFation;

	/**
	VIP专属坐骑
	**/
	string	_VIPHorse;

	/**
	VIP专属法宝
	**/
	string	_VIPTrump;

	/**
	VIP专属仙女
	**/
	string	_VIPBeauty;

	/**
	vip活跃宝箱
	**/
	string	_HuoyueAward;

	/**
	跳过战斗
	**/
	UINT16	_Tiaoguozhandou;

	/**
	九疑鼎加成
	**/
	UINT32	_StoveSpeeding;

	/**
	补签次数
	**/
	UINT16	_SignIn;

	/**
	可破阵眼次数
	**/
	UINT16	_BattleArrayTimes;

	/**
	可购买破阵眼次数
	**/
	UINT16	_BattleArrayBoughtTimes;

	/**
	英雄副本每个每日免费次数
	**/
	UINT16	_HeroDungeonFreeTimes;

	/**
	英雄副本每个每日可购买次数
	**/
	UINT16	_HeroDungeonBuyTimes;

	/**
	可直接召唤宝船
	**/
	UINT8	_ShipGet;

	/**
	守卫峨眉每日免费次数
	**/
	UINT8	_GuardEMeiTimes;

	/**
	守卫峨眉每日可购买次数
	**/
	UINT8	_GuardEMeiBuyingTimes;

	/**
	环任务自动五星
	**/
	UINT8	_CircleTaskMaxStar;

	/**
	历险副本每日次数
	**/
	UINT16	_AdventureDungeonFreeTimes;

	/**
	历险副本每日可购买次数
	**/
	UINT16	_AdventureDungeonBuyTimes;

	/**
	守卫峨眉扫荡免Cd
	**/
	UINT8	_GuardEMeiAutoNoCd;

	/**
	斗剑战败免Cd
	**/
	UINT8	_ArenaNoCd;

	/**
	每日斗剑次数
	**/
	UINT16	_ArenaTimes;

	/**
	斗剑每日可购买次数
	**/
	UINT16	_ArenaBoughtTimes;

	/**
	普通求签每日免费次数
	**/
	UINT16	_FreeDrawTimes;

	/**
	摇钱树购买次数
	**/
	UINT16	_MoneyTree;

	/**
	刷新宝船
	**/
	UINT8	_ShipRefresh;

	/**
	可购买运船次数
	**/
	UINT8	_ShipTime;

	/**
	圣陵进入次数
	**/
	UINT8	_RichTime;

	/**
	圣陵初始遥控色子卡数
	**/
	UINT8	_RichCtrlDiceTime;

	/**
	圣陵初始转向卡数
	**/
	UINT8	_RichComBackTime;

	/**
	圣陵初始生命
	**/
	UINT8	_RichLife;
}; // SVIPLevelCFG define end

//data loader for the excel table
class CVIPLevelLoader
{
public:
	std::vector<SVIPLevelCFG*> _vecData;

	~CVIPLevelLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

