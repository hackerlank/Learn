/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EFashionResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 时装养成结果
	 */
	public final class EFashionResult
	{
		public static const eFashionSucc:uint = 0; //时装养成成功
		public static const eFashionFailed:uint = 1; //时装养成失败
		public static const eFashionItemErr:uint = 2; //时装养成时所需物品不足
		public static const end:uint = eFashionItemErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eFashionSucc:
					return ProtocolMessageProt18.eFashionSucc;
				case eFashionFailed:
					return ProtocolMessageProt18.eFashionFailed;
				case eFashionItemErr:
					return ProtocolMessageProt18.eFashionItemErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
