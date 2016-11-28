/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EArenaAwardType.as
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
 {
	import net.protocol.Message.ProtocolMessageProt26;
	/**
	 * 奖励包类型
	 */
	public final class EArenaAwardType
	{
		public static const Type_NONE:uint = 0; //无定义
		public static const Type_Level:uint = 1; //段位包
		public static const Type_Rank:uint = 2; //排名包
		public static const Type_LadderRank:uint = 3; //天梯排名包
		public static const end:uint = Type_LadderRank;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case Type_NONE:
					return ProtocolMessageProt26.Type_NONE;
				case Type_Level:
					return ProtocolMessageProt26.Type_Level;
				case Type_Rank:
					return ProtocolMessageProt26.Type_Rank;
				case Type_LadderRank:
					return ProtocolMessageProt26.Type_LadderRank;
				default:
					return "Unknown Error";
			}
		}
	}
}
