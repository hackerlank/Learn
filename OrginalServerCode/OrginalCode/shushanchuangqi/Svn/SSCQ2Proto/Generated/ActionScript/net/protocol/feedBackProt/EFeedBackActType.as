/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EFeedBackActType.as
//  Purpose:      消费回馈
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.feedBackProt
 {
	import net.protocol.Message.ProtocolMessageProt144;
	/**
	 * 消费回馈类型
	 */
	public final class EFeedBackActType
	{
		public static const eFeedBackActType_Invalid:uint = 0; //无效
		public static const eFeedBackActType_EquipTrump:uint = 1; //法宝强化
		public static const eFeedBackActType_Stone:uint = 2; //宝石合成
		public static const end:uint = eFeedBackActType_Stone;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eFeedBackActType_Invalid:
					return ProtocolMessageProt144.eFeedBackActType_Invalid;
				case eFeedBackActType_EquipTrump:
					return ProtocolMessageProt144.eFeedBackActType_EquipTrump;
				case eFeedBackActType_Stone:
					return ProtocolMessageProt144.eFeedBackActType_Stone;
				default:
					return "Unknown Error";
			}
		}
	}
}
