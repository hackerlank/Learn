/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EResultInCoinProt.as
//  Purpose:      888礼券协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.coinProt
 {
	import net.protocol.Message.ProtocolMessageProt91;
	/**
	 * 操作结果
	 */
	public final class EResultInCoinProt
	{
		public static const eCoinError:uint = 0; //错误
		public static const eCoinGain:uint = 1; //已经领取
		public static const eCoinSuccess:uint = 2; //成功
		public static const end:uint = eCoinSuccess;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eCoinError:
					return ProtocolMessageProt91.eCoinError;
				case eCoinGain:
					return ProtocolMessageProt91.eCoinGain;
				case eCoinSuccess:
					return ProtocolMessageProt91.eCoinSuccess;
				default:
					return "Unknown Error";
			}
		}
	}
}
