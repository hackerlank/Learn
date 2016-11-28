/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EEquipTrumpBreakResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
 {
	import net.protocol.Message.ProtocolMessageProt30;
	/**
	 * 装备法宝分解结果
	 */
	public final class EEquipTrumpBreakResult
	{
		public static const eETBRSuccess:uint = 0; //成功
		public static const eETBRFailed:uint = 1; //失败
		public static const eETBRPackFull:uint = 2; //背包已满
		public static const eETBREquiped:uint = 3; //仍在装备中
		public static const eETBRMax:uint = 4; //最大值
		public static const end:uint = eETBRMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eETBRSuccess:
					return ProtocolMessageProt30.eETBRSuccess;
				case eETBRFailed:
					return ProtocolMessageProt30.eETBRFailed;
				case eETBRPackFull:
					return ProtocolMessageProt30.eETBRPackFull;
				case eETBREquiped:
					return ProtocolMessageProt30.eETBREquiped;
				case eETBRMax:
					return ProtocolMessageProt30.eETBRMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
