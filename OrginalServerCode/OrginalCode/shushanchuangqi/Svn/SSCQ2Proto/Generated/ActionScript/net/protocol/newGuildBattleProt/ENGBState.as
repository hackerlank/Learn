/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBState.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派战当前状态
	 */
	public final class ENGBState
	{
		public static const eNGBSNone:uint = 0; //没有开启帮派战
		public static const eNGBSReady:uint = 1; //帮派战即将开启，倒计时通知阶段
		public static const eNGBSBattle:uint = 2; //帮派战进行中
		public static const eNGBSBattleEnd:uint = 3; //帮派战战役结束
		public static const end:uint = eNGBSBattleEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBSNone:
					return ProtocolMessageProt68.eNGBSNone;
				case eNGBSReady:
					return ProtocolMessageProt68.eNGBSReady;
				case eNGBSBattle:
					return ProtocolMessageProt68.eNGBSBattle;
				case eNGBSBattleEnd:
					return ProtocolMessageProt68.eNGBSBattleEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
