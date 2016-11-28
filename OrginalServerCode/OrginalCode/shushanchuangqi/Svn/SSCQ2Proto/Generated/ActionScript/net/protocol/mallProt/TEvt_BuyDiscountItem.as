/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_BuyDiscountItem.as
//  Purpose:      协议:商城相关协议, 函数:购买商场限购道具
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	import flash.events.Event;

	/**
	 * 函数BuyDiscountItem[购买商场限购道具]的返回事件
	 */
	public final class TEvt_BuyDiscountItem extends Event
	{
		public static const DATA_RETURN:String = "MallProt_BuyDiscountItem";
		public static const DATA_ERROR:String = "MallProt_BuyDiscountItem_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_BuyDiscountItem; //返回的参数

		public function TEvt_BuyDiscountItem(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_BuyDiscountItem ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
