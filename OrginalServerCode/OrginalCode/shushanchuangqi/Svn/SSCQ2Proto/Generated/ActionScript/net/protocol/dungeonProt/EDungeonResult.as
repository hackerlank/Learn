/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDungeonResult.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
 {
	import net.protocol.Message.ProtocolMessageProt59;
	/**
	 * 副本结果
	 */
	public final class EDungeonResult
	{
		public static const eDungeonSuccess:uint = 0; //成功
		public static const eDungeonSweepingErr:uint = 1; //正在扫荡中
		public static const eDungeonPowerErr:uint = 2; //体力不足
		public static const eDungeonNotSweepingErr:uint = 3; //不在扫荡中
		public static const eDungeonSweepingSpeedUpErr:uint = 4; //扫荡加速中
		public static const eDungeonTypeNotExist:uint = 5; //此副本类型不存在
		public static const eDungeonInDgn:uint = 6; //你在副本中
		public static const eDungeonLowLevel:uint = 7; //你等级不够
		public static const eDungeonCreateErrType:uint = 8; //副本类型不正确，不可以创建副本
		public static const eDungeonPreDgnNotFinish:uint = 9; //前置副本未完成
		public static const eDungeonPackEmptyMin:uint = 10; //包裹空格子不足
		public static const eDungeonOutDgn:uint = 11; //你不在副本中
		public static const eDungeonInsNotExist:uint = 12; //副本不存在
		public static const eDungeonNotFinish:uint = 13; //副本未完成
		public static const eDungeonBusy:uint = 14; //玩家忙
		public static const eDungeonNotSweeping:uint = 15; //不在扫荡状态
		public static const eSpeedUpItemLimit:uint = 16; //加速道具不足
		public static const eDungeonTimesLimit:uint = 17; //进入次数不足
		public static const eDungeonTimesLimitForHero:uint = 18; //英雄本进入次数不足
		public static const eDungeonTimesLimitForLiXian:uint = 19; //历险本进入次数不足
		public static const eDungeonVipBuyHero:uint = 20; //购买英雄副本vip等级不足
		public static const eDungeonVipBuyLiXian:uint = 21; //购买历险副本vip等级不足
		public static const eDungeonNOGold:uint = 22; //仙石不足
		public static const eDungeonOtherErr:uint = 23; //未知错误
		public static const end:uint = eDungeonOtherErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eDungeonSuccess:
					return ProtocolMessageProt59.eDungeonSuccess;
				case eDungeonSweepingErr:
					return ProtocolMessageProt59.eDungeonSweepingErr;
				case eDungeonPowerErr:
					return ProtocolMessageProt59.eDungeonPowerErr;
				case eDungeonNotSweepingErr:
					return ProtocolMessageProt59.eDungeonNotSweepingErr;
				case eDungeonSweepingSpeedUpErr:
					return ProtocolMessageProt59.eDungeonSweepingSpeedUpErr;
				case eDungeonTypeNotExist:
					return ProtocolMessageProt59.eDungeonTypeNotExist;
				case eDungeonInDgn:
					return ProtocolMessageProt59.eDungeonInDgn;
				case eDungeonLowLevel:
					return ProtocolMessageProt59.eDungeonLowLevel;
				case eDungeonCreateErrType:
					return ProtocolMessageProt59.eDungeonCreateErrType;
				case eDungeonPreDgnNotFinish:
					return ProtocolMessageProt59.eDungeonPreDgnNotFinish;
				case eDungeonPackEmptyMin:
					return ProtocolMessageProt59.eDungeonPackEmptyMin;
				case eDungeonOutDgn:
					return ProtocolMessageProt59.eDungeonOutDgn;
				case eDungeonInsNotExist:
					return ProtocolMessageProt59.eDungeonInsNotExist;
				case eDungeonNotFinish:
					return ProtocolMessageProt59.eDungeonNotFinish;
				case eDungeonBusy:
					return ProtocolMessageProt59.eDungeonBusy;
				case eDungeonNotSweeping:
					return ProtocolMessageProt59.eDungeonNotSweeping;
				case eSpeedUpItemLimit:
					return ProtocolMessageProt59.eSpeedUpItemLimit;
				case eDungeonTimesLimit:
					return ProtocolMessageProt59.eDungeonTimesLimit;
				case eDungeonTimesLimitForHero:
					return ProtocolMessageProt59.eDungeonTimesLimitForHero;
				case eDungeonTimesLimitForLiXian:
					return ProtocolMessageProt59.eDungeonTimesLimitForLiXian;
				case eDungeonVipBuyHero:
					return ProtocolMessageProt59.eDungeonVipBuyHero;
				case eDungeonVipBuyLiXian:
					return ProtocolMessageProt59.eDungeonVipBuyLiXian;
				case eDungeonNOGold:
					return ProtocolMessageProt59.eDungeonNOGold;
				case eDungeonOtherErr:
					return ProtocolMessageProt59.eDungeonOtherErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
