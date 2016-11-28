/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMemberOperateResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 帮派成员操作返回结果
	 */
	public final class EMemberOperateResult
	{
		public static const eGMOpResultSuccess:uint = 0; //操作成功
		public static const eGMOpResultFailed:uint = 1; //操作失败
		public static const eGMOpResultSelf:uint = 2; //不能对自己操作
		public static const eGMOpResultNotInGuild:uint = 3; //不在帮派中
		public static const eGMOpResultNoAuthority:uint = 4; //权限不足
		public static const eGMOpResultTooHigh:uint = 5; //只能提升至比自己低的职位
		public static const eGMOpResultTooLow:uint = 6; //目标成员职位过低
		public static const eGMOpResultTooMany:uint = 7; //目标职位成员数过多
		public static const eGMOpResultHaveImpeach:uint = 8; //弹劾发起者无法踢出
		public static const eGMOpResultGuildBattle:uint = 9; //帮派战期间无法执行此操作
		public static const end:uint = eGMOpResultGuildBattle;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGMOpResultSuccess:
					return ProtocolMessageProt16.eGMOpResultSuccess;
				case eGMOpResultFailed:
					return ProtocolMessageProt16.eGMOpResultFailed;
				case eGMOpResultSelf:
					return ProtocolMessageProt16.eGMOpResultSelf;
				case eGMOpResultNotInGuild:
					return ProtocolMessageProt16.eGMOpResultNotInGuild;
				case eGMOpResultNoAuthority:
					return ProtocolMessageProt16.eGMOpResultNoAuthority;
				case eGMOpResultTooHigh:
					return ProtocolMessageProt16.eGMOpResultTooHigh;
				case eGMOpResultTooLow:
					return ProtocolMessageProt16.eGMOpResultTooLow;
				case eGMOpResultTooMany:
					return ProtocolMessageProt16.eGMOpResultTooMany;
				case eGMOpResultHaveImpeach:
					return ProtocolMessageProt16.eGMOpResultHaveImpeach;
				case eGMOpResultGuildBattle:
					return ProtocolMessageProt16.eGMOpResultGuildBattle;
				default:
					return "Unknown Error";
			}
		}
	}
}
