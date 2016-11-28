/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EFriendGroupType.as
//  Purpose:      好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
 {
	import net.protocol.Message.ProtocolMessageProt24;
	/**
	 * 好友组别
	 */
	public final class EFriendGroupType
	{
		public static const eGroupNone:uint = 0; //无
		public static const eCloseFriend:uint = 1; //亲密好友
		public static const eCommonFriend:uint = 2; //普通好友
		public static const eBlackFriend:uint = 3; //黑名单
		public static const eGroupEnd:uint = 4; //结尾
		public static const end:uint = eGroupEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGroupNone:
					return ProtocolMessageProt24.eGroupNone;
				case eCloseFriend:
					return ProtocolMessageProt24.eCloseFriend;
				case eCommonFriend:
					return ProtocolMessageProt24.eCommonFriend;
				case eBlackFriend:
					return ProtocolMessageProt24.eBlackFriend;
				case eGroupEnd:
					return ProtocolMessageProt24.eGroupEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
