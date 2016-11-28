/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EItemLoggerType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 道具日志类型
	 */
	public final class EItemLoggerType
	{
		public static const eItemLogger1:uint = 0; //试炼塔道具日志
		public static const end:uint = eItemLogger1;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eItemLogger1:
					return ProtocolMessageProt18.eItemLogger1;
				default:
					return "Unknown Error";
			}
		}
	}
}
