/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENpcTaskState.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
 {
	import net.protocol.Message.ProtocolMessageProt15;
	/**
	 * 任务NPC的状态
	 */
	public final class ENpcTaskState
	{
		public static const eNpcTaskNone:uint = 0; //无
		public static const eNpcTaskAccept:uint = 1; //任务可接取
		public static const eNpcTaskUnfinish:uint = 2; //任务未完成
		public static const eNpcTaskSubmit:uint = 3; //任务可交付
		public static const eNpcTaskFuture:uint = 4; //将来可接取
		public static const end:uint = eNpcTaskFuture;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNpcTaskNone:
					return ProtocolMessageProt15.eNpcTaskNone;
				case eNpcTaskAccept:
					return ProtocolMessageProt15.eNpcTaskAccept;
				case eNpcTaskUnfinish:
					return ProtocolMessageProt15.eNpcTaskUnfinish;
				case eNpcTaskSubmit:
					return ProtocolMessageProt15.eNpcTaskSubmit;
				case eNpcTaskFuture:
					return ProtocolMessageProt15.eNpcTaskFuture;
				default:
					return "Unknown Error";
			}
		}
	}
}
