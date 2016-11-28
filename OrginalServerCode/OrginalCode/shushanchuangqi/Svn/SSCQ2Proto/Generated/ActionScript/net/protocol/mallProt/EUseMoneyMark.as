/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EUseMoneyMark.as
//  Purpose:      商城相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
 {
	import net.protocol.Message.ProtocolMessageProt27;
	/**
	 * 使用钱币标志
	 */
	public final class EUseMoneyMark
	{
		public static const eUseBindMoney:int = 0; //使用绑定钱币
		public static const eUseNoBindMoney:int = 1; //使用非绑定钱币
		public static const end:int = eUseNoBindMoney;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eUseBindMoney:
					return ProtocolMessageProt27.eUseBindMoney;
				case eUseNoBindMoney:
					return ProtocolMessageProt27.eUseNoBindMoney;
				default:
					return "Unknown Error";
			}
		}
	}
}
