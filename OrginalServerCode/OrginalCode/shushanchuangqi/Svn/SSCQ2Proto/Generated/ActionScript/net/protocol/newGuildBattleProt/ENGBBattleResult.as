/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBBattleResult.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派战战斗相关结果
	 */
	public final class ENGBBattleResult
	{
		public static const eNGBBattleSuccess:uint = 0; //战斗成功
		public static const eNGBBattleFailed:uint = 1; //战斗失败
		public static const end:uint = eNGBBattleFailed;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBBattleSuccess:
					return ProtocolMessageProt68.eNGBBattleSuccess;
				case eNGBBattleFailed:
					return ProtocolMessageProt68.eNGBBattleFailed;
				default:
					return "Unknown Error";
			}
		}
	}
}
