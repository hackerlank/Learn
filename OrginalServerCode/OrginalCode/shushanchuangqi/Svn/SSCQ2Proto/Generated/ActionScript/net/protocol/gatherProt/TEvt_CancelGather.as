/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_CancelGather.as
//  Purpose:      协议:采集协议, 函数:取消采集
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gatherProt
{
	import flash.events.Event;

	/**
	 * 函数CancelGather[取消采集]的返回事件
	 */
	public final class TEvt_CancelGather extends Event
	{
		public static const DATA_RETURN:String = "GatherProt_CancelGather";
		public static const DATA_ERROR:String = "GatherProt_CancelGather_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_CancelGather; //返回的参数

		public function TEvt_CancelGather(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_CancelGather ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
