/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECoinType.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * 货币类型
	 */
	public final class ECoinType
	{
		public static const eCoinNone:uint = 0; //无
		public static const eGoldCoin:uint = 1; //仙石
		public static const eSilverCoin:uint = 2; //银币
		public static const eCouponCoin:uint = 3; //礼券
		public static const eHonourCoin:uint = 4; //荣誉
		public static const eCoinEnd:uint = 5; //结束
		public static const end:uint = eCoinEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eCoinNone:
					return ProtocolMessageProt258.eCoinNone;
				case eGoldCoin:
					return ProtocolMessageProt258.eGoldCoin;
				case eSilverCoin:
					return ProtocolMessageProt258.eSilverCoin;
				case eCouponCoin:
					return ProtocolMessageProt258.eCouponCoin;
				case eHonourCoin:
					return ProtocolMessageProt258.eHonourCoin;
				case eCoinEnd:
					return ProtocolMessageProt258.eCoinEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
