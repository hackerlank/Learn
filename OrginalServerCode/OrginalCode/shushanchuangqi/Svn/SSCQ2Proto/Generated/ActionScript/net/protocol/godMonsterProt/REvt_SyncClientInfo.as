/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SyncClientInfo.as
//  Purpose:      协议:天元神兽协议, 函数:同步数据
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.godMonsterProt
{
	import flash.events.Event;

	/**
	 * 函数SyncClientInfo[同步数据]的接收事件
	 */
	public final class REvt_SyncClientInfo extends Event
	{
		public static const DATA_RECEIVE:String = "GodMonsterProt_SyncClientInfo";
		public static const DATA_ERROR:String = "GodMonsterProt_SyncClientInfo_Error";

		public var sInfo:SyncInfoToClient; //客户端数据

		public function REvt_SyncClientInfo(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SyncClientInfo/>;
			if(sInfo != null)
				topXml.appendChild(sInfo.toXML("sInfo"));
			return topXml;
		}
	}
}
