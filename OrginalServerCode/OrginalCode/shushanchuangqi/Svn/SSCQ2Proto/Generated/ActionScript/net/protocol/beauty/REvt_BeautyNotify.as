/************************************************************************
//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)
//  File Name:    REvt_BeautyNotify.as
//  Purpose:      协议:美女系统, 函数:美女信息更新
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

package net.protocol.beauty
{
	import flash.events.Event;

	/**
	 * 函数BeautyNotify[美女信息更新]的接收事件
	 */
	public final class REvt_BeautyNotify extends Event
	{
		public static const DATA_RECEIVE:String = "Beauty_BeautyNotify";
		public static const DATA_ERROR:String = "Beauty_BeautyNotify_Error";

		public var oBeauty:SBeauty; //美女信息

		public function REvt_BeautyNotify(type:String, bubbles:Boolean = false, cancelable:Boolean = false)
		{
			super(type, bubbles, cancelable);
		}

		/**
		 * 转换为XML
		 */
		public function toXML():XML
		{
			var topXml:XML = <REvt_BeautyNotify/>;
			if(oBeauty != null)
				topXml.appendChild(oBeauty.toXML("oBeauty"));
			return topXml;
		}
	}
}
