/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECombinationResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 散仙组合返回
	 */
	public final class ECombinationResult
	{
		public static const eCombinationSucc:uint = 0; //成功
		public static const eCombinationFailed:uint = 1; //失败
		public static const eCombinationMaxLevel:uint = 2; //散仙组合已达最高等级
		public static const eCombinationHaved:uint = 3; //该散仙组合已激活
		public static const eCombinationNotHaved:uint = 4; //该散仙组合未激活
		public static const eCombinationFighterErr:uint = 5; //散仙未招募满
		public static const eCombinationItemErr:uint = 6; //道具不足
		public static const eCombinationMainLevelErr:uint = 7; //玩家主将等级不足
		public static const end:uint = eCombinationMainLevelErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eCombinationSucc:
					return ProtocolMessageProt20.eCombinationSucc;
				case eCombinationFailed:
					return ProtocolMessageProt20.eCombinationFailed;
				case eCombinationMaxLevel:
					return ProtocolMessageProt20.eCombinationMaxLevel;
				case eCombinationHaved:
					return ProtocolMessageProt20.eCombinationHaved;
				case eCombinationNotHaved:
					return ProtocolMessageProt20.eCombinationNotHaved;
				case eCombinationFighterErr:
					return ProtocolMessageProt20.eCombinationFighterErr;
				case eCombinationItemErr:
					return ProtocolMessageProt20.eCombinationItemErr;
				case eCombinationMainLevelErr:
					return ProtocolMessageProt20.eCombinationMainLevelErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
