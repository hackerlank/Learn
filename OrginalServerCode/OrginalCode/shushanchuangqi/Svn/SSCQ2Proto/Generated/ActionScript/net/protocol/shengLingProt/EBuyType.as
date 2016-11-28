/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBuyType.as
//  Purpose:      圣陵协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
 {
	import net.protocol.Message.ProtocolMessageProt98;
	/**
	 * 购买类型
	 */
	public final class EBuyType
	{
		public static const EBuyType_ControlDice:uint = 0; //购买遥控骰子
		public static const EBuyType_TurnCard:uint = 1; //购买转向卡片
		public static const EBuyType_Life:uint = 2; //购买生命
		public static const EBuyType_Enter:uint = 3; //购买进入次数
		public static const EBuyType_Step:uint = 4; //购买三消步数
		public static const end:uint = EBuyType_Step;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EBuyType_ControlDice:
					return ProtocolMessageProt98.EBuyType_ControlDice;
				case EBuyType_TurnCard:
					return ProtocolMessageProt98.EBuyType_TurnCard;
				case EBuyType_Life:
					return ProtocolMessageProt98.EBuyType_Life;
				case EBuyType_Enter:
					return ProtocolMessageProt98.EBuyType_Enter;
				case EBuyType_Step:
					return ProtocolMessageProt98.EBuyType_Step;
				default:
					return "Unknown Error";
			}
		}
	}
}
