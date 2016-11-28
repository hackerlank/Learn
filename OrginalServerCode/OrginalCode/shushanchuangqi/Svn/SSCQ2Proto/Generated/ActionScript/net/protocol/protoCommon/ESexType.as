/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ESexType.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * 性别
	 */
	public final class ESexType
	{
		public static const ESEX_ALL:uint = 0; //所有性别
		public static const ESEX_MALE:uint = 1;
		public static const ESEX_FEMALE:uint = 2; //女性
		public static const ESEX_MAX:uint = 3; //最大值
		public static const end:uint = ESEX_MAX;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case ESEX_ALL:
					return ProtocolMessageProt258.ESEX_ALL;
				case ESEX_MALE:
					return ProtocolMessageProt258.ESEX_MALE;
				case ESEX_FEMALE:
					return ProtocolMessageProt258.ESEX_FEMALE;
				case ESEX_MAX:
					return ProtocolMessageProt258.ESEX_MAX;
				default:
					return "Unknown Error";
			}
		}
	}
}
