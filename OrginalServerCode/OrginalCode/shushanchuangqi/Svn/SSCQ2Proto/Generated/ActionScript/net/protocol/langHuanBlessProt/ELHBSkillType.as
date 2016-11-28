/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ELHBSkillType.as
//  Purpose:      中午挂机活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
 {
	import net.protocol.Message.ProtocolMessageProt79;
	/**
	 * 技能类型
	 */
	public final class ELHBSkillType
	{
		public static const eLHBSkillType_eNone:uint = 0; //无技能
		public static const eLHBSkillType_eAskTaoism:uint = 1; //问道技能
		public static const eLHBSkillType_eTalkTaoism:uint = 2; //论道技能
		public static const eLHBSkillType_eWander:uint = 3; //开小差技能
		public static const eLHBSkillType_eSit:uint = 4; //打坐技能
		public static const eLHBSkillType_max:uint = 5; //技能最大值
		public static const end:uint = eLHBSkillType_max;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eLHBSkillType_eNone:
					return ProtocolMessageProt79.eLHBSkillType_eNone;
				case eLHBSkillType_eAskTaoism:
					return ProtocolMessageProt79.eLHBSkillType_eAskTaoism;
				case eLHBSkillType_eTalkTaoism:
					return ProtocolMessageProt79.eLHBSkillType_eTalkTaoism;
				case eLHBSkillType_eWander:
					return ProtocolMessageProt79.eLHBSkillType_eWander;
				case eLHBSkillType_eSit:
					return ProtocolMessageProt79.eLHBSkillType_eSit;
				case eLHBSkillType_max:
					return ProtocolMessageProt79.eLHBSkillType_max;
				default:
					return "Unknown Error";
			}
		}
	}
}
