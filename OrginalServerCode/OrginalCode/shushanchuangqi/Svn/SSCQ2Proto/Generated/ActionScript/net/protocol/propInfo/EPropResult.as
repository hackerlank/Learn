/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EPropResult.as
//  Purpose:      属性相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.propInfo
 {
	import net.protocol.Message.ProtocolMessageProt17;
	/**
	 * 属性操作的结果
	 */
	public final class EPropResult
	{
		public static const ePropSucceed:uint = 0; //无
		public static const ePropGoldErr:uint = 1; //仙石不够
		public static const ePropSilverErr:uint = 2; //银币不够
		public static const ePropCouponErr:uint = 3; //礼券不够
		public static const ePropOtherErr:uint = 4; //其它错误
		public static const end:uint = ePropOtherErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ePropSucceed:
					return ProtocolMessageProt17.ePropSucceed;
				case ePropGoldErr:
					return ProtocolMessageProt17.ePropGoldErr;
				case ePropSilverErr:
					return ProtocolMessageProt17.ePropSilverErr;
				case ePropCouponErr:
					return ProtocolMessageProt17.ePropCouponErr;
				case ePropOtherErr:
					return ProtocolMessageProt17.ePropOtherErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
