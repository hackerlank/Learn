/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECuiTiType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 淬体
	 */
	public final class ECuiTiType
	{
		public static const eCuiTiLianPi:uint = 0; //炼皮-武器
		public static const eCuiTiTongJin:uint = 1; //通筋-头盔
		public static const eCuiTiQiangJi:uint = 2; //强肌-戒指
		public static const eCuiTiDuanGu:uint = 3; //锻骨-衣服
		public static const eCuiTiHuoLuo:uint = 4; //活络-鞋子
		public static const eCuiTiXiSui:uint = 5; //洗髓-项链
		public static const eCuiTiMax:uint = 6; //淬体上限
		public static const end:uint = eCuiTiMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eCuiTiLianPi:
					return ProtocolMessageProt20.eCuiTiLianPi;
				case eCuiTiTongJin:
					return ProtocolMessageProt20.eCuiTiTongJin;
				case eCuiTiQiangJi:
					return ProtocolMessageProt20.eCuiTiQiangJi;
				case eCuiTiDuanGu:
					return ProtocolMessageProt20.eCuiTiDuanGu;
				case eCuiTiHuoLuo:
					return ProtocolMessageProt20.eCuiTiHuoLuo;
				case eCuiTiXiSui:
					return ProtocolMessageProt20.eCuiTiXiSui;
				case eCuiTiMax:
					return ProtocolMessageProt20.eCuiTiMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
