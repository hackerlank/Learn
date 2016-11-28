/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SyncChestInfo.as
//  Purpose:      协议:不好归类的小协议, 函数:通知宝箱活动剩余轮次
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.miscProt
{
	import flash.events.Event;

	/**
	 * 函数SyncChestInfo[通知宝箱活动剩余轮次]的接收事件
	 */
	public final class REvt_SyncChestInfo extends Event
	{
		public static const DATA_RECEIVE:String = "MiscProt_SyncChestInfo";
		public static const DATA_ERROR:String = "MiscProt_SyncChestInfo_Error";

		public var sInfo:SGodChestInfo; //宝箱信息

		public function REvt_SyncChestInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SyncChestInfo/>;
			if(sInfo != null)
				topXml.appendChild(sInfo.toXML("sInfo"));
			return topXml;
		}
	}
}
