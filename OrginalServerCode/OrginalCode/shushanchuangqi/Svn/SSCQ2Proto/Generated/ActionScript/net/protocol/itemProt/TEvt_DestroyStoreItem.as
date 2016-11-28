/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_DestroyStoreItem.as
//  Purpose:      协议:道具相关协议, 函数:销毁包裹或仓库中的道具
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数DestroyStoreItem[销毁包裹或仓库中的道具]的返回事件
	 */
	public final class TEvt_DestroyStoreItem extends Event
	{
		public static const DATA_RETURN:String = "ItemProt_DestroyStoreItem";
		public static const DATA_ERROR:String = "ItemProt_DestroyStoreItem_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var origParam:SOrigParam_DestroyStoreItem; //原来的参数
		public var retParam:SRetParam_DestroyStoreItem; //返回的参数

		public function TEvt_DestroyStoreItem(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_DestroyStoreItem ret={ret}/>;
			if(origParam != null)
				topXml.appendChild(origParam.toXML("origParam"));
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
