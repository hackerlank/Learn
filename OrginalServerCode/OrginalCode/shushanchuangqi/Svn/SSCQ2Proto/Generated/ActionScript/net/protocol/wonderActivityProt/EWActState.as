/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EWActState.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
 {
	import net.protocol.Message.ProtocolMessageProt199;
	/**
	 * 活动状态
	 */
	public final class EWActState
	{
		public static const eWActState_Init:uint = 0; //初始状态
		public static const eWActState_Advance:uint = 1; //活动预告
		public static const eWActState_Begin:uint = 2; //活动开始
		public static const eWActState_End:uint = 3; //活动结束
		public static const eWActState_Retain:uint = 4; //活动保留时间
		public static const end:uint = eWActState_Retain;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eWActState_Init:
					return ProtocolMessageProt199.eWActState_Init;
				case eWActState_Advance:
					return ProtocolMessageProt199.eWActState_Advance;
				case eWActState_Begin:
					return ProtocolMessageProt199.eWActState_Begin;
				case eWActState_End:
					return ProtocolMessageProt199.eWActState_End;
				case eWActState_Retain:
					return ProtocolMessageProt199.eWActState_Retain;
				default:
					return "Unknown Error";
			}
		}
	}
}
