/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EActivityResult.as
//  Purpose:      活力任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityProt
 {
	import net.protocol.Message.ProtocolMessageProt53;
	/**
	 * 任务的结果
	 */
	public final class EActivityResult
	{
		public static const eActivitySucceed:uint = 0; //成功
		public static const eActivityMin:uint = 1; //活力度不足
		public static const eActivityTotalMin:uint = 2; //累计活力值不足
		public static const eActivityPackNoSpace:uint = 3; //背包不足
		public static const eActivityHasGet:uint = 4; //奖励已领取
		public static const eActivityVip:uint = 5; //御剑等级不足
		public static const eActivityErrOther:uint = 6; //其它错误
		public static const eActivityNotFinish:uint = 7; //任务未完成
		public static const end:uint = eActivityNotFinish;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eActivitySucceed:
					return ProtocolMessageProt53.eActivitySucceed;
				case eActivityMin:
					return ProtocolMessageProt53.eActivityMin;
				case eActivityTotalMin:
					return ProtocolMessageProt53.eActivityTotalMin;
				case eActivityPackNoSpace:
					return ProtocolMessageProt53.eActivityPackNoSpace;
				case eActivityHasGet:
					return ProtocolMessageProt53.eActivityHasGet;
				case eActivityVip:
					return ProtocolMessageProt53.eActivityVip;
				case eActivityErrOther:
					return ProtocolMessageProt53.eActivityErrOther;
				case eActivityNotFinish:
					return ProtocolMessageProt53.eActivityNotFinish;
				default:
					return "Unknown Error";
			}
		}
	}
}
