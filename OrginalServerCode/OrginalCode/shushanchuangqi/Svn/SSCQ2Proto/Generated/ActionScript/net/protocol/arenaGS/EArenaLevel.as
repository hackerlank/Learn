/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EArenaLevel.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
 {
	import net.protocol.Message.ProtocolMessageProt26;
	/**
	 * 竞技等级
	 */
	public final class EArenaLevel
	{
		public static const EArenaLevel_NONE:uint = 0; //无等级
		public static const EArenaLevel_IRON:uint = 1; //黑铁
		public static const EArenaLevel_COPPER:uint = 2; //青铜
		public static const EArenaLevel_SILVER:uint = 3; //白银
		public static const EArenaLevel_GOLD:uint = 4; //黄金
		public static const EArenaLevel_DIAMOND:uint = 5; //钻石
		public static const EArenaLevel_END:uint = 6; //最大值
		public static const end:uint = EArenaLevel_END;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EArenaLevel_NONE:
					return ProtocolMessageProt26.EArenaLevel_NONE;
				case EArenaLevel_IRON:
					return ProtocolMessageProt26.EArenaLevel_IRON;
				case EArenaLevel_COPPER:
					return ProtocolMessageProt26.EArenaLevel_COPPER;
				case EArenaLevel_SILVER:
					return ProtocolMessageProt26.EArenaLevel_SILVER;
				case EArenaLevel_GOLD:
					return ProtocolMessageProt26.EArenaLevel_GOLD;
				case EArenaLevel_DIAMOND:
					return ProtocolMessageProt26.EArenaLevel_DIAMOND;
				case EArenaLevel_END:
					return ProtocolMessageProt26.EArenaLevel_END;
				default:
					return "Unknown Error";
			}
		}
	}
}
