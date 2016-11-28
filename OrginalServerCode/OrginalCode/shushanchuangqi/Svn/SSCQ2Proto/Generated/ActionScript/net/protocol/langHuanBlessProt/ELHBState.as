/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ELHBState.as
//  Purpose:      中午挂机活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
 {
	import net.protocol.Message.ProtocolMessageProt79;
	/**
	 * 活动状态
	 */
	public final class ELHBState
	{
		public static const eLHBState_none:uint = 0; //无状态
		public static const eLHBState_alarm:uint = 1; //警告
		public static const eLHBState_ready:uint = 2; //报名开始
		public static const eLHBState_begin:uint = 3; //活动开始
		public static const eLHBState_end:uint = 4; //活动结束
		public static const end:uint = eLHBState_end;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eLHBState_none:
					return ProtocolMessageProt79.eLHBState_none;
				case eLHBState_alarm:
					return ProtocolMessageProt79.eLHBState_alarm;
				case eLHBState_ready:
					return ProtocolMessageProt79.eLHBState_ready;
				case eLHBState_begin:
					return ProtocolMessageProt79.eLHBState_begin;
				case eLHBState_end:
					return ProtocolMessageProt79.eLHBState_end;
				default:
					return "Unknown Error";
			}
		}
	}
}
