/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EFighterBuyResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 购买散仙返回
	 */
	public final class EFighterBuyResult
	{
		public static const eFighterBuySucc:uint = 0; //成功
		public static const eFighterBuyFailed:uint = 1; //失败
		public static const eFighterBuyAlready:uint = 2; //已购买
		public static const eFighterBuyLackOfMoney:uint = 3; //货币不足
		public static const end:uint = eFighterBuyLackOfMoney;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eFighterBuySucc:
					return ProtocolMessageProt20.eFighterBuySucc;
				case eFighterBuyFailed:
					return ProtocolMessageProt20.eFighterBuyFailed;
				case eFighterBuyAlready:
					return ProtocolMessageProt20.eFighterBuyAlready;
				case eFighterBuyLackOfMoney:
					return ProtocolMessageProt20.eFighterBuyLackOfMoney;
				default:
					return "Unknown Error";
			}
		}
	}
}
