/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EShareStatus.as
//  Purpose:      活力任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityProt
 {
	import net.protocol.Message.ProtocolMessageProt53;
	/**
	 * 成就完成进度
	 */
	public final class EShareStatus
	{
		public static const eShareStatus_Init:uint = 0; //未完成
		public static const eShareStatus_Finish:uint = 1; //已完成
		public static const eShareStatus_TakePrize:uint = 2; //已领奖
		public static const end:uint = eShareStatus_TakePrize;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eShareStatus_Init:
					return ProtocolMessageProt53.eShareStatus_Init;
				case eShareStatus_Finish:
					return ProtocolMessageProt53.eShareStatus_Finish;
				case eShareStatus_TakePrize:
					return ProtocolMessageProt53.eShareStatus_TakePrize;
				default:
					return "Unknown Error";
			}
		}
	}
}
