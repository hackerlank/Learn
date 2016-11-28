/************************************************************************
//  工具自动生成的Flash客户端协议代码(枚举类型)
//  File Name:    EBuyActionRet.as
//  Purpose:      不好归类的小协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
 {
	import net.protocol.Message.ProtocolMessageProt72;
	/**
	 * 购买体力错误码
	 */
	public final class EBuyActionRet
	{
		public static const eBuyActionRet_Sucess:uint = 0; //成功
		public static const eBuyActionRet_MaxAction:uint = 1; //体力已满
		public static const eBuyActionRet_MoneyLimit:uint = 2; //仙元不足
		public static const eBuyActionRet_CountLimit:uint = 3; //购买次数限制
		public static const eBuyActionRet_VIPCFGError:uint = 4; //vip配置出错
		public static const end:uint = eBuyActionRet_VIPCFGError;

		/////////////////////以下为辅助函数/////////////////////

		public static function getDescription(value:uint):String
		{
			switch(value)
			{
				case eBuyActionRet_Sucess:
					return ProtocolMessageProt72.eBuyActionRet_Sucess;
				case eBuyActionRet_MaxAction:
					return ProtocolMessageProt72.eBuyActionRet_MaxAction;
				case eBuyActionRet_MoneyLimit:
					return ProtocolMessageProt72.eBuyActionRet_MoneyLimit;
				case eBuyActionRet_CountLimit:
					return ProtocolMessageProt72.eBuyActionRet_CountLimit;
				case eBuyActionRet_VIPCFGError:
					return ProtocolMessageProt72.eBuyActionRet_VIPCFGError;
				default:
					return "Unknown Error";
			}
		}
	}
}
