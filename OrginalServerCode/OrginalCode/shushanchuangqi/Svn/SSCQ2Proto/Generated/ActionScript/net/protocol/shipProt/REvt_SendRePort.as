/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SendRePort.as
//  Purpose:      协议:元江金船协议, 函数:发送玩家战报信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shipProt
{
	import flash.events.Event;

	/**
	 * 函数SendRePort[发送玩家战报信息]的接收事件
	 */
	public final class REvt_SendRePort extends Event
	{
		public static const DATA_RECEIVE:String = "ShipProt_SendRePort";
		public static const DATA_ERROR:String = "ShipProt_SendRePort_Error";

		public var vecReportInfo:Vector.<ShipReportForClient>; //玩家战报信息

		public function REvt_SendRePort(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SendRePort/>;
			if(vecReportInfo != null)
			{
				var vecReportInfoXml:XML = <Vec_ShipReportForClient _name_="vecReportInfo"/>;
				for each(var s1:ShipReportForClient in vecReportInfo)
					vecReportInfoXml.appendChild(s1.toXML());
				topXml.appendChild(vecReportInfoXml);
			}
			return topXml;
		}
	}
}
