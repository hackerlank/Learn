/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EAnswerSkill.as
//  Purpose:      答题协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.answerProt
 {
	import net.protocol.Message.ProtocolMessageProt95;
	/**
	 * 答题技能
	 */
	public final class EAnswerSkill
	{
		public static const EAnswerSkill_NONE:uint = 0; //无技能
		public static const EAnswerSkill_1:uint = 1; //仙人之路
		public static const EAnswerSkill_2:uint = 2; //天官赐福
		public static const EAnswerSkill_3:uint = 3; //驱散迷雾
		public static const EAnswerSkill_END:uint = 4; //最大值
		public static const end:uint = EAnswerSkill_END;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EAnswerSkill_NONE:
					return ProtocolMessageProt95.EAnswerSkill_NONE;
				case EAnswerSkill_1:
					return ProtocolMessageProt95.EAnswerSkill_1;
				case EAnswerSkill_2:
					return ProtocolMessageProt95.EAnswerSkill_2;
				case EAnswerSkill_3:
					return ProtocolMessageProt95.EAnswerSkill_3;
				case EAnswerSkill_END:
					return ProtocolMessageProt95.EAnswerSkill_END;
				default:
					return "Unknown Error";
			}
		}
	}
}
