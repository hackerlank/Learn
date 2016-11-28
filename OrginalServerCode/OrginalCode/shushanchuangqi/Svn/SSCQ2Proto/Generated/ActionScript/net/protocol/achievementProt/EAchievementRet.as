/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EAchievementRet.as
//  Purpose:      成就相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.achievementProt
 {
	import net.protocol.Message.ProtocolMessageProt75;
	/**
	 * 成就完成进度
	 */
	public final class EAchievementRet
	{
		public static const eAchievementRet_Sucess:uint = 0; //成功
		public static const eAchievementRet_NotFinish:uint = 1; //未完成
		public static const eAchievementRet_TakePrized:uint = 2; //已领奖
		public static const eAchievementRet_ErrorCFG:uint = 3; //配置错误
		public static const eAchievementRet_PackFull:uint = 4; //包满
		public static const end:uint = eAchievementRet_PackFull;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eAchievementRet_Sucess:
					return ProtocolMessageProt75.eAchievementRet_Sucess;
				case eAchievementRet_NotFinish:
					return ProtocolMessageProt75.eAchievementRet_NotFinish;
				case eAchievementRet_TakePrized:
					return ProtocolMessageProt75.eAchievementRet_TakePrized;
				case eAchievementRet_ErrorCFG:
					return ProtocolMessageProt75.eAchievementRet_ErrorCFG;
				case eAchievementRet_PackFull:
					return ProtocolMessageProt75.eAchievementRet_PackFull;
				default:
					return "Unknown Error";
			}
		}
	}
}
