/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EVIPResult.as
//  Purpose:      VIP特权相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.vIPProt
 {
	import net.protocol.Message.ProtocolMessageProt65;
	/**
	 * VIP特权操作结果
	 */
	public final class EVIPResult
	{
		public static const eVIP_Succeed:uint = 0; //成功
		public static const eVIP_LackMoney:uint = 1; //金钱不够
		public static const eVIP_HasGetAward:uint = 2; //已领取过礼包
		public static const eVIP_Expired:uint = 3; //VIP特权已过期
		public static const eVIP_UnFriend:uint = 4; //对方不是你的好友并且不是你的帮派成员
		public static const eVIP_LevelErr:uint = 5; //VIP特权等级不足
		public static const eVIP_OtherErr:uint = 6; //其他错误
		public static const end:uint = eVIP_OtherErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eVIP_Succeed:
					return ProtocolMessageProt65.eVIP_Succeed;
				case eVIP_LackMoney:
					return ProtocolMessageProt65.eVIP_LackMoney;
				case eVIP_HasGetAward:
					return ProtocolMessageProt65.eVIP_HasGetAward;
				case eVIP_Expired:
					return ProtocolMessageProt65.eVIP_Expired;
				case eVIP_UnFriend:
					return ProtocolMessageProt65.eVIP_UnFriend;
				case eVIP_LevelErr:
					return ProtocolMessageProt65.eVIP_LevelErr;
				case eVIP_OtherErr:
					return ProtocolMessageProt65.eVIP_OtherErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
