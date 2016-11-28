/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDrawType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 求签类型
	 */
	public final class EDrawType
	{
		public static const eDrawTypeNone:uint = 0; //无效类型
		public static const eDrawTypeNormal:uint = 1; //普通求签(银币)
		public static const eDrawTypeAdvance:uint = 2; //高级求签(仙石)
		public static const eDrawTypeMax:uint = 3; //最大类型
		public static const end:uint = eDrawTypeMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eDrawTypeNone:
					return ProtocolMessageProt20.eDrawTypeNone;
				case eDrawTypeNormal:
					return ProtocolMessageProt20.eDrawTypeNormal;
				case eDrawTypeAdvance:
					return ProtocolMessageProt20.eDrawTypeAdvance;
				case eDrawTypeMax:
					return ProtocolMessageProt20.eDrawTypeMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
