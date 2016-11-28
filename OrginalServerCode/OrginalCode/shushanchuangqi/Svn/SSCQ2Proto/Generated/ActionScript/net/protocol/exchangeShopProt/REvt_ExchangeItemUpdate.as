/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ExchangeItemUpdate.as
//  Purpose:      协议:兑换商店, 函数:已兑换信息更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.exchangeShopProt
{
	import flash.events.Event;

	/**
	 * 函数ExchangeItemUpdate[已兑换信息更新]的接收事件
	 */
	public final class REvt_ExchangeItemUpdate extends Event
	{
		public static const DATA_RECEIVE:String = "ExchangeShopProt_ExchangeItemUpdate";
		public static const DATA_ERROR:String = "ExchangeShopProt_ExchangeItemUpdate_Error";

		public var oExchangeInfo:ExchangeInfo; //更新已兑换信息

		public function REvt_ExchangeItemUpdate(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ExchangeItemUpdate/>;
			if(oExchangeInfo != null)
				topXml.appendChild(oExchangeInfo.toXML("oExchangeInfo"));
			return topXml;
		}
	}
}
