/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ELogicType.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
 {
	import net.protocol.Message.ProtocolMessageProt59;
	/**
	 * 副本评价
	 */
	public final class ELogicType
	{
		public static const eLogicNone:uint = 0; //无评价
		public static const eLogicOrderMonster:uint = 1; //按顺序杀怪
		public static const end:uint = eLogicOrderMonster;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eLogicNone:
					return ProtocolMessageProt59.eLogicNone;
				case eLogicOrderMonster:
					return ProtocolMessageProt59.eLogicOrderMonster;
				default:
					return "Unknown Error";
			}
		}
	}
}
