/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMailType.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
 {
	import net.protocol.Message.ProtocolMessageProt19;
	/**
	 * 邮件类型
	 */
	public final class EMailType
	{
		public static const EMAILTYPE_NORMAL:uint = 0; //普通邮件
		public static const EMAILTYPE_SYSTEM:uint = 1; //系统邮件
		public static const end:uint = EMAILTYPE_SYSTEM;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EMAILTYPE_NORMAL:
					return ProtocolMessageProt19.EMAILTYPE_NORMAL;
				case EMAILTYPE_SYSTEM:
					return ProtocolMessageProt19.EMAILTYPE_SYSTEM;
				default:
					return "Unknown Error";
			}
		}
	}
}
