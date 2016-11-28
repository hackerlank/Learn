/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EInviteResult.as
//  Purpose:      邀请好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
 {
	import net.protocol.Message.ProtocolMessageProt134;
	/**
	 * 好友相关的结果
	 */
	public final class EInviteResult
	{
		public static const eInvite_Success:uint = 0; //成功
		public static const eInvite_Failed:uint = 1; //失败
		public static const eInvite_ErrorUserID:uint = 2; //玩家id错误
		public static const eInvite_ErrorCFGID:uint = 3; //配置id错误
		public static const eInvite_TaskInit:uint = 4; //任务未完成
		public static const eInvite_TaskTakedPrize:uint = 5; //任务奖励已领取
		public static const eInvite_ServerBusy:uint = 6; //任务奖励已领取
		public static const end:uint = eInvite_ServerBusy;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eInvite_Success:
					return ProtocolMessageProt134.eInvite_Success;
				case eInvite_Failed:
					return ProtocolMessageProt134.eInvite_Failed;
				case eInvite_ErrorUserID:
					return ProtocolMessageProt134.eInvite_ErrorUserID;
				case eInvite_ErrorCFGID:
					return ProtocolMessageProt134.eInvite_ErrorCFGID;
				case eInvite_TaskInit:
					return ProtocolMessageProt134.eInvite_TaskInit;
				case eInvite_TaskTakedPrize:
					return ProtocolMessageProt134.eInvite_TaskTakedPrize;
				case eInvite_ServerBusy:
					return ProtocolMessageProt134.eInvite_ServerBusy;
				default:
					return "Unknown Error";
			}
		}
	}
}
