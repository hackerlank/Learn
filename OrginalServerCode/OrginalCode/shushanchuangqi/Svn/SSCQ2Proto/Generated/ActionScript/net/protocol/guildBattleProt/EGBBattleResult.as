/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGBBattleResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt76;
	/**
	 * 帮派战战斗相关结果
	 */
	public final class EGBBattleResult
	{
		public static const eGBBattleSuccess:uint = 0; //战斗成功
		public static const eGBBattleFailed:uint = 1; //战斗失败
		public static const eGBBattleNotInGuild:uint = 2; //战斗时不存在帮派
		public static const end:uint = eGBBattleNotInGuild;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBBattleSuccess:
					return ProtocolMessageProt76.eGBBattleSuccess;
				case eGBBattleFailed:
					return ProtocolMessageProt76.eGBBattleFailed;
				case eGBBattleNotInGuild:
					return ProtocolMessageProt76.eGBBattleNotInGuild;
				default:
					return "Unknown Error";
			}
		}
	}
}
