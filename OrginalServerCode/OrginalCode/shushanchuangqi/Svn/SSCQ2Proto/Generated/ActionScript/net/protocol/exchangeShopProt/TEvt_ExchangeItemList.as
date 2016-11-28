/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_ExchangeItemList.as
//  Purpose:      协议:兑换商店, 函数:已兑换列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.exchangeShopProt
{
	import flash.events.Event;

	/**
	 * 函数ExchangeItemList[已兑换列表]的返回事件
	 */
	public final class TEvt_ExchangeItemList extends Event
	{
		public static const DATA_RETURN:String = "ExchangeShopProt_ExchangeItemList";
		public static const DATA_ERROR:String = "ExchangeShopProt_ExchangeItemList_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_ExchangeItemList; //返回的参数

		public function TEvt_ExchangeItemList(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_ExchangeItemList ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
