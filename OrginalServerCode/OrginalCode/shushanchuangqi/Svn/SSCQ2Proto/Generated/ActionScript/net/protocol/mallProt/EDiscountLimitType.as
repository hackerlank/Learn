/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDiscountLimitType.as
//  Purpose:      商城相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
 {
	import net.protocol.Message.ProtocolMessageProt27;
	/**
	 * 限购限制类型
	 */
	public final class EDiscountLimitType
	{
		public static const eDiscountLimitTypeNO:int = 0; //无条件
		public static const eDiscountLimitTypeRecharge:int = 1; //充值限购
		public static const eDiscountLimitTypeConsume:int = 2; //消费限购
		public static const eDiscountLimitTypeEnd:int = 3; //限购类型
		public static const end:int = eDiscountLimitTypeEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eDiscountLimitTypeNO:
					return ProtocolMessageProt27.eDiscountLimitTypeNO;
				case eDiscountLimitTypeRecharge:
					return ProtocolMessageProt27.eDiscountLimitTypeRecharge;
				case eDiscountLimitTypeConsume:
					return ProtocolMessageProt27.eDiscountLimitTypeConsume;
				case eDiscountLimitTypeEnd:
					return ProtocolMessageProt27.eDiscountLimitTypeEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
