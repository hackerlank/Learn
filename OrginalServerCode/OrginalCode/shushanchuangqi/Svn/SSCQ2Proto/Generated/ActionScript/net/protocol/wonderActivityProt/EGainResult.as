/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGainResult.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
 {
	import net.protocol.Message.ProtocolMessageProt199;
	/**
	 * 领奖操作结果
	 */
	public final class EGainResult
	{
		public static const eGainResult_none:uint = 0; //无此奖励
		public static const eGainResult_success:uint = 1; //领奖成功
		public static const eGainResult_alreadyGain:uint = 2; //奖励已领
		public static const eGainResult_fullBag:uint = 3; //背包满
		public static const eGainResult_notGet:uint = 4; //条件未达到
		public static const eGainResult_error:uint = 5; //操作失败
		public static const end:uint = eGainResult_error;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGainResult_none:
					return ProtocolMessageProt199.eGainResult_none;
				case eGainResult_success:
					return ProtocolMessageProt199.eGainResult_success;
				case eGainResult_alreadyGain:
					return ProtocolMessageProt199.eGainResult_alreadyGain;
				case eGainResult_fullBag:
					return ProtocolMessageProt199.eGainResult_fullBag;
				case eGainResult_notGet:
					return ProtocolMessageProt199.eGainResult_notGet;
				case eGainResult_error:
					return ProtocolMessageProt199.eGainResult_error;
				default:
					return "Unknown Error";
			}
		}
	}
}
