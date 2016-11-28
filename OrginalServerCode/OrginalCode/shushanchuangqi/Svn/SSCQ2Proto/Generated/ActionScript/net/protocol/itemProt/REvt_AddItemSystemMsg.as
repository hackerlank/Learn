/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AddItemSystemMsg.as
//  Purpose:      协议:道具相关协议, 函数:角色获得道具提示
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数AddItemSystemMsg[角色获得道具提示]的接收事件
	 */
	public final class REvt_AddItemSystemMsg extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_AddItemSystemMsg";
		public static const DATA_ERROR:String = "ItemProt_AddItemSystemMsg_Error";

		public var vecAddItemMsg:Vector.<SAddItemMsg>; //道具获得提示

		public function REvt_AddItemSystemMsg(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AddItemSystemMsg/>;
			if(vecAddItemMsg != null)
			{
				var vecAddItemMsgXml:XML = <Vec_SAddItemMsg _name_="vecAddItemMsg"/>;
				for each(var s1:SAddItemMsg in vecAddItemMsg)
					vecAddItemMsgXml.appendChild(s1.toXML());
				topXml.appendChild(vecAddItemMsgXml);
			}
			return topXml;
		}
	}
}
