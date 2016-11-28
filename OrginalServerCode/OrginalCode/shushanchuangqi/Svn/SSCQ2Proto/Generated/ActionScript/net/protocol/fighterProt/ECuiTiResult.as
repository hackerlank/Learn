/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ECuiTiResult.as
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.fighterProt
 {
	import net.protocol.Message.ProtocolMessageProt20;
	/**
	 * 淬体
	 */
	public final class ECuiTiResult
	{
		public static const eCuiTiResultSucc:uint = 0; //成功
		public static const eCuiTiResultFailed:uint = 1; //失败
		public static const eCuiTiResultSilverErr:uint = 2; //银币不足
		public static const eCuiTiResultLvlMaxErr:uint = 3; //已达最高等级
		public static const eCuiTiResultPlayerLvlErr:uint = 4; //已达将最高等级
		public static const eCuiTiResultUnlock:uint = 5; //未解锁
		public static const end:uint = eCuiTiResultUnlock;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eCuiTiResultSucc:
					return ProtocolMessageProt20.eCuiTiResultSucc;
				case eCuiTiResultFailed:
					return ProtocolMessageProt20.eCuiTiResultFailed;
				case eCuiTiResultSilverErr:
					return ProtocolMessageProt20.eCuiTiResultSilverErr;
				case eCuiTiResultLvlMaxErr:
					return ProtocolMessageProt20.eCuiTiResultLvlMaxErr;
				case eCuiTiResultPlayerLvlErr:
					return ProtocolMessageProt20.eCuiTiResultPlayerLvlErr;
				case eCuiTiResultUnlock:
					return ProtocolMessageProt20.eCuiTiResultUnlock;
				default:
					return "Unknown Error";
			}
		}
	}
}
