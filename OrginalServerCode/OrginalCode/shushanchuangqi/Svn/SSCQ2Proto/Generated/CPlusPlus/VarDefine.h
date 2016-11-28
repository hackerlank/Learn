/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    VarDefine.h
//  Purpose:      Var变量定义
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

namespace NVarDefine
{

/////////////////////以下为类型定义/////////////////////
//玩家var变量，小于60000
enum EPlayerVar
{
	ePlayerVarNone, //无定义
	ePlayerVarArenaWirship = 101, //竞技场每日膜拜次数
	ePlayerVarArenaChallengeFree = 102, //竞技场挑战次数
	ePlayerVarArenaChallengeFlush = 103, //竞技场购买刷新次数
	ePlayerVarArenaChallenge0 = 104, //竞技场0点刷将
	ePlayerVarArenaChallenge12 = 105, //竞技场12点刷将
	ePlayerVarArenaChallenge18 = 106, //竞技场18点刷将
	ePlayerVarSendMail = 107, //一小时发40封邮件
	ePlayerVarBuyArenaChallengeTimes = 108, //购买的斗剑挑战次数
	ePlayerVarBuyArenaChallengeTimesOneDay = 109, //每日购买挑战次数
	ePlayerVarLadderUpdate = 110, //今日天梯排名累计上升名次，int32，大于100者不动
	ePlayerVarGuildDonate = 111, //帮派捐献
	ePlayerVarGuildWorship = 112, //帮派捐献
	ePlayerVarLadderChallenge = 113, //天梯挑战次数
	ePlayerVarChallegeAward = 114, //挑战领奖,按位表示0位历练，1位天梯
	ePlayerVarAdoreCount = 115, //当日崇拜次数
	ePlayerVarTripodShanfeng = 116, //玩家每日对九疑鼎扇火次数
	ePlayerVarTripodHelp = 117, //玩家每日对九疑鼎协助次数
	ePlayerVarArenaChallengeFreeFlush = 118, //VIP每日竞技场免费刷新次数
	ePlayerNoticeUpdateMark = 119, //客服后台公告更新标志
	ePlayerSysDialogMark = 120, //客服后台系统弹窗标志
	ePlayerQQCoinLevel = 121, //QQ养成计划玩家等级记录
	ePlayerAnswer = 122, //答题信息
	ePlayerAnswerScoreAndTime = 123, //答题信息积分和时间
	ePlayerTeamPos1Cache = 124, //组队副本站位1散仙ID
	ePlayerTeamPos2Cache = 125, //组队副本站位2散仙ID
	ePlayerTeamPos3Cache = 126, //组队副本站位3散仙ID
	ePlayerVarDayRechargeCenter = 127, //今日充值仙石数
	ePlayerVarDragonBall_TodayCount = 128, //七龙珠活动之今日充值额度已达目标额度次数
	ePlayerVarDragonBall_AllCount = 129, //七龙珠活动之达到目标额度的总次数
	ePlayerShipRobTimes = 130, //抢劫次数
	ePlayerShipDefenseTimes = 131, //护送次数
	ePlayerShipOpenTimes = 132, //开船次数
	ePlayerShipReFluseTimes = 133, //刷新次数
	ePlayerBuyOpenShipTimesToday = 134, //今日购买的运船次数
	ePlayerBuyRoBShipTimesToday = 135, //今日购买的抢劫次数
	ePlayerBuyReflushShipTimesToday = 136, //今日购买的刷新次数
	ePlayerFreezShipTimer = 137, //金船战败冷却时间数
	ePlayerInvites = 138, //每日邀请好友数量
	ePlayerVarXiheHelpCount = 139, //羲和神车每日帮助次数
	ePlayerVarFruit = 140, //天元神兽每日喂养朱果数量
	ePlayerVarDayPackage = 141, //天元神兽每日礼包
	ePlayerVarMonsterPackage = 142, //天元神兽成长礼包
	ePlayerVarTotalScore = 143, //天元神兽活动玩家总积分
	ePlayerVarBuyLadderTimes = 143, //斗剑累计购买次数
	ePlayerVarBuyLadderTimesToday = 144, //斗剑今日购买次数
	ePlayerVarGuildExchangedItemToday = 145, //玩家今日帮派战兑换物品数量
	ePlayerVarSevenConsumeGold = 146, //七日消费仙石数
	ePlayerVarSevenConsumeAwardInfo = 147, //七日消费活动领奖信息
	ePlayerVarGuildWorshipTypeBegin = 148, //帮派捐献类型统计1
	ePlayerVarGuildWorshipType2 = 149, //帮派捐献类型统计2
	ePlayerVarGuildWorshipType3 = 150, //帮派捐献类型统计3
	ePlayerVarGuildWorshipTypeEnd = 151, //帮派捐献类型统计4
	ePlayerMinLadderRank = 152, //最小天梯排名
	ePlayerQQCoinExchangeCount = 153, //QQ养成计划玩家兑换次数
	ePlayerQQCoinExchangeValue = 154, //QQ养成计划玩家兑换额度
	ePlayerVarRecharge = 1000, //当前充值总额度
	ePlayerVarConsume = 1001, //当前消费总额度
	ePlayerVarFirstRechrgeStatus = 1002, //首充礼包礼券状态:0未充值 1已充值但未领取 2已领取
	ePlayerVarDayEvent = 1004, //19点刷新事件标志
	ePlayerFlushGroupTask = 1005, //当前刷新师门任务次数
	ePlayerFlushYaMenTask = 1006, //当前刷新衙门任务次数
	ePlayerFinishGroupTask = 1007, //当前完成师门任务次数
	ePlayerFinishYaMenTask = 1008, //当前完成衙门任务次数
	ePlayerGetGroupPExp = 1009, //今日获得师门奖励次数
	ePlayerActivity = 1010, //当日活跃度
	ePlayerActivityTask = 1011, //刷新活跃任务
	ePlayerActivityAward = 1012, //领取每日奖励
	ePlayerVIPEndTime = 1013, //VIP特权结束时间
	ePlayerVIPGrowthValue = 1014, //VIP特权成长值
	ePlayerVIPType = 1015, //开启的VIP特权类型(也可表示是否开启过VIP特权)
	ePlayerVIPDayTime = 1016, //VIP特权成长值每天结算时间
	ePlayerVIPGetDayPack = 1017, //VIP特权每日礼包领取
	ePlayerVIPUsedGold = 1018, //VIP特权消耗仙石数(小于100，若未开通VIP或者VIP过期则表明累计消耗数)
	ePlayerVarIndulgeTime = 1019, //防沉迷时间
	ePlayerVarSittingTime = 1020, //开始打坐时间
	ePlayerVarTaskMark = 1021, //任务前置条件标记
	ePlayerVarMaxAction = 1022, //体力补满标志
	ePlayerVarActionRegain1 = 1023, //定点体力发放1
	ePlayerVarActionRegain2 = 1024, //定点体力发放2
	ePlayerVarActionAdd = 1025, //每隔一段时间体力增加
	ePlayerVarBuyActionCnt = 1026, //购买行动力次数
	ePlayerVarActionBuffer = 1027, //体力buffer数值
	ePlayerGetYaMenPExp = 1028, //今日获得衙门奖励次数
	ePlayerBuyGroupTask = 1029, //今日购买师门任务次数
	ePlayerBuyYaMenTask = 1030, //今日购买衙门任务次数
	eDemonTowerAtkMonsterCd = 1031, //锁妖塔攻击怪物cd
	eTeamDgnAward = 1032, //组队副本领奖次数
	ePlayerYDDayBag = 1033, //QQ黄钻每日礼包
	ePlayerYDNewBag = 1034, //QQ黄钻新手礼包
	ePlayerYDYearBag = 1035, //QQ黄钻年费礼包
	ePlayerYDLuxuryBag = 1036, //QQ黄钻豪华礼包
	ePlayerYDGrowBag = 1037, //QQ黄钻成长礼包
	ePlayerYDHorseBag = 1038, //QQ黄钻座机礼包
	ePlayerOnLineTime = 1039, //当天在线时间
	ePlayerGetInvite = 1040, //获得邀请奖励
	ePlayerVIPGetLevelAward = 1041, //VIP特权等级奖励领取
	ePlayerMallDiscountPos1 = 1042, //商城限购活动期间位置1已购买次数
	ePlayerMallDiscountPos2 = 1043, //商城限购活动期间位置2已购买次数
	ePlayerMallDiscountPos3 = 1044, //商城限购活动期间位置3已购买次数
	ePlayerMallDiscountRecharge = 1045, //商城限购活动期间充值仙石数量
	ePlayerMallDiscountConsume = 1046, //商城限购活动期间消费仙石数量
	ePlayerMallDayLimitFresh = 1047, //商城限购每日刷新数量
	ePlayerSign = 1048, //玩家签到功能
	ePlayerLoginPkg = 1049, //累计登入礼包
	ePlayerLeaveLHB = 1050, //玩家离开琅寰福地
	ePlayerLHBSkill1 = 1051, //琅寰福地技能1
	ePlayerLHBSkill2 = 1052, //琅寰福地技能2
	ePlayerLHBSkill3 = 1053, //琅寰福地技能3
	ePlayerLHBLoginTime = 1054, //琅寰福地登入时间
	ePlayerDujieFailTimes = 1055, //散仙渡劫失败次数(做保护概率)
	ePlayerDujieCount = 1056, //散仙渡劫次数(新手需要)
	ePlayerVarMonthCardEndTime = 1057, //月卡特权结束时间
	ePlayerVarMonthCardGetTime = 1058, //月卡奖励领取时间
	ePlayerVarMonthCardOverNotice = 1059, //月卡过期通知记录
	ePlayerVarLoginDays = 1060, //玩家累计登入天数（最大14天）
	ePlayerVarSecondRechrgeStatus = 1061, //二次充值礼包状态:0未充值 1已充值但未领取 2已领取
	ePlayerVarSecondRechargeValue = 1062, //二次充值总额度
	ePlayerVarCuiTiCount = 1063, //散仙崔体是否到达+7
	ePlayerVarZhanQi = 1064, //玩家是否参加秘境夺宝
	ePlayerVarRechargeToday = 1065, //今日充值总额度
	ePlayerVarGetRechargeAward = 1066, //今日领取单日冲值礼包
	ePlayerVarShengLingBuyLife = 1067, //今日领取单日冲值礼包
	ePlayerVarShengLingBuyEnter = 1068, //圣陵购买次数
	ePlayerVarShengLingUseEnter = 1069, //圣陵使用进入次数
	ePlayerVarUseControlDice = 1070, //遥控骰子使用次数
	ePlayerVarBuyControlDice = 1071, //遥控骰子购买次数
	ePlayerVarUseTurnDice = 1072, //转向骰子使用次数
	ePlayerVarBuyTurnDice = 1073, //转向骰子购买次数
	ePlayerVarMotuScore = 1074, //三消积分
	ePlayerVarMotuStep = 1075, //三消步数
	ePlayerVarMotuPrizeState = 1076, //三消奖励状态
	ePlayerVarPlayerLevel = 1077, //玩家所在层
	ePlayerVarPlayerGridIndex = 1078, //玩家所在格子
	ePlayerVarPlayerPreGridIndex = 1079, //玩家上一次所在格子
	ePlayerVarPlayerPreLevel = 1080, //玩家上一次所在层
	ePlayerVarPlayerDir = 1081, //玩家方向
	ePlayerVarPlayerBuyEnterTimes = 1084, //今天购买次数
	ePlayerVarPlayerBuyTurnDiceTimes = 1085, //今天购买次数
	ePlayerVarPlayerBuyControlDiceTimes = 1086, //今天购买次数
	ePlayerVarPlayerBuyLifeTimes = 1087, //今天购买次数
	ePlayerVarShengLingUseLife = 1088, //今天购买次数
	ePlayerVarControlDiceSended = 1089, //免费遥控骰子是否已经发送
	ePlayerVarCheckContinue = 1090, //是否继续进入圣陵
	ePlayerVarPlayDiceEffect = 1091, //播放特效
	ePlayerVarFenbaoyan = 1092, //分宝岩时间
	ePlayerVarFirstEnterShengLing = 1093, //玩家第一次进入
	ePlayerZeroDay = 10054, //零点刷新事件标志
	ePlayerTHKillNum = 10055, //寻宝每天击杀次数
	ePlayerTHCond = 10056, //寻宝前置条件
	ePlayerTGSL = 10057, //寻宝天罡神力
	ePlayerBJGX = 10058, //寻宝白驹过隙
	ePlayerTLHZ = 10059, //寻宝偷梁换柱
	ePlayerShushanweiwei = 10060, //蜀山微微个人奖励
	ePlayerShushanweixin = 10061, //蜀山微微微信奖励
	ePlayerShushanweibo = 10062, //蜀山微微微博奖励
	ePlayerVarDayRechargeGame = 10065, //今日充值仙石数
	ePlayerVarShushanFoundInfo = 10066, //蜀山基金购买与领取数据
	ePlayerVarShushanFoundLoginDays = 10067, //玩家购买蜀山基金后累计登陆天数
	ePlayerCircleTaskStar = 10068, //环任务星级
	ePlayerCircleTaskNum = 10069, //环任务环数
	ePlayerVarChongZhi = 10070, //商城充值仙石活动奖励信息
	ePlayerTaskMarket = 10071, //任务集市
	ePlayerlixianDgnBuyTimes = 10072, //购买的历险副本总次数
	ePlayerlixianDgnBuyTimesToday = 10073, //今日购买的历险副本总次数
	ePlayerlixianDgnPassToday = 10074, //今日通关的历险副本次数
	ePlayerWeiboNum = 10075, //蜀山微微微博人数
	ePlayerWeixinNum = 10076, //蜀山微微微信人数
	ePlayerGEMEntryNum = 10077, //守卫峨眉（0-31位：每天免费进入次数；32-63位：每天购买进入次数）
	ePlayerGEMMissionStatus = 10078, //每一位代表守卫峨眉每个关卡守卫成功状态（0：未成功；1：成功）
	ePlayerGEMBuyEntryNum = 10079, //守卫峨眉购买进入总次数
	ePlayerQQAlarm = 10080, //玩家安装QQAlarm奖励
	ePlayerDrawCount = 10081, //玩家已经免费求签次数
	ePlayerMoneyTreeCount = 10082, //玩家当日摇钱次数
	ePlayerRegisterSevenDaysA = 10083, //玩家注册第一天目标信息
	ePlayerRegisterSevenDaysB = 10084, //玩家注册第二天目标信息
	ePlayerRegisterSevenDaysC = 10085, //玩家注册第三天目标信息
	ePlayerRegisterSevenDaysD = 10086, //玩家注册第四天目标信息
	ePlayerRegisterSevenDaysE = 10087, //玩家注册第五天目标信息
	ePlayerRegisterSevenDaysF = 10088, //玩家注册第六天目标信息
	ePlayerRegisterSevenDaysG = 10089, //玩家注册第七天目标信息
	ePlayerCurDayBuyMark = 10090, //玩家注册七天活动当天购买标志
	ePlayerFighterBuyMark = 10091, //玩家购买散仙购买标志
	ePlayerMallDiscountPos1Mark = 10092, //商城限购活动期间位置1版本标记
	ePlayerMallDiscountPos2Mark = 10093, //商城限购活动期间位置2版本标记
	ePlayerMallDiscountPos3Mark = 10094, //商城限购活动期间位置3版本标记
	ePlayerMallDiscountPos1Recharge = 10095, //商城限购活动期间位置1充值仙石数量
	ePlayerMallDiscountPos2Recharge = 10096, //商城限购活动期间位置2充值仙石数量
	ePlayerMallDiscountPos3Recharge = 10097, //商城限购活动期间位置3充值仙石数量
	ePlayerMallDiscountPos1Consume = 10098, //商城限购活动期间位置1消费仙石数量
	ePlayerMallDiscountPos2Consume = 10099, //商城限购活动期间位置2消费仙石数量
	ePlayerMallDiscountPos3Consume = 10100, //商城限购活动期间位置3消费仙石数量
	ePlayerVarMax = 59999 //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EPlayerVar);
bool EnumStrToVal(const char*, EPlayerVar&);
#endif //PROT_USE_XML

//系统var变量(大于60000)
enum ESystemVar
{
	eSystemVarNone = 60000, //无定义
	eSystemVarArena = 60001, //竞技场结算
	eSystemVarGuildStatue = 60002, //帮派神像奖励结算
	eSystemVarGuildBattleAward = 60003, //帮派战奖励结算
	eSystemVarDemonTowerMaxTop = 60004, //锁妖塔通关最高层数
	eSystemVarQQCoinConsumeValue = 60005, //QQ养成计划奖励消费额度
	eSystemVarQQCoinMaxValue = 60006, //QQ养成计划奖励最大额度
	eSystemVarQQCoinActTime = 60007, //QQ养成计划活动时间
	eSystemVarAnswer = 60008, //答题活动时间
	eSystemVarAnswerTopicID = 60009, //答题活动当前题目ID
	eSystemVarZeroTime = 60010, //零点时间
	eSystemVarOpenServerActivity = 60011, //开服活动开始时间
	eSystemVar_WorldBossActBeginTime = 60500, //世界BOSS开始时间
	eSystemVar_WorldBossActEndTime = 60501, //世界BOSS结束时间
	eSystemVar_LangHuanBlessActBeginTime = 60502, //琅寰福地开始时间
	eSystemVar_LangHuanBlessActEndTime = 60503, //琅寰福地结束时间
	eSystemVar_GodChest = 60504, //天赐宝箱活动
	eSystemVar_DragonBallActPeriod = 60506, //当前七龙珠活动第多少期
	eSystemVar_SevenConsumeActBeginTime = 60507, //七日消费活动开始时间
	eSystemVar_SevenConsumeActEndTime = 60508, //七日消费活动结束时间
	eSystemVar_DragonBallActBeginTime = 60509, //七龙珠活动开始时间
	eSystemVar_DragonBallActEndTime = 60510, //七龙珠活动结束时间
	eSystemVar_NewGuildBattleGate1HP = 60511, //新帮派战山头一城门血量
	eSystemVar_NewGuildBattleGate2HP = 60512, //新帮派战山头二城门血量
	eSystemVar_NewGuildBattleGate3HP = 60513, //新帮派战山头三城门血量
	eSystemVar_NewGuildBattleGate1Attack = 60514, //新帮派战山头一城门血量
	eSystemVar_NewGuildBattleGate2Attack = 60515, //新帮派战山头二城门攻击力
	eSystemVar_NewGuildBattleGate3Attack = 60516, //新帮派战山头三城门攻击力
	eSystemVarMax //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESystemVar);
bool EnumStrToVal(const char*, ESystemVar&);
#endif //PROT_USE_XML


} //namespace NVarDefine
