/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BuyItemNotify.as
//  Purpose:      协议:商城相关协议, 函数:物品购买数量更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	import flash.events.Event;

	/**
	 * 函数BuyItemNotify[物品购买数量更新]的接收事件
	 */
	public final class REvt_BuyItemNotify extends Event
	{
		public static const DATA_RECEIVE:String = "MallProt_BuyItemNotify";
		public static const DATA_ERROR:String = "MallProt_BuyItemNotify_Error";

		public var oBuyItemInfo:SBuyItemInfo; //更新信息 dwInstID=0 表示整个更新列表清空数量（0点刷新）

		public function REvt_BuyItemNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BuyItemNotify/>;
			if(oBuyItemInfo != null)
				topXml.appendChild(oBuyItemInfo.toXML("oBuyItemInfo"));
			return topXml;
		}
	}
}
