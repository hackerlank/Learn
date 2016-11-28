/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBattleResult.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
 {
	import net.protocol.Message.ProtocolMessageProt21;
	/**
	 * 战斗结果
	 */
	public final class EBattleResult
	{
		public static const EBResultNone:uint = 0; //无
		public static const EBResultAttackWin:uint = 1; //攻击方胜利
		public static const EBResultDefenseWin:uint = 2; //防守方胜利
		public static const EBResultTie:uint = 3; //平局（最后血量都相同，可能为0）
		public static const end:uint = EBResultTie;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EBResultNone:
					return ProtocolMessageProt21.EBResultNone;
				case EBResultAttackWin:
					return ProtocolMessageProt21.EBResultAttackWin;
				case EBResultDefenseWin:
					return ProtocolMessageProt21.EBResultDefenseWin;
				case EBResultTie:
					return ProtocolMessageProt21.EBResultTie;
				default:
					return "Unknown Error";
			}
		}
	}
}
