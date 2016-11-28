/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBossBuyType.as
//  Purpose:      BOSS相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
 {
	import net.protocol.Message.ProtocolMessageProt25;
	/**
	 * 购买加持类型
	 */
	public final class EBossBuyType
	{
		public static const eGold:uint = 0; //金币购买
		public static const eSliver:uint = 1; //银币购买
		public static const end:uint = eSliver;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGold:
					return ProtocolMessageProt25.eGold;
				case eSliver:
					return ProtocolMessageProt25.eSliver;
				default:
					return "Unknown Error";
			}
		}
	}
}
