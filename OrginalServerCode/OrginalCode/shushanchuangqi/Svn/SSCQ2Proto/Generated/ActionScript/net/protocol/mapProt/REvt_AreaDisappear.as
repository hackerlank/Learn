/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_AreaDisappear.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知地图上区域消失
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;

	/**
	 * 函数AreaDisappear[通知地图上区域消失]的接收事件
	 */
	public final class REvt_AreaDisappear extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_AreaDisappear";
		public static const DATA_ERROR:String = "MapProt_AreaDisappear_Error";

		public var dwAreaID:uint; //(无符号32位整数)区域实例ID

		public function REvt_AreaDisappear(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_AreaDisappear dwAreaID={dwAreaID}/>;
			return topXml;
		}
	}
}
