/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ESetAuthorityResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 设置权限返回结果
	 */
	public final class ESetAuthorityResult
	{
		public static const eGSetAuthoritySuccess:uint = 0; //操作成功
		public static const eGSetAuthorityFailed:uint = 1; //操作失败
		public static const eGSetAuthorityNotInGuild:uint = 2; //不在帮派中
		public static const eGSetAuthorityNoAuthority:uint = 3; //权限不足
		public static const eGSetAuthorityTooHigh:uint = 4; //只能提升至比自己低的职位
		public static const eGSetAuthorityNoSelfRank:uint = 5; //不能改变自身权限
		public static const end:uint = eGSetAuthorityNoSelfRank;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGSetAuthoritySuccess:
					return ProtocolMessageProt16.eGSetAuthoritySuccess;
				case eGSetAuthorityFailed:
					return ProtocolMessageProt16.eGSetAuthorityFailed;
				case eGSetAuthorityNotInGuild:
					return ProtocolMessageProt16.eGSetAuthorityNotInGuild;
				case eGSetAuthorityNoAuthority:
					return ProtocolMessageProt16.eGSetAuthorityNoAuthority;
				case eGSetAuthorityTooHigh:
					return ProtocolMessageProt16.eGSetAuthorityTooHigh;
				case eGSetAuthorityNoSelfRank:
					return ProtocolMessageProt16.eGSetAuthorityNoSelfRank;
				default:
					return "Unknown Error";
			}
		}
	}
}
