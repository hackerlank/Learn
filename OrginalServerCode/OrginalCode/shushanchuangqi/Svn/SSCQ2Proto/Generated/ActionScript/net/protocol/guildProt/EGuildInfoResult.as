/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGuildInfoResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 获取帮派信息返回结果
	 */
	public final class EGuildInfoResult
	{
		public static const eGuildInofSuccess:uint = 0; //操作成功
		public static const eGuildInofFailed:uint = 1; //操作失败
		public static const eGuildInofNoGuild:uint = 2; //没有帮派
		public static const end:uint = eGuildInofNoGuild;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGuildInofSuccess:
					return ProtocolMessageProt16.eGuildInofSuccess;
				case eGuildInofFailed:
					return ProtocolMessageProt16.eGuildInofFailed;
				case eGuildInofNoGuild:
					return ProtocolMessageProt16.eGuildInofNoGuild;
				default:
					return "Unknown Error";
			}
		}
	}
}
