/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EGEMOptResult.as
//  Purpose:      守卫峨眉协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.guardEMeiProt
 {
	import net.protocol.Message.ProtocolMessageProt86;
	/**
	 * 操作结果
	 */
	public final class EGEMOptResult
	{
		public static const eGEMOptResultFailed:int = 0; //失败
		public static const eGEMOptResultSucc:int = 1; //成功
		public static const end:int = eGEMOptResultSucc;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:int):String
		{
			switch(value)
			{
				case eGEMOptResultFailed:
					return ProtocolMessageProt86.eGEMOptResultFailed;
				case eGEMOptResultSucc:
					return ProtocolMessageProt86.eGEMOptResultSucc;
				default:
					return "Unknown Error";
			}
		}
	}
}
