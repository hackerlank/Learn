/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetCurBuyInfo.as
//  Purpose:      协议:注册七天目标协议, 函数:请求当天购买信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.registerSevenDaysProt
{
	import flash.events.Event;

	/**
	 * 函数GetCurBuyInfo[请求当天购买信息]的返回事件
	 */
	public final class TEvt_GetCurBuyInfo extends Event
	{
		public static const DATA_RETURN:String = "RegisterSevenDaysProt_GetCurBuyInfo";
		public static const DATA_ERROR:String = "RegisterSevenDaysProt_GetCurBuyInfo_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetCurBuyInfo; //返回的参数

		public function TEvt_GetCurBuyInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetCurBuyInfo ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
