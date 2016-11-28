/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDrawResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 求签结果
	 */
	public final class EDrawResult
	{
		public static const eDrawResultSuccess:uint = 0; //求签成功
		public static const eDrawResultFailed:uint = 1; //求签失败
		public static const eDrawResultLackOfCount:uint = 2; //次数不足
		public static const eDrawResultLackOfMoney:uint = 3; //金钱不足
		public static const eDrawResultMax:uint = 4; //求签结果最大值
		public static const end:uint = eDrawResultMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eDrawResultSuccess:
					return ProtocolMessageProt20.eDrawResultSuccess;
				case eDrawResultFailed:
					return ProtocolMessageProt20.eDrawResultFailed;
				case eDrawResultLackOfCount:
					return ProtocolMessageProt20.eDrawResultLackOfCount;
				case eDrawResultLackOfMoney:
					return ProtocolMessageProt20.eDrawResultLackOfMoney;
				case eDrawResultMax:
					return ProtocolMessageProt20.eDrawResultMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
