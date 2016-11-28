/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_StoreSizeChangeNotify.as
//  Purpose:      协议:道具相关协议, 函数:包裹或仓库容量改变通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数StoreSizeChangeNotify[包裹或仓库容量改变通知]的接收事件
	 */
	public final class REvt_StoreSizeChangeNotify extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_StoreSizeChangeNotify";
		public static const DATA_ERROR:String = "ItemProt_StoreSizeChangeNotify_Error";

		public var eStoreType:uint; //(枚举类型：EStoreType)存储类型
		public var wStoreSize:uint; //(无符号16位整数)包裹或仓库的容量

		public function REvt_StoreSizeChangeNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_StoreSizeChangeNotify eStoreType={eStoreType} wStoreSize={wStoreSize}/>;
			return topXml;
		}
	}
}
