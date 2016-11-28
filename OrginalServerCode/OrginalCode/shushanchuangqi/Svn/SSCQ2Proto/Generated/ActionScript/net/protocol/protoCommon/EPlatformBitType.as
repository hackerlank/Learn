/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EPlatformBitType.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * 平台额外bit参数定义
	 */
	public final class EPlatformBitType
	{
		public static const ePBBitSuper:uint = 0; //豪华/超级
		public static const ePBBitYearly:uint = 1; //年费
		public static const end:uint = ePBBitYearly;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ePBBitSuper:
					return ProtocolMessageProt258.ePBBitSuper;
				case ePBBitYearly:
					return ProtocolMessageProt258.ePBBitYearly;
				default:
					return "Unknown Error";
			}
		}
	}
}
