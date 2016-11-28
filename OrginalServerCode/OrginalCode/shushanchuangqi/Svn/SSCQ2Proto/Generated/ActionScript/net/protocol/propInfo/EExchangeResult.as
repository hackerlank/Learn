/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EExchangeResult.as
//  Purpose:      属性相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.propInfo
 {
	import net.protocol.Message.ProtocolMessageProt17;
	/**
	 * 兑换结果
	 */
	public final class EExchangeResult
	{
		public static const eExchangeResultSuccess:uint = 0; //兑换成功
		public static const eExchangeResultFailed:uint = 1; //兑换失败
		public static const eExchangeResultLack:uint = 2; //兑换数量不足
		public static const eExchangeResultLimit:uint = 3; //兑换已达上限
		public static const eExchangeResultMax:uint = 4; //兑换结果最大值
		public static const end:uint = eExchangeResultMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eExchangeResultSuccess:
					return ProtocolMessageProt17.eExchangeResultSuccess;
				case eExchangeResultFailed:
					return ProtocolMessageProt17.eExchangeResultFailed;
				case eExchangeResultLack:
					return ProtocolMessageProt17.eExchangeResultLack;
				case eExchangeResultLimit:
					return ProtocolMessageProt17.eExchangeResultLimit;
				case eExchangeResultMax:
					return ProtocolMessageProt17.eExchangeResultMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
