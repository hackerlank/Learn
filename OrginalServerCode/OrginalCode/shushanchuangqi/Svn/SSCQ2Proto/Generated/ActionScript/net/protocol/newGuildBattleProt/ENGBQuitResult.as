/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBQuitResult.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派战退出结果
	 */
	public final class ENGBQuitResult
	{
		public static const eNGBQuitSuccess:uint = 0; //退出成功
		public static const eNGBQuitFailed:uint = 1; //退出失败
		public static const end:uint = eNGBQuitFailed;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBQuitSuccess:
					return ProtocolMessageProt68.eNGBQuitSuccess;
				case eNGBQuitFailed:
					return ProtocolMessageProt68.eNGBQuitFailed;
				default:
					return "Unknown Error";
			}
		}
	}
}
