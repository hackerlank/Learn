/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ERecruitResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 招募返回
	 */
	public final class ERecruitResult
	{
		public static const eRecruitSucc:uint = 0; //成功
		public static const eRecruitFailed:uint = 1; //失败
		public static const eRecruitAlready:uint = 2; //已招募
		public static const eRecruitLackOfMoney:uint = 3; //货币不足
		public static const eRecruitLevelLimited:uint = 4; //等级不足
		public static const end:uint = eRecruitLevelLimited;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eRecruitSucc:
					return ProtocolMessageProt20.eRecruitSucc;
				case eRecruitFailed:
					return ProtocolMessageProt20.eRecruitFailed;
				case eRecruitAlready:
					return ProtocolMessageProt20.eRecruitAlready;
				case eRecruitLackOfMoney:
					return ProtocolMessageProt20.eRecruitLackOfMoney;
				case eRecruitLevelLimited:
					return ProtocolMessageProt20.eRecruitLevelLimited;
				default:
					return "Unknown Error";
			}
		}
	}
}
