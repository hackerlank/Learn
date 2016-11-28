/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EChannelSubType.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
 {
	import net.protocol.Message.ProtocolMessageProt28;
	/**
	 * 消息额外类型
	 */
	public final class EChannelSubType
	{
		public static const eSubNone:uint = 0; //无
		public static const eSubBulletin:uint = 1; //公告区域
		public static const eSubBroadcast:uint = 2; //广播区域
		public static const eSubHorn:uint = 3; //喇叭区域
		public static const eSubSuspension:uint = 4; //悬浮区域
		public static const eSubPrompt:uint = 5; //提示区域
		public static const eSubEnd:uint = 6; //结束
		public static const end:uint = eSubEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eSubNone:
					return ProtocolMessageProt28.eSubNone;
				case eSubBulletin:
					return ProtocolMessageProt28.eSubBulletin;
				case eSubBroadcast:
					return ProtocolMessageProt28.eSubBroadcast;
				case eSubHorn:
					return ProtocolMessageProt28.eSubHorn;
				case eSubSuspension:
					return ProtocolMessageProt28.eSubSuspension;
				case eSubPrompt:
					return ProtocolMessageProt28.eSubPrompt;
				case eSubEnd:
					return ProtocolMessageProt28.eSubEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
