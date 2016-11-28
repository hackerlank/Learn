/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GatherChange.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知地图上采集物改变
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;

	/**
	 * 函数GatherChange[通知地图上采集物改变]的接收事件
	 */
	public final class REvt_GatherChange extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_GatherChange";
		public static const DATA_ERROR:String = "MapProt_GatherChange_Error";

		public var dwGatherID:uint; //(无符号32位整数)采集物ID
		public var rGatherAppear:SGatherAppear; //采集物外观

		public function REvt_GatherChange(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GatherChange dwGatherID={dwGatherID}/>;
			if(rGatherAppear != null)
				topXml.appendChild(rGatherAppear.toXML("rGatherAppear"));
			return topXml;
		}
	}
}
