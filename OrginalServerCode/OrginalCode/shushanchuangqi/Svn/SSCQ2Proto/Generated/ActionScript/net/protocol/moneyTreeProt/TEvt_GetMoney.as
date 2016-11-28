/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetMoney.as
//  Purpose:      协议:摇钱树协议, 函数:请求摇钱
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.moneyTreeProt
{
	import flash.events.Event;

	/**
	 * 函数GetMoney[请求摇钱]的返回事件
	 */
	public final class TEvt_GetMoney extends Event
	{
		public static const DATA_RETURN:String = "MoneyTreeProt_GetMoney";
		public static const DATA_ERROR:String = "MoneyTreeProt_GetMoney_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetMoney; //返回的参数

		public function TEvt_GetMoney(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetMoney ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
