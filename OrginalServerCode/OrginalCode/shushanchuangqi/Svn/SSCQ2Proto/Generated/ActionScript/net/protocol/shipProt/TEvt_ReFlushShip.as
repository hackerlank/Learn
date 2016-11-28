/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ReFlushShip.as
//  Purpose:      协议:元江金船协议, 函数:刷新船只
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import flash.events.Event;

	/**
	 * 函数ReFlushShip[刷新船只]的返回事件
	 */
	public final class TEvt_ReFlushShip extends Event
	{
		public static const DATA_RETURN:String = "ShipProt_ReFlushShip";
		public static const DATA_ERROR:String = "ShipProt_ReFlushShip_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ReFlushShip; //返回的参数

		public function TEvt_ReFlushShip(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ReFlushShip ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
