/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGBState.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt76;
	/**
	 * 帮派战当前状态
	 */
	public final class EGBState
	{
		public static const eGBStateNone:uint = 0; //没有开启或即将开启的帮派战
		public static const eGBStatePreReady:uint = 1; //帮派战报名即将开启
		public static const eGBStateReady:uint = 2; //帮派战即将开启，报名阶段
		public static const eGBStatePrepare:uint = 3; //帮派战准备中
		public static const eGBStateBattle:uint = 4; //帮派战进行中
		public static const eGBStateBattleEnd:uint = 5; //帮派战战役结束
		public static const end:uint = eGBStateBattleEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBStateNone:
					return ProtocolMessageProt76.eGBStateNone;
				case eGBStatePreReady:
					return ProtocolMessageProt76.eGBStatePreReady;
				case eGBStateReady:
					return ProtocolMessageProt76.eGBStateReady;
				case eGBStatePrepare:
					return ProtocolMessageProt76.eGBStatePrepare;
				case eGBStateBattle:
					return ProtocolMessageProt76.eGBStateBattle;
				case eGBStateBattleEnd:
					return ProtocolMessageProt76.eGBStateBattleEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
