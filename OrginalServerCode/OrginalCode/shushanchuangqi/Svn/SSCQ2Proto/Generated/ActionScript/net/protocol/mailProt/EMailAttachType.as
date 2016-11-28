/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMailAttachType.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
 {
	import net.protocol.Message.ProtocolMessageProt19;
	/**
	 * 附件类型
	 */
	public final class EMailAttachType
	{
		public static const ATTACH_ITEM:uint = 0; //有模板物品
		public static const ATTACH_INSTANCE:uint = 1; //有实例物品
		public static const ATTACH_MAX:uint = 255; //不当位处理，作为附件已经领取的特殊标记
		public static const end:uint = ATTACH_MAX;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ATTACH_ITEM:
					return ProtocolMessageProt19.ATTACH_ITEM;
				case ATTACH_INSTANCE:
					return ProtocolMessageProt19.ATTACH_INSTANCE;
				case ATTACH_MAX:
					return ProtocolMessageProt19.ATTACH_MAX;
				default:
					return "Unknown Error";
			}
		}
	}
}
