/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGBSkillResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt76;
	/**
	 * 帮派战技能相关结果
	 */
	public final class EGBSkillResult
	{
		public static const eGBSkillSuccess:uint = 0; //成功
		public static const eGBSkillFailed:uint = 1; //失败
		public static const eGBSkillWrongTime:uint = 2; //只有在准备阶段才可以购买增益祝福
		public static const eGBSkillNoGold:uint = 3; //仙石不足
		public static const eGBSkillAlreadyHave:uint = 4; //已经拥有该效果
		public static const end:uint = eGBSkillAlreadyHave;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBSkillSuccess:
					return ProtocolMessageProt76.eGBSkillSuccess;
				case eGBSkillFailed:
					return ProtocolMessageProt76.eGBSkillFailed;
				case eGBSkillWrongTime:
					return ProtocolMessageProt76.eGBSkillWrongTime;
				case eGBSkillNoGold:
					return ProtocolMessageProt76.eGBSkillNoGold;
				case eGBSkillAlreadyHave:
					return ProtocolMessageProt76.eGBSkillAlreadyHave;
				default:
					return "Unknown Error";
			}
		}
	}
}
