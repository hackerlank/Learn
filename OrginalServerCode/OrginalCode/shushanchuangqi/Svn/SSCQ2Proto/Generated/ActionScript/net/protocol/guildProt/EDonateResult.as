/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDonateResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 帮派捐献操作返回结果
	 */
	public final class EDonateResult
	{
		public static const eGDResultSuccess:uint = 0; //操作成功
		public static const eGDResultFailed:uint = 1; //操作失败
		public static const eGDResultNoGuild:uint = 2; //不存在帮派
		public static const eGDResultLackofSilver:uint = 3; //银币不足
		public static const eGDResultNoAuthority:uint = 4; //权限不足
		public static const eGDResultFull:uint = 5; //每日捐献已满
		public static const eGDResultDepotFull:uint = 6; //仓库已满
		public static const end:uint = eGDResultDepotFull;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGDResultSuccess:
					return ProtocolMessageProt16.eGDResultSuccess;
				case eGDResultFailed:
					return ProtocolMessageProt16.eGDResultFailed;
				case eGDResultNoGuild:
					return ProtocolMessageProt16.eGDResultNoGuild;
				case eGDResultLackofSilver:
					return ProtocolMessageProt16.eGDResultLackofSilver;
				case eGDResultNoAuthority:
					return ProtocolMessageProt16.eGDResultNoAuthority;
				case eGDResultFull:
					return ProtocolMessageProt16.eGDResultFull;
				case eGDResultDepotFull:
					return ProtocolMessageProt16.eGDResultDepotFull;
				default:
					return "Unknown Error";
			}
		}
	}
}
