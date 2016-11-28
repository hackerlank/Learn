/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDgnCondStatus.as
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dungeonProt
 {
	import net.protocol.Message.ProtocolMessageProt59;
	/**
	 * 条件状态
	 */
	public final class EDgnCondStatus
	{
		public static const eCondRun:uint = 0; //未达成
		public static const eCondSuc:uint = 1; //已达成
		public static const eCondFal:uint = 2; //已失败
		public static const end:uint = eCondFal;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eCondRun:
					return ProtocolMessageProt59.eCondRun;
				case eCondSuc:
					return ProtocolMessageProt59.eCondSuc;
				case eCondFal:
					return ProtocolMessageProt59.eCondFal;
				default:
					return "Unknown Error";
			}
		}
	}
}
