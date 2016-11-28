/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETHOptResult.as
//  Purpose:      寻宝协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.treasureHuntProt
 {
	import net.protocol.Message.ProtocolMessageProt85;
	/**
	 * 操作结果
	 */
	public final class ETHOptResult
	{
		public static const eTHOptResultFailed:int = 0; //失败
		public static const eTHOptResultSucc:int = 1; //成功
		public static const eTHMaxKillNumDay:int = 2; //今日已达到最大击杀次数
		public static const end:int = eTHMaxKillNumDay;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eTHOptResultFailed:
					return ProtocolMessageProt85.eTHOptResultFailed;
				case eTHOptResultSucc:
					return ProtocolMessageProt85.eTHOptResultSucc;
				case eTHMaxKillNumDay:
					return ProtocolMessageProt85.eTHMaxKillNumDay;
				default:
					return "Unknown Error";
			}
		}
	}
}
