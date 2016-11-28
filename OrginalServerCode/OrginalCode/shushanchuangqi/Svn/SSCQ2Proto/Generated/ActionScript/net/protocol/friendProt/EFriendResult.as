/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EFriendResult.as
//  Purpose:      好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.friendProt
 {
	import net.protocol.Message.ProtocolMessageProt24;
	/**
	 * 好友相关的结果
	 */
	public final class EFriendResult
	{
		public static const eFriendSuccess:uint = 0; //成功
		public static const eFriendFailed:uint = 1; //失败
		public static const eFriendDuplicateErr:uint = 2; //已经存在
		public static const eFriendOtherDuplicateErr:uint = 3; //已存在于目标的好友列表
		public static const eFriendMaxNumErr:uint = 4; //好友达到上限
		public static const eFriendOtherMaxNumErr:uint = 5; //对方好友达到上限
		public static const eFriendOfflineErr:uint = 6; //对方不在线
		public static const eFriendRefuseErr:uint = 7; //对方拒绝
		public static const eFriendNotExistErr:uint = 8; //目标不存在
		public static const eFriendGroupIDErr:uint = 9; //分组ID错误
		public static const eFriendOnBlackList:uint = 10; //对方已在你的黑名单中
		public static const eFriendOnTarBlackList:uint = 11; //对方已把你拉入黑名单
		public static const eFriendSign:uint = 12; //修改签名成功
		public static const eFriendSignLenErr:uint = 13; //签名过长
		public static const eFriendMood:uint = 14; //修改表情成功
		public static const eFriendOtherErr:uint = 15; //其他错误
		public static const end:uint = eFriendOtherErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eFriendSuccess:
					return ProtocolMessageProt24.eFriendSuccess;
				case eFriendFailed:
					return ProtocolMessageProt24.eFriendFailed;
				case eFriendDuplicateErr:
					return ProtocolMessageProt24.eFriendDuplicateErr;
				case eFriendOtherDuplicateErr:
					return ProtocolMessageProt24.eFriendOtherDuplicateErr;
				case eFriendMaxNumErr:
					return ProtocolMessageProt24.eFriendMaxNumErr;
				case eFriendOtherMaxNumErr:
					return ProtocolMessageProt24.eFriendOtherMaxNumErr;
				case eFriendOfflineErr:
					return ProtocolMessageProt24.eFriendOfflineErr;
				case eFriendRefuseErr:
					return ProtocolMessageProt24.eFriendRefuseErr;
				case eFriendNotExistErr:
					return ProtocolMessageProt24.eFriendNotExistErr;
				case eFriendGroupIDErr:
					return ProtocolMessageProt24.eFriendGroupIDErr;
				case eFriendOnBlackList:
					return ProtocolMessageProt24.eFriendOnBlackList;
				case eFriendOnTarBlackList:
					return ProtocolMessageProt24.eFriendOnTarBlackList;
				case eFriendSign:
					return ProtocolMessageProt24.eFriendSign;
				case eFriendSignLenErr:
					return ProtocolMessageProt24.eFriendSignLenErr;
				case eFriendMood:
					return ProtocolMessageProt24.eFriendMood;
				case eFriendOtherErr:
					return ProtocolMessageProt24.eFriendOtherErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
