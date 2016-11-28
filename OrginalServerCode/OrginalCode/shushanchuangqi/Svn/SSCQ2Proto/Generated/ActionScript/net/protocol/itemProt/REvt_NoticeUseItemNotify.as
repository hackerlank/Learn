/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_NoticeUseItemNotify.as
//  Purpose:      协议:道具相关协议, 函数:更新记录的堆叠道具通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数NoticeUseItemNotify[更新记录的堆叠道具通知]的接收事件
	 */
	public final class REvt_NoticeUseItemNotify extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_NoticeUseItemNotify";
		public static const DATA_ERROR:String = "ItemProt_NoticeUseItemNotify_Error";

		public var wItemID:uint; //(无符号16位整数)ID
		public var dwNum:uint; //(无符号32位整数)使用物品数量
		public var vecRes:Vector.<SResource>; //资源
		public var vecItem:Vector.<SItemGenInfo>; //物品

		public function REvt_NoticeUseItemNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_NoticeUseItemNotify wItemID={wItemID} dwNum={dwNum}/>;
			if(vecRes != null)
			{
				var vecResXml:XML = <Vec_SResource _name_="vecRes"/>;
				for each(var s1:SResource in vecRes)
					vecResXml.appendChild(s1.toXML());
				topXml.appendChild(vecResXml);
			}
			if(vecItem != null)
			{
				var vecItemXml:XML = <Vec_SItemGenInfo _name_="vecItem"/>;
				for each(var s2:SItemGenInfo in vecItem)
					vecItemXml.appendChild(s2.toXML());
				topXml.appendChild(vecItemXml);
			}
			return topXml;
		}
	}
}
