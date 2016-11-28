/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EMailErrorResult.as
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mailProt
 {
	import net.protocol.Message.ProtocolMessageProt19;
	/**
	 * 邮件状态
	 */
	public final class EMailErrorResult
	{
		public static const EMail_SendOk:uint = 1; //发送成功
		public static const EMail_SendFail:uint = 2; //发送失败
		public static const EMail_DeleteOk:uint = 3; //删除成功
		public static const EMail_DeleteFail:uint = 4; //删除失败
		public static const EMail_OverMaxCount:uint = 5; //超过最大上限
		public static const end:uint = EMail_OverMaxCount;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EMail_SendOk:
					return ProtocolMessageProt19.EMail_SendOk;
				case EMail_SendFail:
					return ProtocolMessageProt19.EMail_SendFail;
				case EMail_DeleteOk:
					return ProtocolMessageProt19.EMail_DeleteOk;
				case EMail_DeleteFail:
					return ProtocolMessageProt19.EMail_DeleteFail;
				case EMail_OverMaxCount:
					return ProtocolMessageProt19.EMail_OverMaxCount;
				default:
					return "Unknown Error";
			}
		}
	}
}
