/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EEquipTrumpType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
 {
	import net.protocol.Message.ProtocolMessageProt30;
	/**
	 * 能装备法宝的道具类型
	 */
	public final class EEquipTrumpType
	{
		public static const eETTNone:uint = 0; //无
		public static const eETTInnate:uint = 1; //先天法宝
		public static const eETTPassive:uint = 2; //被动法宝
		public static const eETTHalo:uint = 3; //光环法宝
		public static const eETTTransform:uint = 4; //变身法宝
		public static const eETTEnd:uint = 5; //结束
		public static const end:uint = eETTEnd;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eETTNone:
					return ProtocolMessageProt30.eETTNone;
				case eETTInnate:
					return ProtocolMessageProt30.eETTInnate;
				case eETTPassive:
					return ProtocolMessageProt30.eETTPassive;
				case eETTHalo:
					return ProtocolMessageProt30.eETTHalo;
				case eETTTransform:
					return ProtocolMessageProt30.eETTTransform;
				case eETTEnd:
					return ProtocolMessageProt30.eETTEnd;
				default:
					return "Unknown Error";
			}
		}
	}
}
