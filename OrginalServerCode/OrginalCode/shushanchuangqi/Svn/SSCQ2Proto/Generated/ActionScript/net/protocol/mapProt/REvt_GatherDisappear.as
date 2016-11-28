/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_GatherDisappear.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知地图上采集物消失
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;

	/**
	 * 函数GatherDisappear[通知地图上采集物消失]的接收事件
	 */
	public final class REvt_GatherDisappear extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_GatherDisappear";
		public static const DATA_ERROR:String = "MapProt_GatherDisappear_Error";

		public var dwGatherID:uint; //(无符号32位整数)采集物ID
		public var bDieFade:Boolean; //true为采集后消失，false为移出视野

		public function REvt_GatherDisappear(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_GatherDisappear dwGatherID={dwGatherID} bDieFade={bDieFade}/>;
			return topXml;
		}
	}
}
