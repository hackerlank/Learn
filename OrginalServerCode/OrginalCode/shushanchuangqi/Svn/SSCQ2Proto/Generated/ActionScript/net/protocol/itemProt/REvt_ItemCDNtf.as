/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ItemCDNtf.as
//  Purpose:      协议:道具相关协议, 函数:道具CD时间通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数ItemCDNtf[道具CD时间通知]的接收事件
	 */
	public final class REvt_ItemCDNtf extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_ItemCDNtf";
		public static const DATA_ERROR:String = "ItemProt_ItemCDNtf_Error";

		public var byType:uint; //(无符号8位整数)冷却类型0:ItemID 1:GroupID
		public var rItemCD:SItemColdTime; //道具CD

		public function REvt_ItemCDNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ItemCDNtf byType={byType}/>;
			if(rItemCD != null)
				topXml.appendChild(rItemCD.toXML("rItemCD"));
			return topXml;
		}
	}
}
