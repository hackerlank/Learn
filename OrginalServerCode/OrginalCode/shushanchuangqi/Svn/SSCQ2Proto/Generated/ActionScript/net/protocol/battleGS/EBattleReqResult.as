/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBattleReqResult.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
 {
	import net.protocol.Message.ProtocolMessageProt21;
	/**
	 * 战斗请求结果
	 */
	public final class EBattleReqResult
	{
		public static const EBattleReq_Suc:uint = 1; //成功
		public static const EBattleReq_CoolDown:uint = 2; //您还处在战斗冷却中
		public static const EBattleReq_Protect:uint = 3; //对方在战斗保护中
		public static const EBattleReq_GuardFirst:uint = 4; //请先去击杀护卫
		public static const EBattleReq_DieCD:uint = 5; //死亡冷却中
		public static const EBattleReq_FieldCoolDown:uint = 6; //野外战斗冷却中
		public static const EBattleReq_Level:uint = 7; //等级不够
		public static const EBattleReq_Other:uint = 8; //未知错误
		public static const end:uint = EBattleReq_Other;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EBattleReq_Suc:
					return ProtocolMessageProt21.EBattleReq_Suc;
				case EBattleReq_CoolDown:
					return ProtocolMessageProt21.EBattleReq_CoolDown;
				case EBattleReq_Protect:
					return ProtocolMessageProt21.EBattleReq_Protect;
				case EBattleReq_GuardFirst:
					return ProtocolMessageProt21.EBattleReq_GuardFirst;
				case EBattleReq_DieCD:
					return ProtocolMessageProt21.EBattleReq_DieCD;
				case EBattleReq_FieldCoolDown:
					return ProtocolMessageProt21.EBattleReq_FieldCoolDown;
				case EBattleReq_Level:
					return ProtocolMessageProt21.EBattleReq_Level;
				case EBattleReq_Other:
					return ProtocolMessageProt21.EBattleReq_Other;
				default:
					return "Unknown Error";
			}
		}
	}
}
