/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EventType.as
//  Purpose:      游戏事件枚举
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.eventCenter
 {
	import net.protocol.Message.ProtocolMessageProt256;
	/**
	 * 事件类型枚举
	 */
	public final class EventType
	{
		public static const eEventType_PlayerLogin:uint = 1; //登录【玩家登录游戏时】参数：1
		public static const eEventType_GetResource:uint = 2; //货币【玩家得到货币】参数：货币类型,得到数量，当前剩余值
		public static const eEventType_SpendResource:uint = 3; //货币【玩家消耗货币】参数：货币类型，消耗数量，当前剩余值
		public static const eEventType_PackExpand:uint = 100; //背包【成功扩展背包后】参数：累计扩展背包格数
		public static const eEventType_PackItemSold:uint = 101; //背包【出售物品成功后】参数：出售物品数量
		public static const eEventType_PackArrange:uint = 102; //背包【整理背包后】参数：整理背包次数
		public static const eEventType_AchievementLevelUp:uint = 201; //成就【成就等级升级后】参数：成就等级
		public static const eEventType_AchievementGet:uint = 202; //成就【成就达成时】参数：成就Id
		public static const eEventType_PlayerLevelChanging:uint = 301; //主角【主角等级发生变化】参数：主角等级
		public static const eEventType_DungeonEnter:uint = 401; //副本【进入副本】参数：副本id
		public static const eEventType_DungeonFinish:uint = 402; //副本【通关副本】参数：副本id，副本星级，战斗力，出战散仙id（副本id;副本星级;战斗力;出战散仙id,出战散仙id...）
		public static const eEventType_DungeonLeave:uint = 403; //副本【离开副本】参数：副本id，副本星级分别状态，装备阵灵id，出战散仙id，装备法宝id，战斗力
		public static const eEventType_DungeonAutoFight:uint = 404; //副本【副本扫荡】参数：副本id
		public static const eEventType_DungeonStarGet:uint = 405; //副本【通关获得星级时】参数：获得星级数
		public static const eEventType_DungeonBattleWin:uint = 406; //副本【副本中战斗胜利】参数：1
		public static const eEventType_DungeonFinishAndAuto:uint = 407; //副本【通关或扫荡副本后】参数：1
		public static const eEventType_DungeonStar:uint = 408; //副本【单人副本完成】参数：副本id,评价星级
		public static const eEventType_DungeonFinishType:uint = 409; //副本【副本通关或扫荡后】参数：副本类型,通关次数
		public static const eEventType_DungeonVsMonster:uint = 410; //副本【打怪物】参数：GroupID,胜负,string 玩家参数
		public static const eEventType_DungeonFightMonster:uint = 411; //副本【副本打怪物】参数：副本id,怪物id,玩家战斗力,胜负
		public static const eEventType_DivisionFinish:uint = 501; //师门【完成师门任务】参数：今日完成次数，师门任务品质
		public static const eEventType_DivisionRefresh:uint = 502; //师门【刷新师门任务】参数：免费刷新师门任务次数
		public static const eEventType_DivisionRefreshGet:uint = 503; //师门【刷新得到师门任务】参数：刷到的任务品质
		public static const eEventType_DivisionBuying:uint = 504; //师门【购买师门任务】参数：购买师门任务次数
		public static const eEventType_DivisionLevelUp:uint = 505; //师门【师门等级升级】参数：师门等级
		public static const eEventType_DivisionPrizeGet:uint = 506; //师门【领取清修奖励后】参数：1
		public static const eEventType_GovernmentTaskFinish:uint = 601; //衙门【完成衙门任务】参数：完成次数，品质
		public static const eEventType_GovernmentTaskRefresh:uint = 602; //衙门【刷新衙门任务】参数：刷新衙门任务次数
		public static const eEventType_GovernmentTaskRefreshGet:uint = 603; //衙门【刷新得到衙门任务】参数：刷到的任务品质
		public static const eEventType_GovernmentTaskBuying:uint = 604; //衙门【购买衙门任务】参数：购买衙门任务次数
		public static const eEventType_GovernmentTaskLevelUp:uint = 605; //衙门【衙门等级升级】参数：衙门等级
		public static const eEventType_GovernmentTaskPrizeGet:uint = 606; //衙门【领取侠义奖励】参数：1
		public static const eEventType_GuildCreation:uint = 701; //帮派【成功创建帮派】参数：帮派id
		public static const eEventType_GuildJoining:uint = 702; //帮派【成功加入帮派（含创建）】参数：帮派id，帮派等级
		public static const eEventType_GuildDismiss:uint = 703; //帮派【成功解散帮派】参数：帮派id
		public static const eEventType_GuildQuit:uint = 704; //帮派【成功退出帮派】参数：帮派id
		public static const eEventType_GuildSetQQ:uint = 705; //帮派【成功设置Q群】参数：帮派id，帮派Q群号码
		public static const eEventType_GuildAccuse:uint = 706; //帮派【成功弹劾】参数：帮派id
		public static const eEventType_GuildLevel:uint = 707; //帮派【帮派升级至x级】参数：帮派等级  string 帮派id，
		public static const eEventType_GuildDonate:uint = 708; //帮派【帮派捐献】参数：帮派当前资金，捐献银币数，获得贡献数，捐献银币数 string 帮派id
		public static const eEventType_GuildBuildingUpgrade:uint = 709; //帮派【帮派建筑升级】参数：帮派id，建筑id，建筑等级
		public static const eEventType_GuildOblation:uint = 710; //帮派【帮派供奉】参数：帮派id，供奉类型，当前供奉人数
		public static const eEventType_GuildOblationSelf:uint = 713; //帮派【自身帮派供奉】参数：供奉类型，累计次数
		public static const eEventType_GuildShopBought:uint = 711; //帮派【在帮派商店购买】参数：购买物品id，消耗帮贡
		public static const eEventType_GuildSkillUpgrade:uint = 712; //帮派【帮派技能升级】参数：帮派技能id，０（占位），所有帮派技能等级
		public static const eEventType_RankFightingPowerChanging:uint = 801; //排行榜【队伍战力排名发生改变、登录时】参数：战力排行值
		public static const eEventType_RankPetChanging:uint = 802; //排行榜【阵灵排名发生改变、登录时】参数：阵灵排行值
		public static const eEventType_RankFighterChanging:uint = 803; //排行榜【散仙战力排名发生改变、登录时】参数：散仙战力排行值
		public static const eEventType_RankTrumpChanging:uint = 804; //排行榜【法宝战力排名发生变化、登录时】参数：法宝战力排行值
		public static const eEventType_PlayerProstrate:uint = 805; //排行榜【进行崇拜】参数：今日崇拜次数
		public static const eEventType_ReceiveProstrate:uint = 806; //排行榜【受到崇拜、登录时】参数：今日受崇拜次数
		public static const eEventType_ExperienceChallenge:uint = 901; //历练【历练发起挑战】参数：今日历练挑战次数
		public static const eEventType_ExperienceSectionChanging:uint = 902; //历练【历练段位发生改变、登录时】参数：段位id
		public static const eEventType_ExperienceRefresh:uint = 903; //历练【历练刷新】参数：历练刷新次数
		public static const eEventType_ExperienceTimesBought:uint = 904; //历练【历练购买次数】参数：购买历练次数
		public static const eEventType_ExperienceGetVictory:uint = 905; //历练【历练获得胜利】参数：1
		public static const eEventType_ExperienceGetPrize:uint = 906; //历练【玩家领取历练奖励】参数：奖励类型
		public static const eEventType_ExperienceLevelChange:uint = 907; //历练等级发生变化【历练结算】参数： 初始段位，现在段位
		public static const eEventType_ArenaRankChanging:uint = 1001; //斗剑【斗剑排名发生变化、登录时】参数：斗剑最高排名
		public static const eEventType_ArenaChallenge:uint = 1002; //斗剑【斗剑发起挑战】参数：今日斗剑次数
		public static const eEventType_ArenaGetVictory:uint = 1003; //斗剑【斗剑胜利】参数：1
		public static const eEventType_ArenaCancelRankBridge:uint = 1004; //斗剑【玩家点击取消跨度】参数：1
		public static const eEventType_ArenaGetPrize:uint = 1005; //斗剑【玩家领取斗剑奖励】参数：奖励类型
		public static const eEventType_ArenaRankDwon:uint = 1006; //斗剑【玩家斗剑名次下降】参数：当前名次
		public static const eEventType_ArenaRank:uint = 1007; //斗剑【玩家斗剑】参数：今日斗剑次数,当前排名
		public static const eEventType_ArenaBestRank:uint = 1008; //斗剑【历史最高排名发生变化】参数：今日斗剑次数,当前排名
		public static const eEventType_TeamBattleVictory:uint = 1101; //组队副本【玩家通关组队副本】参数：组队副本id，通关类型（普通，协助），今日对应通关次数
		public static const eEventType_DemonTowerBattle:uint = 1201; //锁妖塔【进行锁妖塔战斗】参数：1
		public static const eEventType_DemonTowerHighestChanging:uint = 1202; //锁妖塔【玩家锁妖塔最高层数发生变化】参数：锁妖塔最高层数
		public static const eEventType_DemonTowerDefendSuccess:uint = 1203; //锁妖塔【玩家成功镇守锁妖塔】参数：镇守时间，魂魄id，获得数
		public static const eEventType_DemonTowerRobSuccess:uint = 1204; //锁妖塔【玩家成功抢夺锁妖塔】参数：获得奖励id，获得数
		public static const eEventType_DemonTowerGetPrize:uint = 1205; //锁妖塔【领取锁妖塔奖励、登录时】参数：1
		public static const eEventType_DemonTowerRob:uint = 1206; //锁妖塔【玩家进行抢夺】参数：1
		public static const eEventType_DemonTowerClearPVECD:uint = 1207; //锁妖塔【玩家清除打怪CD】参数：1
		public static const eEventType_DemonTowerClearPVPCD:uint = 1208; //锁妖塔【玩家清除抢人CD】参数：1
		public static const eEventType_HolyLandJoin:uint = 1301; //琅嬛福地【参加琅环福地】参数：1
		public static const eEventType_HolyLandQuit:uint = 1302; //琅嬛福地【结束琅环福地】参数：参加时间
		public static const eEventType_HolyLandUseItem:uint = 1303; //琅嬛福地【完成琅环福地物件交互】参数：交互技能id
		public static const eEventType_WorldBossEnter:uint = 1401; //世界BOSS【进入世界Boss活动】参数：Bossid
		public static const eEventType_WorldBossKill:uint = 1402; //世界BOSS【击杀世界Boss】参数：Bossid
		public static const eEventType_WorldBossInspire:uint = 1403; //世界BOSS【在世界Boss进行鼓舞】参数：鼓舞类型，当前鼓舞次数
		public static const eEventType_WorldBossAttack:uint = 1404; //世界BOSS【攻击世界Boss】参数
		public static const eEventType_WorldBossAttackRightNow:uint = 1405; //世界BOSS立即战斗【世界Boss立即战斗】参数1
		public static const eEventType_WorldBossBuyLive:uint = 1406; //世界BOSS买活【世界Boss买活】参数1
		public static const eEventType_ShushanBattleJoin:uint = 1501; //蜀山论剑【参加蜀山论剑】参数：1
		public static const eEventType_ShushanBattleQuit:uint = 1502; //蜀山论剑【离开蜀山论剑】参数：参加时间(暂时不做)
		public static const eEventType_ShushanBattleVictory:uint = 1503; //蜀山论剑【蜀山论剑获胜】参数：获胜次数，使用霸气、怒气技能id（多个）
		public static const eEventType_ShushanBattleSkillUsing:uint = 1504; //蜀山论剑【蜀山论剑使用技能】参数：技能id
		public static const eEventType_ShushanBattleTaskFinish:uint = 1505; //蜀山论剑【蜀山论剑完成任务】参数：今日完成次数，任务id
		public static const eEventType_ShushanBattleWinStreak:uint = 1506; //蜀山论剑【蜀山论剑胜利时】参数：当前连杀次数
		public static const eEventType_ShushanBattleBadgeUpgrade:uint = 1507; //蜀山论剑【蜀山论剑徽章等级提升】参数：当前徽章等级
		public static const eEventType_ShushanBattleGetPrize:uint = 1508; //蜀山论剑【蜀山论剑发奖励时】参数：奖励类型(1普通，2连杀，3荣誉王)
		public static const eEventType_GuildBattleSignUp:uint = 1601; //帮派战【帮派战报名】参数：帮派id（所有帮派id都是string类型不在参数列表）
		public static const eEventType_GuildBattleOneRoundEnd:uint = 1602; //帮派战【帮派战一轮结束】参数：帮派id，积分，对战帮派id，对战帮派积分，我的获胜场次
		public static const eEventType_GuildBattleEnd:uint = 1603; //帮派战【帮派战结束】参数：帮派id，参与时间
		public static const eEventType_GuildBattleInspire:uint = 1604; //帮派战【在帮派战中进行鼓舞】参数：鼓舞类型
		public static const eEventType_GuildBattleWeekendEnd:uint = 1605; //帮派战【帮派战周结束】参数：我的帮派排名
		public static const eEventType_GuildBattleWin:uint = 1606; //帮派战【帮派战胜利】
		public static const eEventType_GuildBattleComboKill:uint = 1607; //灵山争夺战【灵山争夺战连杀】参数：连杀次数
		public static const eEventType_GuildBattleJoin:uint = 1608; //灵山争夺战【参加帮派战】参数：连杀次数
		public static const eEventType_FightingPowerChanging:uint = 1701; //战斗力【进入战斗时】参数：队伍战力
		public static const eEventType_FightingPowerChangingPlayer:uint = 1702; //战斗力【进入战斗时】参数：主角战力
		public static const eEventType_FightingPowerChangingAnyFigher:uint = 1703; //战斗力【进入战斗】参数：出战散仙战力（4个）
		public static const eEventType_FriendAdding:uint = 1801; //好友【成功添加好友后】参数：好友数量
		public static const eEventType_FriendRecommendUsing:uint = 1802; //好友【使用好友推荐后】参数：1
		public static const eEventType_FriendSignatureChangings:uint = 1803; //好友【修改个性签名成功】参数：1
		public static const eEventType_VipLevelChanging:uint = 1901; //vip【Vip等级发生变化】参数：Vip等级
		public static const eEventType_VipRechargeSuccess:uint = 1902; //vip【玩家成功充值】参数：仙石数量
		public static const eEventType_VipConsumptionSuccess:uint = 1903; //vip【玩家成功消费】参数：仙石数量
		public static const eEventType_VipGetPrize:uint = 1904; //vip【玩家领取vip礼包】参数：礼包类型
		public static const eEventType_VipGetPrizeMore:uint = 1905; //vip【玩家领取vip礼包】参数：礼包类型1每日 2是一次性礼包，礼包等级
		public static const eEventType_ActiveValueGetPrize:uint = 2001; //活跃度【玩家领取活跃宝箱】参数：宝箱id，今日打开宝箱状态
		public static const eEventType_ActivePointGet:uint = 2002; //活跃度【获得活跃度】参数：活跃度值
		public static const eEventType_FightingPowerComparing:uint = 2101; //变强【玩家进行战力对比】参数：对比方式
		public static const eEventType_MallBought:uint = 2201; //商城【在商城进行购买】参数：商城类型，道具id，消耗数量，货币类型
		public static const eEventType_MallBoughtMomey:uint = 2202; //商城【在商城进行购买】参数：道具id，货币类型,货币数量
		public static const eEventType_ExChangingMallBought:uint = 2301; //兑换【完成兑换】参数：兑换次数，兑换类型，消耗数量，消耗类型
		public static const eEventType_SettingsChanging:uint = 2401; //设置【设置变更】参数：设置类型（设置面板，屏蔽）
		public static const eEventType_SettingsFastShield:uint = 2402; //设置【使用快速屏蔽】参数：1
		public static const eEventType_SettingsFullScreen:uint = 2403; //设置【使用全屏20分钟】参数：1
		public static const eEventType_WorldMapMoving:uint = 2501; //世界地图【进行世界地图传送】参数：1
		public static const eEventType_MailReading:uint = 2601; //邮件【邮件查看】参数：1
		public static const eEventType_MailReceiving:uint = 2602; //邮件【邮件接收附件】参数：1
		public static const eEventType_SkillLearning:uint = 2701; //技能【技能学习】参数：技能id
		public static const eEventType_SkillEquiping:uint = 2702; //技能【技能装备】参数：当前装备的技能id
		public static const eEventType_SkillUpgrade:uint = 2703; //技能【技能升级】参数：技能id，所有已学习技能等级
		public static const eEventType_EquipmentStrengthening:uint = 2801; //装备【完成装备强化】参数：装备类型，装备等级
		public static const eEventType_EquipmentForging:uint = 2802; //装备【完成装备铸造】参数：装备类型，装备等级
		public static const eEventType_TrumpActive:uint = 2901; //法宝【激活法宝】参数：法宝id
		public static const eEventType_TrumpEquiping:uint = 2902; //法宝【装备法宝】参数：所有装备的法宝id
		public static const eEventType_TrumpForging:uint = 2903; //法宝【完成法宝祭炼】参数：法宝id，祭炼次数，祭炼等级，其他所有拥有法宝的祭炼等级
		public static const eEventType_FighterEnlisted:uint = 3001; //散仙【招募散仙】参数：散仙id，当前已招募散仙数，招募散仙状态（散仙id;当前已招募散仙数;招募散仙id,招募散仙id...）
		public static const eEventType_FighterLevelUp:uint = 3002; //散仙【散仙升级】参数：散仙id，散仙等级，所有已招募散仙等级
		public static const eEventType_FighterCuiTi:uint = 3003; //散仙【散仙淬体】参数：散仙id，淬体类型，该散仙所有淬体类型的等级
		public static const eEventType_FighterSkillUpgrade:uint = 3004; //散仙【散仙技能升级】参数：散仙id，散仙技能id，该散仙所有技能等级
		public static const eEventType_FighterSkillExchange:uint = 3005; //散仙【散仙技能顺序调整】参数：散仙id，散仙技能顺序
		public static const eEventType_FighterLearningRecipe:uint = 3006; //散仙【散仙学习心法】参数：散仙id，心法id，散仙当前已学习心法数
		public static const eEventType_FighterRecipeUpgrade:uint = 3007; //散仙【散仙升级心法】参数：散仙id，心法id，该散仙所有心法等级
		public static const eEventType_FormationActive:uint = 3008; //散仙【激活阵型】参数：阵型id，当前已激活阵型数
		public static const eEventType_FormationChange:uint = 3009; //散仙【阵型调整】参数：所有出战散仙的id
		public static const eEventType_PetActive:uint = 3010; //散仙【激活阵灵】参数：阵灵id，当前已激活阵灵数
		public static const eEventType_PetGetFighting:uint = 3011; //散仙【出战阵灵】参数：阵灵id
		public static const eEventType_FighterBatterPoint:uint = 3012; //散仙【出战时战斗力】参数：散仙id，战斗力
		public static const eEventType_FighterCollected:uint = 3013; //散仙【招募指定品质散仙数量】参数：color,数量
		public static const eEventType_FighterStarCollected:uint = 3014; //散仙【招募指定星级散仙数量】参数：星级,数量
		public static const eEventType_FighterInBattle:uint = 3015; //散仙【上阵散仙数量-含主角】参数：数量
		public static const eEventType_FormationChangeMore:uint = 3016; //散仙【阵型详细调整】参数：所有出战散仙的id，位置id
		public static const eEventType_FighterCombinationUnlock:uint = 3017; //散仙【激活组合】参数：组合id
		public static const eEventType_PetUpgrade:uint = 3101; //阵灵【阵灵培养成功】参数：阵灵id，阵灵等级,所有已激活阵灵阶数
		public static const eEventType_BeastSoulActive:uint = 3102; //阵灵【兽魂激活】参数：兽魂id
		public static const eEventType_BeastUpgrade:uint = 3103; //阵灵【兽魂升级】参数：兽魂类型，等级,阶位,所有兽魂类型等级,阶位
		public static const eEventType_BeastSoulGet:uint = 3104; //兽魂【获得兽魂】参数：兽魂id，值
		public static const eEventType_HorseActive:uint = 3201; //坐骑【激活坐骑】参数：坐骑id，当前已激活坐骑数
		public static const eEventType_HorseGetUsed:uint = 3202; //坐骑【出战坐骑】参数：坐骑id
		public static const eEventType_HorseUpgrade:uint = 3203; //坐骑【坐骑进阶成功】参数：坐骑id，坐骑阶数，其他所有已激活坐骑阶数
		public static const eEventType_PlayerLearningRecipe:uint = 3301; //主角心法【主角学习心法】参数：心法id，主角当前已学习心法数
		public static const eEventType_PlayerEquipingRecipe:uint = 3302; //主角心法【主角装备心法】参数：心法id，主角当前所有装备心法id
		public static const eEventType_PlayerRecipeUpgrade:uint = 3303; //主角心法【主角心法升级】参数：心法id，所有已学习心法等级
		public static const eEventType_PlayerDujieSuccess:uint = 3401; //渡劫【主角或散仙渡劫成功】参数：单位id，渡劫等级，所有已招募散仙渡劫等级（渡劫散仙id;渡劫等级;散仙id,散仙等级$散仙id,散仙等级...）
		public static const eEventType_OnlineTime:uint = 3501; //在线【每在线1分钟时】参数：1
		public static const eEventType_FaionActive:uint = 3601; //时装【激活时装】参数：时装id，当前已激活时装数
		public static const eEventType_FaionGetUsed:uint = 3602; //时装【装备时装】参数：时装id
		public static const eEventType_FaionUpgrade:uint = 3603; //时装【时装炼化成功】参数：时装id，所有已激活时装阶数
		public static const eEventType_StoveFireLearning:uint = 3701; //九疑鼎【学会配方】参数：配方Id，配方可使用次数
		public static const eEventType_StoveFireFinish:uint = 3702; //九疑鼎【完成炼取】参数：配方Id，已领取次数，配方可使用次数
		public static const eEventType_StoveUpgrade:uint = 3703; //九疑鼎【九疑鼎培养成功】参数：九疑鼎Id，该九疑鼎阶数，所有九疑鼎阶数
		public static const eEventType_StovePlayerHelp:uint = 3704; //九疑鼎【进行九疑鼎协助】参数：1
		public static const eEventType_StoveFighterHelp:uint = 3705; //九疑鼎【进行散仙协助】参数：1
		public static const eEventType_StoveBellow:uint = 3706; //九疑鼎【进行九疑鼎煽火】参数：1
		public static const eEventType_StoveComingIn:uint = 3707; //九疑鼎【成功入鼎】参数：入鼎道具Id，入鼎道具数量
		public static const eEventType_StoveFireStarting:uint = 3708; //九疑鼎【祈火成功】参数：配方Id，火种品质，配方可使用次数
		public static const eEventType_NewPlayerTask:uint = 3801; //任务【新手引导】参数任务Id
		public static const eEventType_NewPlayerClient:uint = 3901; //任务【新手引导】参数 任务步骤string
		public static const eEventType_CircleTaskFinish:uint = 3921; //环任务【完成环任务】参数：次数
		public static const eEventType_CircleTaskStarUp:uint = 3922; //环任务【环任务升星】参数：星级, 升星次数
		public static const eEventType_TravelFinish:uint = 3941; //游历【完成游历】参数： 游历类型，游历次数
		public static const eEventType_GuardEmeiFinish:uint = 3946; //锁仙台【完成锁仙台】参数： 关卡Id
		public static const eEventType_GuardEmeiFinishMore:uint = 3947; //锁仙台战力【完成锁仙台】参数： 关卡Id,玩家战斗力
		public static const eEventType_QQAlarmClock:uint = 3949; //QQ闹钟【开启QQ闹钟】参数： 结果（1-开启成功 2-开启失败）
		public static const eEventType_BeautyUnlock:uint = 3950; //仙女【解锁仙女】参数： 仙女Id
		public static const eEventType_BeautyUnlockNum:uint = 3951; //仙女【解锁仙女数量】参数： 总数
		public static const eEventType_BeautyHug:uint = 3952; //仙女【完成缠绵】参数： 缠绵次数
		public static const eEventType_BeautySend:uint = 3953; //仙女【完成赠送】参数： 完成赠送仙女数量
		public static const eEventType_BeautySendAppreciate:uint = 3954; //仙女喜好品赠送【完成赠送】参数： 非喜欢礼物增加值，喜欢礼物增加值log
		public static const eEventType_BeautyLevelUp:uint = 3955; //仙女升级【仙女升级】参数： 美女id，美女等级
		public static const eEventType_BattleArraySuccess:uint = 3961; //破阵【成功破阵或完成扫荡】参数： 阵位Id，次数
		public static const eEventType_BattleArraySuccessInfo:uint = 3962; //破阵【成功破阵】参数： 阵位Id，战斗力
		public static const eEventType_TreasureUseBuff:uint = 3965; //寻宝【寻宝使用Buff】参数： BuffId，次数
		public static const eEventType_TreasureSuccess:uint = 3966; //寻宝【寻宝成功次数】参数： 关卡Id，次数
		public static const eEventType_XinfaLearn:uint = 3910; //心法【心法习得】参数： 心法id
		public static const eEventType_XinfaLevelUp:uint = 3911; //心法【心法升级】参数： 心法id,占位，等级
		public static const eEventType_BoatFinish:uint = 4001; //元江金船【完成运船】参数： 品质，次数
		public static const eEventType_BoatRefresh:uint = 4002; //元江金船【刷新得到船】参数： 品质，次数
		public static const eEventType_BoatRob:uint = 4003; //元江金船【打劫】参数： 结果（胜败 1-失败 2-胜利），次数
		public static const eEventType_BoatProtect:uint = 4004; //元江金船【护送】参数：次数
		public static const eEventType_BoatBegin:uint = 4005; //元江金船【开始运船】参数：1
		public static const eEventType_BoatGet:uint = 4006; //元江金船【获得宝船】参数：1
		public static const eEventType_MoneyTree:uint = 4010; //摇钱树【摇钱】参数： 次数
		public static const eEventType_LingMountainSeize:uint = 4020; //灵山争夺战【占领】参数： 灵山（峨嵋-1，昆仑-2，黄山-3），占领次数
		public static const eEventType_LingMountainJoin:uint = 4021; //灵山争夺战【参加】参数： 灵山（峨嵋-1，昆仑-2，黄山-3），参加次数
		public static const eEventType_LingMountainConquer:uint = 4022; //灵山争夺战【攻破山门】参数： 灵山（峨嵋-1，昆仑-2，黄山-3）,所用时间
		public static const eEventType_LingMountainWin:uint = 4023; //灵山争夺战【有帮派资源达到3000】参数： 内城（峨嵋洞-1，昆仑洞-2，黄山洞-3）,所用时间
		public static const eEventType_GemsGet:uint = 4031; //宝石【得到宝石】参数： 宝石类型，宝石等级
		public static const eEventType_GemsSuit:uint = 4032; //宝石【全身宝石等级】参数：散仙id，宝石等级,全身宝石等级（第三列）
		public static const eEventType_GemsCompose:uint = 4033; //宝石【宝石合成】参数：1
		public static const eEventType_MysteryTreasureJoin:uint = 4040; //秘境寻宝【参加秘境寻宝】参数： 1
		public static const eEventType_MysteryTreasureBox:uint = 4041; //秘境寻宝【获得秘境宝箱】参数： 1
		public static const eEventType_MysteryTreasureWin:uint = 4042; //秘境寻宝【和夺宝者战斗】参数：是否战胜，是宝匣持有者（1为是）
		public static const eEventType_MysteryTreasureMove:uint = 4043; //秘境寻宝【秘境寻宝中移动】参数：轮数
		public static const eEventType_MysteryTreasureAliveTime:uint = 4044; //秘境寻宝【秘境寻宝中失败】参数：存活回合数
		public static const eEventType_MysteryTreasureReport:uint = 4045; //秘境寻宝【秘境寻宝中结束】参数：获得宝箱数量，机缘值，存活回合数
		public static const eEventType_QuestionJoin:uint = 4050; //天问【参加天问】参数：1
		public static const eEventType_QuestionUseSkill:uint = 4051; //天问【天问中使用技能】参数：技能Id
		public static const eEventType_QuestionScore:uint = 4052; //天问【天问结束】参数：玩家积分
		public static const eEventType_SkyTreasureJoin:uint = 4055; //天赐宝藏【参加天赐宝藏】参数：1
		public static const eEventType_SkyTreasureGet:uint = 4056; //天赐宝藏【获得天赐宝藏】参数：宝箱Id
		public static const eEventType_PlayerDraw:uint = 4060; //求签【进行求签】参数：求签类型1银币2高级
		public static const eEventType_GetEnergy:uint = 4066; //仙气充盈【领取仙气充盈】参数：1
		public static const eEventType_CheckIn:uint = 4070; //签到【进行签到】参数：本月已签到次数
		public static const eEventType_CheckInAdd:uint = 4071; //签到【进行补签】参数：1
		public static const eEventType_CheckInGetPrize:uint = 4072; //签到【领取签到奖励】参数：奖励Id
		public static const eEventType_MonthCard:uint = 4076; //月卡【购买月卡】参数：1
		public static const eEventType_MonthCardSend:uint = 4077; //月卡【给他人赠送月卡】参数：1
		public static const eEventType_14DaysGift:uint = 4081; //14天礼包【领取14天礼包】参数：礼包Id
		public static const eEventType_YellowDiamondNum:uint = 4086; //黄钻玩家人数【创角成功】参数：1
		public static const eEventType_YellowDiamondGift:uint = 4087; //黄钻礼包【领取黄钻礼包】参数：礼包Id
		public static const eEventType_SitDownTime:uint = 4091; //上次打坐时间【完成打坐】参数：上次打坐时间
		public static const eEventType_UsePromote:uint = 4096; //使用变强功能【从变强界面打开其他界面】参数：1
		public static const eEventType_QQAlarmGift:uint = 5001; //QQ提醒礼包【领取QQ提醒礼包】参数：1
		public static const eEventType_WeiBoGift:uint = 5006; //微博礼包【领取微博礼包】参数：礼包Id
		public static const eEventType_WeChatGift:uint = 5007; //微信礼包【领取微信礼包】参数：礼包Id
		public static const eEventType_FriendInviteGift:uint = 5011; //邀请好友【领取邀请好友礼包】参数：礼包Id
		public static const eEventType_XiHeTruck:uint = 5012; //羲和神车帮助别人的次数【每当帮助别人完成装箱】 参数：1
		public static const eEventType_TrumpGet:uint = 4101; //新法宝【法宝、法宝碎片获得】参数：法宝、碎片id
		public static const eEventType_TrumpEquip:uint = 4102; //新法宝【法宝装备】参数：法宝id、散仙id，身上所有法宝id
		public static const eEventType_TrumpToStrongSucess:uint = 4103; //新法宝【法宝强化成功】参数：强化等级、强化石id、法宝id
		public static const eEventType_TrumpToStrongFaild:uint = 4104; //新法宝【法宝强化失败】参数：强化等级、强化石id、法宝id
		public static const eEventType_TrumpPu:uint = 4105; //新法宝【法宝洗炼】参数：保护个数、法宝id
		public static const eEventType_TrumpDes:uint = 4106; //新法宝【法宝分解】参数：法宝id、强化等级
		public static const eEventType_ItemUpgrade:uint = 4201; //合成【合成】参数：合成id
		public static const eEventType_ShenglingPlay:uint = 4301; //圣陵【掷骰子】参数：触发格子类型，格子id、当前层
		public static const eEventType_ShenglingControl:uint = 4302; //圣陵【遥控骰子】参数：触发格子类型，格子id、当前层
		public static const eEventType_ShenglingReturn:uint = 4303; //圣陵【转向】参数：格子id，当前层
		public static const eEventType_ShenglingThreeGameOver:uint = 4304; //圣陵【三消游戏结束】参数：玩家积分
		public static const eEventType_ShenglingPuzzOver:uint = 4305; //圣陵【拼图游戏结束】参数：拼图是否完成
		public static const eEventType_Max:uint = 4306; //最大值
		public static const end:uint = eEventType_XiHeTruck;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eEventType_PlayerLogin:
					return ProtocolMessageProt256.eEventType_PlayerLogin;
				case eEventType_GetResource:
					return ProtocolMessageProt256.eEventType_GetResource;
				case eEventType_SpendResource:
					return ProtocolMessageProt256.eEventType_SpendResource;
				case eEventType_PackExpand:
					return ProtocolMessageProt256.eEventType_PackExpand;
				case eEventType_PackItemSold:
					return ProtocolMessageProt256.eEventType_PackItemSold;
				case eEventType_PackArrange:
					return ProtocolMessageProt256.eEventType_PackArrange;
				case eEventType_AchievementLevelUp:
					return ProtocolMessageProt256.eEventType_AchievementLevelUp;
				case eEventType_AchievementGet:
					return ProtocolMessageProt256.eEventType_AchievementGet;
				case eEventType_PlayerLevelChanging:
					return ProtocolMessageProt256.eEventType_PlayerLevelChanging;
				case eEventType_DungeonEnter:
					return ProtocolMessageProt256.eEventType_DungeonEnter;
				case eEventType_DungeonFinish:
					return ProtocolMessageProt256.eEventType_DungeonFinish;
				case eEventType_DungeonLeave:
					return ProtocolMessageProt256.eEventType_DungeonLeave;
				case eEventType_DungeonAutoFight:
					return ProtocolMessageProt256.eEventType_DungeonAutoFight;
				case eEventType_DungeonStarGet:
					return ProtocolMessageProt256.eEventType_DungeonStarGet;
				case eEventType_DungeonBattleWin:
					return ProtocolMessageProt256.eEventType_DungeonBattleWin;
				case eEventType_DungeonFinishAndAuto:
					return ProtocolMessageProt256.eEventType_DungeonFinishAndAuto;
				case eEventType_DungeonStar:
					return ProtocolMessageProt256.eEventType_DungeonStar;
				case eEventType_DungeonFinishType:
					return ProtocolMessageProt256.eEventType_DungeonFinishType;
				case eEventType_DungeonVsMonster:
					return ProtocolMessageProt256.eEventType_DungeonVsMonster;
				case eEventType_DungeonFightMonster:
					return ProtocolMessageProt256.eEventType_DungeonFightMonster;
				case eEventType_DivisionFinish:
					return ProtocolMessageProt256.eEventType_DivisionFinish;
				case eEventType_DivisionRefresh:
					return ProtocolMessageProt256.eEventType_DivisionRefresh;
				case eEventType_DivisionRefreshGet:
					return ProtocolMessageProt256.eEventType_DivisionRefreshGet;
				case eEventType_DivisionBuying:
					return ProtocolMessageProt256.eEventType_DivisionBuying;
				case eEventType_DivisionLevelUp:
					return ProtocolMessageProt256.eEventType_DivisionLevelUp;
				case eEventType_DivisionPrizeGet:
					return ProtocolMessageProt256.eEventType_DivisionPrizeGet;
				case eEventType_GovernmentTaskFinish:
					return ProtocolMessageProt256.eEventType_GovernmentTaskFinish;
				case eEventType_GovernmentTaskRefresh:
					return ProtocolMessageProt256.eEventType_GovernmentTaskRefresh;
				case eEventType_GovernmentTaskRefreshGet:
					return ProtocolMessageProt256.eEventType_GovernmentTaskRefreshGet;
				case eEventType_GovernmentTaskBuying:
					return ProtocolMessageProt256.eEventType_GovernmentTaskBuying;
				case eEventType_GovernmentTaskLevelUp:
					return ProtocolMessageProt256.eEventType_GovernmentTaskLevelUp;
				case eEventType_GovernmentTaskPrizeGet:
					return ProtocolMessageProt256.eEventType_GovernmentTaskPrizeGet;
				case eEventType_GuildCreation:
					return ProtocolMessageProt256.eEventType_GuildCreation;
				case eEventType_GuildJoining:
					return ProtocolMessageProt256.eEventType_GuildJoining;
				case eEventType_GuildDismiss:
					return ProtocolMessageProt256.eEventType_GuildDismiss;
				case eEventType_GuildQuit:
					return ProtocolMessageProt256.eEventType_GuildQuit;
				case eEventType_GuildSetQQ:
					return ProtocolMessageProt256.eEventType_GuildSetQQ;
				case eEventType_GuildAccuse:
					return ProtocolMessageProt256.eEventType_GuildAccuse;
				case eEventType_GuildLevel:
					return ProtocolMessageProt256.eEventType_GuildLevel;
				case eEventType_GuildDonate:
					return ProtocolMessageProt256.eEventType_GuildDonate;
				case eEventType_GuildBuildingUpgrade:
					return ProtocolMessageProt256.eEventType_GuildBuildingUpgrade;
				case eEventType_GuildOblation:
					return ProtocolMessageProt256.eEventType_GuildOblation;
				case eEventType_GuildOblationSelf:
					return ProtocolMessageProt256.eEventType_GuildOblationSelf;
				case eEventType_GuildShopBought:
					return ProtocolMessageProt256.eEventType_GuildShopBought;
				case eEventType_GuildSkillUpgrade:
					return ProtocolMessageProt256.eEventType_GuildSkillUpgrade;
				case eEventType_RankFightingPowerChanging:
					return ProtocolMessageProt256.eEventType_RankFightingPowerChanging;
				case eEventType_RankPetChanging:
					return ProtocolMessageProt256.eEventType_RankPetChanging;
				case eEventType_RankFighterChanging:
					return ProtocolMessageProt256.eEventType_RankFighterChanging;
				case eEventType_RankTrumpChanging:
					return ProtocolMessageProt256.eEventType_RankTrumpChanging;
				case eEventType_PlayerProstrate:
					return ProtocolMessageProt256.eEventType_PlayerProstrate;
				case eEventType_ReceiveProstrate:
					return ProtocolMessageProt256.eEventType_ReceiveProstrate;
				case eEventType_ExperienceChallenge:
					return ProtocolMessageProt256.eEventType_ExperienceChallenge;
				case eEventType_ExperienceSectionChanging:
					return ProtocolMessageProt256.eEventType_ExperienceSectionChanging;
				case eEventType_ExperienceRefresh:
					return ProtocolMessageProt256.eEventType_ExperienceRefresh;
				case eEventType_ExperienceTimesBought:
					return ProtocolMessageProt256.eEventType_ExperienceTimesBought;
				case eEventType_ExperienceGetVictory:
					return ProtocolMessageProt256.eEventType_ExperienceGetVictory;
				case eEventType_ExperienceGetPrize:
					return ProtocolMessageProt256.eEventType_ExperienceGetPrize;
				case eEventType_ExperienceLevelChange:
					return ProtocolMessageProt256.eEventType_ExperienceLevelChange;
				case eEventType_ArenaRankChanging:
					return ProtocolMessageProt256.eEventType_ArenaRankChanging;
				case eEventType_ArenaChallenge:
					return ProtocolMessageProt256.eEventType_ArenaChallenge;
				case eEventType_ArenaGetVictory:
					return ProtocolMessageProt256.eEventType_ArenaGetVictory;
				case eEventType_ArenaCancelRankBridge:
					return ProtocolMessageProt256.eEventType_ArenaCancelRankBridge;
				case eEventType_ArenaGetPrize:
					return ProtocolMessageProt256.eEventType_ArenaGetPrize;
				case eEventType_ArenaRankDwon:
					return ProtocolMessageProt256.eEventType_ArenaRankDwon;
				case eEventType_ArenaRank:
					return ProtocolMessageProt256.eEventType_ArenaRank;
				case eEventType_ArenaBestRank:
					return ProtocolMessageProt256.eEventType_ArenaBestRank;
				case eEventType_TeamBattleVictory:
					return ProtocolMessageProt256.eEventType_TeamBattleVictory;
				case eEventType_DemonTowerBattle:
					return ProtocolMessageProt256.eEventType_DemonTowerBattle;
				case eEventType_DemonTowerHighestChanging:
					return ProtocolMessageProt256.eEventType_DemonTowerHighestChanging;
				case eEventType_DemonTowerDefendSuccess:
					return ProtocolMessageProt256.eEventType_DemonTowerDefendSuccess;
				case eEventType_DemonTowerRobSuccess:
					return ProtocolMessageProt256.eEventType_DemonTowerRobSuccess;
				case eEventType_DemonTowerGetPrize:
					return ProtocolMessageProt256.eEventType_DemonTowerGetPrize;
				case eEventType_DemonTowerRob:
					return ProtocolMessageProt256.eEventType_DemonTowerRob;
				case eEventType_DemonTowerClearPVECD:
					return ProtocolMessageProt256.eEventType_DemonTowerClearPVECD;
				case eEventType_DemonTowerClearPVPCD:
					return ProtocolMessageProt256.eEventType_DemonTowerClearPVPCD;
				case eEventType_HolyLandJoin:
					return ProtocolMessageProt256.eEventType_HolyLandJoin;
				case eEventType_HolyLandQuit:
					return ProtocolMessageProt256.eEventType_HolyLandQuit;
				case eEventType_HolyLandUseItem:
					return ProtocolMessageProt256.eEventType_HolyLandUseItem;
				case eEventType_WorldBossEnter:
					return ProtocolMessageProt256.eEventType_WorldBossEnter;
				case eEventType_WorldBossKill:
					return ProtocolMessageProt256.eEventType_WorldBossKill;
				case eEventType_WorldBossInspire:
					return ProtocolMessageProt256.eEventType_WorldBossInspire;
				case eEventType_WorldBossAttack:
					return ProtocolMessageProt256.eEventType_WorldBossAttack;
				case eEventType_WorldBossAttackRightNow:
					return ProtocolMessageProt256.eEventType_WorldBossAttackRightNow;
				case eEventType_WorldBossBuyLive:
					return ProtocolMessageProt256.eEventType_WorldBossBuyLive;
				case eEventType_ShushanBattleJoin:
					return ProtocolMessageProt256.eEventType_ShushanBattleJoin;
				case eEventType_ShushanBattleQuit:
					return ProtocolMessageProt256.eEventType_ShushanBattleQuit;
				case eEventType_ShushanBattleVictory:
					return ProtocolMessageProt256.eEventType_ShushanBattleVictory;
				case eEventType_ShushanBattleSkillUsing:
					return ProtocolMessageProt256.eEventType_ShushanBattleSkillUsing;
				case eEventType_ShushanBattleTaskFinish:
					return ProtocolMessageProt256.eEventType_ShushanBattleTaskFinish;
				case eEventType_ShushanBattleWinStreak:
					return ProtocolMessageProt256.eEventType_ShushanBattleWinStreak;
				case eEventType_ShushanBattleBadgeUpgrade:
					return ProtocolMessageProt256.eEventType_ShushanBattleBadgeUpgrade;
				case eEventType_ShushanBattleGetPrize:
					return ProtocolMessageProt256.eEventType_ShushanBattleGetPrize;
				case eEventType_GuildBattleSignUp:
					return ProtocolMessageProt256.eEventType_GuildBattleSignUp;
				case eEventType_GuildBattleOneRoundEnd:
					return ProtocolMessageProt256.eEventType_GuildBattleOneRoundEnd;
				case eEventType_GuildBattleEnd:
					return ProtocolMessageProt256.eEventType_GuildBattleEnd;
				case eEventType_GuildBattleInspire:
					return ProtocolMessageProt256.eEventType_GuildBattleInspire;
				case eEventType_GuildBattleWeekendEnd:
					return ProtocolMessageProt256.eEventType_GuildBattleWeekendEnd;
				case eEventType_GuildBattleWin:
					return ProtocolMessageProt256.eEventType_GuildBattleWin;
				case eEventType_GuildBattleComboKill:
					return ProtocolMessageProt256.eEventType_GuildBattleComboKill;
				case eEventType_GuildBattleJoin:
					return ProtocolMessageProt256.eEventType_GuildBattleJoin;
				case eEventType_FightingPowerChanging:
					return ProtocolMessageProt256.eEventType_FightingPowerChanging;
				case eEventType_FightingPowerChangingPlayer:
					return ProtocolMessageProt256.eEventType_FightingPowerChangingPlayer;
				case eEventType_FightingPowerChangingAnyFigher:
					return ProtocolMessageProt256.eEventType_FightingPowerChangingAnyFigher;
				case eEventType_FriendAdding:
					return ProtocolMessageProt256.eEventType_FriendAdding;
				case eEventType_FriendRecommendUsing:
					return ProtocolMessageProt256.eEventType_FriendRecommendUsing;
				case eEventType_FriendSignatureChangings:
					return ProtocolMessageProt256.eEventType_FriendSignatureChangings;
				case eEventType_VipLevelChanging:
					return ProtocolMessageProt256.eEventType_VipLevelChanging;
				case eEventType_VipRechargeSuccess:
					return ProtocolMessageProt256.eEventType_VipRechargeSuccess;
				case eEventType_VipConsumptionSuccess:
					return ProtocolMessageProt256.eEventType_VipConsumptionSuccess;
				case eEventType_VipGetPrize:
					return ProtocolMessageProt256.eEventType_VipGetPrize;
				case eEventType_VipGetPrizeMore:
					return ProtocolMessageProt256.eEventType_VipGetPrizeMore;
				case eEventType_ActiveValueGetPrize:
					return ProtocolMessageProt256.eEventType_ActiveValueGetPrize;
				case eEventType_ActivePointGet:
					return ProtocolMessageProt256.eEventType_ActivePointGet;
				case eEventType_FightingPowerComparing:
					return ProtocolMessageProt256.eEventType_FightingPowerComparing;
				case eEventType_MallBought:
					return ProtocolMessageProt256.eEventType_MallBought;
				case eEventType_MallBoughtMomey:
					return ProtocolMessageProt256.eEventType_MallBoughtMomey;
				case eEventType_ExChangingMallBought:
					return ProtocolMessageProt256.eEventType_ExChangingMallBought;
				case eEventType_SettingsChanging:
					return ProtocolMessageProt256.eEventType_SettingsChanging;
				case eEventType_SettingsFastShield:
					return ProtocolMessageProt256.eEventType_SettingsFastShield;
				case eEventType_SettingsFullScreen:
					return ProtocolMessageProt256.eEventType_SettingsFullScreen;
				case eEventType_WorldMapMoving:
					return ProtocolMessageProt256.eEventType_WorldMapMoving;
				case eEventType_MailReading:
					return ProtocolMessageProt256.eEventType_MailReading;
				case eEventType_MailReceiving:
					return ProtocolMessageProt256.eEventType_MailReceiving;
				case eEventType_SkillLearning:
					return ProtocolMessageProt256.eEventType_SkillLearning;
				case eEventType_SkillEquiping:
					return ProtocolMessageProt256.eEventType_SkillEquiping;
				case eEventType_SkillUpgrade:
					return ProtocolMessageProt256.eEventType_SkillUpgrade;
				case eEventType_EquipmentStrengthening:
					return ProtocolMessageProt256.eEventType_EquipmentStrengthening;
				case eEventType_EquipmentForging:
					return ProtocolMessageProt256.eEventType_EquipmentForging;
				case eEventType_TrumpActive:
					return ProtocolMessageProt256.eEventType_TrumpActive;
				case eEventType_TrumpEquiping:
					return ProtocolMessageProt256.eEventType_TrumpEquiping;
				case eEventType_TrumpForging:
					return ProtocolMessageProt256.eEventType_TrumpForging;
				case eEventType_FighterEnlisted:
					return ProtocolMessageProt256.eEventType_FighterEnlisted;
				case eEventType_FighterLevelUp:
					return ProtocolMessageProt256.eEventType_FighterLevelUp;
				case eEventType_FighterCuiTi:
					return ProtocolMessageProt256.eEventType_FighterCuiTi;
				case eEventType_FighterSkillUpgrade:
					return ProtocolMessageProt256.eEventType_FighterSkillUpgrade;
				case eEventType_FighterSkillExchange:
					return ProtocolMessageProt256.eEventType_FighterSkillExchange;
				case eEventType_FighterLearningRecipe:
					return ProtocolMessageProt256.eEventType_FighterLearningRecipe;
				case eEventType_FighterRecipeUpgrade:
					return ProtocolMessageProt256.eEventType_FighterRecipeUpgrade;
				case eEventType_FormationActive:
					return ProtocolMessageProt256.eEventType_FormationActive;
				case eEventType_FormationChange:
					return ProtocolMessageProt256.eEventType_FormationChange;
				case eEventType_PetActive:
					return ProtocolMessageProt256.eEventType_PetActive;
				case eEventType_PetGetFighting:
					return ProtocolMessageProt256.eEventType_PetGetFighting;
				case eEventType_FighterBatterPoint:
					return ProtocolMessageProt256.eEventType_FighterBatterPoint;
				case eEventType_FighterCollected:
					return ProtocolMessageProt256.eEventType_FighterCollected;
				case eEventType_FighterStarCollected:
					return ProtocolMessageProt256.eEventType_FighterStarCollected;
				case eEventType_FighterInBattle:
					return ProtocolMessageProt256.eEventType_FighterInBattle;
				case eEventType_FormationChangeMore:
					return ProtocolMessageProt256.eEventType_FormationChangeMore;
				case eEventType_FighterCombinationUnlock:
					return ProtocolMessageProt256.eEventType_FighterCombinationUnlock;
				case eEventType_PetUpgrade:
					return ProtocolMessageProt256.eEventType_PetUpgrade;
				case eEventType_BeastSoulActive:
					return ProtocolMessageProt256.eEventType_BeastSoulActive;
				case eEventType_BeastUpgrade:
					return ProtocolMessageProt256.eEventType_BeastUpgrade;
				case eEventType_BeastSoulGet:
					return ProtocolMessageProt256.eEventType_BeastSoulGet;
				case eEventType_HorseActive:
					return ProtocolMessageProt256.eEventType_HorseActive;
				case eEventType_HorseGetUsed:
					return ProtocolMessageProt256.eEventType_HorseGetUsed;
				case eEventType_HorseUpgrade:
					return ProtocolMessageProt256.eEventType_HorseUpgrade;
				case eEventType_PlayerLearningRecipe:
					return ProtocolMessageProt256.eEventType_PlayerLearningRecipe;
				case eEventType_PlayerEquipingRecipe:
					return ProtocolMessageProt256.eEventType_PlayerEquipingRecipe;
				case eEventType_PlayerRecipeUpgrade:
					return ProtocolMessageProt256.eEventType_PlayerRecipeUpgrade;
				case eEventType_PlayerDujieSuccess:
					return ProtocolMessageProt256.eEventType_PlayerDujieSuccess;
				case eEventType_OnlineTime:
					return ProtocolMessageProt256.eEventType_OnlineTime;
				case eEventType_FaionActive:
					return ProtocolMessageProt256.eEventType_FaionActive;
				case eEventType_FaionGetUsed:
					return ProtocolMessageProt256.eEventType_FaionGetUsed;
				case eEventType_FaionUpgrade:
					return ProtocolMessageProt256.eEventType_FaionUpgrade;
				case eEventType_StoveFireLearning:
					return ProtocolMessageProt256.eEventType_StoveFireLearning;
				case eEventType_StoveFireFinish:
					return ProtocolMessageProt256.eEventType_StoveFireFinish;
				case eEventType_StoveUpgrade:
					return ProtocolMessageProt256.eEventType_StoveUpgrade;
				case eEventType_StovePlayerHelp:
					return ProtocolMessageProt256.eEventType_StovePlayerHelp;
				case eEventType_StoveFighterHelp:
					return ProtocolMessageProt256.eEventType_StoveFighterHelp;
				case eEventType_StoveBellow:
					return ProtocolMessageProt256.eEventType_StoveBellow;
				case eEventType_StoveComingIn:
					return ProtocolMessageProt256.eEventType_StoveComingIn;
				case eEventType_StoveFireStarting:
					return ProtocolMessageProt256.eEventType_StoveFireStarting;
				case eEventType_NewPlayerTask:
					return ProtocolMessageProt256.eEventType_NewPlayerTask;
				case eEventType_NewPlayerClient:
					return ProtocolMessageProt256.eEventType_NewPlayerClient;
				case eEventType_CircleTaskFinish:
					return ProtocolMessageProt256.eEventType_CircleTaskFinish;
				case eEventType_CircleTaskStarUp:
					return ProtocolMessageProt256.eEventType_CircleTaskStarUp;
				case eEventType_TravelFinish:
					return ProtocolMessageProt256.eEventType_TravelFinish;
				case eEventType_GuardEmeiFinish:
					return ProtocolMessageProt256.eEventType_GuardEmeiFinish;
				case eEventType_GuardEmeiFinishMore:
					return ProtocolMessageProt256.eEventType_GuardEmeiFinishMore;
				case eEventType_QQAlarmClock:
					return ProtocolMessageProt256.eEventType_QQAlarmClock;
				case eEventType_BeautyUnlock:
					return ProtocolMessageProt256.eEventType_BeautyUnlock;
				case eEventType_BeautyUnlockNum:
					return ProtocolMessageProt256.eEventType_BeautyUnlockNum;
				case eEventType_BeautyHug:
					return ProtocolMessageProt256.eEventType_BeautyHug;
				case eEventType_BeautySend:
					return ProtocolMessageProt256.eEventType_BeautySend;
				case eEventType_BeautySendAppreciate:
					return ProtocolMessageProt256.eEventType_BeautySendAppreciate;
				case eEventType_BeautyLevelUp:
					return ProtocolMessageProt256.eEventType_BeautyLevelUp;
				case eEventType_BattleArraySuccess:
					return ProtocolMessageProt256.eEventType_BattleArraySuccess;
				case eEventType_BattleArraySuccessInfo:
					return ProtocolMessageProt256.eEventType_BattleArraySuccessInfo;
				case eEventType_TreasureUseBuff:
					return ProtocolMessageProt256.eEventType_TreasureUseBuff;
				case eEventType_TreasureSuccess:
					return ProtocolMessageProt256.eEventType_TreasureSuccess;
				case eEventType_XinfaLearn:
					return ProtocolMessageProt256.eEventType_XinfaLearn;
				case eEventType_XinfaLevelUp:
					return ProtocolMessageProt256.eEventType_XinfaLevelUp;
				case eEventType_BoatFinish:
					return ProtocolMessageProt256.eEventType_BoatFinish;
				case eEventType_BoatRefresh:
					return ProtocolMessageProt256.eEventType_BoatRefresh;
				case eEventType_BoatRob:
					return ProtocolMessageProt256.eEventType_BoatRob;
				case eEventType_BoatProtect:
					return ProtocolMessageProt256.eEventType_BoatProtect;
				case eEventType_BoatBegin:
					return ProtocolMessageProt256.eEventType_BoatBegin;
				case eEventType_BoatGet:
					return ProtocolMessageProt256.eEventType_BoatGet;
				case eEventType_MoneyTree:
					return ProtocolMessageProt256.eEventType_MoneyTree;
				case eEventType_LingMountainSeize:
					return ProtocolMessageProt256.eEventType_LingMountainSeize;
				case eEventType_LingMountainJoin:
					return ProtocolMessageProt256.eEventType_LingMountainJoin;
				case eEventType_LingMountainConquer:
					return ProtocolMessageProt256.eEventType_LingMountainConquer;
				case eEventType_LingMountainWin:
					return ProtocolMessageProt256.eEventType_LingMountainWin;
				case eEventType_GemsGet:
					return ProtocolMessageProt256.eEventType_GemsGet;
				case eEventType_GemsSuit:
					return ProtocolMessageProt256.eEventType_GemsSuit;
				case eEventType_GemsCompose:
					return ProtocolMessageProt256.eEventType_GemsCompose;
				case eEventType_MysteryTreasureJoin:
					return ProtocolMessageProt256.eEventType_MysteryTreasureJoin;
				case eEventType_MysteryTreasureBox:
					return ProtocolMessageProt256.eEventType_MysteryTreasureBox;
				case eEventType_MysteryTreasureWin:
					return ProtocolMessageProt256.eEventType_MysteryTreasureWin;
				case eEventType_MysteryTreasureMove:
					return ProtocolMessageProt256.eEventType_MysteryTreasureMove;
				case eEventType_MysteryTreasureAliveTime:
					return ProtocolMessageProt256.eEventType_MysteryTreasureAliveTime;
				case eEventType_MysteryTreasureReport:
					return ProtocolMessageProt256.eEventType_MysteryTreasureReport;
				case eEventType_QuestionJoin:
					return ProtocolMessageProt256.eEventType_QuestionJoin;
				case eEventType_QuestionUseSkill:
					return ProtocolMessageProt256.eEventType_QuestionUseSkill;
				case eEventType_QuestionScore:
					return ProtocolMessageProt256.eEventType_QuestionScore;
				case eEventType_SkyTreasureJoin:
					return ProtocolMessageProt256.eEventType_SkyTreasureJoin;
				case eEventType_SkyTreasureGet:
					return ProtocolMessageProt256.eEventType_SkyTreasureGet;
				case eEventType_PlayerDraw:
					return ProtocolMessageProt256.eEventType_PlayerDraw;
				case eEventType_GetEnergy:
					return ProtocolMessageProt256.eEventType_GetEnergy;
				case eEventType_CheckIn:
					return ProtocolMessageProt256.eEventType_CheckIn;
				case eEventType_CheckInAdd:
					return ProtocolMessageProt256.eEventType_CheckInAdd;
				case eEventType_CheckInGetPrize:
					return ProtocolMessageProt256.eEventType_CheckInGetPrize;
				case eEventType_MonthCard:
					return ProtocolMessageProt256.eEventType_MonthCard;
				case eEventType_MonthCardSend:
					return ProtocolMessageProt256.eEventType_MonthCardSend;
				case eEventType_14DaysGift:
					return ProtocolMessageProt256.eEventType_14DaysGift;
				case eEventType_YellowDiamondNum:
					return ProtocolMessageProt256.eEventType_YellowDiamondNum;
				case eEventType_YellowDiamondGift:
					return ProtocolMessageProt256.eEventType_YellowDiamondGift;
				case eEventType_SitDownTime:
					return ProtocolMessageProt256.eEventType_SitDownTime;
				case eEventType_UsePromote:
					return ProtocolMessageProt256.eEventType_UsePromote;
				case eEventType_QQAlarmGift:
					return ProtocolMessageProt256.eEventType_QQAlarmGift;
				case eEventType_WeiBoGift:
					return ProtocolMessageProt256.eEventType_WeiBoGift;
				case eEventType_WeChatGift:
					return ProtocolMessageProt256.eEventType_WeChatGift;
				case eEventType_FriendInviteGift:
					return ProtocolMessageProt256.eEventType_FriendInviteGift;
				case eEventType_XiHeTruck:
					return ProtocolMessageProt256.eEventType_XiHeTruck;
				case eEventType_TrumpGet:
					return ProtocolMessageProt256.eEventType_TrumpGet;
				case eEventType_TrumpEquip:
					return ProtocolMessageProt256.eEventType_TrumpEquip;
				case eEventType_TrumpToStrongSucess:
					return ProtocolMessageProt256.eEventType_TrumpToStrongSucess;
				case eEventType_TrumpToStrongFaild:
					return ProtocolMessageProt256.eEventType_TrumpToStrongFaild;
				case eEventType_TrumpPu:
					return ProtocolMessageProt256.eEventType_TrumpPu;
				case eEventType_TrumpDes:
					return ProtocolMessageProt256.eEventType_TrumpDes;
				case eEventType_ItemUpgrade:
					return ProtocolMessageProt256.eEventType_ItemUpgrade;
				case eEventType_ShenglingPlay:
					return ProtocolMessageProt256.eEventType_ShenglingPlay;
				case eEventType_ShenglingControl:
					return ProtocolMessageProt256.eEventType_ShenglingControl;
				case eEventType_ShenglingReturn:
					return ProtocolMessageProt256.eEventType_ShenglingReturn;
				case eEventType_ShenglingThreeGameOver:
					return ProtocolMessageProt256.eEventType_ShenglingThreeGameOver;
				case eEventType_ShenglingPuzzOver:
					return ProtocolMessageProt256.eEventType_ShenglingPuzzOver;
				case eEventType_Max:
					return ProtocolMessageProt256.eEventType_Max;
				default:
					return "Unknown Error";
			}
		}
	}
}
