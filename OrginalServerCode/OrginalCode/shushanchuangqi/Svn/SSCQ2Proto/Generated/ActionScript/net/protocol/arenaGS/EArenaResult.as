/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EArenaResult.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
 {
	import net.protocol.Message.ProtocolMessageProt26;
	/**
	 * 竞技场操作结果
	 */
	public final class EArenaResult
	{
		public static const EArenaR_Suc:uint = 0; //成功
		public static const EArenaR_NoEnter:uint = 1; //没有参加斗剑
		public static const EArenaR_CDTime:uint = 2; //正在冷却
		public static const EArenaR_NoChanllengeTimes:uint = 3; //挑战次数用完
		public static const EArenaR_BuyTimesChanllengeTimes:uint = 4; //购买挑战次数已达上限
		public static const EArenaR_LackMoney:uint = 5; //钱钱不够
		public static const EArenaR_EnemyNoExist:uint = 6; //挑战目标不存在
		public static const EArenaR_EnemyTimeOut:uint = 7; //挑战目标已过期
		public static const EArenaR_EnemyIsSuc:uint = 8; //挑战目标已胜利
		public static const EArenaR_NoReward:uint = 9; //没有奖励可领取
		public static const EArenaR_RewardHasGet:uint = 10; //奖励已经领取
		public static const EArenaR_PackageFull:uint = 11; //包裹满了
		public static const EArenaR_AwardTimeOut:uint = 12; //奖励已过期
		public static const EArenaR_WirShipOverTimes:uint = 13; //膜拜次数已达上限
		public static const EArenaR_WirShipPlayerOverTimer:uint = 14; //膜拜对象已过期
		public static const EArenaR_BuyTimesMax:uint = 15; //累计购买次数已达上限
		public static const EArenaR_VIPLevel:uint = 16; //御剑等级不足
		public static const EArenaR_LadderNOOpen:uint = 17; //天梯未开启
		public static const EArenaR_LadderTimesLimit:uint = 18; //天梯挑战次数不足
		public static const EArenaR_LadderAwardHasGet:uint = 19; //天梯挑战奖励已领
		public static const EArenaR_LadderRankErr:uint = 20; //排名验证错误
		public static const EArenaR_LadderRankLimit:uint = 21; //挑战资格验证错误
		public static const EArenaR_ArenaNoOpen:uint = 22; //斗剑功能未开放
		public static const EArenaR_ArenaTimesLimit:uint = 23; //历练挑战次数不足
		public static const EArenaR_ArenaAwardHasGet:uint = 24; //历练挑战奖励已领
		public static const EArenaR_LadderTimesZero:uint = 25; //天梯挑战次数用完
		public static const EArenaR_LadderBuyTimesUp:uint = 26; //天梯挑战购买次数到达上限
		public static const EArenaR_OtherErr:uint = 27; //其他错误
		public static const end:uint = EArenaR_OtherErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EArenaR_Suc:
					return ProtocolMessageProt26.EArenaR_Suc;
				case EArenaR_NoEnter:
					return ProtocolMessageProt26.EArenaR_NoEnter;
				case EArenaR_CDTime:
					return ProtocolMessageProt26.EArenaR_CDTime;
				case EArenaR_NoChanllengeTimes:
					return ProtocolMessageProt26.EArenaR_NoChanllengeTimes;
				case EArenaR_BuyTimesChanllengeTimes:
					return ProtocolMessageProt26.EArenaR_BuyTimesChanllengeTimes;
				case EArenaR_LackMoney:
					return ProtocolMessageProt26.EArenaR_LackMoney;
				case EArenaR_EnemyNoExist:
					return ProtocolMessageProt26.EArenaR_EnemyNoExist;
				case EArenaR_EnemyTimeOut:
					return ProtocolMessageProt26.EArenaR_EnemyTimeOut;
				case EArenaR_EnemyIsSuc:
					return ProtocolMessageProt26.EArenaR_EnemyIsSuc;
				case EArenaR_NoReward:
					return ProtocolMessageProt26.EArenaR_NoReward;
				case EArenaR_RewardHasGet:
					return ProtocolMessageProt26.EArenaR_RewardHasGet;
				case EArenaR_PackageFull:
					return ProtocolMessageProt26.EArenaR_PackageFull;
				case EArenaR_AwardTimeOut:
					return ProtocolMessageProt26.EArenaR_AwardTimeOut;
				case EArenaR_WirShipOverTimes:
					return ProtocolMessageProt26.EArenaR_WirShipOverTimes;
				case EArenaR_WirShipPlayerOverTimer:
					return ProtocolMessageProt26.EArenaR_WirShipPlayerOverTimer;
				case EArenaR_BuyTimesMax:
					return ProtocolMessageProt26.EArenaR_BuyTimesMax;
				case EArenaR_VIPLevel:
					return ProtocolMessageProt26.EArenaR_VIPLevel;
				case EArenaR_LadderNOOpen:
					return ProtocolMessageProt26.EArenaR_LadderNOOpen;
				case EArenaR_LadderTimesLimit:
					return ProtocolMessageProt26.EArenaR_LadderTimesLimit;
				case EArenaR_LadderAwardHasGet:
					return ProtocolMessageProt26.EArenaR_LadderAwardHasGet;
				case EArenaR_LadderRankErr:
					return ProtocolMessageProt26.EArenaR_LadderRankErr;
				case EArenaR_LadderRankLimit:
					return ProtocolMessageProt26.EArenaR_LadderRankLimit;
				case EArenaR_ArenaNoOpen:
					return ProtocolMessageProt26.EArenaR_ArenaNoOpen;
				case EArenaR_ArenaTimesLimit:
					return ProtocolMessageProt26.EArenaR_ArenaTimesLimit;
				case EArenaR_ArenaAwardHasGet:
					return ProtocolMessageProt26.EArenaR_ArenaAwardHasGet;
				case EArenaR_LadderTimesZero:
					return ProtocolMessageProt26.EArenaR_LadderTimesZero;
				case EArenaR_LadderBuyTimesUp:
					return ProtocolMessageProt26.EArenaR_LadderBuyTimesUp;
				case EArenaR_OtherErr:
					return ProtocolMessageProt26.EArenaR_OtherErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
