/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EXiheTaskStatus.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 羲和神车任务完成状态
	 */
	public final class EXiheTaskStatus
	{
		public static const eXiheTaskUnfinish:uint = 0; //未完成装货也未请求帮助
		public static const eXiheTaskRequest:uint = 1; //未完成装货已请求帮助
		public static const eXiheTaskFinishURe:uint = 2; //未请求帮助但已完成装货
		public static const eXiheTaskFinishRe:uint = 3; //已请求帮助但已完成装货
		public static const end:uint = eXiheTaskFinishRe;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eXiheTaskUnfinish:
					return ProtocolMessageProt16.eXiheTaskUnfinish;
				case eXiheTaskRequest:
					return ProtocolMessageProt16.eXiheTaskRequest;
				case eXiheTaskFinishURe:
					return ProtocolMessageProt16.eXiheTaskFinishURe;
				case eXiheTaskFinishRe:
					return ProtocolMessageProt16.eXiheTaskFinishRe;
				default:
					return "Unknown Error";
			}
		}
	}
}
