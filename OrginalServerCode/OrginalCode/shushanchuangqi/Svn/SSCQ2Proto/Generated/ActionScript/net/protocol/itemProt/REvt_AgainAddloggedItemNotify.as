/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AgainAddloggedItemNotify.as
//  Purpose:      协议:道具相关协议, 函数:再一次增加记录道具通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数AgainAddloggedItemNotify[再一次增加记录道具通知]的接收事件
	 */
	public final class REvt_AgainAddloggedItemNotify extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_AgainAddloggedItemNotify";
		public static const DATA_ERROR:String = "ItemProt_AgainAddloggedItemNotify_Error";

		public var rVecLoggedItem:Vector.<SLoggedItem>; //道具列表

		public function REvt_AgainAddloggedItemNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AgainAddloggedItemNotify/>;
			if(rVecLoggedItem != null)
			{
				var rVecLoggedItemXml:XML = <Vec_SLoggedItem _name_="rVecLoggedItem"/>;
				for each(var s1:SLoggedItem in rVecLoggedItem)
					rVecLoggedItemXml.appendChild(s1.toXML());
				topXml.appendChild(rVecLoggedItemXml);
			}
			return topXml;
		}
	}
}
