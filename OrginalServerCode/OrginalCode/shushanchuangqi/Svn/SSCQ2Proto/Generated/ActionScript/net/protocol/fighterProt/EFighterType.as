/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EFighterType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 将类型
	 */
	public final class EFighterType
	{
		public static const eFighter:uint = 0; //将
		public static const eFighterPlayer:uint = 1; //主将
		public static const eFighterHero:uint = 2; //散仙
		public static const eFighterMonster:uint = 3; //怪
		public static const eFighterMax:uint = 4; //将类型结束
		public static const end:uint = eFighterMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eFighter:
					return ProtocolMessageProt20.eFighter;
				case eFighterPlayer:
					return ProtocolMessageProt20.eFighterPlayer;
				case eFighterHero:
					return ProtocolMessageProt20.eFighterHero;
				case eFighterMonster:
					return ProtocolMessageProt20.eFighterMonster;
				case eFighterMax:
					return ProtocolMessageProt20.eFighterMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
