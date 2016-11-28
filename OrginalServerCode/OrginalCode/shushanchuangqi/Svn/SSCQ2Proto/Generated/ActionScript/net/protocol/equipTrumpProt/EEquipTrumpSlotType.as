/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EEquipTrumpSlotType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.equipTrumpProt
 {
	import net.protocol.Message.ProtocolMessageProt30;
	/**
	 * 装备法宝位类型
	 */
	public final class EEquipTrumpSlotType
	{
		public static const eETSTNone:int = 0; //无
		public static const eETSTInnate:int = 1; //先天法宝
		public static const eETSTPassive:int = 2; //被动
		public static const eETSTHalo:int = 3; //光环
		public static const eETSTTransform:int = 4; //变身
		public static const eETSTMax:int = 5; //结束
		public static const end:int = eETSTMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eETSTNone:
					return ProtocolMessageProt30.eETSTNone;
				case eETSTInnate:
					return ProtocolMessageProt30.eETSTInnate;
				case eETSTPassive:
					return ProtocolMessageProt30.eETSTPassive;
				case eETSTHalo:
					return ProtocolMessageProt30.eETSTHalo;
				case eETSTTransform:
					return ProtocolMessageProt30.eETSTTransform;
				case eETSTMax:
					return ProtocolMessageProt30.eETSTMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
