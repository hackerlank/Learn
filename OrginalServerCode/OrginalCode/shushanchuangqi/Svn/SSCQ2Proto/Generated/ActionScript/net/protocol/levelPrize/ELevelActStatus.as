/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ELevelActStatus.as
//  Purpose:      等级奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.levelPrize
 {
	import net.protocol.Message.ProtocolMessageProt121;
	/**
	 * 奖励状态信息
	 */
	public final class ELevelActStatus
	{
		public static const eLevleActStatus_Init:uint = 0; //未完成
		public static const eLevleActStatus_Finish:uint = 1; //完成
		public static const eLevleActStatus_GetPrize:uint = 2; //已领取奖励
		public static const eLevleActStatus_FullPack:uint = 3; //背包满
		public static const eLevleActStatus_Success:uint = 4; //操作成功
		public static const eLevleActStatus_Error:uint = 5; //操作失败
		public static const end:uint = eLevleActStatus_Error;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eLevleActStatus_Init:
					return ProtocolMessageProt121.eLevleActStatus_Init;
				case eLevleActStatus_Finish:
					return ProtocolMessageProt121.eLevleActStatus_Finish;
				case eLevleActStatus_GetPrize:
					return ProtocolMessageProt121.eLevleActStatus_GetPrize;
				case eLevleActStatus_FullPack:
					return ProtocolMessageProt121.eLevleActStatus_FullPack;
				case eLevleActStatus_Success:
					return ProtocolMessageProt121.eLevleActStatus_Success;
				case eLevleActStatus_Error:
					return ProtocolMessageProt121.eLevleActStatus_Error;
				default:
					return "Unknown Error";
			}
		}
	}
}
