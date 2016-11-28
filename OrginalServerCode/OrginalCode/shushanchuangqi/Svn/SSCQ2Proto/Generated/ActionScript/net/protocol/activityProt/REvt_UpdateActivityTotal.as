/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateActivityTotal.as
//  Purpose:      协议:活力任务协议, 函数:活力总值更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateActivityTotal[活力总值更新]的接收事件
	 */
	public final class REvt_UpdateActivityTotal extends Event
	{
		public static const DATA_RECEIVE:String = "ActivityProt_UpdateActivityTotal";
		public static const DATA_ERROR:String = "ActivityProt_UpdateActivityTotal_Error";

		public var dwTotolActivity:uint; //(无符号32位整数)活力总值

		public function REvt_UpdateActivityTotal(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateActivityTotal dwTotolActivity={dwTotolActivity}/>;
			return topXml;
		}
	}
}
