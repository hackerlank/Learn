/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EEquipTrumpShuffleResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
 {
	import net.protocol.Message.ProtocolMessageProt30;
	/**
	 * 装备法宝洗炼结果
	 */
	public final class EEquipTrumpShuffleResult
	{
		public static const eETSRSuccess:uint = 0; //装备法宝洗炼成功
		public static const eETSRFailed:uint = 1; //装备法宝洗炼失败
		public static const eETSRLevelErr:uint = 2; //装备法宝洗炼时玩家等级不足
		public static const eETSRSilverErr:uint = 3; //洗炼时银币不足
		public static const eETSRMaterialErr:uint = 4; //洗炼时材料不足
		public static const end:uint = eETSRMaterialErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eETSRSuccess:
					return ProtocolMessageProt30.eETSRSuccess;
				case eETSRFailed:
					return ProtocolMessageProt30.eETSRFailed;
				case eETSRLevelErr:
					return ProtocolMessageProt30.eETSRLevelErr;
				case eETSRSilverErr:
					return ProtocolMessageProt30.eETSRSilverErr;
				case eETSRMaterialErr:
					return ProtocolMessageProt30.eETSRMaterialErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
