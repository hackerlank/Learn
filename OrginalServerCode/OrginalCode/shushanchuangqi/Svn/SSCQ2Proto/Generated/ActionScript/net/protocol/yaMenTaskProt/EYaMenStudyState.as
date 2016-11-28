/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EYaMenStudyState.as
//  Purpose:      衙门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yaMenTaskProt
 {
	import net.protocol.Message.ProtocolMessageProt52;
	/**
	 * 清修的状态
	 */
	public final class EYaMenStudyState
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
					return ProtocolMessageProt52.eCanStudy;
				case eStudied:
					return ProtocolMessageProt52.eStudied;
				case eCanChallenge:
					return ProtocolMessageProt52.eCanChallenge;
				case eChallenging:
					return ProtocolMessageProt52.eChallenging;
				default:
					return "Unknown Error";
			}
		}
	}
}
