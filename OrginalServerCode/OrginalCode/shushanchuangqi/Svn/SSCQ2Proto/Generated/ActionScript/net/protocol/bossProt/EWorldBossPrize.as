/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EWorldBossPrize.as
//  Purpose:      BOSS相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.bossProt
 {
	import net.protocol.Message.ProtocolMessageProt25;
	/**
	 * boss奖励类型
	 */
	public final class EWorldBossPrize
	{
		public static const eWorldBossPrizeTop:uint = 1; //排名奖励
		public static const eWorldBossPrizeDamage:uint = 2; //伤害奖励
		public static const eWorldBossPrizeRandom:uint = 3; //幸运奖励
		public static const eWorldBossPrizeNPC:uint = 4; //参与奖励
		public static const eWorldBossPrizeKillBoss:uint = 5; //击杀世界boss奖励
		public static const eWorldBossPrizeBossHP:uint = 6; //伤害boss百分比血量奖励
		public static const end:uint = eWorldBossPrizeBossHP;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eWorldBossPrizeTop:
					return ProtocolMessageProt25.eWorldBossPrizeTop;
				case eWorldBossPrizeDamage:
					return ProtocolMessageProt25.eWorldBossPrizeDamage;
				case eWorldBossPrizeRandom:
					return ProtocolMessageProt25.eWorldBossPrizeRandom;
				case eWorldBossPrizeNPC:
					return ProtocolMessageProt25.eWorldBossPrizeNPC;
				case eWorldBossPrizeKillBoss:
					return ProtocolMessageProt25.eWorldBossPrizeKillBoss;
				case eWorldBossPrizeBossHP:
					return ProtocolMessageProt25.eWorldBossPrizeBossHP;
				default:
					return "Unknown Error";
			}
		}
	}
}
