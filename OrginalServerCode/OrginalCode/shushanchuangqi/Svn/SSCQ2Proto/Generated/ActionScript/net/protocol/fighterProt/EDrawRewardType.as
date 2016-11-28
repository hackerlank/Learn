/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDrawRewardType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 求签类型
	 */
	public final class EDrawRewardType
	{
		public static const eDrawRewardTypeNone:uint = 0; //无效类型
		public static const eDrawRewardTypeBlue:uint = 1; //蓝色仙缘
		public static const eDrawRewardTypePurple:uint = 2; //紫色仙缘
		public static const eDrawRewardTypeOrange:uint = 3; //橙色仙缘
		public static const eDrawRewardTypeMax:uint = 4; //最大类型
		public static const end:uint = eDrawRewardTypeMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eDrawRewardTypeNone:
					return ProtocolMessageProt20.eDrawRewardTypeNone;
				case eDrawRewardTypeBlue:
					return ProtocolMessageProt20.eDrawRewardTypeBlue;
				case eDrawRewardTypePurple:
					return ProtocolMessageProt20.eDrawRewardTypePurple;
				case eDrawRewardTypeOrange:
					return ProtocolMessageProt20.eDrawRewardTypeOrange;
				case eDrawRewardTypeMax:
					return ProtocolMessageProt20.eDrawRewardTypeMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
