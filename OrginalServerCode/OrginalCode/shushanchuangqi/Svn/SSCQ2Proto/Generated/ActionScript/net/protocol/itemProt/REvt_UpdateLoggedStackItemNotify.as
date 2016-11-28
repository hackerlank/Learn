/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_UpdateLoggedStackItemNotify.as
//  Purpose:      协议:道具相关协议, 函数:更新记录的堆叠道具通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数UpdateLoggedStackItemNotify[更新记录的堆叠道具通知]的接收事件
	 */
	public final class REvt_UpdateLoggedStackItemNotify extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_UpdateLoggedStackItemNotify";
		public static const DATA_ERROR:String = "ItemProt_UpdateLoggedStackItemNotify_Error";

		public var wItemID:uint; //(无符号16位整数)ID
		public var byQuality:uint; //(无符号8位整数)品质
		public var dwCount:uint; //(无符号32位整数)数目

		public function REvt_UpdateLoggedStackItemNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_UpdateLoggedStackItemNotify wItemID={wItemID} byQuality={byQuality} dwCount={dwCount}/>;
			return topXml;
		}
	}
}
