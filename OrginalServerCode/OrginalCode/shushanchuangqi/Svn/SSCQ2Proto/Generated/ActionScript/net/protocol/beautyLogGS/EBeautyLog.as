/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBeautyLog.as
//  Purpose:      美女log
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beautyLogGS
 {
	import net.protocol.Message.ProtocolMessageProt133;
	/**
	 * 美女log
	 */
	public final class EBeautyLog
	{
		public static const eBeautyLog_Sucess:uint = 0; //成功
		public static const eBeautyLog_Error:uint = 1; //失败
		public static const end:uint = eBeautyLog_Error;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBeautyLog_Sucess:
					return ProtocolMessageProt133.eBeautyLog_Sucess;
				case eBeautyLog_Error:
					return ProtocolMessageProt133.eBeautyLog_Error;
				default:
					return "Unknown Error";
			}
		}
	}
}
