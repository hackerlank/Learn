/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBattleArrayStatus.as
//  Purpose:      破阵
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
 {
	import net.protocol.Message.ProtocolMessageProt130;
	/**
	 * 阵状态
	 */
	public final class EBattleArrayStatus
	{
		public static const eBattleArrayStatus_Init:uint = 0; //初始状态
		public static const eBattleArrayStatus_End:uint = 1; //已破阵
		public static const eBattleArrayStatus_TakePrized:uint = 2; //已领奖
		public static const end:uint = eBattleArrayStatus_TakePrized;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBattleArrayStatus_Init:
					return ProtocolMessageProt130.eBattleArrayStatus_Init;
				case eBattleArrayStatus_End:
					return ProtocolMessageProt130.eBattleArrayStatus_End;
				case eBattleArrayStatus_TakePrized:
					return ProtocolMessageProt130.eBattleArrayStatus_TakePrized;
				default:
					return "Unknown Error";
			}
		}
	}
}
