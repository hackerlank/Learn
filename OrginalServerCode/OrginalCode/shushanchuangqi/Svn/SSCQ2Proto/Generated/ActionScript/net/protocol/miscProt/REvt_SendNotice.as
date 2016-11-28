/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SendNotice.as
//  Purpose:      协议:不好归类的小协议, 函数:宝箱下一波公告
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	import flash.events.Event;

	/**
	 * 函数SendNotice[宝箱下一波公告]的接收事件
	 */
	public final class REvt_SendNotice extends Event
	{
		public static const DATA_RECEIVE:String = "MiscProt_SendNotice";
		public static const DATA_ERROR:String = "MiscProt_SendNotice_Error";

		public var byRount:uint; //(无符号8位整数)剩余波数
		public var byMaxRount:uint; //(无符号8位整数)最大波数

		public function REvt_SendNotice(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SendNotice byRount={byRount} byMaxRount={byMaxRount}/>;
			return topXml;
		}
	}
}
