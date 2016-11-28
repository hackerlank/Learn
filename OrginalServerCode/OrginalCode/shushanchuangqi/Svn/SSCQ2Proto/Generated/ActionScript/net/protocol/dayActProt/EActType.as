/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EActType.as
//  Purpose:      活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayActProt
 {
	import net.protocol.Message.ProtocolMessageProt69;
	/**
	 * 活动类型
	 */
	public final class EActType
	{
		public static const eActTypeInvalid:uint = 0;
		public static const eActTypeWorldBoss:uint = 1; //boss活动
		public static const eActTypeLangHuanBless:uint = 2; //LangHuanBless活动
		public static const eActTypeGuildBattle:uint = 3; //帮派战活动
		public static const eActTypeShushanBattle:uint = 4; //蜀山论剑活动
		public static const eActTypeEnergy:uint = 5; //剑气充盈活动
		public static const eActTypeTeamReward:uint = 6; //组队副本奖励活动
		public static const eActTypeAnswer:uint = 7; //答题活动
		public static const eActTypeLingShan:uint = 8; //秘境寻宝
		public static const eActTypeNewGuildBattle:uint = 9; //新帮派战
		public static const eActTypeChest:uint = 10; //刷宝箱
		public static const eActTypeShipReward:uint = 11; //元江金船活动
		public static const eActTypeEnd:uint = 12;
		public static const end:uint = eActTypeEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eActTypeInvalid:
					return ProtocolMessageProt69.eActTypeInvalid;
				case eActTypeWorldBoss:
					return ProtocolMessageProt69.eActTypeWorldBoss;
				case eActTypeLangHuanBless:
					return ProtocolMessageProt69.eActTypeLangHuanBless;
				case eActTypeGuildBattle:
					return ProtocolMessageProt69.eActTypeGuildBattle;
				case eActTypeShushanBattle:
					return ProtocolMessageProt69.eActTypeShushanBattle;
				case eActTypeEnergy:
					return ProtocolMessageProt69.eActTypeEnergy;
				case eActTypeTeamReward:
					return ProtocolMessageProt69.eActTypeTeamReward;
				case eActTypeAnswer:
					return ProtocolMessageProt69.eActTypeAnswer;
				case eActTypeLingShan:
					return ProtocolMessageProt69.eActTypeLingShan;
				case eActTypeNewGuildBattle:
					return ProtocolMessageProt69.eActTypeNewGuildBattle;
				case eActTypeChest:
					return ProtocolMessageProt69.eActTypeChest;
				case eActTypeShipReward:
					return ProtocolMessageProt69.eActTypeShipReward;
				case eActTypeEnd:
					return ProtocolMessageProt69.eActTypeEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
