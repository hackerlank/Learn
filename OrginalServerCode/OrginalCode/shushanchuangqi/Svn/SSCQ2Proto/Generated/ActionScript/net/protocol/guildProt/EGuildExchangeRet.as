/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGuildExchangeRet.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 帮派兑换错误码
	 */
	public final class EGuildExchangeRet
	{
		public static const eGuildExchange_Failed:uint = 0; //失败
		public static const eGuildExchange_Sucess:uint = 1; //成功
		public static const eGuildExchange_ErrorPack:uint = 2; //背包满无法添加物品
		public static const eGuildExchange_MoneyLimit:uint = 3; //钱币不够
		public static const eGuildExchange_CondLimitA:uint = 4; //商品剩余数量为0
		public static const eGuildExchange_CondLimitB:uint = 5; //帮派成员每天购买次数达到上限
		public static const eGuildExchange_CondLimitC:uint = 6; //帮派所有成员每天购买次数达到上限
		public static const eGuildExchange_NoLingShan:uint = 7; //要占领该据点才可兑换
		public static const end:uint = eGuildExchange_NoLingShan;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGuildExchange_Failed:
					return ProtocolMessageProt16.eGuildExchange_Failed;
				case eGuildExchange_Sucess:
					return ProtocolMessageProt16.eGuildExchange_Sucess;
				case eGuildExchange_ErrorPack:
					return ProtocolMessageProt16.eGuildExchange_ErrorPack;
				case eGuildExchange_MoneyLimit:
					return ProtocolMessageProt16.eGuildExchange_MoneyLimit;
				case eGuildExchange_CondLimitA:
					return ProtocolMessageProt16.eGuildExchange_CondLimitA;
				case eGuildExchange_CondLimitB:
					return ProtocolMessageProt16.eGuildExchange_CondLimitB;
				case eGuildExchange_CondLimitC:
					return ProtocolMessageProt16.eGuildExchange_CondLimitC;
				case eGuildExchange_NoLingShan:
					return ProtocolMessageProt16.eGuildExchange_NoLingShan;
				default:
					return "Unknown Error";
			}
		}
	}
}
