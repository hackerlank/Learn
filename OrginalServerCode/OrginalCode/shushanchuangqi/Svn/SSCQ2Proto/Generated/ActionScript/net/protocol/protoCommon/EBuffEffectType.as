/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBuffEffectType.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * Buff效果类型
	 */
	public final class EBuffEffectType
	{
		public static const eBETNone:uint = 0; //无效Buff效果类型
		public static const eBETAttr:uint = 1; //Buff属性加成
		public static const eBETTimeCount:uint = 2; //Buff持续时间同时持续次数
		public static const eBETCount:uint = 3; //Buff仅持续时间
		public static const eBETMax:uint = 4; //Buff效果最大值
		public static const end:uint = eBETMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBETNone:
					return ProtocolMessageProt258.eBETNone;
				case eBETAttr:
					return ProtocolMessageProt258.eBETAttr;
				case eBETTimeCount:
					return ProtocolMessageProt258.eBETTimeCount;
				case eBETCount:
					return ProtocolMessageProt258.eBETCount;
				case eBETMax:
					return ProtocolMessageProt258.eBETMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
