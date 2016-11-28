/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_StoreNotify.as
//  Purpose:      协议:道具相关协议, 函数:包裹或仓库道具通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数StoreNotify[包裹或仓库道具通知]的接收事件
	 */
	public final class REvt_StoreNotify extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_StoreNotify";
		public static const DATA_ERROR:String = "ItemProt_StoreNotify_Error";

		public var eStoreType:uint; //(枚举类型：EStoreType)存储类型
		public var wStoreSize:uint; //(无符号16位整数)包裹或仓库的容量
		public var vecStoreItem:Vector.<SItem>; //包裹或仓库中道具的列表

		public function REvt_StoreNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_StoreNotify eStoreType={eStoreType} wStoreSize={wStoreSize}/>;
			if(vecStoreItem != null)
			{
				var vecStoreItemXml:XML = <Vec_SItem _name_="vecStoreItem"/>;
				for each(var s1:SItem in vecStoreItem)
					vecStoreItemXml.appendChild(s1.toXML());
				topXml.appendChild(vecStoreItemXml);
			}
			return topXml;
		}
	}
}
