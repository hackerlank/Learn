/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ActChangeNotify.as
//  Purpose:      协议:活动, 函数:活动状态改变通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.dayActProt
{
	import flash.events.Event;

	/**
	 * 函数ActChangeNotify[活动状态改变通知]的接收事件
	 */
	public final class REvt_ActChangeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "DayActProt_ActChangeNotify";
		public static const DATA_ERROR:String = "DayActProt_ActChangeNotify_Error";

		public var dwActType:uint; //(无符号32位整数)活动id
		public var dwActStatus:uint; //(无符号32位整数)活动状态

		public function REvt_ActChangeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ActChangeNotify dwActType={dwActType} dwActStatus={dwActStatus}/>;
			return topXml;
		}
	}
}
