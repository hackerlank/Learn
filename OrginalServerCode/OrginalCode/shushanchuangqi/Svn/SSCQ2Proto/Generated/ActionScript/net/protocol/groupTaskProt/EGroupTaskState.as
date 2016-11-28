/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGroupTaskState.as
//  Purpose:      师门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.groupTaskProt
 {
	import net.protocol.Message.ProtocolMessageProt51;
	/**
	 * 推任务的状态
	 */
	public final class EGroupTaskState
	{
		public static const eNone:uint = 0; //未接
		public static const eAccept:uint = 1; //已接
		public static const eFinish:uint = 2; //已完成
		public static const eFal:uint = 3; //已失败
		public static const end:uint = eFal;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNone:
					return ProtocolMessageProt51.eNone;
				case eAccept:
					return ProtocolMessageProt51.eAccept;
				case eFinish:
					return ProtocolMessageProt51.eFinish;
				case eFal:
					return ProtocolMessageProt51.eFal;
				default:
					return "Unknown Error";
			}
		}
	}
}
