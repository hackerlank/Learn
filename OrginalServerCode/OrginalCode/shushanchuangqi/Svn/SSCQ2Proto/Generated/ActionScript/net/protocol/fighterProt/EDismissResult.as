/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDismissResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 散功返回
	 */
	public final class EDismissResult
	{
		public static const eDismissSucc:uint = 0; //成功
		public static const eDismissFailed:uint = 1; //失败
		public static const eNeedTakeOffStone:uint = 2; //需要卸下宝石
		public static const end:uint = eNeedTakeOffStone;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eDismissSucc:
					return ProtocolMessageProt20.eDismissSucc;
				case eDismissFailed:
					return ProtocolMessageProt20.eDismissFailed;
				case eNeedTakeOffStone:
					return ProtocolMessageProt20.eNeedTakeOffStone;
				default:
					return "Unknown Error";
			}
		}
	}
}
