/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ERankType.as
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.rankProt
 {
	import net.protocol.Message.ProtocolMessageProt80;
	/**
	 * 排行榜类型
	 */
	public final class ERankType
	{
		public static const eRTNone:uint = 0; //无效排行榜类型
		public static const eRTHead:uint = 1; //魁首榜
		public static const eRTRoleRankBegin:uint = 2; //玩家排行榜开始索引
		public static const eRTBattlePoint:uint = eRTRoleRankBegin; //总战力榜
		public static const eRTLevel:uint = eRTRoleRankBegin + 1; //等级榜
		public static const eRTFormation:uint = eRTRoleRankBegin + 2; //阵灵榜
		public static const eRTHeroFighter:uint = eRTRoleRankBegin + 3; //散仙榜
		public static const eRTTrump:uint = eRTRoleRankBegin + 4; //法宝榜
		public static const eRTArena:uint = eRTRoleRankBegin + 5; //斗剑榜
		public static const eRTRoleRankEnd:uint = eRTArena; //玩家排行榜结束索引
		public static const eRTGuildRankBegin:uint = eRTArena + 1; //帮派排行榜开始索引
		public static const eRTGuildBattle:uint = eRTGuildRankBegin; //帮派战排行榜
		public static const eRTGuildRankEnd:uint = eRTGuildRankBegin + 1; //帮派排行榜结束索引
		public static const eRTMax:uint = eRTGuildRankBegin + 2; //排名类型最大值
		public static const end:uint = eRTMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eRTNone:
					return ProtocolMessageProt80.eRTNone;
				case eRTHead:
					return ProtocolMessageProt80.eRTHead;
				case eRTRoleRankBegin:
					return ProtocolMessageProt80.eRTRoleRankBegin;
				case eRTLevel:
					return ProtocolMessageProt80.eRTLevel;
				case eRTFormation:
					return ProtocolMessageProt80.eRTFormation;
				case eRTHeroFighter:
					return ProtocolMessageProt80.eRTHeroFighter;
				case eRTTrump:
					return ProtocolMessageProt80.eRTTrump;
				case eRTArena:
					return ProtocolMessageProt80.eRTArena;
				case eRTGuildRankBegin:
					return ProtocolMessageProt80.eRTGuildRankBegin;
				case eRTGuildRankEnd:
					return ProtocolMessageProt80.eRTGuildRankEnd;
				case eRTMax:
					return ProtocolMessageProt80.eRTMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
