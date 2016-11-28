/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EStoreType.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
 {
	import net.protocol.Message.ProtocolMessageProt18;
	/**
	 * 存储类型
	 */
	public final class EStoreType
	{
		public static const eStoreNone:uint = 0; //无
		public static const eStorePack:uint = 1; //道具包裹
		public static const eStoreDepot:uint = 2; //角色仓库
		public static const eStorePlayerTrump:uint = 3; //法宝栏
		public static const eStorePlayerCitta:uint = 4; //心法栏
		public static const eStoreFashion:uint = 5; //时装栏
		public static const eStoreGemstone:uint = 6; //宝石栏
		public static const eStoreEquipTrump:uint = 7; //装备法宝栏
		public static const end:uint = eStoreEquipTrump;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eStoreNone:
					return ProtocolMessageProt18.eStoreNone;
				case eStorePack:
					return ProtocolMessageProt18.eStorePack;
				case eStoreDepot:
					return ProtocolMessageProt18.eStoreDepot;
				case eStorePlayerTrump:
					return ProtocolMessageProt18.eStorePlayerTrump;
				case eStorePlayerCitta:
					return ProtocolMessageProt18.eStorePlayerCitta;
				case eStoreFashion:
					return ProtocolMessageProt18.eStoreFashion;
				case eStoreGemstone:
					return ProtocolMessageProt18.eStoreGemstone;
				case eStoreEquipTrump:
					return ProtocolMessageProt18.eStoreEquipTrump;
				default:
					return "Unknown Error";
			}
		}
	}
}
