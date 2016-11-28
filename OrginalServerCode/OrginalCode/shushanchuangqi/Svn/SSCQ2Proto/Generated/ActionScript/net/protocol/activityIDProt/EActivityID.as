/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EActivityID.as
//  Purpose:      活动ID统一管理
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityIDProt
 {
	import net.protocol.Message.ProtocolMessageProt97;
	/**
	 * 活动ID
	 */
	public final class EActivityID
	{
		public static const eActivityID_None:uint = 0; //无
		public static const eQQCoinActivity:uint = 1; //汇灵盏
		public static const eOpenActActivity:uint = 2; //七日七天购买礼包
		public static const eSevenConsumeAct:uint = 3; //七日消费活动
		public static const eDragonBallAct:uint = 4; //七龙珠活动
		public static const eActivityID_Max:uint = 5; //无
		public static const end:uint = eActivityID_Max;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eActivityID_None:
					return ProtocolMessageProt97.eActivityID_None;
				case eQQCoinActivity:
					return ProtocolMessageProt97.eQQCoinActivity;
				case eOpenActActivity:
					return ProtocolMessageProt97.eOpenActActivity;
				case eSevenConsumeAct:
					return ProtocolMessageProt97.eSevenConsumeAct;
				case eDragonBallAct:
					return ProtocolMessageProt97.eDragonBallAct;
				case eActivityID_Max:
					return ProtocolMessageProt97.eActivityID_Max;
				default:
					return "Unknown Error";
			}
		}
	}
}
