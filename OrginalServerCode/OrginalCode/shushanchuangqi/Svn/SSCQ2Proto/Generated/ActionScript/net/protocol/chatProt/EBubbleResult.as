/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBubbleResult.as
//  Purpose:      聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.chatProt
 {
	import net.protocol.Message.ProtocolMessageProt23;
	/**
	 * 气泡操作失败
	 */
	public final class EBubbleResult
	{
		public static const eBRSuccess:uint = 0; //气泡操作成功
		public static const eBRFailed:uint = 1; //气泡操作失败
		public static const end:uint = eBRFailed;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBRSuccess:
					return ProtocolMessageProt23.eBRSuccess;
				case eBRFailed:
					return ProtocolMessageProt23.eBRFailed;
				default:
					return "Unknown Error";
			}
		}
	}
}
