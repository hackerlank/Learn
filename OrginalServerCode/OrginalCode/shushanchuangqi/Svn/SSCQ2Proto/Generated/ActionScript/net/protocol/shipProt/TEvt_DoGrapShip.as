/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_DoGrapShip.as
//  Purpose:      协议:元江金船协议, 函数:返抢
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import flash.events.Event;

	/**
	 * 函数DoGrapShip[返抢]的返回事件
	 */
	public final class TEvt_DoGrapShip extends Event
	{
		public static const DATA_RETURN:String = "ShipProt_DoGrapShip";
		public static const DATA_ERROR:String = "ShipProt_DoGrapShip_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_DoGrapShip; //返回的参数

		public function TEvt_DoGrapShip(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_DoGrapShip ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}