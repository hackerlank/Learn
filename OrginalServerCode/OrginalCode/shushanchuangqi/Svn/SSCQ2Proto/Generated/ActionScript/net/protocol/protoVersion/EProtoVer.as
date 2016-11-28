/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EProtoVer.as
//  Purpose:      协议版本号
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoVersion
 {
	import net.protocol.Message.ProtocolMessageProt259;
	/**
	 * 协议版本
	 */
	public final class EProtoVer
	{
		public static const EPROTOVERSION:uint = 14080801; //版本号，年2位(14),月2位(07),日2位，序号2位
		public static const end:uint = EPROTOVERSION;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EPROTOVERSION:
					return ProtocolMessageProt259.EPROTOVERSION;
				default:
					return "Unknown Error";
			}
		}
	}
}
