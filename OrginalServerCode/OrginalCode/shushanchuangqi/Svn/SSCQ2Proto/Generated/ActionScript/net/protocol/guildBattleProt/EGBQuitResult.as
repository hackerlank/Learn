/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGBQuitResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt76;
	/**
	 * 帮派战退出结果
	 */
	public final class EGBQuitResult
	{
		public static const eGBQuitSuccess:uint = 0; //退出成功
		public static const eGBQuitFailed:uint = 1; //退出失败
		public static const eGBQuitNotInGuild:uint = 2; //退出时不存在帮派
		public static const eGBQuitNotInBattle:uint = 3; //当前不在帮派战
		public static const eGBQuitRepeat:uint = 4; //退出重复
		public static const eGBQuitWrongTime:uint = 5; //当前不存在帮派战
		public static const end:uint = eGBQuitWrongTime;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBQuitSuccess:
					return ProtocolMessageProt76.eGBQuitSuccess;
				case eGBQuitFailed:
					return ProtocolMessageProt76.eGBQuitFailed;
				case eGBQuitNotInGuild:
					return ProtocolMessageProt76.eGBQuitNotInGuild;
				case eGBQuitNotInBattle:
					return ProtocolMessageProt76.eGBQuitNotInBattle;
				case eGBQuitRepeat:
					return ProtocolMessageProt76.eGBQuitRepeat;
				case eGBQuitWrongTime:
					return ProtocolMessageProt76.eGBQuitWrongTime;
				default:
					return "Unknown Error";
			}
		}
	}
}
