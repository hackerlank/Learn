/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EDujieResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 散仙渡劫
	 */
	public final class EDujieResult
	{
		public static const eDujieSucc:uint = 0; //成功
		public static const eDujieFailed:uint = 1; //失败
		public static const eDujieItemErr:uint = 2; //渡劫符不足
		public static const eDujieLevelMaxErr:uint = 3; //渡劫等级已是最高级
		public static const end:uint = eDujieLevelMaxErr;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eDujieSucc:
					return ProtocolMessageProt20.eDujieSucc;
				case eDujieFailed:
					return ProtocolMessageProt20.eDujieFailed;
				case eDujieItemErr:
					return ProtocolMessageProt20.eDujieItemErr;
				case eDujieLevelMaxErr:
					return ProtocolMessageProt20.eDujieLevelMaxErr;
				default:
					return "Unknown Error";
			}
		}
	}
}
