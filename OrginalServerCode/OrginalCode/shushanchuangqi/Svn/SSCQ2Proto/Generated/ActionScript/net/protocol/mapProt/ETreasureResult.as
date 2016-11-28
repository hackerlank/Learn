/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETreasureResult.as
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
 {
	import net.protocol.Message.ProtocolMessageProt5;
	/**
	 * 宝藏图操作结果
	 */
	public final class ETreasureResult
	{
		public static const eTreasureSuccess:uint = 0; //成功
		public static const eTreasureFail:uint = 1; //失败
		public static const eTreasureNoItem:uint = 2; //没有藏宝图
		public static const eTreasureLackCoin:uint = 3; //仙石不足
		public static const eTreasureNoInArea:uint = 4; //没有在指定区域挖掘
		public static const eTreasureDropErr:uint = 5; //掉落物品错误
		public static const eTreasureDiamond:uint = 6; //钻石不足
		public static const eTreasureBuyInfoSuccess:uint = 7; //购买信息成功
		public static const end:uint = eTreasureBuyInfoSuccess;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eTreasureSuccess:
					return ProtocolMessageProt5.eTreasureSuccess;
				case eTreasureFail:
					return ProtocolMessageProt5.eTreasureFail;
				case eTreasureNoItem:
					return ProtocolMessageProt5.eTreasureNoItem;
				case eTreasureLackCoin:
					return ProtocolMessageProt5.eTreasureLackCoin;
				case eTreasureNoInArea:
					return ProtocolMessageProt5.eTreasureNoInArea;
				case eTreasureDropErr:
					return ProtocolMessageProt5.eTreasureDropErr;
				case eTreasureDiamond:
					return ProtocolMessageProt5.eTreasureDiamond;
				case eTreasureBuyInfoSuccess:
					return ProtocolMessageProt5.eTreasureBuyInfoSuccess;
				default:
					return "Unknown Error";
			}
		}
	}
}
