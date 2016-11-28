/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EApplyResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 申请帮派返回结果
	 */
	public final class EApplyResult
	{
		public static const eGApplySuccess:uint = 0; //操作成功
		public static const eGApplyFailed:uint = 1; //操作失败
		public static const eGApplyGuildFull:uint = 2; //帮派成员已满
		public static const eGApplyOtherGuild:uint = 3; //已加入其他帮派
		public static const eGApplyInGuild:uint = 4; //已在帮派中
		public static const eGApplyListFull:uint = 5; //申请列表已满
		public static const eGApplyNoAuthority:uint = 6; //权限不足
		public static const eGApplyNoGuild:uint = 7; //没有帮派
		public static const eGApplyNoUser:uint = 8; //不存在的用户
		public static const eGApplyNotOnline:uint = 9; //玩家不在线
		public static const eGApplyAlreadyApplyed:uint = 10; //您已经发送过该申请
		public static const eGApplyLevelLow:uint = 11; //等级过低
		public static const eGApplyNoSelf:uint = 12; //不能邀请自己
		public static const eGApplyGuildBattle:uint = 13; //帮派战期间无法执行此操作
		public static const end:uint = eGApplyGuildBattle;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGApplySuccess:
					return ProtocolMessageProt16.eGApplySuccess;
				case eGApplyFailed:
					return ProtocolMessageProt16.eGApplyFailed;
				case eGApplyGuildFull:
					return ProtocolMessageProt16.eGApplyGuildFull;
				case eGApplyOtherGuild:
					return ProtocolMessageProt16.eGApplyOtherGuild;
				case eGApplyInGuild:
					return ProtocolMessageProt16.eGApplyInGuild;
				case eGApplyListFull:
					return ProtocolMessageProt16.eGApplyListFull;
				case eGApplyNoAuthority:
					return ProtocolMessageProt16.eGApplyNoAuthority;
				case eGApplyNoGuild:
					return ProtocolMessageProt16.eGApplyNoGuild;
				case eGApplyNoUser:
					return ProtocolMessageProt16.eGApplyNoUser;
				case eGApplyNotOnline:
					return ProtocolMessageProt16.eGApplyNotOnline;
				case eGApplyAlreadyApplyed:
					return ProtocolMessageProt16.eGApplyAlreadyApplyed;
				case eGApplyLevelLow:
					return ProtocolMessageProt16.eGApplyLevelLow;
				case eGApplyNoSelf:
					return ProtocolMessageProt16.eGApplyNoSelf;
				case eGApplyGuildBattle:
					return ProtocolMessageProt16.eGApplyGuildBattle;
				default:
					return "Unknown Error";
			}
		}
	}
}
