/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ESignResult.as
//  Purpose:      签到协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.signProt
 {
	import net.protocol.Message.ProtocolMessageProt83;
	/**
	 * 请求的结果
	 */
	public final class ESignResult
	{
		public static const eSignSucceed:uint = 0; //成功
		public static const eSignHasDone:uint = 1; //今日已签到
		public static const eSignResignDone:uint = 2; //补签日已签到
		public static const eSignResignErrDate:uint = 3; //补签日期错误
		public static const eSignResignOverTimes:uint = 4; //补签次数用完
		public static const eSignAwardHasGet:uint = 5; //该签到奖励已领
		public static const eSignAwardIdErr:uint = 6; //该签到奖励id不正确
		public static const eSignAwardLowDays:uint = 7; //该签到奖励的签到天数不足
		public static const eSignAwardPacketFull:uint = 8; //签到奖励包裹放不下
		public static const eSignVIP:uint = 9; //提醒开通御剑
		public static const eSignOther:uint = 10; //其它错误
		public static const end:uint = eSignOther;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eSignSucceed:
					return ProtocolMessageProt83.eSignSucceed;
				case eSignHasDone:
					return ProtocolMessageProt83.eSignHasDone;
				case eSignResignDone:
					return ProtocolMessageProt83.eSignResignDone;
				case eSignResignErrDate:
					return ProtocolMessageProt83.eSignResignErrDate;
				case eSignResignOverTimes:
					return ProtocolMessageProt83.eSignResignOverTimes;
				case eSignAwardHasGet:
					return ProtocolMessageProt83.eSignAwardHasGet;
				case eSignAwardIdErr:
					return ProtocolMessageProt83.eSignAwardIdErr;
				case eSignAwardLowDays:
					return ProtocolMessageProt83.eSignAwardLowDays;
				case eSignAwardPacketFull:
					return ProtocolMessageProt83.eSignAwardPacketFull;
				case eSignVIP:
					return ProtocolMessageProt83.eSignVIP;
				case eSignOther:
					return ProtocolMessageProt83.eSignOther;
				default:
					return "Unknown Error";
			}
		}
	}
}
