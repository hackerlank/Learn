/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGBUserState.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt76;
	/**
	 * 帮派战玩家状态
	 */
	public final class EGBUserState
	{
		public static const eGBUserStateNone:uint = 0; //无效状态
		public static const eGBUserStatePrepare:uint = 1; //准备状态(在准备场中)
		public static const eGBUserStateWait:uint = 2; //待战状态
		public static const eGBUserStateBattle:uint = 3; //战斗状态
		public static const eGBUserStateDead:uint = 4; //死亡状态
		public static const eGBUserStateWin:uint = 5; //胜利状态
		public static const eGBUserStateWinTooMuch:uint = 6; //连胜八场，封刀
		public static const eGBUserStateRunAway:uint = 7; //逃跑状态
		public static const eGBUserStateMax:uint = 8; //最大状态
		public static const end:uint = eGBUserStateMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBUserStateNone:
					return ProtocolMessageProt76.eGBUserStateNone;
				case eGBUserStatePrepare:
					return ProtocolMessageProt76.eGBUserStatePrepare;
				case eGBUserStateWait:
					return ProtocolMessageProt76.eGBUserStateWait;
				case eGBUserStateBattle:
					return ProtocolMessageProt76.eGBUserStateBattle;
				case eGBUserStateDead:
					return ProtocolMessageProt76.eGBUserStateDead;
				case eGBUserStateWin:
					return ProtocolMessageProt76.eGBUserStateWin;
				case eGBUserStateWinTooMuch:
					return ProtocolMessageProt76.eGBUserStateWinTooMuch;
				case eGBUserStateRunAway:
					return ProtocolMessageProt76.eGBUserStateRunAway;
				case eGBUserStateMax:
					return ProtocolMessageProt76.eGBUserStateMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
