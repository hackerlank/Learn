/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ESyncLevelResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 散仙等级同步
	 */
	public final class ESyncLevelResult
	{
		public static const eSyncLevelSucc:uint = 0; //成功
		public static const eSyncLevelFailed:uint = 1; //失败
		public static const eSyncLevelAlready:uint = 2; //已是最高等级
		public static const eSyncLevelMoney:uint = 3; //同步等级所需银币不足
		public static const eSyncLevelMoneyMore:uint = 4; //同步等级成功但所需银币不足无法继续升级
		public static const end:uint = eSyncLevelMoneyMore;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eSyncLevelSucc:
					return ProtocolMessageProt20.eSyncLevelSucc;
				case eSyncLevelFailed:
					return ProtocolMessageProt20.eSyncLevelFailed;
				case eSyncLevelAlready:
					return ProtocolMessageProt20.eSyncLevelAlready;
				case eSyncLevelMoney:
					return ProtocolMessageProt20.eSyncLevelMoney;
				case eSyncLevelMoneyMore:
					return ProtocolMessageProt20.eSyncLevelMoneyMore;
				default:
					return "Unknown Error";
			}
		}
	}
}
