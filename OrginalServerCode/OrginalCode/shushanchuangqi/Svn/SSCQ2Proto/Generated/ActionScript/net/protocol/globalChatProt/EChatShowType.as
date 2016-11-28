/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EChatShowType.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
 {
	import net.protocol.Message.ProtocolMessageProt28;
	/**
	 * 展示类型
	 */
	public final class EChatShowType
	{
		public static const eShowItem:uint = 0; //道具
		public static const eShowRole:uint = 1; //角色
		public static const eShowPet:uint = 2; //阵灵
		public static const eShowHorse:uint = 3; //坐骑
		public static const end:uint = eShowHorse;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eShowItem:
					return ProtocolMessageProt28.eShowItem;
				case eShowRole:
					return ProtocolMessageProt28.eShowRole;
				case eShowPet:
					return ProtocolMessageProt28.eShowPet;
				case eShowHorse:
					return ProtocolMessageProt28.eShowHorse;
				default:
					return "Unknown Error";
			}
		}
	}
}
