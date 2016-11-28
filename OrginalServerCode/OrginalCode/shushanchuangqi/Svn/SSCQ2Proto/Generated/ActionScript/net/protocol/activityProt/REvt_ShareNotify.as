/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_ShareNotify.as
//  Purpose:      协议:活力任务协议, 函数:成就分享通知
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.activityProt
{
	import flash.events.Event;

	/**
	 * 函数ShareNotify[成就分享通知]的接收事件
	 */
	public final class REvt_ShareNotify extends Event
	{
		public static const DATA_RECEIVE:String = "ActivityProt_ShareNotify";
		public static const DATA_ERROR:String = "ActivityProt_ShareNotify_Error";

		public var oActivityShare:SActivityShare; //成就分享信息

		public function REvt_ShareNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_ShareNotify/>;
			if(oActivityShare != null)
				topXml.appendChild(oActivityShare.toXML("oActivityShare"));
			return topXml;
		}
	}
}
