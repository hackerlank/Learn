/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDayTargetRet.as
//  Purpose:      七日目标活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayTarget
 {
	import net.protocol.Message.ProtocolMessageProt125;
	/**
	 * 错误码
	 */
	public final class EDayTargetRet
	{
		public static const eDayTargetRet_Sucess:uint = 0; //成功
		public static const eDayTargetRet_NotFinish:uint = 1; //任务未完成
		public static const eDayTargetRet_DayLimit:uint = 2; //未到领奖天数
		public static const eDayTargetRet_TakePrized:uint = 3; //已经领过奖励
		public static const eDayTargetRet_CFGError:uint = 4; //基础配置错误
		public static const eDayTargetRet_PackFull:uint = 5; //背包空间不足
		public static const end:uint = eDayTargetRet_PackFull;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eDayTargetRet_Sucess:
					return ProtocolMessageProt125.eDayTargetRet_Sucess;
				case eDayTargetRet_NotFinish:
					return ProtocolMessageProt125.eDayTargetRet_NotFinish;
				case eDayTargetRet_DayLimit:
					return ProtocolMessageProt125.eDayTargetRet_DayLimit;
				case eDayTargetRet_TakePrized:
					return ProtocolMessageProt125.eDayTargetRet_TakePrized;
				case eDayTargetRet_CFGError:
					return ProtocolMessageProt125.eDayTargetRet_CFGError;
				case eDayTargetRet_PackFull:
					return ProtocolMessageProt125.eDayTargetRet_PackFull;
				default:
					return "Unknown Error";
			}
		}
	}
}
