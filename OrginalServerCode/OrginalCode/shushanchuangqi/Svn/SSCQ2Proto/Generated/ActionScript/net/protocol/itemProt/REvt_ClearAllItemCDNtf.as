/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ClearAllItemCDNtf.as
//  Purpose:      协议:道具相关协议, 函数:清除道具使用冷却CD
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数ClearAllItemCDNtf[清除道具使用冷却CD]的接收事件
	 */
	public final class REvt_ClearAllItemCDNtf extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_ClearAllItemCDNtf";
		public static const DATA_ERROR:String = "ItemProt_ClearAllItemCDNtf_Error";


		public function REvt_ClearAllItemCDNtf(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ClearAllItemCDNtf/>;
			return topXml;
		}
	}
}
