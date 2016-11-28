/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETHStatus.as
//  Purpose:      寻宝协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
 {
	import net.protocol.Message.ProtocolMessageProt85;
	/**
	 * 寻宝状态
	 */
	public final class ETHStatus
	{
		public static const eTHNone:int = 0; //无
		public static const eTHProgress:int = 1; //寻宝进行中
		public static const eTHWaitGetAward:int = 2; //等待领取奖品
		public static const end:int = eTHWaitGetAward;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eTHNone:
					return ProtocolMessageProt85.eTHNone;
				case eTHProgress:
					return ProtocolMessageProt85.eTHProgress;
				case eTHWaitGetAward:
					return ProtocolMessageProt85.eTHWaitGetAward;
				default:
					return "Unknown Error";
			}
		}
	}
}
