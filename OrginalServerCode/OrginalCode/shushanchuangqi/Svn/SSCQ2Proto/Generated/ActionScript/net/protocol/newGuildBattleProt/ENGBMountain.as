/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBMountain.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派战灵山
	 */
	public final class ENGBMountain
	{
		public static const eNGBMNone:uint = 0; //无效灵山
		public static const eNGBMEMei:uint = 1; //峨眉
		public static const eNGBMKunLun:uint = 2; //昆仑
		public static const eNGBMHuangShan:uint = 3; //黄山
		public static const eNGBMMax:uint = 4; //最大灵山数
		public static const end:uint = eNGBMMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBMNone:
					return ProtocolMessageProt68.eNGBMNone;
				case eNGBMEMei:
					return ProtocolMessageProt68.eNGBMEMei;
				case eNGBMKunLun:
					return ProtocolMessageProt68.eNGBMKunLun;
				case eNGBMHuangShan:
					return ProtocolMessageProt68.eNGBMHuangShan;
				case eNGBMMax:
					return ProtocolMessageProt68.eNGBMMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
