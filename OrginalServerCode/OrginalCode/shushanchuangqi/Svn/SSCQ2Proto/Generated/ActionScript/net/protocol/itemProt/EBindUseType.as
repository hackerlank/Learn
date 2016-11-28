/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBindUseType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 绑定优先使用类型
	 */
	public final class EBindUseType
	{
		public static const eBindUseNone:uint = 0; //只使用非绑定
		public static const eBindUseBind:uint = 1; //只使用绑定
		public static const eBindUseNoneFirst:uint = 2; //优先使用非绑定
		public static const eBindUseBindFirst:uint = 3; //优先使用绑定
		public static const end:uint = eBindUseBindFirst;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBindUseNone:
					return ProtocolMessageProt18.eBindUseNone;
				case eBindUseBind:
					return ProtocolMessageProt18.eBindUseBind;
				case eBindUseNoneFirst:
					return ProtocolMessageProt18.eBindUseNoneFirst;
				case eBindUseBindFirst:
					return ProtocolMessageProt18.eBindUseBindFirst;
				default:
					return "Unknown Error";
			}
		}
	}
}
