/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EPlayerVar.as
//  Purpose:      Var变量定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.varDefine
 {
	import net.protocol.Message.ProtocolMessageProt62;
	/**
	 * 玩家var变量，小于60000
	 */
	public final class EPlayerVar
	{
		public static const ePlayerVarNone:uint = 0; //无定义
		public static const ePlayerVarArenaWirship:uint = 101; //竞技场每日膜拜次数
		public static const ePlayerVarArenaChallengeFree:uint = 102; //竞技场挑战次数
		public static const ePlayerVarArenaChallengeFlush:uint = 103; //竞技场购买刷新次数
		public static const ePlayerVarArenaChallenge0:uint = 104; //竞技场0点刷将
		public static const ePlayerVarArenaChallenge12:uint = 105; //竞技场12点刷将
		public static const ePlayerVarArenaChallenge18:uint = 106; //竞技场18点刷将
		public static const ePlayerVarSendMail:uint = 107; //一小时发40封邮件
		public static const ePlayerVarBuyArenaChallengeTimes:uint = 108; //购买的斗剑挑战次数
		public static const ePlayerVarBuyArenaChallengeTimesOneDay:uint = 109; //每日购买挑战次数
		public static const ePlayerVarLadderUpdate:uint = 110; //今日天梯排名累计上升名次，int32，大于100者不动
		public static const ePlayerVarGuildDonate:uint = 111; //帮派捐献
		public static const ePlayerVarGuildWorship:uint = 112; //帮派捐献
		public static const ePlayerVarLadderChallenge:uint = 113; //天梯挑战次数
		public static const ePlayerVarChallegeAward:uint = 114; //挑战领奖,按位表示0位历练，1位天梯
		public static const ePlayerVarAdoreCount:uint = 115; //当日崇拜次数
		public static const ePlayerVarTripodShanfeng:uint = 116; //玩家每日对九疑鼎扇火次数
		public static const ePlayerVarTripodHelp:uint = 117; //玩家每日对九疑鼎协助次数
		public static const ePlayerVarArenaChallengeFreeFlush:uint = 118; //VIP每日竞技场免费刷新次数
		public static const ePlayerNoticeUpdateMark:uint = 119; //客服后台公告更新标志
		public static const ePlayerSysDialogMark:uint = 120; //客服后台系统弹窗标志
		public static const ePlayerQQCoinLevel:uint = 121; //QQ养成计划玩家等级记录
		public static const ePlayerAnswer:uint = 122; //答题信息
		public static const ePlayerAnswerScoreAndTime:uint = 123; //答题信息积分和时间
		public static const ePlayerTeamPos1Cache:uint = 124; //组队副本站位1散仙ID
		public static const ePlayerTeamPos2Cache:uint = 125; //组队副本站位2散仙ID
		public static const ePlayerTeamPos3Cache:uint = 126; //组队副本站位3散仙ID
		public static const ePlayerVarDayRechargeCenter:uint = 127; //今日充值仙石数
		public static const ePlayerVarDragonBall_TodayCount:uint = 128; //七龙珠活动之今日充值额度已达目标额度次数
		public static const ePlayerVarDragonBall_AllCount:uint = 129; //七龙珠活动之达到目标额度的总次数
		public static const ePlayerShipRobTimes:uint = 130; //抢劫次数
		public static const ePlayerShipDefenseTimes:uint = 131; //护送次数
		public static const ePlayerShipOpenTimes:uint = 132; //开船次数
		public static const ePlayerShipReFluseTimes:uint = 133; //刷新次数
		public static const ePlayerBuyOpenShipTimesToday:uint = 134; //今日购买的运船次数
		public static const ePlayerBuyRoBShipTimesToday:uint = 135; //今日购买的抢劫次数
		public static const ePlayerBuyReflushShipTimesToday:uint = 136; //今日购买的刷新次数
		public static const ePlayerFreezShipTimer:uint = 137; //金船战败冷却时间数
		public static const ePlayerInvites:uint = 138; //每日邀请好友数量
		public static const ePlayerVarXiheHelpCount:uint = 139; //羲和神车每日帮助次数
		public static const ePlayerVarFruit:uint = 140; //天元神兽每日喂养朱果数量
		public static const ePlayerVarDayPackage:uint = 141; //天元神兽每日礼包
		public static const ePlayerVarMonsterPackage:uint = 142; //天元神兽成长礼包
		public static const ePlayerVarTotalScore:uint = 143; //天元神兽活动玩家总积分
		public static const ePlayerVarBuyLadderTimes:uint = 143; //斗剑累计购买次数
		public static const ePlayerVarBuyLadderTimesToday:uint = 144; //斗剑今日购买次数
		public static const ePlayerVarGuildExchangedItemToday:uint = 145; //玩家今日帮派战兑换物品数量
		public static const ePlayerVarSevenConsumeGold:uint = 146; //七日消费仙石数
		public static const ePlayerVarSevenConsumeAwardInfo:uint = 147; //七日消费活动领奖信息
		public static const ePlayerVarGuildWorshipTypeBegin:uint = 148; //帮派捐献类型统计1
		public static const ePlayerVarGuildWorshipType2:uint = 149; //帮派捐献类型统计2
		public static const ePlayerVarGuildWorshipType3:uint = 150; //帮派捐献类型统计3
		public static const ePlayerVarGuildWorshipTypeEnd:uint = 151; //帮派捐献类型统计4
		public static const ePlayerMinLadderRank:uint = 152; //最小天梯排名
		public static const ePlayerQQCoinExchangeCount:uint = 153; //QQ养成计划玩家兑换次数
		public static const ePlayerQQCoinExchangeValue:uint = 154; //QQ养成计划玩家兑换额度
		public static const ePlayerVarRecharge:uint = 1000; //当前充值总额度
		public static const ePlayerVarConsume:uint = 1001; //当前消费总额度
		public static const ePlayerVarFirstRechrgeStatus:uint = 1002; //首充礼包礼券状态:0未充值 1已充值但未领取 2已领取
		public static const ePlayerVarDayEvent:uint = 1004; //19点刷新事件标志
		public static const ePlayerFlushGroupTask:uint = 1005; //当前刷新师门任务次数
		public static const ePlayerFlushYaMenTask:uint = 1006; //当前刷新衙门任务次数
		public static const ePlayerFinishGroupTask:uint = 1007; //当前完成师门任务次数
		public static const ePlayerFinishYaMenTask:uint = 1008; //当前完成衙门任务次数
		public static const ePlayerGetGroupPExp:uint = 1009; //今日获得师门奖励次数
		public static const ePlayerActivity:uint = 1010; //当日活跃度
		public static const ePlayerActivityTask:uint = 1011; //刷新活跃任务
		public static const ePlayerActivityAward:uint = 1012; //领取每日奖励
		public static const ePlayerVIPEndTime:uint = 1013; //VIP特权结束时间
		public static const ePlayerVIPGrowthValue:uint = 1014; //VIP特权成长值
		public static const ePlayerVIPType:uint = 1015; //开启的VIP特权类型(也可表示是否开启过VIP特权)
		public static const ePlayerVIPDayTime:uint = 1016; //VIP特权成长值每天结算时间
		public static const ePlayerVIPGetDayPack:uint = 1017; //VIP特权每日礼包领取
		public static const ePlayerVIPUsedGold:uint = 1018; //VIP特权消耗仙石数(小于100，若未开通VIP或者VIP过期则表明累计消耗数)
		public static const ePlayerVarIndulgeTime:uint = 1019; //防沉迷时间
		public static const ePlayerVarSittingTime:uint = 1020; //开始打坐时间
		public static const ePlayerVarTaskMark:uint = 1021; //任务前置条件标记
		public static const ePlayerVarMaxAction:uint = 1022; //体力补满标志
		public static const ePlayerVarActionRegain1:uint = 1023; //定点体力发放1
		public static const ePlayerVarActionRegain2:uint = 1024; //定点体力发放2
		public static const ePlayerVarActionAdd:uint = 1025; //每隔一段时间体力增加
		public static const ePlayerVarBuyActionCnt:uint = 1026; //购买行动力次数
		public static const ePlayerVarActionBuffer:uint = 1027; //体力buffer数值
		public static const ePlayerGetYaMenPExp:uint = 1028; //今日获得衙门奖励次数
		public static const ePlayerBuyGroupTask:uint = 1029; //今日购买师门任务次数
		public static const ePlayerBuyYaMenTask:uint = 1030; //今日购买衙门任务次数
		public static const eDemonTowerAtkMonsterCd:uint = 1031; //锁妖塔攻击怪物cd
		public static const eTeamDgnAward:uint = 1032; //组队副本领奖次数
		public static const ePlayerYDDayBag:uint = 1033; //QQ黄钻每日礼包
		public static const ePlayerYDNewBag:uint = 1034; //QQ黄钻新手礼包
		public static const ePlayerYDYearBag:uint = 1035; //QQ黄钻年费礼包
		public static const ePlayerYDLuxuryBag:uint = 1036; //QQ黄钻豪华礼包
		public static const ePlayerYDGrowBag:uint = 1037; //QQ黄钻成长礼包
		public static const ePlayerYDHorseBag:uint = 1038; //QQ黄钻座机礼包
		public static const ePlayerOnLineTime:uint = 1039; //当天在线时间
		public static const ePlayerGetInvite:uint = 1040; //获得邀请奖励
		public static const ePlayerVIPGetLevelAward:uint = 1041; //VIP特权等级奖励领取
		public static const ePlayerMallDiscountPos1:uint = 1042; //商城限购活动期间位置1已购买次数
		public static const ePlayerMallDiscountPos2:uint = 1043; //商城限购活动期间位置2已购买次数
		public static const ePlayerMallDiscountPos3:uint = 1044; //商城限购活动期间位置3已购买次数
		public static const ePlayerMallDiscountRecharge:uint = 1045; //商城限购活动期间充值仙石数量
		public static const ePlayerMallDiscountConsume:uint = 1046; //商城限购活动期间消费仙石数量
		public static const ePlayerMallDayLimitFresh:uint = 1047; //商城限购每日刷新数量
		public static const ePlayerSign:uint = 1048; //玩家签到功能
		public static const ePlayerLoginPkg:uint = 1049; //累计登入礼包
		public static const ePlayerLeaveLHB:uint = 1050; //玩家离开琅寰福地
		public static const ePlayerLHBSkill1:uint = 1051; //琅寰福地技能1
		public static const ePlayerLHBSkill2:uint = 1052; //琅寰福地技能2
		public static const ePlayerLHBSkill3:uint = 1053; //琅寰福地技能3
		public static const ePlayerLHBLoginTime:uint = 1054; //琅寰福地登入时间
		public static const ePlayerDujieFailTimes:uint = 1055; //散仙渡劫失败次数(做保护概率)
		public static const ePlayerDujieCount:uint = 1056; //散仙渡劫次数(新手需要)
		public static const ePlayerVarMonthCardEndTime:uint = 1057; //月卡特权结束时间
		public static const ePlayerVarMonthCardGetTime:uint = 1058; //月卡奖励领取时间
		public static const ePlayerVarMonthCardOverNotice:uint = 1059; //月卡过期通知记录
		public static const ePlayerVarLoginDays:uint = 1060; //玩家累计登入天数（最大14天）
		public static const ePlayerVarSecondRechrgeStatus:uint = 1061; //二次充值礼包状态:0未充值 1已充值但未领取 2已领取
		public static const ePlayerVarSecondRechargeValue:uint = 1062; //二次充值总额度
		public static const ePlayerVarCuiTiCount:uint = 1063; //散仙崔体是否到达+7
		public static const ePlayerVarZhanQi:uint = 1064; //玩家是否参加秘境夺宝
		public static const ePlayerVarRechargeToday:uint = 1065; //今日充值总额度
		public static const ePlayerVarGetRechargeAward:uint = 1066; //今日领取单日冲值礼包
		public static const ePlayerVarShengLingBuyLife:uint = 1067; //今日领取单日冲值礼包
		public static const ePlayerVarShengLingBuyEnter:uint = 1068; //圣陵购买次数
		public static const ePlayerVarShengLingUseEnter:uint = 1069; //圣陵使用进入次数
		public static const ePlayerVarUseControlDice:uint = 1070; //遥控骰子使用次数
		public static const ePlayerVarBuyControlDice:uint = 1071; //遥控骰子购买次数
		public static const ePlayerVarUseTurnDice:uint = 1072; //转向骰子使用次数
		public static const ePlayerVarBuyTurnDice:uint = 1073; //转向骰子购买次数
		public static const ePlayerVarMotuScore:uint = 1074; //三消积分
		public static const ePlayerVarMotuStep:uint = 1075; //三消步数
		public static const ePlayerVarMotuPrizeState:uint = 1076; //三消奖励状态
		public static const ePlayerVarPlayerLevel:uint = 1077; //玩家所在层
		public static const ePlayerVarPlayerGridIndex:uint = 1078; //玩家所在格子
		public static const ePlayerVarPlayerPreGridIndex:uint = 1079; //玩家上一次所在格子
		public static const ePlayerVarPlayerPreLevel:uint = 1080; //玩家上一次所在层
		public static const ePlayerVarPlayerDir:uint = 1081; //玩家方向
		public static const ePlayerVarPlayerBuyEnterTimes:uint = 1084; //今天购买次数
		public static const ePlayerVarPlayerBuyTurnDiceTimes:uint = 1085; //今天购买次数
		public static const ePlayerVarPlayerBuyControlDiceTimes:uint = 1086; //今天购买次数
		public static const ePlayerVarPlayerBuyLifeTimes:uint = 1087; //今天购买次数
		public static const ePlayerVarShengLingUseLife:uint = 1088; //今天购买次数
		public static const ePlayerVarControlDiceSended:uint = 1089; //免费遥控骰子是否已经发送
		public static const ePlayerVarCheckContinue:uint = 1090; //是否继续进入圣陵
		public static const ePlayerVarPlayDiceEffect:uint = 1091; //播放特效
		public static const ePlayerVarFenbaoyan:uint = 1092; //分宝岩时间
		public static const ePlayerVarFirstEnterShengLing:uint = 1093; //玩家第一次进入
		public static const ePlayerZeroDay:uint = 10054; //零点刷新事件标志
		public static const ePlayerTHKillNum:uint = 10055; //寻宝每天击杀次数
		public static const ePlayerTHCond:uint = 10056; //寻宝前置条件
		public static const ePlayerTGSL:uint = 10057; //寻宝天罡神力
		public static const ePlayerBJGX:uint = 10058; //寻宝白驹过隙
		public static const ePlayerTLHZ:uint = 10059; //寻宝偷梁换柱
		public static const ePlayerShushanweiwei:uint = 10060; //蜀山微微个人奖励
		public static const ePlayerShushanweixin:uint = 10061; //蜀山微微微信奖励
		public static const ePlayerShushanweibo:uint = 10062; //蜀山微微微博奖励
		public static const ePlayerVarDayRechargeGame:uint = 10065; //今日充值仙石数
		public static const ePlayerVarShushanFoundInfo:uint = 10066; //蜀山基金购买与领取数据
		public static const ePlayerVarShushanFoundLoginDays:uint = 10067; //玩家购买蜀山基金后累计登陆天数
		public static const ePlayerCircleTaskStar:uint = 10068; //环任务星级
		public static const ePlayerCircleTaskNum:uint = 10069; //环任务环数
		public static const ePlayerVarChongZhi:uint = 10070; //商城充值仙石活动奖励信息
		public static const ePlayerTaskMarket:uint = 10071; //任务集市
		public static const ePlayerlixianDgnBuyTimes:uint = 10072; //购买的历险副本总次数
		public static const ePlayerlixianDgnBuyTimesToday:uint = 10073; //今日购买的历险副本总次数
		public static const ePlayerlixianDgnPassToday:uint = 10074; //今日通关的历险副本次数
		public static const ePlayerWeiboNum:uint = 10075; //蜀山微微微博人数
		public static const ePlayerWeixinNum:uint = 10076; //蜀山微微微信人数
		public static const ePlayerGEMEntryNum:uint = 10077; //守卫峨眉（0-31位：每天免费进入次数；32-63位：每天购买进入次数）
		public static const ePlayerGEMMissionStatus:uint = 10078; //每一位代表守卫峨眉每个关卡守卫成功状态（0：未成功；1：成功）
		public static const ePlayerGEMBuyEntryNum:uint = 10079; //守卫峨眉购买进入总次数
		public static const ePlayerQQAlarm:uint = 10080; //玩家安装QQAlarm奖励
		public static const ePlayerDrawCount:uint = 10081; //玩家已经免费求签次数
		public static const ePlayerMoneyTreeCount:uint = 10082; //玩家当日摇钱次数
		public static const ePlayerRegisterSevenDaysA:uint = 10083; //玩家注册第一天目标信息
		public static const ePlayerRegisterSevenDaysB:uint = 10084; //玩家注册第二天目标信息
		public static const ePlayerRegisterSevenDaysC:uint = 10085; //玩家注册第三天目标信息
		public static const ePlayerRegisterSevenDaysD:uint = 10086; //玩家注册第四天目标信息
		public static const ePlayerRegisterSevenDaysE:uint = 10087; //玩家注册第五天目标信息
		public static const ePlayerRegisterSevenDaysF:uint = 10088; //玩家注册第六天目标信息
		public static const ePlayerRegisterSevenDaysG:uint = 10089; //玩家注册第七天目标信息
		public static const ePlayerCurDayBuyMark:uint = 10090; //玩家注册七天活动当天购买标志
		public static const ePlayerFighterBuyMark:uint = 10091; //玩家购买散仙购买标志
		public static const ePlayerMallDiscountPos1Mark:uint = 10092; //商城限购活动期间位置1版本标记
		public static const ePlayerMallDiscountPos2Mark:uint = 10093; //商城限购活动期间位置2版本标记
		public static const ePlayerMallDiscountPos3Mark:uint = 10094; //商城限购活动期间位置3版本标记
		public static const ePlayerMallDiscountPos1Recharge:uint = 10095; //商城限购活动期间位置1充值仙石数量
		public static const ePlayerMallDiscountPos2Recharge:uint = 10096; //商城限购活动期间位置2充值仙石数量
		public static const ePlayerMallDiscountPos3Recharge:uint = 10097; //商城限购活动期间位置3充值仙石数量
		public static const ePlayerMallDiscountPos1Consume:uint = 10098; //商城限购活动期间位置1消费仙石数量
		public static const ePlayerMallDiscountPos2Consume:uint = 10099; //商城限购活动期间位置2消费仙石数量
		public static const ePlayerMallDiscountPos3Consume:uint = 10100; //商城限购活动期间位置3消费仙石数量
		public static const ePlayerVarMax:uint = 59999; //最大值
		public static const end:uint = ePlayerVarMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ePlayerVarNone:
					return ProtocolMessageProt62.ePlayerVarNone;
				case ePlayerVarArenaWirship:
					return ProtocolMessageProt62.ePlayerVarArenaWirship;
				case ePlayerVarArenaChallengeFree:
					return ProtocolMessageProt62.ePlayerVarArenaChallengeFree;
				case ePlayerVarArenaChallengeFlush:
					return ProtocolMessageProt62.ePlayerVarArenaChallengeFlush;
				case ePlayerVarArenaChallenge0:
					return ProtocolMessageProt62.ePlayerVarArenaChallenge0;
				case ePlayerVarArenaChallenge12:
					return ProtocolMessageProt62.ePlayerVarArenaChallenge12;
				case ePlayerVarArenaChallenge18:
					return ProtocolMessageProt62.ePlayerVarArenaChallenge18;
				case ePlayerVarSendMail:
					return ProtocolMessageProt62.ePlayerVarSendMail;
				case ePlayerVarBuyArenaChallengeTimes:
					return ProtocolMessageProt62.ePlayerVarBuyArenaChallengeTimes;
				case ePlayerVarBuyArenaChallengeTimesOneDay:
					return ProtocolMessageProt62.ePlayerVarBuyArenaChallengeTimesOneDay;
				case ePlayerVarLadderUpdate:
					return ProtocolMessageProt62.ePlayerVarLadderUpdate;
				case ePlayerVarGuildDonate:
					return ProtocolMessageProt62.ePlayerVarGuildDonate;
				case ePlayerVarGuildWorship:
					return ProtocolMessageProt62.ePlayerVarGuildWorship;
				case ePlayerVarLadderChallenge:
					return ProtocolMessageProt62.ePlayerVarLadderChallenge;
				case ePlayerVarChallegeAward:
					return ProtocolMessageProt62.ePlayerVarChallegeAward;
				case ePlayerVarAdoreCount:
					return ProtocolMessageProt62.ePlayerVarAdoreCount;
				case ePlayerVarTripodShanfeng:
					return ProtocolMessageProt62.ePlayerVarTripodShanfeng;
				case ePlayerVarTripodHelp:
					return ProtocolMessageProt62.ePlayerVarTripodHelp;
				case ePlayerVarArenaChallengeFreeFlush:
					return ProtocolMessageProt62.ePlayerVarArenaChallengeFreeFlush;
				case ePlayerNoticeUpdateMark:
					return ProtocolMessageProt62.ePlayerNoticeUpdateMark;
				case ePlayerSysDialogMark:
					return ProtocolMessageProt62.ePlayerSysDialogMark;
				case ePlayerQQCoinLevel:
					return ProtocolMessageProt62.ePlayerQQCoinLevel;
				case ePlayerAnswer:
					return ProtocolMessageProt62.ePlayerAnswer;
				case ePlayerAnswerScoreAndTime:
					return ProtocolMessageProt62.ePlayerAnswerScoreAndTime;
				case ePlayerTeamPos1Cache:
					return ProtocolMessageProt62.ePlayerTeamPos1Cache;
				case ePlayerTeamPos2Cache:
					return ProtocolMessageProt62.ePlayerTeamPos2Cache;
				case ePlayerTeamPos3Cache:
					return ProtocolMessageProt62.ePlayerTeamPos3Cache;
				case ePlayerVarDayRechargeCenter:
					return ProtocolMessageProt62.ePlayerVarDayRechargeCenter;
				case ePlayerVarDragonBall_TodayCount:
					return ProtocolMessageProt62.ePlayerVarDragonBall_TodayCount;
				case ePlayerVarDragonBall_AllCount:
					return ProtocolMessageProt62.ePlayerVarDragonBall_AllCount;
				case ePlayerShipRobTimes:
					return ProtocolMessageProt62.ePlayerShipRobTimes;
				case ePlayerShipDefenseTimes:
					return ProtocolMessageProt62.ePlayerShipDefenseTimes;
				case ePlayerShipOpenTimes:
					return ProtocolMessageProt62.ePlayerShipOpenTimes;
				case ePlayerShipReFluseTimes:
					return ProtocolMessageProt62.ePlayerShipReFluseTimes;
				case ePlayerBuyOpenShipTimesToday:
					return ProtocolMessageProt62.ePlayerBuyOpenShipTimesToday;
				case ePlayerBuyRoBShipTimesToday:
					return ProtocolMessageProt62.ePlayerBuyRoBShipTimesToday;
				case ePlayerBuyReflushShipTimesToday:
					return ProtocolMessageProt62.ePlayerBuyReflushShipTimesToday;
				case ePlayerFreezShipTimer:
					return ProtocolMessageProt62.ePlayerFreezShipTimer;
				case ePlayerInvites:
					return ProtocolMessageProt62.ePlayerInvites;
				case ePlayerVarXiheHelpCount:
					return ProtocolMessageProt62.ePlayerVarXiheHelpCount;
				case ePlayerVarFruit:
					return ProtocolMessageProt62.ePlayerVarFruit;
				case ePlayerVarDayPackage:
					return ProtocolMessageProt62.ePlayerVarDayPackage;
				case ePlayerVarMonsterPackage:
					return ProtocolMessageProt62.ePlayerVarMonsterPackage;
				case ePlayerVarTotalScore:
					return ProtocolMessageProt62.ePlayerVarTotalScore;
				case ePlayerVarBuyLadderTimesToday:
					return ProtocolMessageProt62.ePlayerVarBuyLadderTimesToday;
				case ePlayerVarGuildExchangedItemToday:
					return ProtocolMessageProt62.ePlayerVarGuildExchangedItemToday;
				case ePlayerVarSevenConsumeGold:
					return ProtocolMessageProt62.ePlayerVarSevenConsumeGold;
				case ePlayerVarSevenConsumeAwardInfo:
					return ProtocolMessageProt62.ePlayerVarSevenConsumeAwardInfo;
				case ePlayerVarGuildWorshipTypeBegin:
					return ProtocolMessageProt62.ePlayerVarGuildWorshipTypeBegin;
				case ePlayerVarGuildWorshipType2:
					return ProtocolMessageProt62.ePlayerVarGuildWorshipType2;
				case ePlayerVarGuildWorshipType3:
					return ProtocolMessageProt62.ePlayerVarGuildWorshipType3;
				case ePlayerVarGuildWorshipTypeEnd:
					return ProtocolMessageProt62.ePlayerVarGuildWorshipTypeEnd;
				case ePlayerMinLadderRank:
					return ProtocolMessageProt62.ePlayerMinLadderRank;
				case ePlayerQQCoinExchangeCount:
					return ProtocolMessageProt62.ePlayerQQCoinExchangeCount;
				case ePlayerQQCoinExchangeValue:
					return ProtocolMessageProt62.ePlayerQQCoinExchangeValue;
				case ePlayerVarRecharge:
					return ProtocolMessageProt62.ePlayerVarRecharge;
				case ePlayerVarConsume:
					return ProtocolMessageProt62.ePlayerVarConsume;
				case ePlayerVarFirstRechrgeStatus:
					return ProtocolMessageProt62.ePlayerVarFirstRechrgeStatus;
				case ePlayerVarDayEvent:
					return ProtocolMessageProt62.ePlayerVarDayEvent;
				case ePlayerFlushGroupTask:
					return ProtocolMessageProt62.ePlayerFlushGroupTask;
				case ePlayerFlushYaMenTask:
					return ProtocolMessageProt62.ePlayerFlushYaMenTask;
				case ePlayerFinishGroupTask:
					return ProtocolMessageProt62.ePlayerFinishGroupTask;
				case ePlayerFinishYaMenTask:
					return ProtocolMessageProt62.ePlayerFinishYaMenTask;
				case ePlayerGetGroupPExp:
					return ProtocolMessageProt62.ePlayerGetGroupPExp;
				case ePlayerActivity:
					return ProtocolMessageProt62.ePlayerActivity;
				case ePlayerActivityTask:
					return ProtocolMessageProt62.ePlayerActivityTask;
				case ePlayerActivityAward:
					return ProtocolMessageProt62.ePlayerActivityAward;
				case ePlayerVIPEndTime:
					return ProtocolMessageProt62.ePlayerVIPEndTime;
				case ePlayerVIPGrowthValue:
					return ProtocolMessageProt62.ePlayerVIPGrowthValue;
				case ePlayerVIPType:
					return ProtocolMessageProt62.ePlayerVIPType;
				case ePlayerVIPDayTime:
					return ProtocolMessageProt62.ePlayerVIPDayTime;
				case ePlayerVIPGetDayPack:
					return ProtocolMessageProt62.ePlayerVIPGetDayPack;
				case ePlayerVIPUsedGold:
					return ProtocolMessageProt62.ePlayerVIPUsedGold;
				case ePlayerVarIndulgeTime:
					return ProtocolMessageProt62.ePlayerVarIndulgeTime;
				case ePlayerVarSittingTime:
					return ProtocolMessageProt62.ePlayerVarSittingTime;
				case ePlayerVarTaskMark:
					return ProtocolMessageProt62.ePlayerVarTaskMark;
				case ePlayerVarMaxAction:
					return ProtocolMessageProt62.ePlayerVarMaxAction;
				case ePlayerVarActionRegain1:
					return ProtocolMessageProt62.ePlayerVarActionRegain1;
				case ePlayerVarActionRegain2:
					return ProtocolMessageProt62.ePlayerVarActionRegain2;
				case ePlayerVarActionAdd:
					return ProtocolMessageProt62.ePlayerVarActionAdd;
				case ePlayerVarBuyActionCnt:
					return ProtocolMessageProt62.ePlayerVarBuyActionCnt;
				case ePlayerVarActionBuffer:
					return ProtocolMessageProt62.ePlayerVarActionBuffer;
				case ePlayerGetYaMenPExp:
					return ProtocolMessageProt62.ePlayerGetYaMenPExp;
				case ePlayerBuyGroupTask:
					return ProtocolMessageProt62.ePlayerBuyGroupTask;
				case ePlayerBuyYaMenTask:
					return ProtocolMessageProt62.ePlayerBuyYaMenTask;
				case eDemonTowerAtkMonsterCd:
					return ProtocolMessageProt62.eDemonTowerAtkMonsterCd;
				case eTeamDgnAward:
					return ProtocolMessageProt62.eTeamDgnAward;
				case ePlayerYDDayBag:
					return ProtocolMessageProt62.ePlayerYDDayBag;
				case ePlayerYDNewBag:
					return ProtocolMessageProt62.ePlayerYDNewBag;
				case ePlayerYDYearBag:
					return ProtocolMessageProt62.ePlayerYDYearBag;
				case ePlayerYDLuxuryBag:
					return ProtocolMessageProt62.ePlayerYDLuxuryBag;
				case ePlayerYDGrowBag:
					return ProtocolMessageProt62.ePlayerYDGrowBag;
				case ePlayerYDHorseBag:
					return ProtocolMessageProt62.ePlayerYDHorseBag;
				case ePlayerOnLineTime:
					return ProtocolMessageProt62.ePlayerOnLineTime;
				case ePlayerGetInvite:
					return ProtocolMessageProt62.ePlayerGetInvite;
				case ePlayerVIPGetLevelAward:
					return ProtocolMessageProt62.ePlayerVIPGetLevelAward;
				case ePlayerMallDiscountPos1:
					return ProtocolMessageProt62.ePlayerMallDiscountPos1;
				case ePlayerMallDiscountPos2:
					return ProtocolMessageProt62.ePlayerMallDiscountPos2;
				case ePlayerMallDiscountPos3:
					return ProtocolMessageProt62.ePlayerMallDiscountPos3;
				case ePlayerMallDiscountRecharge:
					return ProtocolMessageProt62.ePlayerMallDiscountRecharge;
				case ePlayerMallDiscountConsume:
					return ProtocolMessageProt62.ePlayerMallDiscountConsume;
				case ePlayerMallDayLimitFresh:
					return ProtocolMessageProt62.ePlayerMallDayLimitFresh;
				case ePlayerSign:
					return ProtocolMessageProt62.ePlayerSign;
				case ePlayerLoginPkg:
					return ProtocolMessageProt62.ePlayerLoginPkg;
				case ePlayerLeaveLHB:
					return ProtocolMessageProt62.ePlayerLeaveLHB;
				case ePlayerLHBSkill1:
					return ProtocolMessageProt62.ePlayerLHBSkill1;
				case ePlayerLHBSkill2:
					return ProtocolMessageProt62.ePlayerLHBSkill2;
				case ePlayerLHBSkill3:
					return ProtocolMessageProt62.ePlayerLHBSkill3;
				case ePlayerLHBLoginTime:
					return ProtocolMessageProt62.ePlayerLHBLoginTime;
				case ePlayerDujieFailTimes:
					return ProtocolMessageProt62.ePlayerDujieFailTimes;
				case ePlayerDujieCount:
					return ProtocolMessageProt62.ePlayerDujieCount;
				case ePlayerVarMonthCardEndTime:
					return ProtocolMessageProt62.ePlayerVarMonthCardEndTime;
				case ePlayerVarMonthCardGetTime:
					return ProtocolMessageProt62.ePlayerVarMonthCardGetTime;
				case ePlayerVarMonthCardOverNotice:
					return ProtocolMessageProt62.ePlayerVarMonthCardOverNotice;
				case ePlayerVarLoginDays:
					return ProtocolMessageProt62.ePlayerVarLoginDays;
				case ePlayerVarSecondRechrgeStatus:
					return ProtocolMessageProt62.ePlayerVarSecondRechrgeStatus;
				case ePlayerVarSecondRechargeValue:
					return ProtocolMessageProt62.ePlayerVarSecondRechargeValue;
				case ePlayerVarCuiTiCount:
					return ProtocolMessageProt62.ePlayerVarCuiTiCount;
				case ePlayerVarZhanQi:
					return ProtocolMessageProt62.ePlayerVarZhanQi;
				case ePlayerVarRechargeToday:
					return ProtocolMessageProt62.ePlayerVarRechargeToday;
				case ePlayerVarGetRechargeAward:
					return ProtocolMessageProt62.ePlayerVarGetRechargeAward;
				case ePlayerVarShengLingBuyLife:
					return ProtocolMessageProt62.ePlayerVarShengLingBuyLife;
				case ePlayerVarShengLingBuyEnter:
					return ProtocolMessageProt62.ePlayerVarShengLingBuyEnter;
				case ePlayerVarShengLingUseEnter:
					return ProtocolMessageProt62.ePlayerVarShengLingUseEnter;
				case ePlayerVarUseControlDice:
					return ProtocolMessageProt62.ePlayerVarUseControlDice;
				case ePlayerVarBuyControlDice:
					return ProtocolMessageProt62.ePlayerVarBuyControlDice;
				case ePlayerVarUseTurnDice:
					return ProtocolMessageProt62.ePlayerVarUseTurnDice;
				case ePlayerVarBuyTurnDice:
					return ProtocolMessageProt62.ePlayerVarBuyTurnDice;
				case ePlayerVarMotuScore:
					return ProtocolMessageProt62.ePlayerVarMotuScore;
				case ePlayerVarMotuStep:
					return ProtocolMessageProt62.ePlayerVarMotuStep;
				case ePlayerVarMotuPrizeState:
					return ProtocolMessageProt62.ePlayerVarMotuPrizeState;
				case ePlayerVarPlayerLevel:
					return ProtocolMessageProt62.ePlayerVarPlayerLevel;
				case ePlayerVarPlayerGridIndex:
					return ProtocolMessageProt62.ePlayerVarPlayerGridIndex;
				case ePlayerVarPlayerPreGridIndex:
					return ProtocolMessageProt62.ePlayerVarPlayerPreGridIndex;
				case ePlayerVarPlayerPreLevel:
					return ProtocolMessageProt62.ePlayerVarPlayerPreLevel;
				case ePlayerVarPlayerDir:
					return ProtocolMessageProt62.ePlayerVarPlayerDir;
				case ePlayerVarPlayerBuyEnterTimes:
					return ProtocolMessageProt62.ePlayerVarPlayerBuyEnterTimes;
				case ePlayerVarPlayerBuyTurnDiceTimes:
					return ProtocolMessageProt62.ePlayerVarPlayerBuyTurnDiceTimes;
				case ePlayerVarPlayerBuyControlDiceTimes:
					return ProtocolMessageProt62.ePlayerVarPlayerBuyControlDiceTimes;
				case ePlayerVarPlayerBuyLifeTimes:
					return ProtocolMessageProt62.ePlayerVarPlayerBuyLifeTimes;
				case ePlayerVarShengLingUseLife:
					return ProtocolMessageProt62.ePlayerVarShengLingUseLife;
				case ePlayerVarControlDiceSended:
					return ProtocolMessageProt62.ePlayerVarControlDiceSended;
				case ePlayerVarCheckContinue:
					return ProtocolMessageProt62.ePlayerVarCheckContinue;
				case ePlayerVarPlayDiceEffect:
					return ProtocolMessageProt62.ePlayerVarPlayDiceEffect;
				case ePlayerVarFenbaoyan:
					return ProtocolMessageProt62.ePlayerVarFenbaoyan;
				case ePlayerVarFirstEnterShengLing:
					return ProtocolMessageProt62.ePlayerVarFirstEnterShengLing;
				case ePlayerZeroDay:
					return ProtocolMessageProt62.ePlayerZeroDay;
				case ePlayerTHKillNum:
					return ProtocolMessageProt62.ePlayerTHKillNum;
				case ePlayerTHCond:
					return ProtocolMessageProt62.ePlayerTHCond;
				case ePlayerTGSL:
					return ProtocolMessageProt62.ePlayerTGSL;
				case ePlayerBJGX:
					return ProtocolMessageProt62.ePlayerBJGX;
				case ePlayerTLHZ:
					return ProtocolMessageProt62.ePlayerTLHZ;
				case ePlayerShushanweiwei:
					return ProtocolMessageProt62.ePlayerShushanweiwei;
				case ePlayerShushanweixin:
					return ProtocolMessageProt62.ePlayerShushanweixin;
				case ePlayerShushanweibo:
					return ProtocolMessageProt62.ePlayerShushanweibo;
				case ePlayerVarDayRechargeGame:
					return ProtocolMessageProt62.ePlayerVarDayRechargeGame;
				case ePlayerVarShushanFoundInfo:
					return ProtocolMessageProt62.ePlayerVarShushanFoundInfo;
				case ePlayerVarShushanFoundLoginDays:
					return ProtocolMessageProt62.ePlayerVarShushanFoundLoginDays;
				case ePlayerCircleTaskStar:
					return ProtocolMessageProt62.ePlayerCircleTaskStar;
				case ePlayerCircleTaskNum:
					return ProtocolMessageProt62.ePlayerCircleTaskNum;
				case ePlayerVarChongZhi:
					return ProtocolMessageProt62.ePlayerVarChongZhi;
				case ePlayerTaskMarket:
					return ProtocolMessageProt62.ePlayerTaskMarket;
				case ePlayerlixianDgnBuyTimes:
					return ProtocolMessageProt62.ePlayerlixianDgnBuyTimes;
				case ePlayerlixianDgnBuyTimesToday:
					return ProtocolMessageProt62.ePlayerlixianDgnBuyTimesToday;
				case ePlayerlixianDgnPassToday:
					return ProtocolMessageProt62.ePlayerlixianDgnPassToday;
				case ePlayerWeiboNum:
					return ProtocolMessageProt62.ePlayerWeiboNum;
				case ePlayerWeixinNum:
					return ProtocolMessageProt62.ePlayerWeixinNum;
				case ePlayerGEMEntryNum:
					return ProtocolMessageProt62.ePlayerGEMEntryNum;
				case ePlayerGEMMissionStatus:
					return ProtocolMessageProt62.ePlayerGEMMissionStatus;
				case ePlayerGEMBuyEntryNum:
					return ProtocolMessageProt62.ePlayerGEMBuyEntryNum;
				case ePlayerQQAlarm:
					return ProtocolMessageProt62.ePlayerQQAlarm;
				case ePlayerDrawCount:
					return ProtocolMessageProt62.ePlayerDrawCount;
				case ePlayerMoneyTreeCount:
					return ProtocolMessageProt62.ePlayerMoneyTreeCount;
				case ePlayerRegisterSevenDaysA:
					return ProtocolMessageProt62.ePlayerRegisterSevenDaysA;
				case ePlayerRegisterSevenDaysB:
					return ProtocolMessageProt62.ePlayerRegisterSevenDaysB;
				case ePlayerRegisterSevenDaysC:
					return ProtocolMessageProt62.ePlayerRegisterSevenDaysC;
				case ePlayerRegisterSevenDaysD:
					return ProtocolMessageProt62.ePlayerRegisterSevenDaysD;
				case ePlayerRegisterSevenDaysE:
					return ProtocolMessageProt62.ePlayerRegisterSevenDaysE;
				case ePlayerRegisterSevenDaysF:
					return ProtocolMessageProt62.ePlayerRegisterSevenDaysF;
				case ePlayerRegisterSevenDaysG:
					return ProtocolMessageProt62.ePlayerRegisterSevenDaysG;
				case ePlayerCurDayBuyMark:
					return ProtocolMessageProt62.ePlayerCurDayBuyMark;
				case ePlayerFighterBuyMark:
					return ProtocolMessageProt62.ePlayerFighterBuyMark;
				case ePlayerMallDiscountPos1Mark:
					return ProtocolMessageProt62.ePlayerMallDiscountPos1Mark;
				case ePlayerMallDiscountPos2Mark:
					return ProtocolMessageProt62.ePlayerMallDiscountPos2Mark;
				case ePlayerMallDiscountPos3Mark:
					return ProtocolMessageProt62.ePlayerMallDiscountPos3Mark;
				case ePlayerMallDiscountPos1Recharge:
					return ProtocolMessageProt62.ePlayerMallDiscountPos1Recharge;
				case ePlayerMallDiscountPos2Recharge:
					return ProtocolMessageProt62.ePlayerMallDiscountPos2Recharge;
				case ePlayerMallDiscountPos3Recharge:
					return ProtocolMessageProt62.ePlayerMallDiscountPos3Recharge;
				case ePlayerMallDiscountPos1Consume:
					return ProtocolMessageProt62.ePlayerMallDiscountPos1Consume;
				case ePlayerMallDiscountPos2Consume:
					return ProtocolMessageProt62.ePlayerMallDiscountPos2Consume;
				case ePlayerMallDiscountPos3Consume:
					return ProtocolMessageProt62.ePlayerMallDiscountPos3Consume;
				case ePlayerVarMax:
					return ProtocolMessageProt62.ePlayerVarMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
