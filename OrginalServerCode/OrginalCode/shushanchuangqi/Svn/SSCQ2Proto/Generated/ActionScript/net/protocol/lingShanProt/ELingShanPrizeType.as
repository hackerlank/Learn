/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ELingShanPrizeType.as
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.lingShanProt
 {
	import net.protocol.Message.ProtocolMessageProt135;
	/**
	 * 玩家获取奖励类型
	 */
	public final class ELingShanPrizeType
	{
		public static const eLingShanPrizeType_Invalid:uint = 0; //无效类型
		public static const eLingShanPrizeType_PickNormalBox:uint = 1; //拣普通宝箱
		public static const eLingShanPrizeType_PickGodBox:uint = 2; //拣大宝箱
		public static const eLingShanPrizeType_MoveByGodBox:uint = 3; //带有大宝箱
		public static const eLingShanPrizeType_Win:uint = 4; //击败玩家
		public static const eLingShanPrizeType_Fail:uint = 5; //被击败
		public static const eLingShanPrizeType_End:uint = 6;
		public static const end:uint = eLingShanPrizeType_End;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eLingShanPrizeType_Invalid:
					return ProtocolMessageProt135.eLingShanPrizeType_Invalid;
				case eLingShanPrizeType_PickNormalBox:
					return ProtocolMessageProt135.eLingShanPrizeType_PickNormalBox;
				case eLingShanPrizeType_PickGodBox:
					return ProtocolMessageProt135.eLingShanPrizeType_PickGodBox;
				case eLingShanPrizeType_MoveByGodBox:
					return ProtocolMessageProt135.eLingShanPrizeType_MoveByGodBox;
				case eLingShanPrizeType_Win:
					return ProtocolMessageProt135.eLingShanPrizeType_Win;
				case eLingShanPrizeType_Fail:
					return ProtocolMessageProt135.eLingShanPrizeType_Fail;
				case eLingShanPrizeType_End:
					return ProtocolMessageProt135.eLingShanPrizeType_End;
				default:
					return "Unknown Error";
			}
		}
	}
}
