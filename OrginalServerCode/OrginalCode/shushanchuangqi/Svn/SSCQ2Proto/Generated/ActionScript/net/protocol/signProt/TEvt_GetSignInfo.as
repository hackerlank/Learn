/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetSignInfo.as
//  Purpose:      协议:签到协议, 函数:请求签到信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.signProt
{
	import flash.events.Event;

	/**
	 * 函数GetSignInfo[请求签到信息]的返回事件
	 */
	public final class TEvt_GetSignInfo extends Event
	{
		public static const DATA_RETURN:String = "SignProt_GetSignInfo";
		public static const DATA_ERROR:String = "SignProt_GetSignInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetSignInfo; //返回的参数

		public function TEvt_GetSignInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetSignInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
