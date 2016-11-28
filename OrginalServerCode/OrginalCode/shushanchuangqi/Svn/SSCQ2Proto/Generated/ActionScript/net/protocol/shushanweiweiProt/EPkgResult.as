/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EPkgResult.as
//  Purpose:      蜀山微微协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanweiweiProt
 {
	import net.protocol.Message.ProtocolMessageProt93;
	/**
	 * 操作结果
	 */
	public final class EPkgResult
	{
		public static const ePackError:uint = 0; //错误
		public static const ePackGain:uint = 1; //已经领取
		public static const ePackFull:uint = 2; //背包已满
		public static const ePackSuccess:uint = 3; //成功
		public static const end:uint = ePackSuccess;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ePackError:
					return ProtocolMessageProt93.ePackError;
				case ePackGain:
					return ProtocolMessageProt93.ePackGain;
				case ePackFull:
					return ProtocolMessageProt93.ePackFull;
				case ePackSuccess:
					return ProtocolMessageProt93.ePackSuccess;
				default:
					return "Unknown Error";
			}
		}
	}
}
