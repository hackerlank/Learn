/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDgnSubType.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
 {
	import net.protocol.Message.ProtocolMessageProt59;
	/**
	 * 副本次类型
	 */
	public final class EDgnSubType
	{
		public static const eSubCommon:uint = 0; //普通
		public static const eSubHero:uint = 1; //英雄副本
		public static const eSubHistory:uint = 2; //史诗副本
		public static const eSubLiXian:uint = 3; //历险副本
		public static const end:uint = eSubLiXian;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eSubCommon:
					return ProtocolMessageProt59.eSubCommon;
				case eSubHero:
					return ProtocolMessageProt59.eSubHero;
				case eSubHistory:
					return ProtocolMessageProt59.eSubHistory;
				case eSubLiXian:
					return ProtocolMessageProt59.eSubLiXian;
				default:
					return "Unknown Error";
			}
		}
	}
}
