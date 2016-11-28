/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    EventCenter.h
//  Purpose:      游戏事件枚举
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include <string>
#include <memory>
#include "ServerDefine.h"
#include "Archive.h"
#ifdef PROT_USE_XML
#include "tinyxml.h"
#endif

namespace NEventCenter
{

/////////////////////以下为类型定义/////////////////////
//事件类型枚举
enum EventType
{
	eEventType_PlayerLogin = 1, //登录【玩家登录游戏时】参数：1
	eEventType_GetResource = 2, //货币【玩家得到货币】参数：货币类型,得到数量，当前剩余值
	eEventType_SpendResource = 3, //货币【玩家消耗货币】参数：货币类型，消耗数量，当前剩余值
	eEventType_PackExpand = 100, //背包【成功扩展背包后】参数：累计扩展背包格数
	eEventType_PackItemSold = 101, //背包【出售物品成功后】参数：出售物品数量
	eEventType_PackArrange = 102, //背包【整理背包后】参数：整理背包次数
	eEventType_AchievementLevelUp = 201, //成就【成就等级升级后】参数：成就等级
	eEventType_AchievementGet = 202, //成就【成就达成时】参数：成就Id
	eEventType_PlayerLevelChanging = 301, //主角【主角等级发生变化】参数：主角等级
	eEventType_DungeonEnter = 401, //副本【进入副本】参数：副本id
	eEventType_DungeonFinish = 402, //副本【通关副本】参数：副本id，副本星级，战斗力，出战散仙id（副本id;副本星级;战斗力;出战散仙id,出战散仙id...）
	eEventType_DungeonLeave = 403, //副本【离开副本】参数：副本id，副本星级分别状态，装备阵灵id，出战散仙id，装备法宝id，战斗力
	eEventType_DungeonAutoFight = 404, //副本【副本扫荡】参数：副本id
	eEventType_DungeonStarGet = 405, //副本【通关获得星级时】参数：获得星级数
	eEventType_DungeonBattleWin = 406, //副本【副本中战斗胜利】参数：1
	eEventType_DungeonFinishAndAuto = 407, //副本【通关或扫荡副本后】参数：1
	eEventType_DungeonStar = 408, //副本【单人副本完成】参数：副本id,评价星级
	eEventType_DungeonFinishType = 409, //副本【副本通关或扫荡后】参数：副本类型,通关次数
	eEventType_DungeonVsMonster = 410, //副本【打怪物】参数：GroupID,胜负,string 玩家参数
	eEventType_DungeonFightMonster = 411, //副本【副本打怪物】参数：副本id,怪物id,玩家战斗力,胜负
	eEventType_DivisionFinish = 501, //师门【完成师门任务】参数：今日完成次数，师门任务品质
	eEventType_DivisionRefresh = 502, //师门【刷新师门任务】参数：免费刷新师门任务次数
	eEventType_DivisionRefreshGet = 503, //师门【刷新得到师门任务】参数：刷到的任务品质
	eEventType_DivisionBuying = 504, //师门【购买师门任务】参数：购买师门任务次数
	eEventType_DivisionLevelUp = 505, //师门【师门等级升级】参数：师门等级
	eEventType_DivisionPrizeGet = 506, //师门【领取清修奖励后】参数：1
	eEventType_GovernmentTaskFinish = 601, //衙门【完成衙门任务】参数：完成次数，品质
	eEventType_GovernmentTaskRefresh = 602, //衙门【刷新衙门任务】参数：刷新衙门任务次数
	eEventType_GovernmentTaskRefreshGet = 603, //衙门【刷新得到衙门任务】参数：刷到的任务品质
	eEventType_GovernmentTaskBuying = 604, //衙门【购买衙门任务】参数：购买衙门任务次数
	eEventType_GovernmentTaskLevelUp = 605, //衙门【衙门等级升级】参数：衙门等级
	eEventType_GovernmentTaskPrizeGet = 606, //衙门【领取侠义奖励】参数：1
	eEventType_GuildCreation = 701, //帮派【成功创建帮派】参数：帮派id
	eEventType_GuildJoining = 702, //帮派【成功加入帮派（含创建）】参数：帮派id，帮派等级
	eEventType_GuildDismiss = 703, //帮派【成功解散帮派】参数：帮派id
	eEventType_GuildQuit = 704, //帮派【成功退出帮派】参数：帮派id
	eEventType_GuildSetQQ = 705, //帮派【成功设置Q群】参数：帮派id，帮派Q群号码
	eEventType_GuildAccuse = 706, //帮派【成功弹劾】参数：帮派id
	eEventType_GuildLevel = 707, //帮派【帮派升级至x级】参数：帮派等级  string 帮派id，
	eEventType_GuildDonate = 708, //帮派【帮派捐献】参数：帮派当前资金，捐献银币数，获得贡献数，捐献银币数 string 帮派id
	eEventType_GuildBuildingUpgrade = 709, //帮派【帮派建筑升级】参数：帮派id，建筑id，建筑等级
	eEventType_GuildOblation = 710, //帮派【帮派供奉】参数：帮派id，供奉类型，当前供奉人数
	eEventType_GuildOblationSelf = 713, //帮派【自身帮派供奉】参数：供奉类型，累计次数
	eEventType_GuildShopBought = 711, //帮派【在帮派商店购买】参数：购买物品id，消耗帮贡
	eEventType_GuildSkillUpgrade = 712, //帮派【帮派技能升级】参数：帮派技能id，０（占位），所有帮派技能等级
	eEventType_RankFightingPowerChanging = 801, //排行榜【队伍战力排名发生改变、登录时】参数：战力排行值
	eEventType_RankPetChanging = 802, //排行榜【阵灵排名发生改变、登录时】参数：阵灵排行值
	eEventType_RankFighterChanging = 803, //排行榜【散仙战力排名发生改变、登录时】参数：散仙战力排行值
	eEventType_RankTrumpChanging = 804, //排行榜【法宝战力排名发生变化、登录时】参数：法宝战力排行值
	eEventType_PlayerProstrate = 805, //排行榜【进行崇拜】参数：今日崇拜次数
	eEventType_ReceiveProstrate = 806, //排行榜【受到崇拜、登录时】参数：今日受崇拜次数
	eEventType_ExperienceChallenge = 901, //历练【历练发起挑战】参数：今日历练挑战次数
	eEventType_ExperienceSectionChanging = 902, //历练【历练段位发生改变、登录时】参数：段位id
	eEventType_ExperienceRefresh = 903, //历练【历练刷新】参数：历练刷新次数
	eEventType_ExperienceTimesBought = 904, //历练【历练购买次数】参数：购买历练次数
	eEventType_ExperienceGetVictory = 905, //历练【历练获得胜利】参数：1
	eEventType_ExperienceGetPrize = 906, //历练【玩家领取历练奖励】参数：奖励类型
	eEventType_ExperienceLevelChange = 907, //历练等级发生变化【历练结算】参数： 初始段位，现在段位
	eEventType_ArenaRankChanging = 1001, //斗剑【斗剑排名发生变化、登录时】参数：斗剑最高排名
	eEventType_ArenaChallenge = 1002, //斗剑【斗剑发起挑战】参数：今日斗剑次数
	eEventType_ArenaGetVictory = 1003, //斗剑【斗剑胜利】参数：1
	eEventType_ArenaCancelRankBridge = 1004, //斗剑【玩家点击取消跨度】参数：1
	eEventType_ArenaGetPrize = 1005, //斗剑【玩家领取斗剑奖励】参数：奖励类型
	eEventType_ArenaRankDwon = 1006, //斗剑【玩家斗剑名次下降】参数：当前名次
	eEventType_ArenaRank = 1007, //斗剑【玩家斗剑】参数：今日斗剑次数,当前排名
	eEventType_ArenaBestRank = 1008, //斗剑【历史最高排名发生变化】参数：今日斗剑次数,当前排名
	eEventType_TeamBattleVictory = 1101, //组队副本【玩家通关组队副本】参数：组队副本id，通关类型（普通，协助），今日对应通关次数
	eEventType_DemonTowerBattle = 1201, //锁妖塔【进行锁妖塔战斗】参数：1
	eEventType_DemonTowerHighestChanging = 1202, //锁妖塔【玩家锁妖塔最高层数发生变化】参数：锁妖塔最高层数
	eEventType_DemonTowerDefendSuccess = 1203, //锁妖塔【玩家成功镇守锁妖塔】参数：镇守时间，魂魄id，获得数
	eEventType_DemonTowerRobSuccess = 1204, //锁妖塔【玩家成功抢夺锁妖塔】参数：获得奖励id，获得数
	eEventType_DemonTowerGetPrize = 1205, //锁妖塔【领取锁妖塔奖励、登录时】参数：1
	eEventType_DemonTowerRob = 1206, //锁妖塔【玩家进行抢夺】参数：1
	eEventType_DemonTowerClearPVECD = 1207, //锁妖塔【玩家清除打怪CD】参数：1
	eEventType_DemonTowerClearPVPCD = 1208, //锁妖塔【玩家清除抢人CD】参数：1
	eEventType_HolyLandJoin = 1301, //琅嬛福地【参加琅环福地】参数：1
	eEventType_HolyLandQuit = 1302, //琅嬛福地【结束琅环福地】参数：参加时间
	eEventType_HolyLandUseItem = 1303, //琅嬛福地【完成琅环福地物件交互】参数：交互技能id
	eEventType_WorldBossEnter = 1401, //世界BOSS【进入世界Boss活动】参数：Bossid
	eEventType_WorldBossKill = 1402, //世界BOSS【击杀世界Boss】参数：Bossid
	eEventType_WorldBossInspire = 1403, //世界BOSS【在世界Boss进行鼓舞】参数：鼓舞类型，当前鼓舞次数
	eEventType_WorldBossAttack = 1404, //世界BOSS【攻击世界Boss】参数
	eEventType_WorldBossAttackRightNow = 1405, //世界BOSS立即战斗【世界Boss立即战斗】参数1
	eEventType_WorldBossBuyLive = 1406, //世界BOSS买活【世界Boss买活】参数1
	eEventType_ShushanBattleJoin = 1501, //蜀山论剑【参加蜀山论剑】参数：1
	eEventType_ShushanBattleQuit = 1502, //蜀山论剑【离开蜀山论剑】参数：参加时间(暂时不做)
	eEventType_ShushanBattleVictory = 1503, //蜀山论剑【蜀山论剑获胜】参数：获胜次数，使用霸气、怒气技能id（多个）
	eEventType_ShushanBattleSkillUsing = 1504, //蜀山论剑【蜀山论剑使用技能】参数：技能id
	eEventType_ShushanBattleTaskFinish = 1505, //蜀山论剑【蜀山论剑完成任务】参数：今日完成次数，任务id
	eEventType_ShushanBattleWinStreak = 1506, //蜀山论剑【蜀山论剑胜利时】参数：当前连杀次数
	eEventType_ShushanBattleBadgeUpgrade = 1507, //蜀山论剑【蜀山论剑徽章等级提升】参数：当前徽章等级
	eEventType_ShushanBattleGetPrize = 1508, //蜀山论剑【蜀山论剑发奖励时】参数：奖励类型(1普通，2连杀，3荣誉王)
	eEventType_GuildBattleSignUp = 1601, //帮派战【帮派战报名】参数：帮派id（所有帮派id都是string类型不在参数列表）
	eEventType_GuildBattleOneRoundEnd = 1602, //帮派战【帮派战一轮结束】参数：帮派id，积分，对战帮派id，对战帮派积分，我的获胜场次
	eEventType_GuildBattleEnd = 1603, //帮派战【帮派战结束】参数：帮派id，参与时间
	eEventType_GuildBattleInspire = 1604, //帮派战【在帮派战中进行鼓舞】参数：鼓舞类型
	eEventType_GuildBattleWeekendEnd = 1605, //帮派战【帮派战周结束】参数：我的帮派排名
	eEventType_GuildBattleWin = 1606, //帮派战【帮派战胜利】
	eEventType_GuildBattleComboKill = 1607, //灵山争夺战【灵山争夺战连杀】参数：连杀次数
	eEventType_GuildBattleJoin = 1608, //灵山争夺战【参加帮派战】参数：连杀次数
	eEventType_FightingPowerChanging = 1701, //战斗力【进入战斗时】参数：队伍战力
	eEventType_FightingPowerChangingPlayer = 1702, //战斗力【进入战斗时】参数：主角战力
	eEventType_FightingPowerChangingAnyFigher = 1703, //战斗力【进入战斗】参数：出战散仙战力（4个）
	eEventType_FriendAdding = 1801, //好友【成功添加好友后】参数：好友数量
	eEventType_FriendRecommendUsing = 1802, //好友【使用好友推荐后】参数：1
	eEventType_FriendSignatureChangings = 1803, //好友【修改个性签名成功】参数：1
	eEventType_VipLevelChanging = 1901, //vip【Vip等级发生变化】参数：Vip等级
	eEventType_VipRechargeSuccess = 1902, //vip【玩家成功充值】参数：仙石数量
	eEventType_VipConsumptionSuccess = 1903, //vip【玩家成功消费】参数：仙石数量
	eEventType_VipGetPrize = 1904, //vip【玩家领取vip礼包】参数：礼包类型
	eEventType_VipGetPrizeMore = 1905, //vip【玩家领取vip礼包】参数：礼包类型1每日 2是一次性礼包，礼包等级
	eEventType_ActiveValueGetPrize = 2001, //活跃度【玩家领取活跃宝箱】参数：宝箱id，今日打开宝箱状态
	eEventType_ActivePointGet = 2002, //活跃度【获得活跃度】参数：活跃度值
	eEventType_FightingPowerComparing = 2101, //变强【玩家进行战力对比】参数：对比方式
	eEventType_MallBought = 2201, //商城【在商城进行购买】参数：商城类型，道具id，消耗数量，货币类型
	eEventType_MallBoughtMomey = 2202, //商城【在商城进行购买】参数：道具id，货币类型,货币数量
	eEventType_ExChangingMallBought = 2301, //兑换【完成兑换】参数：兑换次数，兑换类型，消耗数量，消耗类型
	eEventType_SettingsChanging = 2401, //设置【设置变更】参数：设置类型（设置面板，屏蔽）
	eEventType_SettingsFastShield = 2402, //设置【使用快速屏蔽】参数：1
	eEventType_SettingsFullScreen = 2403, //设置【使用全屏20分钟】参数：1
	eEventType_WorldMapMoving = 2501, //世界地图【进行世界地图传送】参数：1
	eEventType_MailReading = 2601, //邮件【邮件查看】参数：1
	eEventType_MailReceiving = 2602, //邮件【邮件接收附件】参数：1
	eEventType_SkillLearning = 2701, //技能【技能学习】参数：技能id
	eEventType_SkillEquiping = 2702, //技能【技能装备】参数：当前装备的技能id
	eEventType_SkillUpgrade = 2703, //技能【技能升级】参数：技能id，所有已学习技能等级
	eEventType_EquipmentStrengthening = 2801, //装备【完成装备强化】参数：装备类型，装备等级
	eEventType_EquipmentForging = 2802, //装备【完成装备铸造】参数：装备类型，装备等级
	eEventType_TrumpActive = 2901, //法宝【激活法宝】参数：法宝id
	eEventType_TrumpEquiping = 2902, //法宝【装备法宝】参数：所有装备的法宝id
	eEventType_TrumpForging = 2903, //法宝【完成法宝祭炼】参数：法宝id，祭炼次数，祭炼等级，其他所有拥有法宝的祭炼等级
	eEventType_FighterEnlisted = 3001, //散仙【招募散仙】参数：散仙id，当前已招募散仙数，招募散仙状态（散仙id;当前已招募散仙数;招募散仙id,招募散仙id...）
	eEventType_FighterLevelUp = 3002, //散仙【散仙升级】参数：散仙id，散仙等级，所有已招募散仙等级
	eEventType_FighterCuiTi = 3003, //散仙【散仙淬体】参数：散仙id，淬体类型，该散仙所有淬体类型的等级
	eEventType_FighterSkillUpgrade = 3004, //散仙【散仙技能升级】参数：散仙id，散仙技能id，该散仙所有技能等级
	eEventType_FighterSkillExchange = 3005, //散仙【散仙技能顺序调整】参数：散仙id，散仙技能顺序
	eEventType_FighterLearningRecipe = 3006, //散仙【散仙学习心法】参数：散仙id，心法id，散仙当前已学习心法数
	eEventType_FighterRecipeUpgrade = 3007, //散仙【散仙升级心法】参数：散仙id，心法id，该散仙所有心法等级
	eEventType_FormationActive = 3008, //散仙【激活阵型】参数：阵型id，当前已激活阵型数
	eEventType_FormationChange = 3009, //散仙【阵型调整】参数：所有出战散仙的id
	eEventType_PetActive = 3010, //散仙【激活阵灵】参数：阵灵id，当前已激活阵灵数
	eEventType_PetGetFighting = 3011, //散仙【出战阵灵】参数：阵灵id
	eEventType_FighterBatterPoint = 3012, //散仙【出战时战斗力】参数：散仙id，战斗力
	eEventType_FighterCollected = 3013, //散仙【招募指定品质散仙数量】参数：color,数量
	eEventType_FighterStarCollected = 3014, //散仙【招募指定星级散仙数量】参数：星级,数量
	eEventType_FighterInBattle = 3015, //散仙【上阵散仙数量-含主角】参数：数量
	eEventType_FormationChangeMore = 3016, //散仙【阵型详细调整】参数：所有出战散仙的id，位置id
	eEventType_FighterCombinationUnlock = 3017, //散仙【激活组合】参数：组合id
	eEventType_PetUpgrade = 3101, //阵灵【阵灵培养成功】参数：阵灵id，阵灵等级,所有已激活阵灵阶数
	eEventType_BeastSoulActive = 3102, //阵灵【兽魂激活】参数：兽魂id
	eEventType_BeastUpgrade = 3103, //阵灵【兽魂升级】参数：兽魂类型，等级,阶位,所有兽魂类型等级,阶位
	eEventType_BeastSoulGet = 3104, //兽魂【获得兽魂】参数：兽魂id，值
	eEventType_HorseActive = 3201, //坐骑【激活坐骑】参数：坐骑id，当前已激活坐骑数
	eEventType_HorseGetUsed = 3202, //坐骑【出战坐骑】参数：坐骑id
	eEventType_HorseUpgrade = 3203, //坐骑【坐骑进阶成功】参数：坐骑id，坐骑阶数，其他所有已激活坐骑阶数
	eEventType_PlayerLearningRecipe = 3301, //主角心法【主角学习心法】参数：心法id，主角当前已学习心法数
	eEventType_PlayerEquipingRecipe = 3302, //主角心法【主角装备心法】参数：心法id，主角当前所有装备心法id
	eEventType_PlayerRecipeUpgrade = 3303, //主角心法【主角心法升级】参数：心法id，所有已学习心法等级
	eEventType_PlayerDujieSuccess = 3401, //渡劫【主角或散仙渡劫成功】参数：单位id，渡劫等级，所有已招募散仙渡劫等级（渡劫散仙id;渡劫等级;散仙id,散仙等级$散仙id,散仙等级...）
	eEventType_OnlineTime = 3501, //在线【每在线1分钟时】参数：1
	eEventType_FaionActive = 3601, //时装【激活时装】参数：时装id，当前已激活时装数
	eEventType_FaionGetUsed = 3602, //时装【装备时装】参数：时装id
	eEventType_FaionUpgrade = 3603, //时装【时装炼化成功】参数：时装id，所有已激活时装阶数
	eEventType_StoveFireLearning = 3701, //九疑鼎【学会配方】参数：配方Id，配方可使用次数
	eEventType_StoveFireFinish = 3702, //九疑鼎【完成炼取】参数：配方Id，已领取次数，配方可使用次数
	eEventType_StoveUpgrade = 3703, //九疑鼎【九疑鼎培养成功】参数：九疑鼎Id，该九疑鼎阶数，所有九疑鼎阶数
	eEventType_StovePlayerHelp = 3704, //九疑鼎【进行九疑鼎协助】参数：1
	eEventType_StoveFighterHelp = 3705, //九疑鼎【进行散仙协助】参数：1
	eEventType_StoveBellow = 3706, //九疑鼎【进行九疑鼎煽火】参数：1
	eEventType_StoveComingIn = 3707, //九疑鼎【成功入鼎】参数：入鼎道具Id，入鼎道具数量
	eEventType_StoveFireStarting = 3708, //九疑鼎【祈火成功】参数：配方Id，火种品质，配方可使用次数
	eEventType_NewPlayerTask = 3801, //任务【新手引导】参数任务Id
	eEventType_NewPlayerClient = 3901, //任务【新手引导】参数 任务步骤string
	eEventType_CircleTaskFinish = 3921, //环任务【完成环任务】参数：次数
	eEventType_CircleTaskStarUp = 3922, //环任务【环任务升星】参数：星级, 升星次数
	eEventType_TravelFinish = 3941, //游历【完成游历】参数： 游历类型，游历次数
	eEventType_GuardEmeiFinish = 3946, //锁仙台【完成锁仙台】参数： 关卡Id
	eEventType_GuardEmeiFinishMore = 3947, //锁仙台战力【完成锁仙台】参数： 关卡Id,玩家战斗力
	eEventType_QQAlarmClock = 3949, //QQ闹钟【开启QQ闹钟】参数： 结果（1-开启成功 2-开启失败）
	eEventType_BeautyUnlock = 3950, //仙女【解锁仙女】参数： 仙女Id
	eEventType_BeautyUnlockNum = 3951, //仙女【解锁仙女数量】参数： 总数
	eEventType_BeautyHug = 3952, //仙女【完成缠绵】参数： 缠绵次数
	eEventType_BeautySend = 3953, //仙女【完成赠送】参数： 完成赠送仙女数量
	eEventType_BeautySendAppreciate = 3954, //仙女喜好品赠送【完成赠送】参数： 非喜欢礼物增加值，喜欢礼物增加值log
	eEventType_BeautyLevelUp = 3955, //仙女升级【仙女升级】参数： 美女id，美女等级
	eEventType_BattleArraySuccess = 3961, //破阵【成功破阵或完成扫荡】参数： 阵位Id，次数
	eEventType_BattleArraySuccessInfo = 3962, //破阵【成功破阵】参数： 阵位Id，战斗力
	eEventType_TreasureUseBuff = 3965, //寻宝【寻宝使用Buff】参数： BuffId，次数
	eEventType_TreasureSuccess = 3966, //寻宝【寻宝成功次数】参数： 关卡Id，次数
	eEventType_XinfaLearn = 3910, //心法【心法习得】参数： 心法id
	eEventType_XinfaLevelUp = 3911, //心法【心法升级】参数： 心法id,占位，等级
	eEventType_BoatFinish = 4001, //元江金船【完成运船】参数： 品质，次数
	eEventType_BoatRefresh = 4002, //元江金船【刷新得到船】参数： 品质，次数
	eEventType_BoatRob = 4003, //元江金船【打劫】参数： 结果（胜败 1-失败 2-胜利），次数
	eEventType_BoatProtect = 4004, //元江金船【护送】参数：次数
	eEventType_BoatBegin = 4005, //元江金船【开始运船】参数：1
	eEventType_BoatGet = 4006, //元江金船【获得宝船】参数：1
	eEventType_MoneyTree = 4010, //摇钱树【摇钱】参数： 次数
	eEventType_LingMountainSeize = 4020, //灵山争夺战【占领】参数： 灵山（峨嵋-1，昆仑-2，黄山-3），占领次数
	eEventType_LingMountainJoin = 4021, //灵山争夺战【参加】参数： 灵山（峨嵋-1，昆仑-2，黄山-3），参加次数
	eEventType_LingMountainConquer = 4022, //灵山争夺战【攻破山门】参数： 灵山（峨嵋-1，昆仑-2，黄山-3）,所用时间
	eEventType_LingMountainWin = 4023, //灵山争夺战【有帮派资源达到3000】参数： 内城（峨嵋洞-1，昆仑洞-2，黄山洞-3）,所用时间
	eEventType_GemsGet = 4031, //宝石【得到宝石】参数： 宝石类型，宝石等级
	eEventType_GemsSuit = 4032, //宝石【全身宝石等级】参数：散仙id，宝石等级,全身宝石等级（第三列）
	eEventType_GemsCompose = 4033, //宝石【宝石合成】参数：1
	eEventType_MysteryTreasureJoin = 4040, //秘境寻宝【参加秘境寻宝】参数： 1
	eEventType_MysteryTreasureBox = 4041, //秘境寻宝【获得秘境宝箱】参数： 1
	eEventType_MysteryTreasureWin = 4042, //秘境寻宝【和夺宝者战斗】参数：是否战胜，是宝匣持有者（1为是）
	eEventType_MysteryTreasureMove = 4043, //秘境寻宝【秘境寻宝中移动】参数：轮数
	eEventType_MysteryTreasureAliveTime = 4044, //秘境寻宝【秘境寻宝中失败】参数：存活回合数
	eEventType_MysteryTreasureReport = 4045, //秘境寻宝【秘境寻宝中结束】参数：获得宝箱数量，机缘值，存活回合数
	eEventType_QuestionJoin = 4050, //天问【参加天问】参数：1
	eEventType_QuestionUseSkill = 4051, //天问【天问中使用技能】参数：技能Id
	eEventType_QuestionScore = 4052, //天问【天问结束】参数：玩家积分
	eEventType_SkyTreasureJoin = 4055, //天赐宝藏【参加天赐宝藏】参数：1
	eEventType_SkyTreasureGet = 4056, //天赐宝藏【获得天赐宝藏】参数：宝箱Id
	eEventType_PlayerDraw = 4060, //求签【进行求签】参数：求签类型1银币2高级
	eEventType_GetEnergy = 4066, //仙气充盈【领取仙气充盈】参数：1
	eEventType_CheckIn = 4070, //签到【进行签到】参数：本月已签到次数
	eEventType_CheckInAdd = 4071, //签到【进行补签】参数：1
	eEventType_CheckInGetPrize = 4072, //签到【领取签到奖励】参数：奖励Id
	eEventType_MonthCard = 4076, //月卡【购买月卡】参数：1
	eEventType_MonthCardSend = 4077, //月卡【给他人赠送月卡】参数：1
	eEventType_14DaysGift = 4081, //14天礼包【领取14天礼包】参数：礼包Id
	eEventType_YellowDiamondNum = 4086, //黄钻玩家人数【创角成功】参数：1
	eEventType_YellowDiamondGift = 4087, //黄钻礼包【领取黄钻礼包】参数：礼包Id
	eEventType_SitDownTime = 4091, //上次打坐时间【完成打坐】参数：上次打坐时间
	eEventType_UsePromote = 4096, //使用变强功能【从变强界面打开其他界面】参数：1
	eEventType_QQAlarmGift = 5001, //QQ提醒礼包【领取QQ提醒礼包】参数：1
	eEventType_WeiBoGift = 5006, //微博礼包【领取微博礼包】参数：礼包Id
	eEventType_WeChatGift = 5007, //微信礼包【领取微信礼包】参数：礼包Id
	eEventType_FriendInviteGift = 5011, //邀请好友【领取邀请好友礼包】参数：礼包Id
	eEventType_XiHeTruck = 5012, //羲和神车帮助别人的次数【每当帮助别人完成装箱】 参数：1
	eEventType_TrumpGet = 4101, //新法宝【法宝、法宝碎片获得】参数：法宝、碎片id
	eEventType_TrumpEquip = 4102, //新法宝【法宝装备】参数：法宝id、散仙id，身上所有法宝id
	eEventType_TrumpToStrongSucess = 4103, //新法宝【法宝强化成功】参数：强化等级、强化石id、法宝id
	eEventType_TrumpToStrongFaild = 4104, //新法宝【法宝强化失败】参数：强化等级、强化石id、法宝id
	eEventType_TrumpPu = 4105, //新法宝【法宝洗炼】参数：保护个数、法宝id
	eEventType_TrumpDes = 4106, //新法宝【法宝分解】参数：法宝id、强化等级
	eEventType_ItemUpgrade = 4201, //合成【合成】参数：合成id
	eEventType_ShenglingPlay = 4301, //圣陵【掷骰子】参数：触发格子类型，格子id、当前层
	eEventType_ShenglingControl = 4302, //圣陵【遥控骰子】参数：触发格子类型，格子id、当前层
	eEventType_ShenglingReturn = 4303, //圣陵【转向】参数：格子id，当前层
	eEventType_ShenglingThreeGameOver = 4304, //圣陵【三消游戏结束】参数：玩家积分
	eEventType_ShenglingPuzzOver = 4305, //圣陵【拼图游戏结束】参数：拼图是否完成
	eEventType_Max //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EventType);
bool EnumStrToVal(const char*, EventType&);
#endif //PROT_USE_XML
const char* GetDescription(EventType);


} //namespace NEventCenter
