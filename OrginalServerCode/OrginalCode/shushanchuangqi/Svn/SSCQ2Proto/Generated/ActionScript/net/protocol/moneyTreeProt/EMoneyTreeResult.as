/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMoneyTreeResult.as
//  Purpose:      摇钱树协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.moneyTreeProt
 {
	import net.protocol.Message.ProtocolMessageProt88;
	/**
	 * 操作结果
	 */
	public final class EMoneyTreeResult
	{
		public static const Succeed:uint = 0; //成功
		public static const Error:uint = 1; //失败
		public static const end:uint = Error;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case Succeed:
					return ProtocolMessageProt88.Succeed;
				case Error:
					return ProtocolMessageProt88.Error;
				default:
					return "Unknown Error";
			}
		}
	}
}
