/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EWorshipResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 帮派捐献操作返回结果
	 */
	public final class EWorshipResult
	{
		public static const eGWResultSuccess:uint = 0; //操作成功
		public static const eGWResultFailed:uint = 1; //操作失败
		public static const eGWResultNoGuild:uint = 2; //不存在帮派
		public static const eGWResultLackofSilver:uint = 3; //银币不足
		public static const eGWResultNoAuthority:uint = 4; //权限不足
		public static const eGWResultLevelTooLow:uint = 5; //帮派等级过低
		public static const end:uint = eGWResultLevelTooLow;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGWResultSuccess:
					return ProtocolMessageProt16.eGWResultSuccess;
				case eGWResultFailed:
					return ProtocolMessageProt16.eGWResultFailed;
				case eGWResultNoGuild:
					return ProtocolMessageProt16.eGWResultNoGuild;
				case eGWResultLackofSilver:
					return ProtocolMessageProt16.eGWResultLackofSilver;
				case eGWResultNoAuthority:
					return ProtocolMessageProt16.eGWResultNoAuthority;
				case eGWResultLevelTooLow:
					return ProtocolMessageProt16.eGWResultLevelTooLow;
				default:
					return "Unknown Error";
			}
		}
	}
}
