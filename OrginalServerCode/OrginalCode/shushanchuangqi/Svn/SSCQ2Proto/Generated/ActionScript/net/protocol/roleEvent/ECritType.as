/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECritType.as
//  Purpose:      玩家在GameServer的消息处理
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.roleEvent
 {
	import net.protocol.Message.ProtocolMessageProt11;
	/**
	 * 暴击类型
	 */
	public final class ECritType
	{
		public static const ePetCrit:int = 0; //阵灵暴击
		public static const eHorseCrit:int = 1; //坐骑暴击
		public static const eFashionCrit:int = 2; //时装暴击
		public static const eTrumpCrit:int = 3; //法宝暴击
		public static const eDujieCrit:int = 4; //渡劫暴击
		public static const eMoneyTreeCrit:int = 5; //摇钱树暴击
		public static const end:int = eMoneyTreeCrit;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case ePetCrit:
					return ProtocolMessageProt11.ePetCrit;
				case eHorseCrit:
					return ProtocolMessageProt11.eHorseCrit;
				case eFashionCrit:
					return ProtocolMessageProt11.eFashionCrit;
				case eTrumpCrit:
					return ProtocolMessageProt11.eTrumpCrit;
				case eDujieCrit:
					return ProtocolMessageProt11.eDujieCrit;
				case eMoneyTreeCrit:
					return ProtocolMessageProt11.eMoneyTreeCrit;
				default:
					return "Unknown Error";
			}
		}
	}
}
