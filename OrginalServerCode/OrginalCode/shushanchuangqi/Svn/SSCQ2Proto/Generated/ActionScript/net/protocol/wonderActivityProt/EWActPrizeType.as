/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EWActPrizeType.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
 {
	import net.protocol.Message.ProtocolMessageProt199;
	/**
	 * 活动奖励类型
	 */
	public final class EWActPrizeType
	{
		public static const eWActPrizeType_default:uint = 0; //全部奖励
		public static const eWActPrizeType_first:uint = 1; //第一名玩家奖励
		public static const eWActPrizeType_one:uint = 2; //一等奖
		public static const eWActPrizeType_two:uint = 3; //二等奖
		public static const eWActPrizeType_three:uint = 4; //三等奖
		public static const eWActPrizeType_MAX:uint = 5; //奖励最大值
		public static const end:uint = eWActPrizeType_MAX;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eWActPrizeType_default:
					return ProtocolMessageProt199.eWActPrizeType_default;
				case eWActPrizeType_first:
					return ProtocolMessageProt199.eWActPrizeType_first;
				case eWActPrizeType_one:
					return ProtocolMessageProt199.eWActPrizeType_one;
				case eWActPrizeType_two:
					return ProtocolMessageProt199.eWActPrizeType_two;
				case eWActPrizeType_three:
					return ProtocolMessageProt199.eWActPrizeType_three;
				case eWActPrizeType_MAX:
					return ProtocolMessageProt199.eWActPrizeType_MAX;
				default:
					return "Unknown Error";
			}
		}
	}
}
