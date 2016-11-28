/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EImpeachResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 弹劾操作返回结果
	 */
	public final class EImpeachResult
	{
		public static const eGImpeachResultSuccess:uint = 0; //操作成功
		public static const eGImpeachResultFailed:uint = 1; //操作失败
		public static const eGImpeachResultSelf:uint = 2; //不能对自己操作
		public static const eGImpeachResultNotInGuild:uint = 3; //不在帮派中
		public static const eGImpeachResultWrongGuild:uint = 4; //不是该帮派
		public static const eGImpeachResultNoAuthority:uint = 5; //权限不足
		public static const eGImpeachResultHasLaunched:uint = 6; //已经存在弹劾
		public static const eGImpeachResultHasReplyed:uint = 7; //已经回应
		public static const eGImpeachResultLackOfGold:uint = 8; //仙石不足
		public static const end:uint = eGImpeachResultLackOfGold;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGImpeachResultSuccess:
					return ProtocolMessageProt16.eGImpeachResultSuccess;
				case eGImpeachResultFailed:
					return ProtocolMessageProt16.eGImpeachResultFailed;
				case eGImpeachResultSelf:
					return ProtocolMessageProt16.eGImpeachResultSelf;
				case eGImpeachResultNotInGuild:
					return ProtocolMessageProt16.eGImpeachResultNotInGuild;
				case eGImpeachResultWrongGuild:
					return ProtocolMessageProt16.eGImpeachResultWrongGuild;
				case eGImpeachResultNoAuthority:
					return ProtocolMessageProt16.eGImpeachResultNoAuthority;
				case eGImpeachResultHasLaunched:
					return ProtocolMessageProt16.eGImpeachResultHasLaunched;
				case eGImpeachResultHasReplyed:
					return ProtocolMessageProt16.eGImpeachResultHasReplyed;
				case eGImpeachResultLackOfGold:
					return ProtocolMessageProt16.eGImpeachResultLackOfGold;
				default:
					return "Unknown Error";
			}
		}
	}
}
