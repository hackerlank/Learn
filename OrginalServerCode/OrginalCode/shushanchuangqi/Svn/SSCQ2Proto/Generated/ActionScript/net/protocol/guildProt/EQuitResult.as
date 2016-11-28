/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EQuitResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 退出帮派返回结果
	 */
	public final class EQuitResult
	{
		public static const eGQuitSuccess:uint = 0; //操作成功
		public static const eGQuitFailed:uint = 1; //操作失败
		public static const eGQuitNoGuild:uint = 2; //不在帮派中
		public static const eGQuitOwnerQuit:uint = 3; //帮主不能退出帮派
		public static const eGQuitGuildBattle:uint = 4; //帮派战期间无法执行此操作
		public static const end:uint = eGQuitGuildBattle;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGQuitSuccess:
					return ProtocolMessageProt16.eGQuitSuccess;
				case eGQuitFailed:
					return ProtocolMessageProt16.eGQuitFailed;
				case eGQuitNoGuild:
					return ProtocolMessageProt16.eGQuitNoGuild;
				case eGQuitOwnerQuit:
					return ProtocolMessageProt16.eGQuitOwnerQuit;
				case eGQuitGuildBattle:
					return ProtocolMessageProt16.eGQuitGuildBattle;
				default:
					return "Unknown Error";
			}
		}
	}
}
