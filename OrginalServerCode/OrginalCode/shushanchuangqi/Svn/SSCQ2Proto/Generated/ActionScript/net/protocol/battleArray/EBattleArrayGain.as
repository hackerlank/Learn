/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBattleArrayGain.as
//  Purpose:      破阵
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleArray
 {
	import net.protocol.Message.ProtocolMessageProt130;
	/**
	 * 获的物品的类型
	 */
	public final class EBattleArrayGain
	{
		public static const eBattleArrayGain_Attack:uint = 0; //攻击阵图
		public static const eBattleArrayGain_Sweep:uint = 1; //扫荡(自动破阵)
		public static const end:uint = eBattleArrayGain_Sweep;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBattleArrayGain_Attack:
					return ProtocolMessageProt130.eBattleArrayGain_Attack;
				case eBattleArrayGain_Sweep:
					return ProtocolMessageProt130.eBattleArrayGain_Sweep;
				default:
					return "Unknown Error";
			}
		}
	}
}
