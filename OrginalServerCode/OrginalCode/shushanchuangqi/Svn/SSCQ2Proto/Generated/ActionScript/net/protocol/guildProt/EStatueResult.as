/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EStatueResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 帮派神像操作返回结果
	 */
	public final class EStatueResult
	{
		public static const eGSResultSuccess:uint = 0; //操作成功
		public static const eGSResultFailed:uint = 1; //操作失败
		public static const eGSResultNoGuild:uint = 2; //不存在帮派
		public static const eGSResultLackofSilver:uint = 3; //银币不足
		public static const eGSResultLackofGold:uint = 4; //仙石不足
		public static const eGSResultLevelMax:uint = 5; //已经是最大等级
		public static const eGSResultNoAuthority:uint = 6; //权限不足
		public static const eGSResultBuildingLevelTooLow:uint = 7; //帮派建筑等级过低
		public static const eGSResultWorshiped:uint = 8; //本日已经供奉过
		public static const eGSResultTooFast:uint = 9; //操作过快
		public static const eGSResultNotToday:uint = 10; //进入当日无法操作
		public static const end:uint = eGSResultNotToday;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGSResultSuccess:
					return ProtocolMessageProt16.eGSResultSuccess;
				case eGSResultFailed:
					return ProtocolMessageProt16.eGSResultFailed;
				case eGSResultNoGuild:
					return ProtocolMessageProt16.eGSResultNoGuild;
				case eGSResultLackofSilver:
					return ProtocolMessageProt16.eGSResultLackofSilver;
				case eGSResultLackofGold:
					return ProtocolMessageProt16.eGSResultLackofGold;
				case eGSResultLevelMax:
					return ProtocolMessageProt16.eGSResultLevelMax;
				case eGSResultNoAuthority:
					return ProtocolMessageProt16.eGSResultNoAuthority;
				case eGSResultBuildingLevelTooLow:
					return ProtocolMessageProt16.eGSResultBuildingLevelTooLow;
				case eGSResultWorshiped:
					return ProtocolMessageProt16.eGSResultWorshiped;
				case eGSResultTooFast:
					return ProtocolMessageProt16.eGSResultTooFast;
				case eGSResultNotToday:
					return ProtocolMessageProt16.eGSResultNotToday;
				default:
					return "Unknown Error";
			}
		}
	}
}
