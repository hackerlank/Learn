/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBPlayerState.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派战玩家状态
	 */
	public final class ENGBPlayerState
	{
		public static const eNGBPSNone:uint = 0; //无效状态
		public static const eNGBPSWait:uint = 1; //待战状态
		public static const eNGBPSDead:uint = 2; //死亡状态
		public static const eNGBPSRunAway:uint = 3; //逃跑状态
		public static const eNGBPSMax:uint = 4; //最大状态
		public static const end:uint = eNGBPSMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBPSNone:
					return ProtocolMessageProt68.eNGBPSNone;
				case eNGBPSWait:
					return ProtocolMessageProt68.eNGBPSWait;
				case eNGBPSDead:
					return ProtocolMessageProt68.eNGBPSDead;
				case eNGBPSRunAway:
					return ProtocolMessageProt68.eNGBPSRunAway;
				case eNGBPSMax:
					return ProtocolMessageProt68.eNGBPSMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
