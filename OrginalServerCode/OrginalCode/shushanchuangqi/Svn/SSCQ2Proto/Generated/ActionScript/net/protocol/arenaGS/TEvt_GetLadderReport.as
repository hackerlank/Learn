/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetLadderReport.as
//  Purpose:      协议:竞技场协议, 函数:清求战报
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.arenaGS
{
	import flash.events.Event;

	/**
	 * 函数GetLadderReport[清求战报]的返回事件
	 */
	public final class TEvt_GetLadderReport extends Event
	{
		public static const DATA_RETURN:String = "ArenaGS_GetLadderReport";
		public static const DATA_ERROR:String = "ArenaGS_GetLadderReport_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetLadderReport; //返回的参数

		public function TEvt_GetLadderReport(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetLadderReport ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
