/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ESittingResult.as
//  Purpose:      打坐协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.sittingProt
 {
	import net.protocol.Message.ProtocolMessageProt55;
	/**
	 * 请求的结果
	 */
	public final class ESittingResult
	{
		public static const eSittingSucceed:uint = 0; //成功
		public static const eSittingTogether:uint = 1; //没有找到双修的人
		public static const eHasSitting:uint = 2; //您已经在打坐
		public static const eNotInCity:uint = 3; //主城才能打坐
		public static const eLevelLow:uint = 4; //等级不足
		public static const eSittingErrOther:uint = 5; //其它错误
		public static const end:uint = eSittingErrOther;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eSittingSucceed:
					return ProtocolMessageProt55.eSittingSucceed;
				case eSittingTogether:
					return ProtocolMessageProt55.eSittingTogether;
				case eHasSitting:
					return ProtocolMessageProt55.eHasSitting;
				case eNotInCity:
					return ProtocolMessageProt55.eNotInCity;
				case eLevelLow:
					return ProtocolMessageProt55.eLevelLow;
				case eSittingErrOther:
					return ProtocolMessageProt55.eSittingErrOther;
				default:
					return "Unknown Error";
			}
		}
	}
}
