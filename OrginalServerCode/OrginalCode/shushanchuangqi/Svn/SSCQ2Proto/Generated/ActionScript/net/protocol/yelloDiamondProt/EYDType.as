/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EYDType.as
//  Purpose:      QQ黄钻协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yelloDiamondProt
 {
	import net.protocol.Message.ProtocolMessageProt200;
	/**
	 * QQ黄钻类型
	 */
	public final class EYDType
	{
		public static const EYDType_eNone:uint = 0; //未开通QQ黄钻
		public static const EYDType_eDayType:uint = 1; //普通QQ黄钻
		public static const EYDType_eYearType:uint = 2; //年QQ黄钻
		public static const EYDType_eLuxuryType:uint = 3; //豪华QQ黄钻
		public static const end:uint = EYDType_eLuxuryType;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EYDType_eNone:
					return ProtocolMessageProt200.EYDType_eNone;
				case EYDType_eDayType:
					return ProtocolMessageProt200.EYDType_eDayType;
				case EYDType_eYearType:
					return ProtocolMessageProt200.EYDType_eYearType;
				case EYDType_eLuxuryType:
					return ProtocolMessageProt200.EYDType_eLuxuryType;
				default:
					return "Unknown Error";
			}
		}
	}
}
