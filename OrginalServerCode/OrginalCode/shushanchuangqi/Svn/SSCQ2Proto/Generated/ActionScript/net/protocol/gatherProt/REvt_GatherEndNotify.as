/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GatherEndNotify.as
//  Purpose:      协议:采集协议, 函数:采集结束通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.gatherProt
{
	import flash.events.Event;

	/**
	 * 函数GatherEndNotify[采集结束通知]的接收事件
	 */
	public final class REvt_GatherEndNotify extends Event
	{
		public static const DATA_RECEIVE:String = "GatherProt_GatherEndNotify";
		public static const DATA_ERROR:String = "GatherProt_GatherEndNotify_Error";

		public var eResult:uint; //(枚举类型：EGatherResult)服务器返回结果

		public function REvt_GatherEndNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GatherEndNotify eResult={eResult}/>;
			return topXml;
		}
	}
}
