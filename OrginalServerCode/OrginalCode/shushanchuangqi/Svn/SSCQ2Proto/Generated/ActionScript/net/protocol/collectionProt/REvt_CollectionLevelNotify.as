/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_CollectionLevelNotify.as
//  Purpose:      协议:收藏协议, 函数:收藏等级通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.collectionProt
{
	import flash.events.Event;

	/**
	 * 函数CollectionLevelNotify[收藏等级通知]的接收事件
	 */
	public final class REvt_CollectionLevelNotify extends Event
	{
		public static const DATA_RECEIVE:String = "CollectionProt_CollectionLevelNotify";
		public static const DATA_ERROR:String = "CollectionProt_CollectionLevelNotify_Error";

		public var wLevel:uint; //(无符号16位整数)收藏等级

		public function REvt_CollectionLevelNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_CollectionLevelNotify wLevel={wLevel}/>;
			return topXml;
		}
	}
}
