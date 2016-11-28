/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETaskState.as
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.taskProt
 {
	import net.protocol.Message.ProtocolMessageProt15;
	/**
	 * 任务的状态
	 */
	public final class ETaskState
	{
		public static const eTaskNone:uint = 0; //无
		public static const eTaskAccept:uint = 1; //任务已接取
		public static const eTaskFail:uint = 2; //任务失败
		public static const eTaskFinish:uint = 3; //任务完成
		public static const end:uint = eTaskFinish;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eTaskNone:
					return ProtocolMessageProt15.eTaskNone;
				case eTaskAccept:
					return ProtocolMessageProt15.eTaskAccept;
				case eTaskFail:
					return ProtocolMessageProt15.eTaskFail;
				case eTaskFinish:
					return ProtocolMessageProt15.eTaskFinish;
				default:
					return "Unknown Error";
			}
		}
	}
}
