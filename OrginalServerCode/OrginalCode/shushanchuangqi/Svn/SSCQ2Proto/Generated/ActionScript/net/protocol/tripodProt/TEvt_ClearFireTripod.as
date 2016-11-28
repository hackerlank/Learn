/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ClearFireTripod.as
//  Purpose:      协议:九疑鼎相关协议, 函数:清除九疑鼎祈火记录
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.tripodProt
{
	import flash.events.Event;

	/**
	 * 函数ClearFireTripod[清除九疑鼎祈火记录]的返回事件
	 */
	public final class TEvt_ClearFireTripod extends Event
	{
		public static const DATA_RETURN:String = "TripodProt_ClearFireTripod";
		public static const DATA_ERROR:String = "TripodProt_ClearFireTripod_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ClearFireTripod; //返回的参数

		public function TEvt_ClearFireTripod(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ClearFireTripod ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
