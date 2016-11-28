/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBattleActionType.as
//  Purpose:      角色数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleInfoDefine
 {
	import net.protocol.Message.ProtocolMessageProt10;
	/**
	 * 战报发起类型
	 */
	public final class EBattleActionType
	{
		public static const eTypeAttack:uint = 0; //玩家进攻
		public static const eTypeDefense:uint = 1; //玩家防守
		public static const eTypeALL:uint = 2; //防守和进攻
		public static const end:uint = eTypeALL;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eTypeAttack:
					return ProtocolMessageProt10.eTypeAttack;
				case eTypeDefense:
					return ProtocolMessageProt10.eTypeDefense;
				case eTypeALL:
					return ProtocolMessageProt10.eTypeALL;
				default:
					return "Unknown Error";
			}
		}
	}
}
