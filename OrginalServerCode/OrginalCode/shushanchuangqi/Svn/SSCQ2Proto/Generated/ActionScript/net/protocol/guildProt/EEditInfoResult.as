/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EEditInfoResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 编辑公告返回结果
	 */
	public final class EEditInfoResult
	{
		public static const eGEditInfoSuccess:uint = 0; //操作成功
		public static const eGEditInfoFailed:uint = 1; //操作失败
		public static const eGEditInfoNotInGuild:uint = 2; //不在帮派中
		public static const eGEditInfoNoAuthority:uint = 3; //权限不足
		public static const eGEditInfoTooLong:uint = 4; //信息过长
		public static const end:uint = eGEditInfoTooLong;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGEditInfoSuccess:
					return ProtocolMessageProt16.eGEditInfoSuccess;
				case eGEditInfoFailed:
					return ProtocolMessageProt16.eGEditInfoFailed;
				case eGEditInfoNotInGuild:
					return ProtocolMessageProt16.eGEditInfoNotInGuild;
				case eGEditInfoNoAuthority:
					return ProtocolMessageProt16.eGEditInfoNoAuthority;
				case eGEditInfoTooLong:
					return ProtocolMessageProt16.eGEditInfoTooLong;
				default:
					return "Unknown Error";
			}
		}
	}
}
