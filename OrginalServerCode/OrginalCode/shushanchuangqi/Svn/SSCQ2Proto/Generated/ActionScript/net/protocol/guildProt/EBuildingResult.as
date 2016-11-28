/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBuildingResult.as
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guildProt
 {
	import net.protocol.Message.ProtocolMessageProt16;
	/**
	 * 帮派建筑操作返回结果
	 */
	public final class EBuildingResult
	{
		public static const eGBuildingResultSuccess:uint = 0; //操作成功
		public static const eGBuildingResultFailed:uint = 1; //操作失败
		public static const eGBuildingResultNoGuild:uint = 2; //不存在帮派
		public static const eGBuildingResultLackofSilver:uint = 3; //银币不足
		public static const eGBuildingResultLevelMax:uint = 4; //已经是最大等级
		public static const eGBuildingResultNoAuthority:uint = 5; //权限不足
		public static const eGBuildingResultGuildLevelTooLow:uint = 6; //帮派等级过低
		public static const eGBuildingResultOracleLevelTooLow:uint = 7; //神谕塔等级过低
		public static const end:uint = eGBuildingResultOracleLevelTooLow;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eGBuildingResultSuccess:
					return ProtocolMessageProt16.eGBuildingResultSuccess;
				case eGBuildingResultFailed:
					return ProtocolMessageProt16.eGBuildingResultFailed;
				case eGBuildingResultNoGuild:
					return ProtocolMessageProt16.eGBuildingResultNoGuild;
				case eGBuildingResultLackofSilver:
					return ProtocolMessageProt16.eGBuildingResultLackofSilver;
				case eGBuildingResultLevelMax:
					return ProtocolMessageProt16.eGBuildingResultLevelMax;
				case eGBuildingResultNoAuthority:
					return ProtocolMessageProt16.eGBuildingResultNoAuthority;
				case eGBuildingResultGuildLevelTooLow:
					return ProtocolMessageProt16.eGBuildingResultGuildLevelTooLow;
				case eGBuildingResultOracleLevelTooLow:
					return ProtocolMessageProt16.eGBuildingResultOracleLevelTooLow;
				default:
					return "Unknown Error";
			}
		}
	}
}
