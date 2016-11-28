/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EAnswerResult.as
//  Purpose:      答题协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
 {
	import net.protocol.Message.ProtocolMessageProt95;
	/**
	 * 答题操作结果
	 */
	public final class EAnswerResult
	{
		public static const EAnswerResult_Suc:uint = 0; //操作成功
		public static const EAnswerResult_Lack:uint = 1; //技能使用完
		public static const EAnswerResult_No:uint = 2; //技能无法使用
		public static const EAnswerResult_Err:uint = 3; //操作失败
		public static const end:uint = EAnswerResult_Err;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EAnswerResult_Suc:
					return ProtocolMessageProt95.EAnswerResult_Suc;
				case EAnswerResult_Lack:
					return ProtocolMessageProt95.EAnswerResult_Lack;
				case EAnswerResult_No:
					return ProtocolMessageProt95.EAnswerResult_No;
				case EAnswerResult_Err:
					return ProtocolMessageProt95.EAnswerResult_Err;
				default:
					return "Unknown Error";
			}
		}
	}
}
