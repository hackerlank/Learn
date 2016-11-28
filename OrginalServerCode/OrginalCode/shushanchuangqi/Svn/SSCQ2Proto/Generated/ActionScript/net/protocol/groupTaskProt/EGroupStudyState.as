/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGroupStudyState.as
//  Purpose:      师门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.groupTaskProt
 {
	import net.protocol.Message.ProtocolMessageProt51;
	/**
	 * 清修的状态
	 */
	public final class EGroupStudyState
	{
		public static const eCanStudy:uint = 0; //可清修
		public static const eStudied:uint = 1; //已清修
		public static const eCanChallenge:uint = 2; //可挑战
		public static const eChallenging:uint = 3; //正挑战
		public static const end:uint = eChallenging;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eCanStudy:
					return ProtocolMessageProt51.eCanStudy;
				case eStudied:
					return ProtocolMessageProt51.eStudied;
				case eCanChallenge:
					return ProtocolMessageProt51.eCanChallenge;
				case eChallenging:
					return ProtocolMessageProt51.eChallenging;
				default:
					return "Unknown Error";
			}
		}
	}
}
