/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETripodLogType.as
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
 {
	import net.protocol.Message.ProtocolMessageProt63;
	/**
	 * 九疑鼎日志类型
	 */
	public final class ETripodLogType
	{
		public static const eTripodLogNone:uint = 0; //无效日志类型
		public static const eTripodLogHelp:uint = 1; //成员日志
		public static const eTripodLogMax:uint = 2; //日志类型最大值
		public static const end:uint = eTripodLogMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eTripodLogNone:
					return ProtocolMessageProt63.eTripodLogNone;
				case eTripodLogHelp:
					return ProtocolMessageProt63.eTripodLogHelp;
				case eTripodLogMax:
					return ProtocolMessageProt63.eTripodLogMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
