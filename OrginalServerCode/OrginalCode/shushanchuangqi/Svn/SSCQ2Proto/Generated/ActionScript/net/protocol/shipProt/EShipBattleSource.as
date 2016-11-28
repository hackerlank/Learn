/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EShipBattleSource.as
//  Purpose:      元江金船协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
 {
	import net.protocol.Message.ProtocolMessageProt84;
	/**
	 * 战斗原因
	 */
	public final class EShipBattleSource
	{
		public static const EBS_OPENSHIP:uint = 0; //开船
		public static const EBS_ROBWITHOWER:uint = 1; //打劫与船主战斗
		public static const EBS_ROBWITHDEFENSE:uint = 2; //打劫与护卫战斗
		public static const EBS_GRABBYOWER:uint = 3; //返抢与船主战斗
		public static const EBS_GRABBYDEFENSE:uint = 4; //返抢与护卫战斗
		public static const EBS_CLOSESHIP:uint = 5; //结束航运
		public static const end:uint = EBS_CLOSESHIP;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EBS_OPENSHIP:
					return ProtocolMessageProt84.EBS_OPENSHIP;
				case EBS_ROBWITHOWER:
					return ProtocolMessageProt84.EBS_ROBWITHOWER;
				case EBS_ROBWITHDEFENSE:
					return ProtocolMessageProt84.EBS_ROBWITHDEFENSE;
				case EBS_GRABBYOWER:
					return ProtocolMessageProt84.EBS_GRABBYOWER;
				case EBS_GRABBYDEFENSE:
					return ProtocolMessageProt84.EBS_GRABBYDEFENSE;
				case EBS_CLOSESHIP:
					return ProtocolMessageProt84.EBS_CLOSESHIP;
				default:
					return "Unknown Error";
			}
		}
	}
}
