/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EExTest.as
//  Purpose:      通信协议示例
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.example
 {
	import net.protocol.Message.ProtocolMessageProt255;
	/**
	 * 枚举类型示例
	 */
	public final class EExTest
	{
		public static const eExTest1:int = 0; //枚举值1
		public static const eExTest2:int = 10; //枚举值2
		public static const eExTest3:int = 0x7FFF; //枚举值3
		public static const end:int = eExTest3;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eExTest1:
					return ProtocolMessageProt255.eExTest1;
				case eExTest2:
					return ProtocolMessageProt255.eExTest2;
				case eExTest3:
					return ProtocolMessageProt255.eExTest3;
				default:
					return "Unknown Error";
			}
		}
	}
}
