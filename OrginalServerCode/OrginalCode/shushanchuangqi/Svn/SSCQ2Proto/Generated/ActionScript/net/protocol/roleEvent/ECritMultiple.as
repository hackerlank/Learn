/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECritMultiple.as
//  Purpose:      玩家在GameServer的消息处理
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
 {
	import net.protocol.Message.ProtocolMessageProt11;
	/**
	 * 暴击倍数
	 */
	public final class ECritMultiple
	{
		public static const eTwoMultipleCrit:int = 0; //2倍暴击
		public static const eFiveMultipleCrit:int = 1; //5倍暴击
		public static const eTenMultipleCrit:int = 2; //10倍暴击
		public static const end:int = eTenMultipleCrit;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eTwoMultipleCrit:
					return ProtocolMessageProt11.eTwoMultipleCrit;
				case eFiveMultipleCrit:
					return ProtocolMessageProt11.eFiveMultipleCrit;
				case eTenMultipleCrit:
					return ProtocolMessageProt11.eTenMultipleCrit;
				default:
					return "Unknown Error";
			}
		}
	}
}
