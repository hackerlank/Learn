/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBResult.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派战返回结果
	 */
	public final class ENGBResult
	{
		public static const eNGBRSuccess:uint = 0; //成功
		public static const eNGBRFailed:uint = 1; //失败
		public static const eNGBRWrongTime:uint = 2; //时间段错误
		public static const eNGBRNotInBattle:uint = 3; //不在帮派战中
		public static const eNGBRNoGuild:uint = 4; //不存在帮派
		public static const eNGBRInvalidMountain:uint = 5; //错误的灵山
		public static const eNGBRNoAuthority:uint = 6; //权限不足
		public static const end:uint = eNGBRNoAuthority;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBRSuccess:
					return ProtocolMessageProt68.eNGBRSuccess;
				case eNGBRFailed:
					return ProtocolMessageProt68.eNGBRFailed;
				case eNGBRWrongTime:
					return ProtocolMessageProt68.eNGBRWrongTime;
				case eNGBRNotInBattle:
					return ProtocolMessageProt68.eNGBRNotInBattle;
				case eNGBRNoGuild:
					return ProtocolMessageProt68.eNGBRNoGuild;
				case eNGBRInvalidMountain:
					return ProtocolMessageProt68.eNGBRInvalidMountain;
				case eNGBRNoAuthority:
					return ProtocolMessageProt68.eNGBRNoAuthority;
				default:
					return "Unknown Error";
			}
		}
	}
}
