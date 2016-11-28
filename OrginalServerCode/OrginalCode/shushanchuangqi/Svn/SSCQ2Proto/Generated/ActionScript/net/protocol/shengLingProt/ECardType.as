/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECardType.as
//  Purpose:      圣陵协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
 {
	import net.protocol.Message.ProtocolMessageProt98;
	/**
	 * 卡片类型
	 */
	public final class ECardType
	{
		public static const ECardType_ControlDice:uint = 0; //遥控骰子
		public static const ECardType_TurnDice:uint = 1; //转向卡片
		public static const end:uint = ECardType_TurnDice;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ECardType_ControlDice:
					return ProtocolMessageProt98.ECardType_ControlDice;
				case ECardType_TurnDice:
					return ProtocolMessageProt98.ECardType_TurnDice;
				default:
					return "Unknown Error";
			}
		}
	}
}
