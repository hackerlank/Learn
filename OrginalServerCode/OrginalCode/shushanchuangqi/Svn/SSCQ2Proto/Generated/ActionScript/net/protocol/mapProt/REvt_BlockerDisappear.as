/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BlockerDisappear.as
//  Purpose:      协议:地图相关功能的协议, 函数:通知地图上阻挡物消失
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.mapProt
{
	import flash.events.Event;

	/**
	 * 函数BlockerDisappear[通知地图上阻挡物消失]的接收事件
	 */
	public final class REvt_BlockerDisappear extends Event
	{
		public static const DATA_RECEIVE:String = "MapProt_BlockerDisappear";
		public static const DATA_ERROR:String = "MapProt_BlockerDisappear_Error";

		public var dwInstID:uint; //(无符号32位整数)阻挡物唯一ID

		public function REvt_BlockerDisappear(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BlockerDisappear dwInstID={dwInstID}/>;
			return topXml;
		}
	}
}
