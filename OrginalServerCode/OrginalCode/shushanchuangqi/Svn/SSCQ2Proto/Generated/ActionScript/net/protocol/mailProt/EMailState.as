/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMailState.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
 {
	import net.protocol.Message.ProtocolMessageProt19;
	/**
	 * 邮件状态
	 */
	public final class EMailState
	{
		public static const eStateNew:uint = 0; //新邮件
		public static const eStateReaded:uint = 1; //已读
		public static const eStateDelete:uint = 2; //已删
		public static const end:uint = eStateDelete;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eStateNew:
					return ProtocolMessageProt19.eStateNew;
				case eStateReaded:
					return ProtocolMessageProt19.eStateReaded;
				case eStateDelete:
					return ProtocolMessageProt19.eStateDelete;
				default:
					return "Unknown Error";
			}
		}
	}
}
