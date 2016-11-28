/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBBuyPuppetResult.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派战购买傀儡返回结果
	 */
	public final class ENGBBuyPuppetResult
	{
		public static const eNGBBPRSuccess:uint = 0; //购买成功
		public static const eNGBBPRFailed:uint = 1; //购买失败
		public static const eNGBBPRLackOfMoney:uint = 2; //货币不足
		public static const eNGBBPRCountLimit:uint = 3; //已经到达上限
		public static const eNGBBPRWrongTime:uint = 4; //不在正确的时间段内
		public static const eNGBBPRDefencer:uint = 5; //防守方不能购买傀儡
		public static const end:uint = eNGBBPRDefencer;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBBPRSuccess:
					return ProtocolMessageProt68.eNGBBPRSuccess;
				case eNGBBPRFailed:
					return ProtocolMessageProt68.eNGBBPRFailed;
				case eNGBBPRLackOfMoney:
					return ProtocolMessageProt68.eNGBBPRLackOfMoney;
				case eNGBBPRCountLimit:
					return ProtocolMessageProt68.eNGBBPRCountLimit;
				case eNGBBPRWrongTime:
					return ProtocolMessageProt68.eNGBBPRWrongTime;
				case eNGBBPRDefencer:
					return ProtocolMessageProt68.eNGBBPRDefencer;
				default:
					return "Unknown Error";
			}
		}
	}
}
