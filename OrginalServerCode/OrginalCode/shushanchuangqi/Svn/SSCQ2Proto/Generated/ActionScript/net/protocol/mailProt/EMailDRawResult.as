/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMailDRawResult.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
 {
	import net.protocol.Message.ProtocolMessageProt19;
	/**
	 * 附件提取结果
	 */
	public final class EMailDRawResult
	{
		public static const DRAW_SUC:uint = 0; //提取成功
		public static const PACK_FULL:uint = 1; //包裹满
		public static const end:uint = PACK_FULL;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case DRAW_SUC:
					return ProtocolMessageProt19.DRAW_SUC;
				case PACK_FULL:
					return ProtocolMessageProt19.PACK_FULL;
				default:
					return "Unknown Error";
			}
		}
	}
}
