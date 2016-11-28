/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EActState.as
//  Purpose:      等级奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
 {
	import net.protocol.Message.ProtocolMessageProt121;
	/**
	 * 活动信息
	 */
	public final class EActState
	{
		public static const eActState_Init:uint = 0; //未完成
		public static const eActState_OnAdvance:uint = 1; //预告
		public static const eActState_OnBegin:uint = 2; //开始
		public static const eActState_OnEnd:uint = 3; //结束
		public static const eActState_OnRetain:uint = 4; //保留
		public static const end:uint = eActState_OnRetain;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eActState_Init:
					return ProtocolMessageProt121.eActState_Init;
				case eActState_OnAdvance:
					return ProtocolMessageProt121.eActState_OnAdvance;
				case eActState_OnBegin:
					return ProtocolMessageProt121.eActState_OnBegin;
				case eActState_OnEnd:
					return ProtocolMessageProt121.eActState_OnEnd;
				case eActState_OnRetain:
					return ProtocolMessageProt121.eActState_OnRetain;
				default:
					return "Unknown Error";
			}
		}
	}
}
