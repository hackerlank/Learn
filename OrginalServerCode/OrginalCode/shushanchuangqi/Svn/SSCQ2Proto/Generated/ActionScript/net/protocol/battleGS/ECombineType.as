/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECombineType.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
 {
	import net.protocol.Message.ProtocolMessageProt21;
	/**
	 * 连携槽增长方式
	 */
	public final class ECombineType
	{
		public static const eCTNone:uint = 0; //无效方式
		public static const eCTCritical:uint = 1; //暴击
		public static const eCTBlock:uint = 2; //格挡
		public static const eCTEvade:uint = 3; //闪避
		public static const eCTCounter:uint = 4; //反击
		public static const eCTPeerless:uint = 5; //无双
		public static const eCTMax:uint = 6; //最大
		public static const end:uint = eCTMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eCTNone:
					return ProtocolMessageProt21.eCTNone;
				case eCTCritical:
					return ProtocolMessageProt21.eCTCritical;
				case eCTBlock:
					return ProtocolMessageProt21.eCTBlock;
				case eCTEvade:
					return ProtocolMessageProt21.eCTEvade;
				case eCTCounter:
					return ProtocolMessageProt21.eCTCounter;
				case eCTPeerless:
					return ProtocolMessageProt21.eCTPeerless;
				case eCTMax:
					return ProtocolMessageProt21.eCTMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
