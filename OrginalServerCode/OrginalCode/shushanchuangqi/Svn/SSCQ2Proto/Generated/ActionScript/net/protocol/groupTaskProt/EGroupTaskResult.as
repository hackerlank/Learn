/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGroupTaskResult.as
//  Purpose:      师门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.groupTaskProt
 {
	import net.protocol.Message.ProtocolMessageProt51;
	/**
	 * 任务的结果
	 */
	public final class EGroupTaskResult
	{
		public static const eGroupTaskSucceed:uint = 0; //成功
		public static const eGroupTaskLowMoney:uint = 1; //钱不足
		public static const eBuyTimesUpLimit:uint = 2; //购买次数已达上限
		public static const eGroupSaveTimesUpLimit:uint = 3; //总次数已达上限
		public static const eGroupTaskErrOther:uint = 4; //其它错误
		public static const end:uint = eGroupTaskErrOther;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGroupTaskSucceed:
					return ProtocolMessageProt51.eGroupTaskSucceed;
				case eGroupTaskLowMoney:
					return ProtocolMessageProt51.eGroupTaskLowMoney;
				case eBuyTimesUpLimit:
					return ProtocolMessageProt51.eBuyTimesUpLimit;
				case eGroupSaveTimesUpLimit:
					return ProtocolMessageProt51.eGroupSaveTimesUpLimit;
				case eGroupTaskErrOther:
					return ProtocolMessageProt51.eGroupTaskErrOther;
				default:
					return "Unknown Error";
			}
		}
	}
}
