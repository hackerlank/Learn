/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ELogType.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 日志类型
	 */
	public final class ELogType
	{
		public static const eLogNone:uint = 0; //无效日志类型
		public static const eLogMember:uint = 1; //成员日志
		public static const eLogDonate:uint = 2; //捐献日志
		public static const eLogBuilding:uint = 3; //建筑日志
		public static const eLogStatue:uint = 4; //神像日志
		public static const eLogMax:uint = 5; //日志类型最大值
		public static const end:uint = eLogMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eLogNone:
					return ProtocolMessageProt16.eLogNone;
				case eLogMember:
					return ProtocolMessageProt16.eLogMember;
				case eLogDonate:
					return ProtocolMessageProt16.eLogDonate;
				case eLogBuilding:
					return ProtocolMessageProt16.eLogBuilding;
				case eLogStatue:
					return ProtocolMessageProt16.eLogStatue;
				case eLogMax:
					return ProtocolMessageProt16.eLogMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
