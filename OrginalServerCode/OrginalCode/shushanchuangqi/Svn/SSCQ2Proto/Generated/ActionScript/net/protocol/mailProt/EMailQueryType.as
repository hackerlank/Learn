/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMailQueryType.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
 {
	import net.protocol.Message.ProtocolMessageProt19;
	/**
	 * 邮件状态
	 */
	public final class EMailQueryType
	{
		public static const eQueryNew:uint = 0; //新邮件
		public static const eQueryReaded:uint = 1; //已读
		public static const eQueryTotal:uint = 2; //全部
		public static const eQueryPerson:uint = 3; //个人
		public static const eQuerysysTem:uint = 4; //系统
		public static const eQueryAttch:uint = 5; //附件
		public static const end:uint = eQueryAttch;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eQueryNew:
					return ProtocolMessageProt19.eQueryNew;
				case eQueryReaded:
					return ProtocolMessageProt19.eQueryReaded;
				case eQueryTotal:
					return ProtocolMessageProt19.eQueryTotal;
				case eQueryPerson:
					return ProtocolMessageProt19.eQueryPerson;
				case eQuerysysTem:
					return ProtocolMessageProt19.eQuerysysTem;
				case eQueryAttch:
					return ProtocolMessageProt19.eQueryAttch;
				default:
					return "Unknown Error";
			}
		}
	}
}
