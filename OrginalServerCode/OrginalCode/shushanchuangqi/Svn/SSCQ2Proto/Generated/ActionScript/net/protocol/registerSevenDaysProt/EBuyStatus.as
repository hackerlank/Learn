/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBuyStatus.as
//  Purpose:      注册七天目标协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.registerSevenDaysProt
 {
	import net.protocol.Message.ProtocolMessageProt89;
	/**
	 * 购买状态
	 */
	public final class EBuyStatus
	{
		public static const eNoBuy:uint = 0; //不能购买
		public static const eCanBuy:uint = 1; //能够购买
		public static const eAlreadyBuy:uint = 2; //已经购买
		public static const end:uint = eAlreadyBuy;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNoBuy:
					return ProtocolMessageProt89.eNoBuy;
				case eCanBuy:
					return ProtocolMessageProt89.eCanBuy;
				case eAlreadyBuy:
					return ProtocolMessageProt89.eAlreadyBuy;
				default:
					return "Unknown Error";
			}
		}
	}
}
