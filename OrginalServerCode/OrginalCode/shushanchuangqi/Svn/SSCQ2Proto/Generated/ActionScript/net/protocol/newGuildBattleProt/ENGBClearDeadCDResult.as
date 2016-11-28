/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    ENGBClearDeadCDResult.as
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.newGuildBattleProt
 {
	import net.protocol.Message.ProtocolMessageProt68;
	/**
	 * 帮派战买活返回结果
	 */
	public final class ENGBClearDeadCDResult
	{
		public static const eNGBCDCDRSuccess:uint = 0; //买活成功
		public static const eNGBCDCDRFailed:uint = 1; //买活失败
		public static const eNGBCDCDRIsAlive:uint = 2; //已经复活
		public static const eNGBCDCDRWrongTime:uint = 3; //不在正确的时间段内
		public static const end:uint = eNGBCDCDRWrongTime;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eNGBCDCDRSuccess:
					return ProtocolMessageProt68.eNGBCDCDRSuccess;
				case eNGBCDCDRFailed:
					return ProtocolMessageProt68.eNGBCDCDRFailed;
				case eNGBCDCDRIsAlive:
					return ProtocolMessageProt68.eNGBCDCDRIsAlive;
				case eNGBCDCDRWrongTime:
					return ProtocolMessageProt68.eNGBCDCDRWrongTime;
				default:
					return "Unknown Error";
			}
		}
	}
}
