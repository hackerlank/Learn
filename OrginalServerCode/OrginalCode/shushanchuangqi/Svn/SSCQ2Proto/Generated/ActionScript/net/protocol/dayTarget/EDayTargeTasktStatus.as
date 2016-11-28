/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDayTargeTasktStatus.as
//  Purpose:      七日目标活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayTarget
 {
	import net.protocol.Message.ProtocolMessageProt125;
	/**
	 * 任务状态
	 */
	public final class EDayTargeTasktStatus
	{
		public static const eDayTargetTaskStatus_Init:uint = 0; //任务未完成
		public static const eDayTargetTaskStatus_Finish:uint = 1; //任务完成
		public static const eDayTargetTaskStatus_TakePrized:uint = 2; //任务已领奖
		public static const end:uint = eDayTargetTaskStatus_TakePrized;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eDayTargetTaskStatus_Init:
					return ProtocolMessageProt125.eDayTargetTaskStatus_Init;
				case eDayTargetTaskStatus_Finish:
					return ProtocolMessageProt125.eDayTargetTaskStatus_Finish;
				case eDayTargetTaskStatus_TakePrized:
					return ProtocolMessageProt125.eDayTargetTaskStatus_TakePrized;
				default:
					return "Unknown Error";
			}
		}
	}
}
