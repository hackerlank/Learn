/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETEAMResult.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.teamGS
 {
	import net.protocol.Message.ProtocolMessageProt56;
	/**
	 * 竞技场操作结果
	 */
	public final class ETEAMResult
	{
		public static const ETeam_Suc:uint = 0; //成功
		public static const ETeam_OtherTeam:uint = 1; //在其他房间中
		public static const ETeam_NOTInTeam:uint = 2; //不在房间中
		public static const ETeam_PreDgn:uint = 3; //前置副本没有通过
		public static const ETeam_PackFull:uint = 4; //包裹满
		public static const ETeam_Full:uint = 5; //房间满
		public static const ETeam_NOLeader:uint = 6; //您不是队长
		public static const ETeam_NODgnType:uint = 7; //不存在这个副本
		public static const ETeam_ErrTeam:uint = 8; //不存在这个队伍
		public static const ETeam_NewHeroErr:uint = 9; //新将不存在
		public static const ETeam_MainHero:uint = 10; //主将不可替换
		public static const ETeam_NewHeroIn:uint = 11; //新将已在
		public static const ETeam_NewHeroPosErr:uint = 12; //新将位置错误
		public static const ETeam_PlayerINReady:uint = 13; //玩家已准备
		public static const ETeam_PlayerNOReady:uint = 14; //玩家没有准备好
		public static const ETeam_MemBerNOReady:uint = 15; //有玩家没有准备好
		public static const ETeam_LowLevel:uint = 16; //等级不足，无法进入副本
		public static const ETeam_Fighters:uint = 17; //将不足，无法进入副本
		public static const ETeam_KickSelf:uint = 18; //不可踢自己
		public static const ETeam_KickErr:uint = 19; //被踢不在该队伍中
		public static const ETeam_PosErr:uint = 20; //位置不正确
		public static const ETeam_InBattle:uint = 21; //战斗中
		public static const ETeam_MinPerSon:uint = 22; //人数不足
		public static const ETeam_ErrPerSon:uint = 23; //有人不满足条件
		public static const ETeam_DiffDgn:uint = 24; //副本人数不一致
		public static const ETeam_PetErr:uint = 25; //错误玩家阵灵
		public static const ETeam_PassWord:uint = 26; //密码错误
		public static const ETeam_IsLeader:uint = 27; //已经是队长
		public static const ETeam_ErrMem:uint = 28; //不是房间成员
		public static const ETeam_OtherErr:uint = 29; //其他错误
		public static const end:uint = ETeam_OtherErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ETeam_Suc:
					return ProtocolMessageProt56.ETeam_Suc;
				case ETeam_OtherTeam:
					return ProtocolMessageProt56.ETeam_OtherTeam;
				case ETeam_NOTInTeam:
					return ProtocolMessageProt56.ETeam_NOTInTeam;
				case ETeam_PreDgn:
					return ProtocolMessageProt56.ETeam_PreDgn;
				case ETeam_PackFull:
					return ProtocolMessageProt56.ETeam_PackFull;
				case ETeam_Full:
					return ProtocolMessageProt56.ETeam_Full;
				case ETeam_NOLeader:
					return ProtocolMessageProt56.ETeam_NOLeader;
				case ETeam_NODgnType:
					return ProtocolMessageProt56.ETeam_NODgnType;
				case ETeam_ErrTeam:
					return ProtocolMessageProt56.ETeam_ErrTeam;
				case ETeam_NewHeroErr:
					return ProtocolMessageProt56.ETeam_NewHeroErr;
				case ETeam_MainHero:
					return ProtocolMessageProt56.ETeam_MainHero;
				case ETeam_NewHeroIn:
					return ProtocolMessageProt56.ETeam_NewHeroIn;
				case ETeam_NewHeroPosErr:
					return ProtocolMessageProt56.ETeam_NewHeroPosErr;
				case ETeam_PlayerINReady:
					return ProtocolMessageProt56.ETeam_PlayerINReady;
				case ETeam_PlayerNOReady:
					return ProtocolMessageProt56.ETeam_PlayerNOReady;
				case ETeam_MemBerNOReady:
					return ProtocolMessageProt56.ETeam_MemBerNOReady;
				case ETeam_LowLevel:
					return ProtocolMessageProt56.ETeam_LowLevel;
				case ETeam_Fighters:
					return ProtocolMessageProt56.ETeam_Fighters;
				case ETeam_KickSelf:
					return ProtocolMessageProt56.ETeam_KickSelf;
				case ETeam_KickErr:
					return ProtocolMessageProt56.ETeam_KickErr;
				case ETeam_PosErr:
					return ProtocolMessageProt56.ETeam_PosErr;
				case ETeam_InBattle:
					return ProtocolMessageProt56.ETeam_InBattle;
				case ETeam_MinPerSon:
					return ProtocolMessageProt56.ETeam_MinPerSon;
				case ETeam_ErrPerSon:
					return ProtocolMessageProt56.ETeam_ErrPerSon;
				case ETeam_DiffDgn:
					return ProtocolMessageProt56.ETeam_DiffDgn;
				case ETeam_PetErr:
					return ProtocolMessageProt56.ETeam_PetErr;
				case ETeam_PassWord:
					return ProtocolMessageProt56.ETeam_PassWord;
				case ETeam_IsLeader:
					return ProtocolMessageProt56.ETeam_IsLeader;
				case ETeam_ErrMem:
					return ProtocolMessageProt56.ETeam_ErrMem;
				case ETeam_OtherErr:
					return ProtocolMessageProt56.ETeam_OtherErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
