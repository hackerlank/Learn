/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EWActResult.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
 {
	import net.protocol.Message.ProtocolMessageProt199;
	/**
	 * 操作结果
	 */
	public final class EWActResult
	{
		public static const eWActResult_none:uint = 0; //无此活动
		public static const eWActResult_success:uint = 1; //操作成功
		public static const eWActResult_error:uint = 2; //操作失败
		public static const end:uint = eWActResult_error;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eWActResult_none:
					return ProtocolMessageProt199.eWActResult_none;
				case eWActResult_success:
					return ProtocolMessageProt199.eWActResult_success;
				case eWActResult_error:
					return ProtocolMessageProt199.eWActResult_error;
				default:
					return "Unknown Error";
			}
		}
	}
}
