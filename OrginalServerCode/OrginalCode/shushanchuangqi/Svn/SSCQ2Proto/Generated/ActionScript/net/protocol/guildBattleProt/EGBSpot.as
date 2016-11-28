/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGBSpot.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt76;
	/**
	 * 帮派战据点
	 */
	public final class EGBSpot
	{
		public static const eGBSpotNone:uint = 0; //无效据点
		public static const eGBSpotYuzhufeng:uint = 1; //玉柱峰
		public static const eGBSpotGuangmingding:uint = 2; //光明顶
		public static const eGBSpotShiwangfeng:uint = 3; //十王峰
		public static const eGBSpotWanfoding:uint = 4; //万佛顶
		public static const eGBSpotMax:uint = 5; //最大据点
		public static const eGBSpotZhurongfeng:uint = 5; //祝融峰
		public static const eGBSpotYuxuding:uint = 6; //玉虚顶
		public static const end:uint = eGBSpotYuxuding;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBSpotNone:
					return ProtocolMessageProt76.eGBSpotNone;
				case eGBSpotYuzhufeng:
					return ProtocolMessageProt76.eGBSpotYuzhufeng;
				case eGBSpotGuangmingding:
					return ProtocolMessageProt76.eGBSpotGuangmingding;
				case eGBSpotShiwangfeng:
					return ProtocolMessageProt76.eGBSpotShiwangfeng;
				case eGBSpotWanfoding:
					return ProtocolMessageProt76.eGBSpotWanfoding;
				case eGBSpotMax:
					return ProtocolMessageProt76.eGBSpotMax;
				case eGBSpotYuxuding:
					return ProtocolMessageProt76.eGBSpotYuxuding;
				default:
					return "Unknown Error";
			}
		}
	}
}
