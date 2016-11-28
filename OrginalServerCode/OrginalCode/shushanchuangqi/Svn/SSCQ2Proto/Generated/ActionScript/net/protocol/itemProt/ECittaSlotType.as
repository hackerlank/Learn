/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECittaSlotType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 心法位类型
	 */
	public final class ECittaSlotType
	{
		public static const eSlotCitta1:int = 0; //心法1
		public static const eSlotCitta2:int = 1; //心法2
		public static const eSlotCitta3:int = 2; //心法3
		public static const eSlotCitta4:int = 3; //心法4
		public static const eSlotCitta5:int = 4; //心法5
		public static const eSlotCitta6:int = 5; //心法6
		public static const eSlotCitta7:int = 6; //心法7
		public static const eSlotCitta8:int = 7; //心法8
		public static const end:int = eSlotCitta8;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eSlotCitta1:
					return ProtocolMessageProt18.eSlotCitta1;
				case eSlotCitta2:
					return ProtocolMessageProt18.eSlotCitta2;
				case eSlotCitta3:
					return ProtocolMessageProt18.eSlotCitta3;
				case eSlotCitta4:
					return ProtocolMessageProt18.eSlotCitta4;
				case eSlotCitta5:
					return ProtocolMessageProt18.eSlotCitta5;
				case eSlotCitta6:
					return ProtocolMessageProt18.eSlotCitta6;
				case eSlotCitta7:
					return ProtocolMessageProt18.eSlotCitta7;
				case eSlotCitta8:
					return ProtocolMessageProt18.eSlotCitta8;
				default:
					return "Unknown Error";
			}
		}
	}
}
