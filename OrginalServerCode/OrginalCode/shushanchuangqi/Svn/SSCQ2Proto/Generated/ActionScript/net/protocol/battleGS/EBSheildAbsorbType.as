/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBSheildAbsorbType.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
 {
	import net.protocol.Message.ProtocolMessageProt21;
	/**
	 * 被动状态枚举
	 */
	public final class EBSheildAbsorbType
	{
		public static const EBSheildAbsorbPhysic:uint = 1; //吸收物理伤害
		public static const EBSheildAbsorbMagic:uint = 2; //吸收法术伤害
		public static const EBSheildAbsorbDamage:uint = 3; //吸收伤害
		public static const end:uint = EBSheildAbsorbDamage;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EBSheildAbsorbPhysic:
					return ProtocolMessageProt21.EBSheildAbsorbPhysic;
				case EBSheildAbsorbMagic:
					return ProtocolMessageProt21.EBSheildAbsorbMagic;
				case EBSheildAbsorbDamage:
					return ProtocolMessageProt21.EBSheildAbsorbDamage;
				default:
					return "Unknown Error";
			}
		}
	}
}
