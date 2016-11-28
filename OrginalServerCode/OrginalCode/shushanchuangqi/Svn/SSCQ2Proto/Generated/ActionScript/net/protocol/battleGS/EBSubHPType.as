/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBSubHPType.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
 {
	import net.protocol.Message.ProtocolMessageProt21;
	/**
	 * 扣血伤害类型（物理/法术）
	 */
	public final class EBSubHPType
	{
		public static const EBSubHPPhy:uint = 0; //物理
		public static const EBSubHPMgc:uint = 1; //法术
		public static const end:uint = EBSubHPMgc;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EBSubHPPhy:
					return ProtocolMessageProt21.EBSubHPPhy;
				case EBSubHPMgc:
					return ProtocolMessageProt21.EBSubHPMgc;
				default:
					return "Unknown Error";
			}
		}
	}
}
