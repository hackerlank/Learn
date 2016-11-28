/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EAchievementShareType.as
//  Purpose:      成就相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.achievementProt
 {
	import net.protocol.Message.ProtocolMessageProt75;
	/**
	 * 成就分享类型
	 */
	public final class EAchievementShareType
	{
		public static const eAchievementShareType_Invalid:uint = 0; //无效类型
		public static const eAchievementShareType_Friend:uint = 1; //qq好友分享
		public static const eAchievementShareType_Game:uint = 2; //游戏内炫耀
		public static const end:uint = eAchievementShareType_Game;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eAchievementShareType_Invalid:
					return ProtocolMessageProt75.eAchievementShareType_Invalid;
				case eAchievementShareType_Friend:
					return ProtocolMessageProt75.eAchievementShareType_Friend;
				case eAchievementShareType_Game:
					return ProtocolMessageProt75.eAchievementShareType_Game;
				default:
					return "Unknown Error";
			}
		}
	}
}
