/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpDateShipReportAdd.as
//  Purpose:      协议:元江金船协议, 函数:发送记录增加消息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import flash.events.Event;

	/**
	 * 函数UpDateShipReportAdd[发送记录增加消息]的接收事件
	 */
	public final class REvt_UpDateShipReportAdd extends Event
	{
		public static const DATA_RECEIVE:String = "ShipProt_UpDateShipReportAdd";
		public static const DATA_ERROR:String = "ShipProt_UpDateShipReportAdd_Error";

		public var stReport:ShipReportForClient; //记录信息

		public function REvt_UpDateShipReportAdd(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpDateShipReportAdd/>;
			if(stReport != null)
				topXml.appendChild(stReport.toXML("stReport"));
			return topXml;
		}
	}
}
