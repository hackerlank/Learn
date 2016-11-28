/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGBAdjustResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt76;
	/**
	 * 帮派战调整结果
	 */
	public final class EGBAdjustResult
	{
		public static const eGBAdjustSuccess:uint = 0; //调整成功
		public static const eGBAdjustFailed:uint = 1; //调整失败
		public static const eGBAdjustNotInGuild:uint = 2; //调整时不存在帮派
		public static const eGBAdjustNoAuthority:uint = 3; //调整权限不足
		public static const eGBAdjustWrongTime:uint = 4; //不在调整时间段
		public static const eGBAdjustSpotFull:uint = 5; //调整目标据点已满
		public static const end:uint = eGBAdjustSpotFull;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBAdjustSuccess:
					return ProtocolMessageProt76.eGBAdjustSuccess;
				case eGBAdjustFailed:
					return ProtocolMessageProt76.eGBAdjustFailed;
				case eGBAdjustNotInGuild:
					return ProtocolMessageProt76.eGBAdjustNotInGuild;
				case eGBAdjustNoAuthority:
					return ProtocolMessageProt76.eGBAdjustNoAuthority;
				case eGBAdjustWrongTime:
					return ProtocolMessageProt76.eGBAdjustWrongTime;
				case eGBAdjustSpotFull:
					return ProtocolMessageProt76.eGBAdjustSpotFull;
				default:
					return "Unknown Error";
			}
		}
	}
}
