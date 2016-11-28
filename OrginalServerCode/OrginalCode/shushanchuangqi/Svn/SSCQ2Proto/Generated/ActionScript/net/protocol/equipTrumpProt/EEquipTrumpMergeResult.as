/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EEquipTrumpMergeResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
 {
	import net.protocol.Message.ProtocolMessageProt30;
	/**
	 * 装备法宝合成结果
	 */
	public final class EEquipTrumpMergeResult
	{
		public static const eETMRSuccess:uint = 0; //成功
		public static const eETMRFailed:uint = 1; //失败
		public static const eETMRLackOfMaterial:uint = 2; //材料不足
		public static const eETMRLackOfSilver:uint = 3; //银币不足
		public static const eETMRPackFull:uint = 4; //背包已满
		public static const eETMRMax:uint = 5; //最大值
		public static const end:uint = eETMRMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eETMRSuccess:
					return ProtocolMessageProt30.eETMRSuccess;
				case eETMRFailed:
					return ProtocolMessageProt30.eETMRFailed;
				case eETMRLackOfMaterial:
					return ProtocolMessageProt30.eETMRLackOfMaterial;
				case eETMRLackOfSilver:
					return ProtocolMessageProt30.eETMRLackOfSilver;
				case eETMRPackFull:
					return ProtocolMessageProt30.eETMRPackFull;
				case eETMRMax:
					return ProtocolMessageProt30.eETMRMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
