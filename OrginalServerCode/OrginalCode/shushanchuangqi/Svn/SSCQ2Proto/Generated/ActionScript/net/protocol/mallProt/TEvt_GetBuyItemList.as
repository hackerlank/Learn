/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_GetBuyItemList.as
//  Purpose:      协议:商城相关协议, 函数:获取物品购买数量列表
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mallProt
{
	import flash.events.Event;

	/**
	 * 函数GetBuyItemList[获取物品购买数量列表]的返回事件
	 */
	public final class TEvt_GetBuyItemList extends Event
	{
		public static const DATA_RETURN:String = "MallProt_GetBuyItemList";
		public static const DATA_ERROR:String = "MallProt_GetBuyItemList_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var retParam:SRetParam_GetBuyItemList; //返回的参数

		public function TEvt_GetBuyItemList(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_GetBuyItemList ret={ret}/>;
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
