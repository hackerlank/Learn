/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGBSpotState.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt76;
	/**
	 * 帮派据点状态
	 */
	public final class EGBSpotState
	{
		public static const eGBSpotStateNone:uint = 0; //无效状态
		public static const eGBSpotStateWin:uint = 1; //胜利
		public static const eGBSpotStateLose:uint = 2; //失败
		public static const eGBSpotStateTie:uint = 3; //平局
		public static const eGBSpotStateBattle:uint = 4; //战斗中
		public static const eGBSpotStateNobody:uint = 5; //无人参战
		public static const eGBSpotStateMax:uint = 6; //最大状态
		public static const end:uint = eGBSpotStateMax;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBSpotStateNone:
					return ProtocolMessageProt76.eGBSpotStateNone;
				case eGBSpotStateWin:
					return ProtocolMessageProt76.eGBSpotStateWin;
				case eGBSpotStateLose:
					return ProtocolMessageProt76.eGBSpotStateLose;
				case eGBSpotStateTie:
					return ProtocolMessageProt76.eGBSpotStateTie;
				case eGBSpotStateBattle:
					return ProtocolMessageProt76.eGBSpotStateBattle;
				case eGBSpotStateNobody:
					return ProtocolMessageProt76.eGBSpotStateNobody;
				case eGBSpotStateMax:
					return ProtocolMessageProt76.eGBSpotStateMax;
				default:
					return "Unknown Error";
			}
		}
	}
}
