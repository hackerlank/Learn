/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EChatShowResult.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
 {
	import net.protocol.Message.ProtocolMessageProt28;
	/**
	 * 获取展示道具结果
	 */
	public final class EChatShowResult
	{
		public static const eChatShowSucceed:uint = 0; //成功
		public static const eChatShowNotExist:uint = 1; //展示道具不存在
		public static const eChatShowErrOther:uint = 2; //其他错误
		public static const end:uint = eChatShowErrOther;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eChatShowSucceed:
					return ProtocolMessageProt28.eChatShowSucceed;
				case eChatShowNotExist:
					return ProtocolMessageProt28.eChatShowNotExist;
				case eChatShowErrOther:
					return ProtocolMessageProt28.eChatShowErrOther;
				default:
					return "Unknown Error";
			}
		}
	}
}
