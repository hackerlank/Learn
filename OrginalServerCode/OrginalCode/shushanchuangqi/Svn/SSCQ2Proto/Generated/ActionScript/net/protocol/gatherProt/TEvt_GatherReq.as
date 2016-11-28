/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GatherReq.as
//  Purpose:      协议:采集协议, 函数:采集请求
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gatherProt
{
	import flash.events.Event;

	/**
	 * 函数GatherReq[采集请求]的返回事件
	 */
	public final class TEvt_GatherReq extends Event
	{
		public static const DATA_RETURN:String = "GatherProt_GatherReq";
		public static const DATA_ERROR:String = "GatherProt_GatherReq_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var origParam:SOrigParam_GatherReq; //原来的参数
		public var retParam:SRetParam_GatherReq; //返回的参数

		public function TEvt_GatherReq(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GatherReq ret={ret}/>;
			if(origParam != null)
				topXml.appendChild(origParam.toXML("origParam"));
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
