/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EChannelType.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
 {
	import net.protocol.Message.ProtocolMessageProt28;
	/**
	 * 通道类型
	 */
	public final class EChannelType
	{
		public static const eChannelNone:uint = 0; //None
		public static const eChannelAll:uint = 1; //综合
		public static const eChannelWorld:uint = 2; //世界
		public static const eChannelGuild:uint = 3; //帮派
		public static const eChannelSys:uint = 4; //系统
		public static const eChannelTeam:uint = 5; //组队
		public static const eChannelNoLabelSys:uint = 6; //无字系统消息
		public static const end:uint = eChannelNoLabelSys;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eChannelNone:
					return ProtocolMessageProt28.eChannelNone;
				case eChannelAll:
					return ProtocolMessageProt28.eChannelAll;
				case eChannelWorld:
					return ProtocolMessageProt28.eChannelWorld;
				case eChannelGuild:
					return ProtocolMessageProt28.eChannelGuild;
				case eChannelSys:
					return ProtocolMessageProt28.eChannelSys;
				case eChannelTeam:
					return ProtocolMessageProt28.eChannelTeam;
				case eChannelNoLabelSys:
					return ProtocolMessageProt28.eChannelNoLabelSys;
				default:
					return "Unknown Error";
			}
		}
	}
}
