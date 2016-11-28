/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BeginNotify.as
//  Purpose:      协议:中午挂机活动, 函数:挂机活动开始
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.langHuanBlessProt
{
	import flash.events.Event;

	/**
	 * 函数BeginNotify[挂机活动开始]的接收事件
	 */
	public final class REvt_BeginNotify extends Event
	{
		public static const DATA_RECEIVE:String = "LangHuanBlessProt_BeginNotify";
		public static const DATA_ERROR:String = "LangHuanBlessProt_BeginNotify_Error";

		public var dwBeginTime:uint; //(无符号32位整数)开始时间

		public function REvt_BeginNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BeginNotify dwBeginTime={dwBeginTime}/>;
			return topXml;
		}
	}
}
