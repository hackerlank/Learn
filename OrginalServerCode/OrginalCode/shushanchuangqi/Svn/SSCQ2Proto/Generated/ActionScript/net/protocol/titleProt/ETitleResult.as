/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETitleResult.as
//  Purpose:      称号协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.titleProt
 {
	import net.protocol.Message.ProtocolMessageProt54;
	/**
	 * 请求的结果
	 */
	public final class ETitleResult
	{
		public static const eTitleSucceed:uint = 0; //成功
		public static const eTitleVIPLevel:uint = 1; //御剑等级不足
		public static const eTitleNoHas:uint = 2; //该称号没有获得
		public static const eTitleErrOther:uint = 3; //其它错误
		public static const end:uint = eTitleErrOther;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eTitleSucceed:
					return ProtocolMessageProt54.eTitleSucceed;
				case eTitleVIPLevel:
					return ProtocolMessageProt54.eTitleVIPLevel;
				case eTitleNoHas:
					return ProtocolMessageProt54.eTitleNoHas;
				case eTitleErrOther:
					return ProtocolMessageProt54.eTitleErrOther;
				default:
					return "Unknown Error";
			}
		}
	}
}
