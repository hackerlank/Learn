/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETHNotify.as
//  Purpose:      寻宝协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
 {
	import net.protocol.Message.ProtocolMessageProt85;
	/**
	 * 寻宝开始/结束通知
	 */
	public final class ETHNotify
	{
		public static const eTHBegin:int = 0; //开始
		public static const eTHEnd:int = 1; //结束
		public static const end:int = eTHEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eTHBegin:
					return ProtocolMessageProt85.eTHBegin;
				case eTHEnd:
					return ProtocolMessageProt85.eTHEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
