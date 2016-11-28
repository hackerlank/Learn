/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EWActType.as
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
 {
	import net.protocol.Message.ProtocolMessageProt199;
	/**
	 * 活动类型
	 */
	public final class EWActType
	{
		public static const eWActType_NONE:uint = 0; //无活动
		public static const eWActType_RANKPOINT:uint = 702; //战力排行榜
		public static const eWActType_LEVELACT:uint = 703; //全服等级奖励
		public static const eWActType_HORSEACT:uint = 704; //坐骑收集奖励
		public static const eWActType_DUNGON:uint = 705; //全服副本奖励
		public static const eWActType_FIGHTER:uint = 706; //全服散仙奖励
		public static const eWActType_FORMATION:uint = 707; //全服阵灵奖励
		public static const eWActType_TRUMP:uint = 708; //全服法宝奖励
		public static const eWActType_RANKLEVEL:uint = 709; //等级排行榜
		public static const eWActType_RANKPET:uint = 710; //阵灵排行榜
		public static const eWActType_RANKFIGHTER:uint = 711; //散仙排行榜
		public static const eWActType_RANKARENA:uint = 712; //斗剑排行榜
		public static const eWActType_RANKGUILD:uint = 713; //帮派排行榜
		public static const eWActType_RANKTRUMP:uint = 717; //法宝排行榜
		public static const eWActType_QQCOIN:uint = 715; //Q养成活动
		public static const eWActType_BEAUTYACT:uint = 716; //美女奖励
		public static const eWActType_POINT:uint = 718; //战力奖励
		public static const eWActType_OpenBuy:uint = 719; //开服购买礼包
		public static const eWActType_MAX:uint = 720; //活动最大值
		public static const end:uint = eWActType_MAX;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eWActType_NONE:
					return ProtocolMessageProt199.eWActType_NONE;
				case eWActType_RANKPOINT:
					return ProtocolMessageProt199.eWActType_RANKPOINT;
				case eWActType_LEVELACT:
					return ProtocolMessageProt199.eWActType_LEVELACT;
				case eWActType_HORSEACT:
					return ProtocolMessageProt199.eWActType_HORSEACT;
				case eWActType_DUNGON:
					return ProtocolMessageProt199.eWActType_DUNGON;
				case eWActType_FIGHTER:
					return ProtocolMessageProt199.eWActType_FIGHTER;
				case eWActType_FORMATION:
					return ProtocolMessageProt199.eWActType_FORMATION;
				case eWActType_TRUMP:
					return ProtocolMessageProt199.eWActType_TRUMP;
				case eWActType_RANKLEVEL:
					return ProtocolMessageProt199.eWActType_RANKLEVEL;
				case eWActType_RANKPET:
					return ProtocolMessageProt199.eWActType_RANKPET;
				case eWActType_RANKFIGHTER:
					return ProtocolMessageProt199.eWActType_RANKFIGHTER;
				case eWActType_RANKARENA:
					return ProtocolMessageProt199.eWActType_RANKARENA;
				case eWActType_RANKGUILD:
					return ProtocolMessageProt199.eWActType_RANKGUILD;
				case eWActType_RANKTRUMP:
					return ProtocolMessageProt199.eWActType_RANKTRUMP;
				case eWActType_QQCOIN:
					return ProtocolMessageProt199.eWActType_QQCOIN;
				case eWActType_BEAUTYACT:
					return ProtocolMessageProt199.eWActType_BEAUTYACT;
				case eWActType_POINT:
					return ProtocolMessageProt199.eWActType_POINT;
				case eWActType_OpenBuy:
					return ProtocolMessageProt199.eWActType_OpenBuy;
				case eWActType_MAX:
					return ProtocolMessageProt199.eWActType_MAX;
				default:
					return "Unknown Error";
			}
		}
	}
}
