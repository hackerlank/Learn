/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBuffState.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * Buff状态
	 */
	public final class EBuffState
	{
		public static const eBSNone:uint = 0; //无效Buff状态
		public static const eBSActived:uint = 1; //Buff生效
		public static const eBSPaused:uint = 2; //Buff暂停
		public static const eBSOverdue:uint = 3; //Buff过期
		public static const eBSMax:uint = 4; //Buff状态最大值
		public static const end:uint = eBSMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBSNone:
					return ProtocolMessageProt258.eBSNone;
				case eBSActived:
					return ProtocolMessageProt258.eBSActived;
				case eBSPaused:
					return ProtocolMessageProt258.eBSPaused;
				case eBSOverdue:
					return ProtocolMessageProt258.eBSOverdue;
				case eBSMax:
					return ProtocolMessageProt258.eBSMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
