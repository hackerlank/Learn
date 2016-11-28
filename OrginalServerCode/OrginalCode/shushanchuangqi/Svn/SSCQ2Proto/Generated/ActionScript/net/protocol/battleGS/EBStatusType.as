/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBStatusType.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
 {
	import net.protocol.Message.ProtocolMessageProt21;
	/**
	 * 被动状态枚举
	 */
	public final class EBStatusType
	{
		public static const EBStatusType_Evade:uint = 0; //闪避
		public static const EBStatusType_Resist:uint = 1; //抵抗
		public static const EBStatusType_Immu:uint = 2; //免疫
		public static const EBStatusType_Block:uint = 3; //格挡
		public static const end:uint = EBStatusType_Block;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EBStatusType_Evade:
					return ProtocolMessageProt21.EBStatusType_Evade;
				case EBStatusType_Resist:
					return ProtocolMessageProt21.EBStatusType_Resist;
				case EBStatusType_Immu:
					return ProtocolMessageProt21.EBStatusType_Immu;
				case EBStatusType_Block:
					return ProtocolMessageProt21.EBStatusType_Block;
				default:
					return "Unknown Error";
			}
		}
	}
}
