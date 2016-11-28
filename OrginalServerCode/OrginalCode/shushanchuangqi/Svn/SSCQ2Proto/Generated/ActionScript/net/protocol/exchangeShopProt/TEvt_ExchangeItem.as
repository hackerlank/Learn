/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ExchangeItem.as
//  Purpose:      协议:兑换商店, 函数:兑换物品
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.exchangeShopProt
{
	import flash.events.Event;

	/**
	 * 函数ExchangeItem[兑换物品]的返回事件
	 */
	public final class TEvt_ExchangeItem extends Event
	{
		public static const DATA_RETURN:String = "ExchangeShopProt_ExchangeItem";
		public static const DATA_ERROR:String = "ExchangeShopProt_ExchangeItem_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ExchangeItem; //返回的参数

		public function TEvt_ExchangeItem(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ExchangeItem ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
