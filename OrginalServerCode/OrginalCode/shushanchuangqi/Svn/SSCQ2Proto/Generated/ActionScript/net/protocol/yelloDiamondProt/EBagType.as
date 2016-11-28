/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBagType.as
//  Purpose:      QQ黄钻协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.yelloDiamondProt
 {
	import net.protocol.Message.ProtocolMessageProt200;
	/**
	 * 礼包类型
	 */
	public final class EBagType
	{
		public static const EBagType_eNone:uint = 0; //无礼包可领取
		public static const EBagType_eDayBag:uint = 1; //黄钻日常礼包
		public static const EBagType_eYearBag:uint = 2; //年黄钻礼包
		public static const EBagType_eLuxuryBag:uint = 3; //豪华QQ黄钻礼包
		public static const EBagType_eNewBag:uint = 4; //新手礼包
		public static const EBagType_eGrowBag:uint = 5; //成长礼包
		public static const EBagType_eHorseBag:uint = 6; //座机礼包
		public static const EBagType_eMax:uint = 7; //最大值
		public static const end:uint = EBagType_eMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EBagType_eNone:
					return ProtocolMessageProt200.EBagType_eNone;
				case EBagType_eDayBag:
					return ProtocolMessageProt200.EBagType_eDayBag;
				case EBagType_eYearBag:
					return ProtocolMessageProt200.EBagType_eYearBag;
				case EBagType_eLuxuryBag:
					return ProtocolMessageProt200.EBagType_eLuxuryBag;
				case EBagType_eNewBag:
					return ProtocolMessageProt200.EBagType_eNewBag;
				case EBagType_eGrowBag:
					return ProtocolMessageProt200.EBagType_eGrowBag;
				case EBagType_eHorseBag:
					return ProtocolMessageProt200.EBagType_eHorseBag;
				case EBagType_eMax:
					return ProtocolMessageProt200.EBagType_eMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
