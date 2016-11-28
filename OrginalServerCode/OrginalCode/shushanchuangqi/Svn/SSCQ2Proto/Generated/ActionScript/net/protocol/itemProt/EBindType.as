/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBindType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 绑定类型
	 */
	public final class EBindType
	{
		public static const eBindNone:uint = 0; //未绑定
		public static const eBindGet:uint = 1; //获取绑定
		public static const eBindStren:uint = 2; //强化后绑定
		public static const end:uint = eBindStren;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBindNone:
					return ProtocolMessageProt18.eBindNone;
				case eBindGet:
					return ProtocolMessageProt18.eBindGet;
				case eBindStren:
					return ProtocolMessageProt18.eBindStren;
				default:
					return "Unknown Error";
			}
		}
	}
}
