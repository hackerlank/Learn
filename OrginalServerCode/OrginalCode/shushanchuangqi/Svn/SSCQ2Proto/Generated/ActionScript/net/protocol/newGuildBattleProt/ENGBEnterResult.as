/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBEnterResult.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派战进入结果
	 */
	public final class ENGBEnterResult
	{
		public static const eNGBERSuccess:uint = 0; //进入成功
		public static const eNGBERFailed:uint = 1; //进入失败
		public static const eNGBERNotInGuild:uint = 2; //进入时不存在帮派
		public static const eNGBERRepeat:uint = 3; //进入重复
		public static const eNGBERWrongTime:uint = 4; //不在进入时段
		public static const eNGBERGuildLevel:uint = 5; //帮派等级过低
		public static const eNGBEREscape:uint = 6; //刚刚从战斗中逃离
		public static const eNGBERGuildWrong:uint = 7; //您的帮派未入围洞府战
		public static const end:uint = eNGBERGuildWrong;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBERSuccess:
					return ProtocolMessageProt68.eNGBERSuccess;
				case eNGBERFailed:
					return ProtocolMessageProt68.eNGBERFailed;
				case eNGBERNotInGuild:
					return ProtocolMessageProt68.eNGBERNotInGuild;
				case eNGBERRepeat:
					return ProtocolMessageProt68.eNGBERRepeat;
				case eNGBERWrongTime:
					return ProtocolMessageProt68.eNGBERWrongTime;
				case eNGBERGuildLevel:
					return ProtocolMessageProt68.eNGBERGuildLevel;
				case eNGBEREscape:
					return ProtocolMessageProt68.eNGBEREscape;
				case eNGBERGuildWrong:
					return ProtocolMessageProt68.eNGBERGuildWrong;
				default:
					return "Unknown Error";
			}
		}
	}
}
