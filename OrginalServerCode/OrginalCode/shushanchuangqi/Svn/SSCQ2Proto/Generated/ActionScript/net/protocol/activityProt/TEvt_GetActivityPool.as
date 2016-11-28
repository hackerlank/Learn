/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetActivityPool.as
//  Purpose:      协议:活力任务协议, 函数:请求获得奖池
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityProt
{
	import flash.events.Event;

	/**
	 * 函数GetActivityPool[请求获得奖池]的返回事件
	 */
	public final class TEvt_GetActivityPool extends Event
	{
		public static const DATA_RETURN:String = "ActivityProt_GetActivityPool";
		public static const DATA_ERROR:String = "ActivityProt_GetActivityPool_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetActivityPool; //返回的参数

		public function TEvt_GetActivityPool(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetActivityPool ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
