/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGuildResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 帮派操作返回结果
	 */
	public final class EGuildResult
	{
		public static const eGuildSuccess:uint = 0; //操作成功
		public static const eGuildFailed:uint = 1; //操作失败
		public static const eGuildNotExisted:uint = 2; //不存在帮派
		public static const eGuildExisted:uint = 3; //存在帮派
		public static const eGuildLoading:uint = 4; //加载中
		public static const eGuildTryAgain:uint = 5; //没加载到（已经开始加载了）稍等一会再试
		public static const eGuildLackOfMoney:uint = 6; //帮贡不足
		public static const end:uint = eGuildLackOfMoney;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGuildSuccess:
					return ProtocolMessageProt16.eGuildSuccess;
				case eGuildFailed:
					return ProtocolMessageProt16.eGuildFailed;
				case eGuildNotExisted:
					return ProtocolMessageProt16.eGuildNotExisted;
				case eGuildExisted:
					return ProtocolMessageProt16.eGuildExisted;
				case eGuildLoading:
					return ProtocolMessageProt16.eGuildLoading;
				case eGuildTryAgain:
					return ProtocolMessageProt16.eGuildTryAgain;
				case eGuildLackOfMoney:
					return ProtocolMessageProt16.eGuildLackOfMoney;
				default:
					return "Unknown Error";
			}
		}
	}
}
