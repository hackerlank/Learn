/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ESSBattleResult.as
//  Purpose:      蜀山论剑相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt66;
	/**
	 * 蜀山论剑操作结果
	 */
	public final class ESSBattleResult
	{
		public static const eSSBattle_Suc:uint = 0; //成功
		public static const eSSBattle_NotRuning:uint = 1; //论剑活动未开始
		public static const eSSBattle_CDTime:uint = 2; //正在冷却
		public static const eSSBattle_LevelLimit:uint = 3; //等级小于30级
		public static const eSSBattle_LackMoney:uint = 4; //金钱不够
		public static const eSSBattle_NotEnter:uint = 5; //未参加
		public static const eSSBattle_Full:uint = 6; //霸气or怒气已满
		public static const eSSBattle_NotEnough:uint = 7; //霸气or怒气不足
		public static const eSSBattle_Used:uint = 8; //已使用
		public static const eSSBattle_OtherErr:uint = 9; //其他错误
		public static const end:uint = eSSBattle_OtherErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eSSBattle_Suc:
					return ProtocolMessageProt66.eSSBattle_Suc;
				case eSSBattle_NotRuning:
					return ProtocolMessageProt66.eSSBattle_NotRuning;
				case eSSBattle_CDTime:
					return ProtocolMessageProt66.eSSBattle_CDTime;
				case eSSBattle_LevelLimit:
					return ProtocolMessageProt66.eSSBattle_LevelLimit;
				case eSSBattle_LackMoney:
					return ProtocolMessageProt66.eSSBattle_LackMoney;
				case eSSBattle_NotEnter:
					return ProtocolMessageProt66.eSSBattle_NotEnter;
				case eSSBattle_Full:
					return ProtocolMessageProt66.eSSBattle_Full;
				case eSSBattle_NotEnough:
					return ProtocolMessageProt66.eSSBattle_NotEnough;
				case eSSBattle_Used:
					return ProtocolMessageProt66.eSSBattle_Used;
				case eSSBattle_OtherErr:
					return ProtocolMessageProt66.eSSBattle_OtherErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
