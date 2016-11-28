/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMallType.as
//  Purpose:      商城相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
 {
	import net.protocol.Message.ProtocolMessageProt27;
	/**
	 * 商城类型
	 */
	public final class EMallType
	{
		public static const eMallGold:int = 1; //奇珍商城
		public static const eMallFashion:int = 2; //时装商城
		public static const eMallVIP:int = 3; //VIP商城
		public static const eMallPrestige:int = 4; //声望商城
		public static const eMallHonor:int = 5; //荣誉商城
		public static const eMallCoupon:int = 6; //礼券商城
		public static const eMallSilver:int = 7; //银币商城
		public static const eMallLimit:int = 8; //限购商城
		public static const eMallGem:int = 9; //宝石商城
		public static const eMallEnd:int = 10; //商城
		public static const end:int = eMallEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eMallGold:
					return ProtocolMessageProt27.eMallGold;
				case eMallFashion:
					return ProtocolMessageProt27.eMallFashion;
				case eMallVIP:
					return ProtocolMessageProt27.eMallVIP;
				case eMallPrestige:
					return ProtocolMessageProt27.eMallPrestige;
				case eMallHonor:
					return ProtocolMessageProt27.eMallHonor;
				case eMallCoupon:
					return ProtocolMessageProt27.eMallCoupon;
				case eMallSilver:
					return ProtocolMessageProt27.eMallSilver;
				case eMallLimit:
					return ProtocolMessageProt27.eMallLimit;
				case eMallGem:
					return ProtocolMessageProt27.eMallGem;
				case eMallEnd:
					return ProtocolMessageProt27.eMallEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
