/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBattleArrayRet.as
//  Purpose:      破阵
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
 {
	import net.protocol.Message.ProtocolMessageProt130;
	/**
	 * 破阵操作结果
	 */
	public final class EBattleArrayRet
	{
		public static const eBattleArrayRet_Sucess:uint = 0; //成功
		public static const eBattleArrayRet_LevelLimit:uint = 1; //等级不够
		public static const eBattleArrayRet_PreID:uint = 2; //前置阵未破
		public static const eBattleArrayRet_PosLimit:uint = 3; //阵位只能一次
		public static const eBattleArrayRet_AttackLimit:uint = 4; //攻击次数限制
		public static const eBattleArrayRet_TotalAttackLimit:uint = 5; //总攻击次数一次
		public static const eBattleArrayRet_ErrorCFG:uint = 6; //配置错误
		public static const eBattleArrayRet_PreLevel:uint = 7; //阵图未解锁
		public static const eBattleArrayRet_NoPass:uint = 8; //未破阵图
		public static const eBattleArrayRet_TakePrized:uint = 9; //已经领过奖励
		public static const eBattleArrayRet_PackError:uint = 10; //背包格子不够
		public static const eBattleArrayRet_MoneyError:uint = 11; //钻石不够
		public static const eBattleArrayRet_MaxBuyCnt:uint = 12; //超过最大购买次数
		public static const eBattleArrayRet_AttackCd:uint = 13; //攻击cd
		public static const end:uint = eBattleArrayRet_AttackCd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBattleArrayRet_Sucess:
					return ProtocolMessageProt130.eBattleArrayRet_Sucess;
				case eBattleArrayRet_LevelLimit:
					return ProtocolMessageProt130.eBattleArrayRet_LevelLimit;
				case eBattleArrayRet_PreID:
					return ProtocolMessageProt130.eBattleArrayRet_PreID;
				case eBattleArrayRet_PosLimit:
					return ProtocolMessageProt130.eBattleArrayRet_PosLimit;
				case eBattleArrayRet_AttackLimit:
					return ProtocolMessageProt130.eBattleArrayRet_AttackLimit;
				case eBattleArrayRet_TotalAttackLimit:
					return ProtocolMessageProt130.eBattleArrayRet_TotalAttackLimit;
				case eBattleArrayRet_ErrorCFG:
					return ProtocolMessageProt130.eBattleArrayRet_ErrorCFG;
				case eBattleArrayRet_PreLevel:
					return ProtocolMessageProt130.eBattleArrayRet_PreLevel;
				case eBattleArrayRet_NoPass:
					return ProtocolMessageProt130.eBattleArrayRet_NoPass;
				case eBattleArrayRet_TakePrized:
					return ProtocolMessageProt130.eBattleArrayRet_TakePrized;
				case eBattleArrayRet_PackError:
					return ProtocolMessageProt130.eBattleArrayRet_PackError;
				case eBattleArrayRet_MoneyError:
					return ProtocolMessageProt130.eBattleArrayRet_MoneyError;
				case eBattleArrayRet_MaxBuyCnt:
					return ProtocolMessageProt130.eBattleArrayRet_MaxBuyCnt;
				case eBattleArrayRet_AttackCd:
					return ProtocolMessageProt130.eBattleArrayRet_AttackCd;
				default:
					return "Unknown Error";
			}
		}
	}
}
