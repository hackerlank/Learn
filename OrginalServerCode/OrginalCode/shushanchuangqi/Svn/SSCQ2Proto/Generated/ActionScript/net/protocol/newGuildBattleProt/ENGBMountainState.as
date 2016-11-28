/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBMountainState.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派灵山状态
	 */
	public final class ENGBMountainState
	{
		public static const eNGBMSNone:uint = 0; //无效状态
		public static const eNGBMSGate:uint = 1; //城门战
		public static const eNGBMSCave:uint = 2; //洞府战
		public static const eNGBMSEnd:uint = 3; //战斗结束
		public static const eNGBMSMax:uint = 4; //最大状态
		public static const end:uint = eNGBMSMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBMSNone:
					return ProtocolMessageProt68.eNGBMSNone;
				case eNGBMSGate:
					return ProtocolMessageProt68.eNGBMSGate;
				case eNGBMSCave:
					return ProtocolMessageProt68.eNGBMSCave;
				case eNGBMSEnd:
					return ProtocolMessageProt68.eNGBMSEnd;
				case eNGBMSMax:
					return ProtocolMessageProt68.eNGBMSMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
