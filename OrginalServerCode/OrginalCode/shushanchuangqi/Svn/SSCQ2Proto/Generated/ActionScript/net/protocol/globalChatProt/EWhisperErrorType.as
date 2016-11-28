/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EWhisperErrorType.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
 {
	import net.protocol.Message.ProtocolMessageProt28;
	/**
	 * 私聊错误类型
	 */
	public final class EWhisperErrorType
	{
		public static const eWhisperTooFastErr:uint = 0; //太快
		public static const eWhisperOfflineErr:uint = 1; //目标不在线
		public static const eWhisperLengthErr:uint = 2; //信息长度不对
		public static const end:uint = eWhisperLengthErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eWhisperTooFastErr:
					return ProtocolMessageProt28.eWhisperTooFastErr;
				case eWhisperOfflineErr:
					return ProtocolMessageProt28.eWhisperOfflineErr;
				case eWhisperLengthErr:
					return ProtocolMessageProt28.eWhisperLengthErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
