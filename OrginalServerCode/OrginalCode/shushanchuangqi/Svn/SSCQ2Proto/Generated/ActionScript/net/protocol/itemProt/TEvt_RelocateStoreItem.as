/************************************************************************
//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)
//  File Name:    TEvt_RelocateStoreItem.as
//  Purpose:      协议:道具相关协议, 函数:包裹或仓库中道具换位置
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数RelocateStoreItem[包裹或仓库中道具换位置]的返回事件
	 */
	public final class TEvt_RelocateStoreItem extends Event
	{
		public static const DATA_RETURN:String = "ItemProt_RelocateStoreItem";
		public static const DATA_ERROR:String = "ItemProt_RelocateStoreItem_Error";

		public var ret:int; //0为成功，1为失败，2为超时
		public var origParam:SOrigParam_RelocateStoreItem; //原来的参数
		public var retParam:SRetParam_RelocateStoreItem; //返回的参数

		public function TEvt_RelocateStoreItem(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():String
		{
			var topXml:XML = <TEvt_RelocateStoreItem ret={ret}/>;
			if(origParam != null)
				topXml.appendChild(origParam.toXML("origParam"));
			if(retParam != null)
				topXml.appendChild(retParam.toXML("retParam"));
			return topXml.toXMLString();
		}
	}
}
