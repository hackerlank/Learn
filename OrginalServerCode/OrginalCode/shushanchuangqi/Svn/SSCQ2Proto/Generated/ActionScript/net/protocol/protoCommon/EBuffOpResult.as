/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBuffOpResult.as
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.protoCommon
 {
	import net.protocol.Message.ProtocolMessageProt258;
	/**
	 * Buff相关操作结果
	 */
	public final class EBuffOpResult
	{
		public static const eBORSuccess:uint = 0; //操作成功
		public static const eBORFailed:uint = 1; //操作失败
		public static const eBORExisted:uint = 2; //存在相同Buff
		public static const eBORNotExisted:uint = 3; //不存在该Buff
		public static const eBOROverdue:uint = 4; //已经过期的Buff
		public static const eBORPaused:uint = 5; //已经暂停的Buff
		public static const end:uint = eBORPaused;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBORSuccess:
					return ProtocolMessageProt258.eBORSuccess;
				case eBORFailed:
					return ProtocolMessageProt258.eBORFailed;
				case eBORExisted:
					return ProtocolMessageProt258.eBORExisted;
				case eBORNotExisted:
					return ProtocolMessageProt258.eBORNotExisted;
				case eBOROverdue:
					return ProtocolMessageProt258.eBOROverdue;
				case eBORPaused:
					return ProtocolMessageProt258.eBORPaused;
				default:
					return "Unknown Error";
			}
		}
	}
}
