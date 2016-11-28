/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EInvitedTask.as
//  Purpose:      邀请好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.inviteGS
 {
	import net.protocol.Message.ProtocolMessageProt134;
	/**
	 * 邀请任务状态
	 */
	public final class EInvitedTask
	{
		public static const eInvitedTask_Init:uint = 0; //未完成
		public static const eInvitedTask_Finish:uint = 1; //已完成
		public static const eInvitedTask_TakePrized:uint = 2; //已领奖
		public static const end:uint = eInvitedTask_TakePrized;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eInvitedTask_Init:
					return ProtocolMessageProt134.eInvitedTask_Init;
				case eInvitedTask_Finish:
					return ProtocolMessageProt134.eInvitedTask_Finish;
				case eInvitedTask_TakePrized:
					return ProtocolMessageProt134.eInvitedTask_TakePrized;
				default:
					return "Unknown Error";
			}
		}
	}
}
