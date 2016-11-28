/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ESkillResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 技能操作结果
	 */
	public final class ESkillResult
	{
		public static const eSkillSucc:uint = 0; //成功
		public static const eSkillFailed:uint = 1; //失败
		public static const eSkillNotExist:uint = 2; //没有此技能
		public static const eSkillLevelMax:uint = 3; //已达最高等级
		public static const eSkillLevelErr:uint = 4; //玩家等级不足
		public static const eSkillNotUp:uint = 5; //未装备此技能
		public static const eSkillPExpErr:uint = 6; //修为不足
		public static const eSkillSopErr:uint = 7; //阅历不足
		public static const eSkillSigilErr:uint = 8; //符印不足
		public static const eSkillCentsYErr:uint = 9; //仙元不足
		public static const eSkillPotenErr:uint = 10; //潜力不足
		public static const eRuneNotExist:uint = 11; //符文不存在
		public static const eRuneLevelMax:uint = 12; //符文已达最高等级
		public static const eRuneLevelErr:uint = 13; //玩家等级不足
		public static const eAdvNotExist:uint = 14; //进阶不存在
		public static const eAdvLevelGTSkillLevelErr:uint = 15; //进阶等级大于技能等级
		public static const eItemNotEnough:uint = 16; //物品不足
		public static const end:uint = eItemNotEnough;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eSkillSucc:
					return ProtocolMessageProt20.eSkillSucc;
				case eSkillFailed:
					return ProtocolMessageProt20.eSkillFailed;
				case eSkillNotExist:
					return ProtocolMessageProt20.eSkillNotExist;
				case eSkillLevelMax:
					return ProtocolMessageProt20.eSkillLevelMax;
				case eSkillLevelErr:
					return ProtocolMessageProt20.eSkillLevelErr;
				case eSkillNotUp:
					return ProtocolMessageProt20.eSkillNotUp;
				case eSkillPExpErr:
					return ProtocolMessageProt20.eSkillPExpErr;
				case eSkillSopErr:
					return ProtocolMessageProt20.eSkillSopErr;
				case eSkillSigilErr:
					return ProtocolMessageProt20.eSkillSigilErr;
				case eSkillCentsYErr:
					return ProtocolMessageProt20.eSkillCentsYErr;
				case eSkillPotenErr:
					return ProtocolMessageProt20.eSkillPotenErr;
				case eRuneNotExist:
					return ProtocolMessageProt20.eRuneNotExist;
				case eRuneLevelMax:
					return ProtocolMessageProt20.eRuneLevelMax;
				case eRuneLevelErr:
					return ProtocolMessageProt20.eRuneLevelErr;
				case eAdvNotExist:
					return ProtocolMessageProt20.eAdvNotExist;
				case eAdvLevelGTSkillLevelErr:
					return ProtocolMessageProt20.eAdvLevelGTSkillLevelErr;
				case eItemNotEnough:
					return ProtocolMessageProt20.eItemNotEnough;
				default:
					return "Unknown Error";
			}
		}
	}
}
