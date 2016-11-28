/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBattleType.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
 {
	import net.protocol.Message.ProtocolMessageProt21;
	/**
	 * 战斗模式：PVP/PVE
	 */
	public final class EBattleType
	{
		public static const EBTINVALID:uint = 1; //PVE(攻击怪物)
		public static const EBTMonster:uint = 2; //PVE(攻击怪物)
		public static const EBTPlayer:uint = 3; //PVP(攻击玩家)
		public static const EBWorldBoss:uint = 4; //世界boss战
		public static const EBArena:uint = 5; //竞技场
		public static const EBDemonTower:uint = 6; //锁妖塔
		public static const ETreasureHunt:uint = 7; //寻宝
		public static const EGuardEMei:uint = 8; //守卫峨嵋
		public static const EBShip:uint = 9; //运船
		public static const EBShushan:uint = 10; //论剑
		public static const EBLingshan:uint = 11; //灵山寻宝
		public static const EBattleEnd:uint = 12; //结束标志
		public static const end:uint = EBattleEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EBTINVALID:
					return ProtocolMessageProt21.EBTINVALID;
				case EBTMonster:
					return ProtocolMessageProt21.EBTMonster;
				case EBTPlayer:
					return ProtocolMessageProt21.EBTPlayer;
				case EBWorldBoss:
					return ProtocolMessageProt21.EBWorldBoss;
				case EBArena:
					return ProtocolMessageProt21.EBArena;
				case EBDemonTower:
					return ProtocolMessageProt21.EBDemonTower;
				case ETreasureHunt:
					return ProtocolMessageProt21.ETreasureHunt;
				case EGuardEMei:
					return ProtocolMessageProt21.EGuardEMei;
				case EBShip:
					return ProtocolMessageProt21.EBShip;
				case EBShushan:
					return ProtocolMessageProt21.EBShushan;
				case EBLingshan:
					return ProtocolMessageProt21.EBLingshan;
				case EBattleEnd:
					return ProtocolMessageProt21.EBattleEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
