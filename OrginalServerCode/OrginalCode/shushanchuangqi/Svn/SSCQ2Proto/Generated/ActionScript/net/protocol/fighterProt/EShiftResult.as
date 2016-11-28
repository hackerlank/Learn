/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EShiftResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 转移
	 */
	public final class EShiftResult
	{
		public static const eShiftSucc:uint = 0; //成功
		public static const eShiftFailed:uint = 1; //失败
		public static const eShiftGoldErr:uint = 2; //仙石不足
		public static const end:uint = eShiftGoldErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eShiftSucc:
					return ProtocolMessageProt20.eShiftSucc;
				case eShiftFailed:
					return ProtocolMessageProt20.eShiftFailed;
				case eShiftGoldErr:
					return ProtocolMessageProt20.eShiftGoldErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
