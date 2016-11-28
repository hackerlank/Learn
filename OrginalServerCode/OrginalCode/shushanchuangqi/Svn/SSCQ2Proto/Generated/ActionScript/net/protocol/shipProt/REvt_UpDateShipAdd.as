/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpDateShipAdd.as
//  Purpose:      协议:元江金船协议, 函数:发送船只增加消息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import flash.events.Event;

	/**
	 * 函数UpDateShipAdd[发送船只增加消息]的接收事件
	 */
	public final class REvt_UpDateShipAdd extends Event
	{
		public static const DATA_RECEIVE:String = "ShipProt_UpDateShipAdd";
		public static const DATA_ERROR:String = "ShipProt_UpDateShipAdd_Error";

		public var stShipInfo:PlayerShipForList; //船只信息

		public function REvt_UpDateShipAdd(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpDateShipAdd/>;
			if(stShipInfo != null)
				topXml.appendChild(stShipInfo.toXML("stShipInfo"));
			return topXml;
		}
	}
}
