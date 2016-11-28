/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EYaMenTaskResult.as
//  Purpose:      衙门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yaMenTaskProt
 {
	import net.protocol.Message.ProtocolMessageProt52;
	/**
	 * 任务的结果
	 */
	public final class EYaMenTaskResult
	{
		public static const eYaMenTaskSucceed:uint = 0; //成功
		public static const eYaMenTaskLowMoney:uint = 1; //钱不足
		public static const eBuyTimesUpLimit:uint = 2; //购买次数已达上限
		public static const eYaMenSaveTimesUpLimit:uint = 3; //总次数已达上限
		public static const eYaMenAwardPackFull:uint = 4; //包裹满
		public static const eYaMenTaskErrOther:uint = 5; //其它错误
		public static const end:uint = eYaMenTaskErrOther;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eYaMenTaskSucceed:
					return ProtocolMessageProt52.eYaMenTaskSucceed;
				case eYaMenTaskLowMoney:
					return ProtocolMessageProt52.eYaMenTaskLowMoney;
				case eBuyTimesUpLimit:
					return ProtocolMessageProt52.eBuyTimesUpLimit;
				case eYaMenSaveTimesUpLimit:
					return ProtocolMessageProt52.eYaMenSaveTimesUpLimit;
				case eYaMenAwardPackFull:
					return ProtocolMessageProt52.eYaMenAwardPackFull;
				case eYaMenTaskErrOther:
					return ProtocolMessageProt52.eYaMenTaskErrOther;
				default:
					return "Unknown Error";
			}
		}
	}
}
