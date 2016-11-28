/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ELingShanObjType.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
 {
	import net.protocol.Message.ProtocolMessageProt135;
	/**
	 * 地图格子上单元类型（暂时不用）
	 */
	public final class ELingShanObjType
	{
		public static const eLingShanObjType_Invalid:uint = 0; //无效类型
		public static const eLingShanObjType_Player:uint = 1; //玩家
		public static const eLingShanObjType_Box:uint = 2; //物品(宝箱)
		public static const eLingShanObjType_Monster:uint = 3; //怪物
		public static const eObjType_End:uint = 4; //活动结束状态
		public static const end:uint = eObjType_End;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eLingShanObjType_Invalid:
					return ProtocolMessageProt135.eLingShanObjType_Invalid;
				case eLingShanObjType_Player:
					return ProtocolMessageProt135.eLingShanObjType_Player;
				case eLingShanObjType_Box:
					return ProtocolMessageProt135.eLingShanObjType_Box;
				case eLingShanObjType_Monster:
					return ProtocolMessageProt135.eLingShanObjType_Monster;
				case eObjType_End:
					return ProtocolMessageProt135.eObjType_End;
				default:
					return "Unknown Error";
			}
		}
	}
}
