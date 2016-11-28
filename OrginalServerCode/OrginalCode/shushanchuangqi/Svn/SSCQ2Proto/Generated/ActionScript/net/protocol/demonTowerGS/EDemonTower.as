/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDemonTower.as
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.demonTowerGS
 {
	import net.protocol.Message.ProtocolMessageProt71;
	/**
	 * 镇妖塔
	 */
	public final class EDemonTower
	{
		public static const eDemonTower_Sucess:uint = 0; //成功
		public static const eDemonTower_Error:uint = 1; //锁妖塔错误码
		public static const eDemonTower_NotPass:uint = 2; //未通关层数，不能进入
		public static const eDemonTower_NotInTower:uint = 3; //不在镇妖塔中
		public static const eDemonTower_Invalid_CFG:uint = 4; //配置不存在
		public static const eDemonTower_Invalid_FloorID:uint = 5; //层数错误
		public static const eDemonTower_Invalid_Positoin:uint = 6; //镇守位置错误
		public static const eDemonTower_Not_Empty_Positoin:uint = 7; //非空镇守位置
		public static const eDemonTower_Empty_Positoin:uint = 8; //空位置没有玩家镇守
		public static const eDemonTower_Empty_Prize:uint = 9; //无奖励或奖励已经领取
		public static const eDemonTower_Invalid_PrizeType:uint = 10; //错误的领奖类型
		public static const eDemonTower_Invalid_UserID:uint = 11; //玩家不在线
		public static const eDemonTower_FightCD:uint = 12; //镇守位处在战斗状态中
		public static const eDemonTower_LackMoney:uint = 13; //钻石不足
		public static const end:uint = eDemonTower_LackMoney;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eDemonTower_Sucess:
					return ProtocolMessageProt71.eDemonTower_Sucess;
				case eDemonTower_Error:
					return ProtocolMessageProt71.eDemonTower_Error;
				case eDemonTower_NotPass:
					return ProtocolMessageProt71.eDemonTower_NotPass;
				case eDemonTower_NotInTower:
					return ProtocolMessageProt71.eDemonTower_NotInTower;
				case eDemonTower_Invalid_CFG:
					return ProtocolMessageProt71.eDemonTower_Invalid_CFG;
				case eDemonTower_Invalid_FloorID:
					return ProtocolMessageProt71.eDemonTower_Invalid_FloorID;
				case eDemonTower_Invalid_Positoin:
					return ProtocolMessageProt71.eDemonTower_Invalid_Positoin;
				case eDemonTower_Not_Empty_Positoin:
					return ProtocolMessageProt71.eDemonTower_Not_Empty_Positoin;
				case eDemonTower_Empty_Positoin:
					return ProtocolMessageProt71.eDemonTower_Empty_Positoin;
				case eDemonTower_Empty_Prize:
					return ProtocolMessageProt71.eDemonTower_Empty_Prize;
				case eDemonTower_Invalid_PrizeType:
					return ProtocolMessageProt71.eDemonTower_Invalid_PrizeType;
				case eDemonTower_Invalid_UserID:
					return ProtocolMessageProt71.eDemonTower_Invalid_UserID;
				case eDemonTower_FightCD:
					return ProtocolMessageProt71.eDemonTower_FightCD;
				case eDemonTower_LackMoney:
					return ProtocolMessageProt71.eDemonTower_LackMoney;
				default:
					return "Unknown Error";
			}
		}
	}
}
