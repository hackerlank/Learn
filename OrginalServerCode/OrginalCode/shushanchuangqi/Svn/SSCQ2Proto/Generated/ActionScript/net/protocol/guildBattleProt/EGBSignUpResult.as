/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGBSignUpResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt76;
	/**
	 * 帮派战报名结果
	 */
	public final class EGBSignUpResult
	{
		public static const eGBSignUpSuccess:uint = 0; //报名成功
		public static const eGBSignUpFailed:uint = 1; //报名失败
		public static const eGBSignUpNotInGuild:uint = 2; //报名时不存在帮派
		public static const eGBSignUpRepeat:uint = 3; //报名重复
		public static const eGBSignUpWrongTime:uint = 4; //不在报名时段
		public static const eGBSignUpSpotFull:uint = 5; //报名据点已满
		public static const eGBSignUpEscape:uint = 6; //由于您刚刚逃离了帮派战，暂时无法报名
		public static const end:uint = eGBSignUpEscape;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBSignUpSuccess:
					return ProtocolMessageProt76.eGBSignUpSuccess;
				case eGBSignUpFailed:
					return ProtocolMessageProt76.eGBSignUpFailed;
				case eGBSignUpNotInGuild:
					return ProtocolMessageProt76.eGBSignUpNotInGuild;
				case eGBSignUpRepeat:
					return ProtocolMessageProt76.eGBSignUpRepeat;
				case eGBSignUpWrongTime:
					return ProtocolMessageProt76.eGBSignUpWrongTime;
				case eGBSignUpSpotFull:
					return ProtocolMessageProt76.eGBSignUpSpotFull;
				case eGBSignUpEscape:
					return ProtocolMessageProt76.eGBSignUpEscape;
				default:
					return "Unknown Error";
			}
		}
	}
}
