/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDayActivityStatus.as
//  Purpose:      活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayActProt
 {
	import net.protocol.Message.ProtocolMessageProt69;
	/**
	 * 活动状态
	 */
	public final class EDayActivityStatus
	{
		public static const eDayActivityStatusInit:uint = 0; //活动初始化状态
		public static const eDayActivityStatusAlarm:uint = 1; //活动警戒状态
		public static const eDayActivityStatusReady:uint = 2; //活动准备状态
		public static const eDayActivityStatusProcess:uint = 3; //活动进行状态
		public static const eDayActivityStatusEnd:uint = 4; //活动结束状态
		public static const end:uint = eDayActivityStatusEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eDayActivityStatusInit:
					return ProtocolMessageProt69.eDayActivityStatusInit;
				case eDayActivityStatusAlarm:
					return ProtocolMessageProt69.eDayActivityStatusAlarm;
				case eDayActivityStatusReady:
					return ProtocolMessageProt69.eDayActivityStatusReady;
				case eDayActivityStatusProcess:
					return ProtocolMessageProt69.eDayActivityStatusProcess;
				case eDayActivityStatusEnd:
					return ProtocolMessageProt69.eDayActivityStatusEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
