/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_CollectionInfoNotify.as
//  Purpose:      协议:收藏协议, 函数:收藏等级通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.collectionProt
{
	import flash.events.Event;

	/**
	 * 函数CollectionInfoNotify[收藏等级通知]的接收事件
	 */
	public final class REvt_CollectionInfoNotify extends Event
	{
		public static const DATA_RECEIVE:String = "CollectionProt_CollectionInfoNotify";
		public static const DATA_ERROR:String = "CollectionProt_CollectionInfoNotify_Error";

		public var oCollectionInfo:SCollectionInfo; //收藏信息

		public function REvt_CollectionInfoNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_CollectionInfoNotify/>;
			if(oCollectionInfo != null)
				topXml.appendChild(oCollectionInfo.toXML("oCollectionInfo"));
			return topXml;
		}
	}
}
