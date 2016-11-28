/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBeastSoulResult.as
//  Purpose:      阵灵相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.formationProt
 {
	import net.protocol.Message.ProtocolMessageProt22;
	/**
	 * 兽魂操作返回结果
	 */
	public final class EBeastSoulResult
	{
		public static const eBeastSoulSucces:uint = 0; //操作成功
		public static const eBeastSoulFailed:uint = 1; //操作失败
		public static const eBeastSoulLackOfMoney:uint = 2; //对应货币不足
		public static const eBeastSoulRankMax:uint = 3; //已经是最大等级
		public static const eBeastSoulLevelLimit:uint = 4; //玩家等级不足
		public static const end:uint = eBeastSoulLevelLimit;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBeastSoulSucces:
					return ProtocolMessageProt22.eBeastSoulSucces;
				case eBeastSoulFailed:
					return ProtocolMessageProt22.eBeastSoulFailed;
				case eBeastSoulLackOfMoney:
					return ProtocolMessageProt22.eBeastSoulLackOfMoney;
				case eBeastSoulRankMax:
					return ProtocolMessageProt22.eBeastSoulRankMax;
				case eBeastSoulLevelLimit:
					return ProtocolMessageProt22.eBeastSoulLevelLimit;
				default:
					return "Unknown Error";
			}
		}
	}
}
