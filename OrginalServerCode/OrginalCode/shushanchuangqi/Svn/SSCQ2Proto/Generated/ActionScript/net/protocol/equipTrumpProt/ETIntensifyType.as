/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETIntensifyType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
 {
	import net.protocol.Message.ProtocolMessageProt30;
	/**
	 * 装备法宝强化类型
	 */
	public final class ETIntensifyType
	{
		public static const eETIntensify_None:int = 0; //无
		public static const eETIntensify_NormalGold:int = 1; //太乙真金
		public static const eETIntensify_GodGold:int = 2; //太乙精金
		public static const eETIntensify_MAX:int = 3; //结束
		public static const end:int = eETIntensify_MAX;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eETIntensify_None:
					return ProtocolMessageProt30.eETIntensify_None;
				case eETIntensify_NormalGold:
					return ProtocolMessageProt30.eETIntensify_NormalGold;
				case eETIntensify_GodGold:
					return ProtocolMessageProt30.eETIntensify_GodGold;
				case eETIntensify_MAX:
					return ProtocolMessageProt30.eETIntensify_MAX;
				default:
					return "Unknown Error";
			}
		}
	}
}
