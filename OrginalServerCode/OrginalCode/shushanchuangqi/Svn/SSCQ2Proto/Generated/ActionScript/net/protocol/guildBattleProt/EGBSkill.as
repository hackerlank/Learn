/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGBSkill.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt76;
	/**
	 * 帮派战技能
	 */
	public final class EGBSkill
	{
		public static const eGBSkillNone:uint = 0; //无效技能
		public static const eGBSkillAttack:uint = 1; //攻击强化
		public static const eGBSkillDefence:uint = 2; //防御强化
		public static const eGBSkillSpeed:uint = 3; //身法强化
		public static const eGBSkillHP:uint = 4; //生命强化
		public static const eGBSkillMax:uint = 5; //技能最大值
		public static const end:uint = eGBSkillMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBSkillNone:
					return ProtocolMessageProt76.eGBSkillNone;
				case eGBSkillAttack:
					return ProtocolMessageProt76.eGBSkillAttack;
				case eGBSkillDefence:
					return ProtocolMessageProt76.eGBSkillDefence;
				case eGBSkillSpeed:
					return ProtocolMessageProt76.eGBSkillSpeed;
				case eGBSkillHP:
					return ProtocolMessageProt76.eGBSkillHP;
				case eGBSkillMax:
					return ProtocolMessageProt76.eGBSkillMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
