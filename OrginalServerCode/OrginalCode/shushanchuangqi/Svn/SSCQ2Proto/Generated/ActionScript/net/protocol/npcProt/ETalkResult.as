/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETalkResult.as
//  Purpose:      NPC相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.npcProt
 {
	import net.protocol.Message.ProtocolMessageProt14;
	/**
	 * NPC对话结果
	 */
	public final class ETalkResult
	{
		public static const eTalkSucceed:uint = 0; //打开对话成功
		public static const eTalkNotExist:uint = 1; //NPC不存在
		public static const eTalkTooFar:uint = 2; //玩家距离NPC太远
		public static const eTalkScriptFail:uint = 3; //NPC对话脚本执行失败
		public static const eTalkOther:uint = 4; //其它错误
		public static const end:uint = eTalkOther;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eTalkSucceed:
					return ProtocolMessageProt14.eTalkSucceed;
				case eTalkNotExist:
					return ProtocolMessageProt14.eTalkNotExist;
				case eTalkTooFar:
					return ProtocolMessageProt14.eTalkTooFar;
				case eTalkScriptFail:
					return ProtocolMessageProt14.eTalkScriptFail;
				case eTalkOther:
					return ProtocolMessageProt14.eTalkOther;
				default:
					return "Unknown Error";
			}
		}
	}
}
