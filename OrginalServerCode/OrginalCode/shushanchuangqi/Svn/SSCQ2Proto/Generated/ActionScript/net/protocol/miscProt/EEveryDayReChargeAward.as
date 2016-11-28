/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EEveryDayReChargeAward.as
//  Purpose:      不好归类的小协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
 {
	import net.protocol.Message.ProtocolMessageProt72;
	/**
	 * 每日冲值领奖奖励
	 */
	public final class EEveryDayReChargeAward
	{
		public static const eEveryDayReChargeAward_Sucess:uint = 0; //成功
		public static const eEveryDayReChargeAward_LowMoney:uint = 1; //今日冲值不足
		public static const eEveryDayReChargeAward_HasDone:uint = 2; //今日已经领奖
		public static const eEveryDayReChargeAward_NoAward:uint = 3; //今日无奖
		public static const end:uint = eEveryDayReChargeAward_NoAward;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eEveryDayReChargeAward_Sucess:
					return ProtocolMessageProt72.eEveryDayReChargeAward_Sucess;
				case eEveryDayReChargeAward_LowMoney:
					return ProtocolMessageProt72.eEveryDayReChargeAward_LowMoney;
				case eEveryDayReChargeAward_HasDone:
					return ProtocolMessageProt72.eEveryDayReChargeAward_HasDone;
				case eEveryDayReChargeAward_NoAward:
					return ProtocolMessageProt72.eEveryDayReChargeAward_NoAward;
				default:
					return "Unknown Error";
			}
		}
	}
}
