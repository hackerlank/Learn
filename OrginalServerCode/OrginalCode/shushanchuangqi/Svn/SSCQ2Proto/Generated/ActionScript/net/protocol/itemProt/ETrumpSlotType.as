/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ETrumpSlotType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 法宝位类型
	 */
	public final class ETrumpSlotType
	{
		public static const eSlotTrump1:int = 0; //法宝1
		public static const eSlotTrump2:int = 1; //法宝2
		public static const eSlotTrump3:int = 2; //法宝3
		public static const eSlotTrump4:int = 3; //法宝4
		public static const eSlotTrump5:int = 4; //法宝5
		public static const eSlotTrump6:int = 5; //法宝6
		public static const eSlotTrump7:int = 6; //法宝7
		public static const eSlotTrump8:int = 7; //法宝8
		public static const eSlotTrump9:int = 8; //法宝9
		public static const eSlotTrump10:int = 9; //法宝10
		public static const end:int = eSlotTrump10;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eSlotTrump1:
					return ProtocolMessageProt18.eSlotTrump1;
				case eSlotTrump2:
					return ProtocolMessageProt18.eSlotTrump2;
				case eSlotTrump3:
					return ProtocolMessageProt18.eSlotTrump3;
				case eSlotTrump4:
					return ProtocolMessageProt18.eSlotTrump4;
				case eSlotTrump5:
					return ProtocolMessageProt18.eSlotTrump5;
				case eSlotTrump6:
					return ProtocolMessageProt18.eSlotTrump6;
				case eSlotTrump7:
					return ProtocolMessageProt18.eSlotTrump7;
				case eSlotTrump8:
					return ProtocolMessageProt18.eSlotTrump8;
				case eSlotTrump9:
					return ProtocolMessageProt18.eSlotTrump9;
				case eSlotTrump10:
					return ProtocolMessageProt18.eSlotTrump10;
				default:
					return "Unknown Error";
			}
		}
	}
}
