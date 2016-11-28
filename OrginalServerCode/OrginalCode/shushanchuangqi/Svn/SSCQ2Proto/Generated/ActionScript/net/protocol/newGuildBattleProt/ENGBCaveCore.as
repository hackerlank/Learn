/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBCaveCore.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派战洞府战阵眼类型
	 */
	public final class ENGBCaveCore
	{
		public static const eNGBCCNone:uint = 0; //无效阵眼
		public static const eNGBCCDragon:uint = 1; //青龙
		public static const eNGBCCTiger:uint = 2; //白虎
		public static const eNGBCCPhenix:uint = 3; //朱雀
		public static const eNGBCCTurtle:uint = 4; //玄武
		public static const eNGBCCMax:uint = 5; //最大阵眼
		public static const end:uint = eNGBCCMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBCCNone:
					return ProtocolMessageProt68.eNGBCCNone;
				case eNGBCCDragon:
					return ProtocolMessageProt68.eNGBCCDragon;
				case eNGBCCTiger:
					return ProtocolMessageProt68.eNGBCCTiger;
				case eNGBCCPhenix:
					return ProtocolMessageProt68.eNGBCCPhenix;
				case eNGBCCTurtle:
					return ProtocolMessageProt68.eNGBCCTurtle;
				case eNGBCCMax:
					return ProtocolMessageProt68.eNGBCCMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
