/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EExchangeShop.as
//  Purpose:      兑换商店
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.exchangeShopProt
 {
	import net.protocol.Message.ProtocolMessageProt101;
	/**
	 * 兑换商店错误码
	 */
	public final class EExchangeShop
	{
		public static const eExchangeShop_Sucess:uint = 0; //成功
		public static const eExchangeShop_CfgLimit:uint = 1; //没有该兑换商品
		public static const eExchangeShop_MoneyLimit:uint = 2; //钱不够
		public static const eExchangeShop_CondLimit:uint = 3; //购买条件不满足
		public static const eExchangeShop_CountLimit:uint = 4; //购买数量限制
		public static const eExchangeShop_ErrorItemID:uint = 5; //物品配置找不到
		public static const eExchangeShop_ErrorPack:uint = 6; //背包满无法添加物品
		public static const end:uint = eExchangeShop_ErrorPack;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eExchangeShop_Sucess:
					return ProtocolMessageProt101.eExchangeShop_Sucess;
				case eExchangeShop_CfgLimit:
					return ProtocolMessageProt101.eExchangeShop_CfgLimit;
				case eExchangeShop_MoneyLimit:
					return ProtocolMessageProt101.eExchangeShop_MoneyLimit;
				case eExchangeShop_CondLimit:
					return ProtocolMessageProt101.eExchangeShop_CondLimit;
				case eExchangeShop_CountLimit:
					return ProtocolMessageProt101.eExchangeShop_CountLimit;
				case eExchangeShop_ErrorItemID:
					return ProtocolMessageProt101.eExchangeShop_ErrorItemID;
				case eExchangeShop_ErrorPack:
					return ProtocolMessageProt101.eExchangeShop_ErrorPack;
				default:
					return "Unknown Error";
			}
		}
	}
}
