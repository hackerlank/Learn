/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ERegisterSevenDaysResult.as
//  Purpose:      注册七天目标协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.registerSevenDaysProt
 {
	import net.protocol.Message.ProtocolMessageProt89;
	/**
	 * 操作结果
	 */
	public final class ERegisterSevenDaysResult
	{
		public static const eSucceed:uint = 0; //成功
		public static const eFailed:uint = 1; //失败
		public static const end:uint = eFailed;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eSucceed:
					return ProtocolMessageProt89.eSucceed;
				case eFailed:
					return ProtocolMessageProt89.eFailed;
				default:
					return "Unknown Error";
			}
		}
	}
}
