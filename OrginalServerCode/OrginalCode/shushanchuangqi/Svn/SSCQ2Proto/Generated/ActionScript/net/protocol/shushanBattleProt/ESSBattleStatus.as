/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ESSBattleStatus.as
//  Purpose:      蜀山论剑相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shushanBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt66;
	/**
	 * 蜀山论剑参加状态
	 */
	public final class ESSBattleStatus
	{
		public static const eSSBattle_ENTER:uint = 0; //已进入
		public static const eSSBattle_QUIT:uint = 1; //已退出
		public static const eSSBattle_JOINBYE:uint = 2; //轮空
		public static const eSSBattle_FIGHTING:uint = 3; //正在战斗
		public static const end:uint = eSSBattle_FIGHTING;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eSSBattle_ENTER:
					return ProtocolMessageProt66.eSSBattle_ENTER;
				case eSSBattle_QUIT:
					return ProtocolMessageProt66.eSSBattle_QUIT;
				case eSSBattle_JOINBYE:
					return ProtocolMessageProt66.eSSBattle_JOINBYE;
				case eSSBattle_FIGHTING:
					return ProtocolMessageProt66.eSSBattle_FIGHTING;
				default:
					return "Unknown Error";
			}
		}
	}
}
