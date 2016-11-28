/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_SyncData.as
//  Purpose:      协议:圣陵协议, 函数:玩家数据推送（0点)
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.shengLingProt
{
	import flash.events.Event;

	/**
	 * 函数SyncData[玩家数据推送（0点)]的接收事件
	 */
	public final class REvt_SyncData extends Event
	{
		public static const DATA_RECEIVE:String = "ShengLingProt_SyncData";
		public static const DATA_ERROR:String = "ShengLingProt_SyncData_Error";

		public var sInfo:SShengLingInfo; //玩家数据

		public function REvt_SyncData(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_SyncData/>;
			if(sInfo != null)
				topXml.appendChild(sInfo.toXML("sInfo"));
			return topXml;
		}
	}
}
