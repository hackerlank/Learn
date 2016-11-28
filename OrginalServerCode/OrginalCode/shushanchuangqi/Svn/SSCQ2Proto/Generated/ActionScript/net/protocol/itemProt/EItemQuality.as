/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EItemQuality.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 道具品质
	 */
	public final class EItemQuality
	{
		public static const eColorNone:uint = 0; //无
		public static const eColorGreen:uint = 1; //绿
		public static const eColorBlue:uint = 2; //蓝
		public static const eColorPurple:uint = 3; //紫
		public static const eColorOrange:uint = 4; //橙
		public static const eColorBlackGold:uint = 5; //暗金
		public static const eColorEnd:uint = 6; //结束
		public static const end:uint = eColorEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eColorNone:
					return ProtocolMessageProt18.eColorNone;
				case eColorGreen:
					return ProtocolMessageProt18.eColorGreen;
				case eColorBlue:
					return ProtocolMessageProt18.eColorBlue;
				case eColorPurple:
					return ProtocolMessageProt18.eColorPurple;
				case eColorOrange:
					return ProtocolMessageProt18.eColorOrange;
				case eColorBlackGold:
					return ProtocolMessageProt18.eColorBlackGold;
				case eColorEnd:
					return ProtocolMessageProt18.eColorEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
