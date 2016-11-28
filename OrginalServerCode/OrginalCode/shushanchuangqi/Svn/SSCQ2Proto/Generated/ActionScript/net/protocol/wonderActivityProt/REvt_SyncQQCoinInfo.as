/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SyncQQCoinInfo.as
//  Purpose:      协议:精彩活动, 函数:同步QQ养成信息
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.wonderActivityProt
{
	import flash.events.Event;

	/**
	 * 函数SyncQQCoinInfo[同步QQ养成信息]的接收事件
	 */
	public final class REvt_SyncQQCoinInfo extends Event
	{
		public static const DATA_RECEIVE:String = "WonderActivityProt_SyncQQCoinInfo";
		public static const DATA_ERROR:String = "WonderActivityProt_SyncQQCoinInfo_Error";

		public var oQQCoinInfo:SQQCoinActInfo; //Q养成活动信息

		public function REvt_SyncQQCoinInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SyncQQCoinInfo/>;
			if(oQQCoinInfo != null)
				topXml.appendChild(oQQCoinInfo.toXML("oQQCoinInfo"));
			return topXml;
		}
	}
}
