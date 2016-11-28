/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMiscOptRes.as
//  Purpose:      不好归类的小协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
 {
	import net.protocol.Message.ProtocolMessageProt72;
	/**
	 * 操作结果
	 */
	public final class EMiscOptRes
	{
		public static const eMiscOptRes_Sucess:uint = 0; //成功
		public static const eMiscOptRes_Error:uint = 1; //失败
		public static const end:uint = eMiscOptRes_Error;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eMiscOptRes_Sucess:
					return ProtocolMessageProt72.eMiscOptRes_Sucess;
				case eMiscOptRes_Error:
					return ProtocolMessageProt72.eMiscOptRes_Error;
				default:
					return "Unknown Error";
			}
		}
	}
}
