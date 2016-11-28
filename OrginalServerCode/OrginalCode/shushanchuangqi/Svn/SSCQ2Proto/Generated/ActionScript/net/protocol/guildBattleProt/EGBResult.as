/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGBResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt76;
	/**
	 * 帮派战返回结果
	 */
	public final class EGBResult
	{
		public static const eGBResultSuccess:uint = 0; //成功
		public static const eGBResultFailed:uint = 1; //失败
		public static const eGBResultWrongTime:uint = 2; //时间段错误
		public static const eGBResultNotInBattle:uint = 3; //不在帮派战中
		public static const eGBResultNoGuild:uint = 4; //不存在帮派
		public static const eGBResultNoAuthority:uint = 5; //权限不足
		public static const end:uint = eGBResultNoAuthority;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBResultSuccess:
					return ProtocolMessageProt76.eGBResultSuccess;
				case eGBResultFailed:
					return ProtocolMessageProt76.eGBResultFailed;
				case eGBResultWrongTime:
					return ProtocolMessageProt76.eGBResultWrongTime;
				case eGBResultNotInBattle:
					return ProtocolMessageProt76.eGBResultNotInBattle;
				case eGBResultNoGuild:
					return ProtocolMessageProt76.eGBResultNoGuild;
				case eGBResultNoAuthority:
					return ProtocolMessageProt76.eGBResultNoAuthority;
				default:
					return "Unknown Error";
			}
		}
	}
}
