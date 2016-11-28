/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EXinFaResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 心法返回
	 */
	public final class EXinFaResult
	{
		public static const eXinFaSucc:uint = 0; //成功
		public static const eXinFaFailed:uint = 1; //失败
		public static const end:uint = eXinFaFailed;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eXinFaSucc:
					return ProtocolMessageProt20.eXinFaSucc;
				case eXinFaFailed:
					return ProtocolMessageProt20.eXinFaFailed;
				default:
					return "Unknown Error";
			}
		}
	}
}
