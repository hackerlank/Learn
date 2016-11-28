/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ESShowInfoType.as
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.globalChatProt
 {
	import net.protocol.Message.ProtocolMessageProt28;
	/**
	 * 炫耀类型
	 */
	public final class ESShowInfoType
	{
		public static const eFlauntGood:uint = 0; //物品，使用SItem解析
		public static const eFlauntHero:uint = 1; //散仙，使用SFlauntHero解析
		public static const eFlauntPet:uint = 2; //阵灵，使用SFlauntPet解析
		public static const eFlauntHorse:uint = 3; //坐骑，使用SFlauntHorse解析
		public static const eShowAchievement:uint = 4; //成就
		public static const eFlauntFashion:uint = 5; //时装，使用SFlauntFashion解析
		public static const end:uint = eFlauntFashion;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eFlauntGood:
					return ProtocolMessageProt28.eFlauntGood;
				case eFlauntHero:
					return ProtocolMessageProt28.eFlauntHero;
				case eFlauntPet:
					return ProtocolMessageProt28.eFlauntPet;
				case eFlauntHorse:
					return ProtocolMessageProt28.eFlauntHorse;
				case eShowAchievement:
					return ProtocolMessageProt28.eShowAchievement;
				case eFlauntFashion:
					return ProtocolMessageProt28.eFlauntFashion;
				default:
					return "Unknown Error";
			}
		}
	}
}
