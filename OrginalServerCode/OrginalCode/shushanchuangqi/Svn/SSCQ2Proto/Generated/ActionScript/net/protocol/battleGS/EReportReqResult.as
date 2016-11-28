/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EReportReqResult.as
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.battleGS
 {
	import net.protocol.Message.ProtocolMessageProt21;
	/**
	 * 战报请求结果
	 */
	public final class EReportReqResult
	{
		public static const EReportReq_Suc:uint = 1; //成功
		public static const EReportReq_NonExistent:uint = 2; //请求的战报不存在
		public static const EReportReq_Other:uint = 4; //未知错误
		public static const end:uint = EReportReq_Other;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case EReportReq_Suc:
					return ProtocolMessageProt21.EReportReq_Suc;
				case EReportReq_NonExistent:
					return ProtocolMessageProt21.EReportReq_NonExistent;
				case EReportReq_Other:
					return ProtocolMessageProt21.EReportReq_Other;
				default:
					return "Unknown Error";
			}
		}
	}
}
