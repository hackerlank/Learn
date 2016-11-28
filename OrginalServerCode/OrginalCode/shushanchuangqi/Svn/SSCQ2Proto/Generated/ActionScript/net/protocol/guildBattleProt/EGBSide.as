/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGBSide.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt76;
	/**
	 * 帮派战战斗方向
	 */
	public final class EGBSide
	{
		public static const eGBSideA:uint = 0; //A方
		public static const eGBSideB:uint = 1; //B方
		public static const eGBSideInvalid:uint = 2; //无效方
		public static const end:uint = eGBSideInvalid;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBSideA:
					return ProtocolMessageProt76.eGBSideA;
				case eGBSideB:
					return ProtocolMessageProt76.eGBSideB;
				case eGBSideInvalid:
					return ProtocolMessageProt76.eGBSideInvalid;
				default:
					return "Unknown Error";
			}
		}
	}
}
