/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EAchievementProcess.as
//  Purpose:      成就相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.achievementProt
 {
	import net.protocol.Message.ProtocolMessageProt75;
	/**
	 * 成就完成进度
	 */
	public final class EAchievementProcess
	{
		public static const eAchievementProcess_Init:uint = 0; //未完成
		public static const eAchievementProcess_Finish:uint = 1; //已完成
		public static const eAchievementProcess_TakePrize:uint = 2; //已领奖
		public static const end:uint = eAchievementProcess_TakePrize;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eAchievementProcess_Init:
					return ProtocolMessageProt75.eAchievementProcess_Init;
				case eAchievementProcess_Finish:
					return ProtocolMessageProt75.eAchievementProcess_Finish;
				case eAchievementProcess_TakePrize:
					return ProtocolMessageProt75.eAchievementProcess_TakePrize;
				default:
					return "Unknown Error";
			}
		}
	}
}
