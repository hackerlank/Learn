/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_OpenDepot.as
//  Purpose:      协议:道具相关协议, 函数:打开包裹或仓库
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.itemProt
{
	import flash.events.Event;

	/**
	 * 函数OpenDepot[打开包裹或仓库]的接收事件
	 */
	public final class REvt_OpenDepot extends Event
	{
		public static const DATA_RECEIVE:String = "ItemProt_OpenDepot";
		public static const DATA_ERROR:String = "ItemProt_OpenDepot_Error";

		public var eStoreType:uint; //(枚举类型：EStoreType)存储类型

		public function REvt_OpenDepot(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_OpenDepot eStoreType={eStoreType}/>;
			return topXml;
		}
	}
}
