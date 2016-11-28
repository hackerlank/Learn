/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EChatResult.as
//  Purpose:      聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.chatProt
 {
	import net.protocol.Message.ProtocolMessageProt23;
	/**
	 * 聊天结果提示
	 */
	public final class EChatResult
	{
		public static const eChatSucceed:uint = 0; //成功
		public static const eChatNotExist:uint = 1; //展示道具不存在
		public static const eChatErrStore:uint = 2; //容器错误
		public static const eChatErrOther:uint = 3; //其他错误
		public static const end:uint = eChatErrOther;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eChatSucceed:
					return ProtocolMessageProt23.eChatSucceed;
				case eChatNotExist:
					return ProtocolMessageProt23.eChatNotExist;
				case eChatErrStore:
					return ProtocolMessageProt23.eChatErrStore;
				case eChatErrOther:
					return ProtocolMessageProt23.eChatErrOther;
				default:
					return "Unknown Error";
			}
		}
	}
}
