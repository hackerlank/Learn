/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EEquipTrumpIntensifyResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
 {
	import net.protocol.Message.ProtocolMessageProt30;
	/**
	 * 装备法宝强化结果
	 */
	public final class EEquipTrumpIntensifyResult
	{
		public static const eETIRSuccess:uint = 0; //装备法宝强化成功
		public static const eETIRFailed:uint = 1; //未知错误
		public static const eETIRCrit:uint = 2; //装备法宝强化成功并暴击
		public static const eETIRMaxErr:uint = 3; //已达最大强化等级
		public static const eETIRSilverErr:uint = 4; //强化时银币不足
		public static const eETIRItemErr:uint = 5; //强化时物品不足
		public static const eETIRCFGErr:uint = 6; //强化配置错误
		public static const eETIRTypeErr:uint = 7; //强化参数错误
		public static const eETIRRandomFailErr:uint = 8; //强化失败
		public static const end:uint = eETIRRandomFailErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eETIRSuccess:
					return ProtocolMessageProt30.eETIRSuccess;
				case eETIRFailed:
					return ProtocolMessageProt30.eETIRFailed;
				case eETIRCrit:
					return ProtocolMessageProt30.eETIRCrit;
				case eETIRMaxErr:
					return ProtocolMessageProt30.eETIRMaxErr;
				case eETIRSilverErr:
					return ProtocolMessageProt30.eETIRSilverErr;
				case eETIRItemErr:
					return ProtocolMessageProt30.eETIRItemErr;
				case eETIRCFGErr:
					return ProtocolMessageProt30.eETIRCFGErr;
				case eETIRTypeErr:
					return ProtocolMessageProt30.eETIRTypeErr;
				case eETIRRandomFailErr:
					return ProtocolMessageProt30.eETIRRandomFailErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
